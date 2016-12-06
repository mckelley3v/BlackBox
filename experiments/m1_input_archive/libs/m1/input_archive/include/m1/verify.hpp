#ifndef M1_VERIFY_HPP
#define M1_VERIFY_HPP

// ====================================================================================================================

#ifndef M1_USE_EXCEPTIONS
#define M1_USE_EXCEPTIONS() 0
#endif M1_USE_EXCEPTIONS

#if M1_USE_EXCEPTIONS()

#define M1_ERROR(throw_expression) [&]() -> bool { throw_expression; } ()
#define M1_VERIFY(condition, throw_expression) [&]() -> bool { if(!(condition)) { throw_expression; } return true; } ()

#else

#include <exception>
#include <cassert>

#define M1_STR_IMPL(s) #s
#define M1_STR(s) M1_STR_IMPL(s)

#define M1_ERROR(_) [&]() -> bool { assert(false); std::terminate(); } ()
#define M1_VERIFY(condition, _) [&] { if(!(condition)) { assert(false && M1_STR(condition)); std::terminate(); } return true; } ()

#endif

// ====================================================================================================================

#endif // M1_VERIFY_HPP
