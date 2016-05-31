#ifndef M1_SIGNAL_HPP
#define M1_SIGNAL_HPP

#include "m1/intrusive_list.hpp"
#include <functional>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename>
    class signal; // undefined

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R,
              typename ...Args>
    class signal<R(Args...)>
    {
    public:
        class connection;

        signal() noexcept = default;
        signal(signal &&rhs) noexcept = default;
        signal& operator = (signal &&rhs) noexcept = default;
        ~signal() = default;

        template <typename F>
        connection connect(F &&f);

        template <typename Alloc,
                  typename F>
        connection connect(std::allocator_arg_t,
                           Alloc const &alloc,
                           F &&f);

        void emit(Args ...args) const;

        template <typename T,
                  typename AccumOp>
        T emit(T init,
               AccumOp op,
               Args ...args) const;

    private:
        signal(signal const &rhs) = delete;
        signal& operator = (signal const &rhs) = delete;

        // members:
        intrusive_list<connection> m_Connections;
    };

    // ----------------------------------------------------------------------------------------------------------------

    class connection_impl
    {
    public:
        connection_impl() noexcept = default;
        connection_impl(connection_impl &&rhs) noexcept = default;
        connection_impl(connection_impl const &rhs) noexcept = default;
        connection_impl& operator = (connection_impl &&rhs) noexcept = default;
        connection_impl& operator = (connection_impl const &rhs) noexcept = default;
        ~connection_impl() = default;

        void enable();
        void disable();
        void set_enabled(bool value);
        bool is_enabled() const;

    private:
        // members:
        bool m_IsEnabled = true;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R,
              typename ...Args>
    class signal<R(Args...)>::connection
        : public intrusive_list_node
        , private connection_impl
        , private std::function<R(Args...)>
    {
        typedef intrusive_list_node node_base;
        typedef std::function<R(Args...)> function_impl;

    public:
        connection(connection &&rhs) = default;
        connection& operator = (connection &&rhs) = default;
        ~connection() = default;

        void disconnect();
        bool is_connected() const;

        using connection_impl::enable;
        using connection_impl::disable;
        using connection_impl::set_enabled;
        using connection_impl::is_enabled;

    private:
        friend class signal<R(Args...)>;
        connection(std::function<R(Args...)> &&f);
        connection() = delete;
        connection(connection const &rhs) = delete;
        connection& operator = (connection const &rhs) = delete;

        using std::function<R(Args...)>::operator ();
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename R,
          typename ...Args>
template <typename F>
typename m1::signal<R(Args...)>::connection m1::signal<R(Args...)>::connect(F &&f)
{
    connection result(std::function<R(Args...)>(std::forward<F>(f)));
    m_Connections.push_back(result);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R,
          typename ...Args>
template <typename Alloc,
          typename F>
typename m1::signal<R(Args...)>::connection m1::signal<R(Args...)>::connect(std::allocator_arg_t,
                                                                            Alloc const &alloc,
                                                                            F &&f)
{
    connection result(std::function<R(Args...)>(std::allocator_arg, alloc, std::forward<F>(f)));
    m_Connections.push_back(result);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R,
          typename ...Args>
void m1::signal<R(Args...)>::emit(Args ...args) const
{
    for(connection const &c : m_Connections)
    {
        if(c.is_enabled())
        {
            c(args...);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R,
          typename ...Args>
template <typename T,
          typename AccumOp>
T m1::signal<R(Args...)>::emit(T init,
                               AccumOp op,
                               Args ...args) const
{
    T &result = init;
    for(connection const &c : m_Connections)
    {
        if(c.is_enabled())
        {
            result = op(result, c(args...));
        }
    }

    return result;
}

// ====================================================================================================================

template <typename R,
          typename ...Args>
m1::signal<R(Args...)>::connection::connection(std::function<R(Args...)> &&f)
    : function_impl(std::move(f))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R,
          typename ...Args>
void m1::signal<R(Args...)>::connection::disconnect()
{
    // consider possibility of disconnect called from signal::emit()
    node_base::clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R,
          typename ...Args>
bool m1::signal<R(Args...)>::connection::is_connected() const
{
    return node_base::is_linked();
}

// ====================================================================================================================

#endif // M1_SIGNAL_HPP
