#include <src/components/physics.hpp>

namespace dog {

namespace component {

void Physics::tick(bave::Seconds dt) {
	static constexpr bave::Seconds ft{0.005}; // 5ms

	if (dt.count() > tick_limit_v.count()) {
		return;
	} // return for unexpected dt values, particularly during the beginning of the state

	for (dt += m_residue; dt > ft; dt -= ft) { integrate(ft); }
	m_residue = dt;
}

void Physics::integrate(bave::Seconds dt) {
	acceleration.y += gravity * dt.count();
	velocity = (velocity + (acceleration / mass) * dt.count()) * friction;

	velocity = glm::clamp(velocity, -max_velocity_v, max_velocity_v);

	position += velocity * dt.count();
}

} // namespace component

} // namespace dog
