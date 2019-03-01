#pragma once
#ifndef __COUPLED_EDGES_H__
#define __COUPLED_EDGES_H__

#include <ostream>
//#include "fixed_edges.h"
#include "rubik_moves.h"
#include "cubeNNN.h"
#include "edge_positions.h"

namespace rubik_cube {

class Coupled_edges {
public:
	Coupled_edges();
	// set cube to initial position
	void init();

	void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	// combination of both 12 a-positions and 12 b-positions to one permutation
	void disp_perm24();
	// signum of the perm24
	int perm24_signum();
	void to_perm24(int (&perm)[24]);
	void toPermutationN();

	template <int N>
	Permutation<N> toPermutationN(Permutation<N> &in);

	friend Coupled_edges &operator*(Coupled_edges &c1, const moves &f);

	void apply_L(); 
	void apply_R(); 
	void apply_U(); 
	void apply_D(); 
	void apply_F(); 
	void apply_B(); 
	void apply_ML(); 
	void apply_MR(); 
	void apply_MU(); 
	void apply_MD(); 
	void apply_MF(); 
	void apply_MB(); 

private:
	int get_index(int position, char face, bool ab, int cube_dim, int layer);

	int perm_a[12];
	int orient_a[12];

	int perm_b[12];
	int orient_b[12];

};

template <int N>
Permutation<N> Coupled_edges::toPermutationN(Permutation<N> &in) {
	Permutation<N> output(in);

	int num_layers = (N % 2 == 0? (N - 2) / 2: (N - 3) / 3);

	for (int l = 1; l <= num_layers; l++) {
		// a positions
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 2; j++) {
				int idx1 = get_index(perm_a[i], edge_positions[orient_a[i]][perm_a[i]].at(j), orient_a[i] == 1, N, l),
				idx2 = get_index(i, edge_positions[0][i].at(j), false, N, l);
				if (idx1 != idx2)
					output._components[idx1] = in._components[idx2];
			}
		}

		// b positions
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 2; j++) {
				int idx1 = get_index(perm_b[i], edge_positions[orient_b[i]][perm_b[i]].at(j), orient_b[i] == 0, N, l),
				idx2 = get_index(i, edge_positions[0][i].at(j), true, N, l);
				if (idx1 != idx2)
					output._components[idx1] = in._components[idx2];

			}
		}
	}
	return output;
}

}

#endif
