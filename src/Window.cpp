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

/**
 * \file Window.cpp
 * \brief Implementation file for the Window class.
 */

#include "Window.hpp"
#include "Subwindow.hpp"
#include "Ncurses.hpp"

#include <cassert>

#include "errors.hpp"

namespace nccpp
{

/**
 * \brief Take ownership of an existing ncurses window.
 * 
 * \param win The ncurses window. If win is nullptr, the Window created doesn't manage anything.
 */
Window::Window(WINDOW* win)
	: win_{win}, subwindows_{}
{}

/**
 * \brief Create a new ncurses window.
 * 
 * \param nlines Height of the window.
 * \param ncols Width of the window.
 * \param begin_y y position of the window.
 * \param begin_x x position of the window.
 * \exception errors::WindowInit Thrown if the window can't be created.
 */
Window::Window(int nlines, int ncols, int begin_y, int begin_x)
	: win_{ncurses().newwin_(nlines, ncols, begin_y, begin_x, Key{})},
	  subwindows_{}
{
	if (!win_)
		throw errors::WindowInit{};
}

/**
 * \brief Copy constructor.
 * 
 * \exception errors::WindowInit Thrown if the window can't be duplicated.
 */
Window::Window(Window const& cp)
	: win_{nullptr}, subwindows_{}
{
	if (cp.win_ && !(win_ = dupwin(cp.win_)))
		throw errors::WindowInit{};
	for (auto& subw : cp.subwindows_)
	{
		auto tmp = dupwin(subw.win_);
		if (!tmp)
			throw errors::WindowInit{};
		subwindows_.emplace_back(*this, tmp, Key{});
	}
}

/**
 * \brief Copy assignment operator.
 * 
 * \exception errors::WindowInit Thrown if the window can't be duplicated.
 * If this occurs, the object is left unchanged.
 */
Window& Window::operator=(Window const& cp)
{
	if (this != &cp)
	{
		Window tmp{cp};
		*this = std::move(tmp);
	}
	return *this;
}

/**
 * \brief Move constructor.
 */
Window::Window(Window&& mv) noexcept
	: win_{mv.win_}, subwindows_{std::move(mv.subwindows_)}
{
	mv.win_ = nullptr;
}

/**
 * \brief Move assignment operator.
 */
Window& Window::operator=(Window&& mv) noexcept
{
	if (this != &mv)
	{
		destroy();
		win_ = mv.win_;
		subwindows_ = std::move(mv.subwindows_);
		mv.win_ = nullptr;
	}
	return *this;
}

/**
 * \brief Destroy the managed ncurses window, if present.
 */
Window::~Window()
{
	destroy();
}

/**
 * \brief Take ownership of a new ncurses window.
 * 
 * If there already is a managed window, destroy it.
 * 
 * \param new_win The new window.
 */
void Window::assign(WINDOW* new_win)
{
	if (win_)
		destroy();
	win_ = new_win;
}

/**
 * \brief Destroy the managed ncurses window, if present.
 */
void Window::destroy()
{
	if (win_)
	{
		subwindows_.clear();
		delwin(win_);
		win_ = nullptr;
	}
}

/**
 * \brief Get the managed window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The managed window.
 */
WINDOW* Window::get_handle()
{
	assert(win_ && "Window doesn't manage any object");
	return win_;
}

/**
 * \brief Create a new subwindow.
 * 
 * \param lines,cols,beg_y,beg_x Values to pass on to subwin.
 * \pre The Window manages a ncurses window.
 * \pre The function parameters are valid subwindow coodinates.
 * \exception errors::WindowInit Thrown if the subwindow can't be created.
 * \return The subwindow index.
 */
std::size_t Window::add_subwindow(int lines, int cols, int beg_y, int beg_x)
{
	assert(win_ && "Window doesn't manage any object");
#ifndef NDEBUG
	int posx = 0, posy = 0, maxx = 0, maxy = 0;
	get_begyx(posy, posx);
	get_maxyx(maxy, maxx);
	maxy += posy; maxx += posx;
#endif
	assert(posy <= beg_y && posx <= beg_x && maxy >= beg_y + lines && maxx >= beg_x + cols &&
	       "Invalid subwindow coordinates");
	auto new_subw = subwin(win_, lines, cols, beg_y, beg_x);
	if (!new_subw)
		throw errors::WindowInit{};
	try
	{
		subwindows_.emplace_back(*this, new_subw, Window::Key{});
	}
	catch (...)
	{
		delwin(new_subw);
		throw;
	}
	return subwindows_.size() - 1;
}

/**
 * \brief Get an existing subwindow.
 * 
 * \param index Index of the subwindow.
 * \pre The Window manages a ncurses window.
 * \pre *index* is a valid subwindow index.
 * \return The subwindow.
 */
Subwindow& Window::get_subwindow(std::size_t index)
{
	assert(win_ && "Window doesn't manage any object");
	assert(index < subwindows_.size() && subwindows_[index].get_handle() && "Invalid subwindow");
	return subwindows_[index];
}

/**
 * \brief Destroy a subwindow.
 * 
 * References obtained by calling get_subwindow(index) shouldn't be used after calling this function.
 * References to other subwindows are not invalidated.
 * 
 * \param index Index of the subwindow.
 * \pre The Window manages a ncurses window.
 * \pre *index* is a valid subwindow index.
 */
void Window::delete_subwindow(std::size_t index)
{
	assert(win_ && "Window doesn't manage any object");
	assert(index < subwindows_.size() && subwindows_[index].get_handle() && "Invalid subwindow");
	subwindows_[index].destroy();
}

} // namespace nccpp
