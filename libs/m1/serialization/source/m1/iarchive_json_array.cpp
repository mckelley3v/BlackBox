#include "m1/iarchive_json.hpp"
#include "m1/parse_json.hpp"
#include <cassert>

// =====================================================================================================================

m1::iarchive_json::array_indices::const_iterator m1::iarchive_json::array_indices::begin() const
{
    return const_iterator(*m_ArchivePtr);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::const_iterator m1::iarchive_json::array_indices::end() const
{
    return const_iterator();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::const_iterator m1::iarchive_json::array_indices::cbegin() const
{
    return const_iterator(*m_ArchivePtr);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::const_iterator m1::iarchive_json::array_indices::cend() const
{
    return const_iterator();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::array_indices(iarchive_json &archive)
    : m_ArchivePtr(&archive)
{
}

// =====================================================================================================================

m1::iarchive_json::array_indices::const_iterator::const_iterator()
    : m_ArchivePtr(nullptr)
    , m_ArrayIndex(0)
    , m_IsSingle(false)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::const_iterator::const_iterator(iarchive_json &archive)
    : m_ArchivePtr(&archive)
    , m_ArrayIndex(0)
    , m_IsSingle(false)
{
    // find first value -- but don't consume it
    // single values are okay if not an actual array
    // empty/null array is okay -- set as end of stream iterator in that case
    enum parse_state
    {
        expect_value_or_array_begin,
        expect_value_or_array_end,
        found_array,
    };

    log &logger = m_ArchivePtr->logger();
    char const *&curr = m_ArchivePtr->m_Current;
    char const * const end = m_ArchivePtr->m_End;

    parse_state state = parse_state::expect_value_or_array_begin;
    while((curr != end) && (state != parse_state::found_array))
    {
        char const * const prev = curr;
        json_token const token = parse_json_token(curr, end);

        switch(state)
        {
            case parse_state::expect_value_or_array_begin:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return;

                    case json_token_id::object_end:
                    case json_token_id::array_end:
                    case json_token_id::separator:
                    case json_token_id::property:
                        M1_ERROR(logger, "Unexpected token, expected array\n");
                        set_error_state();
                        return;

                    case json_token_id::array_begin:
                        state = parse_state::expect_value_or_array_end;
                        break;

                    case json_token_id::value_null:
                        set_end_of_stream_state();
                        state = parse_state::found_array;
                        break;

                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                    case json_token_id::object_begin:
                        curr = prev;
                        m_IsSingle = true;
                        state = parse_state::found_array;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return;
                }
                break;

            case parse_state::expect_value_or_array_end:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return;

                    case json_token_id::object_end:
                    case json_token_id::separator:
                    case json_token_id::property:
                        M1_ERROR(logger, "Unexpected token, expected value\n");
                        set_error_state();
                        return;

                    case json_token_id::array_end:
                        set_end_of_stream_state();
                        state = parse_state::found_array;
                        break;

                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        curr = prev;
                        state = parse_state::found_array;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return;
                }
                break;

            default:
                assert(false && "unexpected parse_state");
                set_error_state();
                return;
        }
    }

    if(state != parse_state::found_array)
    {
        set_error_state();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices::const_iterator& m1::iarchive_json::array_indices::const_iterator::operator ++ ()
{
    // special case of a single value instead of a actual object
    if(m_IsSingle)
    {
        set_end_of_stream_state();
        return *this;
    }

    // find next value -- but don't consume it
    // end of array is okay -- set as end of stream iterator in that case
    enum parse_state
    {
        expect_separator_or_end,
        expect_value,
        found_value_or_end,
    };

    log &logger = m_ArchivePtr->logger();
    char const *&curr = m_ArchivePtr->m_Current;
    char const * const end = m_ArchivePtr->m_End;

    parse_state state = parse_state::expect_separator_or_end;
    while((curr != end) && (state != parse_state::found_value_or_end))
    {
        char const * const prev = curr;
        json_token const token = parse_json_token(curr, end);

        switch(state)
        {
            case parse_state::expect_separator_or_end:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return *this;

                    case json_token_id::object_end:
                    case json_token_id::property:
                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        M1_ERROR(logger, "Unexpected token, expected , or ]\n");
                        set_error_state();
                        return *this;

                    case json_token_id::array_end:
                        set_end_of_stream_state();
                        state = parse_state::found_value_or_end;
                        break;

                    case json_token_id::separator:
                        state = parse_state::expect_value;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return *this;
                }
                break;

            case parse_state::expect_value:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return *this;

                    case json_token_id::object_end:
                    case json_token_id::array_end:
                    case json_token_id::separator:
                    case json_token_id::property:
                        M1_ERROR(logger, "Unexpected token, expected value\n");
                        set_error_state();
                        return *this;

                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        curr = prev;
                        state = parse_state::found_value_or_end;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return *this;
                }
                break;

            default:
                assert(false && "unexpected parse_state");
                set_error_state();
                return *this;
        }
    }

    if(state != parse_state::found_value_or_end)
    {
        set_error_state();
        return *this;
    }

    ++m_ArrayIndex;
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

int m1::iarchive_json::array_indices::const_iterator::operator * ()
{
    return m_ArrayIndex;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::array_indices::const_iterator::set_error_state()
{
    m_ArchivePtr->set_error_state();
    m_ArchivePtr = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::array_indices::const_iterator::set_end_of_stream_state()
{
    m_ArchivePtr = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator == (iarchive_json::array_indices::const_iterator const &lhs,
                                 iarchive_json::array_indices::const_iterator const &rhs)
{
    // return true if both are end-of-stream iterators
    return (lhs.m_ArchivePtr == nullptr) &&
           (rhs.m_ArchivePtr == nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator != (iarchive_json::array_indices::const_iterator const &lhs,
                                 iarchive_json::array_indices::const_iterator const &rhs)
{
    // return true if either isn't an end-of-stream iterators
    return (lhs.m_ArchivePtr != nullptr) ||
           (rhs.m_ArchivePtr != nullptr);
}

// =====================================================================================================================
