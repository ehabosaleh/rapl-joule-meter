cmake_minimum_required(VERSION 3.5)
project(Ctest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/main")
find_package(Rapl REQUIRED CONFIG)

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/main/saxpy.cpp)
target_link_libraries(test PRIVATE rapl::rapl)
