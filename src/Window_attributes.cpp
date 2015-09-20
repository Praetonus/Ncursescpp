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
#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

int (Window::attroff)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattroff(win_, a);
}

int (Window::attron)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattron(win_, a);
}

int (Window::attrset)(int a)
{
	assert(win_ && "Window doesn't manage any object");
	return wattrset(win_, a);
}

int (Window::attr_get)(attr_t& a)
{
	assert(win_ && "Window doesn't manage any object");
	return (wattr_get)(win_, &a, nullptr, nullptr);
}

int Window::color_get(Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, nullptr, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

int Window::attr_color_get(attr_t& a, Color& c)
{
	assert(win_ && "Window doesn't manage any object");
	short pair_n{0};
	if ((wattr_get)(win_, &a, &pair_n, nullptr) == ERR)
		return ERR;
	c = ncurses().pair_number_to_color(pair_n);
	return OK;
}

int (Window::chgat)(int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return ::wchgat(win_, n, a, ncurses().color_to_pair_number(c), nullptr);
}

int (Window::mvchgat)(int y, int x, int n, attr_t a, Color c)
{
	assert(win_ && "Window doesn't manage any object");
	return move(y, x) == ERR ? ERR : (this->chgat)(n, a, c);
}

} // namespace nccpp
