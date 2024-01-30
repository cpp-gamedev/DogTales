#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

namespace component {

constexpr glm::vec2 default_friction{0.999f};
constexpr float default_gravity{-1000.f};
constexpr float default_mass{1.f};

constexpr glm::vec2 max_velocity_v{1000.f};
constexpr bave::Seconds tick_limit_v{100ms};

class Physics {

	bave::Seconds m_residue{};

  public:

	Physics(glm::vec2 fric = default_friction, float grav = default_gravity, float m = default_mass) : friction(fric), gravity(grav), mass(m) {}

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
