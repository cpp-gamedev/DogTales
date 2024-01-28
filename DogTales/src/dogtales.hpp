#pragma once
#include <bave/driver.hpp>
#include <src/player.hpp>

class DogTales : public bave::Driver {
	std::optional<Player> m_player{};
	glm::vec2 m_render_buffer_size{};

	void tick() final;
	void render() const final;

	void on_key(bave::KeyInput const& key_input) final;

	void set_viewport_to_window_size() const;
	void set_viewport_to_fixed_buffer() const;

  public:
	explicit DogTales(bave::App& app);
};
