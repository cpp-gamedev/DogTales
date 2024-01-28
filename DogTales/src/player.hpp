#pragma once
#include <bave/app.hpp>
//#include <bave/graphics/shape.hpp>
#include <bave/graphics/sprite.hpp>

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

constexpr glm::vec2 PLAYER_SPEED { 500.0f, 500.0f };

class Player {
    bave::NotNull<bave::App const*> m_app;

	bave::Sprite m_sprite{};

	glm::vec2 m_vel{};

	bool m_isTouchingGround{};

	bool m_isMovingLeft{};
	bool m_isMovingRight{};
	bool m_isMovingUp{};
	bool m_isMovingDown{};

	void HandleWallCollision();
	void HandleLeftRightWallCollision(const float sprite_width, const float frame_width);
	void HandleTopBottomWallCollision(const float sprite_height, const float frame_height);

  public:
	explicit Player(bave::NotNull<bave::App const*> app);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;
};
