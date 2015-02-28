#ifndef M1_NUMERIC_MODF_HPP
#define M1_NUMERIC_MODF_HPP

namespace m1
{
    // =================================================================================================================

    float modf(float x, float *int_part);
    double modf(double x, double *int_part);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_MODF_HPP
