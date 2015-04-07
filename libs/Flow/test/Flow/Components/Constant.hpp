#ifndef FLOW_COMPONENTS_CONSTANT_HPP
#define FLOW_COMPONENTS_CONSTANT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/TypeName.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"

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
        class InstanceData;
        static ComponentDefinition GetDefinition();

        Constant(TypeManager const &type_manager,
                 std::string instance_name,
                 ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                 InstanceData instance_data);
        Constant(Constant &&rhs) = default;
        Constant& operator = (Constant &&rhs) = default;
        virtual ~Constant() = default;

        T const& GetValue() const;

    private:
        Constant() = delete;
        Constant(Constant const &rhs) = delete;
        Constant& operator = (Constant const &rhs) = delete;

        // members:
        T m_Value;
    };

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> std::unique_ptr<Component> MakeConstantInstance(TypeManager const &type_manager,
                                                                          std::string instance_name,
                                                                          ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                          Component::InstanceData *instance_data_ptr);

    // =================================================================================================================

    template <typename T>
    class Constant<T>::InstanceData
        : public Component::InstanceData
    {
    public:
        InstanceData() = default;
        InstanceData(T &&value);
        InstanceData(T const &value);
        InstanceData(InstanceData &&rhs) = default;
        InstanceData& operator = (InstanceData &&rhs) = default;
        virtual ~InstanceData() = default;

        T& Value();
        T const& GetValue() const;

    private:
        InstanceData(InstanceData const &rhs) = delete;
        InstanceData& operator = (InstanceData const &rhs) = delete;

        virtual bool ReadArchive(m1::iarchive_json &in);
        virtual bool ReadArchive(m1::iarchive_ubjson &in);

        // members:
        T m_Value;
    };

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
/*static*/ Flow::ComponentDefinition Flow::Components::Constant<T>::GetDefinition()
{
    return
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
            ComponentProcessAnnotation::Never, // Process
        },
    };
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
Flow::Components::Constant<T>::Constant(TypeManager const &type_manager,
                                        std::string instance_name,
                                        ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                        InstanceData instance_data)
    : Component(type_manager,
                GetDefinition(),
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"Value", &m_Value}}})
    , m_Value(std::move(instance_data.Value()))
{
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
T const& Flow::Components::Constant<T>::GetValue() const
{
    return m_Value;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> std::unique_ptr<Flow::Component> Flow::Components::MakeConstantInstance(TypeManager const &type_manager,
                                                                                              std::string instance_name,
                                                                                              ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                                              Component::InstanceData * const instance_data_ptr)
{
    typedef typename Constant<T>::InstanceData InstanceData;
    assert(dynamic_cast<InstanceData*>(instance_data_ptr) != nullptr);

    return std::make_unique<Constant<T>>(type_manager,
                                         std::move(instance_name),
                                         std::move(input_connection_ptrs_dict),
                                         std::move(static_cast<InstanceData&>(*instance_data_ptr)));
}

// =====================================================================================================================

template <typename T> Flow::Components::Constant<T>::InstanceData::InstanceData(T &&value)
    : m_Value(std::move(value))
{
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> Flow::Components::Constant<T>::InstanceData::InstanceData(T const &value)
    : m_Value(value)
{
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T& Flow::Components::Constant<T>::InstanceData::Value()
{
    return m_Value;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const& Flow::Components::Constant<T>::InstanceData::GetValue() const
{
    return m_Value;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> /*virtual*/ bool Flow::Components::Constant<T>::InstanceData::ReadArchive(m1::iarchive_json &in)
{
    return read_value(in, m_Value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> /*virtual*/ bool Flow::Components::Constant<T>::InstanceData::ReadArchive(m1::iarchive_ubjson &in)
{
    return false;
}

// =====================================================================================================================

#endif // FLOW_COMPONENTS_CONSTANT_HPP
