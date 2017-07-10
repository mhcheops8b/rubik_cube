#pragma once
#ifndef __COUPLED_EDGES_H__
#define __COUPLED_EDGES_H__

#include <ostream>
//#include "fixed_edges.h"
#include "rubik_moves.h"

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

	int perm_a[12];
	int orient_a[12];

	int perm_b[12];
	int orient_b[12];

};

}

#endif
