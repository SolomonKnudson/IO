cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

#Stop module flags from being passed
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(IO LANGUAGES CXX)

add_library(IO INTERFACE)

target_include_directories(IO INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/"
)

target_compile_features(IO INTERFACE
  cxx_std_20
)

include(FetchContent)
FetchContent_Declare(
  Operator
  GIT_REPOSITORY https://github.com/SolomonKnudson/Operator.git
  GIT_TAG main
)
FetchContent_MakeAvailable(Operator)
target_link_libraries(IO INTERFACE Operator)

#For internal development only
if(PROJECT_IS_TOP_LEVEL)
add_library(debug_warnings INTERFACE)
target_compile_options(debug_warnings INTERFACE
  $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wmissing-declarations
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wformat=2
    -Wnull-dereference
    -Woverloaded-virtual
    -Wsign-conversion
    -Wundef
    -Wdouble-promotion
    -Wcast-align
    -Wcast-qual
    # -Werror
   >
)

add_library(debug_build_flags INTERFACE)
target_compile_options(debug_build_flags INTERFACE
  $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:
    -O0
    -g3
   >
)

target_link_libraries(IO INTERFACE
  debug_warnings
  debug_build_flags
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/app)
endif()
