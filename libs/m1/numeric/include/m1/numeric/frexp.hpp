#ifndef M1_NUMERIC_FREXP_HPP
#define M1_NUMERIC_FREXP_HPP

namespace m1
{
    // =================================================================================================================

    void frexp(float *scale,
               int *exp,
               float x);

    void frexp(double *scale,
               int *exp,
               double x);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_FREXP_HPP
