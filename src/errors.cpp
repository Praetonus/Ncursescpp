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

#include "errors.hpp"

namespace nccpp
{

char const* BaseError::what() const noexcept
{
	return "nccpp::BaseError";
}

char const* NcursesInitError::what() const noexcept
{
	return "nccpp::NcursesInitError : Can't initialize ncuses, initscr() failed";
}

char const* WindowInitError::what() const noexcept
{
	return "nccpp::WindowInitError : Can't create new window, newwin() failed";
}

char const* ColorInitError::what() const noexcept
{
	return "nccpp::ColorInitError : Can't initialize colors, start_color() failed";
}

TooMuchColors::TooMuchColors(Color const& c) noexcept
	: color{c}
{}

char const* TooMuchColors::what() const noexcept
{
	return "nccpp::TooMuchColors : Can't initialize new colors, init_pair failed";
}

NoSuchColor::NoSuchColor(int pa, bool ip) noexcept
	: pair_or_attr{pa}, is_pair_error{ip}
{}

char const* NoSuchColor::what() const noexcept
{
	return "nccpp::NoSuchColor : Color is uninitialized";
}

} // namespace nccpp
