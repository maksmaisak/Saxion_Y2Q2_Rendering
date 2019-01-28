#include <iostream>
#include <memory>

#include "Engine.h"
#include "Actor.h"
#include "systems/TransformHierarchySystem.h"
#include "systems/DestroySystem.h"
#include "systems/DestroyByTimerSystem.h"
#include "systems/RenderSystem.h"
#include "systems/PhysicsSystem.h"

#include "components/RenderInfo.h"
#include "components/Camera.h"

#include "TestScene.h"
#include "LightingScene.h"
#include "TerrainScene.h"
#include "LuaScene.h"

int main() {

    std::cout << "Starting Game" << std::endl;

    auto engine = std::make_unique<en::Engine>();
    engine->initialize();

    {
        engine->addSystem<en::TransformHierarchySystem>();
        engine->addSystem<en::RenderSystem>(false);

        engine->addSystem<en::PhysicsSystem>().setGravity({0, -9.8, 0});

        engine->addSystem<en::DestroyByTimerSystem>();
        engine->addSystem<en::DestroySystem>();
    }

    //engine->getSceneManager().setCurrentScene<TestScene>();
    engine->getSceneManager().setCurrentScene<LightingScene>();
    //engine->getSceneManager().setCurrentScene<TerrainScene>();
    //engine->getSceneManager().setCurrentScene<LuaScene>("assets/scripts/luaScene.lua");
    //engine->getSceneManager().setCurrentScene<LuaScene>("assets/scripts/arena.lua");
    //engine->getSceneManager().setCurrentScene<LuaScene>("assets/scripts/stressTest.lua");

    engine->run();

    return 0;
}



