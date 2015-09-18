#ifndef NCURSESCPP_ERROR_HPP_
#define NCURSESCPP_ERROR_HPP_

#include <exception>

#include "Color.hpp"

namespace nccpp
{

class BaseError : public std::exception
{
	public:
	BaseError() noexcept = default;

	BaseError(BaseError const&) noexcept = default;
	BaseError& operator=(BaseError const&) noexcept = default;

	virtual ~BaseError() = default;

	char const* what() const noexcept override;
};

class NcursesInitError : public BaseError
{
	public:
	NcursesInitError() noexcept = default;

	NcursesInitError(NcursesInitError const&) noexcept = default;
	NcursesInitError& operator=(NcursesInitError const&) noexcept = default;

	virtual ~NcursesInitError() = default;

	char const* what() const noexcept override;
};

class WindowInitError : public BaseError
{
	public:
	WindowInitError() noexcept = default;

	WindowInitError(WindowInitError const&) noexcept = default;
	WindowInitError& operator=(WindowInitError const&) noexcept = default;

	virtual ~WindowInitError() = default;

	char const* what() const noexcept override;
};

class ColorInitError : public BaseError
{
	public:
	ColorInitError() noexcept = default;

	ColorInitError(ColorInitError const&) noexcept = default;
	ColorInitError& operator=(ColorInitError const&) noexcept = default;

	virtual ~ColorInitError() = default;

	char const* what() const noexcept override;
};

class TooMuchColors : public BaseError
{
	public:
	TooMuchColors(Color const&) noexcept;

	TooMuchColors(TooMuchColors const&) noexcept = default;
	TooMuchColors& operator=(TooMuchColors const&) noexcept = default;

	virtual ~TooMuchColors() = default;

	char const* what() const noexcept override;

	Color const color;
};

class NoSuchColor : public BaseError
{
	public:
	NoSuchColor(bool, int) noexcept;

	NoSuchColor(NoSuchColor const&) noexcept = default;
	NoSuchColor& operator=(NoSuchColor const&) noexcept = default;

	virtual ~NoSuchColor() = default;

	char const* what() const noexcept override;

	bool is_pair_error;
	int pair_or_attr;
};

} // namespace nccpp

#endif // Header guard
