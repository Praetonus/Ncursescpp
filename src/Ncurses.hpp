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

/**
 * \file Ncurses.hpp
 * \brief Header file for the Ncurses class.
 */

#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include <vector>

#include "Window.hpp"
#include "Color.hpp"

namespace nccpp
{

/**
 * \brief The primary interface class.
 * 
 * This class is used to access ncurses features.
 * It is responsible of the initialization of ncurses.
 */
class Ncurses : public Window
{
	friend Ncurses& ncurses();
	public:
	/// \cond NODOC
	Ncurses(Ncurses const&) = delete;
	Ncurses& operator=(Ncurses const&) = delete;

	Ncurses(Ncurses&&) = delete;
	Ncurses& operator=(Ncurses&&) = delete;

	~Ncurses();
	/// \endcond

	// Input options

	int cbreak(bool);
	int echo(bool);
	int halfdelay(int);
	int intrflush(bool);
	int meta(bool);
	int raw(bool);
	void qiflush(bool);
	int typeahead(int);

	// Output options

	int clearok(bool, bool = false);
	int idlok(bool);
	void idcok(bool);
	void immedok(bool);
	int leaveok(bool);
	int scrollok(bool);
	int nl(bool);

	// Input functions

	int ungetch(int);
	int has_key(int);

	// Misc

	int doupdate();
	int line_count();
	int column_count();

	// Window

	/// \cond NODOC
	WINDOW* newwin_(int, int, int, int, Window::Key);
	/// \endcond

	// Color

	void start_color();
	int use_default_colors();

	short color_to_pair_number(Color const&);
	int color_to_attr(Color const&);
	Color pair_number_to_color(short);
	Color attr_to_color(attr_t);

	int init_color(short, short, short, short);

	private:
	Ncurses();

	std::vector<Color> registered_colors_;
	bool colors_initialized;

	// Do not implement
	void assign(WINDOW*);
	WINDOW* release();
	void destroy();
};

/**
 * Access the Ncurses singleton.
 * 
 * \exception errors::NcursesInit Thrown when ncurses can't be initialized.
 * \return A reference to the singleton.
 */
Ncurses& ncurses();

} // namespace nccpp

#endif // Header guard
