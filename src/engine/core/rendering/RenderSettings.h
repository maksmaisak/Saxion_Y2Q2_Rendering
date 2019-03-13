//
// Created by Maksym Maisak on 2019-03-11.
//

#ifndef SAXION_Y2Q2_RENDERING_RENDERSETTINGS_H
#define SAXION_Y2Q2_RENDERING_RENDERSETTINGS_H

#include <memory>
#include "config.hpp"
#include "glm.hpp"
#include "Texture.hpp"
#include "Resources.h"

namespace en {

    struct RenderSettings {

        glm::vec3 ambientColor = {0, 0, 0};
        std::shared_ptr<Texture> skyboxTexture = Resources<Texture>::get("skybox", std::array<std::string, 6> {
            config::TEXTURE_PATH + "skybox/Right.png" ,
            config::TEXTURE_PATH + "skybox/Left.png"  ,
            config::TEXTURE_PATH + "skybox/Top.png"   ,
            config::TEXTURE_PATH + "skybox/Bottom.png",
            config::TEXTURE_PATH + "skybox/Front.png" ,
            config::TEXTURE_PATH + "skybox/Back.png"
        });
    };
}

#endif //SAXION_Y2Q2_RENDERING_RENDERSETTINGS_H
