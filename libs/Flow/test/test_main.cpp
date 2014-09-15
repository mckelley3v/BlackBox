extern bool TestComponent();
extern bool TestSystem();

bool test_main()
{
    bool result = true;
    result &= TestComponent();
    result &= TestSystem();
    return result;
}

#include <cstdlib>

int main(int argc, char *argv[])
{
    return test_main() ? EXIT_SUCCESS
                       : EXIT_FAILURE;
}
