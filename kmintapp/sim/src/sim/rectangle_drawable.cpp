// your code here
// Don't forget to add this file in your CMakeLists.txt

#include "sim/rectangle_drawable.hpp"
#include "kmint/play.hpp"

namespace sim {
void rectangle_drawable::draw(kmint::ui::frame& f) const {
	f.draw_rectangle(actor_->location(), { 10.0, 10.0 },
			kmint::graphics::colors::white);
}
} // namespace sim