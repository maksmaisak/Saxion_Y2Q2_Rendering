#include "mge/behaviours/RotatingBehavior.hpp"
#include "mge/core/GameObject.hpp"
#include "components/Transform.h"

RotatingBehavior::RotatingBehavior(en::Actor actor) : Behavior(actor) {}

void RotatingBehavior::update(float pStep) {
    
    //rotates 45� per second
	m_actor.get<en::Transform>().rotate(pStep * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
}
