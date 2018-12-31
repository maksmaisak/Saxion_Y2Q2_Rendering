//
// Created by Maksym Maisak on 30/12/18.
//

#include "LuaScene.h"
#include <iostream>
#include <lua/lua.hpp>
#include <cassert>
#include <map>
#include <optional>
#include "engine/Engine.h"
#include "engine/core/lua/LuaStack.h"
#include "engine/resources/Resources.h"

#include "engine/components/Transform.h"
#include "engine/components/RenderInfo.h"
#include "engine/components/Camera.h"
#include "TextureMaterial.hpp"
#include "engine/actor/Actor.h"

template<typename TComponent>
void makeComponent(en::Actor& actor, int componentValueIndex) {

    actor.add<TComponent>();
    //std::cout << "No handler defined for this type of component: " << typeid(TComponent).name() << std::endl;
}

template<>
void makeComponent<en::RenderInfo>(en::Actor& actor, int componentValueIndex) {

    auto& renderInfo = actor.add<en::RenderInfo>();

    auto& lua = actor.getEngine().getLuaState();
    if (!lua_istable(lua, componentValueIndex)) return;

    std::optional<std::string> meshPath = lua.getField<std::string>("mesh", componentValueIndex);
    if (meshPath) renderInfo.mesh = en::Resources<Mesh>::get("assets/" + *meshPath);

    std::optional<std::string> texturePath = lua.getField<std::string>("texture", componentValueIndex);
    if (texturePath) renderInfo.material = en::Resources<TextureMaterial>::get("assets/" + *texturePath);
}

template<>
void makeComponent<en::Transform>(en::Actor& actor, int componentValueIndex) {

    auto& transform = actor.add<en::Transform>();

    auto& lua = actor.getEngine().getLuaState();
    if (!lua_istable(lua, componentValueIndex)) return;

    {
        auto popPosition = lua::PopperOnDestruct(lua);
        lua_getfield(lua, componentValueIndex, "position");
    }
}

void makeComponent(en::Actor& actor, const std::string& componentTypeName, int componentValueIndex) {

    en::LuaState& lua = actor.getEngine().getLuaState();
    assert(lua_istable(lua, componentValueIndex));

    static const std::map<std::string, std::function<void(en::Actor&, int)>> typeToMakeFunction = {
        {"Transform" , &makeComponent<en::Transform> },
        {"RenderInfo", &makeComponent<en::RenderInfo>},
        {"Camera"    , &makeComponent<en::Camera>    }
    };

    auto it = typeToMakeFunction.find(componentTypeName);
    if (it != typeToMakeFunction.end()) it->second(actor, componentValueIndex);
}

LuaScene::LuaScene(const std::string& filename) : m_filename(filename) {}

void LuaScene::open(en::Engine& engine) {

    en::LuaState& lua = engine.getLuaState();
    lua_State* const L = lua;

    lua.makeEnvironment();
    auto popEnvironment = lua::PopperOnDestruct(L);
    if (!lua.loadFile(m_filename)) return;
    lua.setEnvironment(-2);

    auto popFunctionValue = lua::PopperOnDestruct(L);
    if (!lua.pCall(0, 1)) return;

    // Top of stack is now the table with the scene definition
    // Below that is the environment.

    // Iterate over the scene definition.
    lua_pushnil(L);
    while (lua_next(L, -2)) {

        // top of stack is now an table that defines an entity
        // pop it before moving to the next one.
        auto popValue = lua::PopperOnDestruct(L);
        makeEntity(engine, -1);
    }
}

void LuaScene::makeEntity(en::Engine& engine, int entityTableIndex) {

    en::LuaState& lua = engine.getLuaState();
    entityTableIndex = lua_absindex(lua, entityTableIndex);
    assert(lua_istable(lua, entityTableIndex));

    en::Actor actor = engine.makeActor();

    // Iterate over the entity definition.
    lua_pushnil(lua);
    while (lua_next(lua, entityTableIndex)) {

        auto popValue = lua::PopperOnDestruct(lua);

        // key (component type name) is at -2
        // value (component definition) is at -1
        auto componentTypeName = lua.to<std::string>(-2);
        makeComponent(actor, componentTypeName, -1);
    }
}
