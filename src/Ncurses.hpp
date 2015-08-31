#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include <exception>
#include <string>

typedef unsigned int chtype;
struct _win_st;
typedef _win_st WINDOW;

namespace nccpp
{

using String = std::basic_string<chtype>;

class Ncurses
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
	int notimeout(bool);
	void timeout(int);
	int typeahead(int);

	// Output options

	int clearok(bool, bool = false);
	int idlok(bool);
	void idcok(bool);
	void immedok(bool);
	int leaveok(bool);
	int setscrreg(int, int);
	int scrollok(bool);
	int nl(bool);

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

	private:
	Ncurses();

	WINDOW* stdscr_;
};

Ncurses& ncurses();

class InitError : public std::exception
{
	public:
	InitError() noexcept;

	InitError(InitError const& cp) noexcept = default;
	InitError& operator=(InitError const& cp) noexcept = default;

	virtual ~InitError() = default;

	char const* what() const noexcept override;
};

} // namespace ncpp

#endif // Header guard
