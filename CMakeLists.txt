# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

cmake_minimum_required(VERSION 2.6)
project(zint-package)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_VERBOSE_MAKEFILE ON)
#comment or remove the above line before release

add_definitions (-DZINT_VERSION=\"${ZINT_VERSION}\" -Wno-unused-variable -Wall )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )

include (SetPaths.cmake)

INCLUDE (CheckCXXCompilerFlag)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    check_cxx_compiler_flag("-Wall" CXX_COMPILER_FLAG_WALL)
    if (CXX_COMPILER_FLAG_WALL)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wall")
    endif (CXX_COMPILER_FLAG_WALL)
endif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)

add_subdirectory(backend)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

install(FILES cmake/modules/FindZint.cmake DESTINATION /usr/share/cmake/Modules COMPONENT Devel)

# This needs to be run very last so other parts of the scripts can take
# advantage of this.
IF(NOT ZINT_HAS_BEEN_RUN_BEFORE)
    SET(ZINT_HAS_BEEN_RUN_BEFORE 1 CACHE INTERNAL "Flag to track whether this is the first time running CMake or if CMake has been configured before")
ENDIF(NOT ZINT_HAS_BEEN_RUN_BEFORE)


