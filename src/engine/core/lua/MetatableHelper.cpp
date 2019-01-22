//
// Created by Maksym Maisak on 3/1/19.
//

#include "MetatableHelper.h"

namespace lua {

    namespace detail {

        /// The __index function: (table, key) -> value
        /// Try using a property getter from __getters, otherwise look it up in the metatable
        int indexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property getter from metatable.__getters
            lua_getfield(L, -1, "__getters");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isnil(L, -1)) {

                lua_pop(L, 2); // remove __getters, nil
                lua_pushvalue(L, 2);
                lua_gettable(L, -2); // get from metatable

                lua_remove(L, -2); // remove metatable

                return 1;
            }

            lua_remove(L, -2); // remove __getters

            // call the getter
            lua_pushvalue(L, 1); // table
            lua_pushvalue(L, 2); // key
            lua_pcall(L, 2, 1, 0); // getter(table, key)

            lua_remove(L, -2); // remove metatable

            return 1;
        }

        /// The __index function: (table, key, value) -> ()
        /// Try using a property setter from __setters, otherwise just rawset it
        int newindexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key
            luaL_checkany(L, 3); // value

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property setter from metatable.__setter
            lua_getfield(L, -1, "__setters");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isnil(L, -1)) {

                lua_pop(L, 3); // remove metatable, __setters, nil
                if (lua_istable(L, 1)) {
                    lua_pushvalue(L, 2);
                    lua_pushvalue(L, 3);
                    lua_rawset(L, 1);
                } else {
                    std::cout << "Can't assign this key to userdata " << std::endl;
                }

                return 0;
            }

            lua_remove(L, -2); // remove __setters

            lua_pushvalue(L, 1); // table
            lua_pushvalue(L, 3); // value
            lua_pcall(L, 2, 0, 0);

            lua_remove(L, -2); // remove the metatable

            return 0;
        }
    }
}