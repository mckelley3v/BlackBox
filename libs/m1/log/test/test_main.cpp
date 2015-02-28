extern bool test_log();

bool test_main()
{
    bool result = true;
    result &= test_log();
    return result;
}

int main(int argc, char *argv[])
{
    return test_main() ? 0 : 1;
}
