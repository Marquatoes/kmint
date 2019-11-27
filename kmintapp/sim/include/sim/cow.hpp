// your code here
#ifndef SIM_COW_HPP
#define SIM_COW_HPP

#include <optional>
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace sim {

class hare;

class cow : public kmint::play::map_bound_actor {
public:
	cow(kmint::map::map_graph& g, kmint::map::map_node& initial_node);
	// wordt elke game tick aangeroepen
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const& drawable() const override { return drawable_; }
	// als incorporeal false is, doet de actor mee aan collision detection
	bool incorporeal() const override { return false; }
	// geeft de lengte van een zijde van de collision box van deze actor terug.
	// Belangrijk voor collision detection
	kmint::scalar collision_range() const override { return 16.0; }
	void set_hare(hare& h) { hare_ = &h; }
	hare* get_hare() const noexcept { return hare_; }
private:
	// hoeveel tijd is verstreken sinds de laatste beweging
	kmint::delta_time t_passed_{};
	// weet hoe de koe getekend moet worden
	kmint::play::image_drawable drawable_;
	hare* hare_{};
};

} // namespace sim

#endif SIM_COW_HPP