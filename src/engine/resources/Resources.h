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
        /// The default loader does one of these, in order of priority:
        /// - Uses a custom ResourceLoader<TResource> template specialization, if exists.
        /// - Uses TResource::load(args), if exists.
        /// - Uses TResource::TResource(args), if exists.
        /// - Otherwise a compile error.
        template<typename TLoader = ResourceLoader<TResource>, typename... Args>
        inline static std::shared_ptr<TResource> get(const std::string& key, Args&&... args) {

            auto it = m_resources.find(key);
            if (it != m_resources.end()) return it->second;

            bool didAdd = false;

            // Fall back to constructor if there is no valid loader.
            if constexpr (std::is_base_of_v<NoLoader, TLoader>) {

                if constexpr (sizeof...(Args) > 0 || std::is_constructible_v<TResource>)
                    std::tie(it, didAdd) = m_resources.emplace(key, std::make_shared<TResource>(std::forward<Args>(args)...));
                else if constexpr (std::is_constructible_v<TResource, decltype(key)>)
                    std::tie(it, didAdd) = m_resources.emplace(key, std::make_shared<TResource>(key));
                else
                    throw "Invalid parameters for resource constructor.";

            } else {

                if constexpr (sizeof...(Args) > 0 || std::is_invocable_v<decltype(&TLoader::load)>)
                    std::tie(it, didAdd) = m_resources.emplace(key, TLoader::load(std::forward<Args>(args)...));
                else if constexpr (std::is_invocable_v<decltype(&TLoader::load), decltype(key)>)
                    std::tie(it, didAdd) = m_resources.emplace(key, TLoader::load(key));
                else
                    throw "Invalid parameters for resource loader.";
            }

            assert(didAdd);
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
