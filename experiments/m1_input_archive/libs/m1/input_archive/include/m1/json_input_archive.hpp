#ifndef M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP
#define M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP

#include "m1/property_id.hpp"
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

        void skip_space();
        char32_t peek_char();
        char32_t read_char();

        bool read_bool(bool &value);
        bool read_int(int &value);
        bool read_float(float &value);
        bool read_string(string_builder_base &value);

    private:
        json_input_archive() = delete;
        json_input_archive(json_input_archive const &rhs) = delete;
        json_input_archive& operator = (json_input_archive const &rhs) = delete;

        json_input_error make_json_input_error(char const *message) const;
        json_syntax_error make_json_syntax_error(char const *message) const;

        // types:
        struct location
        {
            int row;
            int col;
        };

        typedef std::wbuffer_convert<std::codecvt_utf8<char32_t>, char32_t> streambuf;

        // members:
        streambuf m_Buffer;
        location m_Location = {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    // id:
    bool operator >> (json_input_archive &in, property_id &id);

    // bool:
    bool operator >> (json_input_archive &in, bool &value);

    // number:
    bool operator >> (json_input_archive &in, int &value);
    bool operator >> (json_input_archive &in, float &value);

    // string:
    bool operator >> (json_input_archive &in, crc32 &value);
    bool operator >> (json_input_archive &in, std::string &value);
    bool operator >> (json_input_archive &in, std::wstring &value);
    bool operator >> (json_input_archive &in, std::u16string &value);
    bool operator >> (json_input_archive &in, std::u32string &value);
    bool operator >> (json_input_archive &in, ustring &value);

    // array:
    template <typename OutputItr> bool operator >> (json_input_archive &in, array_t<OutputItr> &&value);

    // enum:
    template <typename T, typename ...Options> bool operator >> (json_input_archive &in, select_t<T, Options...> &&value);

    // object:
    template <typename ...Ts> bool operator >> (json_input_archive &in, object_t<Ts...> &&obj);


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

namespace m1
{
    // ================================================================================================================

    template <typename Tuple,
              typename Func>
    void tuple_visit(Tuple const &tuple,
                     Func func)
    {
        impl::tuple_visit_impl(tuple, func, std::make_index_sequence<std::tuple_size_v<Tuple>>());
    }

    // ================================================================================================================

    namespace impl
    {
        // ============================================================================================================

        template <typename Tuple,
                  typename Func,
                  std::size_t ...Indices>
        void tuple_visit_impl(Tuple const &tuple,
                              Func func,
                              std::index_sequence<Indices...> const &/*indices*/)
        {
            auto expand = {(func(std::get<Indices>(tuple)), 0)...};
        }

        // ============================================================================================================
    } // namespace impl

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename ...Ts> bool m1::serialization::operator >> (json_input_archive &in, object_t<Ts...> &&obj)
{
    bool result = true;

    json_input_archive location = in.m_Location;
    for(property_id const &id : in.get_property_ids())
    {
        bool known = false;
        tuple_visit(obj.properties,
                    [&] (auto const &prop)
                    {
                        if(id == prop.id)
                        {
                            known = true;
                            result &= in >> prop.ref;
                        }
                    });

        if (!known)
        {
            // unknown property id
        }

        location = in.m_Location;
    }

    return result;
}

// ====================================================================================================================

#endif // M1_SERIALIZATION_JSON_INPUT_ARCHIVE_HPP
