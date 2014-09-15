extern bool test_dictionary();

bool test_main()
{
    bool result = true;
    result &= test_dictionary();
    return result;
}

int main(int argc, char *argv[])
{
    return test_main() ? 0 : 1;
}
