#include <dog/dogtales.hpp>

namespace dog {
DogTales::DogTales(bave::App& app) : bave::Driver(app) {}

void DogTales::tick() {
	auto const dt = get_app().get_dt();

	m_player.tick(dt);
}

void DogTales::render() const {
	set_viewport_to_world_space(); // stretch sprites to fit the fixed sized world space.

	if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) { m_player.draw(*shader); }
}

void DogTales::on_key(bave::KeyInput const& key_input) {
	if (key_input.key == bave::Key::eEscape && key_input.action == bave::Action::eRelease) { get_app().shutdown(); }
}

void DogTales::set_viewport_to_world_space() const {
	get_app().get_render_device().render_view.viewport = world_space_v;
}
} // namespace dog
