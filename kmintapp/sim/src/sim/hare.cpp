#include "sim/hare.hpp"
#include "kmint/random.hpp"
#include "sim/cow.hpp"
namespace sim {

using namespace kmint;

static const char *hare_image = "resources/hare.png";

std::size_t random_hare_node(map::map_graph const &graph) {
  int r = kmint::random_int(0, 3);
  for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
    if (graph[i].node_info().kind == 'H') {
      if (r == 0)
        return i;
      else
        --r;
    }
  }
  throw "could not find node for hare";
}

hare::hare(map::map_graph &g)
    : play::map_bound_actor{g[random_hare_node(g)]},
      drawable_{*this, kmint::graphics::image{hare_image}}, graph_{&g} {}

void hare::act(kmint::delta_time dt) {
  for (std::size_t i = 0; i < num_colliding_actors(); ++i) {
    auto &a = colliding_actor(i);
    if (cow_ != nullptr && &a == cow_) {
      auto &g = *graph_;
      node(g[random_hare_node(g)]);
      return;
    }
  }
}
} // namespace sim
