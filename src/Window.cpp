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

void (Window::getyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getyx(win_, y, x);
}

void (Window::getbegyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getbegyx(win_, y, x);
}

void (Window::getmaxyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getmaxyx(win_, y, x);
}

} // namespace nccpp
