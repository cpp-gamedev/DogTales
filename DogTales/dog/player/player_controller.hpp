#pragma once
#include <bave/app.hpp>
#include <bave/core/string_hash.hpp>
#include <unordered_map>
#include <vector>

namespace dog {
class PlayerController {

  public:
	struct Throttle {
		bave::Key lo{}; // -1
		bave::Key hi{}; // +1
	};

	explicit PlayerController(bave::NotNull<bave::App const*> app);

	void bind_throttle(std::string_view id, Throttle throttle);
	void bind_key(std::string_view id, bave::Key key);

	float get_state(std::string_view id) const;

  private:
	bave::NotNull<bave::App const*> m_app;

	using Mapping = Throttle; // later to be a variant of Throttle / GamepadAxis / GamepadButton.

	std::unordered_map<std::string, std::vector<Mapping>, bave::StringHash, std::equal_to<>> m_mappings{};
};
} // namespace dog
