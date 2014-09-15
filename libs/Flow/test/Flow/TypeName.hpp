#ifndef FLOW_TYPENAME_HPP
#define FLOW_TYPENAME_HPP

namespace Flow
{

    template <typename T>
    struct TypeName;

    template <>
    struct TypeName<bool>
    {
        constexpr static char const * const value = "bool";
    };

    template <>
    struct TypeName<int>
    {
        constexpr static char const * const value = "int";
    };

    template <>
    struct TypeName<float>
    {
        constexpr static char const * const value = "float";
    };

    template <typename T>
    constexpr char const* GetTypeName()
    {
        return TypeName<T>::value;
    }

} // namespace Flow 

#endif // FLOW_TYPENAME_HPP
