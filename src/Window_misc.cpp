#include "Window.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

int (Window::move)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return wmove(win_, y, x);
}

int (Window::erase)()
{
	assert(win_ && "Window doesn't manage any object");
	return werase(win_);
}

int (Window::clear)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclear(win_);
}

int (Window::clrtobot)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtobot(win_);
}

int (Window::clrtoeol)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtoeol(win_);
}

int (Window::refresh)()
{
	assert(win_ && "Window doesn't manage any object");
	return wrefresh(win_);
}

int Window::outrefresh()
{
	assert(win_ && "Window doesn't manage any object");
	return wnoutrefresh(win_);
}

int Window::redraw()
{
	assert(win_ && "Window doesn't manage any object");
	return redrawwin(win_);
}

int Window::redrawln(int beg, int num)
{
	assert(win_ && "Window doesn't manage any object");
	return wredrawln(win_, beg, num);
}

int (Window::scroll)(int n)
{
	assert(win_ && "Window doesn't manage any object");
	return wscrl(win_, n);
}

} // namespace nccpp
