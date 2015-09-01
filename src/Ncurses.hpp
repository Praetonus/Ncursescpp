#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include "Window.hpp"

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
	int keypad(bool);
	int meta(bool);
	int nodelay(bool);
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

	private:
	Ncurses();

	// Do not implement
	void assign(WINDOW*);
	WINDOW* release();
	void destroy();
};

Ncurses& ncurses();

} // namespace nccpp

#endif // Header guard
