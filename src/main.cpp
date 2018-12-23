#include <iostream>
#include <engine/components/Transformable.h>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/MGETestScene.h"
#include "Transformable.h"

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

    auto test = en::Transformable();
    std::cout << test.getLocalTransform() << std::endl;

	std::unique_ptr<AbstractGame> game = std::make_unique<MGETestScene>();
    game->initialize();
    game->run();

    return 0;
}



