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
	test_cube666_solve test_cube666_shuffle \
	test_cube666_moves \
	test_center_edges_even

OBJECTS = \
	fixed_edges.o	\
	coupled_edges.o \
	corners.o \
	_cube222.o _cube333.o _cube444.o _cube555.o _cube666.o \
	edge_positions.o

all:	$(APPS) $(OBJECTS)

gen_cube_perm: gen_cube_perm.cpp
	g++ -O3 -Wall --pedantic -std=c++11 -o $@ $<

_cube222.o: _cube222.cpp _cube222.h
	g++ -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube333.o: _cube333.cpp _cube333.h
	g++ -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube444.o: _cube444.cpp _cube444.h
	g++ -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube555.o: _cube555.cpp _cube555.h
	g++ -O3 -Wall --pedantic --ansi -c -o $@ $<

_cube666.o: _cube666.cpp _cube666.h
	g++ -O3 -Wall --pedantic --ansi -c -o $@ $<

edge_positions.o: edge_positions.cpp edge_positions.h
	g++ -c -O3 -Wall --pedantic --ansi -c -o $@ $<

corners.o: corners.cpp corners.h
	g++ -c -O3 -Wall --pedantic --ansi -c -o $@ $<

cube444: cube444.cpp _cube444.o cubeNNN.h
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube444.o

cube555: cube555.cpp cubeNNN.h _cube555.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube555.o

cube666: cube666.cpp cubeNNN.h _cube666.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_solve: test_cube666_solve.cpp cubeNNN.h _cube666.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_shuffle: test_cube666_shuffle.cpp cubeNNN.h _cube666.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

test_cube666_moves: test_cube666_moves.cpp cubeNNN.h _cube666.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< _cube666.o

corners_cube: corners_cube.cpp corners.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< corners.o

fixed_edges_cube: fixed_edges_cube.cpp fixed_edges.o edge_positions.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< fixed_edges.o edge_positions.o

fixed_edges.o: fixed_edges.h fixed_edges.cpp
	g++ -c -O3 -Wall --pedantic --ansi -o $@ fixed_edges.cpp

coupled_edges.o: coupled_edges.h coupled_edges.cpp edge_positions.o
	g++ -c -O3 -Wall --pedantic --ansi -o $@ coupled_edges.cpp 

coupled_edges_cube: coupled_edges_cube.cpp coupled_edges.o edge_positions.o
	g++ -O3 -Wall --pedantic --ansi -o $@ $< coupled_edges.o edge_positions.o

center_edges: center_edges.cpp
	g++ -O3 -Wall --pedantic --ansi -o $@ $<

center_edges_cube: center_edges_cube.cpp center_edges_old.h
	g++ -O3 -Wall --pedantic -std=c++14 -o $@ $<

center_corners_cube: center_corners_cube.cpp
	g++ -O3 -Wall --pedantic --ansi -o $@ $<

center_corners_cube2: center_corners_cube2.cpp center_corners.h 
	g++ -O3 -Wall --pedantic -std=c++11  -o $@ $<

center_corners_cube3: center_corners_cube3.cpp center_corners.h 
	g++ -O3 -Wall --pedantic -std=c++11 -o $@ $<


test_center_edges_even: test_center_edges_even.cpp center_edges_old.h center_edges.h
	g++ -O3 -Wall --pedantic -std=c++11 -o $@ $<

test_cube: test_cube.cpp center_corners.h center_edges_old.h
	g++ -O3 -Wall --pedantic -std=c++14 -o $@ $<

clean: 
	@rm -fv $(APPS) $(OBJECTS)
