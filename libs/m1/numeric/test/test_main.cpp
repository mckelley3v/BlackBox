extern bool test_clamp();
extern bool test_degrees();
extern bool test_fract();
extern bool test_inverse_sqrt();
extern bool test_is_pow2();
extern bool test_lerp();
extern bool test_log2();
extern bool test_mirror();
extern bool test_mod();
extern bool test_radians();
extern bool test_repeat();
extern bool test_round();
extern bool test_round_even();
extern bool test_smooth_step();
extern bool test_step();
extern bool test_trunc();

bool test_main()
{
    bool result = true;

    result &= test_clamp();
    result &= test_degrees();
    result &= test_fract();
    result &= test_inverse_sqrt();
    result &= test_is_pow2();
    result &= test_lerp();
    result &= test_log2();
    result &= test_mirror();
    result &= test_mod();
    result &= test_radians();
    result &= test_repeat();
    result &= test_round();
    result &= test_round_even();
    result &= test_smooth_step();
    result &= test_step();
    result &= test_trunc();

    return result;
}

int main(int argc, char *argv[])
{
    return test_main() ? 0 : 1;
}
