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

#include "Window.hpp"
#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

/**
 * \fn int Window::attroff(int a)
 * \brief Call wattroff for this window.
 * 
 * \param a The attribute value.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::attroff)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattroff(win_, a);
}

/**
 * \fn int Window::attron(int a)
 * \brief Call wattron for this window.
 * 
 * \param a The attribute value.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::attron)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattron(win_, a);
}

/**
 * \fn int Window::attrset(int a)
 * \brief Call wattrset for this window.
 * 
 * \param a The attribute value.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::attrset)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattrset(win_, a);
}

/**
 * \fn int Window::attr_get(attr_t& a)
 * \brief Get the attributes of the window.
 * 
 * \param[out] a Reference to store the attributes.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::attr_get)(attr_t& a)
{
	assert(win_ && "Window doesn't manage any object");
	return (wattr_get)(win_, &a, nullptr, nullptr);
}

/**
 * \fn int Window::color_get(Color& c)
 * \brief Get the color of the window.
 * 
 * \param[out] c Reference to store the color.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::color_get(Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, nullptr, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

/**
 * \fn int Window::attr_color_get(Color& c)
 * \brief Get the attributes and the color of the window.
 * 
 * \param[out] a Reference to store the attributes.
 * \param[out] c Reference to store the color.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int Window::attr_color_get(attr_t& a, Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, &a, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

/**
 * \fn int Window::chgat(int n, attr_t a, Color c)
 * \brief Call wchgat for this window.
 * \param n,a,c Values to pass on to wchgat.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::chgat)(int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return ::wchgat(win_, n, a, ncurses().color_to_pair_number(c), nullptr);
}

/**
 * \fn int Window::mvchgat(int y, int x, int n, attr_t a, Color c)
 * \brief Call mvwchgat for this window.
 * \param y,x,n,a,c Values to pass on to mvwchgat.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
int (Window::mvchgat)(int y, int x, int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return (this->move)(y, x) == ERR ? ERR : (this->chgat)(n, a, c);
}

} // namespace nccpp
