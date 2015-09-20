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
