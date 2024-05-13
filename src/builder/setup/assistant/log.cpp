#include "../assist.h"
#include "../../class/head/err.h"

std::string _log::file_log = "CLMakeLog.txt";
std::ofstream _log::log_file(file_log.c_str(), std::ios::app);
std::atomic<bool> _log::log_ = 0;
std::atomic<bool> _log::write = 0;

std::atomic<const char *> _log::str_write;

std::atomic<bool> _log::work = 0;

void _log::start_log()
{
    if (!_log::log_file.is_open())
    {
        error__::ERR.callError("FATAL_ERR_FILE_OPEN", "The file was not found or did not open. File - " + _log::file_log);
    }
    _log::logging();
    _log::log_file.close();
}

void _log::logging()
{
    _log::work.exchange(1);
    while (_assistant::assistant_.load())
    {
        while (_log::log_.load())
        {
            if (_log::write.load())
            {
                _log::log_file << _log::str_write.load();

                _log::str_write.exchange("");
                _log::write.exchange(0);
            }
        }
    }
    _log::work.exchange(0);
}

void _log::log_event(std::string event)
{
    if (_log::work.load())
    {
        _log::str_write.exchange(event.c_str());
        _log::write.exchange(1);
        while (_log::write.load())
            ;
    }
}