//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H
#define SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H

#include "Engine.h"
#include "Messaging.h"
#include "EntityEvents.h"
#include "TransformableSFML.h"

namespace en {

    /// Keeps the hierarchy of en::Transformable|s in order.
    class TransformableHierarchySystem : public System,
        Receiver<ComponentAdded<TransformableSFML>>,
        Receiver<ComponentWillBeRemoved<TransformableSFML>>
    {
        void receive(const ComponentAdded<TransformableSFML>& info) override;
        void receive(const ComponentWillBeRemoved<TransformableSFML>& info) override;
    };
}

#endif //SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H
