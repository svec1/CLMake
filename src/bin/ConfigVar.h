#pragma once
#include "include.h"

#if defined _WIN32
#include <Windows.h>
extern HANDLE handle;
#endif

static std::string NameProject = "";
static std::string NameExecutable = "";

static std::string pathProject;
static std::string pathFileCLMake;

static std::vector<std::string> SrcFiles;
static std::vector<std::string> LibFiles;
static std::vector<std::string> DllFiles;

extern double versionCLMake;

extern uint8_t C_STANDART;
extern uint8_t CPP_STANDART;

extern bool warning;
extern bool log_;

extern std::vector<std::string> pathCatalogLibStat;
extern std::vector<std::string> pathCatalogLibDLL;

extern std::string pathCompiler_;
extern std::string pathLinker_;
extern std::string pathArc_;
extern std::string pathllvm_ranlib;

extern std::string pathInclude;

extern bool regDLL;

extern std::uint32_t compiler; // 0 - c/c++, 1 - c#, 2 - asm;

extern std::string asm_lib;

extern std::vector<std::string> entry_point;

static std::string flags = "";
extern std::string LinkFlags;

extern const double CLMAKE_VERSION;

extern bool scold_VersionCLMake;

extern std::string compiler__;
extern std::string linker__;
extern std::string archivator__;
extern std::string runlib__;

extern std::vector<std::pair<std::string, std::uint32_t>> oth_commands;

extern std::uint64_t incFiles;

static bool exe = false;

extern bool find_compiler;
extern bool find_linker;
extern bool find_arc;
extern bool find_llvmrl;

extern bool workLINK;

extern std::string standartClmakeCompilerFlags;
extern std::string standartClmakeLinkerFlags;

extern bool user_template;
extern bool asm_;