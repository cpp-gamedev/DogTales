#pragma once
#include <bave/driver.hpp>
#include <src/player.hpp>

class DogTales : public bave::Driver {
	std::optional<Player> m_player{};

	void tick() final;
	void render() const final;

	void on_key(bave::KeyInput const& key_input) final;

  public:
	explicit DogTales(bave::App& app);
};
