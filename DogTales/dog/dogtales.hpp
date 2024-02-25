#pragma once
#include <bave/driver.hpp>
#include <dog/player/player.hpp>

namespace dog {
class DogTales : public bave::Driver {
	static constexpr glm::vec2 world_space_v{1280.0f, 720.0f};

	Player m_player;

	void tick() final;
	void render() const final;

	void set_viewport_to_world_space() const;

  public:
	explicit DogTales(bave::App& app);
};
} // namespace dog
