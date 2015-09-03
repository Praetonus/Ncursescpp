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
	return (this->addnstr)(str, str.size());
}

int (Window::addnstr)(std::string const& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	assert(n <= str.size());
	return waddnstr(win_, str.c_str(), static_cast<int>(n));
}

int (Window::mvaddstr)(int y, int x, std::string const& str)
{
	return (this->mvaddnstr)(y, x, str, str.size());
}

int (Window::mvaddnstr)(int y, int x, std::string const& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->addnstr)(str, n);
}

int (Window::addchstr)(String const& chstr)
{
	return (this->addchnstr)(chstr, chstr.size());
}

int (Window::addchnstr)(String const& chstr, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	assert(n <= chstr.size());
	return waddchnstr(win_, chstr.c_str(), static_cast<int>(n));
}

int (Window::mvaddchstr)(int y, int x, String const& chstr)
{
	return (this->mvaddchnstr)(y, x, chstr.c_str(), chstr.size());
}

int (Window::mvaddchnstr)(int y, int x, String const& chstr, std::size_t n)
{
	return (this->move)(y, x) ? ERR : (this->addchnstr)(chstr, n);
}

int (Window::insstr)(std::string const& str)
{
	return (this->insnstr)(str, str.size());
}

int (Window::insnstr)(std::string const& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	assert(n <= str.size());
	return winsnstr(win_, str.c_str(), static_cast<int>(n));
}

int (Window::mvinsstr)(int y, int x, std::string const& str)
{
	return (this->mvinsnstr)(y, x, str, str.size());
}

int (Window::mvinsnstr)(int y, int x, std::string const& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->insnstr)(str, n);
}

// Deletion functions

int (Window::delch)()
{
	return wdelch(win_);
}

int (Window::mvdelch)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwdelch(win_, y, x);
}

int (Window::insdelln)(int n)
{
	assert(win_ && "Window doesn't manage any object");
	return winsdelln(win_, n);
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
