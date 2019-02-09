//
// Created by Maksym Maisak on 2019-01-19.
//

#include "Light.h"
#include <map>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include "ComponentReference.h"
#include "Transform.h"
#include "GLHelpers.h"

using namespace en;

Light::Kind readKind(LuaState& lua) {

    std::optional<std::string> kindName = lua.tryGetField<std::string>("kind");

    if (!kindName)
        return Light::Kind::POINT;

    static const std::map<std::string, Light::Kind> kinds = {
        {"DIRECTIONAL", Light::Kind::DIRECTIONAL},
        {"POINT", Light::Kind::POINT},
        {"SPOT", Light::Kind::SPOT}
    };

    std::string name = *kindName;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto it = kinds.find(name);
    if (it != kinds.end()) {
        return it->second;
    }

    return Light::Kind::POINT;
}

void Light::addFromLua(Actor& actor, LuaState& lua) {

    luaL_checktype(lua, -1, LUA_TTABLE);
    actor.add<Light>(readKind(lua));
}

void Light::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "intensity", property(
        [](ComponentReference<Light>& l){return l->m_settings.intensity;},
        [](ComponentReference<Light>& l, float value){l->m_settings.intensity = value;}
    ));

    lua::addProperty(lua, "color", property(
        [](ComponentReference<Light>& l){return l->m_settings.color;},
        [](ComponentReference<Light>& l, const glm::vec3& value){l->m_settings.color = value;}
    ));

    lua::addProperty(lua, "colorAmbient", property(
        [](ComponentReference<Light>& l){return l->m_settings.colorAmbient;},
        [](ComponentReference<Light>& l, const glm::vec3& value){l->m_settings.colorAmbient = value;}
    ));
}

Light::Light(Kind kind) : m_kind(kind) {

    makeDepthMapTexture();
    attachDepthMapToFramebuffer();
}

Light::Light(Light&& other) : m_kind(other.m_kind), m_fbo(other.m_fbo), m_depthMap(other.m_depthMap), m_settings(other.m_settings) {

    other.m_fbo = 0;
    other.m_depthMap = 0;
}

Light& Light::operator=(Light&& other) {

    glDeleteTextures(1, &m_depthMap);
    glDeleteFramebuffers(1, &m_fbo);

    m_settings = other.m_settings;
    m_kind = other.m_kind;
    m_fbo = other.m_fbo;
    m_depthMap = other.m_depthMap;

    other.m_fbo = 0;
    other.m_depthMap = 0;

    return *this;
}

Light::~Light() {

    glDeleteTextures(1, &m_depthMap);
    glDeleteFramebuffers(1, &m_fbo);
}

Light::Settings& Light::getSettings() {
    return m_settings;
}

const Light::Settings& Light::getSettings() const {
    return m_settings;
}

void Light::setSettings(Light::Settings& settings) {
    m_settings = settings;
}

Light::Kind Light::getKind() const {
    return m_kind;
}

void Light::setKind(Light::Kind kind) {

    bool isDifferentDepthMapNeeded = (kind == Kind::DIRECTIONAL) != (m_kind == Kind::DIRECTIONAL);

    m_kind = kind;

    if (isDifferentDepthMapNeeded) {

        glDeleteTextures(1, &m_depthMap);
        makeDepthMapTexture();
        attachDepthMapToFramebuffer();
    }
}

GLuint Light::getFramebufferId() const {
    return m_fbo;
}

GLuint Light::getDepthMapId() const {
    return m_depthMap;
}

glm::mat4 Light::getProjectionMatrix() const {

    return glm::ortho(
        -20.f, 20.f,
        -20.f, 20.f,
        1.f, 100.f
    );
}

glm::mat4 Light::getViewMatrix(const Transform& tf) const {

    return glm::lookAt(tf.getForward() * 10, {0, 0, 0}, {0, 1, 0});
}

void Light::makeDepthMapTexture() {

    glCheckError();

    if (m_depthMap != 0)
        glDeleteTextures(1, &m_depthMap);

    glGenTextures(1, &m_depthMap);
    if (m_kind == Kind::DIRECTIONAL) {

        glBindTexture(GL_TEXTURE_2D, m_depthMap);
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, DepthMapResolution.x, DepthMapResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor[] = {1, 1, 1, 1};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        }
        glBindTexture(GL_TEXTURE_2D, 0);

    } else {

        glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthMap);
        {
            for (GLenum i = 0; i < 6; ++i)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, DepthMapResolution.x, DepthMapResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    glCheckError();
}

void Light::attachDepthMapToFramebuffer() {

    glCheckError();

    if (m_fbo != 0)
        glDeleteFramebuffers(1, &m_fbo);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    {
        if (m_kind == Kind::DIRECTIONAL) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
        } else {
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthMap, 0);
        }
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glCheckError();
}
