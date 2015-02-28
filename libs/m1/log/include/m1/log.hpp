#ifndef M1_LOG_HPP
#define M1_LOG_HPP

#include <iosfwd>

// =====================================================================================================================

#define M1_LOG_LEVEL_MSG 1
#define M1_LOG_LEVEL_WARN 2
#define M1_LOG_LEVEL_ERROR 3

#ifndef M1_LOG_LEVEL
#define M1_LOG_LEVEL M1_LOG_LEVEL_MSG
#endif

// =====================================================================================================================

namespace m1
{
    // =================================================================================================================

    class log
    {
    public:
        log() = delete;
        log(std::ostream &message_out,
            std::ostream &warning_out,
            std::ostream &error_out);
        log(log &&rhs) = default;
        log(log const &rhs) = delete;
        log& operator = (log &&rhs) = default;
        log& operator = (log const &rhs) = delete;
        ~log() = default;

        int get_message_count() const;
        int get_warning_count() const;
        int get_error_count() const;

        std::ostream& message(char const * const file, int const line);
        std::ostream& warning(char const * const file, int const line);
        std::ostream& error(char const * const file, int const line);

    private:
        // members:
        int m_MessageCount;
        int m_WarningCount;
        int m_ErrorCount;

        std::ostream &m_MessageOut;
        std::ostream &m_WarningOut;
        std::ostream &m_ErrorOut;
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

#if M1_LOG_LEVEL_MSG >= M1_LOG_LEVEL
#define M1_MSG(log, ...) (log).message(__FILE__, __LINE__) << __VA_ARGS__
#else
#define M1_MSG(log, ...)
#endif

#if M1_LOG_LEVEL_WARN >= M1_LOG_LEVEL
#define M1_WARN(log, ...) (log).warning(__FILE__, __LINE__) << __VA_ARGS__
#else
#define M1_WARN(log, ...)
#endif

#if M1_LOG_LEVEL_ERROR >= M1_LOG_LEVEL
#define M1_ERROR(log, ...) (log).error(__FILE__, __LINE__) << __VA_ARGS__
#else
#define M1_ERROR(log, ...)
#endif

// =====================================================================================================================

#endif // M1_LOG_HPP
