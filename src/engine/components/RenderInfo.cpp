//
// Created by Maksym Maisak on 2019-01-19.
//

#include "RenderInfo.h"
#include <memory>
#include "Material.h"

using namespace en;

void readMaterial(RenderInfo& renderInfo, LuaState& lua) {

    lua_getfield(lua, -1, "material");
    auto p = lua::PopperOnDestruct(lua);

    luaL_checktype(lua, -1, LUA_TTABLE);

    // TODO reuse materials instead of creating new ones for each instance.
    // TODO make it possible to specify different shaders, other than "lit".
    auto material = std::make_shared<Material>("lit");

    material->setUniformValue("diffuseColor" , lua.tryGetField<glm::vec3>("diffuseColor").value_or(glm::vec3(1,1,1)));
    material->setUniformValue("specularColor", lua.tryGetField<glm::vec3>("specularColor").value_or(glm::vec3(1,1,1)));
    material->setUniformValue("shininess", lua.tryGetField<float>("shininess").value_or(10.f));

    std::optional<std::string> diffusePath = lua.tryGetField<std::string>("diffuse");
    if (diffusePath)
        material->setUniformValue("diffuseMap", Textures::get(config::ASSETS_PATH + *diffusePath));
    else
        material->setUniformValue("diffuseMap", Textures::white());

    std::optional<std::string> specularPath = lua.tryGetField<std::string>("specular");
    if (specularPath)
        material->setUniformValue("specularMap", Textures::get(config::ASSETS_PATH + *specularPath));
    else
        material->setUniformValue("specularMap", Textures::white());

    renderInfo.material = std::move(material);
}

RenderInfo& RenderInfo::addFromLua(Actor& actor, LuaState& lua) {

    auto& renderInfo = actor.add<en::RenderInfo>();
    readMaterial(renderInfo, lua);
    return renderInfo;
}

void RenderInfo::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "mesh", lua::writeonlyProperty([](ComponentReference<RenderInfo> renderInfo, const std::string& value) {
        renderInfo->mesh = en::Resources<Mesh>::get("assets/" + value);
    }));
}
