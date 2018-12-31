//
// Created by Maksym Maisak on 27/12/18.
//

#include "TestScene.h"
#include "Engine.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Resources.h"
#include "TextureMaterial.hpp"
#include "WobblingMaterial.h"
#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "components/Transform.h"
#include "components/Camera.h"
#include "components/Light.h"
#include "components/RenderInfo.h"
#include "CameraOrbitBehavior.h"
#include "RotatingBehavior.hpp"

void TestScene::open(en::Engine& engine) {

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
    // TODO have make behaviors work when added from registry too.
    en::Actor camera = engine.makeActor();
    camera.add<en::Camera>();
    auto& t = camera.add<en::Transform>();
    t.move({0, 0, 10});

    // Add the floor
    // Use en::Registry this time,
    // this is more representative of what's actually happening under the hood.
    en::EntityRegistry& registry = engine.getRegistry();
    en::Entity plane = registry.makeEntity();
    auto& planeTransform = registry.add<en::Transform>(plane);
    planeTransform.setLocalPosition({0, -4, 0});
    planeTransform.setLocalScale({5, 5, 5});
    registry.add<en::RenderInfo>(plane, planeMeshDefault, floorMaterial);

    //add a spinning sphere
    en::Actor sphere = engine.makeActor();
    sphere.add<en::Transform>().setLocalScale({2.5f, 2.5f, 2.5f});
    sphere.add<en::RenderInfo>(testObjectMeshS, wobblingMaterial);
    sphere.add<RotatingBehavior>();
    camera.add<CameraOrbitBehavior>(sphere, 10, -15.f, 60.f);

    en::Actor ring = engine.makeActor();
    ring.add<en::Transform>();
    ring.add<RotatingBehavior>();

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
        auto& transform = object.add<en::Transform>();
        transform.setParent(ring);
        transform.setLocalPosition(offset);
        transform.scale(glm::vec3(0.2f));
        object.add<RotatingBehavior>();
        if (i % 2 == 0) {
            object.add<en::Light>();
            auto material = std::make_shared<ColorMaterial>(glm::abs(glm::sphericalRand(1.f)));
            object.add<en::RenderInfo>(cubeMeshF, material);
        } else {
            object.add<en::RenderInfo>(sphereMeshS, runicStoneMaterial);
        }
    }
}
