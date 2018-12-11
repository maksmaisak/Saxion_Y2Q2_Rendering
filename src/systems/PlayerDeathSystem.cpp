//
// Created by Maksym Maisak on 29/10/18.
//

#include "PlayerDeathSystem.h"
#include <optional>
#include <tuple>
#include "Actor.h"
#include "Asteroid.h"
#include "Player.h"
#include "Factory.h"
#include "Restart.h"
#include "Destroy.h"
#include "GameOverScreen.h"

void destroyPlayer(en::Engine& engine, Entity player) {

    auto& registry = engine.getRegistry();
    registry.add<en::Destroy>(player);
    registry.get<Player>(player).exhaustParticleSystem->setIsEmissionActive(false);
    for (Entity child : registry.get<en::Transformable>(player).getChildren()) {
        engine.setParent(child, std::nullopt);
    }
}

void makeGameOverScreen(en::Engine& engine) {

    engine.makeActor().add<GameOverScreen>();
}

void PlayerDeathSystem::receive(const en::Collision& collision) {

    if (m_isAtGameOverScreen) return;

    auto [success, player, asteroid] = en::getCollision<Player, Asteroid>(*m_registry, collision);
    if (!success) return;

    destroyPlayer(*m_engine, player);
    makeGameOverScreen(*m_engine);

    m_engine->getScheduler().delay(sf::seconds(4.f), [this](){
        m_registry->destroyAll();
        en::Receiver<Restart>::accept({});
        game::makeMainLevel(*m_engine);
        m_isAtGameOverScreen = false;
    });
    m_isAtGameOverScreen = true;
}