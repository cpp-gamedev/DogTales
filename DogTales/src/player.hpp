#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

class Player {
	enum class Dir : int { eLeft, eRight, eUp, eDown };

	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	glm::vec2 m_world_space{};
	float m_speed{500.0f};

	bave::Sprite m_sprite{};

	std::array<bool, 4> m_dir_held{};

	void handle_wall_collision();

  public:
	explicit Player(glm::vec2 world_space);

	void handle(bave::KeyInput const& key_input);
	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;

	void draw_debug_window();
};
