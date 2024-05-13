#include "StreamEI.h"

std::vector<std::pair<std::string, std::vector<std::string>>> StreamEI::listPlugins;
std::vector<StreamEI::ImportPlagin> StreamEI::Plugin;
std::vector<std::thread> StreamEI::Plugins_th;

static const std::string file_ExpPlugin = "ListPlugin.exp";
static const std::string file_ExpTemplate = "template.clm";

void StreamEI::ImportPlagin::open_Plugin()
{
    typedef const char *(__stdcall * pInit)();
    pInit pl;
    pl = (pInit)GetProcAddress(ld, name_Initfunc.c_str());
    if (pl == NULL)
    {
        _assistant::_error_hand::errorUS_create(std::exception(toString("Unexpected error dll " + toString(GetLastError()) + ". Not found function init for of premature launch dll - " + name_filePluginDLL).c_str()));
        _assistant::exit_();
    }

    // inf = name_Plugin|version_Plugin
    int stdout_backup = dup(1);
    close(1);
    std::string inf = pl();
    dup2(stdout_backup, 1);
    std::cout.clear();
    std::uint32_t i = 0;
    while (i != inf.size())
    {
        while (inf[i] != '|')
        {
            name_Plugin += inf[i];
            ++i;
            if (i == inf.size())
                break;
        }
        if (inf[i] == '|')
        {
            std::string tmp;
            ++i;
            while (i != inf.size())
            {
                tmp += inf[i];
                ++i;
            }
            bool num = true;
            for (uint64_t i3 = 0; i3 < tmp.size(); ++i3)
            {
                if (std::isdigit(tmp[i3]) == 0)
                {
                    num = false;
                    break;
                }
            }
            if (num)
                version_Plugin = std::stoi(tmp);
            else
                _assistant::_error_hand::errorUS_create(std::exception(toString("Incorrect structure of the received message from the dll - " + name_filePluginDLL).c_str()));
        }
        else
        {
            _assistant::_error_hand::errorUS_create(std::exception(toString("Incorrect structure of the received message from the dll - " + name_filePluginDLL).c_str()));
        }
    }

#if defined _WIN32
    id_Plugin = generate_IdPlugins(name_Plugin, version_Plugin, this->ld);
#else
    id_Plugin = generate_IdPlugins(name_Plugin, version_Plugin);
#endif
}
void StreamEI::ImportPlagin::start_Plugin()
{
    typedef void(__stdcall * plugin)(void *);
    plugin pl;
    pl = (plugin)GetProcAddress(ld, name_WorkPlugFunc.c_str());
    if (pl != NULL)
    {
        void *res_ = &res;
        Plugins_th.push_back(std::thread(pl, res_));
    }
    else
    {
        _assistant::_error_hand::errorUS_create(std::exception(toString("Unexpected error dll " + toString(GetLastError()) + ". Not found function start plugin - " + name_WorkPlugFunc).c_str()));
        _assistant::exit_();
    }
}
void StreamEI::ImportPlagin::stop_Plugin()
{
}

std::string StreamEI::generate_IdPlugins(std::string name_Plugin_, std::uint32_t ver)
{
    std::string out;
    for (std::uint32_t i = 0; i < name_Plugin_.size(); ++i)
    {
        out += (int)(name_Plugin_[i] ^ listPlugins.size() & ver);
    }
    return ToHex(std::stoi(out.c_str()));
}
#if defined _WIN32
std::string StreamEI::generate_IdPlugins(std::string name_Plugin_, std::uint32_t ver, HINSTANCE hd)
{
    std::string out;
    for (std::uint32_t i = 0; i < name_Plugin_.size(); ++i)
    {
        out += (name_Plugin_[i] ^ listPlugins.size() & ver) ^ toString(hd)[toString(hd).size() - 1];
    }
    return out.c_str();
}
#endif

void StreamEI::SEI_()
{
    std::ifstream ExpPlugin(file_ExpPlugin);
    if (!ExpPlugin.is_open())
    {
        _assistant::_error_hand::errorUS_create(std::exception(toString("Not found a file - " + file_ExpPlugin + ".").c_str()));
        _assistant::exit_();
    }
    deserelization_plugins(ExpPlugin);
    _assistant::_debug::debug_msg_call("Plugins import was successful!", "StreamEI", 2);

    if (asm_)
    {
        std::ifstream file_templateList(file_ExpTemplate);
        if (!file_templateList.is_open())
        {
            _assistant::_error_hand::errorUS_create(std::exception(toString("Not found a file - " + file_ExpTemplate + ".").c_str()));
            _assistant::exit_();
        }
        deserelization_template(file_templateList);
        _assistant::_debug::debug_msg_call("Template loading was successful!", "StreamEI", 2);
    }

    for (std::uint32_t i = 0; i < listPlugins.size(); ++i)
    {
        ImportPlagin tmp(listPlugins[i]);
        tmp.open_Plugin();
        Plugin.push_back(tmp);
    }

    /*for (std::uint32_t i = 0; i < Plugin.size(); ++i)
    {
        Plugin[i].open_Plugin();
    }*/
}