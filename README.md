# Ncursescpp

A RAII-conform C++ ncurses wrapper.

Ncurses features supported by ncursescpp :

* Text output
* Keyboard and mouse input
* Colors and attributes
* Windows
* Subwindows

Ncursescpp is still WIP and more features will be added.

## Philosophy

Ncursescpp goal is to provide access to ncurses through an interface using C++ resource management idiom, RAII. Each ncurses object (windows, colors, etc) is managed in an automatic and transparent way.

## Installing

Ncursescpp is a header-only library. You can use [CMake](http://www.cmake.org) to install, or copy the library files where you want. Using ncursescpp in a program requires a compiler supporting the C++11 standard.

## License

Ncursescpp is distributed under the CeCILL-B license (akin to the MIT license). See the LICENSE file or http://www.cecill.info/index.en.html for more information.

## Documentation

You can generate the library documentation with [Doxygen](http://www.doxygen.org/index.html). Go to the `doc/` directory and run `doxygen Doxyfile`. The documentation only contains information about ncursescpp interface, as ncurses is already fully documented.
