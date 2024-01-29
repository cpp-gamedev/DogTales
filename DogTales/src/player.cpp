#include <src/player.hpp>

Player::Player(glm::vec2 const world_space) : m_world_space(world_space) { m_sprite.set_size(size_v); }

void Player::tick(bave::Seconds const dt) {
	// Update the player's movement based on velocity.
	m_sprite.transform.position += m_vel * dt.count();

	handle_wall_collision();
}

void Player::draw(bave::Shader& shader) const { m_sprite.draw(shader); }

void Player::update_movement(glm::vec2 const& direction) {
	// Normalize the direction vector
	glm::vec2 normalized_direction = glm::normalize(direction);

	// Apply speed to the normalized direction vector
	m_vel = normalized_direction * speed_v;
}

void Player::handle_input(bave::KeyInput const& key_input) {
	// Mapping keys to direction offsets
	std::unordered_map<bave::Key, glm::vec2> keyMappings{
		{bave::Key::eW, {0.0f, 1.0f}},
		{bave::Key::eA, {-1.0f, 0.0f}},
		{bave::Key::eS, {0.0f, -1.0f}},
		{bave::Key::eD, {1.0f, 0.0f}},
	};

	// Check if the pressed key has a corresponding direction in the map
	auto it = keyMappings.find(key_input.key);
	if (it != keyMappings.end()) { update_movement(it->second); }
}

void Player::handle_wall_collision() {
	auto& position = m_sprite.transform.position;
	// bounce_rect represents the play area for the sprite, ie the limits for its centre.
	// the size is simply the total space minus the sprite size, centered at the origin.
	// the second argument (glm::vec2{0.0f}) is the default value and can be omitted here.
	auto const bounce_rect = bave::Rect<>::from_size(m_world_space - m_sprite.get_size(), glm::vec2{0.0f});

	// if the sprite's position exceeds the play area, the corresponding velocity component needs to flip.
	if (position.x < bounce_rect.top_left().x || position.x > bounce_rect.bottom_right().x) { m_vel.x *= -1.0f; }
	if (position.y > bounce_rect.top_left().y || position.y < bounce_rect.bottom_right().y) { m_vel.y *= -1.0f; }

	// clamp the position to the play area.
	// bottom_left() gives us the minimum x and y whereas top_right() gives us the maximum.
	position = glm::clamp(position, bounce_rect.bottom_left(), bounce_rect.top_right());
}
