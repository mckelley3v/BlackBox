#ifndef R2_DATA_STORAGE_HPP
#define R2_DATA_STORAGE_HPP

#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    // internal interface class to access underlying data in a type-erased manner
    template <typename T>
    class data_source
    {
    public:
        // types:
        typedef T value_type;

        // construct/move/destroy:
        data_source() = default;
        data_source(data_source &&rhs) = default;
        data_source& operator = (data_source &&rhs) = default;
        virtual ~data_source() = default;

        // properties:
        virtual std::size_t size() const = 0;
        virtual value_type const& operator [] (std::size_t index) const = 0;

    private:
        // copy (deleted):
        data_source(data_source const &rhs) = delete;
        data_source& operator = (data_source const &rhs) = delete;
    };

    // ================================================================================================================

    // adaptor for underlying data to conform to the data_source interface
    // this allows for any data to be used without having to add specialized code for it
    // the only requirements on the underlying data is:
    //      value_type
    //      size()
    //      operator []
    //  std::vector<T> is supported out of the box
    template <typename U>
    class data_source_adaptor
        : public data_source<typename U::value_type>
    {
        typedef data_source<typename U::value_type> base_type;

    public:
        // types:
        typedef U underlying_type;
        typedef typename base_type::value_type value_type;

        // construct/move/destroy:
        data_source_adaptor() = default;
        explicit data_source_adaptor(U &&underlying_data);
        explicit data_source_adaptor(U const &underlying_data);
        data_source_adaptor(data_source_adaptor &&rhs) = default;
        data_source_adaptor& operator = (data_source_adaptor &&rhs) = default;
        virtual ~data_source_adaptor() override = default;

        // properties:
        virtual std::size_t size() const override;
        virtual value_type const& operator [] (std::size_t index) const override;

    private:
        // copy (deleted):
        data_source_adaptor(data_source_adaptor const &rhs) = delete;
        data_source_adaptor& operator = (data_source_adaptor const &rhs) = delete;

        // members:
        underlying_type m_UnderlyingData {};
    };

    // ================================================================================================================
} // namespace r2

// ====================================================================================================================
// r2::data_source_adaptor<T>
// ====================================================================================================================

template <typename U>
/*explicit*/ r2::data_source_adaptor<U>::data_source_adaptor(U &&underlying_data)
    : base_type()
    , m_UnderlyingData(std::move(underlying_data))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename U>
/*explicit*/ r2::data_source_adaptor<U>::data_source_adaptor(U const &underlying_data)
    : base_type()
    , m_UnderlyingData(underlying_data)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename U>
/*virtual*/ std::size_t r2::data_source_adaptor<U>::size() const /*override*/
{
    return m_UnderlyingData.size();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename U>
/*virtual*/ typename r2::data_source_adaptor<U>::value_type const& r2::data_source_adaptor<U>::operator [] (std::size_t const index) const /*override*/
{
    assert(index < size());
    return m_UnderlyingData[index];
}

// ====================================================================================================================

#endif // R2_DATA_STORAGE_HPP
