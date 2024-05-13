#include "function.h"

cdecl inline void create_executable(build::inst &INST)
{
    exe = true;
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] == '$' && INST.param[0][1] == '\"' && INST.param[0][INST.param[0].size() - 1] == '\"')
        {

            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            INST.param[0] = tmp;
            STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), INST.param[0]);
            if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "a wrapper over the executable file with name specified Variable: " + INST.param[0]);
            }
            if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
            {
                std::string tmp = INST.param[1];
                tmp.erase(0, 2);
                tmp.erase(tmp.size() - 1, 1);
                INST.param[1] = tmp;
            }
            else
            {
                if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                {
                    INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                }
            }

            uint64_t index = project::find_project(INST.param[1]);
            if (index != std::uint64_t(-1))
            {
                executable::executables_.push_back(std::pair(INST.param[0], project::project_[index]));
                entry_point.push_back(STRING_[STRING_.find_("CLMAKE_ASM_ENTRYPOINT")]);
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
            }
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {

                STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), STRING_[STRING_.find_(INST.param[0])]);
                if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "a wrapper over the executable file with name specified Variable: " + INST.param[0] + std::string(". Already exists!"));
                }
                if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
                {
                    std::string tmp = INST.param[1];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    INST.param[1] = tmp;
                }
                else
                {
                    if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                    {
                        INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                    }
                }

                uint64_t index = project::find_project(INST.param[1]);
                if (index != std::uint64_t(-1))
                {
                    executable::executables_.push_back(std::pair(STRING_[STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME")], project::project_[index]));
                    entry_point.push_back(STRING_[STRING_.find_("CLMAKE_ASM_ENTRYPOINT")]);
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
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

cdecl inline void create_Library(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] == '$' && INST.param[0][1] == '\"' && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            INST.param[0] = tmp;
            STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), INST.param[0]);
            if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "a wrapper over the executable file with name specified Variable: " + INST.param[0] + std::string(". Already exists!"));
            }
            if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
            {
                std::string tmp = INST.param[1];
                tmp.erase(0, 2);
                tmp.erase(tmp.size() - 1, 1);
                INST.param[1] = tmp;
            }
            else
            {
                if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                {
                    INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                }
            }

            uint64_t index = project::find_project(INST.param[1]);
            if (index != std::uint64_t(-1))
            {
                executable::executables_.push_back(std::pair("<LIB>" + INST.param[0], project::project_[index]));
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
            }
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {
                STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), STRING_[STRING_.find_(INST.param[0])]);
                if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "a wrapper over the executable file with name specified Variable: " + INST.param[0]);
                    exit(10);
                }
                if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
                {
                    std::string tmp = INST.param[1];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    INST.param[1] = tmp;
                }
                else
                {
                    if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                    {
                        INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                    }
                }

                uint64_t index = project::find_project(INST.param[1]);
                if (index != std::uint64_t(-1))
                {
                    executable::executables_.push_back(std::pair("<LIB>" + STRING_[STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME")], project::project_[index]));
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
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

cdecl inline void create_Dynamic_Library(build::inst &INST)
{
    if (INST.param.size() == 2)
    {
        if (INST.param[0][0] == '$' && INST.param[0][1] == '\"' && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            INST.param[0] = tmp;
            STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), INST.param[0]);
            if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "a wrapper over the executable file with name specified Variable: " + INST.param[0]);
            }
            if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
            {
                std::string tmp = INST.param[1];
                tmp.erase(0, 2);
                tmp.erase(tmp.size() - 1, 1);
                INST.param[1] = tmp;
            }
            else
            {
                if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                {
                    INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                }
            }

            uint64_t index = project::find_project(INST.param[1]);
            if (index != std::uint64_t(-1))
            {
                executable::executables_.push_back(std::pair("<DLL>" + INST.param[0], project::project_[index]));
                entry_point.push_back(STRING_[STRING_.find_("CLMAKE_ASM_ENTRYPOINT")]);
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
            }
        }
        else
        {
            if (STRING_.find_(INST.param[0]) != std::uint64_t(-1))
            {

                STRING_.redataVar(STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME"), STRING_[STRING_.find_(INST.param[0])]);
                if (executable::find_exe(INST.param[0]) != std::uint64_t(-1))
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "a wrapper over the executable file with name specified Variable: " + INST.param[0]);
                }
                if (INST.param[1][0] == '$' && INST.param[1][1] == '\"' && INST.param[1][INST.param[1].size() - 1] == '\"')
                {
                    std::string tmp = INST.param[1];
                    tmp.erase(0, 2);
                    tmp.erase(tmp.size() - 1, 1);
                    INST.param[1] = tmp;
                }
                else
                {
                    if (STRING_.find_(INST.param[1]) != std::uint64_t(-1))
                    {
                        INST.param[1] = STRING_[STRING_.find_(INST.param[1])];
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
                    }
                }

                uint64_t index = project::find_project(INST.param[1]);
                if (index != std::uint64_t(-1))
                {
                    executable::executables_.push_back(std::pair("<DLL>" + STRING_[STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME")], project::project_[index]));
                    entry_point.push_back(STRING_[STRING_.find_("CLMAKE_ASM_ENTRYPOINT")]);
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "project(wrapper) with name: " + INST.param[1] + std::string(". Does not exist!"));
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