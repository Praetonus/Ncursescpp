#include "Window.hpp"
#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

int (Window::attroff)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattroff(win_, a);
}

int (Window::attron)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattron(win_, a);
}

int (Window::attrset)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattrset(win_, a);
}

int (Window::attr_get)(attr_t& a)
{
	assert(win_ && "Window doesn't manage any object");
	return (wattr_get)(win_, &a, nullptr, nullptr);
}

int Window::color_get(Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, nullptr, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

int Window::attr_color_get(attr_t& a, Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, &a, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

int (Window::chgat)(int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return ::wchgat(win_, n, a, ncurses().color_to_pair_number(c), nullptr);
}

int (Window::mvchgat)(int y, int x, int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return move(y, x) == ERR ? ERR : (this->chgat)(n, a, c);
}

} // namespace nccpp
