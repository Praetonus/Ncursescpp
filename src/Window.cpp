#include "Window.hpp"
#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

#include "errors.hpp"

namespace nccpp
{

Window::Window(WINDOW* win)
	: win_{win}
{}

Window::Window(int nlines, int ncols, int begin_y, int begin_x)
	: win_{ncurses().newwin_(nlines, ncols, begin_y, begin_x, Key{})}
{
	if (!win_)
		throw WindowInitError{};
}

Window::Window(Window&& mv) noexcept
	: win_{mv.win_}
{
	mv.win_ = nullptr;
}

Window& Window::operator=(Window&& mv) noexcept
{
	if (this != &mv)
	{
		win_ = mv.win_;
		mv.win_ = nullptr;
	}
	return *this;
}

Window::~Window()
{
	destroy();
}

void Window::assign(WINDOW* new_win)
{
	if (win_)
		destroy();
	win_ = new_win;
}

void Window::destroy()
{
	if (win_)
	{
		delwin(win_);
		win_ = nullptr;
	}
}

WINDOW* Window::get_handle()
{
	assert(win_ && "Window doesn't manage any object");
	return win_;
}

int (Window::notimeout)(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return ::notimeout(win_, on);
}

void (Window::timeout)(int delay)
{
	assert(win_ && "Window doesn't manage any object");
	wtimeout(win_, delay);
}

int (Window::clearok)(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return::clearok(win_, on);
}

int (Window::setscrreg)(int top, int bot)
{
	assert(win_ && "Window doesn't manage any object");
	return wsetscrreg(win_, top, bot);
}

// Input functions

int (Window::getch)()
{
	assert(win_ && "Window doesn't manage any object");
	return wgetch(win_);
}

int (Window::mvgetch)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwgetch(win_, y, x);
}

int Window::scanw(char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(win_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

int Window::mvscanw(int y, int x, char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	if (move(y, x) == ERR)
		return ERR;
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(win_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

int (Window::getstr)(std::string& str)
{
	return (this->getnstr)(str, str.size());
}

int (Window::getnstr)(std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return ::wgetnstr(win_, &str[0], static_cast<int>(n));
}

int (Window::mvgetstr)(int y, int x, std::string& str)
{
	return (this->mvgetnstr)(y, x, str, str.size());
}

int (Window::mvgetnstr)(int y, int x, std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	return move(y, x) == ERR ? ERR : (this->getnstr)(str, n);
}

// Output functions

int (Window::addch)(chtype const ch)
{
	assert(win_ && "Window doesn't manage any object");
	return waddch(win_, ch);
}

int (Window::mvaddch)(int y, int x, chtype const ch)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwaddch(win_, y, x, ch);
}

int (Window::echochar)(chtype const ch)
{
	assert(win_ && "Window doesn't manage any object");
	return wechochar(win_, ch);
}

int Window::printw(char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	va_list args;
	va_start(args, fmt);
	auto ret = vw_printw(win_, fmt, args);
	va_end(args);
	return ret;
}

int Window::mvprintw(int y, int x, char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	if (move(y, x) == ERR)
		return ERR;
	va_list args;
	va_start(args, fmt);
	auto ret = vw_printw(win_, fmt, args);
	va_end(args);
	return ret;
}

int (Window::addstr)(std::string const& str)
{
	assert(win_ && "Window doesn't manage any object");
	return waddstr(win_, str.c_str());
}

int (Window::addnstr)(std::string const& str, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return waddnstr(win_, str.c_str(), n);
}

int (Window::mvaddstr)(int y, int x, std::string const& str)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwaddstr(win_, y, x, str.c_str());
}

int (Window::mvaddnstr)(int y, int x, std::string const& str, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwaddnstr(win_, y, x, str.c_str(), n);
}

int (Window::addchstr)(String const& chstr)
{
	assert(win_ && "Window doesn't manage any object");
	return waddchstr(win_, chstr.c_str());
}

int (Window::addchnstr)(String const& chstr, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return waddchnstr(win_, chstr.c_str(), n);
}

int (Window::mvaddchstr)(int y, int x, String const& chstr)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwaddchstr(win_, y, x, chstr.c_str());
}

int (Window::mvaddchnstr)(int y, int x, String const& chstr, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwaddchnstr(win_, y, x, chstr.c_str(), n);
}

// Misc

int (Window::move)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return wmove(win_, y, x);
}

} // namespace nccpp
