#include <dog/player/player_controller.hpp>
#include <algorithm>
#include <cassert>

namespace dog {

PlayerController::PlayerController(bave::NotNull<bave::App const*> app) : m_app(app) {}

void PlayerController::bind_throttle(std::string_view const id, Throttle const throttle) {
	if (throttle.hi == bave::Key::eUnknown) { return; }
	auto it = m_mappings.find(id);
	if (it == m_mappings.end()) {
		auto [i, _] = m_mappings.insert_or_assign(std::string{id}, std::vector<Mapping>{});
		it = i;
	}
	assert(it != m_mappings.end());
	it->second.push_back(throttle);
}

void PlayerController::bind_key(std::string_view id, bave::Key key) {
	// if Throttle::lo is Key::eUnknown it will be ignored in get_state(), so we exploit that here.
	bind_throttle(id, Throttle{.hi = key});
}

float PlayerController::get_state(std::string_view const id) const {
	auto const search = m_mappings.find(id);
	if (search == m_mappings.end()) { return 0.0f; }

	auto const& mappings = search->second;
	auto const get_throttle_state = [&](Throttle const throttle) {
		auto const is_pressed = [this](bave::Key const key) { return m_app->get_key_state().is_pressed(key); };
		if (throttle.lo != bave::Key::eUnknown && is_pressed(throttle.lo)) { return -1.0f; }
		if (is_pressed(throttle.hi)) { return 1.0f; }
		return 0.0f;
	};

	auto ret = 0.0f;
	for (auto const& mapping : mappings) {
		// later a visitor will be required here, to handle Throttle vs GamepadAxis vs GamepadButton.
		ret += get_throttle_state(mapping);
	}
	return std::clamp(ret, -1.0f, 1.0f);
}

} // namespace dog
