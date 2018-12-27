#include <iostream>
#include <memory>

#include "Engine.h"
#include "Actor.h"
#include "EntityRegistry.h"
#include "TransformableHierarchySystem.h"
#include "DestroySystem.h"
#include "DestroyByTimerSystem.h"
#include "RenderSystem.h"

#include "TestScene.h"

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

    en::Engine engine;
    engine.initialize();
    {
        engine.addSystem<en::TransformableHierarchySystem>();
        engine.addSystem<en::RenderSystem>(false);

        engine.addSystem<en::DestroyByTimerSystem>();
        engine.addSystem<en::DestroySystem>();
    }

    engine.getSceneManager().setCurrentScene<TestScene>();
    //engine.getScheduler().delay(sf::seconds(5.f), [&](){engine.getRegistry().destroyAll();});

    engine.run();

    return 0;
}



