#ifndef NCURSESCPP_COLOR_HPP_
#define NCURSESCPP_COLOR_HPP_

namespace nccpp
{

struct Color
{
	Color() : Color{-1, -1} {}
	Color(short f, short b) : foreground{f}, background{b} {}

	short foreground;
	short background;
};

inline bool operator==(nccpp::Color const& lhs, nccpp::Color const& rhs)
{
	return (lhs.foreground == rhs.foreground) && (lhs.background == rhs.background);
}

inline bool operator!=(nccpp::Color const& lhs, nccpp::Color const& rhs)
{
	return !(lhs == rhs);
}

} // namespace nccpp


#endif //Header guard
