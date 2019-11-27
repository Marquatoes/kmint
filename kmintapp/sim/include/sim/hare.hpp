// your code here
#ifndef SIM_HARE_HPP
#define SIM_HARE_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace sim {
	class cow;

	class hare : public kmint::play::map_bound_actor {
	public:
		hare(kmint::map::map_graph& g);
		void act(kmint::delta_time dt) override;
		kmint::ui::drawable const& drawable() const override { return drawable_; }
		void set_cow(cow const& c) { cow_ = &c; }
		bool incorporeal() const override { return false; }
		kmint::scalar collision_range() const override { return 16.0; }
	private:
		kmint::play::image_drawable drawable_;
		kmint::map::map_graph* graph_;
		cow const* cow_{};
	};
} //namespace sim

#endif // SIM_HARE_HPP