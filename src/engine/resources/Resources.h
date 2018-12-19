//
// Created by Maksym Maisak on 19/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RESOURCES_H
#define SAXION_Y2Q2_RENDERING_RESOURCES_H

#include "ResourceLoader.h"
#include <memory>
#include <map>
#include <type_traits>
#include <algorithm>

namespace en {

    template<typename TResource>
    class Resources {

    public:

        /// Gets a resource by given key.
        /// If not present, tries to load the resource with given loader arguments.
        /// If no loader arguments given and loader can't be called with no arguments, tries to pass the key to the loader.
        template<typename TLoader = ResourceLoader<TResource>, typename... Args>
        inline static std::shared_ptr<TResource> get(const std::string& key, Args&&... args) {

            auto it = m_resources.find(key);
            if (it != m_resources.end()) return it->second;

            bool didEmplace = false;

            if constexpr (sizeof...(Args) > 0 || isCallableParameterless<decltype(&TLoader::load)>)
                std::tie(it, didEmplace) = m_resources.emplace(key, TLoader::load(std::forward<Args>(args)...));
            else if constexpr (isCallable<decltype(&TLoader::load), decltype(key)>)
                std::tie(it, didEmplace) = m_resources.emplace(key, TLoader::load(key));
            else
                throw "Invalid parameters for resource loader.";

            assert(didEmplace);
            return it->second;
        }

        /// Removes all resources not referenced elsewhere.
        inline static std::size_t removeUnused() {

            std::size_t numRemoved = 0;
            for (auto it = m_resources.begin(); it != m_resources.end();) {
                if (it->second.unique()) {
                    it = m_resources.erase(it);
                    ++numRemoved;
                } else {
                    ++it;
                }
            }

            return numRemoved;
        }

    private:
        static std::map<std::string, std::shared_ptr<TResource>> m_resources;
    };

    // Using inline static to avoid defining this out of the class body causes clang to segfault :(
    template<typename TResource>
    std::map<std::string, std::shared_ptr<TResource>> Resources<TResource>::m_resources;
}

#endif //SAXION_Y2Q2_RENDERING_RESOURCES_H
