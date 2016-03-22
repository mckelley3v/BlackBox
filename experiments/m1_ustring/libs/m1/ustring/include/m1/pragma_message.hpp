#ifndef M1_PRAGMA_MESSAGE_HPP
#define M1_PRAGMA_MESSAGE_HPP

// ====================================================================================================================

#define M1_MESSAGE_STRINGIZE_IMPL(s) #s
#define M1_MESSAGE_STRINGIZE(s) M1_MESSAGE_STRINGIZE_IMPL(s)
#define M1_MESSAGE(str) message(__FILE__ "(" M1_MESSAGE_STRINGIZE(__LINE__) "): warning message: " str)

// usage: #pragma M1_MESSAGE("your message")

// ====================================================================================================================


#endif // M1_PRAGMA_MESSAGE_HPP
