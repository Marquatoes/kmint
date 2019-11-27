// your code here
// Don't forget to add this file in your CMakeLists.txt
#include "sim/hello_actor.hpp"

namespace sim {

hello_actor::hello_actor(kmint::math::vector2d location)
	: free_roaming_actor{ location }, drawable_{*this} {}

kmint::ui::drawable const& hello_actor::drawable() const { return drawable_; }

void hello_actor::move(kmint::math::vector2d delta) {
	location(location() + delta);
}
} // namespace sim