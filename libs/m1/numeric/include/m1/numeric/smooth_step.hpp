#ifndef M1_NUMERIC_SMOOTH_STEP_HPP
#define M1_NUMERIC_SMOOTH_STEP_HPP

namespace m1
{
    // =================================================================================================================

    float smooth_step(float x);
    double smooth_step(double x);

    float smooth_step(float edge0,
                      float edge1,
                      float x);

    double smooth_step(double edge0,
                       double edge1,
                       double x);

    // =================================================================================================================
} // namespace m1

#endif // M1_NUMERIC_SMOOTH_STEP_HPP
