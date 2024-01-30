#include <bave/imgui/im_text.hpp>
#include <src/player.hpp>

namespace {
constexpr void update_motion(bave::Action const action, bool& out_held, KeyCounter& keyCount) {
	switch (action) {
	case bave::Action::eRepeat: keyCount.repeat++; break;
	case bave::Action::ePress:
		keyCount.press++;
		out_held = true;
		break;
	case bave::Action::eRelease:
		keyCount.release++;
		out_held = false;
		break;
	default: break;
	}
}
} // namespace

void Player::display_key_counter_with_checkbox(char const* name, KeyCounter const& counter, bool& held) {
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::Text("%s", name);
	ImGui::TableSetColumnIndex(1);
	ImGui::Checkbox("##held", &held); // Use the key name as part of the ID to ensure uniqueness
	ImGui::TableSetColumnIndex(2);
	ImGui::Text("%llu", counter.press);
	ImGui::TableSetColumnIndex(3);
	ImGui::Text("%llu", counter.release);
	ImGui::TableSetColumnIndex(4);
	ImGui::Text("%llu", counter.repeat);
}

Player::Player(glm::vec2 const world_space) : m_world_space(world_space) { m_sprite.set_size(size_v); }

void Player::handle(bave::KeyInput const& key_input) {
	if (key_input.key == bave::Key::eW || key_input.key == bave::Key::eUp) {
		update_motion(key_input.action, m_dir_held.at(static_cast<std::size_t>(Dir::eUp)), m_key_w_counter);
		m_tick_event_counter.key_event++;
	}
	if (key_input.key == bave::Key::eA || key_input.key == bave::Key::eLeft) {
		update_motion(key_input.action, m_dir_held.at(static_cast<std::size_t>(Dir::eLeft)), m_key_a_counter);
		m_tick_event_counter.key_event++;
	}
	if (key_input.key == bave::Key::eS || key_input.key == bave::Key::eDown) {
		update_motion(key_input.action, m_dir_held.at(static_cast<std::size_t>(Dir::eDown)), m_key_s_counter);
		m_tick_event_counter.key_event++;
	}
	if (key_input.key == bave::Key::eD || key_input.key == bave::Key::eRight) {
		update_motion(key_input.action, m_dir_held.at(static_cast<std::size_t>(Dir::eRight)), m_key_d_counter);
		m_tick_event_counter.key_event++;
	}
}

void Player::tick(bave::Seconds const dt) {
	m_tick_event_counter.tick++;

	auto dxy = glm::vec2{};
	if (m_dir_held.at(static_cast<std::size_t>(Dir::eUp))) { dxy.y += 1.0f; }
	if (m_dir_held.at(static_cast<std::size_t>(Dir::eLeft))) { dxy.x -= 1.0f; }
	if (m_dir_held.at(static_cast<std::size_t>(Dir::eDown))) { dxy.y -= 1.0f; }
	if (m_dir_held.at(static_cast<std::size_t>(Dir::eRight))) { dxy.x += 1.0f; }

	if (dxy.x != 0.0f || dxy.y != 0.0f) {
		// we have non-zero motion
		dxy = glm::normalize(dxy);
	}

	m_sprite.transform.position += dxy * m_speed * dt.count();

	handle_wall_collision();

	draw_debug_window();
}

void Player::draw(bave::Shader& shader) const { m_sprite.draw(shader); }

void Player::draw_debug_window() {
	if constexpr (bave::imgui_v) {
		if (ImGui::Begin("Player")) {
			ImGui::DragFloat("speed", &m_speed, 1.0f, 1.0f, 10000.0f);

			ImGui::Separator();
			ImGui::Text("Tick Count: %llu", m_tick_event_counter.tick);
			ImGui::Text("Key Event Count: %llu", m_tick_event_counter.key_event);

			ImGui::Separator();
			if (ImGui::BeginTable("Key Counts and Directions", 5)) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Key (Dir)");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("Held");
				ImGui::TableSetColumnIndex(2);
				ImGui::Text("Press");
				ImGui::TableSetColumnIndex(3);
				ImGui::Text("Release");
				ImGui::TableSetColumnIndex(4);
				ImGui::Text("Repeat");

				display_key_counter_with_checkbox("W (Up)", m_key_w_counter,
												  m_dir_held.at(static_cast<std::size_t>(Dir::eUp)));
				display_key_counter_with_checkbox("A (Left)", m_key_a_counter,
												  m_dir_held.at(static_cast<std::size_t>(Dir::eLeft)));
				display_key_counter_with_checkbox("S (Down)", m_key_s_counter,
												  m_dir_held.at(static_cast<std::size_t>(Dir::eDown)));
				display_key_counter_with_checkbox("D (Right)", m_key_d_counter,
												  m_dir_held.at(static_cast<std::size_t>(Dir::eRight)));

				ImGui::EndTable();
			}
			ImGui::End();
		}
	}
}

void Player::handle_wall_collision() {
	auto& position = m_sprite.transform.position;
	// bounce_rect represents the play area for the sprite, ie the limits for its centre.
	// the size is simply the total space minus the sprite size, centered at the origin.
	// the second argument (glm::vec2{0.0f}) is the default value and can be omitted here.
	auto const bounce_rect = bave::Rect<>::from_size(m_world_space - m_sprite.get_size(), glm::vec2{0.0f});

	// clamp the position to the play area.
	// bottom_left() gives us the minimum x and y whereas top_right() gives us the maximum.
	position = glm::clamp(position, bounce_rect.bottom_left(), bounce_rect.top_right());
}
