cmake_minimum_required(VERSION 3.10)

project(SmartPtr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(shared_pt)
add_subdirectory(unique_ptr)
add_subdirectory(weak_pt)
add_subdirectory(smart_pt)

