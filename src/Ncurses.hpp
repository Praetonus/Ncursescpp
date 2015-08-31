#ifndef NCURSESCPP_NCURSES_HPP_
#define NCURSESCPP_NCURSES_HPP_

#include <exception>

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

	private:
	Ncurses();
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
