#ifndef M1_STRING_BUILDER_HPP
#define M1_STRING_BUILDER_HPP

#include "m1/string_builder_base.hpp"
#include <string>

namespace m1
{
    // ================================================================================================================

    class string_builder
        : public string_builder_base
    {
    public:
        string_builder() = default;
        explicit string_builder(std::size_t reserve_hint);
        explicit string_builder(std::locale const &locale);
        string_builder(std::size_t reserve_hint, std::locale const &locale);
        virtual ~string_builder() override = default;

        virtual void append(code_point ch) override;

        std::string str() &&;

    private:
        string_builder(string_builder &&rhs) = delete;
        string_builder(string_builder const &rhs) = delete;
        string_builder& operator = (string_builder &&rhs) = delete;
        string_builder& operator = (string_builder const &rhs) = delete;

        // members:
        std::locale m_Locale;
        std::string m_Str;
    };

    // ================================================================================================================

    class wstring_builder
        : public string_builder_base
    {
    public:
        wstring_builder() = default;
        explicit wstring_builder(std::size_t reserve_hint);
        explicit wstring_builder(std::locale const &locale);
        wstring_builder(std::size_t reserve_hint, std::locale const &locale);
        virtual ~wstring_builder() override = default;

        virtual void append(code_point ch) override;

        std::wstring str() &&;

    private:
        wstring_builder(wstring_builder &&rhs) = delete;
        wstring_builder(wstring_builder const &rhs) = delete;
        wstring_builder& operator = (wstring_builder &&rhs) = delete;
        wstring_builder& operator = (wstring_builder const &rhs) = delete;

        // members:
        std::locale  m_Locale;
        std::wstring m_Str;
    };

    // ================================================================================================================

    class u8string_builder
        : public string_builder_base
    {
    public:
        u8string_builder() = default;
        explicit u8string_builder(std::size_t reserve_hint);
        virtual ~u8string_builder() override = default;

        virtual void append(code_point ch) override;

        std::string str() &&;

    private:
        u8string_builder(u8string_builder &&rhs) = delete;
        u8string_builder(u8string_builder const &rhs) = delete;
        u8string_builder& operator = (u8string_builder &&rhs) = delete;
        u8string_builder& operator = (u8string_builder const &rhs) = delete;

        // members:
        std::string m_Str;
    };

    // ================================================================================================================

    class u16string_builder
        : public string_builder_base
    {
    public:
        u16string_builder() = default;
        explicit u16string_builder(std::size_t reserve_hint);
        virtual ~u16string_builder() override = default;

        virtual void append(code_point ch) override;

        std::u16string str() &&;

    private:
        u16string_builder(u16string_builder &&rhs) = delete;
        u16string_builder(u16string_builder const &rhs) = delete;
        u16string_builder& operator = (u16string_builder &&rhs) = delete;
        u16string_builder& operator = (u16string_builder const &rhs) = delete;

        // members:
        std::u16string m_Str;
    };

    // ================================================================================================================

    class u32string_builder
        : public string_builder_base
    {
    public:
        u32string_builder() = default;
        explicit u32string_builder(std::size_t reserve_hint);
        virtual ~u32string_builder() override = default;

        virtual void append(code_point ch) override;

        std::u32string str() &&;

    private:
        u32string_builder(u32string_builder &&rhs) = delete;
        u32string_builder(u32string_builder const &rhs) = delete;
        u32string_builder& operator = (u32string_builder &&rhs) = delete;
        u32string_builder& operator = (u32string_builder const &rhs) = delete;

        // members:
        std::u32string m_Str;
    };

    // ================================================================================================================
} // namespace m1

#endif // M1_STRING_BUILDER_HPP
