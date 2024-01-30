#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

namespace component {

static constexpr glm::vec2 max_velocity{1000.f, 1000.f};
static constexpr float tick_limit{0.03f}; //this should possibly go somewhere else and be globally accessible

class Physics {

  public:

	glm::vec2 m_position{};
	glm::vec2 m_velocity{};
	glm::vec2 m_acceleration{};
	
	glm::vec2 m_friction{};
	float m_gravity{};
	float m_mass{};

	Physics(glm::vec2 friction, float gravity, float mass = 1.f);

	void tick(bave::Seconds const dt);
	void integrate(float dt);
};

} // namespace component
