//
// Created by Maksym Maisak on 2019-03-11.
//

#include "Batch.h"
#include <algorithm>
#include "EntityRegistry.h"
#include "RenderInfo.h"

using namespace en;

void Batch::add(const en::Mesh& mesh, const glm::mat4& transform) {

    Mesh::add(mesh, transform);
}

void Batch::removeDestroyedEntities(const EntityRegistry& registry) {

    /*for (const auto& e : m_entities) {
        if (!registry.isAlive(e)) {
            remove();
        }
    }*/
}