# vst3sdk_projectTemplate

## Introduction

This is a repository that contains all my preferred changes when creating a new VST3_SDK project.

It features:
- A cleaned up Cmake script that's easy to modify for a new project.
- Will Pirkle's fxobjects.h, fxobjects.cpp and filters.h files (http://www.aspikplugins.com/) as a library.
- My own Filter and Biquad object files for a simple usage example.
- Scripts for building the vst3projectgenerator projects such that it is easy to compile and create the customized source files with a GUI interface.

It also has the incredibly annoying SMTG_CREATE_PLUGIN_LINK variable set to OFF.

## Getting Started

### Dependencies

Cmake: ```https://cmake.org/``` and Visual Studio/Xcode depending on platform (only Windows and MacOS are supported).

### Setup

Clone using: ```git clone https://github.com/rpuhalovich/vst3sdk_projectTemplate.git```.

Use either ```setup.bat``` or ```setup.sh``` to download the required dependencies and build the Visual Studio/Xcode projects. Then open the ```vst3_project_generator_distribution.sln```/```vst3_project_generator_distribution.xcodeproj``` file found in ```extern/vst3projectgenerator/build/``` and run the ```vst3projectgenerator``` target.

Fill out the fields in the GUI application and set the ```Output Directory:``` to be ```extern/vst3projectgenerator/``` (or anywhere else really, but I recommended here so as to be a part of the .gitignore). Finally, copy the contents of ```extern/vst3projectgenerator/(YOUR PLUGIN NAME)/source/``` to ```source/```. 

Run ```build_visual_studio.bat```/```build_xcode.sh``` and have fun coding a VST plugin!
