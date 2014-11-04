#include "Flow/TypeManager.hpp"

// =====================================================================================================================

namespace
{
    typedef Flow::TypeManagerComponentTypeEntry ComponentTypeEntry;
    typedef std::vector<ComponentTypeEntry> ComponentTypes;
    typedef m1::dictionary<ComponentTypeEntry> ComponentTypeEntryDict;

    typedef Flow::TypeManagerConnectionTypeEntry ConnectionTypeEntry;
    typedef std::vector<ConnectionTypeEntry> ConnectionTypes;
    typedef m1::dictionary<std::size_t> ConnectionTypeConversionIndexDict;
    typedef m1::dictionary<ConnectionTypeEntry> ConnectionTypeDict;
} // namespace

// =====================================================================================================================

// copy component type data into dict for fast lookup
static ComponentTypeEntryDict MakeComponentTypeEntryDict(ComponentTypes const &component_types);

// ---------------------------------------------------------------------------------------------------------------------

// calculate index into conversion matrix (simple simulation of 2D array addressing)
static std::size_t CalculateConnectionTypeConversionMatrixIndex(std::size_t const source_type_index,
                                                                std::size_t const target_type_index,
                                                                std::size_t const connection_type_count);

// ---------------------------------------------------------------------------------------------------------------------

// create dict from connection type name to indexes into conversion matrix
// does not create the conversion matrix, pass result into MakeConnectionTypeConversionMatrix to actually create the
// conversion matrix
static ConnectionTypeConversionIndexDict MakeConnectionTypeConversionIndexDict(ConnectionTypes const &connection_types);

// ---------------------------------------------------------------------------------------------------------------------

// create 2D array of bool indicating if a connection from a given source type to target type is valid
static std::vector<bool> MakeConnectionTypeConversionMatrix(ConnectionTypes const &connection_types,
                                                            ConnectionTypeConversionIndexDict const &connection_type_index_dict);

// ---------------------------------------------------------------------------------------------------------------------

// create a dict mapping connection type names to the connection type initializer
static ConnectionTypeDict MakeConnectionTypeDict(ConnectionTypes const &connection_types);

// ---------------------------------------------------------------------------------------------------------------------

// add entries for a given connection type into the conversion matrix
static void SetConnectionTypeConversionMatrixEntries(std::vector<bool> &connection_type_conversion_matrix,
                                                     std::size_t const connection_type_count,
                                                     ConnectionTypeDict const &connection_type_dict,
                                                     ConnectionTypeConversionIndexDict const &connection_type_index_dict,
                                                     std::size_t const source_type_index,
                                                     std::vector<std::string> const &target_type_names);

// =====================================================================================================================

/*explicit*/ Flow::TypeManager::TypeManager(TypeManagerDefinition definition)
    : m_ComponentTypeEntryDict(MakeComponentTypeEntryDict(definition.ComponentTypes))
    , m_ConnectionTypeConversionIndexDict(MakeConnectionTypeConversionIndexDict(definition.ConnectionTypes))
    , m_ConnectionTypeConversionMatrix(MakeConnectionTypeConversionMatrix(definition.ConnectionTypes,
                                                                          m_ConnectionTypeConversionIndexDict))
{
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::TypeManager::IsConnectionValid(char const * const source_type,
                                          char const * const target_type) const
{
    std::size_t const source_type_index = m_ConnectionTypeConversionIndexDict.at(source_type);
    std::size_t const target_type_index = m_ConnectionTypeConversionIndexDict.at(target_type);
    std::size_t const conversion_index = CalculateConnectionTypeConversionMatrixIndex(source_type_index,
                                                                                      target_type_index);
    return m_ConnectionTypeConversionMatrix[conversion_index];
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::TypeManager::IsConnectionValid(std::string const &source_type,
                                          std::string const &target_type) const
{
    std::size_t const source_type_index = m_ConnectionTypeConversionIndexDict.at(source_type);
    std::size_t const target_type_index = m_ConnectionTypeConversionIndexDict.at(target_type);
    std::size_t const conversion_index = CalculateConnectionTypeConversionMatrixIndex(source_type_index,
                                                                                      target_type_index);
    return m_ConnectionTypeConversionMatrix[conversion_index];
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentDefinition const* Flow::TypeManager::FindComponentDefinition(char const * const definition_name) const
{
    ComponentTypeEntryDict::const_iterator const component_type_entry_nvp_itr = m_ComponentTypeEntryDict.find(definition_name);
    if(component_type_entry_nvp_itr != m_ComponentTypeEntryDict.end())
    {
        ComponentTypeEntry const &component_type_entry = component_type_entry_nvp_itr->second;
        return &component_type_entry.Definition;
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentDefinition const* Flow::TypeManager::FindComponentDefinition(std::string const &definition_name) const
{
    ComponentTypeEntryDict::const_iterator const component_type_entry_nvp_itr = m_ComponentTypeEntryDict.find(definition_name);
    if(component_type_entry_nvp_itr != m_ComponentTypeEntryDict.end())
    {
        ComponentTypeEntry const &component_type_entry = component_type_entry_nvp_itr->second;
        return &component_type_entry.Definition;
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

std::unique_ptr<Flow::Component> Flow::TypeManager::MakeSystemComponent(char const * const definition_name,
                                                                        std::string instance_name,
                                                                        ComponentInputConnectionPtrsDict input_connection_ptrs_dict) const
{
    return m_ComponentTypeEntryDict.at(definition_name).MakeInstanceFunc(*this,
                                                                         std::move(instance_name),
                                                                         std::move(input_connection_ptrs_dict));
}

// ---------------------------------------------------------------------------------------------------------------------

std::unique_ptr<Flow::Component> Flow::TypeManager::MakeSystemComponent(std::string const &definition_name,
                                                                        std::string instance_name,
                                                                        ComponentInputConnectionPtrsDict input_connection_ptrs_dict) const
{
    return m_ComponentTypeEntryDict.at(definition_name).MakeInstanceFunc(*this,
                                                                         std::move(instance_name),
                                                                         std::move(input_connection_ptrs_dict));
}

// ---------------------------------------------------------------------------------------------------------------------

std::size_t Flow::TypeManager::CalculateConnectionTypeConversionMatrixIndex(std::size_t const source_type_index,
                                                                            std::size_t const target_type_index) const
{
    return ::CalculateConnectionTypeConversionMatrixIndex(source_type_index,
                                                          target_type_index,
                                                          m_ConnectionTypeConversionIndexDict.size());
}

// =====================================================================================================================

ComponentTypeEntryDict MakeComponentTypeEntryDict(ComponentTypes const &component_types)
{
    ComponentTypeEntryDict result;
    //result.reserve(component_types.size());
    for(ComponentTypeEntry const &component_type_entry : component_types)
    {
        result.emplace(component_type_entry.Definition.Name, component_type_entry);
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

std::size_t CalculateConnectionTypeConversionMatrixIndex(std::size_t const source_type_index,
                                                         std::size_t const target_type_index,
                                                         std::size_t const connection_type_count)
{
    return source_type_index * connection_type_count + target_type_index;
}

// ---------------------------------------------------------------------------------------------------------------------

ConnectionTypeConversionIndexDict MakeConnectionTypeConversionIndexDict(ConnectionTypes const &connection_types)
{
    ConnectionTypeConversionIndexDict result;
    //result.reserve(connection_types.size());

    std::size_t connection_type_index = 0;
    for(ConnectionTypeEntry const &connection_type_entry : connection_types)
    {
        result[connection_type_entry.Name] = connection_type_index++;
    }

    assert(connection_types.size() == result.size());
    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<bool> MakeConnectionTypeConversionMatrix(ConnectionTypes const &connection_types,
                                                     ConnectionTypeConversionIndexDict const &connection_type_index_dict)
{
    ConnectionTypeDict const connection_type_dict = MakeConnectionTypeDict(connection_types);

    std::vector<bool> result;
    std::size_t const connection_type_count = connection_types.size();
    result.resize(connection_type_count * connection_type_count);

    // create a dict from connection type name to index into conversion matrix
    // the conversion matrix holds true if a conversion is valid from source type to target type
    for(ConnectionTypeEntry const &connection_type_entry : connection_types)
    {
        // always allow conversion to same type
        std::size_t const source_type_index = connection_type_index_dict.at(connection_type_entry.Name);
        std::size_t const self_index = CalculateConnectionTypeConversionMatrixIndex(source_type_index,
                                                                                    source_type_index,
                                                                                    connection_type_count);
        result[self_index] = true;

        // recursively add connections to base type
        SetConnectionTypeConversionMatrixEntries(/*ref*/ result,
                                                 connection_type_count,
                                                 connection_type_dict,
                                                 connection_type_index_dict,
                                                 source_type_index,
                                                 connection_type_entry.BaseNames);
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

ConnectionTypeDict MakeConnectionTypeDict(ConnectionTypes const &connection_types)
{
    ConnectionTypeDict result;
    //result.reserve(connection_types.size());

    for(ConnectionTypeEntry const &connection_type_entry : connection_types)
    {
        result.emplace(connection_type_entry.Name, connection_type_entry);
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

void SetConnectionTypeConversionMatrixEntries(std::vector<bool> &connection_type_conversion_matrix,
                                              std::size_t const connection_type_count,
                                              ConnectionTypeDict const &connection_type_dict,
                                              ConnectionTypeConversionIndexDict const &connection_type_index_dict,
                                              std::size_t const source_type_index,
                                              std::vector<std::string> const &target_type_names)
{
    // allow conversions from source type to target types
    for(std::string const &target_type_name : target_type_names)
    {
        std::size_t const target_type_index = connection_type_index_dict.at(target_type_name);
        std::size_t const conversion_index = CalculateConnectionTypeConversionMatrixIndex(source_type_index,
                                                                                          target_type_index,
                                                                                          connection_type_count);
        connection_type_conversion_matrix[conversion_index] = true;

        // recursively add connections to base type
        ConnectionTypeEntry const &target_type_entry = connection_type_dict.at(target_type_name);
        SetConnectionTypeConversionMatrixEntries(connection_type_conversion_matrix,
                                                 connection_type_count,
                                                 connection_type_dict,
                                                 connection_type_index_dict,
                                                 source_type_index,
                                                 target_type_entry.BaseNames);
    }
}

// =====================================================================================================================
