#pragma once

#define RUN_TESTS

#ifdef 	RUN_TESTS
#define TEST(X) X
#else  	// !RUN_TESTS
#define TEST(X)
#endif  // !RUN_TESTS

