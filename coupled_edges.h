#pragma once
#ifndef __COUPLED_EDGES_H__
#define __COUPLED_EDGES_H__

#include <ostream>
#include "fixed_edges.h"
#include "rubik_moves.h"

namespace rubik_cube {

class Coupled_edges {
public:
	Coupled_edges();

	void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	// combination of both 12 a-positions and 12 b-positions to one permutation
	void disp_perm24();
	// signum of the perm24
	int perm24_signum();
	void to_perm24(int (&perm)[24]);

	friend Coupled_edges &operator*(Coupled_edges &c1, const moves &f);

	friend void apply_L(Coupled_edges &edge); 
	friend void apply_R(Coupled_edges &edge); 
	friend void apply_U(Coupled_edges &edge); 
	friend void apply_D(Coupled_edges &edge); 
	friend void apply_F(Coupled_edges &edge); 
	friend void apply_B(Coupled_edges &edge); 
	friend void apply_ML(Coupled_edges &edge); 
	friend void apply_MR(Coupled_edges &edge); 
	friend void apply_MU(Coupled_edges &edge); 
	friend void apply_MD(Coupled_edges &edge); 
	friend void apply_MF(Coupled_edges &edge); 
	friend void apply_MB(Coupled_edges &edge); 

protected:
	void init();

private:

	int perm_a[12];
	int orient_a[12];

	int perm_b[12];
	int orient_b[12];

};

}

#endif
