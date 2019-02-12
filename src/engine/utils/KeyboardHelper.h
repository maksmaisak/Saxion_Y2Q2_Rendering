//
// Created by Maksym Maisak on 2019-02-12.
//

#ifndef SAXION_Y2Q2_RENDERING_KEYBOARDHELPER_H
#define SAXION_Y2Q2_RENDERING_KEYBOARDHELPER_H

#include <string>

namespace utils {

    class KeyboardHelper {

    public:
        static bool isDown(const std::string& keyName);
        static bool isHeld(const std::string& keyName);
        static bool isUp(const std::string& keyName);
        static void update();
    };
}

#endif //SAXION_Y2Q2_RENDERING_KEYBOARDHELPER_H
