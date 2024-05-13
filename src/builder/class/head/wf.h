#ifndef WF__H_
#define WF__H_

#include "../../../bin/include.h"

#if defined _WIN32
#include <Windows.h>
#endif

namespace workFile
{
    static std::string readFile(std::ifstream &file)
    {
        std::string tmp;
        char ch = ' ';
        file.get(ch);
        while (!file.eof())
        {
            tmp += ch;
            file.get(ch);
        }
        return tmp;
    }
    static void copy_file(std::ifstream &file_copy, std::ofstream &file_new)
    {
        std::string tmp = readFile(file_copy);
        uint64_t i = 0;
        while (i < tmp.size())
        {
            file_new << tmp[i];
            ++i;
        }
    }

    extern std::uint32_t val;
    extern bool find;

    extern void FindFiles(std::string folderName, std::string &fileName);
    extern std::string getPath();
    extern void cls();
}

#endif