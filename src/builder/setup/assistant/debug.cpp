#include "../assist.h"

using namespace _assistant;

std::atomic<const char *> _debug::message;
std::atomic<const char *> _debug::owner;
std::atomic<std::uint32_t> _debug::color;
std::atomic<bool> _debug::out = 0;

std::atomic<bool> _debug::work;

void _debug::debug()
{
    work.exchange(1);
    while (assistant_.load())
    {
        if (out.load())
        {
            if (owner.load() != "")
            {
#if defined _WIN32
                SetConsoleTextAttribute(handle, 15);
#endif
                printf("%s: ", owner.load());
            }
#if defined _WIN32
            SetConsoleTextAttribute(handle, color.load());
#endif
            printf("%s\n", message.load());
#if defined _WIN32
            SetConsoleTextAttribute(handle, 15);
#endif
            message.exchange("");
            owner.exchange("");
            color.exchange(0);
            out.exchange(0);
        }
    }
    work.exchange(0);
}
void _debug::debug_msg_call(const char *msg, const char *own, std::uint32_t color_)
{
    if (work.load())
    {
        message.exchange(msg);
        owner.exchange(own);
        color.exchange(color_);
        out.exchange(1);
        while (out.load())
            ;
    }
}