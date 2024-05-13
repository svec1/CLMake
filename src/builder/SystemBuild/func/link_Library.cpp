#include "function.h"

cdecl inline void link_Library(build::inst &INST)
{
    if (INST.param.size() >= 2)
    {
        if (INST.param[0].find("$\"") == 0 && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            uint64_t indexPrj = project::find_project(tmp);
            if (indexPrj == std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[0] + std::string(". Does not exist!"));
            }
            for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
            {
                if (INST.param[i3].find("$\"") == 0 && INST.param[i3][INST.param[i3].size() - 1] == '\"')
                {
                    tmp.clear();
                    tmp = INST.param[i3];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    LibFiles.push_back(tmp);
                }
                else
                {
                    uint64_t ind = STRING_.find_(INST.param[i3]);
                    if (ind != std::uint64_t(-1))
                    {
                        LibFiles.push_back(STRING_[ind]);
                    }
                    else
                    {
                        ind = VEC_STRING_.find_(INST.param[i3]);
                        if (ind != std::uint64_t(-1))
                        {
                            for (uint64_t i4 = 0; i4 < VEC_STRING_[ind].size(); ++i4)
                            {
                                LibFiles.push_back(VEC_STRING_[ind][i4]);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i3]);
                        }
                    }
                }
            }
            project::project_[indexPrj].StaticLibrary = LibFiles;
            LibFiles.clear();
        }
        else
        {
            uint64_t indexPrj = project::find_project(STRING_[STRING_.find_(INST.param[0])]);
            std::string tmp;
            if (indexPrj == std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[0] + std::string(". Does not exist!"));
            }
            for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
            {
                if (INST.param[i3].find("$\"") == 0 && INST.param[i3][INST.param[i3].size() - 1] == '\"')
                {
                    tmp.clear();
                    tmp = INST.param[i3];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    LibFiles.push_back(tmp);
                }
                else
                {
                    uint64_t ind = STRING_.find_(INST.param[i3]);
                    if (ind != std::uint64_t(-1))
                    {
                        LibFiles.push_back(STRING_[ind]);
                    }
                    else
                    {
                        ind = VEC_STRING_.find_(INST.param[i3]);
                        if (ind != std::uint64_t(-1))
                        {
                            for (uint64_t i4 = 0; i4 < VEC_STRING_[ind].size(); ++i4)
                            {
                                LibFiles.push_back(VEC_STRING_[ind][i4]);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i3]);
                        }
                    }
                }
            }
            for (uint32_t i2 = 0; i2 < LibFiles.size(); ++i2)
            {
                project::project_[indexPrj].StaticLibrary.push_back(LibFiles[i2]);
            }
            LibFiles.clear();
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
    }
}

cdecl inline void link_Dynamic_Library(build::inst &INST)
{
    if (INST.param.size() >= 2)
    {
        if (INST.param[0].find("$\"") == 0 && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            uint64_t indexPrj = project::find_project(tmp);
            if (indexPrj == std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[0] + std::string(". Does not exist!"));
            }
            for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
            {
                if (INST.param[i3].find("$\"") == 0 && INST.param[i3][INST.param[i3].size() - 1] == '\"')
                {
                    tmp.clear();
                    tmp = INST.param[i3];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    LibFiles.push_back(tmp);
                }
                else
                {
                    uint64_t ind = STRING_.find_(INST.param[i3]);
                    if (ind != std::uint64_t(-1))
                    {
                        LibFiles.push_back(STRING_[ind]);
                    }
                    else
                    {
                        ind = VEC_STRING_.find_(INST.param[i3]);
                        if (ind != std::uint64_t(-1))
                        {
                            for (uint64_t i4 = 0; i4 < VEC_STRING_[ind].size(); ++i4)
                            {
                                LibFiles.push_back(VEC_STRING_[ind][i4]);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i3]);
                        }
                    }
                }
            }
            for (uint32_t i2 = 0; i2 < LibFiles.size(); ++i2)
            {
                project::project_[indexPrj].DynamicLibrary.push_back(LibFiles[i2]);
            }
            LibFiles.clear();
        }
        else
        {
            uint64_t indexPrj = project::find_project(STRING_[STRING_.find_(INST.param[0])]);
            std::string tmp;
            if (indexPrj == std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[0] + std::string(". Does not exist!"));
            }
            for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
            {
                if (INST.param[i3].find("$\"") == 0 && INST.param[i3][INST.param[i3].size() - 1] == '\"')
                {
                    tmp.clear();
                    tmp = INST.param[i3];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    LibFiles.push_back(tmp);
                }
                else
                {
                    uint64_t ind = STRING_.find_(INST.param[i3]);
                    if (ind != std::uint64_t(-1))
                    {
                        LibFiles.push_back(STRING_[ind]);
                    }
                    else
                    {
                        ind = VEC_STRING_.find_(INST.param[i3]);
                        if (ind != std::uint64_t(-1))
                        {
                            for (uint64_t i4 = 0; i4 < VEC_STRING_[ind].size(); ++i4)
                            {
                                LibFiles.push_back(VEC_STRING_[ind][i4]);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i3]);
                        }
                    }
                }
            }
            project::project_[indexPrj].DynamicLibrary = LibFiles;
            LibFiles.clear();
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
    }
}