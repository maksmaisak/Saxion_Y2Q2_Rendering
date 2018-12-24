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
#include "mge/materials/WobblingMaterial.h"

#include "mge/behaviours/RotatingBehavior.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehavior.h"

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/random.hpp>

#include "Resources.h"

void MGETestScene::_initializeScene() {

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

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, -4, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault.get());
    plane->setMaterial(floorMaterial.get());
    _world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(testObjectMeshS.get());
    sphere->setMaterial(wobblingMaterial.get());
    //sphere->setBehaviour(new RotatingBehavior());
    _world->add(sphere);
    //camera->setBehaviour(new CameraOrbitBehavior(sphere, 10, -15.f, 60.f));

    GameObject* ring = new GameObject("ring", glm::vec3(0, 0, 0));
    //ring->setBehaviour(new RotatingBehavior());
    _world->add(ring);

    const std::size_t numCubes = 10;
    const float radius = 3.5f;
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
            object->setMesh(cubeMeshF.get());
            object->setMaterial(new ColorMaterial(glm::abs(glm::sphericalRand(1.f))));
        } else {
            object = new GameObject("smallSphere", offset);
            object->setMesh(sphereMeshS.get());
            object->setMaterial(runicStoneMaterial.get());
        }

        object->scale(glm::vec3(0.2f));
        //object->setBehaviour(new RotatingBehavior());
        ring->add(object);
    }
}
