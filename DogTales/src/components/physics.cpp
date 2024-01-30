#include <src/components/physics.hpp>

namespace component {

Physics::Physics(glm::vec2 friction, float gravity, float mass) : m_friction(friction), m_gravity(gravity), m_mass(mass) {}

void Physics::tick(bave::Seconds const dt) {
	static constexpr bave::Seconds ft{0.005}; // 5ms

	if (dt.count() > tick_limit) { return; } // return for unexpected dt values, particularly during the beginning of the state

	for (bave::Seconds t{}; t <= dt; t += ft) {
		integrate(t.count());
	}
}

void Physics::integrate(float dt) {
	m_acceleration.y += m_gravity * dt;
	m_velocity = (m_velocity + (m_acceleration / m_mass) * dt) * m_friction;

	m_velocity.x = m_velocity.x > max_velocity.x ? max_velocity.x : m_velocity.x;
	m_velocity.y = m_velocity.y > max_velocity.y ? max_velocity.y : m_velocity.y;
	m_velocity.x = m_velocity.x < -max_velocity.x ? -max_velocity.x : m_velocity.x;
	m_velocity.y = m_velocity.y < -max_velocity.y ? -max_velocity.y : m_velocity.y;

	m_position += m_velocity * dt;
}

} // namespace component
