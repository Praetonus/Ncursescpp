/*****
 * Copyright Benoit Vey (2015)
 *
 * benoit.vey@etu.upmc.fr
 *
 * This software is a libray whose purpose is to provide a RAII-conform
 * interface over the ncurses library.
 *
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 *****/

#include "Window.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

// addch

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

// printw

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

// addstr

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

// addchstr

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

// insch

int (Window::insch)(chtype ch)
{
	assert(win_ && "Window doesn't manage any object");
	return winsch(win_, ch);
}

int (Window::mvinsch)(int y, int x, chtype ch)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwinsch(win_, y, x, ch);
}

// insstr

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

// delch

int (Window::delch)()
{
	assert(win_ && "Window doesn't manage any object");
	return wdelch(win_);
}

int (Window::mvdelch)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwdelch(win_, y, x);
}

// deleteln

int (Window::insdelln)(int n)
{
	assert(win_ && "Window doesn't manage any object");
	return winsdelln(win_, n);
}

} // namespace nccpp
