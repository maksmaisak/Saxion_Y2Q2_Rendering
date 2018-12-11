//
// Created by Maksym Maisak on 26/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENTPOOL_H
#define SAXION_Y2Q1_CPP_COMPONENTPOOL_H

#include <vector>
#include <limits>
#include "Entity.h"
#include "Messaging.h"
#include "EntityEvents.h"

namespace en {

    class ComponentPoolBase {

        static_assert(std::is_unsigned_v<en::Entity>, "Entity must be and unsigned integer type.");

    public:
        using const_iterator = std::vector<en::Entity>::const_iterator;
        using iterator = const_iterator;
        using index_type = std::vector<en::Entity>::size_type;

        const index_type nullIndex = std::numeric_limits<index_type>::max();

        virtual ~ComponentPoolBase() = default;

        inline std::size_t size() const {return m_indexToEntity.size();}
        bool contains(en::Entity entity) const;
        bool remove(en::Entity entity);
        virtual void clear();

        inline const_iterator cbegin() const {return m_indexToEntity.cbegin();}
        inline const_iterator cend()   const {return m_indexToEntity.cend();  }
        inline iterator begin()        const {return cbegin();}
        inline iterator end()          const {return cend();  }

    protected:
        std::vector<en::Entity> m_indexToEntity;
        std::vector<index_type> m_entityIdToIndex;

        index_type insert(en::Entity entity);
        virtual index_type removeInternal(en::Entity entity);
    };

    template<typename TComponent>
    class ComponentPool : public ComponentPoolBase {

        static_assert(
            !std::is_aggregate_v<TComponent> || (std::is_move_constructible_v<TComponent> || std::is_copy_constructible_v<TComponent>),
            "Aggregate component types must be either move or copy constructible."
        );
        static_assert(
            std::is_move_assignable_v<TComponent> || std::is_copy_assignable_v<TComponent>,
            "Component types must be either move or copy assignable."
        );

    public:
        template<typename... Args>
        std::tuple<index_type, TComponent&> insert(en::Entity entity, Args&& ... args);
        std::tuple<index_type, TComponent&> insert(en::Entity entity, const TComponent& component);

        TComponent& get(en::Entity entity);
        TComponent* tryGet(en::Entity entity);
        inline void clear() final;

    protected:
        index_type removeInternal(en::Entity entity) final;

    private:
        std::vector<TComponent> m_indexToComponent;
    };

    template<typename TComponent>
    template<typename... Args>
    std::tuple<ComponentPoolBase::index_type, TComponent&> ComponentPool<TComponent>::insert(en::Entity entity, Args&&... args) {

        const index_type index = ComponentPoolBase::insert(entity);

        if constexpr (std::is_aggregate_v<TComponent>) {
            if constexpr (std::is_move_constructible_v<TComponent>) {
                m_indexToComponent.push_back(TComponent{std::forward<Args>(args)...});
            } else {
                m_indexToComponent.push_back((const TComponent&)TComponent{std::forward<Args>(args)...});
            }
        } else {
            m_indexToComponent.emplace_back(std::forward<Args>(args)...);
        }

        Receiver<ComponentAdded<TComponent>>::accept({entity, m_indexToComponent.back()});

        return std::make_tuple(index, std::ref(m_indexToComponent.back()));
    }

    template<typename TComponent>
    std::tuple<ComponentPoolBase::index_type, TComponent&> ComponentPool<TComponent>::insert(en::Entity entity, const TComponent& component) {

        const index_type index = ComponentPoolBase::insert(entity);
        m_indexToComponent.push_back(component);

        Receiver<ComponentAdded<TComponent>>::accept({entity, m_indexToComponent.back()});

        return std::make_tuple(index, std::ref(m_indexToComponent.back()));
    }

    template<typename TComponent>
    TComponent& ComponentPool<TComponent>::get(en::Entity entity) {

        assert(contains(entity));
        return m_indexToComponent[m_entityIdToIndex[getId(entity)]];
    }

    template<typename TComponent>
    TComponent* ComponentPool<TComponent>::tryGet(en::Entity entity) {

        if (!contains(entity)) return nullptr;
        return &m_indexToComponent[m_entityIdToIndex[getId(entity)]];
    }

    template<typename TComponent>
    void ComponentPool<TComponent>::clear() {

        ComponentPoolBase::clear();
        m_indexToComponent.clear();
    }

    template<typename TComponent>
    ComponentPoolBase::index_type ComponentPool<TComponent>::removeInternal(en::Entity entity) {

        const index_type index = ComponentPoolBase::removeInternal(entity);
        if (index == nullIndex) return nullIndex;

        Receiver<ComponentWillBeRemoved<TComponent>>::accept({entity, m_indexToComponent[index]});

        // Move and pop to keep the storage contiguous.
        if constexpr (std::is_move_assignable_v<TComponent>) {
            m_indexToComponent[index] = std::move(m_indexToComponent.back());
        } else {
            m_indexToComponent[index] = m_indexToComponent.back();
        }
        m_indexToComponent.pop_back();

        return index;
    }
}

#endif //SAXION_Y2Q1_CPP_COMPONENTPOOL_H
