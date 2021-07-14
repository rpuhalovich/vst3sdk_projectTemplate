cd $(dirname $0)
git clone --recursive https://github.com/steinbergmedia/vst3sdk.git ../extern/VST3_SDK
git clone --recursive https://github.com/steinbergmedia/vst3projectgenerator.git ../extern/vst3projectgenerator
cmake -S ../extern/vst3projectgenerator -B ../extern/vst3projectgenerator/build -GXcode
