#ifndef M1_STRING_BUILDER_BASE_HPP
#define M1_STRING_BUILDER_BASE_HPP

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    class string_builder_base
    {
    public:
        virtual ~string_builder_base() = default;
        virtual void append(code_point ch) = 0;
    };

    // ================================================================================================================
} // namespace m1

#endif // M1_STRING_BUILDER_BASE_HPP
