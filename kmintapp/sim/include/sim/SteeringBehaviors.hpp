#ifndef SIM_STEERINGBEHAVIORS_HPP
#define SIM_STEERINGBEHAVIORS_HPP
#include <optional>

namespace sim {

class SteeringBehavoirs {
	public
		kmint::math::vector2d Wander();
		kmint::math::vector2d Seek(kmint::math::vector2d TargetPos);
		kmint::math::vector2d Flee(kmint::math::vector2d TargetPos);
		kmint::math::vector2d Pursuit(const perceptive_actor* evader);
};

} // namespace sim

#endif SIM_STEERINGBEHAVIORS_HPP