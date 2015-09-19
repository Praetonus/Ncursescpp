#include "Window.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

int (Window::border)(chtype ls, chtype rs, chtype ts, chtype bs,
                     chtype tl, chtype tr, chtype bl, chtype br)
{
	assert(win_ && "Window doesn't manage any object");
	return wborder(win_, ls, rs, ts, bs, tl, tr, bl, br);
}

int (Window::box)(chtype vch, chtype hch)
{
	assert(win_ && "Window doesn't manage any object");
	return ::box(win_, vch, hch);
}

int (Window::hline)(chtype ch, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return whline(win_, ch, n);
}

int (Window::vline)(chtype ch, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return wvline(win_, ch, n);
}

int (Window::mvhline)(int y, int x, chtype ch, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return move(y, x) == ERR ? ERR : (this->hline)(ch, n);
}

int (Window::mvvline)(int y, int x, chtype ch, int n)
{
	assert(win_ && "Window doesn't manage any object");
	return move(y, x) == ERR ? ERR : (this->vline)(ch, n);
}

void (Window::bkgdset)(int ch)
{
	assert(win_ && "Window doesn't manage any object");
	wbkgdset(win_, static_cast<chtype>(ch));
}

int (Window::bkgd)(int ch)
{
	assert(win_ && "Window doesn't manage any object");
	return wbkgd(win_, static_cast<chtype>(ch));
}

chtype (Window::getbkgd)()
{
	assert(win_ && "Window doesn't manage any object");
	return (::getbkgd)(win_);
}

} // namespace nccpp
