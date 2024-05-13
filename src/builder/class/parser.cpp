#include "../buildHead.h"

using namespace build;

parser::parser()
{
    rawComm = "";
}
void parser::set_vecComm(const std::map<std::uint32_t, std::string> &comm_)
{
    command = comm_;
}
void parser::push_Comm(std::uint32_t i, std::string comm_)
{
    command.emplace(i, comm_);
}
inst parser::pars(std::string rawCommand)
{
    uint32_t i = 0;
    std::string tmpComm = "";
    inst prcComm;
    bool sk = false;
    bool fsk = false;
    if (rawCommand[i] == ' ')
    {
        spaceIgn(i, rawCommand);
    }
    if (rawCommand[i] == '(')
    {
        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i, "\'any function\'");
    }
    while (rawCommand[i] != '(')
    {
        tmpComm += rawCommand[i];
        ++i;
        if (i == rawCommand.size() - 1)
        {
            error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i, "(");
        }
        if (rawCommand[i] == '$' || rawCommand[i] == '\"' || rawCommand[i] == '{' || rawCommand[i] == '}' || rawCommand[i] == '~')
        {
            error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, "(");
        }
        if (rawCommand[i] == ' ' && ((rawCommand[i - 1] >= 'A' && rawCommand[i - 1] <= 'Z') || (rawCommand[i - 1] >= 'a' && rawCommand[i - 1] <= 'z') || (rawCommand[i - 1] >= '0' || rawCommand[i - 1] <= '9')))
        {
            spaceIgn(i, rawCommand);
            if (rawCommand[i] != '(')
            {
                error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, "(");
            }
        }
    }
    for (uint32_t i2 = 0; i2 < command.size(); ++i2)
    {
        if (tmpComm == command.at(i2))
        {
            prcComm.opCode = i2;
            goto g;
        }
    }
    if (false)
    {
    g:
        ++i;
        tmpComm.clear();
        if (rawCommand[i] == ' ')
        {
            spaceIgn(i, rawCommand);
        }
        while (rawCommand[i] != ')')
        {
        loop:
            tmpComm += rawCommand[i];
            ++i;
            if (rawCommand[i - 1] == '$')
            {
                if (rawCommand[i - 2] != ' ' && rawCommand[i - 2] != '(')
                    error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 2, "\' \'");
                if (rawCommand[i] == '\"')
                {
                    if (sk)
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 3, "\"");
                    tmpComm += rawCommand[i];
                    ++i;
                    sk = true;
                }
                else if (rawCommand[i] == '{')
                {
                    if (fsk)
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 3, "}");
                    if (!sk)
                    {
                        tmpComm += rawCommand[i];
                        ++i;
                        fsk = true;
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i, "\"\" or {}");
                }
            }
            if (rawCommand[i] == ')')
            {
                if (rawCommand[i - 1] == '\"' && rawCommand[i - 2] != '$')
                {
                    if (sk == true)
                    {
                        sk = false;
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 2, "$ ...\"");
                    }
                }
                else if (rawCommand[i - 1] == '}')
                {
                    if (fsk == true)
                    {
                        fsk = false;
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, " ");
                    }
                }
                else if (fsk == true && rawCommand[i - 1] != '}')
                {
                    error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, "}");
                }
                if (!sk)
                {
                    prcComm.param.push_back(tmpComm);
                    tmpComm.clear();
                }
                else
                {
                    goto loop;
                }
            }
            if (rawCommand[i] == ' ')
            {
                if (rawCommand[i - 1] == '\"' && rawCommand[i - 2] != '$')
                {
                    if (sk == true)
                    {
                        sk = false;
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 2, "$ ...\"");
                    }
                }
                else if (rawCommand[i - 1] == '}')
                {
                    if (fsk == true)
                    {
                        fsk = false;
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, " ");
                    }
                }
                if (!sk)
                {
                    spaceIgn(i, rawCommand);
                    prcComm.param.push_back(tmpComm);
                    tmpComm.clear();
                }
            }
            if (i == rawCommand.size())
            {
                error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i, ")");
            }
        }
        tmpComm.clear();
        while (i < rawCommand.size())
        {
            ++i;
            if (rawCommand[i] == ' ')
            {
                spaceIgn(i, rawCommand);
            }
            if (rawCommand[i] == '-')
            {
                ++i;
                if (rawCommand[i] == ' ')
                {
                    spaceIgn(i, rawCommand);
                }
                if ((rawCommand[i] >= 'A' && rawCommand[i] <= 'Z') || (rawCommand[i] >= 'a' && rawCommand[i] <= 'z'))
                {
                    while (rawCommand[i] != '\n')
                    {
                        tmpComm += rawCommand[i];
                        ++i;
                        if (rawCommand[i] == ' ' || i == rawCommand.size())
                            break;
                    }
                    prcComm.param.push_back(tmpComm);
                    tmpComm.clear();
                }
            }
            tmpComm += rawCommand[i];
        }
        return prcComm;
    }
    error__::ERR.callError("FATAL_ERR_PARSER_ERP00", rawCommand, i - 1, "???");
}
parser::~parser()
{
    rawComm.clear();
    command.clear();
}
void parser::spaceIgn(uint32_t &i, std::string &rawCommand)
{
    while (rawCommand[i] == ' ')
    {
        ++i;
    }
}