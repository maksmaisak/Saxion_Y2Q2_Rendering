//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H
#define SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H

#include "Engine.h"
#include <memory>
#include <string>
#include "Behavior.h"

class GameOverScreen : public en::Behavior {

    using Behavior::Behavior;

public:
    void start() override;
    void draw() override;

private:
    std::shared_ptr<sf::Font> m_fontPtr;
    std::vector<sf::Text> m_texts;

    sf::Text& addLine(sf::String textString);
};

#endif //SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H
