#include "constants.hpp"

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

} // namespace nccpp
