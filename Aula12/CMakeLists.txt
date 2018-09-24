cmake_minimum_required(VERSION 3.9)
find_package(Boost 1.67 REQUIRED COMPONENTS filesystem)
message("Boosty version" ${Boost_VERSION})
include_directories( ${Boost_INCLUDE_DIRS} )   
project (projeto_basico)
add_executable(fs exemplo_fs.cpp)


