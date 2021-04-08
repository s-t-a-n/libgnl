cmake_minimum_required(VERSION 3.5)
project(
	gnl
	VERSION 0.1
	DESCRIPTION "Get the next line - 42 project"
	LANGUAGES C CXX)

# CMakeLists.txt inspired by:
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project

set(SRC_D src)
set(INC_D inc)
set(TESTS_D tests)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# global compilation standards
	set(CMAKE_C_STANDARD 99)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
	
	set(CMAKE_CXX_STANDARD 98)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

	option(BUILD_TESTING "Build unittests and standlone torture 'apps' " OFF)
	if(BUILD_TESTING)
		include(CTest)
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR BUILD_TESTING)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

		add_compile_definitions(DEBUG=1)
		add_compile_definitions(DEBUG_FILE="./minishell.log")
	else()
		add_compile_definitions(DEBUG=0)
	endif()

	# Let's nicely support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# Docs only available if this is the main app
	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()

	# Add custom rule to dispose of generateable files from .gitignore
	add_custom_target(distclean
	  COMMAND ${CMAKE_COMMAND} -E echo "Cleaning all files not in source control."
	  COMMAND git clean -d -f -X
	    WORKING_DIRECTORY ${vector_SOURCE_DIR}
	)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
	include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# Target directories
add_subdirectory(${SRC_D})

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(${TESTS_D})
endif()
