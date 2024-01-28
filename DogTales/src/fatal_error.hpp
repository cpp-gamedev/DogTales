#pragma once
#include <fmt/format.h>
#include <stdexcept>

class FatalError : public std::runtime_error {
  public:
	template <typename... Args>
	explicit FatalError(fmt::format_string<Args...> fmt, Args&&... args)
		: std::runtime_error(fmt::format(fmt, std::forward<Args>(args)...)) {}
};
