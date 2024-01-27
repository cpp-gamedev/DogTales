#include <src/player.hpp>

Player::Player(bave::NotNull<bave::App const*> app) : m_app(app) {
	m_shape.set_shape(bave::Quad{});
}

void Player::tick(bave::Seconds dt) {}

void Player::draw(bave::Shader& shader) const {
	m_shape.draw(shader);
}
