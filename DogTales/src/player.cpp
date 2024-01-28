#include <src/player.hpp>

Player::Player(bave::NotNull<bave::App const*> app) 
	: m_app(app), m_sprite(), m_vel(PLAYER_SPEED), 
	  m_isTouchingGround(false), 
	  m_isMovingLeft(false), m_isMovingRight(false), 
	  m_isMovingUp(false), m_isMovingDown(false) {
	m_sprite.set_texture({});
	m_sprite.set_size({50.0f, 90.0f});
}

void Player::tick(bave::Seconds dt) {
    m_sprite.transform.position += m_vel * dt.count();

    HandleWallCollision();
}

void Player::draw(bave::Shader& shader) const { 
	m_sprite.draw(shader);
}

void Player::HandleWallCollision() {
	const glm::vec2 sprite_size = m_sprite.get_size() / 2.0f;
	const glm::vec2 frame_size = m_app->get_framebuffer_size() / 2;

	HandleLeftRightWallCollision(sprite_size.x, frame_size.x);
	HandleTopBottomWallCollision(sprite_size.y, frame_size.y);
}

void Player::HandleLeftRightWallCollision(const float sprite_width, const float frame_width) {
	const float left_bound  = sprite_width - frame_width;
	const float right_bound = frame_width  - sprite_width;

	float& sprite_pos_x = m_sprite.transform.position.x;
	if (sprite_pos_x < left_bound) {
		sprite_pos_x += left_bound - sprite_pos_x; 
		m_vel.x *= -1.0f;
	} else if (sprite_pos_x > right_bound) {
		sprite_pos_x -= sprite_pos_x - right_bound; 
		m_vel.x *= -1.0f;
	}
}

void Player::HandleTopBottomWallCollision(const float sprite_height, const float frame_height) {
	const float top_bound    = frame_height  - sprite_height;
	const float bottom_bound = sprite_height - frame_height;

	float& sprite_pos_y = m_sprite.transform.position.y;
	if (sprite_pos_y > top_bound) {
		sprite_pos_y -= sprite_pos_y - top_bound; 
		m_vel.y *= -1.0f;
	} else if (sprite_pos_y < bottom_bound) {
		sprite_pos_y += bottom_bound - sprite_pos_y; 
		m_vel.y *= -1.0f;
	}
}
