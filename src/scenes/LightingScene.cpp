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
    camera.add<CameraOrbitBehavior>(5);

    auto light = engine.makeActor("Light");
    light.add<en::Light>();
    light.add<en::Transform>().move({-1, 1, 0});

    auto sphere = engine.makeActor("Sphere");
    sphere.add<en::Transform>();
    sphere.add<RotatingBehavior>();
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
    plane.add<en::Transform>().move({0, -1, 0}).setLocalScale({2, 2, 2});
    {
        auto mesh = en::Resources<Mesh>::get(config::MODEL_PATH + "plane.obj");
        auto material = std::make_shared<en::Material>("lit");
        material->setUniformValue("diffuseColor" , glm::vec3(1, 1, 1));
        material->setUniformValue("specularColor", glm::vec3(1, 1, 1));
        material->setUniformValue("shininess", 10.f);
        plane.add<en::RenderInfo>(mesh, std::move(material));
    }
}
