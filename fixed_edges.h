#pragma once

#ifndef __FIXED_EDGES_H__
#define __FIXED_EDGES_H__

#include <ostream>
#include "rubik_moves.h"
#include "edge_positions.h"
#include "cubeNNN.h"
	
namespace rubik_cube {

class Fixed_edges {

public:
	Fixed_edges();

	void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);

	void toPermutationN(int cube_dim);

	template <int N>
	Permutation<N> toPermutationN(Permutation<N> &in);

	friend Fixed_edges& operator*(Fixed_edges &fe, const moves &f);

	void apply_L();
	void apply_R();
	void apply_U();
	void apply_D();
	void apply_F();
	void apply_B();
	void apply_ML();
	void apply_MR();
	void apply_MF();
	void apply_MB();
	void apply_MU();
	void apply_MD();


private:
	int get_index(int position, char face, int cube_dim);

	int perm[12];
	int orient[12];
};

template <int N>
Permutation<N> Fixed_edges::toPermutationN(Permutation<N> &in) {
	Permutation<N> output(in);

	for (int i = 0; i < 12; i++) {
		//std::cout << edge_positions[orient[i]][perm[i]] << "->" << edge_positions[0][i] << '\n';

		for (int j = 0; j < 2; j++) {
			int idx1 = get_index(perm[i], edge_positions[orient[i]][perm[i]].at(j), N),
			idx2 = get_index(i, edge_positions[0][i].at(j),  N);

			if (idx1 != idx2)
				output._components[idx1] = in._components[idx2];
//				std::cout << idx1 << "->" << idx2 << ", ";

		}
//		std::cout << '\n';
		
	}

	return output;
}

}


#endif
