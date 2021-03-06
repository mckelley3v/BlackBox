#ifndef M1_IARCHIVE_JSON_HPP
#define M1_IARCHIVE_JSON_HPP

#include <string>
#include <vector>
#include <iterator>
#include <ostream>
#include <cstdint>
#include <cassert>
#include "m1/log.hpp"
#include "m1/property_id.hpp"

namespace m1
{
    // =================================================================================================================

    enum class iarchive_state
    {
        valid,
        end,
        error,
    };

    // =================================================================================================================

    class iarchive_json
    {
    public:
        class sentry;
        class property_ids;
        class array_indices;

        template <int N> explicit iarchive_json(log &logger,
                                                char const (&buffer)[N]);
        iarchive_json(log &logger,
                      char const *buffer);
        iarchive_json(log &logger,
                      char const *buffer_begin,
                      char const *buffer_end);
        iarchive_json(iarchive_json &&rhs) = default;
        iarchive_json& operator = (iarchive_json &&rhs) = default;
        ~iarchive_json() = default;

        log& logger();

        iarchive_state get_state() const;
        void set_error_state();

        property_ids get_property_ids();
        array_indices get_array_indices();

        bool read_property(property_id &id);
        bool read_property(std::string &name);

        bool read_value(bool &value);
        bool read_value(int &value);
        bool read_value(float &value);
        bool read_value(crc32 &value);
        bool read_value(std::string &value);

        bool skip_value();

    private:
        iarchive_json() = delete;
        iarchive_json(iarchive_json const &rhs) = delete;
        iarchive_json& operator = (iarchive_json const &rhs) = delete;

        void set_state(iarchive_state state);

        // members:
        log *m_LoggerPtr;
        iarchive_state m_State;
        char const * const m_Begin;
        char const * const m_End;
        char const *m_Current;
    };

    // =================================================================================================================

    bool read_property(iarchive_json &in, property_id &id);
    bool read_property(iarchive_json &in, std::string &name);

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(iarchive_json &in, bool &value);
    bool read_value(iarchive_json &in, int &value);
    bool read_value(iarchive_json &in, float &value);
    bool read_value(iarchive_json &in, crc32 &value);
    bool read_value(iarchive_json &in, std::string &value);
    template <typename T> bool read_value(iarchive_json &in, std::vector<T> &values);
    template <typename T> bool read_value(iarchive_json &in, T values[], int size);
    template <typename T, int N> bool read_value(iarchive_json &in, T (&values)[N]);

    // -----------------------------------------------------------------------------------------------------------------

    bool skip_value(iarchive_json &in);

    // =================================================================================================================

    class iarchive_json::sentry
    {
    public:
        explicit sentry(iarchive_json &in);
        ~sentry();

        explicit operator bool () const;

    private:
        sentry() = delete;
        sentry(sentry &&rhs) = delete;
        sentry(sentry const &rhs) = delete;
        sentry& operator = (sentry &&rhs) = delete;
        sentry& operator = (sentry const &rhs) = delete;

        // members:
        iarchive_json *m_ArchivePtr;
    };

    // =================================================================================================================

    class iarchive_json::property_ids
    {
    public:
        class const_iterator;

        property_ids(property_ids &&rhs) = default;
        property_ids& operator = (property_ids &&rhs) = default;
        ~property_ids() = default;

        // range:
        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:
        property_ids() = delete;
        property_ids(property_ids const &rhs) = delete;
        property_ids& operator = (property_ids const &rhs) = delete;

        friend class iarchive_json;
        property_ids(iarchive_json &archive);

        // members:
        iarchive_json *m_ArchivePtr;
    };

    // =================================================================================================================

    bool operator == (iarchive_json::property_ids::const_iterator const &lhs,
                      iarchive_json::property_ids::const_iterator const &rhs);

    // -----------------------------------------------------------------------------------------------------------------

    bool operator != (iarchive_json::property_ids::const_iterator const &lhs,
                      iarchive_json::property_ids::const_iterator const &rhs);

    // =================================================================================================================

    class iarchive_json::property_ids::const_iterator
        : public std::iterator<std::input_iterator_tag,
                               property_id>
    {
    public:
        const_iterator();
        const_iterator(const_iterator &&rhs) = default;
        const_iterator(const_iterator const &rhs) = default;
        const_iterator& operator = (const_iterator &&rhs) = default;
        const_iterator& operator = (const_iterator const &rhs) = default;
        ~const_iterator() = default;

        const_iterator& operator ++ ();
        property_id const& operator * ();

        friend bool operator == (const_iterator const &lhs,
                                 const_iterator const &rhs);

        friend bool operator != (const_iterator const &lhs,
                                 const_iterator const &rhs);

    private:
        friend class property_ids;
        const_iterator(iarchive_json &archive);

        void set_end_of_stream_state();
        void set_error_state();

        // members:
        iarchive_json *m_ArchivePtr;
        property_id m_PropertyId;
        bool m_IsSingle;
    };

    // =================================================================================================================

    class iarchive_json::array_indices
    {
    public:
        class const_iterator;

        array_indices(array_indices &&rhs) = default;
        array_indices& operator = (array_indices &&rhs) = default;
        ~array_indices() = default;

        // range:
        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:
        array_indices() = delete;
        array_indices(array_indices const &rhs) = delete;
        array_indices& operator = (array_indices const &rhs) = delete;

        friend class iarchive_json;
        array_indices(iarchive_json &archive);

        // members:
        iarchive_json *m_ArchivePtr;
    };

    // =================================================================================================================

    bool operator == (iarchive_json::array_indices::const_iterator const &lhs,
                      iarchive_json::array_indices::const_iterator const &rhs);

    // -----------------------------------------------------------------------------------------------------------------

    bool operator != (iarchive_json::array_indices::const_iterator const &lhs,
                      iarchive_json::array_indices::const_iterator const &rhs);

    // =================================================================================================================

    class iarchive_json::array_indices::const_iterator
        : public std::iterator<std::input_iterator_tag,
                               int>
    {
    public:
        const_iterator();
        const_iterator(const_iterator &&rhs) = default;
        const_iterator(const_iterator const &rhs) = default;
        const_iterator& operator = (const_iterator &&rhs) = default;
        const_iterator& operator = (const_iterator const &rhs) = default;
        ~const_iterator() = default;

        const_iterator& operator ++ ();
        int operator * ();

        friend bool operator == (const_iterator const &lhs,
                                 const_iterator const &rhs);

        friend bool operator != (const_iterator const &lhs,
                                 const_iterator const &rhs);

    private:
        friend class array_indices;
        const_iterator(iarchive_json &archive);

        void set_end_of_stream_state();
        void set_error_state();

        // members:
        iarchive_json *m_ArchivePtr;
        int m_ArrayIndex;
        bool m_IsSingle;
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

template <int N> /*explicit*/ m1::iarchive_json::iarchive_json(log &logger,
                                                               char const (&buffer)[N])
    : iarchive_json(logger,
                    buffer,
                    buffer + N)
{
}

// =====================================================================================================================

template <typename T> bool m1::read_value(iarchive_json &in, std::vector<T> &values)
{
    bool result = true;

    T temp{};
    values.clear();
    for(int const array_index : in.get_array_indices())
    {
        // allow user-defined overloads
        using m1::read_value;
        if(result &= read_value(in, temp))
        {
            values.push_back(std::move(temp));
        }
        else
        {
            M1_ERROR(in.logger(), "Unable to read value at index: " << array_index << "\n");
            in.set_error_state();
            break;
        }
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> bool m1::read_value(iarchive_json &in, T values[], int size)
{
    bool result = true;

    T temp{};
    for(int const array_index : in.get_array_indices())
    {
        if(array_index >= size)
        {
            skip_value(in);
            continue;
        }

        // allow user-defined overloads
        using m1::read_value;
        if(result &= read_value(in, temp))
        {
            values[array_index] = std::move(temp);
        }
        else
        {
            M1_ERROR(in.logger(), "Unable to read value at index: " << array_index << "\n");
            in.set_error_state();
            break;
        }
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T, int N> bool m1::read_value(iarchive_json &in, T (&values)[N])
{
    return read_value(in, values, N);
}

// =====================================================================================================================

#endif // M1_IARCHIVE_JSON_HPP
