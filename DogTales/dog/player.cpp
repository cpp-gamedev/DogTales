#include <dog/player.hpp>

namespace dog {
Player::Player(bave::App& app, glm::vec2 const world_space) : m_app(app), m_world_space(world_space) {
	m_sprite.set_size(size_v);
}

void Player::tick(bave::Seconds const dt) {

	m_physics.tick(dt);

	auto const& key_state = m_app.get_key_state();
	auto direction = glm::vec2{};
	if (key_state.is_pressed(bave::Key::eW) || key_state.is_pressed(bave::Key::eUp)) { direction.y += 1.0f; }
	if (key_state.is_pressed(bave::Key::eS) || key_state.is_pressed(bave::Key::eDown)) { direction.y -= 1.0f; }
	if (key_state.is_pressed(bave::Key::eA) || key_state.is_pressed(bave::Key::eLeft)) { direction.x -= 1.0f; }
	if (key_state.is_pressed(bave::Key::eD) || key_state.is_pressed(bave::Key::eRight)) { direction.x += 1.0f; }

	if (direction.x != 0.0f || direction.y != 0.0f) {
		direction = glm::normalize(direction);
		auto const displacement = direction * speed_v * dt.count();
		m_physics.position += displacement;
	}
	handle_wall_collision();
	m_sprite.transform.position = m_physics.position;
}

void Player::draw(bave::Shader& shader) const { m_sprite.draw(shader); }

void Player::handle_wall_collision() {
	auto& position = m_physics.position;
	// bounce_rect represents the play area for the sprite, ie the limits for its centre.
	// the size is simply the total space minus the sprite size, centered at the origin.
	// the second argument (glm::vec2{0.0f}) is the default value and can be omitted here.
	auto const bounce_rect = bave::Rect<>::from_size(m_world_space - m_sprite.get_size(), glm::vec2{0.0f});

	// if the sprite's position exceeds the play area, the corresponding velocity component needs to flip.
	if (position.x < bounce_rect.top_left().x || position.x > bounce_rect.bottom_right().x) {
		m_physics.velocity.x *= -0.9f;
	}
	if (position.y > bounce_rect.top_left().y || position.y < bounce_rect.bottom_right().y) {
		m_physics.velocity.y *= -0.9f;
	}

	// clamp the position to the play area.
	// bottom_left() gives us the minimum x and y whereas top_right() gives us the maximum.
	position = glm::clamp(position, bounce_rect.bottom_left(), bounce_rect.top_right());
}
} // namespace dog
