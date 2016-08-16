#ifndef M1_USTRING_BUILDER_HPP
#define M1_USTRING_BUILDER_HPP

#include "m1/string_builder_base.hpp"
#include "m1/ustring.hpp"

namespace m1
{
    // ================================================================================================================

    class ustring_builder
        : public string_builder_base
    {
    public:
        ustring_builder() = default;
        virtual ~ustring_builder() override = default;

        virtual void append(code_point ch) override;

        ustring str() &&;

    private:
        ustring_builder(ustring_builder &&rhs) = delete;
        ustring_builder(ustring_builder const &rhs) = delete;
        ustring_builder& operator = (ustring_builder &&rhs) = delete;
        ustring_builder& operator = (ustring_builder const &rhs) = delete;

        // members:
        ustring m_Str;
    };

    // ================================================================================================================
} // namespace m1

#endif // M1_CRC32_BUILDER_HPP
