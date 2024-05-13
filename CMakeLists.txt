cmake_minimum_required(VERSION 3.2)


project(clmake)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

file(GLOB MAIN "src/main.cpp")
file(GLOB CONSOLEMANAGER "src/ConsoleManager/ConsoleManager.cpp")
file(GLOB SYSTEM_BUILDER "src/builder/SystemBuild/*.cpp")
file(GLOB SB_CLASS "src/builder/class/*.cpp" "src/builder/StreamEI/*.cpp")
file(GLOB BIN "src/bin/*.cpp" "src/builder/bin/serelization.cpp")
file(GLOB SETUP "src/builder/setup/assistant/*.cpp")
file(GLOB FUNC "src/builder/SystemBuild/func/*.cpp")

add_executable(${PROJECT_NAME} ${MAIN} ${CONSOLEMANAGER} ${SYSTEM_BUILDER} ${SB_CLASS} ${BIN} ${SETUP} ${FUNC})