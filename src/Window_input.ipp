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

#ifndef NCURSESCPP_WINDOW_INPUT_IPP_
#define NCURSESCPP_WINDOW_INPUT_IPP_

namespace nccpp
{

// getch

/**
 * \brief Call wgetch for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::getch()
{
	assert(win_ && "Window doesn't manage any object");
	return wgetch(win_);
}

/**
 * \brief Call mvwgetch for this window.
 *
 * \param y,x Values to pass on to mvwgetch.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvgetch(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwgetch(win_, y, x);
}

// scanw

/**
 * \brief Call wscanw for this window.
 * 
 * \param fmt Value to pass on to wscanw.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::scanw(char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(win_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

/**
 * \brief Call mvwscanw for this window.
 * 
 * \param y,x,fmt Values to pass on to mvwscanw.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvscanw(int y, int x, char const* fmt, ...)
{
	assert(win_ && "Window doesn't manage any object");
	if ((this->move)(y, x) == ERR)
		return ERR;
	va_list args;
	va_start(args, fmt);
	auto ret = vw_scanw(win_, const_cast<char*>(fmt), args);
	va_end(args);
	return ret;
}

// getstr

/**
 * \brief Call wgetnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::getstr(std::string& str)
{
	return (this->getnstr)(str, str.size());
}

/**
 * \brief Call wgetnstr for this window.
 * 
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::getnstr(std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return wgetnstr(win_, &str[0], static_cast<int>(n));
}

/**
 * \brief Call mvwgetnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvgetstr(int y, int x, std::string& str)
{
	return (this->mvgetnstr)(y, x, str, str.size());
}

/**
 * \brief Call mvwgetnstr for this window.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvgetnstr(int y, int x, std::string& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->getnstr)(str, n);
}

// inch

/**
 * \brief Call winch for this window.
 * 
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline chtype Window::inch()
{
	assert(win_ && "Window doesn't manage any object");
	return winch(win_);
}

/**
 * \brief Call mvwinch for this window.
 * 
 * \param y,x New position.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline chtype Window::mvinch(int y, int x)
{
	assert(win_ && "Window doesn't manage any object");
	return mvwinch(win_, y, x);
}

// instr

/**
 * \brief Call winnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::instr(std::string& str)
{
	return (this->innstr)(str, str.size());
}

/**
 * \brief Call winnstr for this window.
 * 
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::innstr(std::string& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return winnstr(win_, &str[0], static_cast<int>(n));
}

/**
 * \brief Call mvwinnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvinstr(int y, int x, std::string& str)
{
	return (this->mvinnstr)(y, x, str, str.size());
}

/**
 * \brief Call mvwinnstr for this window.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvinnstr(int y, int x, std::string& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->innstr)(str, n);
}

// inchstr

/**
 * \brief Call winchnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::inchstr(String& str)
{
	return (this->inchnstr)(str, str.size());
}

/**
 * \brief Call winchnstr for this window.
 * 
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::inchnstr(String& str, std::size_t n)
{
	assert(win_ && "Window doesn't manage any object");
	str.resize(n);
	return winchnstr(win_, &str[0], static_cast<int>(n));
}

/**
 * \brief Call mvwinchnstr for this window.
 * 
 * The function reads at most str.size() characters.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvinchstr(int y, int x, String& str)
{
	return (this->mvinchnstr)(y, x, str, str.size());
}

/**
 * \brief Call mvwinchnstr for this window.
 * 
 * \param y,x New position.
 * \param[out] str The resulting string.
 * \param n Number of characters to read.
 * \pre The Window manages a ncurses window.
 * \return The result of the operation.
 */
inline int Window::mvinchnstr(int y, int x, String& str, std::size_t n)
{
	return (this->move)(y, x) == ERR ? ERR : (this->inchnstr)(str, n);
}

} // namespace nccpp

#endif // Header guard
