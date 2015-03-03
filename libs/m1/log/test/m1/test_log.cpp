#include "m1/log.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Test m1::log", "[m1][m1::log]")
{
    m1::log logger(std::cout,
                   std::clog,
                   std::cerr);
    M1_MSG(logger, "Test\n");

    logger.clear();
    int const test_count = 3;
    for(int i = 0; i < test_count; ++i)
    {
        M1_MSG(logger, "Test " << i << "\n");
        M1_WARN(logger, "Test " << i << "\n");
        M1_ERROR(logger, "Test " << i << "\n");
    }

    CHECK(logger.get_message_count() == test_count);
    CHECK(logger.get_warning_count() == test_count);
    CHECK(logger.get_error_count() == test_count);
}
