#ifndef PRJ__H_
#define PRJ__H_


#include "../../../bin/include.h"

namespace project
{
    class project__
    {
    public:
        std::string NameProject;
        std::vector<std::string> src_file;
        std::string flags;
        double CStandart;
        double CPPStandart;
        std::vector<std::string> StaticLibrary;
        std::vector<std::string> DynamicLibrary;
        bool userTemplate = false;
        std::vector<std::string> userTemplates;
        uint32_t lang;
        std::string pathCompiler_;
        std::string pathLinker_;
    };
    extern std::vector<project__> project_;
    static uint64_t find_project(std::string name)
    {
        for (uint64_t i = 0; i < project_.size(); ++i)
        {
            if (project_[i].NameProject == name)
                return i;
        }
        return -1;
    }
}

#endif