//
// Created by Maksym Maisak on 2019-01-19.
//

#include "RenderInfo.h"
#include <memory>
#include "Material.h"

using namespace en;

RenderInfo& RenderInfo::addFromLua(Actor& actor, LuaState& lua) {

    auto& renderInfo = actor.add<en::RenderInfo>();

    if (!lua_istable(lua, -1)) throw "Can't make RenderInfo from a non-table.";

    std::optional<std::string> meshPath = lua.tryGetField<std::string>("mesh");
    if (meshPath) renderInfo.mesh = en::Resources<Mesh>::get("assets/" + *meshPath);

    {
        lua_getfield(lua, -1, "material");
        auto p = lua::PopperOnDestruct(lua);

        luaL_checktype(lua, -1, LUA_TTABLE);

        // TODO reuse materials instead of creating new ones for each instance.
        // TODO make it possible to specify different shaders, other than "lit".
        auto material = std::make_shared<Material>("lit");

        material->setUniformValue("diffuseColor" , glm::vec3(1, 1, 1));
        material->setUniformValue("specularColor", glm::vec3(1, 1, 1));
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

    return renderInfo;
}