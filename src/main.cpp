#include <iostream>
#include <memory>

#include "Engine.h"
#include "Actor.h"
#include "EntityRegistry.h"
#include "TransformHierarchySystem.h"
#include "DestroySystem.h"
#include "DestroyByTimerSystem.h"
#include "RenderSystem.h"
#include "RenderInfo.h"

#include "TestScene.h"
#include "LuaScene.h"

#include "Camera.h"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */
int main() {

    std::cout << "Starting Game" << std::endl;

    auto engine = std::make_unique<en::Engine>();
    engine->initialize();
    {
        engine->addSystem<en::TransformHierarchySystem>();
        engine->addSystem<en::RenderSystem>(false);

        engine->addSystem<en::DestroyByTimerSystem>();
        engine->addSystem<en::DestroySystem>();
    }

    //engine->getSceneManager().setCurrentScene<TestScene>();

    engine->getSceneManager().setCurrentScene<LuaScene>("assets/scripts/luaScene.lua");
    en::Actor actor = engine->makeActor();
    actor.add<en::Transform>().move({0, 0, 10});
    actor.add<en::Camera>();

    engine->run();

    return 0;
}



