#pragma once
#include <bave/core/not_null.hpp>
#include <bave/core/ptr.hpp>
#include <src/fatal_error.hpp>
#include <typeindex>

/// \brief Concept for a serviceable type: it must be pinned since its address is stored.
template <typename Type>
concept ServiceT = !std::is_move_assignable_v<Type> && !std::is_copy_assignable_v<Type>;

/// \brief Services are effectively globals, since any code anywhere can poke at them.
/// The design employed here minimizes the negative effects of globals via:
/// 1. Type safe service access / provision / unprovision.
/// 2. No ownership of service objects.
/// 3. Consolidated storage of all such globals (as opposed to singletons).
/// 4. Batch removal of all provided services.
///
/// Point 2 means that a service instance must actually be (uniquely) owned elsewhere.
/// This provides deterministic lifetime of all services,
/// as opposed to global storage, which pushes lifetimes beyond main's scope, and
/// makes the initialization/destruction order unspecified wrt each other.
namespace services {
/// \brief Internal usage, do not use anything in detail directly.
namespace detail {
void provide(std::type_index index, void* obj);
void unprovide(std::type_index index);
[[nodiscard]] auto find(std::type_index index) -> void*;
} // namespace detail

/// \brief Provide a service by registering its address.
/// \param obj Address of service object.
/// \pre Type must not already be provided.
template <ServiceT Type>
void provide(bave::NotNull<Type*> obj) {
	detail::provide(std::type_index{typeid(Type)}, obj.get());
}

/// \brief Unprovide a service. Safe to call even if service hasn't been provided.
template <ServiceT Type>
void unprovide() {
	detail::unprovide(std::type_index{typeid(Type)});
}

/// \brief Unregister all provided services.
void unprovide_all();

/// \brief Obtain the count of provided services.
[[nodiscard]] auto get_count() -> std::size_t;

/// \brief Locate a service if provided.
/// \returns Pointer to service instance if provided, nullptr otherwise.
template <ServiceT Type>
[[nodiscard]] auto find() -> bave::Ptr<Type> {
	return static_cast<Type*>(detail::find(std::type_index{typeid(Type)}));
}

/// \brief Check if a service type has been provided.
/// \returns true if provided.
template <ServiceT Type>
[[nodiscard]] auto contains() -> bool {
	return find<Type>() != nullptr;
}

/// \brief Locate a provided service.
/// \returns Reference to provided service instance.
/// \pre Type must have been provided.
template <ServiceT Type>
[[nodiscard]] auto get() -> Type& {
	auto* ret = find<Type>();
	if (ret == nullptr) { throw FatalError{"Requested service not present"}; }
	return *ret;
}
} // namespace services

/// \brief CRTP base class for scoped (RAII) service types.
///
/// Usage:
///  struct Foo : CrtpService<Foo> { /*...*/ };
///  Creating a Foo instance will auto-provide Foo service.
///  It will be unprovided on destruction.
template <typename Type>
class CrtpService {
  public:
	CrtpService(CrtpService&&) = delete;
	CrtpService(CrtpService const&) = delete;
	auto operator=(CrtpService&&) -> CrtpService& = delete;
	auto operator=(CrtpService const&) -> CrtpService& = delete;

	CrtpService() { services::provide<Type>(static_cast<Type*>(this)); }
	~CrtpService() { services::unprovide<Type>(); }
};
