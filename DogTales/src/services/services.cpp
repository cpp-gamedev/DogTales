#include <src/services/services.hpp>
#include <mutex>
#include <unordered_map>

namespace {
struct {
	std::unordered_map<std::type_index, void*> services{};
	std::mutex mutex{};
} g_data{}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
} // namespace

namespace services {
void detail::provide(std::type_index const index, void* obj) {
	auto lock = std::scoped_lock{g_data.mutex};
	if (g_data.services.contains(index)) { throw FatalError{"Duplicate service instance"}; }
	g_data.services.insert_or_assign(index, obj);
}

void detail::unprovide(std::type_index const index) {
	auto lock = std::scoped_lock{g_data.mutex};
	g_data.services.erase(index);
}

auto detail::find(std::type_index const index) -> void* {
	auto lock = std::scoped_lock{g_data.mutex};
	if (auto const it = g_data.services.find(index); it != g_data.services.end()) { return it->second; }
	return {};
}
} // namespace services

void services::unprovide_all() {
	auto lock = std::scoped_lock{g_data.mutex};
	g_data.services.clear();
}

auto services::get_count() -> std::size_t {
	auto lock = std::scoped_lock{g_data.mutex};
	return g_data.services.size();
}
