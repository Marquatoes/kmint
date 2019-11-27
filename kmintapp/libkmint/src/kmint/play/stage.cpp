#include "kmint/play/stage.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/play/quad_tree.hpp"
#include "kmint/util/finally.hpp"
#include <algorithm>
#include <stdexcept>
#include <algorithm>

namespace kmint {
namespace play {

void stage::check_interactions() {
  quad_tree<4> qt{math::rectangle{{0.f, 0.f}, size_}};
  auto b = begin();
  auto e = end();
  for(auto i = b; i != e; ++i) {
    qt.add(*i);
  }
  for(auto i = b; i != e; ++i) {
    qt.find(i->collision_box(), i->collision_adder());
    qt.find(i->perception_box(), i->perceived_adder());
  }
}

void stage::act(delta_time dt) {
  acting_ = true;
  finally f{[&] { acting_ = false; }};

  check_interactions();

  for (actor &a : *this) {
    a.act(dt);
  }

  auto it = actors_.begin();
  while (it != actors_.end()) {
    if (auto &aptr = *it; aptr->removed()) {
      it = actors_.erase(it);
    } else {
      aptr->empty_collisions();
      aptr->empty_perceived();
      ++it;
    }
  }
}

void stage::remove_actor(actor const &a) {
  if (acting_)
    throw std::logic_error{"Cannot call remove_actor while game logic is "
                           "executing. Use actor::remove instead"};
  actors_.erase(
      std::remove_if(actors_.begin(), actors_.end(),
                     [&a](auto const &ptr) { return &a == ptr.get(); }),
      actors_.end());
}
stage::iterator stage::begin() {
  return {actors_.begin(), util::deref_unique_ptr<actor>};
}
stage::iterator stage::end() {
  return {actors_.end(), util::deref_unique_ptr<actor>};
}
stage::const_iterator stage::cbegin() const {
  return {actors_.begin(), util::deref_unique_ptr_const<actor>};
}
stage::const_iterator stage::cend() const {
  return {actors_.end(), util::deref_unique_ptr_const<actor>};
}
stage::const_iterator stage::begin() const { return cbegin(); }
stage::const_iterator stage::end() const { return cend(); }

} // namespace play

} // namespace kmint
