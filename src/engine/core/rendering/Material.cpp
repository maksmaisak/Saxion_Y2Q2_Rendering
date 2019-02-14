//
// Created by Maksym Maisak on 2019-01-09.
//

#include <cassert>
#include <iostream>
#include <utility>
#include "engine/components/Transform.h"
#include "engine/components/Light.h"
#include "Material.h"
#include "Resources.h"
#include "Mesh.hpp"
#include "GLHelpers.h"
#include "GLSetUniform.h"
#include "TupleUtils.h"
#include "GameTime.h"
#include "LuaState.h"

using namespace en;

Material::Material(const std::string& shaderFilename) :
    Material(Resources<ShaderProgram>::get(shaderFilename)) {}

Material::Material(std::shared_ptr<ShaderProgram> shader) : m_shader(std::move(shader)) {

    assert(m_shader);

    m_builtinUniformLocations = cacheBuiltinUniformLocations();
    m_attributeLocations = cacheAttributeLocations();
    detectAllUniforms();
}

std::string getShaderNameFromLua(LuaState& lua) {

    if (!lua_istable(lua, -1) && !lua_isuserdata(lua, -1))
        luaL_error(lua, "Can't make a material out of given %s", luaL_typename(lua, -1));

    return lua.tryGetField<std::string>("shader").value_or("lit");
}

Material::Material(LuaState& lua) : Material(getShaderNameFromLua(lua)) {

    std::string shaderName = getShaderNameFromLua(lua);

    if (shaderName == "lit") {

        setUniformValue("diffuseColor" , lua.tryGetField<glm::vec3>("diffuseColor").value_or(glm::vec3(1, 1, 1)));
        setUniformValue("specularColor", lua.tryGetField<glm::vec3>("specularColor").value_or(glm::vec3(1, 1, 1)));
        setUniformValue("shininess"    , lua.tryGetField<float>("shininess").value_or(10.f));

        std::optional<std::string> diffusePath = lua.tryGetField<std::string>("diffuse");
        if (diffusePath)
            setUniformValue("diffuseMap", Textures::get(config::ASSETS_PATH + *diffusePath));
        else
            setUniformValue("diffuseMap", Textures::white());

        std::optional<std::string> specularPath = lua.tryGetField<std::string>("specular");
        if (specularPath)
            setUniformValue("specularMap", Textures::get(config::ASSETS_PATH + *specularPath));
        else
            setUniformValue("specularMap", Textures::white());

    } else if (shaderName == "sprite") {

        std::optional<std::string> diffusePath = lua.tryGetField<std::string>("texture");
        if (diffusePath)
            setUniformValue("spriteTexture", Textures::get(config::ASSETS_PATH + *diffusePath));
        else
            setUniformValue("spriteTexture", Textures::white());
    }
}

void Material::use(
    Engine* engine,
    DepthMaps* depthMaps,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix
) {
    m_shader->use();
    m_numTexturesInUse = 0;
    setBuiltinUniforms(engine, depthMaps, modelMatrix, viewMatrix, projectionMatrix);
    setCustomUniforms();
}

void Material::render(
    Mesh* mesh,
    Engine* engine,
    DepthMaps* depthMaps,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix
) {
    use(engine, depthMaps, modelMatrix, viewMatrix, projectionMatrix);
    mesh->streamToOpenGL(m_attributeLocations.vertex, m_attributeLocations.normal, m_attributeLocations.uv);
}

inline bool valid(GLint location) {return location != -1;}

void Material::setBuiltinUniforms(
    Engine* engine,
    DepthMaps* depthMaps,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& perspectiveMatrix
) {
    const auto& u = m_builtinUniformLocations;

    // glUniform functions do nothing if location is -1, so checks are only necessary for avoiding calculations.

    gl::setUniform(u.model     , modelMatrix     );
    gl::setUniform(u.view      , viewMatrix      );
    gl::setUniform(u.projection, perspectiveMatrix);

    if (valid(u.pvm))
        gl::setUniform(u.pvm, perspectiveMatrix * viewMatrix * modelMatrix);

    if (valid(u.time))
        gl::setUniform(u.time, GameTime::now().asSeconds());

    if (valid(u.viewPosition))
        gl::setUniform(u.viewPosition, glm::vec3(glm::inverse(viewMatrix)[3]));

    if (depthMaps && valid(u.directionalDepthMaps))
        setUniformTexture(u.directionalDepthMaps, depthMaps->getDirectionalMapsTextureId(), GL_TEXTURE_2D_ARRAY);

    if (depthMaps && valid(u.depthCubemaps))
        setUniformTexture(u.depthCubemaps, depthMaps->getCubemapsTextureId(), GL_TEXTURE_CUBE_MAP_ARRAY);

    auto& registry = engine->getRegistry();

    // Add lights
    int numPointLights = 0;
    int numDirectionalLights = 0;
    int numSpotLights = 0;
    for (Entity e : registry.with<Transform, Light>()) {

        // TODO sort lights by proximity, pick the closest ones.

        auto& light = registry.get<Light>(e);
        auto& tf = registry.get<Transform>(e);

        switch (light.kind) {
            case Light::Kind::POINT:
                if (numPointLights >= m_numSupportedPointLights)
                    break;
                setUniformsPointLight(u.pointLights[numPointLights], light, tf);
                numPointLights += 1;
                break;
            case Light::Kind::DIRECTIONAL:
                if (numDirectionalLights >= m_numSupportedDirectionalLights)
                    break;
                setUniformDirectionalLight(u.directionalLights[numDirectionalLights], light, tf);
                numDirectionalLights += 1;
                break;
            case Light::Kind::SPOT:
                if (numSpotLights >= m_numSupportedSpotLights)
                    break;
                setUniformSpotLight(u.spotLights[numSpotLights], light, tf);
                numSpotLights += 1;
                break;
            default:
                break;
        }
    }
    gl::setUniform(u.numPointLights, numPointLights);
    gl::setUniform(u.numDirectionalLights, numDirectionalLights);
    gl::setUniform(u.numSpotLights, numSpotLights);
}

template<typename T>
void Material::setCustomUniformsOfType(const Material::LocationToUniformValue<T>& values) {

    for (auto& [location, value] : values) {
        gl::setUniform(location, value);
    }
}

template<>
void Material::setCustomUniformsOfType<std::shared_ptr<Texture>>(const Material::LocationToUniformValue<std::shared_ptr<Texture>>& values) {

    for (auto& [location, value] : values) {
        if (!setUniformTexture(location, value->getId()))
            break;
    }
}

void Material::setCustomUniforms() {

    std::apply([this](auto&&... args){(setCustomUniformsOfType(args), ...);}, m_uniformValues);
}

bool Material::setUniformTexture(GLint uniformLocation, GLuint textureId, GLenum textureTarget) {

    if (m_numTexturesInUse >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {

        // TODO have materials (and maybe other resources) have a name to display in these error messages.
        std::cout << "Too many textures for this material: " << m_numTexturesInUse << "/" << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << std::endl;
        return false;
    }

    glActiveTexture(GL_TEXTURE0 + m_numTexturesInUse);
    glBindTexture(textureTarget, textureId);
    glUniform1i(uniformLocation, m_numTexturesInUse);

    //std::cout << "Set texture to uniform. Texture unit: " << m_numTexturesInUse << ", textureId: " << textureId << ", textureTarget: " << textureTarget << ", uniform location: " << uniformLocation << std::endl;

    m_numTexturesInUse += 1;
    return true;
}

Material::BuiltinUniformLocations Material::cacheBuiltinUniformLocations() {

    BuiltinUniformLocations u;

    u.model      = m_shader->getUniformLocation("matrixModel");
    u.view       = m_shader->getUniformLocation("matrixView");
    u.projection = m_shader->getUniformLocation("matrixProjection");
    u.pvm        = m_shader->getUniformLocation("matrixPVM");
    u.time       = m_shader->getUniformLocation("time");
    u.viewPosition = m_shader->getUniformLocation("viewPosition");
    u.directionalDepthMaps = m_shader->getUniformLocation("directionalDepthMaps");
    u.depthCubemaps = m_shader->getUniformLocation("depthCubeMaps");

    // Point lights
    u.numPointLights = m_shader->getUniformLocation("numPointLights");
    for (int i = 0; i < MAX_NUM_POINT_LIGHTS; ++i) {

        std::string prefix = "pointLights[" + std::to_string(i) + "].";
        auto& locations = u.pointLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.position     = m_shader->getUniformLocation(prefix + "position");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");
        locations.farPlaneDistance = m_shader->getUniformLocation(prefix + "farPlaneDistance");

        m_numSupportedPointLights = i + 1;
    }

    // Directional lights
    u.numDirectionalLights = m_shader->getUniformLocation("numDirectionalLights");
    for (int i = 0; i < MAX_NUM_DIRECTIONAL_LIGHTS; ++i) {

        std::string prefix = "directionalLights[" + std::to_string(i) + "].";
        auto& locations = u.directionalLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.direction    = m_shader->getUniformLocation(prefix + "direction");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");
        locations.lightspaceMatrix = m_shader->getUniformLocation("directionalLightspaceMatrix[" + std::to_string(i) + "]");

        m_numSupportedDirectionalLights = i + 1;
    }
    // Spot lights
    u.numSpotLights = m_shader->getUniformLocation("numSpotLights");
    for (int i = 0; i < MAX_NUM_SPOT_LIGHTS; ++i) {

        std::string prefix = "spotLights[" + std::to_string(i) + "].";
        auto& locations = u.spotLights[i];

        locations.color = m_shader->getUniformLocation(prefix + "color");
        if (locations.color == -1)
            break;

        locations.colorAmbient = m_shader->getUniformLocation(prefix + "colorAmbient");
        locations.position     = m_shader->getUniformLocation(prefix + "position");
        locations.direction    = m_shader->getUniformLocation(prefix + "direction");
        locations.falloffConstant  = m_shader->getUniformLocation(prefix + "falloffConstant");
        locations.falloffLinear    = m_shader->getUniformLocation(prefix + "falloffLinear");
        locations.falloffQuadratic = m_shader->getUniformLocation(prefix + "falloffQuadratic");
        locations.innerCutoff      = m_shader->getUniformLocation(prefix + "innerCutoff");
        locations.outerCutoff      = m_shader->getUniformLocation(prefix + "outerCutoff");

        m_numSupportedSpotLights = i + 1;
    }

    return u;
}

Material::AttributeLocations Material::cacheAttributeLocations() {

    AttributeLocations a;
    a.vertex = m_shader->getAttribLocation("vertex");
    a.normal = m_shader->getAttribLocation("normal");
    a.uv     = m_shader->getAttribLocation("uv");

    return a;
}

void Material::detectAllUniforms() {

    std::vector<UniformInfo> uniforms = m_shader->getAllUniforms();

    //std::cout << "Uniforms: " << std::endl;
    for (auto& info : uniforms) {
        //std::cout << info.location << " : " << info.name << std::endl;
        m_uniforms[info.name] = info;
    }
    //std::cout << std::endl;
}

void Material::setUniformsPointLight(
    const Material::BuiltinUniformLocations::PointLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.position))
        gl::setUniform(locations.position, tf.getWorldPosition());

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);

    gl::setUniform(locations.farPlaneDistance, light.farPlaneDistance);
}

void Material::setUniformDirectionalLight(
    const Material::BuiltinUniformLocations::DirectionalLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.direction))
        gl::setUniform(locations.direction, tf.getForward());

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);

    if (valid(locations.lightspaceMatrix)) {
        gl::setUniform(locations.lightspaceMatrix, light.matrixPV);
    }
}

void Material::setUniformSpotLight(
    const BuiltinUniformLocations::SpotLightLocations& locations,
    const Light& light,
    const Transform& tf
) {
    if (valid(locations.position))
        gl::setUniform(locations.position, tf.getWorldPosition());

    if (valid(locations.direction))
        gl::setUniform(locations.direction, glm::normalize(glm::vec3(tf.getWorldTransform()[2])));

    gl::setUniform(locations.color       , light.color * light.intensity);
    gl::setUniform(locations.colorAmbient, light.colorAmbient * light.intensity);
    gl::setUniform(locations.falloffConstant , light.falloff.constant);
    gl::setUniform(locations.falloffLinear   , light.falloff.linear);
    gl::setUniform(locations.falloffQuadratic, light.falloff.quadratic);
    gl::setUniform(locations.innerCutoff, light.spotlightInnerCutoff);
    gl::setUniform(locations.outerCutoff, glm::min(light.spotlightInnerCutoff, light.spotlightOuterCutoff));
}