#include "m1/iarchive_json.hpp"
#include "m1/parse_json.hpp"
#include "m1/eval_json.hpp"
#include <cassert>

// =====================================================================================================================

m1::iarchive_json::property_ids::const_iterator m1::iarchive_json::property_ids::begin() const
{
    return const_iterator(*m_ArchivePtr);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::const_iterator m1::iarchive_json::property_ids::end() const
{
    return const_iterator();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::const_iterator m1::iarchive_json::property_ids::cbegin() const
{
    return const_iterator(*m_ArchivePtr);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::const_iterator m1::iarchive_json::property_ids::cend() const
{
    return const_iterator();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::property_ids(iarchive_json &archive)
    : m_ArchivePtr(&archive)
{
}

// =====================================================================================================================

m1::iarchive_json::property_ids::const_iterator::const_iterator()
    : m_ArchivePtr(nullptr)
    , m_PropertyId(0u)
    , m_IsSingle(false)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::const_iterator::const_iterator(iarchive_json &archive)
    : m_ArchivePtr(&archive)
    , m_PropertyId(0u)
    , m_IsSingle(false)
{
    // read tokens until first value is found
    // single values are okay -- returns default property_id
    // empty/null object is okay -- set as end of stream iterator in that case
    enum parse_state
    {
        expect_value_or_object_begin,
        expect_property_or_object_end,
        found_object,
    };

    log &logger = m_ArchivePtr->logger();
    char const *&curr = m_ArchivePtr->m_Current;
    char const * const end = m_ArchivePtr->m_End;

    parse_state state = parse_state::expect_value_or_object_begin;
    while((curr != end) && (state != parse_state::found_object))
    {
        char const * const prev = curr;
        json_token const token = parse_json_token(curr, end);

        switch(state)
        {
            case parse_state::expect_value_or_object_begin:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return;

                    case json_token_id::array_begin:
                    case json_token_id::object_end:
                    case json_token_id::array_end:
                    case json_token_id::separator:
                    case json_token_id::property:
                        M1_ERROR(logger, "Unexpected token, expected object\n");
                        set_error_state();
                        return;

                    case json_token_id::object_begin:
                        state = parse_state::expect_property_or_object_end;
                        break;

                    case json_token_id::value_null:
                        set_end_of_stream_state();
                        state = parse_state::found_object;
                        break;

                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        curr = prev;
                        m_IsSingle = true;
                        state = parse_state::found_object;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return;
                }
                break;

            case parse_state::expect_property_or_object_end:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return;

                    case json_token_id::array_end:
                    case json_token_id::separator:
                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        M1_ERROR(logger, "Unexpected token, expected property\n");
                        set_error_state();
                        return;

                    case json_token_id::object_end:
                        set_end_of_stream_state();
                        state = parse_state::found_object;
                        break;

                    case json_token_id::property:
                        if(!eval_json_property(logger, token, m_PropertyId))
                        {
                            set_error_state();
                            return;
                        }

                        state = parse_state::found_object;
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

    if(state != parse_state::found_object)
    {
        set_error_state();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids::const_iterator& m1::iarchive_json::property_ids::const_iterator::operator ++ ()
{
    // special case of a single value instead of a actual object
    if(m_IsSingle)
    {
        set_end_of_stream_state();
        return *this;
    }

    // find next value -- but don't consume it
    // end of object is okay -- set as end of stream iterator in that case
    enum parse_state
    {
        expect_separator_or_end,
        expect_property,
        found_property_or_end,
    };

    log &logger = m_ArchivePtr->logger();
    char const *&curr = m_ArchivePtr->m_Current;
    char const * const end = m_ArchivePtr->m_End;

    parse_state state = parse_state::expect_separator_or_end;
    while((curr != end) && (state != parse_state::found_property_or_end))
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

                    case json_token_id::array_end:
                    case json_token_id::property:
                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        M1_ERROR(logger, "Unexpected token, expected , or }\n");
                        set_error_state();
                        return *this;

                    case json_token_id::object_end:
                        set_end_of_stream_state();
                        state = parse_state::found_property_or_end;
                        break;

                    case json_token_id::separator:
                        state = parse_state::expect_property;
                        break;

                    default:
                        assert(false && "Invalid token");
                        set_error_state();
                        return *this;
                }
                break;

            case parse_state::expect_property:
                switch(token.id)
                {
                    case json_token_id::invalid:
                        M1_ERROR(logger, "Invalid json\n");
                        set_error_state();
                        return *this;

                    case json_token_id::object_end:
                    case json_token_id::array_end:
                    case json_token_id::separator:
                    case json_token_id::object_begin:
                    case json_token_id::array_begin:
                    case json_token_id::value_null:
                    case json_token_id::value_true:
                    case json_token_id::value_false:
                    case json_token_id::value_int:
                    case json_token_id::value_float:
                    case json_token_id::value_string:
                        M1_ERROR(logger, "Unexpected token, expected property\n");
                        set_error_state();
                        return *this;

                    case json_token_id::property:
                        if(!eval_json_property(logger, token, m_PropertyId))
                        {
                            set_error_state();
                            return *this;
                        }

                        state = parse_state::found_property_or_end;
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

    if(state != parse_state::found_property_or_end)
    {
        set_error_state();
        return *this;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::property_id const& m1::iarchive_json::property_ids::const_iterator::operator * ()
{
    return m_PropertyId;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::property_ids::const_iterator::set_end_of_stream_state()
{
    m_ArchivePtr = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::property_ids::const_iterator::set_error_state()
{
    m_ArchivePtr->set_error_state();
    m_ArchivePtr = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::operator == (iarchive_json::property_ids::const_iterator const &lhs,
                      iarchive_json::property_ids::const_iterator const &rhs)
{
    // return true if both are end-of-stream iterators
    return (lhs.m_ArchivePtr == nullptr) &&
           (rhs.m_ArchivePtr == nullptr);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::operator != (iarchive_json::property_ids::const_iterator const &lhs,
                      iarchive_json::property_ids::const_iterator const &rhs)
{
    // return true if either isn't an end-of-stream iterators
    return (lhs.m_ArchivePtr != nullptr) ||
           (rhs.m_ArchivePtr != nullptr);
}

// =====================================================================================================================
