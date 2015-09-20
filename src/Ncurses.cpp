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

#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

#include "errors.hpp"

namespace nccpp
{

Ncurses::Ncurses()
	: Window{initscr()}, registered_colors_{}, colors_initialized{false}
{
	if (!win_)
		throw NcursesInitError{};
}

Ncurses::~Ncurses()
{
	endwin();
	win_ = nullptr;
#ifdef NO_LEAKS
	_nc_freeall();
#endif
}

Ncurses& ncurses()
{
	static Ncurses nc{};
	return nc;
}

// Extra parenthesis may be needed to protect functions against macro expansion

// Input options

int Ncurses::cbreak(bool on)
{
	return on ? ::cbreak() : nocbreak();
}

int (Ncurses::echo)(bool on)
{
	return on ? ::echo() : noecho();
}

int (Ncurses::halfdelay)(int delay)
{
	return ::halfdelay(delay);
}

int (Ncurses::intrflush)(bool on)
{
	return ::intrflush(win_, on);
}

int (Ncurses::meta)(bool on)
{
	return ::meta(win_, on);
}

int Ncurses::raw(bool on)
{
	return on ? ::raw() : noraw();
}

void (Ncurses::qiflush)(bool on)
{
	on ? ::qiflush() : noqiflush();
}

int Ncurses::typeahead(int fd)
{
	return ::typeahead(fd);
}

// Output options

int (Ncurses::clearok)(bool on, bool use_cs)
{
	return::clearok(use_cs ? curscr : win_, on);
}

int Ncurses::idlok(bool on)
{
	return ::idlok(win_, on);
}

void (Ncurses::idcok)(bool on)
{
	::idcok(win_, on);
}

void Ncurses::immedok(bool on)
{
	::immedok(win_, on);
}

int (Ncurses::leaveok)(bool on)
{
	return ::leaveok(win_, on);
}

int (Ncurses::scrollok)(bool on)
{
	return ::scrollok(win_, on);
}

int (Ncurses::nl)(bool on)
{
	return on ? ::nl() : nonl();
}

// Input functions

int Ncurses::ungetch(int ch)
{
	return ::ungetch(ch);
}

int Ncurses::has_key(int ch)
{
	return ::has_key(ch);
}

// Misc

int Ncurses::doupdate()
{
	return ::doupdate();
}

int Ncurses::line_count()
{
	return LINES;
}

int Ncurses::column_count()
{
	return COLS;
}

// Window

WINDOW* Ncurses::newwin_(int nlines, int ncols, int begin_y, int begin_x, Window::Key /*dummy*/)
{
	return newwin(nlines, ncols, begin_y, begin_x);
}

// Color

void Ncurses::start_color()
{
	if (colors_initialized)
		return;
	if (::start_color() == ERR)
		throw ColorInitError{};
	colors_initialized = true;
}

int Ncurses::use_default_colors()
{
	start_color();
	return ::use_default_colors();
}

short Ncurses::color_to_pair_number(Color const& color)
{
	auto it = std::find_if(std::begin(registered_colors_), std::end(registered_colors_),
	                       [color](Color const& elem){return color == elem;});
	if (it != std::end(registered_colors_))
		return static_cast<short>(it - std::begin(registered_colors_));

	start_color();
	// Ensure push_back will not throw
	registered_colors_.reserve(registered_colors_.size() + 1);
	auto res = init_pair(static_cast<short>(registered_colors_.size() + 1),
	                     color.foreground, color.background);
	if (res == ERR)
		throw TooMuchColors{color};
	registered_colors_.push_back(color);
	return static_cast<short>(registered_colors_.size());
}

int Ncurses::color_to_attr(Color const& color)
{
	return static_cast<int>(COLOR_PAIR(color_to_pair_number(color)));
}

Color Ncurses::pair_number_to_color(short pair_n)
{
	return static_cast<std::size_t>(pair_n) <= registered_colors_.size()
	       ? registered_colors_[static_cast<std::size_t>(pair_n - 1)]
	       : throw NoSuchColor{pair_n, true};
}

Color Ncurses::attr_to_color(attr_t a)
{
	return pair_number_to_color(static_cast<short>(PAIR_NUMBER(a)));
}

int Ncurses::init_color(short color, short r, short g, short b)
{
	start_color();
	return ::init_color(color, r, g, b);
}

} // namespace nccpp
