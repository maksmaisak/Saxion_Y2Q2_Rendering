//
// Created by Maksym Maisak on 27/12/18.
//

#include "SceneManager.h"
#include "Engine.h"

namespace en {

    void SceneManager::setCurrentScene(std::unique_ptr<en::Scene> scene) {

        closeCurrentScene();

        m_currentScene = std::move(scene);
        if (m_currentScene) m_currentScene->open(*m_engine);
    }

    void SceneManager::setCurrentScene(Scene* scene) {

        setCurrentScene(std::unique_ptr<Scene>(scene));
    }

    void SceneManager::closeCurrentScene() {

        if (!m_currentScene) return;

        m_currentScene->close(*m_engine);
        m_engine->getRegistry().destroyAll();
    }
}