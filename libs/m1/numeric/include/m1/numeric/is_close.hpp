#ifndef M1_NUMERIC_IS_CLOSE_HPP
#define M1_NUMERIC_IS_CLOSE_HPP

namespace m1
{
    // =================================================================================================================

    bool is_close(float lhs,
                  float rhs);

    bool is_close(double lhs,
                  double rhs);

    bool is_close(float lhs,
                  float rhs,
                  float relative_tolerance,
                  float absolute_tolerance);

    bool is_close(double lhs,
                  double rhs,
                  double relative_tolerance,
                  double absolute_tolerance);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_IS_CLOSE_HPP
