//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_IDS_H
#define SAXION_Y2Q1_CPP_IDS_H

#include "HashedString.h"
#include "Resource.h"

template<>
struct en::Loader<sf::Font> {

    static std::shared_ptr<sf::Font> load(const std::string& filename) {
        auto fontPtr = std::make_shared<sf::Font>();
        bool didLoadFont = fontPtr->loadFromFile(filename);
        assert(didLoadFont);
        return fontPtr;
    }
};

/// Some definitions of in one place.
namespace fonts {

    namespace ids {
        inline constexpr auto Main = "FontMain"_hs;
        inline constexpr auto Diagnostics = "FontDiagnostics"_hs;
    }

    using Main = en::Resource<sf::Font, ids::Main>;
    using Diagnostics = en::Resource<sf::Font, ids::Diagnostics>;

    namespace paths {
        inline constexpr auto Main = "assets/hyperspace/Hyperspace.otf";
        inline constexpr auto Diagnostics = "assets/Menlo.ttc";
    }
}
#endif //SAXION_Y2Q1_CPP_IDS_H
