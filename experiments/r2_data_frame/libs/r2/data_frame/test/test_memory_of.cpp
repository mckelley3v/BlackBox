#include "r2/memory_of.hpp"
#include "catch.hpp"
#include <string>

TEST_CASE("Test r2::memory_of", "[r2]")
{
    using namespace r2;

    static_assert(memory_of<int>().size == sizeof(int), "memory_of<int> failed");
    static_assert(memory_of<int>().align == alignof(int), "memory_of<int> failed");

    struct X
    {
        int a;
        float b;
        char c;
        double d;
        char e;
        bool f;
    };

    static_assert(memory_of<X>().size == sizeof(X), "memory_of<X> failed");
    static_assert(memory_of<X>().align == alignof(X), "memory_of<X> failed");
    static_assert(memory_of<int, float, char, double, char, bool>().size == sizeof(X), "memory_of<X members> failed");
    static_assert(memory_of<int, float, char, double, char, bool>().align == alignof(X), "memory_of<X members> failed");

    struct Y
    {
        char a;
        double b;
        std::string c;
    };

    static_assert(memory_of<Y>().size == sizeof(Y), "memory_of<Y> failed");
    static_assert(memory_of<Y>().align == alignof(Y), "memory_of<Y> failed");
    static_assert(memory_of<char, double, std::string>().size == sizeof(Y), "memory_of<Y members> failed");
    static_assert(memory_of<char, double, std::string>().align == alignof(Y), "memory_of<Y members> failed");
}
