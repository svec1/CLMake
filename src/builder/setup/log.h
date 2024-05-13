#ifndef LOG__H_
#define LOG__H_

#include "../../bin/include.h"

namespace _log
{
    extern std::string file_log;

    extern std::ofstream log_file;
    extern std::atomic<bool> log_;
    extern std::atomic<bool> write;
    extern std::atomic<const char *> str_write;

    extern void start_log();
    extern void logging();
    extern void log_event(std::string event);
}

#endif