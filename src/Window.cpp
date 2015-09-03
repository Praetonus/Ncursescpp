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

// Misc

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
