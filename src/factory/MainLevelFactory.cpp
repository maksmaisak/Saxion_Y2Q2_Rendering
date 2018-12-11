//
// Created by Maksym Maisak on 29/10/18.
//

#include "Factory.h"
#include "MyMath.h"

const unsigned int NumAsteroids = 10;

namespace game {

    void makeMainLevel(en::Engine& engine) {

        game::makePlayer(engine);

        for (int i = 0; i < NumAsteroids; ++i) {
            game::makeAsteroid(engine);
        }
    }
}
