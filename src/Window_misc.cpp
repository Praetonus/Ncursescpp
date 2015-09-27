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

/**
 * \fn int Window::move(int y, int x)
 * \brief Call wmove for this window.
 * 
 * \param y,x New position.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::move)(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return wmove(win_, y, x);
}

/**
 * \brief Call mvwin for this window.
 * 
 * \param y,x New position.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::mvwin(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return ::mvwin(win_, y, x);
}

/**
 * \fn int Window::erase()
 * \brief Call werase for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::erase)()
{
	assert(win_ && "Window doesn't manage any object");
	return werase(win_);
}

/**
 * \fn int Window::clear()
 * \brief Call wclear for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::clear)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclear(win_);
}

/**
 * \fn int Window::clrtobot()
 * \brief Call wclrtobot for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::clrtobot)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtobot(win_);
}

/**
 * \fn int Window::clrtoeol()
 * \brief Call wclrtoeol for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::clrtoeol)()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtoeol(win_);
}

/**
 * \fn int Window::refresh()
 * \brief Call wrefresh for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::refresh)()
{
	assert(win_ && "Window doesn't manage any object");
	return wrefresh(win_);
}

/**
 * \brief Call wnoutrefresh for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::outrefresh()
{
	assert(win_ && "Window doesn't manage any object");
	return wnoutrefresh(win_);
}

/**
 * \brief Call redrawwin for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::redraw()
{
	assert(win_ && "Window doesn't manage any object");
	return redrawwin(win_);
}

/**
 * \brief Call wredrawln for this window.
 * 
 * \param beg,num Values to pass on to wredrawln.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::redrawln(int beg, int num)
{
	assert(win_ && "Window doesn't manage any object");
	return wredrawln(win_, beg, num);
}

/**
 * \fn int Window::scroll(int n)
 * \brief Call wscrl for this window.
 * 
 * \param n Value to pass on to wscrl.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::scroll)(int n)
{
	assert(win_ && "Window doesn't manage any object");
	return wscrl(win_, n);
}

/**
 * \fn int Window::getyx(int& y, int& x)
 * \brief Call getyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
void (Window::getyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getyx(win_, y, x);
}

/**
 * \fn int Window::getbegyx(int& y, int& x)
 * \brief Call getbegyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
void (Window::getbegyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getbegyx(win_, y, x);
}

/**
 * \fn int Window::getmaxyx(int& y, int& x)
 * \brief Call getmaxyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
void (Window::getmaxyx)(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getmaxyx(win_, y, x);
}

/**
 * \brief Call wtouchln for this window.
 * 
 * \param start,count,changed Values to pass on to wtouchln.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::touchln(int start, int count, bool changed)
{
	assert(win_ && "Window doesn't manage any object");
	return wtouchln(win_, start, count, changed);
}

} // namespace nccpp
