#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include <exception>

struct _win_st;

namespace nccpp
{

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

	private:
	Ncurses();

	_win_st* stdscr_;
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
