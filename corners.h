#pragma once

#ifndef __CORNERS_H__
#define __CORNERS_H__

#include <iostream>
#include <ostream>
#include <string>
#include "rubik_moves.h"
#include "cubeNNN.h"

namespace rubik_cube {

class Corners {

public:
	Corners();

	void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	friend Corners &operator*(Corners &c1, const moves &f);
	// L move
	void apply_L();
	// R move
	void apply_R();
	// U move
	void apply_U(); 
	// D move
	void apply_D(); 
	// F move
	void apply_F(); 
	// B move
	void apply_B(); 

	// constant positions for display
	static const std::string positions[3][8];
	
	// debug function
	void toPermutationN();

	// apply corner permutations into existing one
	template<int N>
	Permutation<N> toPermutationN(Permutation<N> &in);
private:
	// helper function for conversion to Permutation<N>
	int get_index(int position, char face, int cube_dim);

	int perm[8];
	int orient[8];
};

template<int N>
Permutation<N> Corners::toPermutationN(Permutation<N> &in) {

	Permutation<N> output(in);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			int idx1 = get_index(perm[i], positions[orient[i]][perm[i]].at(j), N),
			idx2 = get_index(i, positions[0][i].at(j), N);

			if (idx1 != idx2) 
				output._components[in._components[idx1]] = in._components[idx2];
		}
	}
	return output;
}


}
#endif
