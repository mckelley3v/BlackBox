#ifndef M1_VECTOR_NUMERIC_MOD_HPP
#define M1_VECTOR_NUMERIC_MOD_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/mod.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename N, typename D>
    impl::vector_copy_type<N> mod(vector<N> const &numer,
                                  D const &denon) noexcept;

    template <typename N, typename D>
    impl::vector_copy_type<D> mod(N const &numer,
                                  vector<D> const &denon) noexcept;

    template <typename N, typename D>
    impl::vector_copy_type<N, D> mod(vector<N> const &numer,
                                     vector<D> const &denon) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename N, typename D>
m1::impl::vector_copy_type<N> m1::mod(vector<N> const &numer,
                                      D const &denom) noexcept
{
    return impl::generate_vector_copy<N>([&](auto index)
                                         {
                                             using m1::mod;
                                             return mod(numer[index], denom);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename N, typename D>
m1::impl::vector_copy_type<D> m1::mod(N const &numer,
                                      vector<D> const &denom) noexcept
{
    return impl::generate_vector_copy<D>([&](auto index)
                                         {
                                             using m1::mod;
                                             return mod(numer, denom[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename N, typename D>
m1::impl::vector_copy_type<N, D> m1::mod(vector<N> const &numer,
                                         vector<D> const &denom) noexcept
{
    return impl::generate_vector_copy<N, D>([&](auto index)
                                            {
                                                using m1::mod;
                                                return mod(numer[index], denom[index]);
                                            });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_MOD_HPP
