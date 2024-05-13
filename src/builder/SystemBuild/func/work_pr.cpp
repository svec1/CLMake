#include "function.h"

cdecl inline void include_File(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0].find("$\"") == INST.param[0].npos)
        {
            ++incFiles;
            if (INST.param[1].find("$\"") == 0)
            {
                INST.param[1].erase(0, 2);
                INST.param[1].erase(INST.param[1].size() - 1, 1);
                FILE_PATH_.createVar(INST.param[0], std::pair(INST.param[1], ""));
            }
            else
            {
                uint64_t ind = STRING_.find_(INST.param[1]);
                if (ind != uint64_t(-1))
                {
                    FILE_PATH_.createVar(INST.param[0], std::pair(STRING_[ind], ""));
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                }
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expecting a name to a string variable(without $\"\")");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}

cdecl inline void parse_File(build::inst &INST)
{
    if (INST.param.size() == 1)
    {
        if (INST.param[0].find("$\"") == INST.param[0].npos)
        {
            uint64_t ind = FILE_PATH_.find_(INST.param[0]);
            if (ind != std::uint64_t(-1))
            {
                _assistant::_debug::debug_msg_call(toString("--------------------Running Parse work.. " + FILE_PATH_[ind].first).c_str(), "", 8);
                FILE_PATH_[ind].second = "CLMakeAn" + toString(incFiles) + ".txt";
                if (system(("clmake.exe " + FILE_PATH_[ind].first + " -AP " + FILE_PATH_[ind].second).c_str()) != 0)
                {
                    error__::ERR.callError("FATAL_ERR_UN_EX");
                }
                _assistant::_debug::debug_msg_call(toString("--------------------End Parse work.   " + FILE_PATH_[ind].first).c_str(), "", 8);
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expecting a name to a string variable(without $\"\")");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 1"));
    }
}

cdecl inline void export_VarFile(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0].find("$\"") == INST.param[0].npos)
        {
            uint64_t ind = FILE_PATH_.find_(INST.param[0]);
            uint32_t exp = 0;
            if (ind != std::uint64_t(-1))
            {
                bool num = true;
                for (uint64_t i3 = 0; i3 < INST.param[1].size(); ++i3)
                {
                    if (std::isdigit(INST.param[1][i3]) == 0)
                    {
                        num = false;
                        break;
                    }
                }
                if (num)
                {
                    exp = std::atoi(INST.param[1].c_str());
                }
                else
                {
                    if (DOUBLE_.find_(INST.param[1]) != std::uint64_t(-1))
                    {
                        exp = DOUBLE_[DOUBLE_.find_(INST.param[1])];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name variable: " + INST.param[1]);
                    }
                }
                std::ifstream file((FILE_PATH_[ind].first + "\\" + FILE_PATH_[ind].second));
                if (file.is_open())
                {
                    deserelization_full(file, exp);
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_FILE_OPEN", "File: " + (FILE_PATH_[ind].first + "\\" + FILE_PATH_[ind].second));
                }
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expecting a name to a string variable(without $\"\")");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}