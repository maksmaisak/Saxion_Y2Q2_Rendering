//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <optional>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include "EntityRegistry.h"
#include "Entity.h"
#include "System.h"
#include "BehaviorSystem.h"
#include "Scheduler.h"
#include "SceneManager.h"
#include "LuaState.h"
#include "ClosureHelper.h"

namespace en {

    class Behavior;
    class Actor;

    class Engine {

    public:
        Engine();
        virtual ~Engine() = default;
        Engine(const Engine& other) = delete;
        Engine& operator=(const Engine& other) = delete;
        Engine(Engine&& other) = delete;
        Engine& operator=(Engine&& other) = delete;

        void initialize();
        void run();

        inline EntityRegistry& getRegistry()   { return m_registry; }
        inline Scheduler& getScheduler()       { return m_scheduler; }
        inline sf::RenderWindow& getWindow()   { return m_window; }
        inline SceneManager& getSceneManager() { return m_sceneManager; }
        inline LuaState& getLuaState()         { return m_lua; }
        inline float getFps()                  { return m_fps; }

        Actor actor(Entity entity);
        Actor makeActor();
        Actor makeActor(const std::string& name);
        Actor findByName(const std::string& name);

        template<typename TSystem, typename... Args>
        TSystem& addSystem(Args&& ... args);

        /// Makes sure a system to handle a given behavior type is in place.
        template<typename TBehavior>
        bool ensureBehaviorSystem();

        void testMemberFunction();

    protected:
        virtual void initializeWindow(sf::RenderWindow& window);

    private:

        EntityRegistry m_registry;
        LuaState m_lua;
        Scheduler m_scheduler;
        sf::RenderWindow m_window;
        SceneManager m_sceneManager;

        std::vector<std::unique_ptr<System>> m_systems;
        std::set<std::type_index> m_behaviorSystemPresence;

        float m_fps = 0.f;

        void printGLContextVersionInfo();
        void initializeGlew();
        void initializeLua();

        void update(float dt);
        void draw();
        void processWindowEvents();
    };

    template<typename TSystem, typename... Args>
    TSystem& Engine::addSystem(Args&&... args) {

        auto ptr = std::make_unique<TSystem>(std::forward<Args>(args)...);
        TSystem& system = *ptr;
        m_systems.push_back(std::move(ptr));

        system.init(*this);
        system.start();
        return system;
    }

    template<typename TBehavior>
    bool Engine::ensureBehaviorSystem() {

        static_assert(std::is_base_of_v<Behavior, TBehavior>);

        // TODO Use CustomTypeIndex for this.
        auto typeIndex = std::type_index(typeid(TBehavior));
        if (m_behaviorSystemPresence.find(typeIndex) == m_behaviorSystemPresence.end()) {

            addSystem<BehaviorSystem<TBehavior>>();
            m_behaviorSystemPresence.insert(typeIndex);
            return true;
        }

        return false;
    }
}

#endif //SAXION_Y2Q1_CPP_ENGINE_H
