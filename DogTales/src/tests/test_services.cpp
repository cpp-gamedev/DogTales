#include <bave/core/pinned.hpp>
#include <src/services/services.hpp>
#include <src/tests/test.hpp>

namespace {
namespace one {
struct Foo : IService {
	int value{};
};
} // namespace one

namespace two {
struct Foo : IService {
	int value{};
};
} // namespace two

ADD_TEST(Services_TypeIntegrity) {
	auto services = Services{};

	auto foo_one = std::make_unique<one::Foo>();
	foo_one->value = 1;
	services.bind<one::Foo>(std::move(foo_one));

	auto foo_two = std::make_unique<two::Foo>();
	foo_two->value = 2;
	services.bind<two::Foo>(std::move(foo_two));

	ASSERT(services.contains<one::Foo>());
	EXPECT(services.get<one::Foo>().value == 1);
	ASSERT(services.contains<two::Foo>());
	EXPECT(services.get<two::Foo>().value == 2);
}

ADD_TEST(Services_GetException) {
	auto services = Services{};
	auto thrown = false;
	try {
		[[maybe_unused]] auto& foo = services.get<one::Foo>();
	} catch (dog::FatalError const&) { thrown = true; }

	EXPECT(thrown);
}

ADD_TEST(Services_DuplicateException) {
	auto services = Services{};

	services.bind<one::Foo>(std::make_unique<one::Foo>());

	auto thrown = false;
	try {
		services.bind<one::Foo>(std::make_unique<one::Foo>());
	} catch (dog::FatalError const&) { thrown = true; }

	EXPECT(thrown);
}

ADD_TEST(Services_BindSubclass) {
	auto services = Services{};

	struct Interface : IService {
		virtual auto get_value() -> int = 0;
	};

	struct Concrete : Interface {
		auto get_value() -> int final { return 42; }
	};

	services.bind<Interface>(std::make_unique<Concrete>());

	ASSERT(services.contains<Interface>());
	EXPECT(services.get<Interface>().get_value() == 42);
}
} // namespace
