project(visualizador)
project(visualizador_parallel)
project(visualizador_nao)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2


pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

# compile flags
SET(SIMDFLAG "-ffast-math -ftree-vectorize -mavx")
SET(SIMDFLAG2 "-ffast-math -ftree-vectorize -mavx2")
SET(OMPFLAG "-fopenmp")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OMPFLAG}")

# Add global definitions
add_executable(visualizador main.cpp visualizador.cpp)
add_executable(visualizador_parallel visualizador_parallel.cpp)
add_executable(visualizador_nao visualizador_nao.cpp)
target_link_libraries(visualizador ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})



