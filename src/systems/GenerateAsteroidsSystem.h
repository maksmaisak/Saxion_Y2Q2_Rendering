//
// Created by Maksym Maisak on 30/10/18.
//

#ifndef SAXION_Y2Q1_CPP_GENERATEASTEROIDSSYSTEM_H
#define SAXION_Y2Q1_CPP_GENERATEASTEROIDSSYSTEM_H

#include "Engine.h"
#include "System.h"

class GenerateAsteroidsSystem : public en::System {



public:
    void update(float dt) override;

private:
    std::size_t m_targetNumAsteroids = 10;
};


#endif //SAXION_Y2Q1_CPP_GENERATEASTEROIDSSYSTEM_H
