cmake_minimum_required(VERSION 3.22)

project(znml
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The Android NDK toolchain file is supplied via CMakePresets.json
# (or -DCMAKE_TOOLCHAIN_FILE=.../android.toolchain.cmake on the command line).
if(NOT ANDROID)
    message(FATAL_ERROR
        "Not cross-compiling for Android. Configure with a preset, e.g.\n"
        "  cmake --preset android-arm64")
endif()

# ---- Dobby: lightweight inline-hook framework (vendored under third_party) ----
# EXCLUDE_FROM_ALL => only the target we actually link (dobby_static) is compiled,
# so Dobby's redundant shared libdobby.so is skipped.
set(DOBBY_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(DOBBY_BUILD_TEST OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/Dobby EXCLUDE_FROM_ALL)

# ---- Android native shared library ----
# Produces libznml.so, loadable from Java/Kotlin via System.loadLibrary("znml").
add_library(znml SHARED
    src/znml.cpp
)
target_include_directories(znml PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# dobby_static is linked statically so libznml.so is self-contained (no libdobby.so to ship).
target_link_libraries(znml PRIVATE
    dobby_static
    log          # Android liblog, for __android_log_print
)

# Android convention: file name lib<name>.so and matching SONAME.
# CMake sets OUTPUT_NAME -> libznml.so and SONAME -> libznml.so automatically.
set_target_properties(znml PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
    # Position-independent code is required for shared objects (NDK default is on).
    POSITION_INDEPENDENT_CODE ON
)

# Minimal example mod, emitted into the directory scanned by the loader.
add_library(minimal_mod SHARED
    examples/minimal_mod.cpp
)
target_include_directories(minimal_mod PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Dobby/include
)
target_link_libraries(minimal_mod PRIVATE
    dobby_static
    log
)
set_target_properties(minimal_mod PROPERTIES
    OUTPUT_NAME login_ui_mod
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/mods
    POSITION_INDEPENDENT_CODE ON
)

