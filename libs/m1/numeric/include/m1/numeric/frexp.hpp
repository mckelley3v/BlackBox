#ifndef M1_NUMERIC_FREXP_HPP
#define M1_NUMERIC_FREXP_HPP

namespace m1
{
    // =================================================================================================================

    void frexp(float *scale,
               int *exp,
               float x) noexcept;

    void frexp(double *scale,
               int *exp,
               double x) noexcept;

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_FREXP_HPP
