#pragma once
#include <bave/app.hpp>
#include <bave/graphics/sprite.hpp>

struct TickAndKeyEventCounter {
	uint64_t tick{0};
	uint64_t key_event{0};
};

struct KeyCounter {
	uint64_t press{0};
	uint64_t release{0};
	uint64_t repeat{0};
};

class Player {
	KeyCounter m_key_w_counter{};
	KeyCounter m_key_a_counter{};
	KeyCounter m_key_s_counter{};
	KeyCounter m_key_d_counter{};
	TickAndKeyEventCounter m_tick_event_counter{};

	enum class Dir : int { eLeft, eRight, eUp, eDown };

	static constexpr glm::vec2 size_v{50.0f, 90.0f};

	glm::vec2 m_world_space{};
	float m_speed{500.0f};

	bave::Sprite m_sprite{};

	std::array<bool, 4> m_dir_held{};

	void handle_wall_collision();

  public:
	explicit Player(glm::vec2 world_space);

	void handle(bave::KeyInput const& key_input);
	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;

	void draw_debug_window();
	void display_key_counter_with_checkbox(char const* name, KeyCounter const& counter, bool& held);
};
