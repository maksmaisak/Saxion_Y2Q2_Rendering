//
// Created by Maksym Maisak on 30/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASCENE_H
#define SAXION_Y2Q2_RENDERING_LUASCENE_H

#include "Scene.h"
#include <string>
#include "engine/core/lua/LuaState.h"

class LuaScene : public en::Scene {

public:
    LuaScene(const std::string& filename);
    void open(en::Engine& engine) override;

private:

    void makeEntity(en::Engine& engine, int entityTableIndex = -1);

    std::string m_filename;
};


#endif //SAXION_Y2Q2_RENDERING_LUASCENE_H
