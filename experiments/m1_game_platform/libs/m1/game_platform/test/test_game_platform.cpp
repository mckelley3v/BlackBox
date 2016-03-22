#include "m1/game_platform.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::game_platform", "[m1]")
{
    m1::game_platform g;
    CHECK(g.run() == 0);
}
