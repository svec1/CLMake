#pragma once
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <typeinfo>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>
#include <exception>
#include <map>
#include <io.h>

template <class T>
std::string ToHex(const T &value)
{
    std::ostringstream oss;
    if (!(oss << std::hex << value))
        throw std::exception("Invalid argument");
    return oss.str();
}

template <class T>
std::string toString(const T &value)
{
    std::ostringstream oss;
    if (!(oss << std::dec << value))
        throw std::exception("Invalid argument");
    return oss.str();
}

static std::string time_()
{
    const time_t tm = time(nullptr);

    std::time_t t = std::time(NULL);
    std::tm timeK = *std::localtime(&t);
    std::string timeStr = toString(timeK.tm_mday) + '.' + toString(timeK.tm_mon + 1) +
                          ' ' + toString(timeK.tm_hour) + ':' + toString(timeK.tm_min) + ' ' + toString(timeK.tm_sec) + "s";
    return timeStr;
}