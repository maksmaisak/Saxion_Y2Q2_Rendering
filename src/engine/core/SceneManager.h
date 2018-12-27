//
// Created by Maksym Maisak on 27/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_SCENEMANAGER_H
#define SAXION_Y2Q2_RENDERING_SCENEMANAGER_H

#include <vector>
#include <cassert>
#include "Scene.h"

namespace en {

    class Engine;

    class SceneManager {

    public:
        explicit SceneManager(Engine* engine) : m_engine(engine) {assert(m_engine);}

        inline Scene* getCurrentScene() { return m_currentScene.get(); }
        void setCurrentScene(std::unique_ptr<Scene> scene);
        void setCurrentScene(Scene* scene);

        template<typename TScene, typename... Args>
        inline void setCurrentScene(Args&& ... args) {

            setCurrentScene(std::make_unique<TScene>(std::forward<Args>(args)...));
        }

    private:
        void closeCurrentScene();

        Engine* m_engine;
        std::unique_ptr<Scene> m_currentScene;
    };
}

#endif //SAXION_Y2Q2_RENDERING_SCENEMANAGER_H
