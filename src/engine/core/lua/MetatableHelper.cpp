//
// Created by Maksym Maisak on 3/1/19.
//

#include "MetatableHelper.h"

namespace lua {

    namespace detail {

        void printValue(lua_State* L, int index = -1) {

            int typeId = lua_type(L, index);
            switch (typeId) {
                case LUA_TSTRING:
                    printf("%d:`%s'\n", index, lua_tostring(L, index));
                    break;
                case LUA_TBOOLEAN:
                    printf("%d: %s\n", index, lua_toboolean(L, index) ? "true" : "false");
                    break;
                case LUA_TNUMBER:
                    printf("%d: %g\n", index, lua_tonumber(L, index));
                    break;
                default:
                    printf("%d: %s\n", index, lua_typename(L, typeId));
                    break;
            }
        }

        // TODO Change the way properties work. Right now getting things from a ComponentReference is really inefficient,
        // Because it also looks up __getters using this indexFunction too, instead of more directly.

        /// The __index function: (table, key) -> value
        /// Try using a property getter from __getters, otherwise look it up in the metatable
        int indexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key

            std::string keyAsString = getAsString(L, 2);

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property getter from metatable.__getters
            lua_getfield(L, 3, "__getters");
            //std::cout << "metatable.__getters: " << getAsString(L, -1) << std::endl;
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isfunction(L, -1)) {

                //std::cout << "Getting with custom getter: " << getAsString(L, 2) << std::endl;

                // call the getter
                lua_pushvalue(L, 1); // table
                lua_pushvalue(L, 2); // key
                lua_call(L, 2, 1); // getter(table, key)

                return 1;
            }

            //std::cout << "Getting from metatable: " << getAsString(L, 2) << std::endl;

            lua_pushvalue(L, 2);
            lua_gettable(L, 3); // get from metatable

            if (lua_isnil(L, -1)) {
                std::cout << "No custom getter and no value for key: " << getAsString(L, 2) << std::endl;
            }

            return 1;
        }

        /// The __index function: (table, key, value) -> ()
        /// Try using a property setter from __setters,
        /// then try just rawsetting it, if assigning to a table,
        /// otherwise look up the __newindex function of the metatable's metatable and use that.
        /// That last one's for component reference
        int newindexFunction(lua_State* L) {

            luaL_checkany(L, 1); // table or userdata
            luaL_checkany(L, 2); // key
            luaL_checkany(L, 3); // value

            std::string keyAsString = getAsString(L, 2);

            bool hasMetatable = lua_getmetatable(L, 1) == 1;
            assert(hasMetatable);

            // get a property setter from metatable.__setter
            lua_getfield(L, 4, "__setters");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);

            if (lua_isfunction(L, -1)) {

                //std::cout << "Setting with custom setter: " << getAsString(L, 2) << ", " << getAsString(L, 3) << std::endl;

                lua_pushvalue(L, 1); // table
                lua_pushvalue(L, 3); // value
                lua_call(L, 2, 0);

                return 0;
            }

            //lua_pop(L, 2); // remove __setters, nil
            if (lua_istable(L, 1)) {

                //std::cout << "Rawsetting to table: " << getAsString(L, 2) << ", " << getAsString(L, 3) << std::endl;

                lua_pushvalue(L, 2);
                lua_pushvalue(L, 3);
                lua_rawset(L, 1);

                return 0;
            }

            if (luaL_getmetafield(L, 4, "__newindex") != LUA_TNIL && lua_isfunction(L, -1)) {

                if (lua_iscfunction(L, -1) && lua_tocfunction(L, -1) == &newindexFunction)
                    return 0;

                std::cout << "Setting with the __newindex function of the metatable of the metatable: " << getAsString(L, 2) << ", " << getAsString(L, 3) << std::endl;

                lua_pushvalue(L, 1); // table
                lua_pushvalue(L, 2); // key
                lua_pushvalue(L, 3); // value
                lua_call(L, 3, 0);
            }

            return 0;
        }
    }
}