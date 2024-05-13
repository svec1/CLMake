#include "serel.h"
#include "../buildHead.h"

void serelization_full(std::ofstream &file)
{
    using namespace variable;
    using namespace project;
    using namespace executable;

    // DOUBLE
    file << "DefinedDSymbols:";
    for (uint64_t i = 0; i < DOUBLE_.size() - 1; ++i)
    {
        if (DOUBLE_.get_name(i).find("CLMAKE_") == 0)
            continue;
        file << DOUBLE_.get_name(i) << '-' << DOUBLE_[i] << ';';
    }

    // STRING
    file << "\nDefinedSSymbols:";
    for (uint64_t i = 0; i < STRING_.size() - 1; ++i)
    {
        if (STRING_.get_name(i).find("CLMAKE_") == 0)
            continue;
        file << STRING_.get_name(i) << "-" << STRING_[i] << ";";
    }

    // STRUCT
    file << "\nDefinedSTSymbols:";
    for (uint64_t i = 0; i < STRUCT_.size() - 1; ++i)
    {
        if (STRUCT_.get_name(i).find("CLMAKE_") == 0)
            continue;
        file << STRUCT_.get_name(i) << '-' << STRUCT_[i].first << ',' << STRUCT_[i].second << ';';
    }

    // VECTOR_STRING
    file << "\nDefinedVSSymbols:";
    for (uint64_t i = 0; i < VEC_STRING_.size() - 1; ++i)
    {
        if (VEC_STRING_.get_name(i).find("CLMAKE_") == 0)
            continue;
        file << VEC_STRING_.get_name(i) << '-';
        for (uint32_t i2 = 0; i2 < VEC_STRING_[i].size(); ++i2)
        {
            file << VEC_STRING_[i][i2] << ",";
        }
        file << ';';
    }

    // PROJECT
    file << "\nProject:\n";
    if (project::project_.size() == 0)
        file << ';' << '\n';
    for (uint32_t i = 0; i < project::project_.size(); ++i)
    {
        file << project_[i].NameProject << ';';
        for (uint32_t i2 = 0; i2 < project_[i].src_file.size(); ++i2)
        {
            file << project_[i].src_file[i2];
            file << ',';
        }
        file << ';';
        file << project_[i].flags << ';';
        file << project_[i].CStandart << ';';
        file << project_[i].CPPStandart << ';';
        for (uint32_t i2 = 0; i2 < project_[i].StaticLibrary.size(); ++i2)
        {
            file << project_[i].StaticLibrary[i2];
            file << ',';
        }
        file << ';';
        for (uint32_t i2 = 0; i2 < project_[i].DynamicLibrary.size(); ++i2)
        {
            file << project_[i].DynamicLibrary[i2];
            file << ',';
        }
        file << ';';
        file << '\n';
    }

    // executable targets
    for (uint64_t i = 0; i < executables_.size(); ++i)
    {
        executable::ENUM_EXE tmp;
        tmp.define(executables_[i]);
        tmp.write(file);
        file << '\n';
    }

    return;
}
void deserelization_full(std::ifstream &file, uint32_t exp)
{
    std::string sCode = "";
    char chTmp;

    bool db = false;
    bool str = false;
    bool vec_str = false;
    bool strct = false;

    bool this_prg = false;

    while (!file.eof())
    {
        file.get(chTmp);
        sCode += chTmp;
        if (chTmp == '\n')
        {
            if ((sCode.find("DefinedDSymbols:") == 0 && exp == 1 || sCode.find("DefinedSSymbols:") == 0 && exp == 2) || ((sCode.find("DefinedDSymbols:") == 0 || sCode.find("DefinedSSymbols:") == 0) && exp == 0))
            {
                if (sCode.find("DefinedDSymbols:") == 0)
                {
                    db = true;
                }
                else if (sCode.find("DefinedSSymbols:") == 0)
                {
                    str = true;
                }
                sCode.erase(0, 16);
                std::string tmp;
                std::string tmp2;
                while (1)
                {
                    if (sCode[0] == '\n')
                    {
                        sCode.clear();
                        break;
                    }
                    uint32_t i2 = 0;
                    while (sCode[i2] != '-')
                    {
                        if (i2 > sCode.size() - 1)
                            break;
                        tmp += sCode[i2];
                        ++i2;
                    }
                    if (sCode[i2] == '-')
                    {
                        ++i2;
                        while (sCode[i2] != ';')
                        {
                            if (i2 > sCode.size() - 1)
                                break;
                            tmp2 += sCode[i2];
                            ++i2;
                        }
                        if (sCode[i2] == ';')
                        {
                            if (db)
                            {
                                if (variable::DOUBLE_.find_(tmp) == std::uint64_t(-1))
                                {
                                    variable::DOUBLE_.createVar(tmp, std::atof(tmp2.c_str()));
                                    sCode.erase(0, i2 + 1);
                                    tmp.clear();
                                    tmp2.clear();
                                }
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_VARIABLE_EX");
                                }
                            }
                            else if (str)
                            {
                                if (variable::STRING_.find_(tmp) == std::uint64_t(-1))
                                {
                                    variable::STRING_.createVar(tmp, tmp2.c_str());
                                    sCode.erase(0, i2 + 1);
                                    tmp.clear();
                                    tmp2.clear();
                                }
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "Name variable: " + tmp);
                                }
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_UN_EX");
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: -");
                    }
                }
                db = false;
                str = false;
            }
            else if ((sCode.find("DefinedVSSymbols:") == 0 && exp == 3) || (sCode.find("DefinedVSSymbols:") == 0 && exp == 0))
            {
                sCode.erase(0, 17);
                std::string tmp;
                std::vector<std::string> tmp2;
                std::string tmp3;
                while (1)
                {
                    if (sCode[0] == '\n')
                    {
                        sCode.clear();
                        break;
                    }
                    uint32_t i2 = 0;
                    while (sCode[i2] != '-')
                    {
                        if (i2 > sCode.size() - 1)
                            break;
                        tmp += sCode[i2];
                        ++i2;
                    }
                    if (sCode[i2] == '-')
                    {
                        while (sCode[i2] != ';')
                        {
                            if (i2 > sCode.size() - 1)
                                break;
                            while (sCode[i2] != ',')
                            {
                                if (i2 > sCode.size() - 1)
                                    break;
                                tmp3 += sCode[i2];
                                ++i2;
                            }
                            if (sCode[i2] == ',')
                            {
                                tmp2.push_back(tmp3);
                                ++i2;
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ,");
                            }
                        }
                        if (sCode[i2] == ';')
                        {
                            if (variable::VEC_STRING_.find_(tmp) == std::uint64_t(-1))
                            {
                                variable::VEC_STRING_.createVar(tmp, tmp2);
                                sCode.erase(0, i2 + 1);
                                tmp.clear();
                                tmp2.clear();
                                tmp3.clear();
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_VARIABLE_EX");
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: -");
                    }
                }
            }
            else if ((sCode.find("DefinedSTSymbols:") == 0 && exp == 4) || (sCode.find("DefinedSTSymbols:") == 0 && exp == 0))
            {
                sCode.erase(0, 17);
                std::string tmp;
                std::pair<std::string, std::string> tmp2;
                std::string tmp3;
                std::string tmp4;
                while (1)
                {
                    if (sCode[0] == '\n')
                    {
                        sCode.clear();
                        break;
                    }
                    uint32_t i2 = 0;
                    while (sCode[i2] != '-')
                    {
                        if (i2 > sCode.size() - 1)
                            break;
                        tmp += sCode[i2];
                        ++i2;
                    }
                    if (sCode[i2] == '-')
                    {
                        if (i2 > sCode.size() - 1)
                            break;
                        while (sCode[i2] != ',')
                        {
                            if (i2 > sCode.size() - 1)
                                break;
                            tmp3 += sCode[i2];
                            ++i2;
                        }
                        if (sCode[i2] == ',')
                        {
                            ++i2;
                            while (sCode[i2] != ';')
                            {
                                if (i2 > sCode.size() - 1)
                                    break;
                                tmp4 += sCode[i2];
                                ++i2;
                            }
                            if (sCode[i2] == ';')
                            {
                                tmp2.first = tmp3;
                                tmp2.second = tmp4;
                                tmp3.clear();
                                tmp4.clear();
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ,");
                        }
                        if (sCode[i2] == ';')
                        {
                            if (variable::STRUCT_.find_(tmp) == std::uint64_t(-1))
                            {
                                variable::STRUCT_.createVar(tmp, tmp2);
                                sCode.erase(0, i2 + 1);
                                tmp.clear();
                                tmp4.clear();
                                tmp3.clear();
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_VARIABLE_EX", "Name variable: " + tmp);
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: -");
                    }
                }
            }
            else if ((sCode.find("Project:\n") == 0 && exp == 5) || (sCode.find("Project:\n") == 0 && exp == 0))
            {
                sCode.clear();
                this_prg = true;
                continue;
            }
            else if (sCode.find("exeConfig_file-") == 0)
            {
                if ((sCode.find("exeConfig_file-") == 0 && exp == 6) || (sCode.find("exeConfig_file-") == 0 && exp == 0))
                {
                    executable::ENUM_EXE tmp;
                    tmp.serel_str = true;
                    tmp.serelStr = sCode;
                    tmp.read(std::ifstream());
                    executable::executables_.push_back(tmp.get());
                    sCode.clear();
                }
            }
            else if (this_prg)
            {
                std::string tmp;
                project::project__ tmp2;
                std::vector<std::string> tmp3;

                uint32_t i = 0;

                while (sCode[i] != ';')
                {
                    if (i > sCode.size() - 1)
                        break;
                    tmp += sCode[i];
                    ++i;
                }
                if (sCode.size() <= 2)
                    ;
                else if (sCode[i] == ';')
                {
                    tmp2.NameProject = tmp;
                    tmp.clear();
                    ++i;
                    while (sCode[i] != ';')
                    {
                        if (i > sCode.size() - 1)
                            break;
                        if (sCode[i] == ',')
                        {
                            tmp3.push_back(tmp);
                            tmp.clear();
                            ++i;
                            continue;
                        }
                        tmp += sCode[i];
                        ++i;
                    }
                    if (sCode[i] == ';')
                    {
                        ++i;
                        tmp2.src_file = tmp3;
                        tmp3.clear();
                        tmp.clear();
                        while (sCode[i] != ';')
                        {
                            if (i > sCode.size() - 1)
                                break;
                            tmp += sCode[i];
                            ++i;
                        }
                        if (sCode[i] == ';')
                        {
                            ++i;
                            tmp2.flags = tmp;
                            tmp.clear();
                            while (sCode[i] != ';')
                            {
                                if (i > sCode.size() - 1)
                                    break;
                                tmp += sCode[i];
                                ++i;
                            }
                            if (sCode[i] == ';')
                            {
                                ++i;
                                tmp2.CStandart = std::atoi(tmp.c_str());
                                tmp.clear();
                                while (sCode[i] != ';')
                                {
                                    if (i > sCode.size() - 1)
                                        break;
                                    tmp += sCode[i];
                                    ++i;
                                }
                                if (sCode[i] == ';')
                                {
                                    ++i;
                                    tmp2.CPPStandart = std::atoi(tmp.c_str());
                                    tmp.clear();
                                    while (sCode[i] != ';')
                                    {
                                        if (i > sCode.size() - 1)
                                            break;
                                        if (sCode[i] == ',')
                                        {
                                            tmp3.push_back(tmp);
                                            tmp.clear();
                                            ++i;
                                            continue;
                                        }
                                        tmp += sCode[i];
                                        ++i;
                                    }
                                    if (sCode[i] == ';')
                                    {
                                        tmp2.StaticLibrary = tmp3;
                                        tmp3.clear();
                                        tmp.clear();
                                        ++i;
                                        while (sCode[i] != ';')
                                        {
                                            if (i > sCode.size() - 1)
                                                break;
                                            if (sCode[i] == ',')
                                            {
                                                tmp3.push_back(tmp);
                                                tmp.clear();
                                                ++i;
                                                continue;
                                            }
                                            tmp += sCode[i];
                                            ++i;
                                        }
                                        if (sCode[i] == ';')
                                        {
                                            tmp2.DynamicLibrary = tmp3;
                                            project::project_.push_back(tmp2);
                                            tmp3.clear();
                                            tmp.clear();
                                            sCode.clear();
                                        }
                                        else
                                        {
                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                                        }
                                    }
                                    else
                                    {
                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                                    }
                                }
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                                }
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ;");
                }
                this_prg = false;
            }
            else if (file.eof())
                break;
            else
            {
                sCode.erase(0, sCode.size());
            }
        }
    }
}
void deserelization_template(std::ifstream &file)
{
    std::string code = "";
    char ch;
    bool structFile = false;
    while (!file.eof())
    {
        file.get(ch);
        code += ch;
    }
    code[code.size() - 1] = '\n';
    std::uint32_t i = 0;
    std::vector<std::string> add;
    std::string name = "";
    while (i < code.size())
    {
        std::string tmp;
        while (code[i] != ':')
        {
            if (i < code.size() - 1)
            {
                name += code[i];
                ++i;
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i, ":");
            }
        }
        if (code[i] != ':')
        {
            error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i, ":");
        }
        ++i;
        while (i < code.size())
        {
            if (code[i] == '-')
            {
                if (structFile && tmp != "command")
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i, ",");
                }
                structFile = true;
                tmp.clear();
                ++i;
                continue;
            }
            else if (code[i] == ',')
            {
                if (i < code.size() - 1)
                {
                    if (code[i + 1] != ',' && code[i + 1] != ':' && code[i + 1] != '\n' && code[i + 1] != ';' && code[i + 1] != '-' && code[i + 1] != ' ')
                    {
                        add.push_back(tmp);
                        tmp.clear();
                        ++i;
                        continue;
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i + 1, "A-z");
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i + 1, "A-z");
                }
            }
            else if (code[i] == ';')
            {
                if (code[i + 1] != '\n')
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", code, i + 1, "A-z");
                }
                add.push_back(tmp);
                tmp.clear();
                i += 2;
                break;
            }
            tmp += code[i];
            ++i;
        }
        variable::templateGenerate.createVar(name, add);
        code.erase(0, i);
        name.clear();
        add.clear();
        tmp.clear();
        i = 0;
        if (code.size() == 1)
            break;
    }
}

void StreamEI::deserelization_plugins(std::ifstream &file)
{
    std::string code;
    char ch = ' ';
    bool dll = false;
    bool com = false;
    while (!file.eof())
    {
        code.clear();
        uint32_t i = 0;
        while (ch != '\n')
        {
            file.get(ch);
            if (file.eof())
                break;
            code += ch;
        }
        if (ch != '\n' && ch != ';')
        {
            _assistant::_error_hand::errorUS_create(std::exception("Not found \'\\n\' or \';\'. Incorrect file architecture!"));
            _assistant::exit_();
        }
        ch = ' ';
        if (code.find("DLL:") == 0 || dll)
        {
            if (!dll)
                code.erase(0, 4);
            dll = true;
            std::string name;
            std::vector<std::string> funcs;
            std::string func;
            while (i != code.size() - 1)
            {
                while (code[i] != '-')
                {
                    if (i == code.size() - 1)
                        break;
                    name += code[i];
                    ++i;
                }
                if (code[i] != '-')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'-\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                ++i;
                if (code[i] != '|')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'||\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                ++i;
                while (code[i] != '|')
                {
                    while (code[i] != ',')
                    {
                        if (i == code.size() - 1 || code[i] == '|')
                            break;
                        func += code[i];
                        ++i;
                    }
                    if (code[i] == ',')
                        funcs.push_back(func);
                    else if (code[i] == '|')
                    {
                        funcs.push_back(func);
                        break;
                    }
                    else
                    {
                        _assistant::_error_hand::errorUS_create(std::exception("Not found \'||\'. Incorrect file architecture!"));
                        _assistant::exit_();
                    }
                    ++i;
                    func.clear();
                }
                if (code[i] != '|')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'||\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                StreamEI::listPlugins.push_back(std::pair(name, funcs));
                ++i;
                if (code[i] == ';')
                {
                    dll = false;
                    break;
                }
                else if (code[i] == '\n')
                {
                    break;
                }
                else if (code[i] != ',')
                {
                    _assistant::_error_hand::errorUS_create(std::exception(toString("Unexpected sym : \'" + toString(code[i]) + "\'. Incorrect file architecture!").c_str()));
                    _assistant::exit_();
                }
                ++i;
                name.clear();
                funcs.clear();
                func.clear();
            }
            if (code[i] != ';' && !dll)
            {
                _assistant::_error_hand::errorUS_create(std::exception("Not found \';\'. Incorrect file architecture!"));
                _assistant::exit_();
            }
        }
        else if (code.find("COMMAND:") == 0 || com)
        {
            if (!com)
                code.erase(0, 8);
            com = true;
            std::string tmp;
            std::string tmp2;
            std::string tmp3;
            while (i != code.size() - 1)
            {
                while (code[i] != '-')
                {
                    if (i == code.size() - 1)
                        break;
                    tmp += code[i];
                    ++i;
                }
                if (code[i] == '\n')
                    break;
                if (code[i] != '-')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'-\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                ++i;
                while (code[i] != '(')
                {
                    if (i == code.size() - 1)
                        break;
                    tmp2 += code[i];
                    ++i;
                }
                bool num = true;
                for (uint64_t i3 = 0; i3 < tmp2.size(); ++i3)
                {
                    if (std::isdigit(tmp2[i3]) == 0)
                    {
                        num = false;
                        break;
                    }
                }
                if (!num)
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Expected \'number\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                if (code[i] != '(')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'()\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
                ++i;
                while (code[i] != ')')
                {
                    if (i == code.size() - 1)
                        break;
                    tmp3 += code[i];
                    ++i;
                }
                if (code[i] != ')')
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \'()\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }

                build::COMMAND.emplace(std::stoi(tmp2), tmp);

                tmp.clear();
                tmp2.clear();
                if (i != code.size() - 1)
                {
                    ++i;
                    if (code[i] == ',')
                        break;
                    if (code[i] != ';')
                    {
                        _assistant::_error_hand::errorUS_create(std::exception("Not found \';\'. Incorrect file architecture!"));
                        _assistant::exit_();
                    }
                }
                else if (code[i] == '\n')
                {
                    break;
                }
                else if (code[i] != ';' && i == code.size() - 1)
                {
                    _assistant::_error_hand::errorUS_create(std::exception("Not found \';\'. Incorrect file architecture!"));
                    _assistant::exit_();
                }
            }
            if (code[i] != ';' && !com)
            {
                _assistant::_error_hand::errorUS_create(std::exception("Not found \';\'. Incorrect file architecture!"));
                _assistant::exit_();
            }
        }
    }
}