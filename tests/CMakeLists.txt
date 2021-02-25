FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.4)
FetchContent_MakeAvailable(Catch2)

## All unittests
set (TEST "test-all")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${TEST}.bin ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE gnl)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

### lexer unittest
#set (TEST "test-lexer")
#set (SRC_LIST "src/lexer.cpp")
#
#add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
#target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
#target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(${TEST}.bin PRIVATE gnl)
#add_test(NAME ${TEST}
#		COMMAND ${TEST}.bin)
