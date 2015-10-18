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
 * \file errors.hpp
 * \brief Header file for exceptions classes.
 */

#ifndef NCURSESCPP_ERRORS_HPP_
#define NCURSESCPP_ERRORS_HPP_

#include <exception>

#include "Color.hpp"

namespace nccpp
{

/**
 * \brief Namespace for exceptions classes.
 */
namespace errors
{

/**
 * \brief %Base ncursescpp exception class.
 */
class Base : public std::exception
{
	public:
	Base() noexcept = default;

	Base(Base const&) noexcept = default;
	Base& operator=(Base const&) noexcept = default;

	virtual ~Base() = default;

	char const* what() const noexcept override
	{
		return "nccpp::errors::Base";
	}
};

/**
 * \brief Thrown when ncurses can't be initialized.
 */
class NcursesInit : public Base
{
	public:
	NcursesInit() noexcept = default;

	NcursesInit(NcursesInit const&) noexcept = default;
	NcursesInit& operator=(NcursesInit const&) noexcept = default;

	virtual ~NcursesInit() = default;

	char const* what() const noexcept override
	{
		return "nccpp::errors::NcursesInit : Can't initialize ncuses, initscr() failed";
	}
};

/**
 * \brief Thrown when window creation fails.
 */
class WindowInit : public Base
{
	public:
	WindowInit() noexcept = default;

	WindowInit(WindowInit const&) noexcept = default;
	WindowInit& operator=(WindowInit const&) noexcept = default;

	virtual ~WindowInit() = default;

	char const* what() const noexcept override
	{
		return "nccpp::errors::WindowInit : Can't create new window, newwin() failed";
	}
};

/**
 * \brief Thrown when color mode can't be initialized.
 */
class ColorInit : public Base
{
	public:
	ColorInit() noexcept = default;

	ColorInit(ColorInit const&) noexcept = default;
	ColorInit& operator=(ColorInit const&) noexcept = default;

	virtual ~ColorInit() = default;

	char const* what() const noexcept override
	{
		return "nccpp::errors::ColorInit : Can't initialize colors, start_color() failed";
	}
};

/**
 * \brief Thrown when no more color pairs can be registered.
 */
class TooMuchColors : public Base
{
	public:
	TooMuchColors(Color const& c) noexcept
		: color{c}
	{}

	TooMuchColors(TooMuchColors const&) noexcept = default;
	TooMuchColors& operator=(TooMuchColors const&) noexcept = default;

	virtual ~TooMuchColors() = default;

	char const* what() const noexcept override
	{
		return "nccpp::errors::TooMuchColors : Can't initialize new colors, init_pair failed";
	}

	Color const color; ///< The color that caused the error.
};

} // namespace errors

} // namespace nccpp

#endif // Header guard
