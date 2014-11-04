#ifndef FLOW_COMPONENTS_CONSTANT_HPP
#define FLOW_COMPONENTS_CONSTANT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/TypeName.hpp"

namespace Flow
{
namespace Components
{
    // =================================================================================================================

    template <typename T>
    class Constant
        : public Component
    {
    public:
        static ComponentDefinitionInitializer const DefinitionInitializer;
        static ComponentDefinition GetDefinition();

        Constant() = delete;
        Constant(TypeManager const &type_manager,
                 std::string instance_name,
                 ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                 T value);
        Constant(Constant &&rhs) = default;
        Constant(Constant const &rhs) = delete;
        Constant& operator = (Constant &&rhs) = default;
        Constant& operator = (Constant const &rhs) = delete;
        ~Constant() = default;

        T const& GetValue() const;

    private:
        // members:
        T m_Value;
    };

    // =================================================================================================================

    template <typename T> MakeSystemComponentInstanceFunc const GetMakeConstantInstanceFunc(T value);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> std::unique_ptr<Component> MakeConstantInstance(TypeManager const &type_manager,
                                                                          std::string instance_name,
                                                                          ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                          T value);

    // =================================================================================================================
} // namespace Components
} // namespace Flow

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    template <>
    struct TypeName<Flow::Components::Constant<bool>>
    {
        constexpr static char const * const value = "Constant<bool>";
    };

    // -----------------------------------------------------------------------------------------------------------------

    template <>
    struct TypeName<Flow::Components::Constant<int>>
    {
        constexpr static char const * const value = "Constant<int>";
    };

    // -----------------------------------------------------------------------------------------------------------------

    template <>
    struct TypeName<Flow::Components::Constant<float>>
    {
        constexpr static char const * const value = "Constant<float>";
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

template <typename T>
/*static*/ Flow::ComponentDefinitionInitializer const Flow::Components::Constant<T>::DefinitionInitializer =
{
    // Name
    Flow::GetTypeName<Constant<T>>(),
    // InputPorts
    {},
    // OutputPorts
    {
        {
            "Value",
            Flow::GetTypeName<T>(),
        },
    },
    // Annotations
    {
        ComponentProcessAnnotation::Ignore, // Process
    },
};

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
/*static*/ Flow::ComponentDefinition Flow::Components::Constant<T>::GetDefinition()
{
    return ComponentDefinition(DefinitionInitializer);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
Flow::Components::Constant<T>::Constant(TypeManager const &type_manager,
                                        std::string instance_name,
                                        ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                        T value)
    : Component(type_manager,
                GetDefinition(),
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"Value", &m_Value}}})
    , m_Value(std::move(value))
{
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
T const& Flow::Components::Constant<T>::GetValue() const
{
    return m_Value;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> Flow::MakeSystemComponentInstanceFunc const Flow::Components::GetMakeConstantInstanceFunc(T value)
{
    return
        [=](TypeManager const &type_manager,
            std::string instance_name,
            ComponentInputConnectionPtrsDict input_connection_ptrs_dict)
        {
            return MakeConstantInstance(type_manager,
                                        std::move(instance_name),
                                        std::move(input_connection_ptrs_dict),
                                        std::move(value));
        };
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> std::unique_ptr<Flow::Component> Flow::Components::MakeConstantInstance(TypeManager const &type_manager,
                                                                                              std::string instance_name,
                                                                                              ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                                              T value)
{
    return std::make_unique<Constant<T>>(type_manager,
                                         std::move(instance_name),
                                         std::move(input_connection_ptrs_dict),
                                         std::move(value));
}

// =====================================================================================================================

#endif // FLOW_COMPONENTS_CONSTANT_HPP
