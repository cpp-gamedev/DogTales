#include <bave/clap/clap.hpp>
#include <bave/desktop_app.hpp>
#include <src/build_version.hpp>
#include <src/dogtales.hpp>
#include <iostream>

namespace {
auto parse_args(int const argc, char const* const* argv) -> std::optional<int> {
	namespace clap = bave::clap;
	auto name = clap::make_app_name(*argv);
	auto description = std::string{"2D platformer game using bave"};
	auto version = bave::to_string(dog_tales::build_version_v);
	auto options = clap::Options{std::move(name), std::move(description), std::move(version)};

	auto show_bave_version = false;
	options.flag(show_bave_version, "bave-version", "show bave version");

	auto const result = options.parse(argc, argv);
	if (clap::should_quit(result)) { return clap::return_code(result); }

	if (show_bave_version) {
		std::cout << "bave version " << bave::to_string(bave::build_version_v) << "\n";
		return EXIT_SUCCESS;
	}

	return {};
}

auto run_app(int const argc, char const* const* argv) -> int {
	auto create_info = bave::DesktopApp::CreateInfo{
		.args = bave::make_args(argc, argv),
		.title = "DogTales",
		.mode = bave::Windowed{.extent = {1280, 720}},
		.assets_patterns = "assets",
	};

	auto app = bave::DesktopApp{create_info};

	app.set_bootloader([](bave::App& app) { return std::make_unique<DogTales>(app); });

	return static_cast<int>(app.run());
}
} // namespace

int main(int argc, char** argv) {
	if (auto const ret = parse_args(argc, argv)) { return *ret; }

	return run_app(argc, argv);
}
