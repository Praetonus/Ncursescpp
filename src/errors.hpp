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

#ifndef NCURSESCPP_ERROR_HPP_
#define NCURSESCPP_ERROR_HPP_

#include <exception>

#include "Color.hpp"

namespace nccpp
{

class BaseError : public std::exception
{
	public:
	BaseError() noexcept = default;

	BaseError(BaseError const&) noexcept = default;
	BaseError& operator=(BaseError const&) noexcept = default;

	virtual ~BaseError() = default;

	char const* what() const noexcept override;
};

class NcursesInitError : public BaseError
{
	public:
	NcursesInitError() noexcept = default;

	NcursesInitError(NcursesInitError const&) noexcept = default;
	NcursesInitError& operator=(NcursesInitError const&) noexcept = default;

	virtual ~NcursesInitError() = default;

	char const* what() const noexcept override;
};

class WindowInitError : public BaseError
{
	public:
	WindowInitError() noexcept = default;

	WindowInitError(WindowInitError const&) noexcept = default;
	WindowInitError& operator=(WindowInitError const&) noexcept = default;

	virtual ~WindowInitError() = default;

	char const* what() const noexcept override;
};

class ColorInitError : public BaseError
{
	public:
	ColorInitError() noexcept = default;

	ColorInitError(ColorInitError const&) noexcept = default;
	ColorInitError& operator=(ColorInitError const&) noexcept = default;

	virtual ~ColorInitError() = default;

	char const* what() const noexcept override;
};

class TooMuchColors : public BaseError
{
	public:
	TooMuchColors(Color const&) noexcept;

	TooMuchColors(TooMuchColors const&) noexcept = default;
	TooMuchColors& operator=(TooMuchColors const&) noexcept = default;

	virtual ~TooMuchColors() = default;

	char const* what() const noexcept override;

	Color const color;
};

class NoSuchColor : public BaseError
{
	public:
	NoSuchColor(int, bool) noexcept;

	NoSuchColor(NoSuchColor const&) noexcept = default;
	NoSuchColor& operator=(NoSuchColor const&) noexcept = default;

	virtual ~NoSuchColor() = default;

	char const* what() const noexcept override;

	int pair_or_attr;
	bool is_pair_error;
};

} // namespace nccpp

#endif // Header guard
