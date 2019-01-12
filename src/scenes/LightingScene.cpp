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
#include <glm/gtx/euler_angles.hpp>

void LightingScene::open(en::Engine& engine) {

    auto camera = engine.makeActor("Camera");
    camera.add<en::Camera>();
    camera.add<en::Transform>();
    camera.add<CameraOrbitBehavior>(5, -45.f, 89.f);

    auto ambientLight = engine.makeActor("AmbientLight");
    ambientLight.add<en::Transform>();
    {
        auto& l = ambientLight.add<en::Light>();
        l.color = {0,0,0};
        l.colorAmbient = {0, 0, 0.2};
    }

    auto directionalLight = engine.makeActor("DirectionalLight");
    directionalLight.add<en::Transform>()
        .setLocalRotation(glm::toQuat(glm::orientate4(glm::radians(glm::vec3(-45,0,-90)))));
    {
        auto& l = directionalLight.add<en::Light>();
        l.kind = en::Light::Kind::DIRECTIONAL;
        l.intensity = 0.4f;
    }

    auto rotatingLights = engine.makeActor("RotatingLights");
    rotatingLights.add<en::Transform>();
    rotatingLights.add<RotatingBehavior>(glm::vec3(0,1,0));

    auto lightMesh = en::Resources<Mesh>::get(config::MODEL_PATH + "cube_flat.obj");

    constexpr int numLights = 6;
    for (int i = 0; i < numLights; ++i) {

        auto light = engine.makeActor("Light");
        light.add<en::Transform>()
            .setParent(rotatingLights)
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
        material->setUniformValue("diffuseMap" , en::Textures::white());
        material->setUniformValue("diffuseColor", glm::vec3(1));
        material->setUniformValue("specularMap", en::Textures::white());
        material->setUniformValue("specularColor", glm::vec3(1));
        material->setUniformValue("shininess", 10.f);
        sphere.add<en::RenderInfo>(mesh, std::move(material));
    }
    camera.get<CameraOrbitBehavior>().setTarget(sphere);

    auto plane = engine.makeActor("Plane");
    plane.add<en::Transform>().move({0, -1, 0}).setLocalScale({3, 3, 3});
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "plane.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseColor", glm::vec3(1));
        material->setUniformValue("diffuseMap" , en::Textures::get(config::TEXTURE_PATH + "land.jpg"));
        material->setUniformValue("specularColor", glm::vec3(0.04));
        material->setUniformValue("specularMap", en::Textures::white());
        material->setUniformValue("shininess", 10.f);
        plane.add<en::RenderInfo>(mesh, std::move(material));
    }
}
