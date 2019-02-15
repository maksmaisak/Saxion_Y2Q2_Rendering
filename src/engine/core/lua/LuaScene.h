//
// Created by Maksym Maisak on 30/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_LUASCENE_H
#define SAXION_Y2Q2_RENDERING_LUASCENE_H

#include "Scene.h"
#include <string>
#include "engine/core/lua/LuaState.h"
#include "engine/actor/Actor.h"
#include "Receiver.h"
#include "Collision.h"
#include "LuaReference.h"

namespace en {

    class LuaScene : public Scene, Receiver<Collision> {

    public:
        LuaScene(const std::string& filename);
        LuaScene(LuaReference&& table);
        virtual ~LuaScene();

        void open() override;
        void update(float dt) override;

    private:

        void receive(const Collision& info) override;

        bool popTableOnStack();

        std::string m_filename;
        LuaReference m_table;

        int m_luaUpdateFunctionRef = LUA_NOREF;
        int m_luaOnCollisionFunctionRef = LUA_NOREF;
    };
}

#endif //SAXION_Y2Q2_RENDERING_LUASCENE_H
