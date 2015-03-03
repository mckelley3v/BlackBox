#include "m1/numeric/log2.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::log1", "[m1][m1::numeric]")
{
    using m1::log2;

    // check exact powers of two
    for(int i = 1; i < 32; ++i)
    {
        CHECK(log2(1 << i) == i);
    }

    // check a bunch of random values
    CHECK(log2(7) == 2);
    CHECK(log2(10) == 3);
    CHECK(log2(16) == 4);
    CHECK(log2(41) == 5);
    CHECK(log2(50) == 5);
    CHECK(log2(51) == 5);
    CHECK(log2(58) == 5);
    CHECK(log2(97) == 6);
    CHECK(log2(99) == 6);
    CHECK(log2(100) == 6);
    CHECK(log2(163) == 7);
    CHECK(log2(225) == 7);
    CHECK(log2(887) == 9);
    CHECK(log2(982) == 9);
    CHECK(log2(2465) == 11);
    CHECK(log2(3601) == 11);
    CHECK(log2(4429) == 12);
    CHECK(log2(4543) == 12);
    CHECK(log2(8094) == 12);
    CHECK(log2(8945) == 13);
    CHECK(log2(9151) == 13);
    CHECK(log2(9919) == 13);
    CHECK(log2(11107) == 13);
    CHECK(log2(11929) == 13);
    CHECK(log2(13062) == 13);
    CHECK(log2(13341) == 13);
    CHECK(log2(13442) == 13);
    CHECK(log2(13513) == 13);
    CHECK(log2(14549) == 13);
    CHECK(log2(22721) == 14);
    CHECK(log2(710975) == 19);
    CHECK(log2(4020296) == 21);
    CHECK(log2(4963132) == 22);
    CHECK(log2(8071182) == 22);
    CHECK(log2(8191905) == 22);
    CHECK(log2(8812743) == 23);
    CHECK(log2(10097231) == 23);
    CHECK(log2(10879143) == 23);
    CHECK(log2(12598487) == 23);
    CHECK(log2(12663428) == 23);
    CHECK(log2(13743526) == 23);
    CHECK(log2(14927214) == 23);
    CHECK(log2(15400622) == 23);
    CHECK(log2(15941355) == 23);
    CHECK(log2(16407028) == 23);
    CHECK(log2(41516311) == 25);
    CHECK(log2(82838072) == 26);
    CHECK(log2(201999071) == 27);
    CHECK(log2(223029530) == 27);
    CHECK(log2(300232240) == 28);
    CHECK(log2(302037514) == 28);
    CHECK(log2(729833305) == 29);
    CHECK(log2(935399813) == 29);
    CHECK(log2(1149907597) == 30);
    CHECK(log2(1279753084) == 30);
    CHECK(log2(1340081584) == 30);
    CHECK(log2(1391580907) == 30);
    CHECK(log2(1584629747) == 30);
    CHECK(log2(1679369151) == 30);
    CHECK(log2(2024024404) == 30);
    CHECK(log2(2051180187) == 30);
}
