//
// Created by Maksym Maisak on 29/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYERDEATHSYSTEM_H
#define SAXION_Y2Q1_CPP_PLAYERDEATHSYSTEM_H

#include "Engine.h"
#include "System.h"
#include "Messaging.h"
#include "Collision.h"

class PlayerDeathSystem : public en::System, en::Receiver<en::Collision> {

public:
    void receive(const en::Collision& info) override;

private:
    bool m_isAtGameOverScreen = false;
};


#endif //SAXION_Y2Q1_CPP_PLAYERDEATHSYSTEM_H
