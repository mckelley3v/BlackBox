#include "m1/dataflow.hpp"

// ====================================================================================================================

m1::dataflow_node::dataflow_node(std::string name,
                                 input_connection_ptr_dict input_port_ptrs,
                                 output_connection_ptr_dict output_port_ptrs)
    : m_Name(std::move(name))
    , m_InputConnectionPtrs(std::move(input_port_ptrs))
    , m_OutputConnectionPtrs(std::move(output_port_ptrs))
{
}

// ====================================================================================================================
