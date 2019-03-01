cmake_minimum_required (VERSION 3.10.2)

project(rubik_cube)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -O3 -Wextra")

add_executable(cube444_comp $<TARGET_OBJECTS:corners> $<TARGET_OBJECTS:edge_positions> $<TARGET_OBJECTS:coupled_edges> $<TARGET_OBJECTS:faces> cube444_comp.cpp)

add_executable(gen_cube_perm gen_cube_perm.cpp)

add_executable(cube444 $<TARGET_OBJECTS:_cube444> cube444.cpp)

add_executable(cube555 $<TARGET_OBJECTS:_cube555> cube555.cpp)

add_executable(cube666 $<TARGET_OBJECTS:_cube666> cube666.cpp)

add_executable(corners_cube $<TARGET_OBJECTS:corners> corners_cube.cpp)

add_executable(coupled_edges_cube $<TARGET_OBJECTS:coupled_edges> $<TARGET_OBJECTS:edge_positions> coupled_edges_cube.cpp)

add_library(faces OBJECT faces.cpp faces.h)

add_library(corners OBJECT corners.cpp corners.h)

add_library(_cube444 OBJECT _cube444.cpp _cube444.h cubeNNN.h)

add_library(_cube555 OBJECT _cube555.cpp cubeNNN.h)

add_library(_cube666 OBJECT _cube666.cpp cubeNNN.h)

add_library(fixed_edges OBJECT fixed_edges.cpp fixed_edges.h)

add_library(edge_positions OBJECT edge_positions.cpp edge_positions.h)

add_library(coupled_edges OBJECT coupled_edges.cpp coupled_edges.h)


add_executable(fixed_edges_cube $<TARGET_OBJECTS:fixed_edges> $<TARGET_OBJECTS:edge_positions> fixed_edges_cube.cpp)

add_executable(test_center_edges_toPermutationN $<TARGET_OBJECTS:faces> test_center_edges_toPermutationN.cpp)


add_executable(center_edges center_edges.cpp)


add_executable(center_edges_cube center_edges_cube.cpp)


add_executable(center_corners_cube center_corners_cube.cpp)

add_executable(center_corners_cube2 $<TARGET_OBJECTS:faces> center_corners_cube2.cpp)

add_executable(center_corners_cube3 $<TARGET_OBJECTS:faces> center_corners_cube3.cpp)


add_executable(test_cube $<TARGET_OBJECTS:corners> $<TARGET_OBJECTS:fixed_edges> $<TARGET_OBJECTS:faces> $<TARGET_OBJECTS:edge_positions> test_cube.cpp)


add_executable(test_cube666_solve $<TARGET_OBJECTS:_cube666> test_cube666_solve.cpp)

add_executable(test_cube666_solve_Ze $<TARGET_OBJECTS:_cube666> test_cube666_solve_Ze.cpp)

add_executable(test_cube666_shuffle $<TARGET_OBJECTS:_cube666> test_cube666_shuffle.cpp)

add_executable(test_cube666_moves $<TARGET_OBJECTS:_cube666> test_cube666_moves.cpp)

add_executable(test_center_edges_even $<TARGET_OBJECTS:faces> test_center_edges_even.cpp center_edges_old.h)
