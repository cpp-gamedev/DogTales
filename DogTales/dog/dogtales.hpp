#pragma once
#include <bave/driver.hpp>
#include <dog/player.hpp>

namespace dog {
class DogTales : public bave::Driver {
	static constexpr glm::vec2 world_space_v{1280.0f, 720.0f};

	Player m_player{world_space_v};

	void tick() final;
	void render() const final;

	void on_key(bave::KeyInput const& key_input) final;

	void set_viewport_to_world_space() const;

  public:
	explicit DogTales(bave::App& app);
};
} // namespace dog
