#include "Ncurses.hpp"

#include <ncurses.h>

namespace nccpp
{

Ncurses::Ncurses()
	: stdscr_{initscr()}
{
	if (!stdscr_)
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

// Extra parenthesis to protect against potential macro expansion

int Ncurses::cbreak(bool on)
{
	return on ? ::cbreak() : nocbreak();
}

int (Ncurses::echo)(bool on)
{
	return on ? ::echo() : noecho();
}

int (Ncurses::halfdelay)(int delay)
{
	return ::halfdelay(delay);
}

int (Ncurses::intrflush)(bool on)
{
	return ::intrflush(stdscr_, on);
}

int Ncurses::keypad(bool on)
{
	return ::keypad(stdscr_, on);
}

int (Ncurses::meta)(bool on)
{
	return ::meta(stdscr_, on);
}

int (Ncurses::nodelay)(bool on)
{
	return ::nodelay(stdscr_, on);
}

int Ncurses::raw(bool on)
{
	return on ? ::raw() : noraw();
}

void (Ncurses::qiflush)(bool on)
{
	on ? ::qiflush() : noqiflush();
}

int (Ncurses::notimeout)(bool on)
{
	return ::notimeout(stdscr_, on);
}

void (Ncurses::timeout)(int delay)
{
	::timeout(delay);
}

int Ncurses::typeahead(int fd)
{
	return ::typeahead(fd);
}

int (Ncurses::clearok)(bool on, bool use_cs)
{
	return::clearok(use_cs ? curscr : stdscr_, on);
}

int Ncurses::idlok(bool on)
{
	return ::idlok(stdscr_, on);
}

void (Ncurses::idcok)(bool on)
{
	::idcok(stdscr_, on);
}

void Ncurses::immedok(bool on)
{
	::immedok(stdscr_, on);
}

int (Ncurses::leaveok)(bool on)
{
	return ::leaveok(stdscr_, on);
}

int (Ncurses::setscrreg)(int top, int bot)
{
	return ::setscrreg(top, bot);
}

int (Ncurses::scrollok)(bool on)
{
	return ::scrollok(stdscr_, on);
}

int (Ncurses::nl)(bool on)
{
	return on ? ::nl() : nonl();
}

InitError::InitError() noexcept
	: exception{}
{}

char const* InitError::what() const noexcept
{
	return "Can't initialize ncurses";
}

} // namespace nccpp
