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
 * \file Color.hpp
 * \brief Header file for the Color class.
 */

#ifndef NCURSESCPP_COLOR_HPP_
#define NCURSESCPP_COLOR_HPP_

namespace nccpp
{

/**
 * \brief Class representing a ncurses color pair.
 */
struct Color
{
	Color() : Color{-1, -1} {}
	Color(short f, short b) : foreground{f}, background{b} {}

	short foreground; ///< Foreground color.
	short background; ///< Background color.
};

inline bool operator==(nccpp::Color const& lhs, nccpp::Color const& rhs)
{
	return (lhs.foreground == rhs.foreground) && (lhs.background == rhs.background);
}

inline bool operator!=(nccpp::Color const& lhs, nccpp::Color const& rhs)
{
	return !(lhs == rhs);
}

} // namespace nccpp


#endif //Header guard
