//
// Created by Maksym Maisak on 3/11/18.
//

#ifndef SAXION_Y2Q1_CPP_SCORESYSTEM_H
#define SAXION_Y2Q1_CPP_SCORESYSTEM_H

#include "Engine.h"
#include "System.h"
#include "Asteroid.h"
#include "Restart.h"

class ScoreSystem : public en::System, en::Receiver<en::ComponentWillBeRemoved<Asteroid>>, en::Receiver<Restart> {

public:
    void start() override;
    void draw() override;

private:
    sf::Text m_scoreText;

    void receive(const en::ComponentWillBeRemoved<Asteroid>& info) override;
    void receive(const Restart& info) override;
};

#endif //SAXION_Y2Q1_CPP_SCORESYSTEM_H
