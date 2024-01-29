#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

class Player {
	static constexpr glm::vec2 speed_v{50.0f, 50.0f};
	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	glm::vec2 m_world_space{};

	bave::Transform m_position{};
	bave::Sprite m_sprite{};
	bave::Rect<> m_collider{};

	glm::vec2 m_vel{0};

	void handle_wall_collision();
	void handle_wall_collision2();

	void reduce_velocity();

  public:
	explicit Player(glm::vec2 world_space, bave::App& app);

	void move(glm::vec2 const& delta);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;

	bave::App &m_app;
};
