//
// Created by Maksym Maisak on 27/10/18.
//

#ifndef SAXION_Y2Q1_CPP_DIAGNOSTICSSYSTEM_H
#define SAXION_Y2Q1_CPP_DIAGNOSTICSSYSTEM_H

#include "System.h"
#include <memory>
#include <SFML/Graphics.hpp>

class DiagnosticsSystem : public en::System {

public:
    void start() override;
    void draw() override;

private:
    std::unique_ptr<sf::Text> m_fpsCounterPtr;
    sf::Clock m_timer;
};


#endif //SAXION_Y2Q1_CPP_DIAGNOSTICSSYSTEM_H
