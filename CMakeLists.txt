 #####
 # Copyright Benoit Vey (2015)
 #
 # benoit.vey@etu.upmc.fr
 #
 # This software is a library whose purpose is to provide a RAII-conform
 # interface over the ncurses library.
 #
 # This software is governed by the CeCILL-B license under French law and
 # abiding by the rules of distribution of free software.  You can  use, 
 # modify and/ or redistribute the software under the terms of the CeCILL-B
 # license as circulated by CEA, CNRS and INRIA at the following URL
 # "http://www.cecill.info". 
 #
 # As a counterpart to the access to the source code and  rights to copy,
 # modify and redistribute granted by the license, users are provided only
 # with a limited warranty  and the software's author,  the holder of the
 # economic rights,  and the successive licensors  have only  limited
 # liability. 
 #
 # In this respect, the user's attention is drawn to the risks associated
 # with loading,  using,  modifying and/or developing or reproducing the
 # software by the user in light of its specific status of free software,
 # that may mean  that it is complicated to manipulate,  and  that  also
 # therefore means  that it is reserved for developers  and  experienced
 # professionals having in-depth computer knowledge. Users are therefore
 # encouraged to load and test the software's suitability as regards their
 # requirements in conditions enabling the security of their systems and/or 
 # data to be ensured and,  more generally, to use and operate it in the 
 # same conditions as regards security. 
 #
 # The fact that you are presently reading this means that you have had
 # knowledge of the CeCILL-B license and that you accept its terms.
 #####

cmake_minimum_required(VERSION 2.8)

project(ncursescpp)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED "Build the library as a shared object." ON)

if(BUILD_SHARED)
    set(LIBRARY_TYPE SHARED)
else(BUILD_SHARED)
    set(LIBRARY_TYPE STATIC)
endif(BUILD_SHARED)

file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE headers src/*.hpp)
file(GLOB_RECURSE source_inline src/*.ipp)

add_library(ncursescpp ${LIBRARY_TYPE} ${source_files})

install(TARGETS ncursescpp DESTINATION lib)
install(FILES ${headers} ${source_inline} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ncursescpp/)
