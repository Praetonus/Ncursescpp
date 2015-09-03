#include "Window.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

// getch

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

// scanw

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

// getstr

int (Window::getstr)(std::string& str)
{
	return (this->getnstr)(str, str.size());
}

int (Window::getnstr)(std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return wgetnstr(win_, &str[0], static_cast<int>(n));
}

int (Window::mvgetstr)(int y, int x, std::string& str)
{
	return (this->mvgetnstr)(y, x, str, str.size());
}

int (Window::mvgetnstr)(int y, int x, std::string& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->getnstr)(str, n);
}

// inch

chtype (Window::inch)()
{
	assert(win_ && "Window doesn't manage any object");
	return winch(win_);
}

chtype (Window::mvinch)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwinch(win_, y, x);
}

// instr

int (Window::instr)(std::string& str)
{
	return (this->innstr)(str, str.size());
}

int (Window::innstr)(std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return winnstr(win_, &str[0], static_cast<int>(n));
}

int (Window::mvinstr)(int y, int x, std::string& str)
{
	return (this->mvinnstr)(y, x, str, str.size());
}

int (Window::mvinnstr)(int y, int x, std::string& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->innstr)(str, n);
}

// inchstr

int (Window::inchstr)(String& str)
{
	return (this->inchnstr)(str, str.size());
}

int (Window::inchnstr)(String& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return winchnstr(win_, &str[0], static_cast<int>(n));
}

int (Window::mvinchstr)(int y, int x, String& str)
{
	return (this->mvinchnstr)(y, x, str, str.size());
}

int (Window::mvinchnstr)(int y, int x, String& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->inchnstr)(str, n);
}

}
