# Ncursescpp

A RAII-conform C++ ncurses wrapper.

Ncurses features supported by ncursescpp :

* Text output
* Keyboard input
* Colors and attributes
* Windows

Ncursescpp is still WIP and more features will be added.

## Philosophy

Ncursescpp goal is to provide access to ncurses through an interface using C++ resource management idiom, RAII. Each ncurses object (windows, colors, etc) is managed in an automatic and transparent way.

## Installing

Installing ncursescpp requires a compiler conform to the C++11 standard and uses [CMake](http://www.cmake.org).

## License

Ncursescpp is distributed under the CeCILL-B license (akin to the MIT license). See the LICENSE file or http://www.cecill.info/index.en.html for more information.

## Documentation

You can generate the library documentation with [Doxygen](http://www.doxygen.org/index.html). Go to the `doc/` directory and run `doxygen Doxyfile`. The documentation only contains information about ncursescpp interface, as ncurses is already fully documented.
