#include "../builder/buildHead.h"

#if defined _WIN32
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

bool asm_ = false;

bool assembly__ = false;
bool warning = false;
bool log_ = false;

bool regDLL = false;

uint8_t C_STANDART = 89;
uint8_t CPP_STANDART = 14;

std::string pathCompiler_ = "";
std::string pathLinker_ = "";
std::string pathArc_ = "";
std::string pathllvm_ranlib = "";

std::string pathInclude;

std::vector<std::string> pathCatalogLibStat;
std::vector<std::string> pathCatalogLibDLL;

std::uint32_t compiler = 0;

std::string compiler__ = "clang.exe";
std::string linker__ = "clang.exe";
std::string archivator__ = "llvm-ar.exe";
std::string runlib__ = "llvm-ranlib.exe";

std::string asm_lib = "kernel32.dll user32.dll ";

std::vector<std::string> entry_point;

std::string LinkFlags = "";

std::vector<std::pair<std::string, std::uint32_t>> oth_commands;

std::uint64_t incFiles = 0;

const double CLMAKE_VERSION = 0.1;
double versionCLMake;

bool scold_VersionCLMake;

bool find_compiler = false;
bool find_linker = false;
bool find_arc = false;
bool find_llvmrl = false;

bool workLINK = true;

bool user_template = false;

std::string standartClmakeCompilerFlags = "-Wall -Wextra -Waddress -Warray-bounds -Wbool-operation -Wunused-value -Wchar-subscripts -Wcomment -Wint-in-bool-context -Wuninitialized -Wvec-elem-size -Wmisleading-indentation -Wmisleading-indentation -Wparentheses -Wpessimizing-move -Wsign-compare -Wsizeof-pointer-div -Wstrict-aliasing -Wtautological-compare -Wuninitialized -Wunused-function -Wunused-variable -Wpedantic -Wsign-promo";
std::string standartClmakeLinkerFlags = "-fuse-ld=lld";

std::vector<
    std::pair</* name, project */
              std::string,
              project::project__>>
    executable::executables_;

std::vector<project::project__> project::project_;

namespace variable
{
    variable<double> DOUBLE_;
    variable<std::string> STRING_;
    variable</* Linker_flags, config_project */ std::pair<std::string, executable::ENUM_EXE>> TARGETS_;
    variable<std::pair<std::string, std::string>> STRUCT_;
    variable<std::pair<std::string, std::string>> FILE_PATH_;
    VariableVector<std::string> VEC_STRING_;
    VariableVector<std::string> templateGenerate;
    variable<std::string> AD_PARAM;
}

namespace error__
{
    error ERR;
}
