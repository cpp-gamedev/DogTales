#include <src/dogtales.hpp>

DogTales::DogTales(bave::App& app) : bave::Driver(app) {
	m_player = Player{&get_app()};
}

void DogTales::tick() {
	auto const dt = get_app().get_dt();

	m_player->tick(dt);
}

void DogTales::render() const {
	if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) {
		m_player->draw(*shader);
	}
}

void DogTales::on_key(bave::KeyInput const& key_input) {
	if (key_input.key == bave::Key::eEscape && key_input.action == bave::Action::eRelease) {
		get_app().shutdown();
	}
}

