//
// Created by Maksym Maisak on 16/12/18.
//

#include "MGETestScene.h"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.h"

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/random.hpp>

void MGETestScene::_initializeScene() {

    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    //MATERIALS

    AbstractMaterial* runicStoneMaterial = new TextureMaterial(
        Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png")
    );

    AbstractMaterial* floorMaterial = new TextureMaterial(
        Texture::load(config::MGE_TEXTURE_PATH + "land.jpg")
    );

    //SCENE SETUP

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, -4, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(floorMaterial);
    _world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->setBehaviour(new RotatingBehaviour());
    _world->add(sphere);
    camera->setBehaviour(new CameraOrbitBehaviour(sphere, 10, -15.f, 60.f));

    GameObject* ring = new GameObject("ring", glm::vec3(0, 0, 0));
    ring->setBehaviour(new RotatingBehaviour());
    _world->add(ring);

    const std::size_t numCubes = 10;
    const float radius = 3;
    for (std::size_t i = 0; i < numCubes; ++i) {

        const float angle = glm::two_pi<float>() * (float)i / numCubes;
        const glm::vec3 offset = {
            glm::cos(angle) * radius,
            0,
            glm::sin(angle) * radius
        };

        GameObject* object = nullptr;
        if (i % 2 == 0) {
            object = new Light("light", offset);
            object->setMesh(cubeMeshF);
            object->setMaterial(new ColorMaterial(glm::abs(glm::sphericalRand(1.f))));
        } else {
            object = new GameObject("smallSphere", offset);
            object->setMesh(sphereMeshS);
            object->setMaterial(runicStoneMaterial);
        }

        object->scale(glm::vec3(0.2f));
        object->setBehaviour(new RotatingBehaviour());
        ring->add(object);
    }
}
