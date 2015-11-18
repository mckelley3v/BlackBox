#ifndef M1_VECTOR_NUMERIC_MODF_HPP
#define M1_VECTOR_NUMERIC_MODF_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/modf.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T1, typename T2>
    impl::vector_copy_type<T1> modf(vector<T1> const &v,
                                    vector<T2> *int_parts) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T1, typename T2>
m1::impl::vector_copy_type<T1> m1::modf(vector<T1> const &v,
                                        vector<T2> *int_parts) noexcept
{
    assert(int_parts != nullptr);

    return impl::generate_vector_copy<T1>([&](auto index)
                                         {
                                             using m1::modf;
                                             return modf(v[index],
                                                         &(*int_parts)[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_MODF_HPP
