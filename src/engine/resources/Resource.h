//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_RESOURCES_H
#define SAXION_Y2Q1_CPP_RESOURCES_H

#include <memory>
#include <type_traits>
#include <string>
#include <SFML/Graphics.hpp>
#include "HashedString.h"

namespace en {

    struct InvalidLoader {};

    template<typename TResource>
    struct Loader : InvalidLoader {};

    template<typename TResource, HashedString::hash_type Id, typename TDefaultLoader = Loader<TResource>>
    class Resource {

    public:
        /// Takes in parameters for the loader to use in case the resource is not present.
        template<typename TLoader = TDefaultLoader, typename... Args>
        static std::shared_ptr<TResource> get(Args&&... args) {

            static_assert(!std::is_base_of_v<InvalidLoader, TLoader>, "There is no resource loader for this type of resource!");

            if (m_resource) return m_resource;
            return m_resource = TLoader::load(std::forward<Args>(args)...);
        }

    private:
        inline static std::shared_ptr<TResource> m_resource = {};
    };
}

#endif //SAXION_Y2Q1_CPP_RESOURCES_H
