#include <src/player.hpp>

#include <imgui.h>



Player::Player(glm::vec2 const world_space, bave::App& app) : m_world_space(world_space), m_app(app) {
	m_sprite.set_size(size_v);
	m_position.position = {0, 0};
	m_sprite.transform = m_position;
	m_collider = bave::Rect<float>::from_size(m_sprite.get_size(), m_position.position);
}

void Player::tick(bave::Seconds const dt) {

	handle_wall_collision();

	reduce_velocity();


	ImGui::Begin("Player");
	ImGui::Text("World Space: (%.2f, %.2f)", m_world_space.x, m_world_space.y);
	ImGui::Text("Player Position: (%.2f, %.2f)", m_position.position.x, m_position.position.y);
	ImGui::Text("Sprite Position: (%.2f, %.2f)", m_sprite.transform.position.x, m_sprite.transform.position.y);
	ImGui::Text("Collider Position: (%.2f, %.2f)", m_collider.top_left().x, m_collider.top_left().y);
	ImGui::Text("Velocity: (%.2f, %.2f)", m_vel.x, m_vel.y);
	ImGui::End();


}


void Player::move(glm::vec2 const& dir)
{
	auto const dt = m_app.get_dt();
	float const velocity = speed_v.x * dt.count();

	m_position.position += dir * velocity;
	m_sprite.transform.position = m_position.position;
	//m_collider.lt = m_position.position;
	//m_collider = bave::Rect<float>::from_size(m_sprite.get_size(), m_position.position);

}

void Player::reduce_velocity() {
	m_vel *= 0.99F;
}

void Player::draw(bave::Shader& shader) const {
	m_sprite.draw(shader);


}



void Player::handle_wall_collision2() {

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


