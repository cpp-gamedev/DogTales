#pragma once
#include <bave/app.hpp>

namespace dog::player {
class PlayerController {

  public:

	PlayerController();

	void tick(bave::Seconds dt, const bave::App& app);

	std::unordered_map<std::string, float> key_map{};

};
} // namespace dog::player
