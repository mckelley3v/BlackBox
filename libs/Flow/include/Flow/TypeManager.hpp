#ifndef FLOW_TYPEMANAGER_HPP
#define FLOW_TYPEMANAGER_HPP

#include "Flow/Component.hpp"
#include "m1/dictionary.hpp"
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <initializer_list>

namespace Flow
{
    // =================================================================================================================

    class TypeManager;

    // =================================================================================================================

    using MakeSystemComponentInstanceFunc =
        std::function<std::unique_ptr<Component>(TypeManager const &type_manager,
                                                 std::string instance_name,
                                                 ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                 Component::InstanceData *instance_data_ptr)>;

    using MakeComponentInstanceDataFunc = std::function<std::shared_ptr<Component::InstanceData>()>;

    template <typename T> std::unique_ptr<Component> MakeSystemComponent(TypeManager const &type_manager,
                                                                         std::string instance_name,
                                                                         ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                         Component::InstanceData *instance_data_ptr);

    // -----------------------------------------------------------------------------------------------------------------

    struct TypeManagerComponentTypeEntry
    {
        // members:
        ComponentDefinition Definition;
        MakeSystemComponentInstanceFunc MakeInstanceFunc;
        MakeComponentInstanceDataFunc MakeInstanceDataFunc;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct TypeManagerConnectionTypeEntry
    {
        // members:
        std::string Name;
        std::vector<std::string> BaseNames;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct TypeManagerDefinition
    {
        // members:
        std::vector<TypeManagerComponentTypeEntry> ComponentTypes;
        std::vector<TypeManagerConnectionTypeEntry> ConnectionTypes;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class TypeManager
    {
    public:
        explicit TypeManager(TypeManagerDefinition definition);
        TypeManager(TypeManager&&) = default;
        TypeManager& operator = (TypeManager&&) = default;
        ~TypeManager() = default;

        bool IsConnectionValid(char const *source_type,
                               char const *target_type) const;

        bool IsConnectionValid(std::string const &source_type,
                               std::string const &target_type) const;

        ComponentDefinition const* FindComponentDefinition(char const *definition_name) const;
        ComponentDefinition const* FindComponentDefinition(std::string const &definition_name) const;

        std::unique_ptr<Component> MakeSystemComponent(char const *definition_name,
                                                       std::string instance_name,
                                                       ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                       Component::InstanceData *instance_data_ptr) const;

        std::unique_ptr<Component> MakeSystemComponent(std::string const &definition_name,
                                                       std::string instance_name,
                                                       ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                       Component::InstanceData *instance_data_ptr) const;

        std::shared_ptr<Component::InstanceData> MakeComponentInstanceData(char const *definition_name) const;
        std::shared_ptr<Component::InstanceData> MakeComponentInstanceData(std::string const &definition_name) const;

    private:
        TypeManager() = delete;
        TypeManager(TypeManager const&) = delete;
        TypeManager& operator = (TypeManager const&) = delete;

        typedef TypeManagerComponentTypeEntry ComponentTypeEntry;
        typedef m1::dictionary<ComponentTypeEntry> ComponentTypeEntryDict;

        typedef m1::dictionary<std::size_t> ConnectionTypeConversionIndexDict;

        std::shared_ptr<Component::InstanceData> MakeComponentInstanceData(ComponentTypeEntryDict::const_iterator const &component_entry_itr) const;
        std::size_t CalculateConnectionTypeConversionMatrixIndex(std::size_t const source_type_index,
                                                                 std::size_t const target_type_index) const;

        // members:
        ComponentTypeEntryDict m_ComponentTypeEntryDict;
        ConnectionTypeConversionIndexDict m_ConnectionTypeConversionIndexDict;
        std::vector<bool> m_ConnectionTypeConversionMatrix;
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

template <typename T> std::unique_ptr<Flow::Component> Flow::MakeSystemComponent(TypeManager const &type_manager,
                                                                                 std::string instance_name,
                                                                                 ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                                 Component::InstanceData * const instance_data_ptr)
{
    return std::make_unique<T>(type_manager,
                               std::move(instance_name),
                               std::move(input_connection_ptrs_dict));
}

// =====================================================================================================================

#endif // FLOW_TYPEMANAGER_HPP
