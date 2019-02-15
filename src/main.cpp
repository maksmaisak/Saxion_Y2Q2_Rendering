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
#include "components/Sprite.h"
#include "components/Transform.h"
#include "components/UIRect.h"

#include "TestScene.h"
#include "LightingScene.h"
#include "TerrainScene.h"
#include "LuaScene.h"
#include "UIEventSystem.h"

int main() {

    std::cout << "Starting Game" << std::endl;

    auto engine = std::make_unique<en::Engine>();
    engine->initialize();

    {
        engine->addSystem<en::TransformHierarchySystem>();
        engine->addSystem<en::RenderSystem>(false);
        engine->addSystem<en::UIEventSystem>();

        engine->addSystem<en::PhysicsSystem>().setGravity({0, -9.8, 0});

        engine->addSystem<en::DestroyByTimerSystem>();
        engine->addSystem<en::DestroySystem>();
    }

    en::LuaState& lua = engine->getLuaState();
    lua_getglobal(lua, "Config");
    std::optional<std::string> startScene = lua.tryGetField<std::string>("startScene");
    if (startScene)
        engine->getSceneManager().setCurrentScene<en::LuaScene>(engine->getLuaState(), *startScene);
    lua.pop();

    //engine->getSceneManager().setCurrentScene<TestScene>();     // Assignment 2
    //engine->getSceneManager().setCurrentScene<LightingScene>(); // Assignment 3
    //engine->getSceneManager().setCurrentScene<TerrainScene>();  // Assignment 4

    engine->run();

    return 0;
}


