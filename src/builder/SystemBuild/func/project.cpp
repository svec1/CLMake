#include "function.h"

cdecl inline void _project(build::inst &INST)
{
    if (INST.param.size() >= 2)
    {
        // set PROJECT NAME is value string
        if (INST.param[0][0] == '$' && INST.param[0][1] == '\"' && INST.param[0][INST.param[0].size() - 1] == '\"')
        {
            std::string tmp = INST.param[0];
            std::vector<std::string> tmpVec;

            tmp.erase(0, 2);
            tmp.erase(tmp.size() - 1, 1);
            INST.param[0] = tmp;
            STRING_.redataVar(STRING_.find_("CLMAKE_PROJECT_NAME"), INST.param[0]);
            for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
            {
                if (VEC_STRING_.find_(INST.param[i3]) != std::uint64_t(-1))
                {
                    for (uint32_t i4 = 0; i4 < VEC_STRING_[VEC_STRING_.find_(INST.param[i3])].size(); ++i4)
                    {
                        tmpVec.push_back(VEC_STRING_[VEC_STRING_.find_(INST.param[i3])][i4]);
                    }
                }
                else if (STRING_.find_(INST.param[i3]) != std::uint64_t(-1))
                {
                    tmpVec.push_back(STRING_[STRING_.find_(INST.param[i3])]);
                }
            }

            VEC_STRING_.redataVar(VEC_STRING_.find_("CLMAKE_SrcFiles"), tmpVec);

#ifdef DEBUG__
            std::cout << "Name project set is value - " << INST.param[0] << std::endl;
#endif
        }
        else
        {
            // set PROJECT NAME is value variable string
            if (INST.param[0][0] != '$' && INST.param[0][1] != '\"' && INST.param[0][INST.param[0].size() - 1] != '\"')
            {
                std::vector<std::string> tmpVec;

                STRING_.redataVar(STRING_.find_("CLMAKE_PROJECT_NAME"), STRING_[STRING_.find_(INST.param[0])]);
                for (uint32_t i3 = 1; i3 < INST.param.size(); ++i3)
                {
                    if (VEC_STRING_.find_(INST.param[i3]) != std::uint64_t(-1))
                    {
                        for (uint32_t i4 = 0; i4 < VEC_STRING_[VEC_STRING_.find_(INST.param[i3])].size(); ++i4)
                        {
                            tmpVec.push_back(VEC_STRING_[VEC_STRING_.find_(INST.param[i3])][i4]);
                        }
                    }
                    else if (STRING_.find_(INST.param[i3]) != std::uint64_t(-1))
                    {
                        tmpVec.push_back(STRING_[STRING_.find_(INST.param[i3])]);
                    }
                }

                VEC_STRING_.redataVar(VEC_STRING_.find_("CLMAKE_SrcFiles"), tmpVec);
#ifdef DEBUG__
                std::cout << "Name project set is value - " << STRING_[STRING_.find_(INST.param[0])] << std::endl;
#endif
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_UN_EX");
            }
        }
        if (project::find_project(STRING_[STRING_.find_("CLMAKE_PROJECT_NAME")]) == std::uint64_t(-1))
        {
            project::project__ tmp;
            tmp.NameProject = STRING_[STRING_.find_("CLMAKE_PROJECT_NAME")];
            tmp.src_file = VEC_STRING_[VEC_STRING_.find_("CLMAKE_SrcFiles")];
            tmp.flags = "<COMPILE>" + STRING_[STRING_.find_("CLMAKE_flags_compile")] + "<LINK>" + STRING_[STRING_.find_("CLMAKE_LinkFlags")];
            tmp.CStandart = DOUBLE_[DOUBLE_.find_("CLMAKE_C_STANDART")];
            tmp.CPPStandart = DOUBLE_[DOUBLE_.find_("CLMAKE_CPP_STANDART")];
            tmp.StaticLibrary = std::vector<std::string>();
            tmp.DynamicLibrary = std::vector<std::string>();
            tmp.lang = 0;
            tmp.pathCompiler_ = "clang.exe";
            tmp.pathLinker_ = "clang.exe";
            project::project_.push_back(tmp);
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "project with name specified Variable: " + STRING_[STRING_.find_("CLMAKE_PROJECT_NAME")]);
        }
    }
    else
    {
        error__::ERR.callError("FATAL_ERR_UNDEF_PARAM", "Count param: " + toString(INST.param.size()) + std::string(". Expected min 2"));
    }
}