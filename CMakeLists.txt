# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SAMS")

include_directories("./include")
aux_source_directory(. SRCS)
add_executable(SAMS ${SRCS})
