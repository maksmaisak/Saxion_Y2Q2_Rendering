//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H
#define SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H

#include "Engine.h"
#include "Messaging.h"
#include "EntityEvents.h"
#include "Transformable.h"

namespace en {

    /// Keeps the hierarchy of en::Transformable|s in order.
    class TransformableHierarchySystem : public System,
        Receiver<ComponentAdded<Transformable>>,
        Receiver<ComponentWillBeRemoved<Transformable>>
    {
        void receive(const ComponentAdded<Transformable>& info) override;
        void receive(const ComponentWillBeRemoved<Transformable>& info) override;
    };
}

#endif //SAXION_Y2Q1_CPP_TRANSFORMABLEHIERARCHYSYSTEM_H
