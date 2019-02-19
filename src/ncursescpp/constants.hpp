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

#include "Ncurses.hpp"

#include <cassert>

namespace nccpp
{

/**
 * \brief Attributes constants
 */
namespace attributes
{

int constexpr normal{A_NORMAL};
int constexpr standout{A_STANDOUT};
int constexpr underline{A_UNDERLINE};
int constexpr reverse{A_REVERSE};
int constexpr blink{A_BLINK};
int constexpr dim{A_DIM};
int constexpr bold{A_BOLD};
int constexpr protect{A_PROTECT};
int constexpr invis{A_INVIS};
int constexpr altcharset{A_ALTCHARSET};
int constexpr chartext{A_CHARTEXT};

} // namespace attributes

/// \cond nodoc
namespace internal
{

struct DefaultColor
{
	operator short const() const
	{
		static bool init_done{false};
		if (!init_done)
		{
			ncurses().use_default_colors();
			init_done = true;
		}
		return -1;
	}
};

} // namespace internal
/// \endcond

/**
 * \brief Colors constants
 */
namespace colors
{

static internal::DefaultColor const def{};
short constexpr black{COLOR_BLACK};
short constexpr red{COLOR_RED};
short constexpr green{COLOR_GREEN};
short constexpr yellow{COLOR_YELLOW};
short constexpr blue{COLOR_BLUE};
short constexpr magenta{COLOR_MAGENTA};
short constexpr cyan{COLOR_CYAN};
short constexpr white{COLOR_WHITE};

} // namespace colors

/// \cond NODOC
namespace internal
{

struct FunctionKeys
{
	int operator()(int n) const
	{
		assert(n < 64 && "Function key doesn't exists");
		return KEY_F0 + n;
	}
};

}
/// \endcond

/**
 * \brief Keys constants
 */
namespace keys
{

int constexpr break_k{KEY_BREAK};
int constexpr sreset{KEY_SRESET};
int constexpr reset{KEY_RESET};
int constexpr down{KEY_DOWN};
int constexpr up{KEY_UP};
int constexpr left{KEY_LEFT};
int constexpr right{KEY_RIGHT};
int constexpr home{KEY_HOME};
int constexpr backspace{KEY_BACKSPACE};
static internal::FunctionKeys const f{};
int constexpr dl{KEY_DL};
int constexpr il{KEY_IL};
int constexpr dc{KEY_DC};
int constexpr ic{KEY_IC};
int constexpr eic{KEY_EIC};
int constexpr clear{KEY_CLEAR};
int constexpr eos{KEY_EOS};
int constexpr eol{KEY_EOL};
int constexpr sf{KEY_SF};
int constexpr sr{KEY_SR};
int constexpr npage{KEY_NPAGE};
int constexpr ppage{KEY_PPAGE};
int constexpr stab{KEY_STAB};
int constexpr ctab{KEY_CTAB};
int constexpr catab{KEY_CATAB};
int constexpr enter{KEY_ENTER};
int constexpr print{KEY_PRINT};
int constexpr ll{KEY_LL};
int constexpr a1{KEY_A1};
int constexpr a3{KEY_A3};
int constexpr b2{KEY_B2};
int constexpr c1{KEY_C1};
int constexpr c3{KEY_C3};
int constexpr btab{KEY_BTAB};
int constexpr beg{KEY_BEG};
int constexpr cancel{KEY_CANCEL};
int constexpr close{KEY_CLOSE};
int constexpr command{KEY_COMMAND};
int constexpr copy{KEY_COPY};
int constexpr create{KEY_CREATE};
int constexpr end{KEY_END};
int constexpr exit{KEY_EXIT};
int constexpr find{KEY_FIND};
int constexpr help{KEY_HELP};
int constexpr mark{KEY_MARK};
int constexpr message{KEY_MESSAGE};
int constexpr move{KEY_MOVE};
int constexpr next{KEY_NEXT};
int constexpr open{KEY_OPEN};
int constexpr options{KEY_OPTIONS};
int constexpr previous{KEY_PREVIOUS};
int constexpr redo{KEY_REDO};
int constexpr reference{KEY_REFERENCE};
int constexpr refresh{KEY_REFRESH};
int constexpr replace{KEY_REPLACE};
int constexpr restart{KEY_RESTART};
int constexpr resume{KEY_RESUME};
int constexpr save{KEY_SAVE};
int constexpr sbeg{KEY_SBEG};
int constexpr scancel{KEY_SCANCEL};
int constexpr scommand{KEY_SCOMMAND};
int constexpr scopy{KEY_SCOPY};
int constexpr screate{KEY_SCREATE};
int constexpr sdc{KEY_SDC};
int constexpr sdl{KEY_SDL};
int constexpr select{KEY_SELECT};
int constexpr send{KEY_SEND};
int constexpr seol{KEY_SEOL};
int constexpr sexit{KEY_SEXIT};
int constexpr sfind{KEY_SFIND};
int constexpr shelp{KEY_SHELP};
int constexpr shome{KEY_SHOME};
int constexpr sic{KEY_SIC};
int constexpr sleft{KEY_SLEFT};
int constexpr smessage{KEY_SMESSAGE};
int constexpr smove{KEY_SMOVE};
int constexpr snext{KEY_SNEXT};
int constexpr soptions{KEY_SOPTIONS};
int constexpr sprevious{KEY_SPREVIOUS};
int constexpr sprint{KEY_SPRINT};
int constexpr sredo{KEY_SREDO};
int constexpr sreplace{KEY_SREPLACE};
int constexpr sright{KEY_SRIGHT};
int constexpr srsume{KEY_SRSUME};
int constexpr ssave{KEY_SSAVE};
int constexpr ssuspend{KEY_SSUSPEND};
int constexpr sundo{KEY_SUNDO};
int constexpr suspend{KEY_SUSPEND};
int constexpr undo{KEY_UNDO};
int constexpr mouse{KEY_MOUSE};
int constexpr resize{KEY_RESIZE};
int constexpr event{KEY_EVENT};

} // namespace keys

/// \cond NODOC
namespace internal
{

struct ButtonRelease
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_RELEASE(event, button);
	}
};

struct ButtonPress
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_PRESS(event, button);
	}
};

struct ButtonClick
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_CLICK(event, button);
	}
};

struct ButtonDoubleClick
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_DOUBLE_CLICK(event, button);
	}
};

struct ButtonTripleClick
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_TRIPLE_CLICK(event, button);
	}
};

struct ButtonReserved
{
	mmask_t operator()(mmask_t event, unsigned char button) const
	{
		return BUTTON_RESERVED_EVENT(event, button);
	}
};

}
/// \endcond

/**
 * \brief Mouse constants
 */
namespace mouse
{

int constexpr button1_pressed{BUTTON1_PRESSED};
int constexpr button1_released{BUTTON1_RELEASED};
int constexpr button1_clicked{BUTTON1_CLICKED};
int constexpr button1_double_clicked{BUTTON1_DOUBLE_CLICKED};
int constexpr button1_triple_clicked{BUTTON1_TRIPLE_CLICKED};
int constexpr button2_pressed{BUTTON2_PRESSED};
int constexpr button2_released{BUTTON2_RELEASED};
int constexpr button2_clicked{BUTTON2_CLICKED};
int constexpr button2_double_clicked{BUTTON2_DOUBLE_CLICKED};
int constexpr button2_triple_clicked{BUTTON2_TRIPLE_CLICKED};
int constexpr button3_pressed{BUTTON3_PRESSED};
int constexpr button3_released{BUTTON3_RELEASED};
int constexpr button3_clicked{BUTTON3_CLICKED};
int constexpr button3_double_clicked{BUTTON3_DOUBLE_CLICKED};
int constexpr button3_triple_clicked{BUTTON3_TRIPLE_CLICKED};
int constexpr button4_pressed{BUTTON4_PRESSED};
int constexpr button4_released{BUTTON4_RELEASED};
int constexpr button4_clicked{BUTTON4_CLICKED};
int constexpr button4_double_clicked{BUTTON4_DOUBLE_CLICKED};
int constexpr button4_triple_clicked{BUTTON4_TRIPLE_CLICKED};
#if NCURSES_MOUSE_VERSION > 1
int constexpr button5_pressed{BUTTON5_PRESSED};
int constexpr button5_released{BUTTON5_RELEASED};
int constexpr button5_clicked{BUTTON5_CLICKED};
int constexpr button5_double_clicked{BUTTON5_DOUBLE_CLICKED};
int constexpr button5_triple_clicked{BUTTON5_TRIPLE_CLICKED};
#else
int constexpr button1_reserved_event{BUTTON1_RESERVED_EVENT};
int constexpr button2_reserved_event{BUTTON2_RESERVED_EVENT};
int constexpr button3_reserved_event{BUTTON3_RESERVED_EVENT};
int constexpr button4_reserved_event{BUTTON4_RESERVED_EVENT};
#endif
int constexpr button_ctrl{BUTTON_CTRL};
int constexpr button_shift{BUTTON_SHIFT};
int constexpr button_alt{BUTTON_ALT};
int constexpr report_mouse_position{REPORT_MOUSE_POSITION};
int constexpr all{ALL_MOUSE_EVENTS};

static internal::ButtonRelease const release{};
static internal::ButtonPress const press{};
static internal::ButtonClick const click{};
static internal::ButtonDoubleClick const double_click{};
static internal::ButtonTripleClick const triple_click{};
static internal::ButtonReserved const reserved_event{};

}

} // namespace nccpp

#endif // Header guard
