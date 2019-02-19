/*****
 * Copyright Benoit Vey (2015)
 *
 * benoit.vey@etu.upmc.fr
 *
 * This software is a library whose purpose is to provide a RAII-conform
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

#ifndef NCURSESCPP_WINDOW_MISC_IPP_
#define NCURSESCPP_WINDOW_MISC_IPP_

namespace nccpp
{

/**
 * \brief Call wmove for this window.
 * 
 * \param y,x New position.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::move(int y, int x)
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
inline int Window::mvwin(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return ::mvwin(win_, y, x);
}

/**
 * \brief Call werase for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::erase()
{
	assert(win_ && "Window doesn't manage any object");
	return werase(win_);
}

/**
 * \brief Call wclear for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::clear()
{
	assert(win_ && "Window doesn't manage any object");
	return wclear(win_);
}

/**
 * \brief Call wclrtobot for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::clrtobot()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtobot(win_);
}

/**
 * \brief Call wclrtoeol for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::clrtoeol()
{
	assert(win_ && "Window doesn't manage any object");
	return wclrtoeol(win_);
}

/**
 * \brief Call wrefresh for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::refresh()
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
inline int Window::outrefresh()
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
inline int Window::redraw()
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
inline int Window::redrawln(int beg, int num)
{
	assert(win_ && "Window doesn't manage any object");
	return wredrawln(win_, beg, num);
}

/**
 * \brief Call wscrl for this window.
 * 
 * \param n Value to pass on to wscrl.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::scroll(int n)
{
	assert(win_ && "Window doesn't manage any object");
	return wscrl(win_, n);
}

/**
 * \brief Call getyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
inline void Window::get_yx(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getyx(win_, y, x);
}

/**
 * \brief Call getbegyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
inline void Window::get_begyx(int& y, int& x)
{
	assert(win_ && "Window doesn't manage any object");
	getbegyx(win_, y, x);
}

/**
 * \brief Call getmaxyx for this window.
 * 
 * \param[out] y,x Result of the operation.
 * \pre The Window manages a ncurses window.
 */
inline void Window::get_maxyx(int& y, int& x)
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
inline int Window::touchln(int start, int count, bool changed)
{
	assert(win_ && "Window doesn't manage any object");
	return wtouchln(win_, start, count, changed);
}

/**
 * \brief Call wenclose for this window.
 * 
 * \param y,x Values to pass on to wenclose.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline bool Window::enclose(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return wenclose(win_, y, x);
}

/**
 * \brief Call wmouse_trafo for this window.
 * 
 * \param[out] y,x Resulting coordinates.
 * \param to_screen If true, convert from window to screen. If false, convert from screen to window.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline bool Window::coord_trafo(int& y, int& x, bool to_screen)
{
	assert(win_ && "Window doesn't manage any object");
	return wmouse_trafo(win_, &y, &x, to_screen);
}

} // namespace nccpp

#endif // Header guard
