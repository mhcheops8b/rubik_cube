#pragma once
#ifndef __COUPLED_EDGES_H__
#define __COUPLED_EDGES_H__

#include <ostream>
#include "fixed_edges.h"

struct coupled_edges {
	fixed_edges ea;
	fixed_edges eb;

	coupled_edges();

	void disp(std::ostream &os = std::cout);
	// combination of both 12 a-positions and 12 b-positions to one permutation
	void disp_perm24();
	// signum of the perm24
	int perm24_signum();
};


void apply_L(coupled_edges &edge); 
void apply_R(coupled_edges &edge); 
void apply_U(coupled_edges &edge); 
void apply_D(coupled_edges &edge); 
void apply_F(coupled_edges &edge); 
void apply_B(coupled_edges &edge); 
void apply_ML(coupled_edges &edge); 
void apply_MR(coupled_edges &edge); 
void apply_MU(coupled_edges &edge); 
void apply_MD(coupled_edges &edge); 
void apply_MF(coupled_edges &edge); 
void apply_MB(coupled_edges &edge); 

#endif
