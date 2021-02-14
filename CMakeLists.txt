cmake_minimum_required(VERSION 3.11)
project(gnl)
add_library(gnl STATIC
src/get_next_line.c
src/get_next_line_utils.c
)
target_compile_options(gnl PRIVATE
${CMAKE_C_FLAGS}
-Wall -Wextra -Werror -std=c89 -pedantic
)
target_include_directories(gnl
    PUBLIC
		inc
)
