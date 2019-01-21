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
#include "LightPropertyAnimator.h"
#include "Resources.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.h"
#include "ColorMaterial.hpp"
#include "glm.hpp"
#include <glm/gtx/euler_angles.hpp>

constexpr bool AnimateLightProperties = false;
constexpr int NumRotatingLights = 4;

void LightingScene::open() {

    en::Engine& engine = getEngine();

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
    if (AnimateLightProperties) ambientLight.add<LightPropertyAnimator>();

    auto directionalLight = engine.makeActor("DirectionalLight");
    directionalLight.add<en::Transform>()
        .setLocalRotation(glm::toQuat(glm::orientate4(glm::radians(glm::vec3(-45,0,-90)))));
    {
        auto& l = directionalLight.add<en::Light>();
        l.kind = en::Light::Kind::DIRECTIONAL;
        l.intensity = 0.4f;
    }
    if (AnimateLightProperties) directionalLight.add<LightPropertyAnimator>();

    auto spotLight = engine.makeActor("SpotLight");
    spotLight.add<en::Transform>()
        .move({0, 0, -2});
    {
        glm::vec3 spotLightColor = {0, 1, 1};

        {
            auto child = engine.makeActor("SpotLightModel");
            child.add<en::Transform>()
                .setParent(spotLight)
                .scale(glm::vec3(0.2f))
                .rotate(glm::radians(-90.f), {1, 0, 0})
                .move({0, 0, 0.1});

            auto mesh = en::Meshes::get(config::MODEL_PATH + "cone_smooth.obj");
            auto material = std::make_shared<en::Material>("color");
            material->setUniformValue("diffuseColor", spotLightColor);
            child.add<en::RenderInfo>(mesh, material);
        }

        auto& l = spotLight.add<en::Light>();
        l.kind  = en::Light::Kind::SPOT;
        l.color = spotLightColor;
        l.spotlightInnerCutoff = glm::cos(glm::radians(20.f));
        l.spotlightOuterCutoff = glm::cos(glm::radians(45.f));
    }
    spotLight.add<RotatingBehavior>(glm::vec3(1,0,0));
    if (AnimateLightProperties) spotLight.add<LightPropertyAnimator>();

    auto rotatingLights = engine.makeActor("RotatingLights");
    rotatingLights.add<en::Transform>();
    rotatingLights.add<RotatingBehavior>(glm::vec3(0,1,0));

    auto lightMesh = en::Resources<Mesh>::get(config::MODEL_PATH + "cube_flat.obj");
    for (int i = 0; i < NumRotatingLights; ++i) {

        auto light = engine.makeActor("Light");
        light.add<en::Transform>()
            .setParent(rotatingLights)
            .move(glm::rotate(glm::vec3(0,0,2), 2.f * glm::pi<float>() * (i + 1.f) / NumRotatingLights, glm::vec3(0,1,0)))
            .scale(glm::vec3(0.1f));

        glm::vec3 lightColor = glm::abs(glm::make_vec3(glm::circularRand(1.f)));

        auto lightMaterial = std::make_shared<en::Material>("color");
        lightMaterial->setUniformValue("diffuseColor", lightColor);

        light.add<en::RenderInfo>(lightMesh, lightMaterial);
        light.add<en::Light>().color = lightColor;
        if (AnimateLightProperties) light.add<LightPropertyAnimator>();
    }

    auto cube = engine.makeActor("Cube");
    cube.add<en::Transform>();
    {
        auto mesh = en::Meshes::get(config::MODEL_PATH + "cube_flat.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseMap"   , en::Textures::get(config::TEXTURE_PATH + "container/diffuse.png"));
        material->setUniformValue("diffuseColor" , glm::vec3(1));
        material->setUniformValue("specularMap"  , en::Textures::get(config::TEXTURE_PATH + "container/specular.png"));
        material->setUniformValue("specularColor", glm::vec3(1));
        material->setUniformValue("shininess"    , 64.f);
        cube.add<en::RenderInfo>(mesh, std::move(material));
    }
    camera.get<CameraOrbitBehavior>().setTarget(cube);

    auto sphere = engine.makeActor("Sphere");
    sphere.add<en::Transform>().move({0, 2, 0});
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "sphere2.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseMap"   , en::Textures::white());
        material->setUniformValue("diffuseColor" , glm::vec3(1));
        material->setUniformValue("specularMap"  , en::Textures::white());
        material->setUniformValue("specularColor", glm::vec3(1));
        material->setUniformValue("shininess"    , 10.f);
        sphere.add<en::RenderInfo>(mesh, std::move(material));
    }

    auto plane = engine.makeActor("Plane");
    plane.add<en::Transform>().move({0, -1, 0}).setLocalScale({3, 3, 3});
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "plane.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseColor" , glm::vec3(1));
        material->setUniformValue("diffuseMap"   , en::Textures::get(config::TEXTURE_PATH + "land.jpg"));
        material->setUniformValue("specularColor", glm::vec3(0.04));
        material->setUniformValue("specularMap"  , en::Textures::white());
        material->setUniformValue("shininess"    , 10.f);
        plane.add<en::RenderInfo>(mesh, std::move(material));
    }
}
