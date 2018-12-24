#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "Behavior.h"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehavior : public en::Behavior
{
	public:
        explicit RotatingBehavior(en::Actor actor);
		virtual ~RotatingBehavior() = default;

		void update(float dt) override;
};

#endif // ROTATINGBEHAVIOUR_HPP
