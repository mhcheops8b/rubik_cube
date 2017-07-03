#pragma once

#ifndef __FIXED_EDGES_H__
#define __FIXED_EDGES_H__

#include <ostream>
	
struct fixed_edges {

	int perm[12];
	int orient[12];

	fixed_edges();

	void disp(std::ostream &os = std::cout);

	friend void apply_R(fixed_edges &edge);
	friend void apply_L(fixed_edges &edge);
	friend void apply_U(fixed_edges &edge);
	friend void apply_D(fixed_edges &edge);
	friend void apply_F(fixed_edges &edge);
	friend void apply_B(fixed_edges &edge);
	friend void apply_ML(fixed_edges &edge);
	friend void apply_MR(fixed_edges &edge);
	friend void apply_MF(fixed_edges &edge);
	friend void apply_MB(fixed_edges &edge);
	friend void apply_MU(fixed_edges &edge);
	friend void apply_MD(fixed_edges &edge);

};


#endif
