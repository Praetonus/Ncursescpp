#include "Window.hpp"

#include <ncurses.h>

namespace nccpp
{

int (Window::attroff)(int a)
{
	return wattroff(win_, a);
}

int (Window::attron)(int a)
{
	return wattron(win_, a);
}

int (Window::attrset)(int a)
{
	return wattrset(win_, a);
}

int (Window::attr_get)(attr_t& a)
{
	return (wattr_get)(win_, &a, nullptr, nullptr);
}

} // namespace nccpp
