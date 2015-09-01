#ifndef NCURSESCPP_WINDOW_HPP_
#define NCURSESCPP_WINDOW_HPP_

#include <string>

struct _win_st;
typedef _win_st WINDOW;
typedef unsigned int chtype;

namespace nccpp
{

using String = std::basic_string<chtype>;

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

	// Output functions

	int addch(chtype const);
	int mvaddch(int, int, chtype const);
	int echochar(chtype const);

	int printw(char const*, ...);
	int mvprintw(int, int, char const*, ...);

	int addstr(std::string const&);
	int addnstr(std::string const&, int);
	int mvaddstr(int, int, std::string const&);
	int mvaddnstr(int, int, std::string const&, int);

	int addchstr(String const&);
	int addchnstr(String const&, int);
	int mvaddchstr(int, int, String const&);
	int mvaddchnstr(int, int, String const&, int);

	// Misc

	int move(int, int);
	
	protected:
	struct Key{};
	
	WINDOW* win_;
};

} // namespace nccpp

#endif // Header guard
