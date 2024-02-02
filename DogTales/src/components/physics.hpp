#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

namespace component {

class Physics {

	static constexpr glm::vec2 default_friction{0.99f};
	static constexpr float default_gravity{-1000.f};
	static constexpr float default_mass{1.f};

	static constexpr glm::vec2 max_velocity_v{1000.f};
	static constexpr bave::Seconds tick_limit_v{100ms};

	bave::Seconds m_residue{};

  public:
	Physics(glm::vec2 friction = default_friction, float gravity = default_gravity, float mass = default_mass)
		: friction(friction), gravity(gravity), mass(mass) {}

	glm::vec2 position{};
	glm::vec2 velocity{};
	glm::vec2 acceleration{};

	glm::vec2 friction{};
	float gravity{};
	float mass{};

	void tick(bave::Seconds dt);
	void integrate(bave::Seconds dt);
};

} // namespace component
