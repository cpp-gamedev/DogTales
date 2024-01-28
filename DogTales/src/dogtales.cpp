#include <src/dogtales.hpp>

DogTales::DogTales(bave::App& app) : bave::Driver(app), m_render_buffer_size({1280, 720}) {
	m_player = Player{&get_app()};
}

void DogTales::tick() {
	auto const dt = get_app().get_dt();

	m_player->tick(dt);
}

void DogTales::render() const {
	set_viewport_to_fixed_buffer();   // stretch sprites to fit the framebuffer, fixed sized world space

	if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) {
		m_player->draw(*shader);
	}
}

void DogTales::on_key(bave::KeyInput const& key_input) {
	if (key_input.key == bave::Key::eEscape && key_input.action == bave::Action::eRelease) {
		get_app().shutdown();
	}
}

void DogTales::set_viewport_to_window_size() const {
	get_app().get_render_device().render_view.viewport = get_app().get_window_size();
}

void DogTales::set_viewport_to_fixed_buffer() const {
	get_app().get_render_device().render_view.viewport = m_render_buffer_size;
}

