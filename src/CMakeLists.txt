# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${gnl_SOURCE_DIR}/inc/*.h")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${gnl_SOURCE_DIR}/src/*.c")

# Make an automatic library - will be static or dynamic based on user setting
add_library(gnl ${SRC_LIST} ${HEADER_LIST})

# Set the compilation standards
set_property(TARGET gnl PROPERTY C_STANDARD 90)

# We need this directory, and users of our library will need it too
target_include_directories(gnl PUBLIC ../inc)

# This depends on (header only) boost
#target_link_libraries(gnl PRIVATE gnl)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/inc"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
