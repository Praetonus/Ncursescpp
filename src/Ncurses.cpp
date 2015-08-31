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

// Output options

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

// Input functions

int (Ncurses::getch)()
{
	return wgetch(stdscr_);
}

int (Ncurses::mvgetch)(int y, int x)
{
	return mvwgetch(stdscr_, y, x);
}

int Ncurses::ungetch(int ch)
{
	return ::ungetch(ch);
}

int Ncurses::has_key(int ch)
{
	return ::has_key(ch);
}

int Ncurses::scanw(char const* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(stdscr_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

int Ncurses::mvscanw(int y, int x, char const* fmt, ...)
{
	if (move(y, x) == ERR)
		return ERR;
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(stdscr_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

int (Ncurses::getstr)(std::string& str)
{
	return (this->getnstr)(str, str.size());
}

int (Ncurses::getnstr)(std::string& str, std::size_t n)
{
	str.resize(n);
	return ::wgetnstr(stdscr_, &str[0], static_cast<int>(n));
}

int (Ncurses::mvgetstr)(int y, int x, std::string& str)
{
	return (this->mvgetnstr)(y, x, str, str.size());
}

int (Ncurses::mvgetnstr)(int y, int x, std::string& str, std::size_t n)
{
	return move(y, x) == ERR ? ERR : (this->getnstr)(str, n);
}

// Output functions

int (Ncurses::addch)(chtype const ch)
{
	return waddch(stdscr_, ch);
}

int (Ncurses::mvaddch)(int y, int x, chtype const ch)
{
	return mvwaddch(stdscr_, y, x, ch);
}

int (Ncurses::echochar)(chtype const ch)
{
	return wechochar(stdscr_, ch);
}

int Ncurses::printw(char const* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	auto ret = vw_printw(stdscr_, fmt, args);
	va_end(args);
	return ret;
}

int Ncurses::mvprintw(int y, int x, char const* fmt, ...)
{
	if (move(y, x) == ERR)
		return ERR;
	va_list args;
	va_start(args, fmt);
	auto ret = vw_printw(stdscr_, fmt, args);
	va_end(args);
	return ret;
}

int (Ncurses::addstr)(std::string const& str)
{
	return waddstr(stdscr_, str.c_str());
}

int (Ncurses::addnstr)(std::string const& str, int n)
{
	return waddnstr(stdscr_, str.c_str(), n);
}

int (Ncurses::mvaddstr)(int y, int x, std::string const& str)
{
	return mvwaddstr(stdscr_, y, x, str.c_str());
}

int (Ncurses::mvaddnstr)(int y, int x, std::string const& str, int n)
{
	return mvwaddnstr(stdscr_, y, x, str.c_str(), n);
}

int (Ncurses::addchstr)(String const& chstr)
{
	return waddchstr(stdscr_, chstr.c_str());
}

int (Ncurses::addchnstr)(String const& chstr, int n)
{
	return waddchnstr(stdscr_, chstr.c_str(), n);
}

int (Ncurses::mvaddchstr)(int y, int x, String const& chstr)
{
	return mvwaddchstr(stdscr_, y, x, chstr.c_str());
}

int (Ncurses::mvaddchnstr)(int y, int x, String const& chstr, int n)
{
	return mvwaddchnstr(stdscr_, y, x, chstr.c_str(), n);
}

// Misc

int (Ncurses::move)(int y, int x)
{
	return wmove(stdscr_, y, x);
}

InitError::InitError() noexcept
	: exception{}
{}

char const* InitError::what() const noexcept
{
	return "Can't initialize ncurses";
}

} // namespace nccpp
