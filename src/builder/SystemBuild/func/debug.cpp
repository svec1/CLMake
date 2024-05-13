#include "function.h"

cdecl inline void debug(build::inst &INST)
{
    if (INST.param.size() == 1)
    {
        if (INST.param[0].find("$\"") == 0)
        {

            INST.param[0].erase(0, 2);
            INST.param[0].erase(INST.param[0].size() - 1, 1);
        }
        else
        {
            uint64_t ind = DOUBLE_.find_(INST.param[0]);
            if (ind != std::uint64_t(-1))
            {
                INST.param[0] = DOUBLE_[ind];
            }
            else
            {
                ind = STRING_.find_(INST.param[0]);
                if (ind != std::uint64_t(-1))
                {
                    INST.param[0] = STRING_[ind];
                }
                else
                {
                    ind = STRUCT_.find_(INST.param[0]);
                    if (ind != std::uint64_t(-1))
                    {
                        INST.param[0] = STRUCT_[ind].first + ',' + STRUCT_[ind].second;
                    }
                    else
                    {
                        ind = VEC_STRING_.find_(INST.param[0]);
                        if (ind != std::uint64_t(-1))
                        {
                            for (uint32_t i2 = 0; i2 < VEC_STRING_[ind].size(); ++i2)
                            {
                                INST.param[0] += VEC_STRING_[ind][i2];
                            }
                        }
                        else
                        {
                            ind = project::find_project(INST.param[0]);
                            if (ind != std::uint64_t(-1))
                            {
                                INST.param[0] = "\tProject name - " + project::project_[ind].NameProject + "\n\tList source files - ";
                                for (uint64_t i2 = 0; i2 < project::project_[ind].src_file.size(); ++i2)
                                {
                                    INST.param[0] += project::project_[ind].src_file[i2];
                                    if (i2 < project::project_[ind].src_file.size() - 1)
                                    {
                                        INST.param[0] += ", ";
                                    }
                                }
                                INST.param[0] += "\n\tFlags - " + project::project_[ind].flags +
                                                 "\n\tStandart C - " + toString(project::project_[ind].CStandart) +
                                                 "\n\tStandart CPP - " + toString(project::project_[ind].CPPStandart) +
                                                 "\n\tElement DLL - " + toString(project::project_[ind].DynamicLibrary.size()) +
                                                 "\n\tElement Static Library - " + toString(project::project_[ind].StaticLibrary.size());
                                INST.param[0] += "\n\tDLL LIBRARY: ";
                                for (uint32_t i2 = 0; i2 < project::project_[ind].DynamicLibrary.size(); ++i2)
                                {
                                    INST.param[0] += project::project_[ind].DynamicLibrary[i2].c_str();
                                    if (i2 < project::project_[ind].DynamicLibrary.size() - 1)
                                    {
                                        INST.param[0] += ", ";
                                    }
                                }
                                INST.param[0] += "\n\tSTATIC LIBRARY: ";
                                for (uint32_t i = 0; i < project::project_[ind].StaticLibrary.size(); ++i)
                                {
                                    INST.param[0] += project::project_[ind].StaticLibrary[i].c_str();
                                    if (i < project::project_[ind].StaticLibrary.size() - 1)
                                    {
                                        INST.param[0] += ", ";
                                    }
                                }
                            }
                            else
                            {
                                ind = executable::find_exe(INST.param[0]);
                                if (ind != std::uint64_t(-1))
                                {
                                    std::cout << "PARSER: ";
                                    executable::printInfoExe(ind);
                                    return;
                                }
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
                                }
                            }
                        }
                    }
                }
            }
            std::cout << "PARSER: ";
            std::cout << INST.param[0] << std::endl;
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 1"));
    }
}