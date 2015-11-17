#ifndef M1_NUMERIC_MIRROR_HPP
#define M1_NUMERIC_MIRROR_HPP

namespace m1
{
    // =================================================================================================================

    float mirror(float value) noexcept;
    double mirror(double value) noexcept;

    float mirror(float value,
                 float min_value,
                 float max_value) noexcept;

    double mirror(double value,
                  double min_value,
                  double max_value) noexcept;

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_MIRROR_HPP
