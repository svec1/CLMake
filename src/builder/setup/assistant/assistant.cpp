#include "../assist.h"

std::atomic<bool> _assistant::assistant_ = false;
std::atomic<bool> _assistant::exit_request = false;

void _assistant::assist()
{
    _assistant::assistant_.exchange(true);

    std::thread th_debug(_debug::debug);
    std::thread th_log(_log::start_log);
    std::thread th_errHand(_error_hand::error_hand);

    while (!_assistant::exit_request.load() && _assistant::assistant_.load())
        ;

    if (_assistant::exit_request.load())
    {
        _assistant::assistant_.exchange(false);
        _log::log_.exchange(false);
    }

    th_errHand.join();
    th_log.join();
    th_debug.join();
}
void _assistant::exit_()
{
    if (!assistant_.load())
    {
        exit_request.exchange(true);
        while (_assistant::assistant_.load())
            ;
    }
    exit(1);
}