//
// Created by Maksym Maisak on 2019-03-11.
//

#ifndef SAXION_Y2Q2_RENDERING_BATCH_H
#define SAXION_Y2Q2_RENDERING_BATCH_H

#include <vector>
#include "Entity.h"
#include "Mesh.hpp"
#include "glm.hpp"

namespace en {

    class EntityRegistry;

    class Batch : public Mesh {

    public:
        void add(const Mesh& mesh, const glm::mat4& transform = glm::mat4(1));
        void removeDestroyedEntities(const EntityRegistry& registry);

    private:

        struct EntityInfo {
            Entity entity = nullEntity;
            std::size_t startIndex  = 0;
            std::size_t numVertices = 0;
        };

        std::vector<EntityInfo> m_entities;
    };
}

#endif //SAXION_Y2Q2_RENDERING_BATCH_H
