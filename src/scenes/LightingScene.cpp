//
// Created by Maksym Maisak on 2019-01-10.
//

#include "LightingScene.h"

#include <memory>
#include "config.hpp"
#include "components/Camera.h"
#include "components/Transform.h"
#include "components/RenderInfo.h"
#include "components/Light.h"
#include "CameraOrbitBehavior.h"
#include "RotatingBehavior.hpp"
#include "Resources.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.h"
#include "ColorMaterial.hpp"
#include "glm.hpp"

void LightingScene::open(en::Engine& engine) {

    auto camera = engine.makeActor("Camera");
    camera.add<en::Camera>();
    camera.add<en::Transform>().move({0, 0, 5});
    camera.add<CameraOrbitBehavior>(5, -45.f, 89.f);

    auto lights = engine.makeActor("Lights");
    lights.add<en::Transform>();
    lights.add<RotatingBehavior>(glm::vec3(0,1,0));

    auto ambientLight = engine.makeActor("AmbientLight");
    ambientLight.add<en::Transform>().setParent(lights);
    {
        auto& l = ambientLight.add<en::Light>();
        l.color = {0,0,0};
        l.colorAmbient = {0, 0, 0.2};
    }

    auto lightMesh = en::Resources<Mesh>::get(config::MODEL_PATH + "cube_flat.obj");

    constexpr int numLights = 6;
    for (int i = 0; i < numLights; ++i) {

        auto light = engine.makeActor("Light");
        light.add<en::Transform>()
            .setParent(lights)
            .move(glm::rotate(glm::vec3(0,0,2), 2.f * glm::pi<float>() * (i + 1.f) / numLights, glm::vec3(0,1,0)))
            .scale({0.1f, 0.1f, 0.1f});

        glm::vec3 lightColor = glm::abs(glm::make_vec3(glm::circularRand(1.f)));

        auto lightMaterial = std::make_shared<en::Material>("color");
        lightMaterial->setUniformValue("diffuseColor", lightColor);

        light.add<en::RenderInfo>(lightMesh, lightMaterial);
        light.add<en::Light>().color = lightColor;
    }

    auto sphere = engine.makeActor("Sphere");
    sphere.add<en::Transform>();
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "sphere2.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseColor" , glm::vec3(1, 1, 1));
        material->setUniformValue("specularColor", glm::vec3(1, 1, 1));
        material->setUniformValue("shininess", 10.f);
        sphere.add<en::RenderInfo>(mesh, std::move(material));
    }
    camera.get<CameraOrbitBehavior>().setTarget(sphere);

    auto plane = engine.makeActor("Plane");
    plane.add<en::Transform>().move({0, -1, 0}).setLocalScale({3, 3, 3});
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "plane.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseColor" , glm::vec3(1, 1, 1));
        material->setUniformValue("specularColor", glm::vec3(1, 1, 1));
        material->setUniformValue("shininess", 10.f);
        plane.add<en::RenderInfo>(mesh, std::move(material));
    }
}
