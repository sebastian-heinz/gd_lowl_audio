# Non functional cmake build file used to provide editor support to the project.
cmake_minimum_required(VERSION 3.6)
project(godot)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GODOT_ROOT_DIR ../../..)

file(GLOB_RECURSE SOURCES ${GODOT_ROOT_DIR}/*.c**)
file(GLOB_RECURSE HEADERS ${GODOT_ROOT_DIR}/*.h**)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(
        ${PROJECT_NAME}
        SYSTEM PUBLIC
        ${GODOT_ROOT_DIR}
        ${GODOT_ROOT_DIR}/modules/tachy
        ${GODOT_ROOT_DIR}/modules/tachy/component
        ${GODOT_ROOT_DIR}/modules/tachy/data
        ${GODOT_ROOT_DIR}/modules/tachy/ext
        ${GODOT_ROOT_DIR}/modules/tachy/manager
        ${GODOT_ROOT_DIR}/modules/tachy/model
        ${GODOT_ROOT_DIR}/modules/tachy/packet
        ${GODOT_ROOT_DIR}/modules/tachy/scene
        ${GODOT_ROOT_DIR}/modules/tachy/server
        ${GODOT_ROOT_DIR}/modules/tachy/server/audio
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/src
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/include
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/third_party/portaudio/include
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/third_party/readerwriterqueue
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/third_party/concurrentqueue
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/third_party/dr_libs
        ${GODOT_ROOT_DIR}/modules/gd_lowl_audio/lowl_audio/third_party/r8brain-free-src
)

add_definitions(-DLOWL_DRIVER_DUMMY)
add_definitions(-DLOWL_DRIVER_PORTAUDIO)
add_definitions(-DLOWL_UNIX)