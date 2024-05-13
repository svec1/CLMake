#include "function.h"

cdecl inline void set(build::inst &INST)
{
    if (INST.param.size() == 0)
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Param: . Unspecified parameters");
    for (uint64_t i2 = 0; i2 < INST.param.size(); ++i2)
    {
        // CLMAKE variable
        if (INST.param[i2].find("CLMAKE_") == 0)
        {
            uint64_t ind = DOUBLE_.find_(INST.param[i2]);
            uint64_t ind2 = STRING_.find_(INST.param[i2]);
            uint64_t ind3 = VEC_STRING_.find_(INST.param[i2]);
            if ((INST.param.size() == 2 || INST.param.size() == 3) && ind != std::uint64_t(-1))
            {
                bool num = true;
                for (uint64_t i3 = 0; i3 < INST.param[i2 + 1].size(); ++i3)
                {
                    if (std::isdigit(INST.param[i2 + 1][i3]) == 0)
                    {
                        if (INST.param[i2 + 1][i3] == '.' && i3 != 0)
                            continue;
                        num = false;
                        break;
                    }
                }
                if (num)
                {
                    DOUBLE_.redataVar(ind, std::atof(INST.param[i2 + 1].c_str()));
                }
                else
                {
                    DOUBLE_.redataVar(ind, DOUBLE_[DOUBLE_.find_(INST.param[i2 + 1])]);
                }
                if (INST.param[i2] == "CLMAKE_minimal_version" && INST.param.size() == 3)
                {
                    if (INST.param[2] == "WARNING")
                    {
                        scold_VersionCLMake = 0;
                    }
                    else if (INST.param[2] == "ERROR")
                    {
                        scold_VersionCLMake = 1;
                    }
                }
                break;
            }
            else if (INST.param.size() == 2 && ind2 != std::uint64_t(-1))
            {
                if (INST.param[i2 + 1].find("$\"") == 0)
                {
                    std::string tmp = INST.param[i2 + 1];
                    tmp.erase(tmp.find("$\""), 2);
                    tmp.erase(tmp.find("\""), 1);
                    INST.param[i2 + 1] = tmp;
                    STRING_.redataVar(ind2, INST.param[i2 + 1]);
                    break;
                }
                else
                {
                    STRING_.redataVar(STRING_.find_(INST.param[i2]), STRING_[STRING_.find_(INST.param[i2 + 1])]);
                }
            }
            else if (INST.param.size() >= 2 && ind3 != std::uint64_t(-1))
            {
                std::vector<std::string> tmp_;
                std::string tmp;
                for (uint64_t i3 = 1; i3 < INST.param.size(); ++i3)
                {
                    tmp = INST.param[i3];
                    if (tmp.find("$\"") == 0)
                    {
                        tmp.erase(0, 2);
                        tmp.erase(tmp.size() - 1, 1);
                        tmp_.push_back(tmp);
                    }
                    else if (tmp.find("${") == 0)
                    {
                        tmp.erase(0, 2);
                        tmp.erase(tmp.size() - 1, 1);
                        tmp_.push_back(STRING_[STRING_.find_(tmp)]);
                    }
                    else
                    {
                        ind2 = STRING_.find_(tmp);
                        if (ind2 != std::uint64_t(-1))
                        {
                            tmp_.push_back(STRING_[ind2]);
                        }
                        else
                        {
                            ind2 = VEC_STRING_.find_(tmp);
                            if (ind2 != std::uint64_t(-1))
                            {
                                for (uint32_t i4 = 0; i4 < VEC_STRING_[ind2].size(); ++i4)
                                {
                                    tmp_.push_back(VEC_STRING_[ind2][i4]);
                                }
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + tmp);
                            }
                        }
                    }
                }
                VEC_STRING_.redataVar(ind3, tmp_);
                tmp_.clear();
                tmp.clear();
                break;
            }
            else
            {
                if (INST.param.size() != 2)
                {
                    error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
                }
                else if (ind3 != std::uint64_t(-1))
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i2]);
                }
            }
        }
        else if (INST.param[i2].find("FLAGS_") == 0 && INST.param.size() == 3)
        {
            if (INST.param[i2 + 1].find("$\"") == 0)
            {
                std::string tmp = INST.param[i2 + 1];
                std::string tmp2 = INST.param[i2 + 2];
                tmp.erase(0, 2);
                tmp.erase(tmp.size() - 1, 1);
                if (INST.param[i2 + 2].find("$\"") == 0)
                {
                    tmp2.erase(0, 2);
                    tmp2.erase(tmp2.size() - 1, 1);
                }
                else
                {
                    uint64_t ind = STRING_.find_(tmp2);
                    if (ind != std::uint64_t(-1))
                    {
                        tmp2 = STRING_[ind];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i2]);
                    }
                }
                if (STRUCT_.find_(INST.param[i2]) == uint64_t(-1))
                {
                    STRUCT_.createVar(INST.param[i2], std::pair(tmp, tmp2));
                }
                else
                {
                    STRUCT_.redataVar(STRUCT_.find_(INST.param[i2]), std::pair(tmp, tmp2));
                }
            }
            else
            {
                std::string tmp = INST.param[i2 + 1];
                std::string tmp2 = INST.param[i2 + 2];
                uint64_t ind = STRING_.find_(INST.param[i2 + 1]);
                if (ind != std::uint64_t(-1))
                {
                    tmp = STRING_[ind];
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i2]);
                }
                if (INST.param[i2 + 2].find("$\"") == 0)
                {
                    tmp2.erase(0, 2);
                    tmp2.erase(tmp2.size() - 1, 1);
                }
                else
                {
                    ind = STRING_.find_(tmp2);
                    if (ind != std::uint64_t(-1))
                    {
                        tmp2 = STRING_[ind];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i2]);
                    }
                }

                if (STRUCT_.find_(INST.param[i2]) == uint64_t(-1))
                {
                    STRUCT_.createVar(INST.param[i2], std::pair(tmp, tmp2));
                }
                else
                {
                    STRUCT_.redataVar(STRUCT_.find_(INST.param[i2]), std::pair(tmp, tmp2));
                }
            }
            break;
        }
        else
        {
            // DOUBLE variable
            if (DOUBLE_.find_(INST.param[i2]) != std::uint64_t(-1) && INST.param.size() == 2)
            {
                uint64_t ind = DOUBLE_.find_(INST.param[i2]);
                uint64_t ind2 = VEC_STRING_.find_(INST.param[i2]);
                if (INST.param.size() == 2 && ind != std::uint64_t(-1))
                {
                    // std::cout << ind << std::endl;
                    DOUBLE_.redataVar(ind, std::atof(INST.param[i2 + 1].c_str()));
                    break;
                }
                else if (INST.param.size() == 2 && ind2 != std::uint64_t(-1))
                {
                    if (INST.param[i2 + 1].find("$\"") == 0)
                    {
                        std::string tmp = INST.param[i2 + 1];
                        tmp.erase(0, 2);
                        tmp.erase(tmp.size() - 1, 1);
                        INST.param[i2 + 1] = tmp;
                        STRING_.redataVar(ind, INST.param[i2 + 1]);
                        break;
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_UN_PR", "Expected double type");
                }
            }
            else if (DOUBLE_.find_(INST.param[i2]) == std::uint64_t(-1) && INST.param.size() == 2)
            {
                bool num = true;
                for (uint64_t i3 = 0; i3 < INST.param[i2 + 1].size(); ++i3)
                {
                    if (std::isdigit(INST.param[i2 + 1][i3]) == 0)
                    {
                        num = false;
                        break;
                    }
                }
                if (num)
                {
                    DOUBLE_.createVar(INST.param[i2], std::atof(INST.param[i2 + 1].c_str()));
                    break;
                }
                goto j;
            }
            else
            {
            j:
                // STRING variable
                if (INST.param.size() == 2)
                {
                    if (INST.param[i2 + 1].find("$\"") == 0)
                    {
                        std::string tmp = INST.param[i2 + 1];
                        tmp.erase(tmp.find("$\""), 2);
                        tmp.erase(tmp.find("\""), 1);
                        INST.param[i2 + 1] = tmp;
                        STRING_.createVar(INST.param[i2], INST.param[i2 + 1]);
                    }
                    else if (INST.param[i2 + 1].find("${") == 0)
                    {
                        std::string tmp = INST.param[i2 + 1];
                        std::string tmp2__;
                        bool plus = false;
                        tmp.erase(tmp.find("${"), 2);
                        tmp.erase(tmp.find("}"), 1);
                        if (tmp.find("+") != tmp.npos)
                        {
                            tmp2__ = tmp;
                            tmp.erase(tmp.find("+"), tmp.size() - 1);
                            plus = true;
                        }
                        uint64_t ind = STRING_.find_(tmp);
                        if (ind != std::uint64_t(-1))
                        {
                            if (plus)
                            {
                                std::string str;
                                str += STRING_[STRING_.find_(tmp)];
                                tmp2__.erase(0, tmp2__.find("+") + 1);
                                str += STRING_[STRING_.find_(tmp2__)];
                                STRING_.createVar(INST.param[i2], str);
                            }
                            else
                            {
                                STRING_.createVar(INST.param[i2], STRING_[STRING_.find_(tmp)]);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + tmp);
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_UN_EX");
                    }
                    break;
                }
                // VEC_STRING variable
                else if (INST.param.size() > 2)
                {
                    if (VEC_STRING_.find_(INST.param[0]) == std::uint64_t(-1))
                    {
                        std::vector<std::string> tmp_;
                        std::string tmp;
                        for (uint64_t i3 = 1; i3 < INST.param.size(); ++i3)
                        {
                            tmp = INST.param[i3];
                            if (tmp.find("$\"") == 0)
                            {
                                tmp.erase(0, 2);
                                tmp.erase(tmp.size() - 1, 1);
                                tmp_.push_back(tmp);
                            }
                            else if (tmp.find("${") == 0)
                            {
                                tmp.erase(0, 2);
                                tmp.erase(tmp.size() - 1, 1);
                                tmp_.push_back(STRING_[STRING_.find_(tmp)]);
                            }
                            else
                            {
                                uint64_t ind2 = STRING_.find_(tmp);
                                if (ind2 != std::uint64_t(-1))
                                {
                                    tmp_.push_back(STRING_[ind2]);
                                }
                                else
                                {
                                    ind2 = VEC_STRING_.find_(tmp);
                                    if (ind2 != std::uint64_t(-1))
                                    {
                                        for (uint32_t i4 = 0; i4 < VEC_STRING_[ind2].size(); ++i4)
                                        {
                                            tmp_.push_back(VEC_STRING_[ind2][i4]);
                                        }
                                    }
                                    else
                                    {
                                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + tmp);
                                    }
                                }
                            }
                        }
                        VEC_STRING_.createVar(INST.param[0], tmp_);
                        break;
                    }
                    else
                    {
                        std::vector<std::string> tmp_;
                        std::string tmp;
                        for (uint64_t i3 = 1; i3 < INST.param.size(); ++i3)
                        {
                            tmp = INST.param[i3];
                            if (tmp.find("$\"") == 0)
                            {
                                tmp.erase(0, 2);
                                tmp.erase(tmp.size() - 1, 1);
                                tmp_.push_back(tmp);
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_UN_PR", "Expected string type");
                            }
                        }
                        VEC_STRING_.redataVar(VEC_STRING_.find_(INST.param[0]), tmp_);
                        break;
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
                }
            }
        }
    }
}

cdecl inline void set_Language(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] != '$' && INST.param[0][INST.param[0].size() - 1] != '\"')
        {
            std::uint64_t index = project::find_project(INST.param[0]);
            if (index != std::uint64_t(-1))
            {
                bool num = true;
                for (uint64_t i3 = 0; i3 < INST.param[1].size(); ++i3)
                {
                    if (std::isdigit(INST.param[1][i3]) == 0)
                    {
                        if (INST.param[1][i3] == '.' && i3 != 0)
                            continue;
                        num = false;
                        break;
                    }
                }
                if (num)
                {
                    project::project_[index].lang = std::stoi(INST.param[1]);
                }
                else
                {
                    std::uint32_t ind = DOUBLE_.find_(INST.param[1]);
                    if (ind != std::uint32_t(-1))
                    {
                        project::project_[index].lang = DOUBLE_[ind];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                    }
                }
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[0] + std::string(". Does not exist!"));
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expected name variable");
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}