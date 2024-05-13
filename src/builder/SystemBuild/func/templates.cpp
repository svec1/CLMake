#include "function.h"

cdecl inline void add_AdditionalParam(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        // AD_PARAM
        if (INST.param[0][0] == '$' && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expected name variable");
        }
        if (INST.param[1][0] == '$' && INST.param[1][INST.param[1].size() - 1] == '\"')
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expected name variable");
        }
        std::uint64_t ind = DOUBLE_.find_(INST.param[1]);
        if (ind == std::uint64_t(-1))
        {
            ind = STRING_.find_(INST.param[1]);
            if (ind == std::uint64_t(-1))
            {
                ind = VEC_STRING_.find_(INST.param[1]);
                if (ind == std::uint64_t(-1))
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                }
            }
        }
        if (AD_PARAM.find_(INST.param[0]) != std::uint64_t(-1))
        {
            AD_PARAM.redataVar(AD_PARAM.find_(INST.param[0]), INST.param[1]);
        }
        else
        {
            AD_PARAM.createVar(INST.param[0], INST.param[1]);
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}

cdecl inline void use_Templates(build::inst &INST)
{
    if (INST.param.size() >= 2)
    {
        if (INST.param[0][0] != '$' && INST.param[0][INST.param[0].size() - 1] != '\"')
        {
            std::vector<std::string> tmpVector;
            std::uint64_t index = project::find_project(INST.param[0]);
            if (index != std::uint64_t(-1))
            {
                for (std::uint64_t i2 = 1; i2 < INST.param.size(); ++i2)
                {
                    if (INST.param[i2][0] == '$' && INST.param[i2][INST.param[i2].size() - 1] == '\"')
                    {
                        INST.param[i2].erase(0, 2);
                        INST.param[i2].erase(INST.param[i2].size() - 1, 1);
                        tmpVector.push_back(INST.param[i2]);
                    }
                    else
                    {
                        std::uint64_t index_ = STRING_.find_(INST.param[i2]);
                        if (index_ != std::uint64_t(-1))
                        {
                            tmpVector.push_back(STRING_[index_]);
                        }
                        else
                        {
                            index_ = VEC_STRING_.find_(INST.param[i2]);
                            if (index_ != std::uint64_t(-1))
                            {
                                for (std::uint64_t i3 = 0; i3 < VEC_STRING_[index_].size(); ++i3)
                                {
                                    tmpVector.push_back(VEC_STRING_[i2][i3]);
                                }
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[i2]);
                            }
                        }
                    }
                }
                project::project_[index].userTemplates = tmpVector;
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
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
    }
}

cdecl inline void uw_Templates(build::inst &INST)
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
                    project::project_[index].userTemplate = std::stoi(INST.param[1].c_str());
                }
                else
                {
                    std::uint64_t index_ = DOUBLE_.find_(INST.param[1]);
                    if (index_ != std::uint64_t(-1))
                    {
                        project::project_[index].userTemplate = DOUBLE_[index_];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
                    }
                }
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