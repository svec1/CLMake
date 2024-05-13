#include "function.h"

cdecl inline void add_standart_C(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        double standartC;

        if (INST.param[0].find("$\"") == 0)
        {

            INST.param[0].erase(0, 2);
            INST.param[0].erase(INST.param[0].size() - 1, 1);
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {
                INST.param[0] = STRING_[STRING_.find_(INST.param[0])];
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }

        uint64_t index = project::find_project(INST.param[0]);

        if (index == std::uint64_t(-1))
        {
            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
        }

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
            standartC = std::atof(INST.param[1].c_str());
        }
        else
        {
            uint64_t ind = DOUBLE_.find_(INST.param[1]);
            if (ind != std::uint64_t(-1))
            {
                standartC = DOUBLE_[ind];
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
            }
        }

        project::project_[index].CStandart = standartC;
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}
cdecl inline void add_standart_CPP(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        double standartCPP;

        if (INST.param[0].find("$\"") == 0)
        {

            INST.param[0].erase(0, 2);
            INST.param[0].erase(INST.param[0].size() - 1, 1);
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {
                INST.param[0] = STRING_[STRING_.find_(INST.param[0])];
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }

        uint64_t index = project::find_project(INST.param[0]);

        if (index == std::uint64_t(-1))
        {
            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
        }

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
            standartCPP = std::atof(INST.param[1].c_str());
        }
        else
        {
            uint64_t ind = DOUBLE_.find_(INST.param[1]);
            if (ind != std::uint64_t(-1))
            {
                standartCPP = DOUBLE_[ind];
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
            }
        }

        project::project_[index].CPPStandart = standartCPP;
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}

cdecl inline void add_flags(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        std::string flags_compile;
        std::string flags_linker;

        if (INST.param[0].find("$\"") == 0)
        {

            INST.param[0].erase(0, 2);
            INST.param[0].erase(INST.param[0].size() - 1, 1);
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {
                INST.param[0] = STRING_[STRING_.find_(INST.param[0])];
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[0]);
            }
        }

        uint64_t index = project::find_project(INST.param[0]);

        if (index == std::uint64_t(-1))
        {
            error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
        }

        if (INST.param[1].find("$\"") != 0)
        {
            uint64_t ind = STRUCT_.find_(INST.param[1]);
            if (ind != std::uint64_t(-1))
            {
                flags_compile = STRUCT_[ind].first;
                flags_linker = STRUCT_[ind].second;
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Name specified Variable: " + INST.param[1]);
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_UN_PR", "Expecting a reference to a string variable");
        }

        project::project_[index].flags = "<COMPILE>" + flags_compile + "<LINK>" + flags_linker;
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected 2"));
    }
}

cdecl inline void add_PathCompiler(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] != '$' && INST.param[0][INST.param[0].size() - 1] != '\"')
        {
            std::uint64_t index = project::find_project(INST.param[0]);
            if (index != std::uint64_t(-1))
            {
                if (INST.param[1][0] == '$' && INST.param[1][INST.param[1].size() - 1] == '\"')
                {
                    INST.param[1].erase(0, 2);
                    INST.param[1].erase(INST.param[1].size() - 1, 1);
                    project::project_[index].pathCompiler_ = INST.param[1];
                }
                else
                {
                    std::uint32_t ind = STRING_.find_(INST.param[1]);
                    if (ind != std::uint32_t(-1))
                    {
                        project::project_[index].pathCompiler_ = STRING_[ind];
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
cdecl inline void add_PathLinker(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] != '$' && INST.param[0][INST.param[0].size() - 1] != '\"')
        {
            std::uint64_t index = project::find_project(INST.param[0]);
            if (index != std::uint64_t(-1))
            {
                if (INST.param[1][0] == '$' && INST.param[1][INST.param[1].size() - 1] == '\"')
                {
                    INST.param[1].erase(0, 2);
                    INST.param[1].erase(INST.param[1].size() - 1, 1);
                    project::project_[index].pathLinker_ = INST.param[1];
                }
                else
                {
                    std::uint32_t ind = STRING_.find_(INST.param[1]);
                    if (ind != std::uint32_t(-1))
                    {
                        project::project_[index].pathLinker_ = STRING_[ind];
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
        error__::ERR.callError("FATAL_ERR_UN_PR", "Expected name variable");
    }
}