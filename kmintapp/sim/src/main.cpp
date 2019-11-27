#include "kmint/main.hpp"          // voor de main loop
#include "kmint/graphics.hpp"      // kleuren en afbeeldingen
#include "kmint/map/map.hpp"       // voor kaarten
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
#include <iostream>

using namespace kmint; // alles van libkmint bevindt zich in deze namespace

class rectangle_drawable : public ui::drawable {
public:
	rectangle_drawable(play::actor const& actor) : drawable{}, actor_{ &actor } {}
	void draw(ui::frame& f) const override;

private:
	play::actor const* actor_;
};

void rectangle_drawable::draw(ui::frame& f) const {
	f.draw_rectangle(actor_->location(), { 10.0, 10.0 }, graphics::colors::white);
}

class perceptive_actor : public play::free_roaming_actor {
public:
	perceptive_actor(math::vector2d location, bool shout, const char* image, kmint::scalar size)
		: free_roaming_actor{ location }, drawable_{ *this, kmint::graphics::image{image, size} }, shout_{ shout } {}

	const ui::drawable& drawable() const override { return drawable_; }
	void move(math::vector2d delta) { location(location() + delta); }
	void act(delta_time dt) override {
		free_roaming_actor::act(dt);
		if (!shout_)
			return;
		for (auto i = begin_perceived(); i != end_perceived(); ++i) {

			std::cout << "saw something at " << i->location().x() << ", "
				<< i->location().y() << "\n";
		}
	}

	// belangrijk! Dit zorgt ervoor dat jouw actor andere actors kan zien
	bool perceptive() const override { return true; }

	// straal waarin een actor andere actors kan waarnemen
	scalar range_of_perception() const { return 30.0f; }

private:
	kmint::play::image_drawable drawable_;
	bool shout_;
	// rectangle_drawable drawable_;
};

int main() {
	// een app object is nodig om
	ui::app app{};

	//  maak een venster aan
	ui::window window{ app.create_window({1024, 768}, "perceptive") };

	// maak een podium aan
	play::stage s{{1024, 768}};

	// Plaats twee actors op het scherm
	math::vector2d center{ 512, 384 };
	auto& my_actor = s.build_actor<perceptive_actor>(center, true, "resources/cow.png", 0.1);

	auto offset = center + math::vector2d{ 50, 50 };
	s.build_actor<perceptive_actor>(offset, false, "resources/hare.png", 1);

	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};

	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls& ctl) {
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.

		for (ui::events::event& e : event_source) {
			// event heeft een methode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });

		}
		});
}