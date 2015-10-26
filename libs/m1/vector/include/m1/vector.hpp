#ifndef M1_VECTOR_HPP
#define M1_VECTOR_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_ops.hpp"
#include "m1/vector_numeric.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    using vector2b = vector<bool[2]>;
    using vector3b = vector<bool[3]>;
    using vector4b = vector<bool[4]>;

    using vector2i = vector<int[2]>;
    using vector3i = vector<int[3]>;
    using vector4i = vector<int[4]>;

    using vector2f = vector<float[2]>;
    using vector3f = vector<float[3]>;
    using vector4f = vector<float[4]>;

    using vector2d = vector<double[2]>;
    using vector3d = vector<double[3]>;
    using vector4d = vector<double[4]>;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_VECTOR_HPP
