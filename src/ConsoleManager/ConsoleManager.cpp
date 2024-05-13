#include "HeadCm.h"
#include "../builder/buildHead.h"

namespace ConsoleManage
{

    void help()
    {
        _assistant::_debug::debug_msg_call(toString(toString("\nAvailable Attributes: ") +
                                                    toString("\n\t -ver -- displays the version of the program\n\t -{path dir} -- starts creating CLMake files for subsequent assembly,") +
                                                    toString("\n\t   in the folder where CLMake (console) is open. The specified directory must contain the CLMakeConfig.txt file") +
                                                    toString("\n\t -build -- starts building and compiler the project in the specified folder where the CLMake files exist") +
                                                    toString("\n\t -AP -- creates a virtual space for just parse project and export all a objects") +
                                                    toString("\n-----------------------------------------------------------------\n"))
                                               .c_str(),
                                           "Console Manager", 15);
    }

    void CM(int argc, char *argv[])
    {
        error__::errorAdd(error__::ERR);
        if (argc > 1)
        {
            if (argc == 2)
            {
                if (argv[1][0] == '-')
                {
                    std::string tmp = argv[1];
                    if (tmp == "-ver" || tmp == "-version" || tmp == "-vr")
                    {
                        _assistant::_debug::debug_msg_call(toString(toString("version CLMake -- ") + toString(CLMAKE_VERSION)).c_str(), "Console Manager", 15);
                    }
                    else if (tmp == "-build")
                    {
                        try
                        {
                            build::assembly(argc, argv);
                        }
                        catch (std::exception &th)
                        {
                            throw th;
                        }
                    }
                    else if (tmp == "-help" || tmp == "-hp" || tmp == "-h")
                    {
                        help();
                    }
                }
                else
                {
                    try
                    {
                        build::build(argc, argv);
                    }
                    catch (std::exception &th)
                    {
                        throw th;
                    }
                }
            }
            else if (argc == 3)
            {
                std::string tmp = argv[1];
                if (tmp.find("-") == tmp.npos)
                {
                    tmp = argv[2];
                    if (tmp == "-f")
                    {
                        try
                        {
                            build::build(argc, argv);
                            build::assembly(argc, argv);
                        }
                        catch (std::exception &th)
                        {
                            throw th;
                        }
                    }
                    else
                    {
                        help();
                    }
                }
                else
                {
                    help();
                }
            }
            else if (argc == 4)
            {
                std::string tmp = argv[1];
                if (tmp.find("-") == tmp.npos)
                {
                    tmp = argv[2];
                    if (tmp == "-AP")
                    {
                        try
                        {
                            variable::STRING_.createVar("CLMAKE_PROJECT_PATH", argv[1]);
                            build::call_to_script(argc, argv);
                            _assistant::_debug::debug_msg_call("Serelization...", "Console Manager", 6);
                            std::string tmp__ = variable::STRING_[variable::STRING_.find_("CLMAKE_PROJECT_PATH")] + '\\' + argv[3];
                            std::ofstream file(tmp__);
                            serelization_full(file);
                            file.close();
                            _assistant::_debug::debug_msg_call("Serelization successfully!", "Console Manager", 6);
                        }
                        catch (std::exception &th)
                        {
                            throw th;
                        }
                    }
                    else
                    {
                        help();
                    }
                }
            }
            else
            {
                help();
            }
        }
    }
}