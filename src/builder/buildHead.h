#ifndef BH__H_
#define BH__H_

#include "../bin/include.h"
#include "../bin/ConfigVar.h"

#include "StreamEI/StreamEI.h"
#include "setup/assist.h"
#include "class/head/var.h"
#include "class/head/project.h"
#include "class/head/err.h"
#include "class/head/wf.h"

#if defined _WIN32
#include <Windows.h>
#endif

// #define DEBUG__
#define debugging

extern bool assembly__;
namespace build
{

    struct inst
    {
        uint32_t opCode;
        std::vector<std::string> param;
    };

    extern void definedVAR_CLMAKE();
    extern void redefinition();

    extern class parser
    {
    public:
        parser();
        void parser::set_vecComm(const std::map<uint32_t, std::string> &comm_);
        void push_Comm(std::uint32_t i, std::string comm_);
        inst pars(std::string rawCommand);
        ~parser();

    private:
        std::string rawComm;
        std::map<uint32_t, std::string> command;
        void spaceIgn(uint32_t &i, std::string &rawCommand);
    };

    static std::map<uint32_t, std::string> COMMAND;

    extern bool started_Build();

    extern void runSCRIPT(std::vector<inst> INST);
    extern void call_to_script(int argc, char *argv[]);

    extern void build(int argc, char *argv[]);
    extern void assembly(int argc, char *argv[]);
}

#endif