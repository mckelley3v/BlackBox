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

//    constexpr std::array<std::size_t, 6> X_offsets = offsets_of<int, float, char, double, char, bool>();
//    static_assert(X_offsets[0] == offsetof(X, a), "offsets_of<X.a> failed");
//    static_assert(X_offsets[1] == offsetof(X, b), "offsets_of<X.b> failed");
//    static_assert(X_offsets[2] == offsetof(X, c), "offsets_of<X.c> failed");
//    static_assert(X_offsets[3] == offsetof(X, d), "offsets_of<X.d> failed");
//    static_assert(X_offsets[4] == offsetof(X, e), "offsets_of<X.e> failed");
//    static_assert(X_offsets[5] == offsetof(X, f), "offsets_of<X.f> failed");

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

//    constexpr std::array<std::size_t, 3> Y_offsets = offsets_of<char, double, std::string>();
//    static_assert(Y_offsets[0] == offsetof(Y, a), "offsets_of<Y.a> failed");
//    static_assert(Y_offsets[1] == offsetof(Y, b), "offsets_of<Y.b> failed");
//    static_assert(Y_offsets[2] == offsetof(Y, c), "offsets_of<Y.c> failed");
}
