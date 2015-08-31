#include "Ncurses.hpp"

#include <ncurses.h>

namespace nccpp
{

Ncurses::Ncurses()
{
	if (!initscr())
		throw InitError{};
}

Ncurses::~Ncurses()
{
	endwin();
}

Ncurses& ncurses()
{
	static Ncurses nc{};
	return nc;
}

InitError::InitError() noexcept
	: exception{}
{}

char const* InitError::what() const noexcept
{
	return "Can't initialize ncurses";
}

} // namespace nccpp
