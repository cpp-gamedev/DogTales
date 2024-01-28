#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

class Player {
	static constexpr glm::vec2 speed_v{500.0f, 500.0f};
	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	glm::vec2 m_world_space{};

	bave::Sprite m_sprite{};

	glm::vec2 m_vel{speed_v};

	void handle_wall_collision();

  public:
	explicit Player(glm::vec2 world_space);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;
};
