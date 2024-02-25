#include <bave/imgui/im_text.hpp>
#include <dog/dogtales.hpp>

namespace dog {
DogTales::DogTales(bave::App& app) : bave::Driver(app), m_player(app, world_space_v) {}

void DogTales::tick() {
	auto const dt = get_app().get_dt();

	// ImGui calls
	if constexpr (bave::imgui_v) {
		if (ImGui::Begin("Debug")) {
			if (ImGui::BeginTabBar("Main")) {
				if (ImGui::BeginTabItem("General")) {
					ImGui::Checkbox("Physics", &m_player.physics_enabled);
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Player")) {
					bave::im_text("Controller States");
					ImGui::Separator();
					bave::im_text("move_x (Press A/D or Left/Right): {:.2f}", m_player.get_controller_state("move_x"));
					bave::im_text("move_y (Press W/S or Up/Down): {:.2f}", m_player.get_controller_state("move_y"));
					bave::im_text("Jump (Press Space): {:.2f}", m_player.get_controller_state("jump"));
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}

	// Update player
	m_player.tick(dt);
}

void DogTales::render() const {
	set_viewport_to_world_space(); // stretch sprites to fit the fixed sized world space.

	if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) { m_player.draw(*shader); }
}

void DogTales::set_viewport_to_world_space() const {
	get_app().get_render_device().render_view.viewport = world_space_v;
}
} // namespace dog
