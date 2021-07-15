# vst3sdk_projectTemplate

## Introduction

This is a repository that contains all my preferred changes when creating a new VST3_SDK project.

It features:
- A cleaned up CMake script that's easy to modify for a new project, with a preconfigured precompiled header.
- Will Pirkle's fxobjects.h, fxobjects.cpp and filters.h files (http://www.aspikplugins.com/) as a library.
- My own Filter and Biquad object files for a simple usage example.
- A script that downloads the VST3_SDK as well as configures and copies all the necessary source files into the appropriate directories.
- A Reaper project file with a sample song for testing any audio plugins on.

It also has the incredibly annoying SMTG_CREATE_PLUGIN_LINK variable set to OFF.

## Getting Started

### Dependencies

CMake (https://cmake.org/) and Visual Studio/Xcode depending on platform (only Windows and MacOS are supported).

### Setup

Edit ```scripts/setup.sh``` to contain the desired plugin information, then run it.

Edit the CMakeLists.txt script to contain the preferred project name and file prefix. Then run ```build_visual_studio.bat```/```build_xcode.sh``` and have fun coding a VST plugin!

## Notes

I'm using ```file(GLOB_RECURSE ...)``` for the simplicity of a gathering source files into a variable. Therefore, every time a source file is added, run the ```build_visual_studio.bat```/```build_xcode.sh``` scripts to refresh the project files (yes, I'm aware that the CMake documentation advises against this but hush, this is more for single developer projects).

The Reaper project file must be added as an argument manually in Visual Studio/Xcode with the startup application obviously being set to Reaper. Most likley the sample song won't be found when the project is as the absolute paths would be different but it is located in host_projects/.
