#include "m1/dictionary.hpp"
#include <cassert>

bool test_dictionary()
{
    {
        m1::dictionary<int> word_count;
        ++word_count["a"];
        ++word_count["a"];
        ++word_count["a"];
        assert(word_count.at("a") == 3);
    }

    {
        m1::dictionary<std::string> const types =
        {
            {"bool", "false or true"},
            {"int", "represents a positive or negative integer"},
            {"float", "represents a floating point approximation of a real number"},
            {"string", "represents a piece of text"},
        };

        assert(types.at("bool") == "false or true");
    }
    return true;
}
