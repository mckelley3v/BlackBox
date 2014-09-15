bool test_main()
{
    extern bool test_any_ptr();
    extern bool test_const_any_ptr();

    bool result = true;
    result &= test_any_ptr();
    result &= test_const_any_ptr();
    return result;
}

int main(int argc, char *argv[])
{
    return test_main() ? 0 : 1;
}
