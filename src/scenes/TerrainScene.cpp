//
// Created by Maksym Maisak on 2019-01-16.
//

#include "TerrainScene.h"

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

void TerrainScene::open(en::Engine& engine) {

    auto camera = engine.makeActor("Camera");
    camera.add<en::Camera>();
    camera.add<en::Transform>();
    camera.add<CameraOrbitBehavior>(5, -45.f, 89.f);

    auto directionalLight = engine.makeActor("DirectionalLight");
    directionalLight.add<en::Transform>()
        .setLocalRotation(glm::toQuat(glm::orientate4(glm::radians(glm::vec3(-45,0,-90)))));
    {
        auto& l = directionalLight.add<en::Light>();
        l.kind = en::Light::Kind::DIRECTIONAL;
        //l.colorAmbient = {0.1, 0.1, 0.1};
        l.intensity = 1.f;
    }

    auto terrain = engine.makeActor("Terrain");
    terrain.add<en::Transform>().scale({4, 1, 4});
    {
        auto mesh = en::Meshes::get(config::MODEL_PATH + "plane_8192.obj");
        auto material = std::make_shared<en::Material>("terrain");
        material->setUniformValue("heightmap", en::Textures::get(config::TEXTURE_PATH + "terrain/heightmap.png"));
        material->setUniformValue("maxHeight", 4.f);
        material->setUniformValue("splatmap", en::Textures::get(config::TEXTURE_PATH + "terrain/splatmap.png"));
        material->setUniformValue("diffuse1", en::Textures::get(config::TEXTURE_PATH + "terrain/diffuse1.jpg"));
        material->setUniformValue("diffuse2", en::Textures::get(config::TEXTURE_PATH + "terrain/water.jpg"));
        material->setUniformValue("diffuse3", en::Textures::get(config::TEXTURE_PATH + "terrain/diffuse3.jpg"));
        material->setUniformValue("diffuse4", en::Textures::get(config::TEXTURE_PATH + "terrain/diffuse4.jpg"));
        material->setUniformValue("diffuseColor" , glm::vec3(1));
        material->setUniformValue("specularColor", glm::vec3(0.04));
        material->setUniformValue("specularMap", en::Textures::white());
        material->setUniformValue("shininess"  , 64.f);
        terrain.add<en::RenderInfo>(mesh, std::move(material));
    }
    //terrain.add<RotatingBehavior>(glm::vec3(0, 1, 0), glm::radians(45.f));
    camera.get<CameraOrbitBehavior>().setTarget(terrain);
}
