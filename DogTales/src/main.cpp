#include <bave/desktop_app.hpp>
#include <src/dogtales.hpp>

int main(int argc, char** argv) {
	auto create_info = bave::DesktopApp::CreateInfo{
		.args = bave::make_args(argc, argv),
		.title = "DogTales",
		.extent = {1280, 720},
		.assets_patterns = "assets",
	};

	auto app = bave::DesktopApp{create_info};

	app.set_bootloader([](bave::App& app) { return std::make_unique<DogTales>(app); });

	return static_cast<int>(app.run());
}
