#ifndef M1_DATAFLOW_HPP
#define M1_DATAFLOW_HPP

#include "m1/observer_ptr.hpp"
#include <map>
#include <string>
#include <vector>
#include <memory>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    //struct dataflow_node_input_port_description;
    //struct dataflow_node_output_port_description;
    //struct dataflow_node_description;

    //struct dataflow_graph_node_description;
    //struct dataflow_graph_connection_port_description;
    //struct dataflow_graph_connection_description;
    //struct dataflow_graph_description;

    //// ----------------------------------------------------------------------------------------------------------------

    class dataflow_node;
    class dataflow_node_connection;
    class dataflow_graph_instance;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    //struct dataflow_node_input_port_description
    //{
    //    std::string port_name;
    //    std::string type_name;
    //    bool is_optional;
    //    bool is_multiplex;
    //};

    //// ----------------------------------------------------------------------------------------------------------------

    //struct dataflow_node_output_port_description
    //{
    //    std::string port_name;
    //    std::string type_name;
    //};

    //// ----------------------------------------------------------------------------------------------------------------

    //struct dataflow_node_description
    //{
    //    std::string description_name;
    //    std::vector<dataflow_node_input_port_description> input_ports;
    //    std::vector<dataflow_node_output_port_description> output_ports;
    //};

    //// ================================================================================================================

    //struct dataflow_graph_node_description
    //{
    //    std::string description_name;
    //    std::string instance_name;
    //    std::shared_ptr<void> instance_data_ptr;
    //};

    //// ----------------------------------------------------------------------------------------------------------------

    //struct dataflow_graph_connection_port_description
    //{
    //    std::string node_instance_name;
    //    std::string port_name;
    //};

    //// ----------------------------------------------------------------------------------------------------------------

    //struct dataflow_graph_connection_description
    //{
    //    dataflow_graph_connection_port_description source_port;
    //    dataflow_graph_connection_port_description target_port;
    //};

    //// ----------------------------------------------------------------------------------------------------------------

    //struct dataflow_graph_description
    //{
    //    dataflow_node_description interface;
    //    std::vector<dataflow_graph_node_description> internal_nodes;
    //    std::vector<dataflow_graph_connection_description> internal_connections;
    //};

    // ================================================================================================================

    class dataflow_node_output_connection_base
    {
    public:
        void mark_dirty();
        void clear_dirty();
        bool is_dirty() const;

    private:
        // members:
        bool m_IsDirty = false; //? list of connected inputs? timestamp that the input connections check?
    };

    // ================================================================================================================

    template <typename T>
    class dataflow_node_output_connection
        : public dataflow_node_output_connection_base
    {
    public:
        T& operator * ()
        {
            mark_dirty();
            return m_Value;
        }

        T const& operator * () const
        {
            return m_Value;
        }

    private:
        T m_Value;
    };

    // ================================================================================================================

    class dataflow_node_input_connection_base
    {
    public:
        bool is_dirty() const;

    private:
        // members:
        dataflow_node_output_connection_base const *m_ConnectionPtr = nullptr;
    };

    // ================================================================================================================

    template <typename T>
    class dataflow_node_input_connection
        : public dataflow_node_input_connection_base
    {
    public:
        T const& operator * () const;

    private:
        // members:
        //dataflow_node_output_connection_base<T> const *m_ConnectionPtr = nullptr;
    };

    // ================================================================================================================

    template <typename T>
    using dictionary = std::map<std::string, T>;

    class dataflow_node
    {
    public:
        template <typename T> using input_connection = m1::dataflow_node_input_connection<T>;
        template <typename T> using output_connection = m1::dataflow_node_output_connection<T>;
        typedef dictionary<dataflow_node_input_connection_base const*> input_connection_ptr_dict;
        typedef dictionary<dataflow_node_output_connection_base const*> output_connection_ptr_dict;

        dataflow_node(std::string name,
                      input_connection_ptr_dict input_port_ptrs,
                      output_connection_ptr_dict output_port_ptrs);

        virtual ~dataflow_node() = default;

        bool is_dirty() const;
        virtual void process() = 0;

    private:
        // members:
        std::string m_Name;
        input_connection_ptr_dict m_InputConnectionPtrs;
        output_connection_ptr_dict m_OutputConnectionPtrs;
    };

    // ================================================================================================================
} // namespace m1

#endif // M1_DATAFLOW_HPP
