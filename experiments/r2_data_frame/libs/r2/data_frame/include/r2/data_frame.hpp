#ifndef R2_DATA_FRAME_HPP
#define R2_DATA_FRAME_HPP

#include "r2/data_sequence.hpp"

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    // shared_ptr to buffer containing entire data_frame, but with stride/offset to just one column
    // class data_frame_buffer_source;

    // ================================================================================================================

    // shared_ptr to some underlying data, return value through func(underlying[index])
    // class data_frame_func_source

    // ================================================================================================================

    // shared_ptr to some underlying data, return value through func(itr(underlying), end(underlying))
    // class data_frame_aggregate_source;

    // ================================================================================================================

    template <typename ...Ts> class data_frame
    {
    private:
        template <typename T>
        using column_ptr_type = std::shared_ptr<data_sequence<T>>;

        // members:
        std::tuple<column_ptr_type<Ts>...> m_ColumnPtrs {};
    };

    // ================================================================================================================
} // namespace r2

// ====================================================================================================================

#endif // R2_DATA_FRAME_HPP
