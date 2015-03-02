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

    class iarchive_json
    {
    public:
        class property_ids;
        class array_indices;

        iarchive_json(char const *buffer);
        template <int N> explicit iarchive_json(char const (&buffer)[N]);
        iarchive_json(char const *buffer_begin,
                      char const *buffer_end);
        iarchive_json(iarchive_json &&rhs) = default;
        iarchive_json& operator = (iarchive_json &&rhs) = default;
        ~iarchive_json() = default;

        bool operator ! () const;
        explicit operator bool () const;

        property_ids get_property_ids(log &logger);
        array_indices get_array_indices(log &logger);

        bool read_property(log &logger, property_id &id);
        bool read_property(log &logger, std::string &name);

        bool read_value(log &logger, bool &value);
        bool read_value(log &logger, int &value);
        bool read_value(log &logger, float &value);
        bool read_value(log &logger, crc32 &value);
        bool read_value(log &logger, std::string &value);

        bool skip_value(log &logger);

    private:
        iarchive_json() = delete;
        iarchive_json(iarchive_json const &rhs) = delete;
        iarchive_json& operator = (iarchive_json const &rhs) = delete;

        bool set_error_state(bool state);
        void set_error_state();

        // members:
        char const * const m_Begin;
        char const * const m_End;
        char const * m_Current;
    };

    // =================================================================================================================

    bool read_property(iarchive_json &in, log &logger, property_id &id);
    bool read_property(iarchive_json &in, log &logger, std::string &name);

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(iarchive_json &in, log &logger, bool &value);
    bool read_value(iarchive_json &in, log &logger, int &value);
    bool read_value(iarchive_json &in, log &logger, float &value);
    bool read_value(iarchive_json &in, log &logger, crc32 &value);
    bool read_value(iarchive_json &in, log &logger, std::string &value);
    template <typename T> bool read_value(iarchive_json &in, log &logger, std::vector<T> &values);
    template <typename T> bool read_value(iarchive_json &in, log &logger, T values[], int size);
    template <typename T, int N> bool read_value(iarchive_json &in, log &logger, T (&values)[N]);

    // -----------------------------------------------------------------------------------------------------------------

    bool skip_value(iarchive_json &in, log &logger);

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
        property_ids(iarchive_json &archive, log &logger);

        // members:
        iarchive_json *m_ArchivePtr;
        log *m_LoggerPtr;
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
        const_iterator(iarchive_json &archive, log &logger);

        void set_end_of_stream_state();
        void set_error_state();

        // members:
        iarchive_json *m_ArchivePtr;
        log *m_LoggerPtr;
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
        array_indices(iarchive_json &archive, log &logger);

        // members:
        iarchive_json *m_ArchivePtr;
        log *m_LoggerPtr;
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
        const_iterator(iarchive_json &archive, log &logger);

        void set_end_of_stream_state();
        void set_error_state();

        // members:
        iarchive_json *m_ArchivePtr;
        log *m_LoggerPtr;
        int m_ArrayIndex;
        bool m_IsSingle;
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

template <int N> /*explicit*/ m1::iarchive_json::iarchive_json(char const (&buffer)[N])
    : iarchive_json(buffer,
                    buffer + N)
{
}

// =====================================================================================================================

template <typename T> bool m1::read_value(iarchive_json &in, log &logger, std::vector<T> &values)
{
    T temp{};
    values.clear();
    for(int const array_index : in.get_array_indices(logger))
    {
        // allow user-defined overloads
        using m1::read_value;
        if(read_value(in, logger, temp))
        {
            values.push_back(std::move(temp));
        }
        else
        {
            M1_ERROR(logger, "Unable to read value at index: " << array_index << "\n");
            return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> bool m1::read_value(iarchive_json &in, log &logger, T values[], int size)
{
    T temp{};
    for(int const array_index : in.get_array_indices(logger))
    {
        if(array_index >= size)
        {
            skip_value(in, logger);
            continue;
        }

        // allow user-defined overloads
        using m1::read_value;
        if(read_value(in, logger, temp))
        {
            values[array_index] = std::move(temp);
        }
        else
        {
            M1_ERROR(logger, "Unable to read value at index: " << array_index << "\n");
            return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T, int N> bool m1::read_value(iarchive_json &in, log &logger, T (&values)[N])
{
    return read_value(in, logger, values, N);
}

// =====================================================================================================================

#endif // M1_IARCHIVE_JSON_HPP
