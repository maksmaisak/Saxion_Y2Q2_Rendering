#include <iostream>
#include <memory>

#include "Engine.h"
#include "Actor.h"
#include "systems/TransformHierarchySystem.h"
#include "systems/DestroySystem.h"
#include "systems/DestroyByTimerSystem.h"
#include "systems/RenderSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/UIEventSystem.h"
#include "systems/TweenSystem.h"

#include "components/RenderInfo.h"
#include "components/Camera.h"
#include "components/Transform.h"
#include "components/UIRect.h"
#include "components/Sprite.h"
#include "components/Text.h"

#include "TestScene.h"
#include "LightingScene.h"
#include "TerrainScene.h"
#include "LuaScene.h"

#include "Model.h"

int main() {

    std::cout << "Starting Game" << std::endl;

    auto engine = std::make_unique<en::Engine>();
    engine->initialize();

    {
        engine->addSystem<en::TransformHierarchySystem>();
        engine->addSystem<en::RenderSystem>();

        engine->addSystem<en::PhysicsSystem>().setGravity({0, -9.8, 0});

        engine->addSystem<en::UIEventSystem>();
        engine->addSystem<en::BehaviorsSystem>();

        engine->addSystem<en::TweenSystem>();
        engine->addSystem<en::DestroyByTimerSystem>();
        engine->addSystem<en::DestroySystem>();
    }

    en::LuaState& lua = engine->getLuaState();
    lua_getglobal(lua, "Config");
    auto popConfig = lua::PopperOnDestruct(lua);
    auto startScene = lua.tryGetField<std::string>("startScene");
    if (startScene)
        engine->getSceneManager().setCurrentScene<en::LuaScene>(engine->getLuaState(), *startScene);
    lua.pop();

    //engine->getSceneManager().setCurrentScene<TestScene>();
    //engine->getSceneManager().setCurrentScene<LightingScene>();
    //engine->getSceneManager().setCurrentScene<TerrainScene>();

    engine->run();

    return 0;
}
