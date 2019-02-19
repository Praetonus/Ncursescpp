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

#ifndef NCURSESCPP_WINDOW_IPP_
#define NCURSESCPP_WINDOW_IPP_

#include <cassert>

namespace nccpp
{
	
/**
 * \brief Take ownership of an existing ncurses window.
 * 
 * \param win The ncurses window. If win is nullptr, the Window created doesn't manage anything.
 */
inline Window::Window(WINDOW* win)
	: win_{win},
#ifndef NDEBUG
	  win_save_{nullptr},
#endif
	  subwindows_{}
{
#ifndef NDEBUG
	if (win_ != stdscr)
		ncurses().register_window_(*this, Key{});
#endif
}

/**
 * \brief Create a new ncurses window.
 * 
 * \param nlines Height of the window.
 * \param ncols Width of the window.
 * \param begin_y y position of the window.
 * \param begin_x x position of the window.
 * \pre %Ncurses mode is on.
 * \exception errors::WindowInit Thrown if the window can't be created.
 */
inline Window::Window(int nlines, int ncols, int begin_y, int begin_x)
	: win_{ncurses().newwin_(nlines, ncols, begin_y, begin_x, Key{})},
#ifndef NDEBUG
	  win_save_{nullptr},
#endif
	  subwindows_{}
{
	if (!win_)
		throw errors::WindowInit{};
#ifndef NDEBUG
	try
	{
		ncurses().register_window_(*this, Key{});
	}
	catch (...)
	{
		delwin(win_);
		throw;
	}
#endif
}

/**
 * \brief Copy constructor.
 * 
 * Subwindows are not copied.
 * 
 * \pre %Ncurses mode is on.
 * \exception errors::WindowInit Thrown if the window can't be duplicated.
 */
inline Window::Window(Window const& cp)
	: win_{nullptr},
#ifndef NDEBUG
	  win_save_{nullptr},
#endif
	  subwindows_{}
{
	assert(!cp.win_save_ && "Can't duplicate windows while ncurses mode is off");
	subwindows_.reserve(cp.subwindows_.size());
	if (cp.win_ && !(win_ = dupwin(cp.win_)))
		throw errors::WindowInit{};
#ifndef NDEBUG
	try
	{
		ncurses().register_window_(*this, Key{});
	}
	catch (...)
	{
		delwin(win_);
		throw;
	}
#endif
}

/**
 * \brief Copy assignment operator.
 * 
 * Subwindows are not copied.
 * 
 * \pre %Ncurses mode is on.
 * \exception errors::WindowInit Thrown if the window can't be duplicated.
 * If this occurs, the object is left unchanged.
 */
inline Window& Window::operator=(Window const& cp)
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
inline Window::Window(Window&& mv)
#ifdef NDEBUG
	noexcept
#endif
	: win_{mv.win_},
#ifndef NDEBUG
	  win_save_{mv.win_save_},
#endif
	  subwindows_{std::move(mv.subwindows_)}
{
	mv.win_ = nullptr;
#ifndef NDEBUG
	mv.win_save_ = nullptr;
	ncurses().register_window_(*this, Key{});
#endif
}

/**
 * \brief Move assignment operator.
 */
inline Window& Window::operator=(Window&& mv) noexcept
{
	if (this != &mv)
	{
		destroy();
		win_ = mv.win_;
		mv.win_ = nullptr;
#ifndef NDEBUG
		win_save_ = mv.win_save_;
		mv.win_save_ = nullptr;
#endif
		subwindows_ = std::move(mv.subwindows_);
	}
	return *this;
}

/**
 * \brief Destroy the managed ncurses window, if present.
 */
inline Window::~Window()
{
#ifndef NDEBUG
	if (this != &ncurses())
		ncurses().unregister_window_(*this, Key{});
#endif
	destroy();
}

/**
 * \brief Take ownership of a new ncurses window.
 * 
 * If there already is a managed window, destroy it.
 * 
 * \param new_win The new window.
 * \pre %Ncurses mode is on.
 */
inline void Window::assign(WINDOW* new_win)
{
	assert(!win_save_ && "Can't modify window while ncurses mode is off");
	if (win_)
		destroy();
	win_ = new_win;
}

/**
 * \brief Destroy the managed ncurses window, if present.
 */
inline void Window::destroy()
{
	if (win_)
	{
		subwindows_.clear();
		delwin(win_);
		win_ = nullptr;
	}
#ifndef NDEBUG
	else if (win_save_)
	{
		subwindows_.clear();
		delwin(win_save_);
		win_save_ = nullptr;
	}
#endif
}

/**
 * \brief Get the managed window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The managed window.
 */
inline WINDOW* Window::get_handle()
{
	assert(win_ && "Window doesn't manage any object");
	return win_;
}

/**
 * \brief Get the managed window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The managed window.
 */
inline WINDOW const* Window::get_handle() const
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
inline std::size_t Window::add_subwindow(int lines, int cols, int beg_y, int beg_x)
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
inline Subwindow& Window::get_subwindow(std::size_t index)
{
	assert(win_ && "Window doesn't manage any object");
	assert(index < subwindows_.size() && subwindows_[index].win_ && "Invalid subwindow");
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
inline void Window::delete_subwindow(std::size_t index)
{
	assert(win_ && "Window doesn't manage any object");
	assert(index < subwindows_.size() && subwindows_[index].win_ && "Invalid subwindow");
	subwindows_[index].~Subwindow();
	new (&subwindows_[index]) Subwindow{*this, nullptr, Key{}};
}

#ifndef NDEBUG
inline void Window::invalidate_for_exit_(Window::Key /*dummy*/)
{
	for (auto& elem : subwindows_)
		elem.invalidate_for_exit_(Key{});
	win_save_ = win_;
	win_ = nullptr;
}

inline void Window::validate_for_resume_(Window::Key /*dummy*/)
{
	for (auto& elem : subwindows_)
		elem.validate_for_resume_(Key{});
	win_ = win_save_;
	win_save_ = nullptr;
}
#endif

/**
 * \brief Call overlay for *src* and *dst*.
 * 
 * \param src,dst Values to pass on to overlay.
 * \return The result of the operation.
 */
inline int overlay(Window const& src, Window& dst)
{
	return ::overlay(src.get_handle(), dst.get_handle());
}

/**
 * \brief Call overwrite for *src* and *dst*.
 * 
 * \param src,dst Values to pass on to overwrite.
 * \return The result of the operation.
 */
inline int overwrite(Window const& src, Window& dst)
{
	return ::overwrite(src.get_handle(), dst.get_handle());
}

/**
 * \brief Call copywin for *src* and *dst*.
 * 
 * \param src,dst,sminrow,smincol,dminrow,dmincol,dmaxrow,dmaxcol,overlay Values to pass on to copywin.
 * \return The result of the operation.
 */
inline int copywin(Window const& src, Window& dst,
                   int sminrow, int smincol, int dminrow, int dmincol, int dmaxrow, int dmaxcol,
                   bool overlay)
{
	return ::copywin(src.get_handle(), dst.get_handle(),
	                 sminrow, smincol, dminrow, dmincol, dmaxrow, dmaxcol, overlay);
}

} // namespace nccpp

#include "Window_appearance.ipp"
#include "Window_attributes.ipp"
#include "Window_input.ipp"
#include "Window_misc.ipp"
#include "Window_options.ipp"
#include "Window_output.ipp"

#endif // Header guard
