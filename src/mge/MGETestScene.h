//
// Created by Maksym Maisak on 16/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_MGETESTSCENE_H
#define SAXION_Y2Q2_RENDERING_MGETESTSCENE_H

#include "MGEDemo.hpp"

class MGETestScene : public MGEDemo {

    using MGEDemo::MGEDemo;

public:
    virtual ~MGETestScene() = default;

protected:
    //override so we can construct the actual scene
    void _initializeScene() override;
};


#endif //SAXION_Y2Q2_RENDERING_MGETESTSCENE_H
