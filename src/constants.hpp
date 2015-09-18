#ifndef NCURSESCPP_CONSTANTS_HPP_
#define NCURSESCPP_CONSTANTS_HPP_

namespace nccpp
{

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

namespace internal
{

struct DefaultColor
{
	operator short const() const;
};

} // namespace internal

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

} // namespace nccpp

#endif // Header guard
