#include "Ncurses.hpp"

#include <ncurses.h>

#include "errors.hpp"

namespace nccpp
{

Ncurses::Ncurses()
	: Window{initscr()}
{
	if (!win_)
		throw NcursesInitError{};
}

Ncurses::~Ncurses()
{
	endwin();
	win_ = nullptr;
}

Ncurses& ncurses()
{
	static Ncurses nc{};
	return nc;
}

// Extra parenthesis may be needed to protect functions against macro expansion

// Input options

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
	return ::intrflush(win_, on);
}

int Ncurses::keypad(bool on)
{
	return ::keypad(win_, on);
}

int (Ncurses::meta)(bool on)
{
	return ::meta(win_, on);
}

int (Ncurses::nodelay)(bool on)
{
	return ::nodelay(win_, on);
}

int Ncurses::raw(bool on)
{
	return on ? ::raw() : noraw();
}

void (Ncurses::qiflush)(bool on)
{
	on ? ::qiflush() : noqiflush();
}

int Ncurses::typeahead(int fd)
{
	return ::typeahead(fd);
}

// Output options

int (Ncurses::clearok)(bool on, bool use_cs)
{
	return::clearok(use_cs ? curscr : win_, on);
}

int Ncurses::idlok(bool on)
{
	return ::idlok(win_, on);
}

void (Ncurses::idcok)(bool on)
{
	::idcok(win_, on);
}

void Ncurses::immedok(bool on)
{
	::immedok(win_, on);
}

int (Ncurses::leaveok)(bool on)
{
	return ::leaveok(win_, on);
}

int (Ncurses::scrollok)(bool on)
{
	return ::scrollok(win_, on);
}

int (Ncurses::nl)(bool on)
{
	return on ? ::nl() : nonl();
}

// Input functions

int Ncurses::ungetch(int ch)
{
	return ::ungetch(ch);
}

int Ncurses::has_key(int ch)
{
	return ::has_key(ch);
}

// Window

WINDOW* Ncurses::newwin_(int nlines, int ncols, int begin_y, int begin_x, Window::Key /*dummy*/)
{
	return newwin(nlines, ncols, begin_y, begin_x);
}

} // namespace nccpp
