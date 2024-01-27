#pragma once
#include <bave/app.hpp>
#include <bave/graphics/shape.hpp>

class Player {
    bave::NotNull<bave::App const*> m_app;
	bave::QuadShape m_shape{};

  public:
	explicit Player(bave::NotNull<bave::App const*> app);

	void tick(bave::Seconds dt);
	void draw(bave::Shader& shader) const;
};
