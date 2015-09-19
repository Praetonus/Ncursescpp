#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include <vector>

#include "Window.hpp"
#include "Color.hpp"

namespace nccpp
{

class Ncurses : public Window
{
	friend Ncurses& ncurses();
	public:
	Ncurses(Ncurses const&) = delete;
	Ncurses& operator=(Ncurses const&) = delete;

	Ncurses(Ncurses&&) = delete;
	Ncurses& operator=(Ncurses&&) = delete;

	~Ncurses();

	// Input options

	int cbreak(bool);
	int echo(bool);
	int halfdelay(int);
	int intrflush(bool);
	int meta(bool);
	int raw(bool);
	void qiflush(bool);
	int typeahead(int);

	// Output options

	int clearok(bool, bool = false);
	int idlok(bool);
	void idcok(bool);
	void immedok(bool);
	int leaveok(bool);
	int scrollok(bool);
	int nl(bool);

	// Input functions

	int ungetch(int);
	int has_key(int);

	// Misc

	int doupdate();
	int line_count();
	int column_count();

	// Window

	WINDOW* newwin_(int, int, int, int, Window::Key);

	// Color

	void start_color();
	int use_default_colors();

	short color_to_pair_number(Color const&);
	int color_to_attr(Color const&);
	Color pair_number_to_color(short);
	Color attr_to_color(attr_t);

	int init_color(short, short, short, short);

	private:
	Ncurses();

	std::vector<Color> registered_colors_;
	bool colors_initialized;

	// Do not implement
	void assign(WINDOW*);
	WINDOW* release();
	void destroy();
};

Ncurses& ncurses();

} // namespace nccpp

#endif // Header guard
