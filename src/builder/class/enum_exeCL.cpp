#include "../buildHead.h"

using namespace build;
using namespace executable;

ENUM_EXE::ENUM_EXE()
{
}
void ENUM_EXE::define(std::pair<std::string, project::project__> exe_)
{
    executables__ = exe_;
}
void ENUM_EXE::def_POE(std::string point)
{
    point_of_entry = point;
    return;
}
std::string ENUM_EXE::get_POE()
{
    return point_of_entry;
}
void ENUM_EXE::write(std::ofstream &file)
{
    stringWrite(file, "exeConfig_file-");
    stringWrite(file, executables__.first);
    byteWrite(file, '~');
    stringWrite(file, executables__.second.NameProject);
    byteWrite(file, '~');
    stringWrite(file, "src-");
    for (uint64_t i = 0; i < executables__.second.src_file.size(); ++i)
    {
        stringWrite(file, executables__.second.src_file[i]);
        byteWrite(file, '|');
    }
    byteWrite(file, '~');
    stringWrite(file, executables__.second.flags);
    byteWrite(file, '~');
    byteWrite(file, executables__.second.CStandart);
    byteWrite(file, '~');
    byteWrite(file, executables__.second.CPPStandart);
    byteWrite(file, '~');
    stringWrite(file, "DLL-");
    for (uint64_t i = 0; i < executables__.second.DynamicLibrary.size(); ++i)
    {
        stringWrite(file, std::string(executables__.second.DynamicLibrary[i].c_str()));
        byteWrite(file, '|');
    }
    byteWrite(file, '~');
    stringWrite(file, "LIB-");
    for (uint64_t i = 0; i < executables__.second.StaticLibrary.size(); ++i)
    {
        stringWrite(file, std::string(executables__.second.StaticLibrary[i].c_str()));
        byteWrite(file, '|');
    }
    byteWrite(file, '~');
    // byteWrite(file, warning);
    // byteWrite(file, '~');
    stringWrite(file, point_of_entry);
    byteWrite(file, '~');
    byteWrite(file, executables__.second.userTemplate);
    byteWrite(file, '~');
    for (std::uint32_t i = 0; i < executables__.second.userTemplates.size(); ++i)
    {
        stringWrite(file, executables__.second.userTemplates[i]);
        byteWrite(file, '|');
    }
    byteWrite(file, '~');
    for (uint64_t i = 0; i < variable::AD_PARAM.size() - 1; ++i)
    {
        stringWrite(file, variable::AD_PARAM.get_name(i) + "-");
        if (variable::DOUBLE_.find_(variable::AD_PARAM[i]) != std::uint64_t(-1))
        {
            stringWrite(file, "D" + toString(variable::DOUBLE_[variable::DOUBLE_.find_(variable::AD_PARAM[i])]));
        }
        else if (variable::STRING_.find_(variable::AD_PARAM[i]) != std::uint64_t(-1))
        {
            stringWrite(file, "S" + variable::STRING_[variable::STRING_.find_(variable::AD_PARAM[i])]);
        }
        else if (variable::VEC_STRING_.find_(variable::AD_PARAM[i]) != std::uint64_t(-1))
        {
            stringWrite(file, "V");
            for (uint32_t i2 = 0; i2 < variable::VEC_STRING_[variable::VEC_STRING_.find_(variable::AD_PARAM[i])].size(); ++i2)
            {
                stringWrite(file, variable::VEC_STRING_[variable::VEC_STRING_.find_(variable::AD_PARAM[i])][i2]);
                byteWrite(file, '|');
            }
        }
        stringWrite(file, "\'");
    }
    byteWrite(file, '~');
    byteWrite(file, executables__.second.lang);
    byteWrite(file, '~');
    stringWrite(file, executables__.second.pathCompiler_);
    byteWrite(file, '~');
    stringWrite(file, executables__.second.pathLinker_);
    byteWrite(file, '~');
}
void ENUM_EXE::read(std::ifstream &file)
{
    std::string tmp;
    std::string tmp2;
    std::vector<std::string> tmp3;
    int32_t tmp__ = 0;
    char ch = ' ';
    if (!ENUM_EXE::serel_str)
    {
        while (!file.eof())
        {
            file.get(ch);
            tmp += ch;
        }
        ch = ' ';
    }
    else
    {
        tmp = ENUM_EXE::serelStr;
    }
    if (tmp.find("exeConfig_file-") == 0)
    {
        tmp.erase(0, std::string("exeConfig_file-").size());
        uint32_t i = 0;
        while (tmp[i] != '~')
        {
            if (i > tmp.size() - 1)
                break;
            tmp2 += tmp[i];
            ++i;
        }
        if (tmp[i] == '~')
        {
            ++i;
            ENUM_EXE::executables__.first = tmp2;
            tmp2.clear();
            while (tmp[i] != '~')
            {
                if (i > tmp.size() - 1)
                    break;
                tmp2 += tmp[i];
                ++i;
            }
            if (tmp[i] == '~')
            {
                ++i;
                ENUM_EXE::executables__.second.NameProject = tmp2;
                tmp2.clear();
                if (i + 4 < tmp.size() - 1)
                {
                    if (tmp[i] == 's' && tmp[i + 1] == 'r' && tmp[i + 2] == 'c' && tmp[i + 3] == '-')
                    {
                        tmp.erase(i, 4);
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: src-");
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", "Not found sym: src-");
                }
                while (tmp[i] != '~')
                {
                    if (i > tmp.size() - 1)
                        break;
                    while (tmp[i] != '|')
                    {
                        if (i > tmp.size() - 1)
                            break;
                        tmp2 += tmp[i];
                        ++i;
                    }
                    if (tmp[i] == '|')
                    {
                        tmp3.push_back(tmp2);
                        tmp2.clear();
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: |");
                    }
                    ++i;
                }
                if (tmp[i] == '~')
                {
                    ++i;
                    ENUM_EXE::executables__.second.src_file = tmp3;
                    tmp3.clear();
                    tmp2.clear();
                    while (tmp[i] != '~')
                    {
                        if (i > tmp.size() - 1)
                            break;
                        tmp2 += tmp[i];
                        ++i;
                    }
                    if (tmp[i] == '~')
                    {
                        ++i;
                        ENUM_EXE::executables__.second.flags = tmp2;
                        tmp2.clear();
                        char ch = tmp[i];
                        ++i;
                        if (tmp[i] == '~')
                        {
                            ++i;
                            ENUM_EXE::executables__.second.CStandart = (int)ch;
                            ch = tmp[i];
                            ++i;
                            if (tmp[i] == '~')
                            {
                                ++i;
                                ENUM_EXE::executables__.second.CPPStandart = (int)ch;
                                if (tmp[i] == 'D' && tmp[i + 1] == 'L' && tmp[i + 2] == 'L' && tmp[i + 3] == '-')
                                    tmp.erase(i, 4);
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", "Not found sym: DLL-");
                                }
                                tmp2.clear();
                                while (tmp[i] != '~')
                                {
                                    if (i > tmp.size() - 1)
                                        break;
                                    while (tmp[i] != '|')
                                    {
                                        if (i > tmp.size() - 1)
                                            break;
                                        tmp2 += tmp[i];
                                        ++i;
                                    }
                                    if (tmp[i] == '|')
                                    {
                                        tmp3.push_back(tmp2);
                                        tmp2.clear();
                                    }
                                    else
                                    {
                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: |");
                                    }
                                    ++i;
                                }
                                if (tmp[i] == '~')
                                {
                                    ++i;
                                    if (tmp3.size() > 0)
                                    {
                                        ENUM_EXE::executables__.second.DynamicLibrary = tmp3;
                                    }
                                    if (tmp[i] == 'L' && tmp[i + 1] == 'I' && tmp[i + 2] == 'B' && tmp[i + 3] == '-')
                                        tmp.erase(i, 4);
                                    else
                                    {
                                        error__::ERR.callError("FATAL_ERR_SYNTAX_UFS", "Not found sym: LIB-");
                                    }
                                    tmp2.clear();
                                    tmp3.clear();
                                    while (tmp[i] != '~')
                                    {
                                        if (i > tmp.size() - 1)
                                            break;
                                        while (tmp[i] != '|')
                                        {
                                            if (i > tmp.size() - 1)
                                                break;
                                            tmp2 += tmp[i];
                                            ++i;
                                        }
                                        if (tmp[i] == '|')
                                        {
                                            tmp3.push_back(tmp2);
                                            tmp2.clear();
                                        }
                                        else
                                        {
                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: |");
                                        }
                                        ++i;
                                    }
                                    if (tmp[i] == '~')
                                    {
                                        ++i;
                                        if (tmp3.size() > 0)
                                        {
                                            ENUM_EXE::executables__.second.StaticLibrary = tmp3;
                                        }
                                        tmp2.clear();
                                        tmp3.clear();
                                        while (tmp[i] != '~')
                                        {
                                            if (i > tmp.size() - 1)
                                                break;
                                            tmp2 += tmp[i];
                                            ++i;
                                        }
                                        if (tmp[i] == '~')
                                        {
                                            ++i;
                                            ENUM_EXE::point_of_entry = tmp2;
                                            tmp2.clear();
                                            ch = tmp[i];
                                            ++i;
                                            if (tmp[i] == '~')
                                            {
                                                ++i;
                                                ENUM_EXE::executables__.second.userTemplate = (char)ch;
                                                tmp2.clear();
                                                while (tmp[i] != '~')
                                                {
                                                    if (i > tmp.size() - 1)
                                                        break;
                                                    while (tmp[i] != '|')
                                                    {
                                                        if (i > tmp.size() - 1)
                                                            break;
                                                        tmp2 += tmp[i];
                                                        ++i;
                                                    }
                                                    if (tmp[i] == '|')
                                                    {
                                                        tmp3.push_back(tmp2);
                                                        tmp2.clear();
                                                        ++i;
                                                    }
                                                }
                                                if (tmp[i] == '~')
                                                {
                                                    ++i;
                                                    ENUM_EXE::executables__.second.userTemplates = tmp3;
                                                    tmp2.clear();
                                                    tmp3.clear();
                                                    while (tmp[i] != '~')
                                                    {
                                                        std::string name_tmp = "";
                                                        while (tmp[i] != '-')
                                                        {
                                                            if (i > tmp.size() - 1)
                                                                break;
                                                            name_tmp += tmp[i];
                                                            ++i;
                                                        }
                                                        if (tmp[i] == '-' || tmp[i] == '\0')
                                                        {
                                                            if (i < tmp.size() - 1)
                                                            {
                                                                ++i;
                                                                std::string value = "";
                                                                if (tmp[i] == 'D' || tmp[i] == 'S')
                                                                {
                                                                    ++i;
                                                                    while (tmp[i] != '\'')
                                                                    {
                                                                        if (i > tmp.size() - 1)
                                                                            break;
                                                                        value += tmp[i];
                                                                        ++i;
                                                                    }
                                                                    if (tmp[i] == '\'')
                                                                    {
                                                                        variable::AD_PARAM.createVar(name_tmp, value);
                                                                        name_tmp.clear();
                                                                        value.clear();
                                                                    }
                                                                    else
                                                                    {
                                                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: \'");
                                                                    }
                                                                }
                                                                else if (tmp[i] == 'V')
                                                                {
                                                                    ++i;
                                                                    std::string value = "";
                                                                    std::string value_el = "";
                                                                    while (tmp[i] != '\'')
                                                                    {
                                                                        if (i > tmp.size() - 1)
                                                                            break;
                                                                        while (tmp[i] != '|')
                                                                        {
                                                                            value_el += tmp[i];
                                                                            if (i > tmp.size() - 1)
                                                                                break;
                                                                            ++i;
                                                                        }
                                                                        if (tmp[i] == '|')
                                                                        {
                                                                            value += value_el + ' ';
                                                                            value_el.clear();
                                                                        }
                                                                        else
                                                                        {
                                                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: |");
                                                                        }
                                                                    }
                                                                    if (tmp[i] == '\'')
                                                                    {
                                                                        variable::AD_PARAM.createVar(name_tmp, value);
                                                                        name_tmp.clear();
                                                                        value.clear();
                                                                    }
                                                                    else
                                                                    {
                                                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: \'");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: -");
                                                        }
                                                        if (i > tmp.size() - 1)
                                                            break;
                                                        ++i;
                                                    }
                                                    if (tmp[i] == '~')
                                                    {
                                                        tmp2.clear();
                                                        tmp3.clear();
                                                        ++i;
                                                        ch = tmp[i];
                                                        ++i;
                                                        if (tmp[i] == '~')
                                                        {
                                                            executables__.second.lang = (std::uint32_t)ch;
                                                            ++i;
                                                            while (tmp[i] != '~')
                                                            {
                                                                if (i > tmp.size() - 1)
                                                                    break;
                                                                tmp2 += tmp[i];
                                                                ++i;
                                                            }
                                                            if (tmp[i] == '~')
                                                            {
                                                                executables__.second.pathCompiler_ = tmp2;
                                                                tmp2.clear();
                                                                ++i;
                                                                while (tmp[i] != '~')
                                                                {
                                                                    if (i > tmp.size() - 1)
                                                                        break;
                                                                    tmp2 += tmp[i];
                                                                    ++i;
                                                                }
                                                                if (tmp[i] == '~')
                                                                {
                                                                    executables__.second.pathLinker_ = tmp2;
                                                                    tmp2.clear();
                                                                }
                                                                else
                                                                {
                                                                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                                                }
                                                            }
                                                            else
                                                            {
                                                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                                            }
                                                        }
                                                        else
                                                        {
                                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                                        }
                                                    }
                                                    else
                                                    {
                                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                                    }
                                                }
                                                else
                                                {
                                                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                                }
                                            }
                                            else
                                            {
                                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                            }
                                        }
                                        else
                                        {
                                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                        }
                                    }
                                    else
                                    {
                                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                    }
                                }
                                else
                                {
                                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                                }
                            }
                            else
                            {
                                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                            }
                        }
                        else
                        {
                            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                        }
                    }
                    else
                    {
                        error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                    }
                }
                else
                {
                    error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
                }
            }
            else
            {
                error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
            }
        }
        else
        {
            error__::ERR.callError("FATAL_ERR_SYNTAX_S", "Not found sym: ~");
        }
    }
    else
    {
        std::cout << "the specified file is not an exe_ENUM file" << std::endl;
        exit(12);
    }
}
std::pair<std::string, project::project__> &ENUM_EXE::get()
{
    return executables__;
}
ENUM_EXE::~ENUM_EXE()
{
}
void ENUM_EXE::stringWrite(std::ofstream &file, std::string str)
{
    for (uint64_t i = 0; i < str.size(); ++i)
    {
        byteWrite(file, (uint8_t)str[i]);
    }
}
void ENUM_EXE::byteWrite(std::ofstream &file, const char &ch)
{
    file << ch;
}
