#include "constants.hpp"

#include "Ncurses.hpp"

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

} // namespace nccpp
