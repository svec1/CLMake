#ifndef AST__H_
#define AST__H_
#include "../../bin/include.h"
#include "../class/head/sys.h"
#include "../../bin/ConfigVar.h"

namespace _log
{
    extern std::string file_log;

    extern std::ofstream log_file;
    extern std::atomic<bool> log_;
    extern std::atomic<bool> write;
    extern std::atomic<const char *> str_write;

    extern std::atomic<bool> work;

    extern void start_log();
    extern void logging();
    extern void log_event(std::string event);
}

namespace _assistant
{
    namespace _error_hand
    {
        extern std::atomic<const char *> SB_Error;
        extern systemCl::thread_safe<std::exception> US_Error;
        extern std::atomic<const char *> additional_tg;
        extern std::atomic<bool> current_error;
        extern std::atomic<bool> fatal;

        extern std::atomic<bool> work;

        extern void error_hand();
        extern void errorSB_create(const char *SB_Error_, const char *additional_tg_, bool fatal);
        extern void errorUS_create(std::exception &US_Error_);
    }
    namespace _debug
    {
        extern std::atomic<const char *> message;
        extern std::atomic<const char *> owner;
        extern std::atomic<std::uint32_t> color;
        extern std::atomic<bool> out;

        extern std::atomic<bool> work;

        extern void debug();
        extern void debug_msg_call(const char *msg, const char *own, std::uint32_t color);
    }
    extern std::atomic<bool> assistant_;
    extern std::atomic<bool> exit_request;
    extern void assist();
    extern void exit_();
}
#endif