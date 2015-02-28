extern bool test_crc32();
extern bool test_iarchive_json();
extern bool test_iarchive_ubjson();

bool test_main()
{
    bool result = true;
    result &= test_crc32();
    result &= test_iarchive_json();
    result &= test_iarchive_ubjson();
    return result;
}

int main(int argc, char *argv[])
{
    return test_main() ? 0 : 1;
}
