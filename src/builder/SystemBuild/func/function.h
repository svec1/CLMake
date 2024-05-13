#ifndef FUNC__H_
    #define FUNC__H_
    #include "../../buildHead.h"

    using namespace variable;

    cdecl inline extern void set(build::inst &INST);
    cdecl inline extern void _project(build::inst &INST);
    cdecl inline extern void create_executable(build::inst &INST);
    cdecl inline extern void create_Library(build::inst &INST);
    cdecl inline extern void create_Dynamic_Library(build::inst &INST);
    cdecl inline extern void link_Library(build::inst &INST);
    cdecl inline extern void link_Dynamic_Library(build::inst &INST);
    cdecl inline extern void call_Command(build::inst &INST);
    cdecl inline extern void include_File(build::inst &INST);
    cdecl inline extern void parse_File(build::inst &INST);
    cdecl inline extern void export_VarFile(build::inst &INST);
    cdecl inline extern void add_flags(build::inst &INST);
    cdecl inline extern void debug(build::inst &INST);
    cdecl inline extern void add_standart_C(build::inst &INST);
    cdecl inline extern void add_standart_CPP(build::inst &INST);
    cdecl inline extern void add_AdditionalParam(build::inst &INST);
    cdecl inline extern void use_Templates(build::inst &INST);
    cdecl inline extern void uw_Templates(build::inst &INST);
    cdecl inline extern void add_PathCompiler(build::inst &INST);
    cdecl inline extern void add_PathLinker(build::inst &INST);
    cdecl inline extern void set_Language(build::inst &INST);
    cdecl inline extern void create_ConfProject(build::inst &INST);
    cdecl inline extern void sc_target(build::inst &INST);

#endif