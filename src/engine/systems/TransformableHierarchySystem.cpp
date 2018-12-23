//
// Created by Maksym Maisak on 4/11/18.
//

#include "TransformableHierarchySystem.h"

namespace en {

    void TransformableHierarchySystem::receive(const ComponentAdded<TransformableSFML>& info) {
        info.component.m_registry = m_registry;
    }

    void TransformableHierarchySystem::receive(const ComponentWillBeRemoved<TransformableSFML>& info) {
        for (Entity child : info.component.m_children) {
            m_registry->destroy(child);
        }
    }
}
