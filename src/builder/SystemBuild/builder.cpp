#include "../buildHead.h"

using namespace build;

namespace build
{
    void assembly(int argc, char *argv[])
    {
        std::string pathBuild = std::filesystem::current_path().string();

        std::ifstream fileCLMCache(pathBuild + "\\CLMakeCache.txt");
        if (!fileCLMCache.is_open())
        {
            _assistant::_error_hand::errorSB_create("FATAL_ERR_FILE_OPEN", toString("The file was not found or opened - " + pathBuild + "\\CLMakeCache.txt").c_str(), 1);
        }

        std::vector<inst> INSTRUCTION;
        parser PARSER;

        std::string tmp;
        char tmp_ = ' ';

        assembly__ = true;

        COMMAND.clear();
        COMMAND.emplace(0, "set");
        COMMAND.emplace(1, "create_ConfProject");
        COMMAND.emplace(2, "sc_target");
        COMMAND.emplace(3, "call_Command");
        PARSER.set_vecComm(COMMAND);

        bool sk = false;

        while (!fileCLMCache.eof())
        {
            while (tmp_ != '\n')
            {
                fileCLMCache.get(tmp_);
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
                        fileCLMCache.get(tmp_);
                    }
                    tmp_ = ' ';
                    tmp.clear();
                    continue;
                }
                if (tmp_ == '\n' && tmp.size() == 0)
                {
                    tmp_ = ' ';
                    continue;
                }
                tmp += tmp_;
                if (fileCLMCache.eof())
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
        _assistant::_debug::debug_msg_call("File was parsed successfully!", "PARSER", 6);
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
        redefinition();
        _assistant::_debug::debug_msg_call("The script was successfully executed!", "PARSER", 6);
        if (log_)
            _log::log_.exchange(true);
        if (log_)
        {
            _log::log_event(time_() + ": start of assembly\n");
            _log::log_event(time_() + ": the CLMakeConfig.txt file was successfully parsed. The script has been executed!\n");
        }

        std::string command_linker;
        std::vector<std::string> tempObj;
        std::vector<std::string> commandCompiler;
        std::string pathTarget;

        std::filesystem::create_directory(pathBuild + "\\tmp");

        // create command for compiler(clang) c/c++

        for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
        {
            if (oth_commands[i3].second == 0)
            {
                system(oth_commands[i3].first.c_str());
            }
        }
        for (uint64_t i = 0; i < variable::TARGETS_.size() - 1; ++i)
        {
            _assistant::_debug::debug_msg_call(toString("---------- " + toString(i) + " TARGET " + "----------").c_str(), "ASSEMBLY", FOREGROUND_RED);
            _log::log_event(time_() + ": ------------------------- TARGET: " + toString(i).c_str() + " START BUILD ---------------------------------\n");
            pathTarget = pathBuild + "\\tmp\\target" + toString(i);
            std::filesystem::create_directory(pathTarget);
            if (variable::TARGETS_[i].second.get().second.userTemplate)
            {
                for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.userTemplates.size(); ++i2)
                {
                    if (variable::templateGenerate.find_(variable::TARGETS_[i].second.get().second.userTemplates[i2]) == std::uint64_t(-1))
                    {
                        error__::ERR.callError("FATAL_ERR_TEMPLATE_U", "Not found a template - " + variable::TARGETS_[i].second.get().second.userTemplates[i2]);
                    }
                }

                for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.userTemplates.size(); ++i2)
                {
                    std::uint64_t index = variable::templateGenerate.find_(variable::TARGETS_[i].second.get().second.userTemplates[i2]);
                    for (uint32_t i3 = 0; i3 < variable::templateGenerate[index].size(); ++i3)
                    {
                        if (variable::AD_PARAM.find_(variable::templateGenerate[index][i3]) == std::uint64_t(-1))
                        {
                            error__::ERR.callError("FATAL_ERR_OBJ_PARAM", "Not found a param expected template. Param - " + variable::templateGenerate[index][i3] + " Template - " + variable::templateGenerate.get_name(index));
                        }
                    }
                }

                for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.userTemplates.size(); ++i2)
                {
                    std::string command = "";
                    std::uint64_t index = variable::templateGenerate.find_(variable::TARGETS_[i].second.get().second.userTemplates[i2]);
                    for (std::uint32_t i3 = 0; i3 < variable::templateGenerate[index].size(); ++i3)
                    {
                        command += variable::AD_PARAM[variable::AD_PARAM.find_(variable::templateGenerate[index][i3])];
                        if (i3 < variable::templateGenerate[index].size())
                            command += ' ';
                    }
                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 1)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }
                    if (log_)
                    {
                        _log::log_event(time_() + ": The command was generated: " + command + '\n');
                    }
                    system(command.c_str());
                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 2)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }
                }
            }
            else
            {
                if (variable::TARGETS_[i].second.get().second.lang == 0)
                {
                    pathCompiler_ = variable::TARGETS_[i].second.get().second.pathCompiler_;
                    pathLinker_ = variable::TARGETS_[i].second.get().second.pathLinker_;
                    for (uint64_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i2)
                    {
                        if (variable::TARGETS_[i].second.get().second.src_file[i2].find(".h") == variable::TARGETS_[i].second.get().second.src_file[i2].size() - 2)
                        {
                            continue;
                        }
                        else if (variable::TARGETS_[i].second.get().second.src_file[i2].find("*.cpp") != variable::TARGETS_[i].second.get().second.src_file[i2].npos || variable::TARGETS_[i].second.get().second.src_file[i2].find("*.c") != variable::TARGETS_[i].second.get().second.src_file[i2].npos)
                        {
                            variable::TARGETS_[i].second.get().second.src_file[i2].erase(variable::TARGETS_[i].second.get().second.src_file[i2].find("*.cpp"), 5);
                            std::string path = variable::TARGETS_[i].second.get().second.src_file[i2];
                            variable::TARGETS_[i].second.get().second.src_file.pop_back();
                            for (auto &p : std::filesystem::directory_iterator(path))
                            {
                                std::filesystem::path tmp;
                                tmp = p;
                                variable::TARGETS_[i].second.get().second.src_file.push_back(tmp.generic_string());
                            }
                        }
                        std::filesystem::path fileSource = std::filesystem::temp_directory_path() / variable::TARGETS_[i].second.get().second.src_file[i2];
                        std::filesystem::path fileCache = std::filesystem::temp_directory_path() / (pathBuild + "\\CLMakeCache.txt");
                        std::ifstream{fileSource.c_str()};
                        std::ifstream{fileCache.c_str()};
                        std::ifstream objectFiles(pathTarget + "\\obj" + toString(i2) + ".o");

                        std::filesystem::file_time_type ftime = std::filesystem::last_write_time(fileSource);
                        std::filesystem::file_time_type fctime = std::filesystem::last_write_time(fileCache);
                        if (objectFiles.is_open())
                        {
                            objectFiles.close();
                            std::filesystem::path fileObject = std::filesystem::temp_directory_path() / (pathTarget + "\\obj" + toString(i2) + ".o");
                            std::ifstream{fileObject.c_str()};
                            std::filesystem::file_time_type ftime2 = std::filesystem::last_write_time(fileObject);
                            if (ftime2 < fctime)
                            {
                                if (variable::TARGETS_[i].second.get().second.src_file[i2].find(".cpp") == (variable::TARGETS_[i].second.get().second.src_file[i2].size() - 4))
                                {
                                    if (!pathInclude.empty())
                                        commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                    else
                                        commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                }
                                else
                                {
                                    if (!pathInclude.empty())
                                        commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                    else
                                        commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                }
                                tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".o");
                                if (log_)
                                {
                                    _log::log_event(time_() + ": The compiler command was generated: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                }
                            }
                            else
                            {
                                if (ftime > ftime2)
                                {
                                    if (variable::TARGETS_[i].second.get().second.src_file[i2].find(".cpp") == (variable::TARGETS_[i].second.get().second.src_file[i2].size() - 4))
                                    {
                                        if (!pathInclude.empty())
                                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                        else
                                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                    }
                                    else
                                    {
                                        if (!pathInclude.empty())
                                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                        else
                                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                    }
                                    tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".o");
                                    if (log_)
                                    {
                                        _log::log_event(time_() + ": The compiler command was generated: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                    }
                                }
                                else if (ftime < ftime2)
                                {
                                    tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".o");
                                }
                                else
                                {
#if defined _WIN32
                                    SetConsoleTextAttribute(handle, FOREGROUND_RED);
#endif
                                    error__::ERR.callError("FATAL_GENERATE_COMPILER&COMM_0GC");
#if defined _WIN32
                                    SetConsoleTextAttribute(handle, 15);
#endif
                                }
                            }
                        }
                        else
                        {
                            if (variable::TARGETS_[i].second.get().second.src_file[i2].find(".cpp") == (variable::TARGETS_[i].second.get().second.src_file[i2].size() - 4))
                            {
                                if (!pathInclude.empty())
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                else
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c++" + toString(variable::TARGETS_[i].second.get().second.CPPStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                            }
                            else
                            {
                                if (!pathInclude.empty())
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + " -I" + pathInclude + " " + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                                else
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -c " + variable::TARGETS_[i].second.get().second.src_file[i2] + " -std=c" + toString(variable::TARGETS_[i].second.get().second.CStandart) + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".o");
                            }
                            tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".o");
                            if (log_)
                            {
                                _log::log_event(time_() + ": The compiler command was generated: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                            }
                        }
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 1)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    bool linker = true;
                    if (workLINK)
                    {
                        if (variable::TARGETS_[i].second.get().first.find("<LIB>") == 0)
                        {
                            variable::TARGETS_[i].second.get().first.erase(0, 5);
                            std::string tmp_command;
                            if (!pathInclude.empty())
                                tmp_command = "\"" + pathArc_ + "\" " + variable::TARGETS_[i].second.get().first + ".lib " + "-I" + pathInclude + " ";
                            else
                                tmp_command = "\"" + pathArc_ + "\" " + variable::TARGETS_[i].second.get().first + ".lib ";
                            for (uint32_t i3 = 0; i3 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i3)
                            {
                                tmp_command += pathTarget + "\\obj" + toString(i3) + ".o ";
                            }
                            commandCompiler.push_back(tmp_command);
                            tmp_command.clear();

                            tmp_command = pathllvm_ranlib + variable::TARGETS_[i].second.get().first + ".lib ";
                            commandCompiler.push_back(tmp_command);
                            tmp_command.clear();

                            linker = false;
                            if (log_)
                            {
                                _log::log_event(time_() + ": The compiler command was generated for lib: " + commandCompiler[commandCompiler.size() - 2] + '\n');
                                _log::log_event(time_() + ": The compiler command was generated for lib: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                            }
                        }
                        else if (variable::TARGETS_[i].second.get().first.find("<DLL>") == 0)
                        {
                            variable::TARGETS_[i].second.get().first.erase(0, 5);
                            std::string tmp_command;
                            if (!pathInclude.empty())
                                tmp_command = "\"" + pathCompiler_ + "\" -shared -o " + variable::TARGETS_[i].second.get().first + ".dll " + variable::TARGETS_[i].second.get().second.flags + " -I" + pathInclude + " ";
                            else
                                tmp_command = "\"" + pathCompiler_ + "\" -shared -o " + variable::TARGETS_[i].second.get().first + ".dll " + variable::TARGETS_[i].second.get().second.flags + ' ';
                            for (uint32_t i3 = 0; i3 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i3)
                            {
                                tmp_command += pathTarget + "\\obj" + toString(i3) + ".o ";
                            }
                            for (uint64_t i2 = 0; i2 < pathCatalogLibStat.size() - 1; ++i2)
                            {
                                tmp_command += "-L" + pathCatalogLibStat[i2] + ' ';
                            }

                            for (uint64_t i2 = 0; i2 < pathCatalogLibDLL.size() - 1; ++i2)
                            {
                                tmp_command += "-L" + pathCatalogLibDLL[i2] + ' ';
                            }

                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.StaticLibrary.size(); ++i2)
                            {
                                tmp_command += "-l" + variable::TARGETS_[i].second.get().second.StaticLibrary[i2] + ' ';
                            }

                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.DynamicLibrary.size(); ++i2)
                            {
                                tmp_command += "-l" + variable::TARGETS_[i].second.get().second.DynamicLibrary[i2] + ' ';
                            }
                            commandCompiler.push_back(tmp_command);
                            tmp_command.clear();

                            if (regDLL)
                            {
                                tmp_command = "regsvr32.exe /i \"" + variable::TARGETS_[i].second.get().first + ".dll\"";
                                commandCompiler.push_back(tmp_command);
                                tmp_command.clear();
                            }

                            linker = false;
                            if (log_)
                            {
                                if (regDLL)
                                {
                                    _log::log_event(time_() + ": The compiler command was generated for DLL lib: " + commandCompiler[commandCompiler.size() - 2] + '\n');
                                    _log::log_event(time_() + ": The command for reg dll: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                }
                                else
                                {
                                    _log::log_event(time_() + ": The compiler command was generated for DLL lib: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                }
                            }
                        }
                    }
                    for (uint64_t o = 0; o < commandCompiler.size(); ++o)
                    {
                        if (system(commandCompiler[o].c_str()) == 0)
                        {
                            if (commandCompiler[o].find(".cpp") != commandCompiler[o].npos)
                            {
                                _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".cpp" + " --> " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", 15);
                            }
                            else if (commandCompiler[o].find(".c") != commandCompiler[o].npos)
                            {
                                _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".c" + " --> " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", 15);
                            }
                        }
                        else
                        {
                            if (commandCompiler[o].find(".cpp") != commandCompiler[o].npos)
                            {
                                _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".cpp" + " != " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", FOREGROUND_RED);
                            }
                            else if (commandCompiler[o].find(".c") != commandCompiler[o].npos)
                            {
                                _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".c" + " != " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", 15);
                            }
                            if (warning == 1)
                            {
                                error__::ERR.callError("FATAL_ERR_0BC");
                            }
                        }
                    }

                    if (log_)
                    {
                        _log::log_event(time_() + ": compilation was successful!\n");
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 2)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    if (workLINK)
                    {
                        command_linker.clear();

                        if (linker)
                        {

                            command_linker = "\"" + pathLinker_ + "\" " + variable::TARGETS_[i].first + ' ';

                            for (uint64_t i2 = 0; i2 < tempObj.size(); ++i2)
                            {
                                command_linker += tempObj[i2] + ' ';
                            }

                            for (uint64_t i2 = 0; i2 < pathCatalogLibStat.size() - 1; ++i2)
                            {
                                command_linker += "-L" + pathCatalogLibStat[i2] + ' ';
                            }

                            for (uint64_t i2 = 0; i2 < pathCatalogLibDLL.size() - 1; ++i2)
                            {
                                command_linker += "-L" + pathCatalogLibDLL[i2] + ' ';
                            }

                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.StaticLibrary.size(); ++i2)
                            {
                                command_linker += "-l" + variable::TARGETS_[i].second.get().second.StaticLibrary[i2] + ' ';
                            }

                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.DynamicLibrary.size(); ++i2)
                            {
                                command_linker += "-l" + variable::TARGETS_[i].second.get().second.DynamicLibrary[i2] + ' ';
                            }

                            command_linker += "-o " + variable::TARGETS_[i].second.get().first + ".exe";

                            if (log_)
                            {
                                _log::log_event(time_() + ": the command for the linker was generated: " + command_linker + '\n');
                            }

                            if (system(command_linker.c_str()) == 0)
                            {
                                _assistant::_debug::debug_msg_call(toString("Object files have been linked. The - \"" + variable::TARGETS_[i].second.get().first + ".exe\" program has been created!").c_str(), "ASSEMBLY", 15);
                            }
                            else
                            {
                                _assistant::_debug::debug_msg_call("Error linked!", "ASSEMBLY", FOREGROUND_RED);
                                if (warning == 1)
                                {
                                    error__::ERR.callError("FATAL_ERR_1BL");
                                }
                            }

                            if (regDLL)
                            {
                            }

                            if (log_)
                            {
                                _log::log_event(time_() + ": linking was successful!\n");
                            }
                        }
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 3)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    command_linker.clear();
                    tempObj.clear();
                    commandCompiler.clear();

                    _assistant::_debug::debug_msg_call(toString("Target - \"" + variable::TARGETS_[i].second.get().first + "\", has been completed!").c_str(), "ASSEMBLY", 2);
                }
                else if (variable::TARGETS_[i].second.get().second.lang == 1)
                {
                    pathCompiler_ = variable::TARGETS_[i].second.get().second.pathCompiler_;
                    pathLinker_ = variable::TARGETS_[i].second.get().second.pathLinker_;
                    std::string tmp__ = "\"" + pathCompiler_ + "\" ";
                    if (variable::TARGETS_[i].second.get().first.find("<DLL>") == 0)
                    {
                        tmp__ += "/t:library ";
                    }
                    else if (variable::TARGETS_[i].second.get().first.find("<LIB>") == 0)
                    {
                        tmp__ += "/t:module ";
                    }
                    else if (variable::TARGETS_[i].second.get().first.find("<WIN_EXE>") == 0)
                    {
                        tmp__ += "/t:winexe ";
                    }
                    else
                    {
                        tmp__ += "/t:exe ";
                    }
                    if (variable::TARGETS_[i].second.get().second.DynamicLibrary.size() > 0)
                    {
                        tmp__ += "/r:";
                    }
                    for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.DynamicLibrary.size(); ++i2)
                    {
                        tmp__ += variable::TARGETS_[i].second.get().second.DynamicLibrary[i2] + ';';
                    }
                    tmp__ += ' ';
                    for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i2)
                    {
                        tmp__ += variable::TARGETS_[i].second.get().second.src_file[i2] + ' ';
                    }
                    if (variable::TARGETS_[i].second.get().first.find("<DLL>") == 0)
                    {
                        variable::TARGETS_[i].second.get().first.erase(0, 5);
                        tmp__ += "/out:" + variable::TARGETS_[i].second.get().first + ".dll";
                    }
                    else
                    {
                        tmp__ += "/out:" + variable::TARGETS_[i].second.get().first + ".exe";
                    }
                    commandCompiler.push_back(tmp__);
                    tmp__.clear();
                    if (log_)
                    {
                        _log::log_event(time_() + ": The compiler command was generated: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 1 || oth_commands[i3].second == 2)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    for (uint32_t o = 0; o < commandCompiler.size(); ++o)
                    {
                        if (system(commandCompiler[o].c_str()) == 0)
                        {
                            _assistant::_debug::debug_msg_call(toString(" TARGET - " + toString(i) + ", completed successfully!").c_str(), "ASSEMBLY", FOREGROUND_GREEN);
                        }
                        else
                        {
                            _assistant::_debug::debug_msg_call(toString(" TARGET - " + toString(i) + ", ERROR!!!").c_str(), "ASSEMBLY", FOREGROUND_RED);
                            if (warning == 1)
                            {
                                error__::ERR.callError("FATAL_ERR_0BC");
                            }
                        }
                    }
                    commandCompiler.clear();

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 3)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }
                }
                else if (variable::TARGETS_[i].second.get().second.lang == 2)
                {
                    pathCompiler_ = variable::TARGETS_[i].second.get().second.pathCompiler_;
                    pathLinker_ = variable::TARGETS_[i].second.get().second.pathLinker_;
                    for (uint64_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i2)
                    {
                        if (variable::TARGETS_[i].second.get().second.src_file[i2].find(".h") == variable::TARGETS_[i].second.get().second.src_file[i2].size() - 2)
                        {
                            continue;
                        }
                        std::filesystem::path fileSource = std::filesystem::temp_directory_path() / variable::TARGETS_[i].second.get().second.src_file[i2];
                        std::filesystem::path fileCache = std::filesystem::temp_directory_path() / (pathBuild + "\\CLMakeCache.txt");
                        std::ifstream{fileSource.c_str()};
                        std::ifstream{fileCache.c_str()};
                        std::ifstream objectFiles(pathTarget + "\\obj" + toString(i2) + ".obj");

                        std::filesystem::file_time_type ftime = std::filesystem::last_write_time(fileSource);
                        std::filesystem::file_time_type fctime = std::filesystem::last_write_time(fileCache);
                        if (objectFiles.is_open())
                        {
                            objectFiles.close();
                            std::filesystem::path fileObject = std::filesystem::temp_directory_path() / (pathTarget + "\\obj" + toString(i2) + ".obj");
                            std::ifstream{fileObject.c_str()};
                            std::filesystem::file_time_type ftime2 = std::filesystem::last_write_time(fileObject);

                            if (ftime2 > ftime && ftime2 < fctime)
                            {
#if defined _WIN32
                                commandCompiler.push_back("\"" + pathCompiler_ + "\" -f win32 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#else
                                commandCompiler.push_back("\"" + pathCompiler_ + "\" -f elf64 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#endif
                                tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".obj");
                            }
                            else
                            {
                                if (ftime > ftime2)
                                {
#if defined _WIN32
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -f win32 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#else
                                    commandCompiler.push_back("\"" + pathCompiler_ + "\" -f elf64 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#endif
                                    tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".obj");
                                }
                                else if (ftime < ftime2)
                                {
                                    tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".obj");
                                }
                                else
                                {
#if defined _WIN32
                                    SetConsoleTextAttribute(handle, FOREGROUND_RED);
#endif
                                    error__::ERR.callError("FATAL_GENERATE_COMPILER&COMM_0GC");
#if defined _WIN32
                                    SetConsoleTextAttribute(handle, 15);
#endif
                                }
                            }
                        }
                        else
                        {
#if defined _WIN32
                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -f win32 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#else
                            commandCompiler.push_back("\"" + pathCompiler_ + "\" -f elf64 " + variable::TARGETS_[i].second.get().second.src_file[i2] + ' ' + variable::TARGETS_[i].second.get().second.flags + " -o " + pathTarget + "\\obj" + toString(i2) + ".obj");
#endif
                            tempObj.push_back(pathTarget + "\\obj" + toString(i2) + ".obj");
                        }
                        if (log_)
                        {
                            _log::log_event(time_() + ": The compiler command was generated: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                        }
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 1)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    bool linker = true;
                    if (workLINK)
                    {
                        if (variable::TARGETS_[i].second.get().first.find("<DLL>") == 0)
                        {
                            variable::TARGETS_[i].second.get().first.erase(0, 5);
                            std::string tmp_command = "\"" + pathLinker_ + "\" /entry: " + entry_point[i] + " /dll ";
                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.StaticLibrary.size(); ++i2)
                            {
                                tmp_command += variable::TARGETS_[i].second.get().second.StaticLibrary[i2] + ' ';
                            }
                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.DynamicLibrary.size(); ++i2)
                            {
                                tmp_command += variable::TARGETS_[i].second.get().second.DynamicLibrary[i2] + ' ';
                            }
                            for (uint32_t i3 = 0; i3 < variable::TARGETS_[i].second.get().second.src_file.size(); ++i3)
                            {
                                tmp_command += pathTarget + "\\obj" + toString(i3) + ".obj";
                            }
                            tmp_command += variable::TARGETS_[i].first + " /fo " + pathBuild + "\\" + variable::TARGETS_[i].second.get().first + ".dll";
                            commandCompiler.push_back(tmp_command);
                            tmp_command.clear();

                            if (regDLL)
                            {
                                tmp_command = "regsvr32.exe /i \"" + variable::TARGETS_[i].second.get().first + ".dll\"";
                                commandCompiler.push_back(tmp_command);
                                tmp_command.clear();
                            }

                            linker = false;
                            if (log_)
                            {
                                if (regDLL)
                                {
                                    _log::log_event(time_() + ": The compiler command was generated for DLL lib: " + commandCompiler[commandCompiler.size() - 2] + '\n');
                                    _log::log_event(time_() + ": The command for reg dll: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                }
                                else
                                {
                                    _log::log_event(time_() + ": The compiler command was generated for DLL lib: " + commandCompiler[commandCompiler.size() - 1] + '\n');
                                }
                            }
                        }
                    }

                    for (uint64_t o = 0; o < commandCompiler.size(); ++o)
                    {
                        if (system(commandCompiler[o].c_str()) == 0)
                        {
                            _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".asm" + " --> " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", 15);
                        }
                        else
                        {
                            _assistant::_debug::debug_msg_call(toString("obj" + toString(o) + ".asm" + " != " + "obj" + toString(o) + ".o").c_str(), "ASSEMBLY", FOREGROUND_RED);
                            if (warning == 1)
                            {
                                error__::ERR.callError("FATAL_ERR_0BC");
                            }
                        }
                    }

                    if (log_)
                    {
                        _log::log_event(time_() + ": compilation was successful!\n");
                    }

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 2)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }

                    if (workLINK)
                    {
                        if (linker)
                        {
                            command_linker = "\"" + pathLinker_ + "\" /entry:" + entry_point[i] + " /console ";
                            for (uint32_t i2 = 0; i2 < variable::TARGETS_[i].second.get().second.DynamicLibrary.size(); ++i2)
                            {
                                command_linker += variable::TARGETS_[i].second.get().second.DynamicLibrary[i2] + ' ';
                            }
                            for (uint64_t i2 = 0; i2 < tempObj.size(); ++i2)
                            {
                                command_linker += tempObj[i2] + ' ';
                            }
                            command_linker += variable::TARGETS_[i].first + " /fo " + pathBuild + "\\" + variable::TARGETS_[i].second.get().first + ".exe";
                            if (log_)
                            {
                                if (commandCompiler.size() > 0)
                                {
                                    _log::log_event(time_() + ": The linker command was generated: " + command_linker + '\n');
                                }
                            }
                            if (system(command_linker.c_str()) == 0)
                            {
                                _assistant::_debug::debug_msg_call(toString("Object files have been linked. The - \"" + variable::TARGETS_[i].second.get().first + ".exe\" program has been created!").c_str(), "ASSEMBLY", 2);
                            }
                            else
                            {
                                _assistant::_debug::debug_msg_call("Error linker", "ASSEMBLY", FOREGROUND_RED);
                                if (warning == 1)
                                {
                                    error__::ERR.callError("FATAL_ERR_1BL");
                                }
                            }

                            if (log_)
                            {
                                _log::log_event(time_() + ": linking was successful!\n");
                            }
                        }
                    }
                    command_linker.clear();
                    tempObj.clear();
                    commandCompiler.clear();

                    for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
                    {
                        if (oth_commands[i3].second == 3)
                        {
                            system(oth_commands[i3].first.c_str());
                        }
                    }
                }
            }
            _log::log_event(time_() + ": -------------------------END-------------------------\n");
        }

        for (uint32_t i3 = 0; i3 < oth_commands.size(); ++i3)
        {
            if (oth_commands[i3].second == 4)
            {
                system(oth_commands[i3].first.c_str());
            }
        }
        if (log_)
        {
            _log::log_event(time_() + ": end assembly\n\n");
        }

        _log::log_.exchange(0);
    }
}