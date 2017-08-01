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

#ifndef NCURSESCPP_SUBWINDOW_IPP_
#define NCURSESCPP_SUBWINDOW_IPP_

#include <cassert>

namespace nccpp
{

/**
 * \brief Get the parent of the subwindow.
 * 
 * \pre The Subwindow manages a ncurses window.
 * \return A reference to the parent.
 */
inline Window& Subwindow::get_parent()
{
	assert(win_ && "Invalid subwindow");
	return parent_;
}

/**
 * \brief Call mvderwin for this subwindow.
 * 
 * \param y,x Values to pass on to mvderwin.
 * \pre The Subwindow manages a ncurses window.
 * \return The result of the operation.
 */
inline int Subwindow::mvderwin(int y, int x)
{
	assert(win_ && "Invalid subwindow");
	return ::mvderwin(win_, y, x);
}

/**
 * \brief Call wsyncup for this subwindow.
 * 
 * \pre The Subwindow manages a ncurses window.
 */
inline void Subwindow::syncup()
{
	assert(win_ && "Invalid subwindow");
	wsyncup(win_);
}

/**
 * \brief Call syncok for this subwindow.
 * 
 * \param on Value to pass on to syncok.
 * \pre The Subwindow manages a ncurses window.
 */
inline int Subwindow::syncok(bool on)
{
	assert(win_ && "Invalid subwindow");
	return ::syncok(win_, on);
}

/**
 * \brief Call wcursyncup for this subwindow.
 * 
 * \pre The Subwindow manages a ncurses window.
 */
inline void Subwindow::cursyncup()
{
	assert(win_ && "Invalid subwindow");
	wcursyncup(win_);
}

/**
 * \brief Call wsyncdown for this subwindow.
 * 
 * \pre The Subwindow manages a ncurses window.
 */
inline void Subwindow::syncdown()
{
	assert(win_ && "Invalid subwindow");
	wsyncdown(win_);
}

inline void Subwindow::assign(WINDOW*)
{
	assert(false && "Can't call nccpp::Subwindow::assign");
}

inline void Subwindow::destroy()
{
	assert(false && "Can't call nccpp::Subwindow::destroy");
}

} // namespace nccpp

#endif // Header guard
