#ifndef NCURSESCPP_WINDOW_HPP_
#define NCURSESCPP_WINDOW_HPP_

#include <string>

struct _win_st;
using WINDOW = _win_st;
using chtype =  unsigned int;
using attr_t = chtype;

namespace nccpp
{

using String = std::basic_string<chtype>;

struct Color;

class Window
{
	public:
	explicit Window(WINDOW*);
	Window(int, int, int, int);

	Window(Window const&) = delete;
	Window& operator=(Window const&) = delete;

	Window(Window&&) noexcept;
	Window& operator=(Window&&) noexcept;

	~Window();

	void assign(WINDOW*);
	void destroy();
	WINDOW* get_handle();

	// Input options

	int notimeout(bool);
	void timeout(int);

	// Output options

	int clearok(bool);
	int setscrreg(int, int);

	// Input functions

	int getch();
	int mvgetch(int, int);

	int scanw(char const*, ...);
	int mvscanw(int, int, char const*, ...);

	int getstr(std::string&);
	int getnstr(std::string&, std::size_t);
	int mvgetstr(int, int, std::string&);
	int mvgetnstr(int, int, std::string&, std::size_t);

	chtype inch();
	chtype mvinch(int, int);

	int instr(std::string&);
	int innstr(std::string&, std::size_t);
	int mvinstr(int, int, std::string&);
	int mvinnstr(int, int, std::string&, std::size_t);

	int inchstr(String&);
	int inchnstr(String&, std::size_t);
	int mvinchstr(int, int, String&);
	int mvinchnstr(int, int, String&, std::size_t);

	// Output functions

	int addch(chtype const);
	int mvaddch(int, int, chtype const);
	int echochar(chtype const);

	int printw(char const*, ...);
	int mvprintw(int, int, char const*, ...);

	int addstr(std::string const&);
	int addnstr(std::string const&, std::size_t);
	int mvaddstr(int, int, std::string const&);
	int mvaddnstr(int, int, std::string const&, std::size_t);

	int addchstr(String const&);
	int addchnstr(String const&, std::size_t);
	int mvaddchstr(int, int, String const&);
	int mvaddchnstr(int, int, String const&, std::size_t);

	int insch(chtype);
	int mvinsch(int y, int x, chtype);

	int insstr(std::string const&);
	int insnstr(std::string const&, std::size_t);
	int mvinsstr(int, int, std::string const&);
	int mvinsnstr(int, int, std::string const&, std::size_t);

	// Deletion functions

	int delch();
	int mvdelch(int, int);

	int insdelln(int);

	// Border

	int border(chtype, chtype, chtype, chtype, chtype, chtype, chtype, chtype);
	int box(chtype, chtype);

	int hline(chtype, int);
	int vline(chtype, int);
	int mvhline(int, int, chtype, int);
	int mvvline(int, int, chtype, int);

	// Attributes

	int attroff(int);
	int attron(int);
	int attrset(int);

	int attr_get(attr_t&);
	int color_get(Color&);

	int attr_color_get(attr_t&, Color&);

	int chgat(int, attr_t, Color);
	int mvchgat(int, int, int, attr_t, Color);

	// Misc

	int move(int, int);
	
	int erase();
	int clear();
	int clrtobot();
	int clrtoeol();

	int refresh();
	int outrefresh();
	int redraw();
	int redrawln(int, int);

	int scroll(int = 1);

	void getyx(int&, int&);
	void getbegyx(int&, int&);
	void getmaxyx(int&, int&);

	protected:
	struct Key{};
	
	WINDOW* win_;
};

} // namespace nccpp

#endif // Header guard
