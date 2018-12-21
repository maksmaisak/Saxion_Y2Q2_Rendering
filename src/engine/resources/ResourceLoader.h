//
// Created by Maksym Maisak on 19/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RESOURCELOADER_H
#define SAXION_Y2Q2_RENDERING_RESOURCELOADER_H

#include "SFML/Graphics.hpp"
#include <exception>
#include <type_traits>

namespace en {

    struct NoLoader {};

    // Base template
    template<typename TResource, typename SFINAEDummy = void>
    struct ResourceLoader : NoLoader {};

    using filename_t = const std::string&;

    // If TResource::load(const std::string&) exists
    template<typename TResource>
    struct ResourceLoader<TResource, std::enable_if_t<std::is_invocable_v<decltype(&TResource::load), filename_t>>> {

        inline static std::shared_ptr<TResource> load(filename_t filename) {

            if constexpr (std::is_convertible_v<std::invoke_result_t<decltype(&TResource::load), filename_t>, std::shared_ptr<TResource>>)
                return TResource::load(filename);
            else
                return std::shared_ptr<TResource>(TResource::load(filename));
        }
    };

    template<>
    struct ResourceLoader<sf::Font> {

        inline static std::shared_ptr<sf::Font> load(const std::string& filename) {

            auto fontPtr = std::make_shared<sf::Font>();
            bool didLoadFont = fontPtr->loadFromFile(filename);
            assert(didLoadFont);
            return fontPtr;
        }
    };
}

#endif //SAXION_Y2Q2_RENDERING_RESOURCELOADER_H
