#ifndef M1_NUMERIC_MIRROR_HPP
#define M1_NUMERIC_MIRROR_HPP

namespace m1
{
    // =================================================================================================================

    float mirror(float value);
    double mirror(double value);

    float mirror(float value,
                 float min_value,
                 float max_value);

    double mirror(double value,
                  double min_value,
                  double max_value);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_MIRROR_HPP
