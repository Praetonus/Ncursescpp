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
 * \file constants.hpp
 * \brief File declaring various ncurses constants
 */

#ifndef NCURSESCPP_CONSTANTS_HPP_
#define NCURSESCPP_CONSTANTS_HPP_

namespace nccpp
{

/**
 * \brief Attributes constants
 */
namespace attributes
{

extern int const normal;
extern int const standout;
extern int const underline;
extern int const reverse;
extern int const blink;
extern int const dim;
extern int const bold;
extern int const protect;
extern int const invis;
extern int const altcharset;
extern int const chartext;

} // namespace attributes

/// \cond nodoc
namespace internal
{

struct DefaultColor
{
	operator short const() const;
};

} // namespace internal
/// \endcond

/**
 * \brief Colors constants
 */
namespace colors
{

extern internal::DefaultColor const def;
extern short const black;
extern short const red;
extern short const green;
extern short const yellow;
extern short const blue;
extern short const magenta;
extern short const cyan;
extern short const white;

} // namespace colors

/// \cond NODOC
namespace internal
{

struct FunctionKeys
{
	int operator()(int) const;
};

}
/// \endcond

/**
 * \brief Keys constants
 */
namespace keys
{

extern int const break_k;
extern int const sreset;
extern int const reset;
extern int const down;
extern int const up;
extern int const left;
extern int const right;
extern int const home;
extern int const backspace;
extern internal::FunctionKeys const f;
extern int const dl;
extern int const il;
extern int const dc;
extern int const ic;
extern int const eic;
extern int const clear;
extern int const eos;
extern int const eol;
extern int const sf;
extern int const sr;
extern int const npage;
extern int const ppage;
extern int const stab;
extern int const ctab;
extern int const catab;
extern int const enter;
extern int const print;
extern int const ll;
extern int const a1;
extern int const a3;
extern int const b2;
extern int const c1;
extern int const c3;
extern int const btab;
extern int const beg;
extern int const cancel;
extern int const close;
extern int const command;
extern int const copy;
extern int const create;
extern int const end;
extern int const exit;
extern int const find;
extern int const help;
extern int const mark;
extern int const message;
extern int const move;
extern int const next;
extern int const open;
extern int const options;
extern int const previous;
extern int const redo;
extern int const reference;
extern int const refresh;
extern int const replace;
extern int const restart;
extern int const resume;
extern int const save;
extern int const sbeg;
extern int const scancel;
extern int const scommand;
extern int const scopy;
extern int const screate;
extern int const sdc;
extern int const sdl;
extern int const select;
extern int const send;
extern int const seol;
extern int const sexit;
extern int const sfind;
extern int const shelp;
extern int const shome;
extern int const sic;
extern int const sleft;
extern int const smessage;
extern int const smove;
extern int const snext;
extern int const soptions;
extern int const sprevious;
extern int const sprint;
extern int const sredo;
extern int const sreplace;
extern int const sright;
extern int const srsume;
extern int const ssave;
extern int const ssuspend;
extern int const sundo;
extern int const suspend;
extern int const undo;
extern int const mouse;
extern int const resize;
extern int const event;

} // namespace keys

} // namespace nccpp

#endif // Header guard
