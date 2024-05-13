#include "function.h"

cdecl inline void call_Command(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0].find("$\"") == 0 && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            bool num = true;
            for (uint64_t i3 = 0; i3 < INST.param[1].size(); ++i3)
            {
                if (std::isdigit(INST.param[1][i3]) == 0)
                {
                    num = false;
                    break;
                }
            }

            // 0 - before generation command for compiler target
            // 1 - before the compiler runs target
            // 2 - before the linker runs target
            // 3 - after completion the structure of each target
            // 4 - after collecting all targets
            if (num)
            {
                if (0 <= std::atoi(INST.param[1].c_str()) < 5)
                {
                    oth_commands.push_back(std::pair(tmp, std::atoi(INST.param[1].c_str())));
                }
            }
            else
            {
                uint64_t ind = DOUBLE_.find_(INST.param[1]);
                if (ind != std::uint64_t(-1))
                {
                    oth_commands.push_back(std::pair(tmp, DOUBLE_[ind]));
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                }
            }
        }
        else
        {
            uint64_t ind = STRING_.find_(INST.param[0]);
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
                    if (0 <= std::atoi(INST.param[1].c_str()) < 5)
                    {
                        oth_commands.push_back(std::pair(STRING_[ind], std::atoi(INST.param[1].c_str())));
                    }
                }
                else
                {
                    uint64_t ind2 = DOUBLE_.find_(INST.param[1]);
                    if (ind2 != std::uint64_t(-1))
                    {
                        oth_commands.push_back(std::pair(STRING_[ind], DOUBLE_[ind2]));
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                    }
                }
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}