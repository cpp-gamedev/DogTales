#include "PlayerController.hpp"

namespace dog {

PlayerController::PlayerController() {
	key_map.insert(std::make_pair("move_x", 0.f));
	key_map.insert(std::make_pair("move_y", 0.f));
	key_map.insert(std::make_pair("jump", 0.f));
}

void PlayerController::tick(bave::Seconds dt, bave::App const& app) {

	auto const& key_state = app.get_key_state();

	bool left = key_state.is_pressed(bave::Key::eA) || key_state.is_pressed(bave::Key::eLeft);
	bool right = key_state.is_pressed(bave::Key::eD) || key_state.is_pressed(bave::Key::eRight);
	bool up = key_state.is_pressed(bave::Key::eW) || key_state.is_pressed(bave::Key::eUp);
	bool down = key_state.is_pressed(bave::Key::eS) || key_state.is_pressed(bave::Key::eDown);

	key_map["move_x"] = 0.f;
	key_map["move_x"] = left && !right ? -1.f : key_map["move_x"];
	key_map["move_x"] = right && !left ? 1.f : key_map["move_x"];
	key_map["move_x"] = right && left ? 0.f : key_map["move_x"];

	key_map["move_y"] = 0.f;
	key_map["move_y"] = down && !up ? -1.f : key_map["move_y"];
	key_map["move_y"] = up && !down ? 1.f : key_map["move_y"];
	key_map["move_y"] = up && down ? 0.f : key_map["move_y"];

	key_map["jump"] = key_state.is_pressed(bave::Key::eW) || key_state.is_pressed(bave::Key::eUp) ? 1.f : 0.f;
}

std::optional<float> PlayerController::get_controller_state(std::string_view key) const {
	if (auto search = key_map.find(key); search != key_map.end()) {
		return search->second;
	} else {
		return -1.f;
	}
}

} // namespace dog
