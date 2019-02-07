//
// Created by Maksym Maisak on 2019-01-19.
//

#include "Light.h"
#include <map>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include "ComponentReference.h"

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

Light::Light(Kind kind) {

    m_kind = kind;

    // Make the depth map texture
    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, DepthMapResolution.x, DepthMapResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // Make the framebuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    if (kind != m_kind) {

        // TODO change the depth map to a cubemap or a flat texture depending on the light kind.
    }

    m_kind = kind;
}

GLuint Light::getFramebufferId() const {
    return m_fbo;
}

GLuint Light::getDepthMapId() const {
    return m_depthMap;
}
