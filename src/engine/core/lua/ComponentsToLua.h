//
// Created by Maksym Maisak on 31/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
#define SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H

#include <map>
#include "engine/actor/Actor.h"

namespace en {

    ///
    class ComponentsToLua {

    public:

        template<typename TComponent>
        inline static void makeComponent(en::Actor& actor, int componentValueIndex) {

            actor.add<TComponent>();
            //std::cout << "No handler defined for this type of component: " << typeid(TComponent).name() << std::endl;
        }
    };
}

#endif //SAXION_Y2Q2_RENDERING_COMPONENTSTOLUA_H
