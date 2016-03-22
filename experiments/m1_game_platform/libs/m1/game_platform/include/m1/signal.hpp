#ifndef M1_SIGNAL_HPP
#define M1_SIGNAL_HPP

#include "m1/intrusive_list.hpp"
#include "m1/intrusive_list_node_traits.hpp"
#include <functional>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename>
    class signal; // undefined

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R, typename... Args>
    class signal<R(Args...)>
    {
    public:
        class connection;

        signal() noexcept = default;
        signal(signal &&rhs) noexcept = default;
        signal& operator = (signal &&rhs) noexcept = default;
        ~signal(); // disconnects all

        template <typename F>
        connection connect(F &&f);

        template <typename Alloc,
                  typename F>
        connection connect(std::allocator_arg_t,
                           Alloc const &alloc,
                           F &&f);

        void emit(Args ...args) const;

        template <typename AccumOp>
        R emit(R init, AccumOp op, Args ...args) const;

    private:
        signal(signal const &rhs) = delete;
        signal& operator = (signal const &rhs) = delete;

        // members:
        intrusive_list<connection> m_Connections;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R, typename... Args>
    class signal<R(Args...)>::connection
        : public intrusive_list_node<connection>
        , private std::function<R(Args...)>
    {
    public:
        connection(connection &&rhs);
        connection& operator = (connection &&rhs);
        ~connection();

        bool disconnect();
        bool is_connected() const;

        bool enable();
        bool disable();
        bool set_enabled(bool value);
        bool is_enabled() const;

    private:
        connection(std::function<R(Args...)> &&f);
        connection() = delete;
        connection(connection const &rhs) = delete;
        connection& operator = (connection const &rhs) = delete;

        using std::function<R(Args...)>::operator ();

        // members:
        bool m_IsEnabled;
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_SIGNAL_HPP
