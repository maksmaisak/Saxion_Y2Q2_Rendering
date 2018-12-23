#include <iostream>
#include <memory>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/MGETestScene.h"
#include "Engine.h"
#include "Actor.h"
#include "EntityRegistry.h"
#include "TransformableHierarchySystem.h"
#include "DestroySystem.h"
#include "DestroyByTimerSystem.h"
#include "RenderSystem.h"

#include "Transformable.h"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Resources.h"
#include "TextureMaterial.hpp"
#include "WobblingMaterial.h"
#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "components/Camera.h"
#include "components/Light.h"
#include "components/RenderInfo.h"

void buildScene(en::Engine& engine) {

    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    std::shared_ptr<Mesh> planeMeshDefault = en::Resources<Mesh>::get(config::MGE_MODEL_PATH + "plane.obj");
    std::shared_ptr<Mesh> cubeMeshF        = en::Resources<Mesh>::get(config::MGE_MODEL_PATH + "cube_flat.obj");
    std::shared_ptr<Mesh> sphereMeshS      = en::Resources<Mesh>::get(config::MGE_MODEL_PATH + "sphere_smooth.obj");
    std::shared_ptr<Mesh> testObjectMeshS  = en::Resources<Mesh>::get(config::MGE_MODEL_PATH + "sphere2.obj");

    //MATERIALS

    std::shared_ptr<AbstractMaterial> runicStoneMaterial = en::Resources<TextureMaterial>::get(config::MGE_TEXTURE_PATH + "runicfloor.png");
    std::shared_ptr<AbstractMaterial> floorMaterial      = en::Resources<TextureMaterial>::get(config::MGE_TEXTURE_PATH + "land.jpg");
    std::shared_ptr<AbstractMaterial> wobblingMaterial   = en::Resources<WobblingMaterial>::get(config::MGE_TEXTURE_PATH + "runicfloor.png");

    //en::Resources<Mesh>::get(config::MGE_MODEL_PATH + "sphere3.obj");
    //en::Resources<Mesh>::removeUnused();

    //SCENE SETUP

    // Add the camera using en::Actor,
    // a thin wrapper around en::Engine and en::Entity
    // Using it to add components also ensures that components
    // inheriting from en::Behavior actually have their update functions called.
    // TODO have Engine auto-add BehaviorSystems for all Behavior types used by the project using CustomTypeIndex or something similar.
    en::Actor camera = engine.makeActor();
    camera.add<en::Camera>();
    camera.add<en::Transformable>().rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));

    // Add the floor
    // Use en::Registry this time,
    // this is more representative of what's actually happening under the hood.
    en::EntityRegistry& registry = engine.getRegistry();
    en::Entity plane = registry.makeEntity();
    registry.add<en::Transformable>(plane).setLocalPosition({0, -4, 0});
    //registry.add<en::RenderInfo>(plane, planeMeshDefault, floorMaterial);

    en::Actor sphere = engine.makeActor();
    sphere.add<en::Transformable>().setLocalScale({2.5f, 2.5f, 2.5f});
    //sphere.add<RenderInfo>(testObjectMeshS, wobblingMaterial);
    //sphere.add<RotatingBehavior>();
    //camera.add<CameraOrbitBehavior>(sphere, 10, -15.f, 60.f);

    /*
    //add a spinning sphere
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(testObjectMeshS.get());
    sphere->setMaterial(wobblingMaterial.get());
    sphere->setBehaviour(new RotatingBehaviour());
    _world->add(sphere);
    camera->setBehaviour(new CameraOrbitBehaviour(sphere, 10, -15.f, 60.f));
     */

    en::Actor ring = engine.makeActor();
    ring.add<en::Transformable>();
    //ring.add<RotatingBehavior>();

    /*GameObject* ring = new GameObject("ring", glm::vec3(0, 0, 0));
    ring->setBehaviour(new RotatingBehaviour());
    _world->add(ring);*/

    const std::size_t numCubes = 10;
    const float radius = 3.5f;
    for (std::size_t i = 0; i < numCubes; ++i) {

        const float angle = glm::two_pi<float>() * (float)i / numCubes;
        const glm::vec3 offset = {
            glm::cos(angle) * radius,
            0,
            glm::sin(angle) * radius
        };

        en::Actor object = engine.makeActor();
        auto& transform = object.add<en::Transformable>();
        transform.setParent(ring);
        transform.setLocalPosition(offset);
        transform.scale(glm::vec3(0.2f));
        //object.add<RotatingBehavior>();
        if (i % 2 == 0) {
            object.add<en::Light>();
            auto material = std::make_shared<ColorMaterial>(glm::abs(glm::sphericalRand(1.f)));
            object.add<en::RenderInfo>(cubeMeshF, material);
        } else {
            object.add<en::RenderInfo>(sphereMeshS, runicStoneMaterial);
        }
    }
}

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
        engine.addSystem<en::RenderSystem>();

        engine.addSystem<en::DestroyByTimerSystem>();
        engine.addSystem<en::DestroySystem>();
    }

    buildScene(engine);

    engine.run();

    /*
    auto test = en::Transformable();
    std::cout << &test << std::endl;
    */

    /*
	std::unique_ptr<AbstractGame> game = std::make_unique<MGETestScene>();
    game->initialize();
    game->run();
    */

    return 0;
}



