//
// Created by Maksym Maisak on 24/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LIGHT_H
#define SAXION_Y2Q2_RENDERING_LIGHT_H

#include "ComponentsToLua.h"
#include "glm.hpp"
#include <GL/glew.h>

namespace en {

    class Light final {

        LUA_TYPE(Light);

    public:

        inline static const glm::vec<2, GLsizei> DepthMapResolution = {1024, 1024};

        enum class Kind {

            POINT = 0,
            DIRECTIONAL,
            SPOT,

            COUNT
        };

        struct Settings {

            struct Falloff {

                float constant  = 1;
                float linear    = 0;
                float quadratic = 1;
            };

            glm::vec3 colorAmbient = {0, 0, 0};
            glm::vec3 color = {1, 1, 1};
            float intensity = 1;
            Falloff falloff = {1, 0, 1};

            // cos of angle in radius
            float spotlightInnerCutoff = glm::cos(glm::radians(40.f));
            float spotlightOuterCutoff = glm::cos(glm::radians(50.f));
        };

        static void addFromLua(Actor& actor, LuaState& lua);
        static void initializeMetatable(LuaState& lua);

        Light(Kind kind = Kind::POINT);
        ~Light();
        Light(const Light& other) = delete;
        Light& operator=(const Light& other) = delete;
        Light(Light&& light) = default;
        Light& operator=(Light&& light) = default;

        Settings& getSettings();
        const Settings& getSettings() const;
        void setSettings(Settings& settings);

        Kind getKind() const;
        void setKind(Kind kind);
        GLuint getFramebufferId() const;
        GLuint getDepthMapId() const;

    private:

        Kind m_kind = Kind::POINT;
        Settings m_settings;

        GLuint m_fbo = 0;
        GLuint m_depthMap = 0;
    };

    struct FalloffFunctions {

        static constexpr Light::Settings::Falloff Constant  = {1, 0, 0};
        static constexpr Light::Settings::Falloff Linear    = {1, 1, 0};
        static constexpr Light::Settings::Falloff Quadratic = {1, 0, 1};
    };
}

#endif //SAXION_Y2Q2_RENDERING_LIGHT_H
