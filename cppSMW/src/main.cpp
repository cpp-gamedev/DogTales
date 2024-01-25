#include <bave/desktop_app.hpp>
#include <bave/graphics/shape.hpp>

using bave::Action;
using bave::App;
using bave::DesktopApp;
using bave::Driver;
using bave::Key;
using bave::KeyInput;
using bave::Quad;
using bave::QuadShape;

namespace {
class TestDriver : public Driver {
	QuadShape m_shape{};

	void on_key(KeyInput const& key_input) final {
		if (key_input.key == Key::eEscape && key_input.action == Action::eRelease) { get_app().shutdown(); }
	}

	void render() const final {
		if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) { m_shape.draw(*shader); }
	}

  public:
	explicit TestDriver(App& app) : Driver(app) { m_shape.set_shape(Quad{}); }
};
} // namespace

int main(int argc, char** argv) {
	auto create_info = DesktopApp::CreateInfo{
		.args = bave::make_args(argc, argv),
		.title = "SMW",
		.extent = {1280, 720},
		.assets_patterns = "assets",
	};
	auto app = DesktopApp{create_info};
	app.set_bootloader([](App& app) { return std::make_unique<TestDriver>(app); });
	return static_cast<int>(app.run());
}
