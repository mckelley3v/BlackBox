#include "m1/log.hpp"
#include <iostream>
#include <cassert>

bool test_log()
{
    m1::log logger(std::cout,
                   std::clog,
                   std::cerr);
    M1_MSG(logger, "Test\n");

    int const test_count = 3;
    int i;
    for(i = 0; i < test_count; ++i)
    {
        M1_MSG(logger, "Test " << i << "\n");
        M1_WARN(logger, "Test " << i << "\n");
        M1_ERROR(logger, "Test " << i << "\n");
    }

    assert(logger.get_message_count() == test_count);
    assert(logger.get_warning_count() == test_count);
    assert(logger.get_error_count() == test_count);

    return true;
}
