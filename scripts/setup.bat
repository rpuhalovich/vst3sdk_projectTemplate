@echo off
cd /D "%~dp0"
call git clone --recursive https://github.com/steinbergmedia/vst3sdk.git ..\extern\VST3_SDK
call git clone --recursive https://github.com/steinbergmedia/vst3projectgenerator.git ..\extern\vst3projectgenerator
call cmake -S ../extern/vst3projectgenerator -B ../extern/vst3projectgenerator/build -G"Visual Studio 16 2019"
cd ..
