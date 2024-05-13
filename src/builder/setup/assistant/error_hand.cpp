#include "../assist.h"
#include "../../class/head/err.h"

using namespace _assistant;

std::atomic<const char *> _error_hand::SB_Error;
systemCl::thread_safe<std::exception> _error_hand::US_Error;
std::atomic<const char *> _error_hand::additional_tg;
std::atomic<bool> _error_hand::current_error = false;
std::atomic<bool> _error_hand::fatal;

std::atomic<bool> _error_hand::work;

void _error_hand::error_hand()
{
    work.exchange(1);
    while (assistant_.load())
    {
        if (current_error.load())
        {
            if (US_Error.load().what() != "Unknown exception")
            {
                _debug::debug_msg_call(US_Error.load().what(), "ERROR HANDLER", FOREGROUND_RED);
                if (_log::log_.load())
                {
                    _log::log_event(time_() + ": ERROR HANDLER: " + toString(US_Error.load().what()) + '\n');
                }
                if (fatal.load())
                {
                    exit_request.exchange(1);
                }
            }
            else if (SB_Error.load() != "")
            {
                _debug::debug_msg_call(toString(error__::ERR.error_t(SB_Error.load()) + additional_tg.load()).c_str(), "ERROR HANDLER", FOREGROUND_RED);
                if (_log::log_.load())
                {
                    _log::log_event(time_() + ": ERROR HANDLER: " + toString(error__::ERR.error_t(SB_Error.load()) + additional_tg.load()) + '\n');
                }
                if (fatal.load())
                {
                    exit_();
                }
            }
            SB_Error.exchange("");
            US_Error.exchange(std::exception());
            additional_tg.exchange("");
            fatal.exchange(0);
            current_error.exchange(0);
        }
    }
    work.exchange(0);
}
void _error_hand::errorSB_create(const char *SB_Error_, const char *additional_tg_, bool fatal_)
{
    if (work.load())
    {
        SB_Error.exchange(SB_Error_);
        additional_tg.exchange(additional_tg_);
        fatal.exchange(fatal_);
        current_error.exchange(1);
        while (current_error.load())
            ;
    }
}
void _error_hand::errorUS_create(std::exception &US_Error_)
{
    if (work.load())
    {
        US_Error.exchange(US_Error_);
        fatal.exchange(1);
        current_error.exchange(1);
        while (current_error.load())
            ;
    }
}
