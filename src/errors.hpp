#ifndef NCURSESCPP_ERROR_HPP

#include <exception>

namespace nccpp
{

class BaseError : public std::exception
{
	public:
	BaseError() noexcept = default;

	BaseError(BaseError const&) noexcept = default;
	BaseError& operator=(BaseError const&) noexcept = default;

	virtual ~BaseError() = default;

	char const* what() const noexcept override
	{
		return "nccpp::BaseError";
	}
};

class NcursesInitError : public BaseError
{
	public:
	NcursesInitError() noexcept = default;

	NcursesInitError(NcursesInitError const& cp) noexcept = default;
	NcursesInitError& operator=(NcursesInitError const& cp) noexcept = default;

	virtual ~NcursesInitError() = default;

	char const* what() const noexcept override
	{
		return "nccpp::NcursesInitError : Can't initialize ncuses, initscr() failed";
	}
};

class WindowInitError : public BaseError
{
	public:
	WindowInitError() noexcept = default;

	WindowInitError(WindowInitError const& cp) noexcept = default;
	WindowInitError& operator=(WindowInitError const& cp) noexcept = default;

	virtual ~WindowInitError() = default;

	char const* what() const noexcept override
	{
		return "nccpp::WindowInitError : Can't create new window, newwin() failed";
	}
};

} // namespace nccpp

#endif // Header guard
