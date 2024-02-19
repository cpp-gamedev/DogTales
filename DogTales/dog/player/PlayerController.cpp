#include "PlayerController.hpp"
#include <dog/player/PlayerController.hpp>

namespace dog::player {

PlayerController::PlayerController() { key_map.insert(std::make_pair("test", 0.f)); }

void PlayerController::tick(bave::Seconds dt, const bave::App& app) {
	auto const& key_state = app.get_key_state();
	key_map["test"] = key_state.is_pressed(bave::Key::eT) ?  1.f : 0.f;
}

} // namespace dog::player
