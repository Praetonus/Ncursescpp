#include "Window.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

int Window::keypad(bool on)
{
	return ::keypad(win_, on);
}

int (Window::nodelay)(bool on)
{
	return ::nodelay(win_, on);
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
	return ::clearok(win_, on);
}

int (Window::setscrreg)(int top, int bot)
{
	assert(win_ && "Window doesn't manage any object");
	return wsetscrreg(win_, top, bot);
}

} // namespace nccpp
