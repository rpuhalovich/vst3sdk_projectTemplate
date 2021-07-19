cd "$(dirname "$0")"

EXTERN_DIR=../extern
PROJECT_GEN_DIR=${EXTERN_DIR}/vst3projectgenerator

git clone --recursive https://github.com/steinbergmedia/vst3projectgenerator.git ${PROJECT_GEN_DIR}
cmake -S ${PROJECT_GEN_DIR} -B ${PROJECT_GEN_DIR}/build -GXcode
cmake --build ${PROJECT_GEN_DIR}/build
open ${PROJECT_GEN_DIR}/build/Debug/VST3_Project_Generator.app
