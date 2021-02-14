cmake_minimum_required(VERSION 3.11)
project(gnl)

add_library(gnl STATIC
src/get_next_line.c
src/get_next_line_utils.c
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	if(BUILD_TESTING)
		target_compile_options(gnl PRIVATE "-Wall -Wextra -Werror -std=c89 -pedantic -g -fsanitize=address")
	else()
		target_compile_options(gnl PRIVATE "-Wall -Wextra -Werror -std=c89 -pedantic")
	endif()
endif()

target_include_directories(gnl
    PUBLIC
		inc
)
