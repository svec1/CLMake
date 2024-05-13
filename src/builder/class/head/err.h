#ifndef ERR_H_
#define ERR_H_

#include "../../../bin/include.h"
#include "../../../bin/ConfigVar.h"

#if defined _WIN32
#include <Windows.h>
#endif

namespace error__
{
    extern class error
    {
    public:
        bool addErrorFatal(std::string index, std::string warningText);
        bool callError(std::string index);
        bool callError(std::string index, std::string line, uint32_t ind_err_sym, std::string obj);
        bool callError(std::string index, std::string additional);
        std::string error_t(std::string err);

    private:
        std::vector<std::pair<std::string, std::string>> error_Fatal;
    };

    static void errorAdd(error &err)
    {

        // BUILDER
        err.addErrorFatal("FATAL_ERR_PARSER_ERP00", "INCORRECT SYNTAX. ");
        err.addErrorFatal("FATAL_GENERATE_COMPILER&COMM_0GC", "ERROR GENERATE COMPILER COMMAND. ");
        err.addErrorFatal("FATAL_ERR_0BC", "ERROR COMPILED. EXECUTION \"BUILDER\" WAS STOPPED. ");
        err.addErrorFatal("FATAL_ERR_1BL", "ERROR LINKED. EXECUTION \"BUILDER\" WAS STOPPED. ");

        // BUILD
        err.addErrorFatal("FATAL_ERR_MIN_VERSION", "INVALID VERSION.");
        err.addErrorFatal("FATAL_ERR_VARIABLE_NF", "VARIABLE NOT FOUND.");
        err.addErrorFatal("FATAL_ERR_VARIABLE_EX", "VARIABLE ALREADY EXIST.");
        err.addErrorFatal("FATAL_ERR_UNDEF_PARAM", "UNKNOWN PARAMETER. ");
        err.addErrorFatal("FATAL_ERR_UN_EX", "UNEXPECTED ERROR. ");
        err.addErrorFatal("FATAL_ERR_UN_PR", "UNEXPECTED PARAMETER. ");

        // PARSE
        err.addErrorFatal("FATAL_ERR_SYNTAX_S", "ERROR SYNTAX. ");
        err.addErrorFatal("FATAL_ERR_SYNTAX_M", "Undefined markup. ");
        err.addErrorFatal("FATAL_ERR_SYNTAX_UFS", "Unknown file structure. ");

        err.addErrorFatal("FATAL_ERR_FILE_OPEN", "Failed to open file. ");

        err.addErrorFatal("FATAL_ERR_OBJ_PARAM", "Undefined param for is a template. ");
        err.addErrorFatal("FATAL_ERR_TEMPLATE_U", "Undefined expected template. ");
    }

    extern error ERR;

}

#endif