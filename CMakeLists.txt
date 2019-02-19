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

cmake_minimum_required(VERSION 3.0)

project(ncursescpp VERSION 1.0)

find_package(Curses REQUIRED)
if (CURSES_FOUND AND NOT TARGET Curses::Curses)
  add_library(Curses::Curses UNKNOWN IMPORTED)
  set_target_properties(Curses::Curses PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
    IMPORTED_LOCATION ${CURSES_LIBRARY}
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CURSES_LIBRARIES}"
    )
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
  )

target_link_libraries(${PROJECT_NAME} INTERFACE
  Curses::Curses
  )

target_compile_features(${PROJECT_NAME} INTERFACE
  cxx_std_11
  )

include (CMakePackageConfigHelpers)
include(GNUInstallDirs)
set(config_install_dir  "share/cmake/${PROJECT_NAME}/")
set(project_config      "${PROJECT_NAME}-config.cmake")
set(version_config      "${PROJECT_NAME}-config-version.cmake")
set(targets_export_name "${PROJECT_NAME}-targets")

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
  ${CMAKE_BINARY_DIR}/${project_config}
  INSTALL_DESTINATION ${config_install_dir}
  NO_SET_AND_CHECK_MACRO
  )

write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/${version_config}
  COMPATIBILITY SameMajorVersion
  )

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/
  FILES_MATCHING REGEX ".*\\.[hi]pp"
  )

install(FILES
  ${CMAKE_BINARY_DIR}/${project_config}
  ${CMAKE_BINARY_DIR}/${version_config}
  DESTINATION ${config_install_dir}
  )

install(TARGETS ${PROJECT_NAME}
  EXPORT ${targets_export_name}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

install(EXPORT ${targets_export_name}
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION ${config_install_dir}
  )

export(
  TARGETS ${PROJECT_NAME}
  NAMESPACE "${PROJECT_NAME}::"
  FILE ${CMAKE_BINARY_DIR}/${targets_export_name}.cmake
  )

