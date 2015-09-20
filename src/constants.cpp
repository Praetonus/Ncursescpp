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

#include "constants.hpp"

#include "Ncurses.hpp"

#include <cassert>

#include <ncurses.h>

namespace nccpp
{

namespace attributes
{

int const normal{A_NORMAL};
int const standout{A_STANDOUT};
int const underline{A_UNDERLINE};
int const reverse{A_REVERSE};
int const blink{A_BLINK};
int const dim{A_DIM};
int const bold{A_BOLD};
int const protect{A_PROTECT};
int const invis{A_INVIS};
int const altcharset{A_ALTCHARSET};
int const chartext{A_CHARTEXT};

} // namespace attributes

namespace internal
{

DefaultColor::operator const short() const
{
	static bool init_done{false};
	if (!init_done)
	{
		ncurses().use_default_colors();
		init_done = true;
	}
	return -1;
}

} // namespace internal

namespace colors
{

internal::DefaultColor const def{};
short const black{COLOR_BLACK};
short const red{COLOR_RED};
short const green{COLOR_GREEN};
short const yellow{COLOR_YELLOW};
short const blue{COLOR_BLUE};
short const magenta{COLOR_MAGENTA};
short const cyan{COLOR_CYAN};
short const white{COLOR_WHITE};

} // namespace colors

namespace internal
{

int FunctionKeys::operator()(int n) const
{
	assert(n < 64 && "Function key doesn't exists");
	return KEY_F0 + n;
}

} // namespace internal

namespace keys
{

int const break_k{KEY_BREAK};
int const sreset{KEY_SRESET};
int const reset{KEY_RESET};
int const down{KEY_DOWN};
int const up{KEY_UP};
int const left{KEY_LEFT};
int const right{KEY_RIGHT};
int const home{KEY_HOME};
int const backspace{KEY_BACKSPACE};
internal::FunctionKeys const f{};
int const dl{KEY_DL};
int const il{KEY_IL};
int const dc{KEY_DC};
int const ic{KEY_IC};
int const eic{KEY_EIC};
int const clear{KEY_CLEAR};
int const eos{KEY_EOS};
int const eol{KEY_EOL};
int const sf{KEY_SF};
int const sr{KEY_SR};
int const npage{KEY_NPAGE};
int const ppage{KEY_PPAGE};
int const stab{KEY_STAB};
int const ctab{KEY_CTAB};
int const catab{KEY_CATAB};
int const enter{KEY_ENTER};
int const print{KEY_PRINT};
int const ll{KEY_LL};
int const a1{KEY_A1};
int const a3{KEY_A3};
int const b2{KEY_B2};
int const c1{KEY_C1};
int const c3{KEY_C3};
int const btab{KEY_BTAB};
int const beg{KEY_BEG};
int const cancel{KEY_CANCEL};
int const close{KEY_CLOSE};
int const command{KEY_COMMAND};
int const copy{KEY_COPY};
int const create{KEY_CREATE};
int const end{KEY_END};
int const exit{KEY_EXIT};
int const find{KEY_FIND};
int const help{KEY_HELP};
int const mark{KEY_MARK};
int const message{KEY_MESSAGE};
int const move{KEY_MOVE};
int const next{KEY_NEXT};
int const open{KEY_OPEN};
int const options{KEY_OPTIONS};
int const previous{KEY_PREVIOUS};
int const redo{KEY_REDO};
int const reference{KEY_REFERENCE};
int const refresh{KEY_REFRESH};
int const replace{KEY_REPLACE};
int const restart{KEY_RESTART};
int const resume{KEY_RESUME};
int const save{KEY_SAVE};
int const sbeg{KEY_SBEG};
int const scancel{KEY_SCANCEL};
int const scommand{KEY_SCOMMAND};
int const scopy{KEY_SCOPY};
int const screate{KEY_SCREATE};
int const sdc{KEY_SDC};
int const sdl{KEY_SDL};
int const select{KEY_SELECT};
int const send{KEY_SEND};
int const seol{KEY_SEOL};
int const sexit{KEY_SEXIT};
int const sfind{KEY_SFIND};
int const shelp{KEY_SHELP};
int const shome{KEY_SHOME};
int const sic{KEY_SIC};
int const sleft{KEY_SLEFT};
int const smessage{KEY_SMESSAGE};
int const smove{KEY_SMOVE};
int const snext{KEY_SNEXT};
int const soptions{KEY_SOPTIONS};
int const sprevious{KEY_SPREVIOUS};
int const sprint{KEY_SPRINT};
int const sredo{KEY_SREDO};
int const sreplace{KEY_SREPLACE};
int const sright{KEY_SRIGHT};
int const srsume{KEY_SRSUME};
int const ssave{KEY_SSAVE};
int const ssuspend{KEY_SSUSPEND};
int const sundo{KEY_SUNDO};
int const suspend{KEY_SUSPEND};
int const undo{KEY_UNDO};
int const mouse{KEY_MOUSE};
int const resize{KEY_RESIZE};
int const event{KEY_EVENT};

} // namespace keys

} // namespace nccpp
