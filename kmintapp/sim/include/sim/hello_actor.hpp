// your code here

#ifndef SIM_HELLO_ACTOR_HPP
#define SIM_HELLO_ACTOR_HPP

#include "kmint/play.hpp"
#include "sim/rectangle_drawable.hpp"

namespace sim {

class hello_actor : public kmint::play::free_roaming_actor {
public:
	hello_actor(kmint::math::vector2d location);
	kmint::ui::drawable const& drawable() const override;
	void move(kmint::math::vector2d delta);
private:
	rectangle_drawable drawable_;
};
} // namespace sim

#endif // SIM_HELLO_ACTOR_HPP