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
