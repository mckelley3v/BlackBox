#include "m1/numeric/log2.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_log2()
{
    using m1::log2;
    using m1::is_close;

    // check exact powers of two
    for(int i = 1; i < 32; ++i)
    {
        assert(log2(1 << i) == i);
    }

    // check a bunch of random values
    assert(log2(7) == 2);
    assert(log2(10) == 3);
    assert(log2(16) == 4);
    assert(log2(41) == 5);
    assert(log2(50) == 5);
    assert(log2(51) == 5);
    assert(log2(58) == 5);
    assert(log2(97) == 6);
    assert(log2(99) == 6);
    assert(log2(100) == 6);
    assert(log2(163) == 7);
    assert(log2(225) == 7);
    assert(log2(887) == 9);
    assert(log2(982) == 9);
    assert(log2(2465) == 11);
    assert(log2(3601) == 11);
    assert(log2(4429) == 12);
    assert(log2(4543) == 12);
    assert(log2(8094) == 12);
    assert(log2(8945) == 13);
    assert(log2(9151) == 13);
    assert(log2(9919) == 13);
    assert(log2(11107) == 13);
    assert(log2(11929) == 13);
    assert(log2(13062) == 13);
    assert(log2(13341) == 13);
    assert(log2(13442) == 13);
    assert(log2(13513) == 13);
    assert(log2(14549) == 13);
    assert(log2(22721) == 14);
    assert(log2(710975) == 19);
    assert(log2(4020296) == 21);
    assert(log2(4963132) == 22);
    assert(log2(8071182) == 22);
    assert(log2(8191905) == 22);
    assert(log2(8812743) == 23);
    assert(log2(10097231) == 23);
    assert(log2(10879143) == 23);
    assert(log2(12598487) == 23);
    assert(log2(12663428) == 23);
    assert(log2(13743526) == 23);
    assert(log2(14927214) == 23);
    assert(log2(15400622) == 23);
    assert(log2(15941355) == 23);
    assert(log2(16407028) == 23);
    assert(log2(41516311) == 25);
    assert(log2(82838072) == 26);
    assert(log2(201999071) == 27);
    assert(log2(223029530) == 27);
    assert(log2(300232240) == 28);
    assert(log2(302037514) == 28);
    assert(log2(729833305) == 29);
    assert(log2(935399813) == 29);
    assert(log2(1149907597) == 30);
    assert(log2(1279753084) == 30);
    assert(log2(1340081584) == 30);
    assert(log2(1391580907) == 30);
    assert(log2(1584629747) == 30);
    assert(log2(1679369151) == 30);
    assert(log2(2024024404) == 30);
    assert(log2(2051180187) == 30);

    return true;
}
