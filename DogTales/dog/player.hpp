#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>
#include "components/physics.hpp"

namespace dog {
class Player {
	static constexpr glm::vec2 speed_v{500.0f, 500.0f};
	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	glm::vec2 m_world_space{};

	bave::Sprite m_sprite{};

	component::Physics m_physics{};

	void handle_wall_collision();

  public:
	explicit Player(glm::vec2 world_space);

	void handle_input(bave::KeyInput const& key_input);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;
	void update_movement(glm::vec2 const& direction);
};
} // namespace dog
