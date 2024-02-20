#pragma once
#include <bave/app.hpp>
#include <bave/core/string_hash.hpp>
#include <optional>

namespace dog {
class PlayerController {

  public:
	PlayerController();

	void tick(bave::Seconds dt, bave::App const& app);
	std::optional<float> get_controller_state(std::string_view key) const;

  private:
	std::unordered_map<std::string, float, bave::StringHash, std::equal_to<>> key_map{};
};
} // namespace dog
