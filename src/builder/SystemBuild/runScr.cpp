#include "../buildHead.h"
#include "func/function.h"

namespace build
{
    void definedVAR_CLMAKE()
    {
        using namespace variable;

        DOUBLE_.createVar(std::string("CLMAKE_minimal_version"), versionCLMake);
        DOUBLE_.createVar(std::string("CLMAKE_C_STANDART"), C_STANDART);     //
        DOUBLE_.createVar(std::string("CLMAKE_CPP_STANDART"), CPP_STANDART); //
        DOUBLE_.createVar(std::string("CLMAKE_WARNING_PROJECT"), warning);
        DOUBLE_.createVar(std::string("CLMAKE_LOGGING"), log_);
        DOUBLE_.createVar(std::string("CLMAKE_DLL_REG"), regDLL);
        DOUBLE_.createVar(std::string("CLMAKE_FIND_COMPILER"), find_compiler);
        DOUBLE_.createVar(std::string("CLMAKE_FIND_LINKER"), find_linker);
        DOUBLE_.createVar(std::string("CLMAKE_FIND_ARC"), find_arc);
        DOUBLE_.createVar(std::string("CLMAKE_FIND_LLVMRL"), find_llvmrl);
        DOUBLE_.createVar(std::string("CLMAKE_LINKER"), workLINK);
        STRING_.createVar(std::string("CLMAKE_pathCompiler"), pathCompiler_);
        STRING_.createVar(std::string("CLMAKE_pathLinker"), pathLinker_);
        STRING_.createVar(std::string("CLMAKE_pathArc"), pathArc_);
        STRING_.createVar(std::string("CLMAKE_pathLLVMRL"), pathllvm_ranlib);
        STRING_.createVar(std::string("CLMAKE_pathInclude"), pathInclude);                   //
        STRING_.createVar(std::string("CLMAKE_flags_compile"), standartClmakeCompilerFlags); //
        STRING_.createVar(std::string("CLMAKE_LinkFlags"), standartClmakeLinkerFlags);       //
        STRING_.createVar(std::string("CLMAKE_PROJECT_NAME"), NameProject);                  //
        STRING_.createVar(std::string("CLMAKE_EXE_NAME"), NameProject);                      //
        STRING_.createVar(std::string("CLMAKE_ASM_ENTRYPOINT"), "");                         //
        STRING_.createVar(std::string("CLMAKE_FILE_EXECUTABLE_NAME"), NameExecutable);       //
        STRING_.createVar(std::string("CLMAKE_ARCHIVATOR_C_CPP"), archivator__);
        STRING_.createVar(std::string("CLMAKE_RUNLIB_C_CPP"), runlib__);
        DOUBLE_.createVar(std::string("CLMAKE_LANG"), compiler);
        VEC_STRING_.createVar(std::string("CLMAKE_SrcFiles"), SrcFiles);
        // VEC_STRING_.createVar(std::string("CLMAKE_LibFiles"), LibFiles);
        // VEC_STRING_.createVar(std::string("CLMAKE_DllFiles"), DllFiles);
        VEC_STRING_.createVar(std::string("CLMAKE_PATH_CATOLOG_LIB"), pathCatalogLibStat); //
        VEC_STRING_.createVar(std::string("CLMAKE_PATH_CATOLOG_DLL"), pathCatalogLibDLL);  //

        DOUBLE_.createVar(std::string("CLMAKE_USER_TEMPLATE"), user_template);
    }
    void redefinition()
    {
        using namespace variable;

        versionCLMake = DOUBLE_[DOUBLE_.find_("CLMAKE_minimal_version")];
        C_STANDART = DOUBLE_[DOUBLE_.find_("CLMAKE_C_STANDART")];
        CPP_STANDART = DOUBLE_[DOUBLE_.find_("CLMAKE_CPP_STANDART")];
        warning = DOUBLE_[DOUBLE_.find_("CLMAKE_WARNING_PROJECT")];
        log_ = DOUBLE_[DOUBLE_.find_("CLMAKE_LOGGING")];
        regDLL = DOUBLE_[DOUBLE_.find_("CLMAKE_DLL_REG")];
        find_compiler = DOUBLE_[DOUBLE_.find_("CLMAKE_FIND_COMPILER")];
        find_linker = DOUBLE_[DOUBLE_.find_("CLMAKE_FIND_LINKER")];
        find_arc = DOUBLE_[DOUBLE_.find_("CLMAKE_FIND_ARC")];
        pathArc_ = STRING_[STRING_.find_("CLMAKE_pathArc")];
        standartClmakeCompilerFlags = STRING_[STRING_.find_("CLMAKE_flags_compile")];
        NameProject = STRING_[STRING_.find_("CLMAKE_PROJECT_NAME")]; //*
        NameExecutable = STRING_[STRING_.find_("CLMAKE_FILE_EXECUTABLE_NAME")];
        SrcFiles = VEC_STRING_[VEC_STRING_.find_("CLMAKE_SrcFiles")]; //*
        standartClmakeLinkerFlags = STRING_[STRING_.find_("CLMAKE_LinkFlags")];
        pathCatalogLibStat = VEC_STRING_[VEC_STRING_.find_("CLMAKE_PATH_CATOLOG_LIB")];
        pathCatalogLibDLL = VEC_STRING_[VEC_STRING_.find_("CLMAKE_PATH_CATOLOG_DLL")];
        compiler = DOUBLE_[DOUBLE_.find_("CLMAKE_LANG")];
        workLINK = DOUBLE_[DOUBLE_.find_("CLMAKE_LINKER")];
        find_llvmrl = DOUBLE_[DOUBLE_.find_("CLMAKE_FIND_LLVMRL")];
        pathllvm_ranlib = STRING_[STRING_.find_("CLMAKE_pathLLVMRL")];
        pathInclude = STRING_[STRING_.find_("CLMAKE_pathInclude")];
        user_template = DOUBLE_[DOUBLE_.find_("CLMAKE_USER_TEMPLATE")];
        if (STRING_[STRING_.find_("CLMAKE_ARCHIVATOR_C_CPP")] != archivator__)
        {
            archivator__ = STRING_[STRING_.find_("CLMAKE_ARCHIVATOR_C_CPP")];
        }
        if (STRING_[STRING_.find_("CLMAKE_RUNLIB_C_CPP")] != runlib__)
        {
            runlib__ = STRING_[STRING_.find_("CLMAKE_RUNLIB_C_CPP")];
        }
    }
    void runSCRIPT(std::vector<inst> INST)
    {
        using namespace variable;

        definedVAR_CLMAKE();
        for (uint32_t i = 0; i < INST.size(); ++i)
        {
            // set - 0 opcode
            if (INST[i].opCode == 0)
            {
                set(INST[i]);
            }
            // project - 1 opcode
            else if (!assembly__ && INST[i].opCode == 1)
            {
                _project(INST[i]);
            }
            // create_executable - 2 opcode
            else if (!assembly__ && INST[i].opCode == 2)
            {
                create_executable(INST[i]);
            }
            // create_Library - 3 opcode
            else if (!assembly__ && INST[i].opCode == 3)
            {
                create_Library(INST[i]);
            }
            // create_Dynamic_Library - 4 opcode
            else if (!assembly__ && INST[i].opCode == 4)
            {
                create_Dynamic_Library(INST[i]);
            }
            // link_Library - 5 opcode
            else if (!assembly__ && INST[i].opCode == 5)
            {
                link_Library(INST[i]);
            }
            // link_Dynamic_Library - 5 opcode
            else if (!assembly__ && INST[i].opCode == 6)
            {
                link_Dynamic_Library(INST[i]);
            }

            // call_Command - 6 opcode
            else if (INST[i].opCode == 7 || (assembly__ && INST[i].opCode == 3))
            {
                call_Command(INST[i]);
            }

            // include_File - 7 opcode
            else if (INST[i].opCode == 8)
            {
                include_File(INST[i]);
            }

            // parse_File - 8 opcode
            else if (INST[i].opCode == 9)
            {
                parse_File(INST[i]);
            }

            // export_VarFile - 9 opcode
            else if (INST[i].opCode == 10)
            {
                export_VarFile(INST[i]);
            }

            // add_flags - 10 opcode
            else if (INST[i].opCode == 11)
            {
                add_flags(INST[i]);
            }

            // debug - 11 opcode
            else if (INST[i].opCode == 12)
            {
                debug(INST[i]);
            }

            // add_standart_C - 12 opcode
            else if (INST[i].opCode == 13)
            {
                add_standart_C(INST[i]);
            }

            // add_standart_CPP - 13 opcode
            else if (INST[i].opCode == 14)
            {
                add_standart_CPP(INST[i]);
            }

            // add_AdditionalParam - 14 opcode
            else if (INST[i].opCode == 15)
            {
                add_AdditionalParam(INST[i]);
            }

            // use_Templates - 15 opcode
            else if (INST[i].opCode == 16)
            {
                use_Templates(INST[i]);
            }

            // uw_Templates - 16 opcode
            else if (INST[i].opCode == 17)
            {
                uw_Templates(INST[i]);
            }

            // add_PathCompiler - 17 opcode
            else if (INST[i].opCode == 18)
            {
                add_PathCompiler(INST[i]);
            }

            // add_PathLinker - 18 opcode
            else if (INST[i].opCode == 19)
            {
                add_PathLinker(INST[i]);
            }

            // set_Language - 19 opcode
            else if (INST[i].opCode == 20)
            {
                set_Language(INST[i]);
            }

            // create_ConfProject
            else if (assembly__ && INST[i].opCode == 1)
            {
                create_ConfProject(INST[i]);
            }
            // sc_target
            else if (assembly__ && INST[i].opCode == 2)
            {
                sc_target(INST[i]);
            }
            else
            {
            }
        }
    }

    void call_to_script(int argc, char *argv[])
    {
        std::string CLMakeConfing_ = argv[1];
        CLMakeConfing_ += "\\CLMakeConfig.txt";
        std::ifstream CLMakeConfing(CLMakeConfing_);
        std::vector<inst> INSTRUCTION;
        std::string tmp;
        char tmp_ = ' ';
        parser PARSER;
        COMMAND.emplace(0, "set");
        COMMAND.emplace(1, "project");
        COMMAND.emplace(2, "create_Executable");
        COMMAND.emplace(3, "create_Library");
        COMMAND.emplace(4, "create_Dynamic_Library");
        COMMAND.emplace(5, "link_Library");
        COMMAND.emplace(6, "link_Dynamic_Library");
        COMMAND.emplace(7, "call_Command");
        COMMAND.emplace(8, "include_File");
        COMMAND.emplace(9, "parse_File");
        COMMAND.emplace(10, "export_VarFile");
        COMMAND.emplace(11, "add_flags");
        COMMAND.emplace(12, "debug");
        COMMAND.emplace(13, "add_standart_C");
        COMMAND.emplace(14, "add_standart_CPP");
        COMMAND.emplace(15, "add_AdditionalParam");
        COMMAND.emplace(16, "use_Templates");
        COMMAND.emplace(17, "uw_Templates");
        COMMAND.emplace(18, "add_PathCompiler");
        COMMAND.emplace(19, "add_PathLinker");
        COMMAND.emplace(20, "set_Language");
        if (!CLMakeConfing.is_open())
        {
            std::cout << "there is no file in the specified directory CLMakeConfig.txt" << std::endl;
            exit(12);
        }
        PARSER.set_vecComm(COMMAND);

        bool sk = false;

        while (!CLMakeConfing.eof())
        {
            while (tmp_ != '\n')
            {
                CLMakeConfing.get(tmp_);

                if (tmp_ == '\"')
                {
                    if (sk)
                    {
                        sk = false;
                    }
                    else
                    {
                        sk = true;
                    }
                }

                if (tmp_ == '#' && sk == false)
                {
                    while (tmp_ != '\n')
                    {
                        CLMakeConfing.get(tmp_);
                    }
                    tmp_ = ' ';
                    tmp.clear();
                    continue;
                }
                if (tmp_ == '\n' && tmp.size() == 0)
                {
                    if (!CLMakeConfing.eof())
                    {
                        tmp_ = ' ';
                        continue;
                    }
                }
                tmp += tmp_;
                if (CLMakeConfing.eof())
                {
                    if (tmp.size() == 1 && (tmp == " " || tmp == "\n"))
                    {
                        goto endParser;
                    }
                    tmp.erase(tmp.size() - 1, 1);
                    goto pars;
                }
            }
        pars:
            tmp_ = ' ';
            INSTRUCTION.push_back(PARSER.pars(tmp));
            tmp.clear();
        }
    endParser:
        _assistant::_debug::debug_msg_call(toString("File was parsed successfully!").c_str(), "BUILD", 6);
#ifdef DEBUG__
        for (uint64_t i = 0; i < INSTRUCTION.size(); ++i)
        {
            std::cout << INSTRUCTION[i].opCode;
            for (uint32_t i2 = 0; i2 < INSTRUCTION[i].param.size(); ++i2)
            {
                std::cout << " - " << INSTRUCTION[i].param[i2];
            }
            std::cout << '\n';
        }
#endif
        runSCRIPT(INSTRUCTION);
        _assistant::_debug::debug_msg_call(toString("The script was successfully executed!").c_str(), "BUILD", 6);
    }
}