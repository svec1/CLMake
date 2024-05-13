#include "function.h"

cdecl inline void create_ConfProject(build::inst &INST)
{
    if (INST.param.size() == 1)
    {
        if (INST.param[0].find("$\"") == 0 && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            INST.param[0] = tmp;
            std::pair<std::string, executable::ENUM_EXE> tmp__;
            TARGETS_.createVar(INST.param[0], tmp__);
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expected string type");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 1"));
    }
}
cdecl inline void sc_target(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0].find("$\"") == 0)
        {
            if (INST.param[1].find("$\"") == 0)
            {
                std::string tmp = INST.param[0];
                tmp.erase(0, 2);
                tmp.erase(tmp.size() - 1, 1);
                INST.param[0] = tmp;
                uint64_t ind = TARGETS_.find_(INST.param[0]);
                if (ind != std::uint64_t(-1))
                {
                    std::string tmp3 = INST.param[1];
                    tmp3.erase(0, 2);
                    tmp3.erase(tmp3.size() - 1, 1);
                    INST.param[1] = tmp3;
                    std::ifstream fileTarget(INST.param[1]);
                    if (!fileTarget.is_open())
                    {
                        std::cout << "target configuration file not found in specified directory. Expected file - " << INST.param[1] << std::endl;
                        exit(12);
                    }
                    std::pair<std::string, executable::ENUM_EXE> tmp2;
                    executable::ENUM_EXE tmp__;
                    tmp__.read(fileTarget);
                    std::string flagsLinkTmp = tmp__.get().second.flags;

                    tmp__.get().second.flags.erase(tmp__.get().second.flags.find("<COMPILE>"), std::string("<COMPILE>").size());
                    tmp__.get().second.flags.erase(tmp__.get().second.flags.find("<LINK>"), tmp__.get().second.flags.size() - 1);

                    flagsLinkTmp.erase(flagsLinkTmp.find("<COMPILE>"), flagsLinkTmp.find("<LINK>") + std::string("<LINK>").size());

                    tmp2.first = flagsLinkTmp;
                    tmp2.second = tmp__;
                    TARGETS_[ind] = tmp2;
                    entry_point.push_back(tmp2.second.get_POE());
                    fileTarget.close();
#ifdef debugging
                    std::cout << "ASSEMBLY: ";
#if defined _WIN32
                    SetConsoleTextAttribute(handle, 6);
#endif
                    std::cout << "Deserialization was successful! All configurations have been imported" << std::endl;
#if defined _WIN32
                    SetConsoleTextAttribute(handle, 15);
#endif
#endif
#ifdef DEBUG__
                    std::cout << "read is config file target: " << std::endl;
                    executable::executables_.push_back(tmp__.get());
                    executable::printInfoExe(executable::executables_.size() - 1);
                    executable::executables_.pop_back();
#endif
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
                }
            }
            else
            {
                uint64_t ind = TARGETS_.find_(INST.param[0]);
                if (ind != std::uint64_t(-1))
                {
                    std::string tmp3 = INST.param[1];
                    tmp3.erase(0, 2);
                    tmp3.erase(tmp3.size() - 1, 1);
                    INST.param[1] = tmp3;
                    std::ifstream fileTarget(INST.param[1]);
                    if (!fileTarget.is_open())
                    {
                        std::cout << "target configuration file not found in specified directory. Expected file - " << INST.param[1] << std::endl;
                        exit(12);
                    }
                    std::pair<std::string, executable::ENUM_EXE> tmp2;
                    executable::ENUM_EXE tmp__;
                    tmp__.read(fileTarget);
                    tmp2.first = "";
                    tmp2.second = tmp__;
                    TARGETS_[ind] = tmp2;
                    fileTarget.close();
#ifdef debugging
                    std::cout << "ASSEMBLY: ";
#if defined _WIN32
                    SetConsoleTextAttribute(handle, 6);
#endif
                    std::cout << "Deserialization was successful! All configurations have been imported" << std::endl;
#if defined _WIN32
                    SetConsoleTextAttribute(handle, 15);
#endif
#endif
#ifdef DEBUG__
                    std::cout << "read is config file target: " << std::endl;
                    executable::executables_.push_back(tmp__.get());
                    executable::printInfoExe(executable::executables_.size() - 1);
                    executable::executables_.pop_back();
#endif
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
                }
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expected string type");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}
