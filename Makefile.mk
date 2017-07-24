APPS = \
	gen_cube_perm \
	cube444 \
	cube555 \
	cube666 \
	corners_cube \
	fixed_edges_cube \
	coupled_edges_cube \
	center_edges \
	center_corners_cube \
	center_corners_cube2 \
	center_corners_cube3 \
	center_edges_cube \
	test_cube \
	test_cube666_solve \
	test_cube666_solve_Ze \
	test_cube666_shuffle \
	test_cube666_moves \
	test_center_edges_even \
	cube444_comp \
	test_center_edges_toPermutationN

OBJECTS = \
	faces.o \
	fixed_edges.o	\
	coupled_edges.o \
	corners.o \
	_cube222.o _cube333.o _cube444.o _cube555.o _cube666.o \
	edge_positions.o

all:	$(APPS) $(OBJECTS)

gen_cube_perm: gen_cube_perm.cpp
	$(CXX) -O3 -Wall --pedantic -std=c++11 -o $@ $<

faces.o: faces.cpp faces.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube222.o: _cube222.cpp _cube222.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube333.o: _cube333.cpp _cube333.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube444.o: _cube444.cpp _cube444.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube555.o: _cube555.cpp _cube555.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube666.o: _cube666.cpp _cube666.h
	$(CXX) -O3 -Wall --pedantic --ansi -c -o $@ $<

edge_positions.o: edge_positions.cpp edge_positions.h
	$(CXX) -c -O3 -Wall --pedantic --ansi -c -o $@ $<

corners.o: corners.cpp corners.h
	$(CXX) -c -O3 -Wall --pedantic --ansi -c -o $@ $<

cube444: cube444.cpp _cube444.o cubeNNN.h
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube444.o

cube555: cube555.cpp cubeNNN.h _cube555.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube555.o

cube666: cube666.cpp cubeNNN.h _cube666.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_solve: test_cube666_solve.cpp cubeNNN.h _cube666.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_solve_Ze: test_cube666_solve_Ze.cpp cubeNNN.h _cube666.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_shuffle: test_cube666_shuffle.cpp cubeNNN.h _cube666.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_moves: test_cube666_moves.cpp cubeNNN.h _cube666.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

corners_cube: corners_cube.cpp corners.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< corners.o

fixed_edges_cube: fixed_edges_cube.cpp fixed_edges.o edge_positions.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< fixed_edges.o edge_positions.o

fixed_edges.o: fixed_edges.h fixed_edges.cpp
	$(CXX) -c -O3 -Wall --pedantic --ansi -o $@ fixed_edges.cpp

coupled_edges.o: coupled_edges.h coupled_edges.cpp edge_positions.o
	$(CXX) -c -O3 -Wall --pedantic --ansi -o $@ coupled_edges.cpp 

coupled_edges_cube: coupled_edges_cube.cpp coupled_edges.o edge_positions.o
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $< coupled_edges.o edge_positions.o

center_edges: center_edges.cpp
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $<

center_edges_cube: center_edges_cube.cpp center_edges_old.h
	$(CXX) -O3 -Wall --pedantic -std=c++14 -o $@ $<

center_corners_cube: center_corners_cube.cpp 
	$(CXX) -O3 -Wall --pedantic --ansi -o $@ $<

center_corners_cube2: center_corners_cube2.cpp center_corners.h faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++11  -o $@ $< faces.o

center_corners_cube3: center_corners_cube3.cpp center_corners.h faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++11 -o $@ $< faces.o


test_center_edges_even: test_center_edges_even.cpp center_edges_old.h center_edges.h faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++11 -o $@ $< faces.o

test_cube: test_cube.cpp center_corners.h center_edges_old.h corners.o fixed_edges.o faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++14 -o $@ $< corners.o fixed_edges.o edge_positions.o faces.o

cube444_comp: cube444_comp.cpp corners.o coupled_edges.o edge_positions.o center_corners.h faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++11 -o $@ $< corners.o edge_positions.o coupled_edges.o faces.o

test_center_edges_toPermutationN: test_center_edges_toPermutationN.cpp center_edges.h faces.o
	$(CXX) -O3 -Wall --pedantic -std=c++11 -o $@ $< faces.o
clean: 
	@rm -fv $(APPS) $(OBJECTS)
