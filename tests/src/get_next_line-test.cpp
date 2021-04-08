#include <catch2/catch.hpp>

extern "C" {
#include "gnl.h"
}

TEST_CASE( "gnl stub test", "[gnl]" ) {
	const bool condition = true;
	REQUIRE(condition) ;
}
