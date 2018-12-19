//
// Created by Maksym Maisak on 19/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_RESOURCELOADER_H
#define SAXION_Y2Q2_RENDERING_RESOURCELOADER_H

#include "SFML/Graphics.hpp"
#include <exception>
#include "CallableTraits.h"

namespace en {

    struct InvalidResourceLoader {};

    template<typename TResource>
    struct ResourceLoader : InvalidResourceLoader {

        template<typename... Args>
        inline static std::shared_ptr<TResource> load(Args&&...) {
            throw "No resource loader is defined for this resource type";
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
