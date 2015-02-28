#ifndef M1_NUMERIC_IS_SMALL_HPP
#define M1_NUMERIC_IS_SMALL_HPP

namespace m1
{
    // =================================================================================================================

    bool is_small(float x);
    bool is_small(double x);

    bool is_small(float x,
                  float tolerance);

    bool is_small(double x,
                  double tolerance);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_IS_SMALL_HPP
