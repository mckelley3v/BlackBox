#ifndef M1_NUMERIC_FREXP_HPP
#define M1_NUMERIC_FREXP_HPP

namespace m1
{
    // =================================================================================================================

    float frexp(float x,
                int *exp) noexcept;

    double frexp(double x,
                 int *exp) noexcept;

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_FREXP_HPP
