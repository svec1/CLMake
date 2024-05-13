#ifndef TRG_EX__H_
#define TRG_EX__H_

#include "../../../bin/include.h"
#include "project.h"

namespace executable
{
    extern std::vector<
        std::pair</* name, project */
                  std::string,
                  project::project__>>
        executables_;

    static uint64_t find_exe(std::string name)
    {
        for (uint64_t i = 0; i < executables_.size(); ++i)
        {
            if (executables_[i].first == name)
                return i;
        }
        return -1;
    }

    static void printInfoExe(uint64_t index)
    {
        if (index >= executables_.size() || index < 0)
        {
            std::cout << "there is no such wrapper over the executable file!" << std::endl;
            return;
        }
        std::cout << "Executable is " << index << ": " << std::endl
                  << "\t-Name - " << executables_[index].first << std::endl
                  << "\t-Project name - " << executables_[index].second.NameProject << std::endl
                  << "\t-List source files - " << std::endl;
        for (uint64_t i = 0; i < executables_[index].second.src_file.size(); ++i)
        {
            std::cout << "\t\t-" << executables_[index].second.src_file[i] << std::endl;
        }
        std::cout << "\t-Flags - " << executables_[index].second.flags << std::endl
                  << "\t-Standart C - " << executables_[index].second.CStandart << std::endl
                  << "\t-Standart CPP - " << executables_[index].second.CPPStandart << std::endl
                  << "\t-Element DLL Library- " << executables_[index].second.DynamicLibrary.size() << std::endl
                  << "\t-Element Static Library - " << executables_[index].second.StaticLibrary.size() << std::endl;
        std::cout << "DLL LIBRARY: " << std::endl;
        for (uint32_t i = 0; i < executables_[index].second.DynamicLibrary.size(); ++i)
        {
            std::cout << "\t" << i << ". " << executables_[index].second.DynamicLibrary[i].c_str() << std::endl;
        }
        std::cout << "STATIC LIBRARY: " << std::endl;
        for (uint32_t i = 0; i < executables_[index].second.StaticLibrary.size(); ++i)
        {
            std::cout << "\t" << i << ". " << executables_[index].second.StaticLibrary[i].c_str() << std::endl;
        }
    }

    extern class ENUM_EXE
    {
    public:
        bool serel_str = false;
        std::string serelStr;

    public:
        ENUM_EXE();
        void define(std::pair<std::string, project::project__> exe_);
        void def_POE(std::string point);
        std::string get_POE();
        void write(std::ofstream &file);
        void read(std::ifstream &file);
        std::pair<std::string, project::project__> &get();
        ~ENUM_EXE();

    private:
        void stringWrite(std::ofstream &file, std::string str);
        void byteWrite(std::ofstream &file, const char &ch);
        std::pair<std::string, project::project__> executables__;
        /* *** */ std::string point_of_entry = "_start"; // *** FOR ASM
    };
}
#endif