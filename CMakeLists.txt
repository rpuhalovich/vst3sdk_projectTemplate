cmake_minimum_required(VERSION 3.14.0)

project(vst3sdk_projectTemplate CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

# --- src -------------------------------------------------
set(RESOURCE_DIR resource)
set(EXTERN_DIR extern)
set(SRC_DIR source)
set(vst3sdk_SOURCE_DIR ${EXTERN_DIR}/VST3_SDK)

file(GLOB_RECURSE src FILE ${SRC_DIR}/*.cpp ${SRC_DIR}/*.hpp ${SRC_DIR}/*.h)

set(src_resources "${RESOURCE_DIR}/myplugineditor.uidesc" "${RESOURCE_DIR}/win32resource.rc")
source_group(resource FILES "${vst3sdk_SOURCE_DIR}/public.sdk/source/main/dllmain.cpp")
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src} ${src_resources})

# --- lib -------------------------------------------------
# fxobjects
add_library(fxobjects ${EXTERN_DIR}/fxobjects/fxobjects.cpp)
set(tgt_inc ${EXTERN_DIR}/fxobjects)
set(lib ${lib} fxobjects)

# --- VST -------------------------------------------------
set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

# turns off creation of symbolic link that's on by default - on windows this needs admin privileges which is annoying
set(SMTG_CREATE_PLUGIN_LINK OFF)

smtg_add_vst3plugin(${PROJECT_NAME} ${src})

# --- VSTGUI Wanted ---
if(SMTG_ADD_VSTGUI)
    target_sources(${PROJECT_NAME} PRIVATE ${src_resources})
    target_link_libraries(${PROJECT_NAME} PRIVATE vstgui_support)
    smtg_add_vst3_resource(${PROJECT_NAME} ${src_resources})
endif()

smtg_add_vst3_snapshot(${PROJECT_NAME} ${RESOURCE_DIR}/snapshot.png)
smtg_add_vst3_snapshot(${PROJECT_NAME} ${RESOURCE_DIR}/snapshot_2.0x.png)

target_link_libraries(${PROJECT_NAME} PRIVATE ${lib} sdk)
target_include_directories(${PROJECT_NAME} PRIVATE ${tgt_inc})
target_precompile_headers(${PROJECT_NAME} PUBLIC
    <vector>
    <string>
    <map>
    <memory>
    <iostream>
    <unordered_map>
    <fstream>
    <sstream>
    <cmath>
)
source_group("Precompile Header File" FILES "${CMAKE_SOURCE_DIR}/build/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.cxx")

set_target_properties(fxobjects validator VST3Inspector PROPERTIES FOLDER "Libraries")

if(SMTG_MAC)
    smtg_set_bundle(${PROJECT_NAME} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(SMTG_WIN)
    target_sources(${PROJECT_NAME} PRIVATE resource/win32resource.rc)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
