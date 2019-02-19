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
 * \file Window.hpp
 * \brief Header file for the Window class.
 */

#ifndef NCURSESCPP_WINDOW_HPP_
#define NCURSESCPP_WINDOW_HPP_

#include <string>
#include <vector>

#ifndef NCURSES_NOMACROS
#define NCURSES_NOMACROS
#endif

#include <ncurses.h>

namespace nccpp
{

/** \brief Alias used for input functions. */
using String = std::basic_string<chtype>;

struct Color;

class Ncurses;
class Subwindow;

/**
 * \brief Class managing a ncurses window.
 */
class Window
{
	public:
	explicit Window(WINDOW*);
	Window(int, int, int, int);

	Window(Window const&);
	Window& operator=(Window const&);

	Window(Window&&)
#ifdef NDEBUG
		noexcept
#endif
		;
	Window& operator=(Window&&)noexcept;

	/// \cond NODOC
	Window(Ncurses const&) = delete;
	Window& operator=(Ncurses const&) = delete;
	Window(Ncurses&&) = delete;
	Window& operator=(Ncurses&&) = delete;

	Window(Subwindow const&) = delete;
	Window& operator=(Subwindow const&) = delete;
	Window(Subwindow&&) = delete;
	Window& operator=(Subwindow&&) = delete;
	/// \endcond

	~Window();

	virtual void assign(WINDOW*);
	virtual void destroy();
	WINDOW* get_handle();
	WINDOW const* get_handle() const;

	std::size_t add_subwindow(int, int, int, int);
	Subwindow& get_subwindow(std::size_t);
	void delete_subwindow(std::size_t);

	// Input options

	int keypad(bool);
	int nodelay(bool);
	int notimeout(bool);
	void timeout(int);

	// Output options

	int clearok(bool);
	int setscrreg(int, int);

	// Input functions

	int getch();
	int mvgetch(int, int);

	int scanw(char const*, ...);
	int mvscanw(int, int, char const*, ...);

	int getstr(std::string&);
	int getnstr(std::string&, std::size_t);
	int mvgetstr(int, int, std::string&);
	int mvgetnstr(int, int, std::string&, std::size_t);

	chtype inch();
	chtype mvinch(int, int);

	int instr(std::string&);
	int innstr(std::string&, std::size_t);
	int mvinstr(int, int, std::string&);
	int mvinnstr(int, int, std::string&, std::size_t);

	int inchstr(String&);
	int inchnstr(String&, std::size_t);
	int mvinchstr(int, int, String&);
	int mvinchnstr(int, int, String&, std::size_t);

	// Output functions

	int addch(chtype const);
	int mvaddch(int, int, chtype const);
	int echochar(chtype const);

	int printw(char const*, ...);
	int mvprintw(int, int, char const*, ...);

	int addstr(std::string const&);
	int addnstr(std::string const&, std::size_t);
	int mvaddstr(int, int, std::string const&);
	int mvaddnstr(int, int, std::string const&, std::size_t);

	int addchstr(String const&);
	int addchnstr(String const&, std::size_t);
	int mvaddchstr(int, int, String const&);
	int mvaddchnstr(int, int, String const&, std::size_t);

	int insch(chtype);
	int mvinsch(int y, int x, chtype);

	int insstr(std::string const&);
	int insnstr(std::string const&, std::size_t);
	int mvinsstr(int, int, std::string const&);
	int mvinsnstr(int, int, std::string const&, std::size_t);

	// Deletion functions

	int delch();
	int mvdelch(int, int);

	int insdelln(int);

	// Border

	int border(chtype, chtype, chtype, chtype, chtype, chtype, chtype, chtype);
	int box(chtype, chtype);

	int hline(chtype, int);
	int vline(chtype, int);
	int mvhline(int, int, chtype, int);
	int mvvline(int, int, chtype, int);

	// Background

	void bkgdset(int);
	int bkgd(int);
	chtype getbkgd();

	// Attributes

	int attroff(int);
	int attron(int);
	int attrset(int);

	int attr_get(attr_t&);
	int color_get(Color&);

	int attr_color_get(attr_t&, Color&);

	int chgat(int, attr_t, Color);
	int mvchgat(int, int, int, attr_t, Color);

	// Misc

	int move(int, int);
	int mvwin(int, int);
	
	int erase();
	int clear();
	int clrtobot();
	int clrtoeol();

	int refresh();
	int outrefresh();
	int redraw();
	int redrawln(int, int);

	int scroll(int = 1);

	void get_yx(int&, int&);
	void get_begyx(int&, int&);
	void get_maxyx(int&, int&);

	int touchln(int, int, bool);

	bool enclose(int, int);
	bool coord_trafo(int&, int&, bool);

	protected:
	/// \cond NODOC
	struct Key{};

	WINDOW* win_;
	/// \endcond

#ifndef NDEBUG
	/// \cond NODOC
	WINDOW* win_save_;
	public:
	void invalidate_for_exit_(Key);
	void validate_for_resume_(Key);
	/// \endcond
#endif

	private:
	std::vector<Subwindow> subwindows_;
};

} // namespace nccpp

#ifndef NCCPP_WINDOW_NOIMPL
#include "Ncurses.hpp"
#include "Subwindow.hpp"

#include "Window.ipp"
#endif

#endif // Header guard
