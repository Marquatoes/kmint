// your code here
#ifndef _SIM_RECTANGLE_DRAWABLE_HPP
#define _SIM_RECTANGLE_DRAWABLE_HPP

#include "kmint/ui.hpp"

namespace kmint::play {
class actor;
}

namespace sim {

class rectangle_drawable : public kmint::ui::drawable {
public:
	rectangle_drawable(kmint::play::actor const &actor)
		: drawable{}, actor_{ &actor } {}
	void draw(kmint::ui::frame& f) const override;

private:
	kmint::play::actor const* actor_;
};
} // namespace sim

#endif // _SIM_RECTANGLE_DRAWABLE_HPP