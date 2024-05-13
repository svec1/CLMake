CLMAKE is a build system that is an unfinished project, with not very good code and with terrible performance due to the latest update (multi-threaded helper).
This assembly system will not be updated soon (although there is a chance that it will be if there are helpers*).
The build system is called one story, and it is in no way connected with Make, although it is connected with the Clang compiler as the main compiler for assembly.

***This project was created for educational purposes, although it intended otherwise.***
*And yes, this build system can be assembled with the same build system, and the finished file “CLMakeConfig.txt” is a CLMAKE config file as well as a regular CMAKE.*

***I also ask you to take into account that all files starting with "СL" (except "CLMakeLists.txt") are postbuild files of this build system.***
The file "ListPlugin.exp" is a file where you can add plugins that will be loaded before building the project (plugins are dll files). Although the loading of plugins is somehow carried out, there are no applications for it, a number of rules have not been written for the operation of the plugins and the code itself for calling functions from the plugin, etc.
