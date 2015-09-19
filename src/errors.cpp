#include "errors.hpp"

namespace nccpp
{

char const* BaseError::what() const noexcept
{
	return "nccpp::BaseError";
}

char const* NcursesInitError::what() const noexcept
{
	return "nccpp::NcursesInitError : Can't initialize ncuses, initscr() failed";
}

char const* WindowInitError::what() const noexcept
{
	return "nccpp::WindowInitError : Can't create new window, newwin() failed";
}

char const* ColorInitError::what() const noexcept
{
	return "nccpp::ColorInitError : Can't initialize colors, start_color() failed";
}

TooMuchColors::TooMuchColors(Color const& c) noexcept
	: color{c}
{}

char const* TooMuchColors::what() const noexcept
{
	return "nccpp::TooMuchColors : Can't initialize new colors, init_pair failed";
}

NoSuchColor::NoSuchColor(int pa, bool ip) noexcept
	: pair_or_attr{pa}, is_pair_error{ip}
{}

char const* NoSuchColor::what() const noexcept
{
	return "nccpp::NoSuchColor : Color is uninitialized";
}

} // namespace nccpp
