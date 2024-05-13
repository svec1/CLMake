#include "../buildHead.h"

using namespace build;

void build::build(int argc, char *argv[])
{
    std::string pathBuild = std::filesystem::current_path().string();
    variable::STRING_.createVar("CLMAKE_PROJECT_PATH", argv[1]);
    call_to_script(argc, argv);
    redefinition();

    char buf[26];

#if defined _WIN32
    GetLogicalDriveStringsA(sizeof(buf), buf);
#endif
    if (find_compiler)
    {
        _assistant::_debug::debug_msg_call(toString("Find compiler's for " + toString(executable::executables_.size()) + " target!").c_str(), "BUILD", 6);
        for (std::uint32_t i = 0; i < executable::executables_.size(); ++i)
        {
            std::string path = toString(buf[0]) + ":\\";
            std::string file = executable::executables_[i].second.pathCompiler_;
            if (!workFile::getPath().empty())
            {
                workFile::FindFiles(workFile::getPath(), file);
            }
            if (!workFile::find)
            {
                uint32_t x_ = 0;
                while (!workFile::find)
                {
#if defined _WIN32
                    workFile::FindFiles(path, file);
#endif
                    if (!workFile::find)
                    {
                        x_ += 4;
                        if (buf[x_] == ' ')
                            break;
                        path = toString(buf[x_]) + ":\\";
                    }
                    if (!workFile::find)
                        _assistant::_debug::debug_msg_call("\n > File not found", "BUILD", 7);
                    break;
                }
            }
            executable::executables_[i].second.pathCompiler_ = workFile::getPath() + file;
            workFile::val = 0;
            workFile::find = 0;
        }
        _assistant::_debug::debug_msg_call("End of compiler search", "BUILD", 6);
    }
    if (find_linker && compiler != 1)
    {
        _assistant::_debug::debug_msg_call(toString("Find linker's for " + toString(executable::executables_.size()) + " target!").c_str(), "BUILD", 6);
        for (std::uint32_t i = 0; i < executable::executables_.size(); ++i)
        {
            std::string path = toString(buf[0]) + ":\\";
            std::string file = executable::executables_[i].second.pathLinker_;
            if (!workFile::getPath().empty())
            {
                workFile::FindFiles(workFile::getPath(), file);
            }
            if (!workFile::find)
            {
                uint32_t x_ = 0;
                while (!workFile::find)
                {
#if defined _WIN32
                    workFile::FindFiles(path, file);
#endif
                    if (!workFile::find)
                    {
                        x_ += 4;
                        if (buf[x_] == ' ')
                            break;
                        path = toString(buf[x_]) + ":\\";
                    }
                    if (!workFile::find)
                        _assistant::_debug::debug_msg_call("\n > File not found", "BUILD", 7);
                    break;
                }
            }
            executable::executables_[i].second.pathLinker_ = workFile::getPath() + file;
            workFile::val = 0;
            workFile::find = 0;
        }
        _assistant::_debug::debug_msg_call("End of compiler search", "BUILD", 6);
    }
    if (find_arc && compiler != 1)
    {
        std::string path = toString(buf[0]) + ":\\";
        std::string file;

        if (compiler == 0)
        {
            file = archivator__;
        }
        else if (compiler == 1)
        {
            file = "";
        }
        else if (compiler == 2)
        {
            file = "";
        }
        else
        {
            file = archivator__;
        }

        _assistant::_debug::debug_msg_call("Find archivator", "BUILD", 6);
#if defined _WIN32
        workFile::FindFiles(workFile::getPath(), file);
#endif
        if (!workFile::find)
        {
            uint32_t x_ = 0;
            while (!workFile::find)
            {
#if defined _WIN32
                workFile::FindFiles(path, file);
#endif
                if (!workFile::find)
                {
                    x_ += 4;
                    if (buf[x_] == ' ')
                        break;
                    path = toString(buf[x_]) + ":\\";
                }
            }
            if (!workFile::find)
                std::cout << "\n > File not found" << std::endl;
        }
        pathArc_ = workFile::getPath() + file;
        workFile::val = 0;
        workFile::find = 0;
        _assistant::_debug::debug_msg_call("End of archivator search", "BUILD", 6);
    }
    else
    {
        if (pathArc_.empty())
        {
            if (compiler == 0)
            {
                pathArc_ = archivator__;
            }
            else if (compiler == 1)
            {
                pathArc_ = "";
            }
            else if (compiler == 2)
            {
                pathArc_ = "";
            }
            else
            {
                pathArc_ = archivator__;
            }
        }
    }
    if (find_llvmrl && compiler != 1)
    {
        std::string path = toString(buf[0]) + ":\\";
        std::string file;

        if (compiler == 0)
        {
            file = runlib__;
        }
        else if (compiler == 1)
        {
            file = "";
        }
        else if (compiler == 2)
        {
            file = "";
        }
        else
        {
            file = runlib__;
        }

        _assistant::_debug::debug_msg_call("Find runlib", "BUILD", 6);
#if defined _WIN32
        workFile::FindFiles(workFile::getPath(), file);
#endif
        if (!workFile::find)
        {
            uint32_t x_ = 0;
            while (!workFile::find)
            {
#if defined _WIN32
                workFile::FindFiles(path, file);
#endif
                if (!workFile::find)
                {
                    x_ += 4;
                    if (buf[x_] == ' ')
                        break;
                    path = toString(buf[x_]) + ":\\";
                }
            }
            if (!workFile::find)
                std::cout << "\n > File not found" << std::endl;
        }
        pathllvm_ranlib = workFile::getPath() + file;
        workFile::val = 0;
        workFile::find = 0;
        _assistant::_debug::debug_msg_call("End of archivator search", "BUILD", 6);
    }
    else
    {
        if (pathArc_.empty())
        {
            if (compiler == 0)
            {
                pathArc_ = "llvm-ar.exe";
            }
            else if (compiler == 1)
            {
                pathArc_ = "";
            }
            else if (compiler == 2)
            {
                pathArc_ = "";
            }
            else
            {
                pathArc_ = "llvm-ar.exe";
            }
        }
    }
    if (log_)
        _log::log_.exchange(true);
    if (log_)
    {
        _log::log_event(time_() + ": begin build\n");
        _log::log_event(time_() + ": the CLMakeConfig.txt file was successfully parsed. The script has been executed!\n");
    }
    if (versionCLMake < CLMAKE_VERSION)
    {
        if (!scold_VersionCLMake)
        {
            _assistant::_debug::debug_msg_call(toString("CLMAKE VERSION specified: " + toString(versionCLMake) + ", LESS THAN CURRENT(" + toString(CLMAKE_VERSION) + ")!!!").c_str(), "BUILD", 3);
        }
        else
        {
            _assistant::_debug::debug_msg_call(toString("CLMAKE VERSION specified: " + toString(versionCLMake) + ", LESS THAN CURRENT(" + toString(CLMAKE_VERSION) + ")!!!").c_str(), "BUILD", FOREGROUND_RED);
            error__::ERR.callError("FATAL_ERR_MIN_VERSION");
        }
        if (log_)
        {
            _log::log_event(time_() + ": CLMAKE VERSION specified ( " + toString(versionCLMake) + " ), less than current ( " + toString(CLMAKE_VERSION) + " )\n");
        }
    }

    _assistant::_debug::debug_msg_call("All modified \"CLMAKE\" variables by the user have been successfully unzipped!", "BUILD", 6);
#ifdef DEBUG__
    for (uint64_t i = 0; i < executable::executables_.size(); ++i)
    {
        executable::printInfoExe(i);
    }
#endif

    if (log_)
    {
        _log::log_event(time_() + ": Start of cache entry...\n");
    }
    std::ofstream fileCache(pathBuild + "\\CLMakeCache.txt");
    fileCache << "# SET SPECIAL CONFIG VARIABLES -- \n";
    fileCache << "set(CLMAKE_LOGGING " + toString(log_) + ")\n";
    fileCache << "set(CLMAKE_DLL_REG " + toString(regDLL) + ")\n";
    fileCache << "set(CLMAKE_WARNING_PROJECT " + toString(warning) + ")\n";
    fileCache << "set(CLMAKE_USER_TEMPLATE " + toString(user_template) + ")";
    fileCache << "\n\n# SET PATH LIBS -- \n";
    fileCache << "set(__LIBS ";
    for (uint32_t i = 0; i < pathCatalogLibStat.size(); ++i)
    {
        fileCache << "$\"" << pathCatalogLibStat[i] << "\" ";
    }
    fileCache << "$\"NONE\")\n";
    fileCache << "set(__LIBS_DLL ";
    for (uint32_t i = 0; i < pathCatalogLibDLL.size(); ++i)
    {
        fileCache << "$\"" << pathCatalogLibDLL[i] << "\" ";
    }
    fileCache << "$\"NONE\")\n";
    fileCache << "\nset(CLMAKE_PATH_CATOLOG_LIB __LIBS)\n";
    fileCache << "set(CLMAKE_PATH_CATOLOG_DLL __LIBS_DLL)\n\n";
    fileCache << "set(CLMAKE_pathInclude $\"" << pathInclude << "\")\n\n";
    fileCache << "# PATH --\n";
    fileCache << "set(CLMAKE_pathArc $\"" << pathArc_ << "\")\n";
    fileCache << "set(CLMAKE_pathLLVMRL $\"" << pathllvm_ranlib << "\")\n\n";
    fileCache << "# LINKER --\n";
    fileCache << "set(CLMAKE_LINKER " << workLINK << ")\n\n";
    for (uint64_t i = 0; i < oth_commands.size(); ++i)
    {
        fileCache << "call_Command($\"" << oth_commands[i].first << ' ' << "\" " << oth_commands[i].second << ")\n";
    }
    fileCache << "\n";
    for (uint64_t i = 0; i < executable::executables_.size(); ++i)
    {
        fileCache << "create_ConfProject($\"target_" << i << "\")" << '\n';
        std::ofstream fileTarget;
        executable::ENUM_EXE CLASS_ENUM_EXE;
        CLASS_ENUM_EXE.define(executable::executables_[i]);
        if (i < entry_point.size())
        {
            CLASS_ENUM_EXE.def_POE(entry_point[i]);
        }
        fileTarget.open(pathBuild + "\\CLMtarget_" + toString(i) + ".txt");
        // sc - set config
        fileCache << "sc_target($\"target_" << i << "\" $\"" << pathBuild + "\\CLMtarget_" + toString(i) + ".txt\")";
        if (i < executable::executables_.size() - 1)
        {
            fileCache << '\n';
        }
        CLASS_ENUM_EXE.write(fileTarget);
        fileTarget.close();
    }
    if (log_)
    {
        _log::log_event(time_() + ": End of cache entry... Successfully!\n");
    }
    fileCache.close();
    oth_commands.clear();
    _assistant::_debug::debug_msg_call("Serialization was successful. All configurations have been saved(exported) successfully!", "BUILD", 6);
    _log::log_.exchange(0);
}