#include "m1/dataflow.hpp"
#include <functional>
#include <tuple>
#include <utility>
#include "catch.hpp"

// ====================================================================================================================

class X
    : public m1::dataflow_node
{
public:
   X();

   virtual void process() override;

private:
    // members:
    input_connection<int> m_LhsInput;
    input_connection<int> m_RhsInput;
    output_connection<int> m_Result;
};

// ====================================================================================================================

X::X()
    : m1::dataflow_node {
                            "X", // name
                            // input_port_ptrs
                            {
                                {"Lhs", &m_LhsInput},
                                {"Rhs", &m_RhsInput},
                            },
                            // output_port_ptrs
                            {
                                {"Result", &m_Result},
                            }
                        }
{
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void X::process() /*override*/
{
    //m_Result.set_value(m_LhsInput.get_value() + m_RhsInput.get_value());
    *m_Result = *m_LhsInput + *m_RhsInput;
}

// ====================================================================================================================

template <typename T> class F;
template <typename R,
          typename ...Args>
class F<R(Args...)>
    : public m1::dataflow_node
{
public:
    F(std::string name,
      std::string (&input_port_names)[sizeof...(Args)],
      std::string output_port_name)
        : m1::dataflow_node {
                                name,
                                // input_port_ptrs
                                make_input_connection_ptr_dict(input_port_names),
                                // output_port_ptrs
                                {
                                    {output_port_name, &m_Result},
                                },
                            }
    {
    }

    virtual void process() override
    {
        process_impl(std::index_sequence_for<Args...>());
    }

private:
    input_connection_ptr_dict make_input_connection_ptr_dict(std::string (&input_port_names)[sizeof...(Args)] input_port_names)
    {
        return make_input_connection_ptr_dict(input_port_names,
                                              std::index_sequence_for<Args...>());
    }

    template <std::size_t ...Indices>
    input_connection_ptr_dict make_input_connection_ptr_dict(std::string (&input_port_names)[sizeof...(Args)] input_port_names,
                                                             std::index_sequence<Indices...> /*indices*/)
    {
        return
        {
            {std::move(input_port_names.begin()[Indices]), &get<Indices>(m_Inputs)}...
        };
    }

    template <std::size_t ...Indices>
    void process_impl(std::index_sequence<Indices...> /*indices*/)
    {
        *m_Output = on_process(*get<Indices>(m_Inputs)...);
    }

    virtual R on_process(Args...) = 0;

    // members:
    std::tuple<input_connection<Args>...> m_Inputs;
    output_connection<R> m_Output;
};

// ====================================================================================================================

TEST_CASE("Test m1::dataflow", "[m1]")
{
}
