#include "head/err.h"

using namespace error__;

bool error::addErrorFatal(std::string index, std::string warningText)
{
    for (uint32_t i = 0; i < this->error_Fatal.size(); ++i)
    {
        if (this->error_Fatal[i].first == index)
        {
            return 0;
        }
    }
    this->error_Fatal.push_back(std::pair(index, warningText));
    return 1;
}

bool error::callError(std::string index)
{
    for (uint32_t i = 0; i < this->error_Fatal.size(); ++i)
    {
        if (this->error_Fatal[i].first == index)
        {
            std::cout << this->error_Fatal[i].first << ": " << this->error_Fatal[i].second << std::endl;
#if defined _WIN32
            SetConsoleTextAttribute(handle, 15);
#endif
            if (log_)
            {
                std::string pathBuild = std::filesystem::current_path().string();
                std::ofstream log_file(pathBuild + "\\CLMakeLog.txt", std::ios::app);
                if (log_file.is_open())
                {
                    log_file << time_() << ": " + this->error_Fatal[i].first + " -> " + this->error_Fatal[i].second;
                    log_file.close();
                }
            }
            exit(4);
        }
    }
    return 0;
}

bool error::callError(std::string index, std::string line, uint32_t ind_err_sym, std::string obj)
{
    for (uint32_t i = 0; i < this->error_Fatal.size(); ++i)
    {
        if (this->error_Fatal[i].first == index)
        {
            std::cout << this->error_Fatal[i].first << ": " << this->error_Fatal[i].second + '\n' + line;
            std::string tmp_ = "";
            for (uint32_t i2 = 0; i2 < ind_err_sym; ++i2)
            {
                tmp_ += ' ';
            }
            std::string tmp = tmp_ + "^\n";
            tmp += tmp_ + obj + " - expected";
            std::cout << tmp << std::endl;

#if defined _WIN32
            SetConsoleTextAttribute(handle, 15);
#endif
            if (log_)
            {
                std::string pathBuild = std::filesystem::current_path().string();
                std::ofstream log_file(pathBuild + "\\CLMakeLog.txt", std::ios::app);
                if (log_file.is_open())
                {
                    log_file << time_() << ": " + this->error_Fatal[i].first + " -> " + this->error_Fatal[i].second;
                    log_file.close();
                }
            }
            exit(4);
        }
    }
    return 0;
}
bool error::callError(std::string index, std::string additional)
{
    for (uint32_t i = 0; i < this->error_Fatal.size(); ++i)
    {
        if (this->error_Fatal[i].first == index)
        {
            std::cout << this->error_Fatal[i].first << ": " << this->error_Fatal[i].second << ". " << additional << std::endl;
#if defined _WIN32
            SetConsoleTextAttribute(handle, 15);
#endif
            if (log_)
            {
                std::string pathBuild = std::filesystem::current_path().string();
                std::ofstream log_file(pathBuild + "\\CLMakeLog.txt", std::ios::app);
                if (log_file.is_open())
                {
                    log_file << time_() << ": " + this->error_Fatal[i].first + " -> " + this->error_Fatal[i].second << ". " << additional;
                    log_file.close();
                }
            }
            exit(4);
        }
    }
    return 0;
}
std::string error::error_t(std::string err)
{
    for (std::uint32_t i = 0; i < error_Fatal.size(); ++i)
    {
        if (error_Fatal[i].first == err)
            return error_Fatal[i].second;
    }
    return "Unexpected error. ";
}