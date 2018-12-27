//
// Created by Maksym Maisak on 27/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_SCENE_H
#define SAXION_Y2Q2_RENDERING_SCENE_H

#include <cassert>

namespace en {

    class Engine;

    class Scene {

    public:
        virtual ~Scene() = default;

        virtual void open(en::Engine& engine) = 0;
        virtual void close(en::Engine& engine) {};
    };
}

#endif //SAXION_Y2Q2_RENDERING_SCENE_H
