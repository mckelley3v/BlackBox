#ifndef M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP
#define M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP

#include "m1/property_id.hpp"
#include "m1/verify.hpp"
#include <vector>
#include <tuple>
#include <locale>
#include <codecvt>
#include <iosfwd>
#include <stdexcept>

// ====================================================================================================================

namespace m1
{
    class crc32;
    class ustring;
    class string_builder_base;
}

// ====================================================================================================================

namespace m1
{
namespace serialization
{
    // ================================================================================================================

    class json_error;
    class json_input_error;
    class json_syntax_error;

    template <typename OutputItr> struct array_t;
    template <typename T, typename ...Options> struct select_t;
    template <typename ...Ts> struct object_t;

    // ----------------------------------------------------------------------------------------------------------------

    class json_input_archive
    {
    public:
        explicit json_input_archive(std::streambuf *buffer_ptr);
        json_input_archive(json_input_archive &&rhs) = default;
        json_input_archive& operator = (json_input_archive &&rhs) = default;
        ~json_input_archive() = default;

        // bool:
        bool operator >> (bool &value);

        // number:
        bool operator >> (int &value);
        bool operator >> (float &value);

        // string:
        bool operator >> (string_builder_base &value);

        // array:
        template <typename OutputItr> bool operator >> (array_t<OutputItr> &&value);

        // enum:
        template <typename T, typename ...Options> bool operator >> (select_t<T, Options...> &&value);

        // object:
        template <typename ...Ts> bool operator >> (object_t<Ts...> &&obj);

    private:
        json_input_archive() = delete;
        json_input_archive(json_input_archive const &rhs) = delete;
        json_input_archive& operator = (json_input_archive const &rhs) = delete;

        void skip_space();
        char32_t peek_char();
        char32_t read_char();

        // value:
        bool read_bool(bool &value);
        bool read_int(int &value);
        bool read_float(float &value);
        bool read_string(string_builder_base &value);

        // object:
        bool begin_object();
        bool read_property_id(property_id &value);

        template <typename Tuple,
                  std::size_t Index,
                  std::size_t End>
        bool read_object_property(property_id const &id,
                                  Tuple const &object_properties_tuple,
                                  std::integral_constant<std::size_t, Index> const &/*index*/,
                                  std::integral_constant<std::size_t, End> const &/*end*/);

        template <typename Tuple,
                  std::size_t End>
        bool read_object_property(property_id const &/*id*/,
                                  Tuple const &/*object_properties_tuple*/,
                                  std::integral_constant<std::size_t, End> const &/*end*/,
                                  std::integral_constant<std::size_t, End> const &/*end*/);

        template <typename ...Ts> bool read_object(object_t<Ts...> &&obj);

        bool skip_property();
        bool end_object();

        json_input_error make_json_input_error(char const *message) const;
        json_syntax_error make_json_syntax_error(char const *message) const;

        // types:
        typedef std::wbuffer_convert<std::codecvt_utf8<char32_t>, char32_t> ustreambuf;

        struct location
        {
            int row;
            int col;
        };

        // members:
        ustreambuf m_Buffer;
        location m_Location = {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    // string:
    template <int N> bool operator >> (json_input_archive &in, char (&value)[N]);
    template <int N> bool operator >> (json_input_archive &in, wchar_t (&value)[N]);
    template <int N> bool operator >> (json_input_archive &in, char16_t (&value)[N]);
    template <int N> bool operator >> (json_input_archive &in, char32_t (&value)[N]);

    bool operator >> (json_input_archive &in, crc32 &value);
    bool operator >> (json_input_archive &in, std::string &value);
    bool operator >> (json_input_archive &in, std::wstring &value);
    bool operator >> (json_input_archive &in, std::u16string &value);
    bool operator >> (json_input_archive &in, std::u32string &value);
    bool operator >> (json_input_archive &in, ustring &value);

    // array:
    template <typename T, int N> bool operator >> (json_input_archive &in, T (&value)[N]);
    template <typename T> bool operator >> (json_input_archive &in, std::vector<T> &value);

    // ================================================================================================================
} // namespace serialization
} // namespace m1

// ====================================================================================================================

namespace m1
{
namespace serialization
{
    // ================================================================================================================

    template <typename T>
    struct array_t;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    array_t<T> array(T &ref) = delete;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T, int N>
    struct array_t<T[N]>
    {
        T (*ptr)[N] = nullptr;
        int index = 0;
    };

    template <typename T, int N>
    array_t<T[N]> array(T (&ref)[N]);

    // ================================================================================================================

    template <typename T>
    struct object_property_t
    {
        property_id id;
        T &ref;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    object_property_t<T> property(property_id const &id, T &&ref);

    // ================================================================================================================

    template <typename ...Ts>
    struct object_t
    {
        std::tuple<object_property_t<Ts>...> properties;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename ...Ts>
    object_t<Ts...> object(object_property_t<Ts> &&...properties);

    // ================================================================================================================

    template <typename T>
    struct select_option_t
    {
        T val;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    select_option_t<T> option(property_id const &id, T const &val);

    // ================================================================================================================

    template <typename T, typename ...Ts>
    struct select_t
    {
        T &ref;
        std::tuple<select_option_t<Ts>...> options;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T,
              typename ...Ts>
    select_t<Ts...> select(T &ref, select_option_t<Ts> &&...options);

    // ================================================================================================================

    class json_error
        : public std::runtime_error
    {
    public:
        json_error(int row,
                   int col,
                   char const *message);

        int row() const;
        int col() const;

    private:
        int m_Row = 0;
        int m_Col = 0;
    };

    // ================================================================================================================

    class json_input_error
        : public json_error
    {
    public:
        using json_error::json_error;
    };

    // ================================================================================================================

    class json_syntax_error
        : public json_error
    {
    public:
        using json_error::json_error;
    };

    // ================================================================================================================
} // namespace serialization
} // namespace m1

// ====================================================================================================================
// Implementation
// ====================================================================================================================

//template <typename OutputItr>
//bool m1::serialization::json_input_archive::operator >> (array_t<OutputItr> &&value);

// ====================================================================================================================

//template <typename T,
//          typename ...Options>
//bool m1::serialization::json_input_archive::operator >> (select_t<T, Options...> &&value);

// ====================================================================================================================

template <typename ...Ts>
bool m1::serialization::json_input_archive::operator >> (object_t<Ts...> &&obj)
{
    return read_object(std::move(obj));
}

// ====================================================================================================================

template <typename Tuple,
          std::size_t Index,
          std::size_t End>
bool m1::serialization::json_input_archive::read_object_property(property_id const &id,
                                                                 Tuple const &object_properties_tuple,
                                                                 std::integral_constant<std::size_t, Index> const &/*index*/,
                                                                 std::integral_constant<std::size_t, End> const &end)
{
    auto const &object_property = std::get<Index>(object_properties_tuple);
    if(object_property.id == id)
    {
        return *this >> object_property.ref;
    }
    else
    {
        return read_object_property(id,
                                    object_properties_tuple,
                                    std::integral_constant<std::size_t, Index + 1>(),
                                    end);
    }
}

// ====================================================================================================================

template <typename Tuple,
          std::size_t End>
bool m1::serialization::json_input_archive::read_object_property(property_id const &/*id*/,
                                                                 Tuple const &/*object_properties_tuple*/,
                                                                 std::integral_constant<std::size_t, End> const &/*end*/,
                                                                 std::integral_constant<std::size_t, End> const &/*end*/)
{
    // unknown id
    return skip_property();
}

// ====================================================================================================================

template <typename ...Ts>
bool m1::serialization::json_input_archive::read_object(object_t<Ts...> &&obj)
{
    bool result = true;
    if(begin_object())
    {
        while(!end_object())
        {
            property_id id;

            // key:
            if(!read_property_id(id))
            {
                result = false;
                M1_ERROR(throw make_json_input_error("error reading object key"));
            }

            // value:
            result &= read_object_property(id,
                                           obj.properties,
                                           std::integral_constant<std::size_t, 0>(),
                                           std::tuple_size<decltype(obj.properties)>());
        }
    }

    return result;
}

// ====================================================================================================================

#endif // M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP
