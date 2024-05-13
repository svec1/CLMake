#ifndef SET__H_
#define SET__H_

#include "../../bin/include.h"
#include "../setup/assist.h"
#include "../bin/serel.h"

#if defined _WIN32
#include <Windows.h>
#endif

namespace StreamEI
{
    class ImportPlagin
    {
    public:
        ImportPlagin(std::pair<std::string, std::vector<std::string>> dPlugin)
        {
            if (dPlugin.second.size() < 2)
            {
                _assistant::_error_hand::errorUS_create(std::exception(toString("Unexpected error. DLL - " + toString(name_filePluginDLL) + " , 0 exportable functions").c_str()));
                _assistant::exit_();
            }
            name_filePluginDLL = dPlugin.first;
            name_Initfunc = dPlugin.second[0];
            name_WorkPlugFunc = dPlugin.second[1];
            for (uint32_t i = 2; i < dPlugin.second.size(); ++i)
            {
                func.push_back(dPlugin.second[i]);
            }
#if defined _WIN32
            ld = LoadLibraryA(name_filePluginDLL.c_str());
            if (ld == NULL)
            {
                _assistant::_error_hand::errorUS_create(std::exception(toString("Unexpected error. DLL - " + toString(name_filePluginDLL) + " , could not open").c_str()));
                _assistant::exit_();
            }
#endif
            work = new bool(false);
        }

        ImportPlagin(const ImportPlagin &obj)
        {
            this->name_filePluginDLL = obj.name_filePluginDLL;
            this->name_Plugin = obj.name_Plugin;
            this->version_Plugin = obj.version_Plugin;
            this->id_Plugin = obj.id_Plugin;
            this->work = obj.work;
#if defined _WIN32
            this->ld = obj.ld;
#endif
        }

    public:
        std::string name_filePluginDLL;

        void open_Plugin();
        void start_Plugin();
        void stop_Plugin();

    private:
        std::string name_Plugin;
        std::uint32_t version_Plugin;
        std::string id_Plugin;
        std::string name_Initfunc;
        std::string name_WorkPlugFunc;
        std::vector<std::string> func;
        std::string res;

        bool *work;

#if defined _WIN32
        HINSTANCE ld;
#endif
    };

    extern std::vector<ImportPlagin> Plugin;
    extern std::vector<std::pair<std::string, std::vector<std::string>>> listPlugins;
    extern std::vector<std::thread> Plugins_th;

    extern void deserelization_plugins(std::ifstream &file);

    extern std::string generate_IdPlugins(std::string name_Plugin_, std::uint32_t ver);
#if defined _WIN32
    extern std::string generate_IdPlugins(std::string name_Plugin_, std::uint32_t ver, HINSTANCE hd);
#endif
    extern void SEI_();

}

#endif