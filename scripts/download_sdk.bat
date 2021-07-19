@echo off
cd /D "%~dp0"
call git clone --recursive https://github.com/steinbergmedia/vst3sdk.git ..\extern\VST3_SDK
cd ..
