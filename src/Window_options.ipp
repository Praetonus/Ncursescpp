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

#ifndef NCURSESCPP_WINDOW_OPTIONS_IPP_
#define NCURSESCPP_WINDOW_OPTIONS_IPP_

namespace nccpp
{

/**
 * \brief Call keypad for this window.
 * 
 * \param on Value to pass on to keypad.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::keypad(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return ::keypad(win_, on);
}

/**
 * \brief Call nodelay for this window.
 * 
 * \param on Value to pass on to nodelay.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::nodelay(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return ::nodelay(win_, on);
}

/**
 * \brief Call notimeout for this window.
 * 
 * \param on Value to pass on to notimeout.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::notimeout(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return ::notimeout(win_, on);
}

/**
 * \brief Call timeout for this window.
 * 
 * \param delay Value to pass on to timeout.
 * \pre The Window manages a ncurses window.
 */
inline void Window::timeout(int delay)
{
	assert(win_ && "Window doesn't manage any object");
	wtimeout(win_, delay);
}

/**
 * \brief Call clearok for this window.
 * 
 * \param on Value to pass on to clearok.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::clearok(bool on)
{
	assert(win_ && "Window doesn't manage any object");
	return ::clearok(win_, on);
}

/**
 * \brief Call wsetscrreg for this window.
 * 
 * \param top,bot Value to pass on to wsetscrreg.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::setscrreg(int top, int bot)
{
	assert(win_ && "Window doesn't manage any object");
	return wsetscrreg(win_, top, bot);
}

} // namespace nccpp

#endif // Header guard
