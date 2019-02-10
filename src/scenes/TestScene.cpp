//
// Created by Maksym Maisak on 27/12/18.
//

#include "TestScene.h"
#include "Engine.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Resources.h"
#include "WobblingMaterial.h"
#include "mge/config.hpp"

#include "components/Transform.h"
#include "components/Camera.h"
#include "components/Light.h"
#include "components/RenderInfo.h"
#include "components/Rigidbody.h"

#include "CameraOrbitBehavior.h"
#include "RotatingBehavior.hpp"

#include "Material.h"

void makeFloorFromSpheres(en::Engine& engine, float sideLength, int numSpheresPerSide) {

    const float diameter = 2.f * sideLength / numSpheresPerSide;
    const float radius = diameter * 0.5f;

    auto mesh = en::Meshes::get(config::MODEL_PATH + "sphere_smooth.obj");
    auto material = std::make_shared<en::Material>("lit");
    material->setUniformValue("diffuseMap", en::Textures::get(config::TEXTURE_PATH + "bricks.jpg"));
    material->setUniformValue("diffuseColor", glm::vec3(1));
    material->setUniformValue("specularMap", en::Textures::white());
    material->setUniformValue("specularColor", glm::vec3(0));

    for (int y = 0; y < numSpheresPerSide; ++y) {
        for (int x = 0; x < numSpheresPerSide; ++x) {

            en::Actor actor = engine.makeActor("Floor_" + std::to_string(x) + "_" + std::to_string(y));

            auto& tf = actor.add<en::Transform>();

            // from (-1, -1) to (1, 1) inclusive
            glm::vec2 positionNormalized = {
                ((float)x / (numSpheresPerSide - 1) - 0.5f) * 2.f,
                ((float)y / (numSpheresPerSide - 1) - 0.5f) * 2.f
            };
            tf.setLocalPosition({
                sideLength * positionNormalized.x * 0.5f,
                -10 + 8 * glm::length2(positionNormalized),
                sideLength * positionNormalized.y * 0.5f
            });
            tf.setLocalScale({radius, radius, radius});

            auto& rb = actor.add<en::Rigidbody>();
            rb.isKinematic = true;
            rb.radius = radius;

            actor.add<en::RenderInfo>(mesh, material);
        }
    }
}

void addRingItems(en::Engine& engine, en::Entity parent, std::size_t numItems = 10, float radius = 3.5f) {

    auto cubeMesh       = en::Meshes::get(config::MODEL_PATH + "cube_flat.obj");
    auto sphereMesh     = en::Meshes::get(config::MODEL_PATH + "sphere_smooth.obj");
    //auto sphereMaterial = en::Resources<TextureMaterial>::get(config::TEXTURE_PATH + "runicfloor.png");

    auto sphereMaterial = std::make_shared<en::Material>("lit");
    sphereMaterial->setUniformValue("diffuseColor", glm::vec3(1, 1, 1));
    sphereMaterial->setUniformValue("diffuseMap", en::Textures::white());
    sphereMaterial->setUniformValue("specularColor", glm::vec3(1, 1, 1));
    sphereMaterial->setUniformValue("specularMap", en::Textures::white());
    sphereMaterial->setUniformValue("shininess", 10.f);

    auto cubeMaterial = std::make_shared<en::Material>("lit");
    cubeMaterial->setUniformValue("diffuseColor", glm::vec3(1, 1, 1));
    cubeMaterial->setUniformValue("diffuseMap", en::Textures::get(config::TEXTURE_PATH + "container/diffuse.png"));
    cubeMaterial->setUniformValue("specularColor", glm::vec3(1, 1, 1));
    cubeMaterial->setUniformValue("specularMap", en::Textures::get(config::TEXTURE_PATH + "container/specular.png"));
    cubeMaterial->setUniformValue("shininess", 64.f);

    for (std::size_t i = 0; i < numItems; ++i) {

        en::Actor object = engine.makeActor("RingItem");

        {
            const float angle = glm::two_pi<float>() * (float)i / numItems;
            const glm::vec3 offset = {
                glm::cos(angle) * radius,
                0,
                glm::sin(angle) * radius
            };

            auto& tf = object.add<en::Transform>();

            //tf.setParent(parent);
            tf.setLocalPosition(offset);
            tf.scale(glm::vec3(0.2f));
        }

        {
            auto& rb = object.add<en::Rigidbody>();
            //rb.isKinematic = true;
            rb.radius = 0.2f;
            rb.invMass = 1.f / 0.1f;
        }

        object.add<RotatingBehavior>();

        if (i % 2 == 0) {

            object.add<en::Light>().getSettings().intensity = 2.f;
            object.add<en::RenderInfo>(sphereMesh, sphereMaterial);

        } else {

            object.add<en::RenderInfo>(cubeMesh, cubeMaterial);
            object.get<en::Transform>().scale(glm::vec3(2));
            auto& rb = object.get<en::Rigidbody>();
            rb.radius *= 2.f;
            rb.invMass /= 2.f;
        }
    }
}

void TestScene::open() {

    en::Engine& engine = getEngine();

    // MESHES

    // load a bunch of meshes we will be using throughout this demo
    // F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    std::shared_ptr<Mesh> planeMeshDefault = en::Meshes::get(config::MODEL_PATH + "plane.obj");
    std::shared_ptr<Mesh> cubeMeshF        = en::Meshes::get(config::MODEL_PATH + "cube_flat.obj");
    std::shared_ptr<Mesh> sphereMeshS      = en::Meshes::get(config::MODEL_PATH + "sphere_smooth.obj");
    std::shared_ptr<Mesh> testObjectMeshS  = en::Meshes::get(config::MODEL_PATH + "sphere2.obj");

    // MATERIALS
    auto runicStoneMaterial = en::Resources<en::Material>::get("runicStoneMaterial", "texture");
    runicStoneMaterial->setUniformValue("diffuseTexture", en::Textures::get(config::TEXTURE_PATH + "runicfloor.png"));

    auto floorMaterial = en::Resources<en::Material>::get("floorMaterial", "lit");
    floorMaterial->setUniformValue("diffuseMap", en::Textures::get(config::TEXTURE_PATH + "land.jpg"));
    floorMaterial->setUniformValue("diffuseColor", glm::vec3(1));
    floorMaterial->setUniformValue("specularMap", en::Textures::white());
    floorMaterial->setUniformValue("specularColor", glm::vec3(0.04));

    auto wobblingMaterial = en::Resources<WobblingMaterial>::get(config::TEXTURE_PATH + "runicfloor.png");

    //en::Meshes::get(config::MODEL_PATH + "sphere3.obj");
    //en::Meshes::removeUnused();

    // SCENE SETUP

    // Add the camera using en::Actor,
    // a thin wrapper around en::Engine and en::Entity
    // Using it to add components also ensures that components
    // inheriting from en::Behavior actually have their update functions called.
    // TODO have behaviors work when added via registry too.
    en::Actor camera = engine.makeActor("Camera");
    camera.add<en::Camera>();
    camera.add<en::Transform>().move({0, 0, 10});
    auto& cameraOrbitBehavior = camera.add<CameraOrbitBehavior>(10, -15.f, 60.f);

    // Add the floor
    // Use en::Registry this time,
    // this is more representative of what's actually happening under the hood.
//    en::EntityRegistry& registry = engine.getRegistry();
//    en::Entity plane = registry.makeEntity("Plane");
//    auto& planeTransform = registry.add<en::Transform>(plane);
//    planeTransform.setLocalPosition({0, -4, 0});
//    planeTransform.setLocalScale({5, 5, 5});
//    registry.add<en::RenderInfo>(plane, planeMeshDefault, floorMaterial);

    makeFloorFromSpheres(engine, 30, 20);

    // Add a directional light
    en::Actor directionalLight = engine.makeActor("DirectionalLight");
    directionalLight.add<en::Transform>()
        .setLocalRotation(glm::toQuat(glm::orientate3(glm::radians(glm::vec3(-45, 0, 90)))));
    {
        auto& l = directionalLight.add<en::Light>(en::Light::Kind::DIRECTIONAL).getSettings();
        l.colorAmbient = glm::vec3(0.1);
        l.color = glm::vec3(0.2);
    }

    // Add an empty rotating object.
    en::Actor ring = engine.makeActor("Ring");
    ring.add<en::Transform>();
    {
        auto& rb = ring.add<en::Rigidbody>();
        //rb.isKinematic = true;
        rb.radius = 2.5f;
    }
    ring.add<RotatingBehavior>();
    addRingItems(engine, ring, 18);

    //add a spinning sphere
    en::Actor sphere = engine.makeActor("Main sphere");
    auto& tf = sphere.add<en::Transform>();
    tf.setParent(ring);
    tf.setLocalScale({2.5f, 2.5f, 2.5f});
    sphere.add<en::RenderInfo>(testObjectMeshS, wobblingMaterial);
    cameraOrbitBehavior.setTarget(sphere);
}
