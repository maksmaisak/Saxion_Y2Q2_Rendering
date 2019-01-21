//
// Created by Maksym Maisak on 30/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASCENE_H
#define SAXION_Y2Q2_RENDERING_LUASCENE_H

#include "Scene.h"
#include <string>
#include "engine/core/lua/LuaState.h"
#include "engine/actor/Actor.h"

class LuaScene : public en::Scene {

public:
    LuaScene(const std::string& filename);
    virtual ~LuaScene();

    void open() override;
    void update(float dt) override;

private:

    void makeEntities(int sceneDefinitionIndex = -1);
    en::Actor makeEntity(int entityDefinitionIndex = -1);
    void addComponents(en::Actor& actor, int entityDefinitionIndex = -1);

    std::string m_filename;

    int m_luaUpdateFunctionRef = LUA_NOREF;
};

#endif //SAXION_Y2Q2_RENDERING_LUASCENE_H
