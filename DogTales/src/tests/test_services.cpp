#include <bave/core/pinned.hpp>
#include <src/services/services.hpp>
#include <src/tests/test.hpp>

namespace {
namespace one {
struct Foo : bave::Pinned {
	int value{};
};
} // namespace one

namespace two {
struct Foo : bave::Pinned {
	int value{};
};
} // namespace two

ADD_TEST(ServicesTypeIntegrity) {
	auto foo_one = one::Foo{};
	foo_one.value = 1;
	services::provide<one::Foo>(&foo_one);

	auto foo_two = two::Foo{};
	foo_two.value = 2;
	services::provide<two::Foo>(&foo_two);

	ASSERT(services::contains<one::Foo>());
	EXPECT(services::get<one::Foo>().value == 1);
	ASSERT(services::contains<two::Foo>());
	EXPECT(services::get<two::Foo>().value == 2);

	services::unprovide_all();
}

ADD_TEST(ServicesGetException) {
	auto thrown = false;
	try {
		[[maybe_unused]] auto& foo = services::get<one::Foo>();
	} catch (FatalError const&) { thrown = true; }

	EXPECT(thrown);
}

ADD_TEST(ServicesDuplicateException) {
	auto foo = one::Foo{};
	services::provide<one::Foo>(&foo);

	auto thrown = false;
	try {
		services::provide<one::Foo>(&foo);
	} catch (FatalError const&) { thrown = true; }

	EXPECT(thrown);
	services::unprovide_all();
}

ADD_TEST(ServicesCrtpService) {
	struct Bar : CrtpService<Bar> {
		int value{};
	};

	{
		auto bar = Bar{};
		bar.value = 42;

		ASSERT(services::contains<Bar>());
		EXPECT(services::get<Bar>().value == 42);
	}

	EXPECT(!services::contains<Bar>());
	services::unprovide_all();
}
} // namespace
