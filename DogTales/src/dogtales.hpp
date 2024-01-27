#include <bave/driver.hpp>
#include <bave/graphics/shape.hpp>

class DogTales : public bave::Driver {
	bave::QuadShape m_shape{};

	void on_key(bave::KeyInput const& key_input) final;
	void render() const final;

  public:
	explicit DogTales(bave::App& app);
};
