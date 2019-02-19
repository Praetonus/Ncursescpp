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

#ifndef NCURSESCPP_NCURSES_IPP_
#define NCURSESCPP_NCURSES_IPP_

#include <algorithm>
#include <cassert>

#include "errors.hpp"

namespace nccpp
{

inline Ncurses::Ncurses()
	: Window{initscr()}, registered_colors_{},
#ifndef NDEBUG
	  windows_{}, is_exit_{false},
#endif
	  colors_initialized_{false}
{
	if (!win_)
		throw errors::NcursesInit{};
}

inline Ncurses::~Ncurses()
{
	endwin();
	win_ = nullptr;
#ifdef NO_LEAKS
	_nc_freeall();
#endif
}

#ifndef NDEBUG
inline void Ncurses::register_window_(Window& new_win, Window::Key /*dummy*/)
{
	windows_.push_back(&new_win);
}

inline void Ncurses::unregister_window_(Window& win, Window::Key /*dummy*/)
{
	auto it = std::find(std::begin(windows_), std::end(windows_), &win);
	assert(it != std::end(windows_));
	windows_.erase(it);
}
#endif

/**
 * \brief Exit ncurses mode and restore normal terminal properties.
 * 
 * \pre %Ncurses mode is on.
 */
inline void Ncurses::exit_ncurses_mode()
{
	assert(!is_exit_ && "Ncurses mode is already off");
#ifndef NDEBUG
	for (auto elem : windows_)
		elem->invalidate_for_exit_(Window::Key{});
	invalidate_for_exit_(Key{});
	is_exit_ = true;
#endif
	endwin();
}

/**
 * \brief Restore ncurses mode after a call to exit_ncurses_mode().
 * 
 * \pre %Ncurses mode is off.
 */
inline void Ncurses::resume_ncurses_mode()
{
	assert(is_exit_ && "Ncurses mode is already on");
#ifndef NDEBUG
	for (auto elem : windows_)
		elem->validate_for_resume_(Window::Key{});
	validate_for_resume_(Key{});
	is_exit_ = false;
#endif
	doupdate();
}

// Input options

/**
 * \brief Change cbreak mode.
 * 
 * \param on If true, call cbreak. Else, call nocbreak.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::cbreak(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return on ? ::cbreak() : nocbreak();
}

/**
 * \brief Change echo mode.
 * 
 * \param on If true, call echo. Else, call noecho.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::echo(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return on ? ::echo() : noecho();
}

/**
 * \brief Call halfdelay.
 * 
 * \param delay Value to pass on to halfdelay.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::halfdelay(int delay)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::halfdelay(delay);
}

/**
 * \brief Call intrflush.
 * 
 * \param on Value to pass on to intrflush.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::intrflush(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::intrflush(win_, on);
}

/**
 * \brief Call meta.
 * 
 * \param on Value to pass on to meta.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::meta(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::meta(win_, on);
}

/**
 * \brief Change raw mode.
 * 
 * \param on If true, call raw. Else, call noraw.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::raw(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return on ? ::raw() : noraw();
}

/**
 * \brief Change qiflush mode.
 * 
 * \param on If true, call qiflush. Else, call noquiflush.
 * \pre %Ncurses mode is on.
 */
inline void Ncurses::qiflush(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	on ? ::qiflush() : noqiflush();
}

/**
 * \brief Call typeahead.
 * 
 * \param fd Value to pass on to typeahead.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::typeahead(int fd)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::typeahead(fd);
}

// Output options

/**
 * \brief Call clearok.
 * 
 * \param on Value to pass on to clearok.
 * \param use_cs If true, call clearok with *curscr* as argument.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::clearok(bool on, bool use_cs)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return::clearok(use_cs ? curscr : win_, on);
}

/**
 * \brief Call idlok.
 * 
 * \param on Value to pass on to idlok.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::idlok(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::idlok(win_, on);
}

/**
 * \brief Call idcok.
 * 
 * \param on Value to pass on to idcok.
 * \pre %Ncurses mode is on.
 */
inline void Ncurses::idcok(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	::idcok(win_, on);
}

/**
 * \brief Call immedok.
 * 
 * \param on Value to pass on to immedok.
 * \pre %Ncurses mode is on.
 */
inline void Ncurses::immedok(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	::immedok(win_, on);
}

/**
 * \brief Call leaveok.
 * 
 * \param on Value to pass on to leaveok.
 * \pre %Ncurses mode is on.
 */
inline int Ncurses::leaveok(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::leaveok(win_, on);
}

/**
 * \brief Call scrollok.
 * 
 * \param on Value to pass on to scrollok.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::scrollok(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::scrollok(win_, on);
}

/**
 * \brief Change nl mode.
 * 
 * \param on If true, call nl. Else, call nonl.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::nl(bool on)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return on ? ::nl() : nonl();
}

// Input functions

/**
 * \brief Call ungetch.
 * 
 * \param ch Value to pass on to ungetch.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::ungetch(int ch)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::ungetch(ch);
}

/**
 * \brief Call has_key.
 * 
 * \param ch Value to pass on to has_key.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::has_key(int ch)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::has_key(ch);
}

// Misc

/**
 * \brief Call doupdate.
 * 
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::doupdate()
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::doupdate();
}

/**
 * \brief Get the height of the terminal.
 * 
 * \pre %Ncurses mode is on.
 * \return The number of lines of the terminal.
 */
inline int Ncurses::line_count()
{
	assert(!is_exit_ && "Ncurses mode is off");
	return LINES;
}

/**
 * \brief Get the width of the terminal.
 * 
 * \pre %Ncurses mode is on.
 * \return The number of columns of the terminal.
 */
inline int Ncurses::column_count()
{
	assert(!is_exit_ && "Ncurses mode is off");
	return COLS;
}

// Mouse

/**
 * \brief Call has_mouse.
 * 
 * \pre %Ncurses mode is on.
 * \return True if the mouse is availiable.
 */
inline bool Ncurses::has_mouse()
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::has_mouse();
}

/**
 * \brief Call getmouse.
 * 
 * \param[out] event Event to store the data.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::getmouse(MEVENT& event)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::getmouse(&event);
}

/**
 * \brief Call ungetmouse.
 * 
 * \param event Event to store.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::ungetmouse(MEVENT& event)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::ungetmouse(&event);
}

/**
 * \brief Call mousemask.
 * 
 * \param newmask,oldmask Values to pass on to mousemask.
 * \pre %Ncurses mode is on.
 * \return The mask of availiable events.
 */
inline mmask_t Ncurses::mousemask(mmask_t newmask, mmask_t* oldmask)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::mousemask(newmask, oldmask);
}

/**
 * \brief Call mouseinterval.
 * 
 * \param erval Value to pass on to mouseinterval.
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::mouseinterval(int erval)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return ::mouseinterval(erval);
}

// Window

inline WINDOW* Ncurses::newwin_(int nlines, int ncols, int begin_y, int begin_x, Window::Key /*dummy*/)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return newwin(nlines, ncols, begin_y, begin_x);
}

// Color

/**
 * \brief Start ncurses color mode.
 * 
 * \pre %Ncurses mode is on.
 * \exception errors::ColorInit Thrown when colors can't be initialized.
 */
inline void Ncurses::start_color()
{
	assert(!is_exit_ && "Ncurses mode is off");
	if (colors_initialized_)
		return;
	if (::start_color() == ERR)
		throw errors::ColorInit{};
	colors_initialized_ = true;
}

/**
 * \brief Call use_default_colors.
 * 
 * \pre %Ncurses mode is on.
 * \return The result of the operation.
 */
inline int Ncurses::use_default_colors()
{
	assert(!is_exit_ && "Ncurses mode is off");
	start_color();
	return ::use_default_colors();
}

/**
 * \brief Get a pair number from a Color.
 * 
 * \param color The color to get.
 * \pre %Ncurses mode is on.
 * \exception errors::TooMuchColors Thrown if no more color pairs can be registered.
 * \return The pair number associated with the color.
 */
inline short Ncurses::color_to_pair_number(Color const& color)
{
	assert(!is_exit_ && "Ncurses mode is off");
	auto it = std::find_if(std::begin(registered_colors_), std::end(registered_colors_),
	                       [color](Color const& elem){return color == elem;});
	if (it != std::end(registered_colors_))
		return static_cast<short>(it - std::begin(registered_colors_) + 1);

	start_color();
	// Ensure push_back will not throw
	registered_colors_.reserve(registered_colors_.size() + 1);
	auto res = init_pair(static_cast<short>(registered_colors_.size() + 1),
	                     color.foreground, color.background);
	if (res == ERR)
		throw errors::TooMuchColors{color};
	registered_colors_.push_back(color);
	return static_cast<short>(registered_colors_.size());
}

/**
 * \brief Get an attribute character from a Color.
 * 
 * \param color The color to get.
 * \pre %Ncurses mode is on.
 * \exception errors::TooMuchColors Thrown if no more color pairs can be registered.
 * \return The attribute associated with the color.
 */
inline attr_t Ncurses::color_to_attr(Color const& color)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return static_cast<attr_t>(COLOR_PAIR(color_to_pair_number(color)));
}

/**
 * \brief Get a Color from a pair number.
 * 
 * \param pair_n The pair number.
 * \pre %Ncurses mode is on.
 * \pre *pair_n* is a valid pair number.
 * \return The color associated with the pair.
 */
inline Color Ncurses::pair_number_to_color(short pair_n)
{
	assert(!is_exit_ && "Ncurses mode is off");
	assert(static_cast<std::size_t>(pair_n) <= registered_colors_.size() && "No such color");
	return registered_colors_[static_cast<std::size_t>(pair_n - 1)];
}

/**
 * \brief Get a Color from an attribute.
 * 
 * \param a The attribute.
 * \pre %Ncurses mode is on.
 * \pre The color pair associated with *a* is a valid color attribute.
 * \return The color associated with the attribute.
 */
inline Color Ncurses::attr_to_color(attr_t a)
{
	assert(!is_exit_ && "Ncurses mode is off");
	return pair_number_to_color(static_cast<short>(PAIR_NUMBER(static_cast<int>(a))));
}

/**
 * \brief Call init_color.
 * 
 * \pre %Ncurses mode is on.
 * \param color,r,g,b Values to pass on to init_color.
 */
inline int Ncurses::init_color(short color, short r, short g, short b)
{
	assert(!is_exit_ && "Ncurses mode is off");
	start_color();
	return ::init_color(color, r, g, b);
}

inline void Ncurses::assign(WINDOW*)
{
	assert(false && "Can't call nccpp::Ncurses::assign");
}

inline void Ncurses::destroy()
{
	assert(false && "Can't call nccpp::Ncurses::destroy");
}


} // namespace nccpp

#endif // Header guard
