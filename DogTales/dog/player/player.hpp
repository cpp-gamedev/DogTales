#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>
#include <dog/components/physics.hpp>
#include <dog/player/player_controller.hpp>

namespace dog {
class Player {
	static constexpr glm::vec2 speed_v{500.0f, 500.0f};
	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	bave::App& m_app; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

	glm::vec2 m_world_space{};

	bave::Sprite m_sprite{};

	component::Physics m_physics{};
	PlayerController m_player_controller{&m_app};

	void handle_wall_collision();

  public:
	explicit Player(bave::App& app, glm::vec2 world_space);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;

	float get_controller_state(std::string_view key) const;

	bool physics_enabled{}; // for debugging
};
} // namespace dog
