#pragma once

#ifndef __FIXED_EDGES_H__
#define __FIXED_EDGES_H__

#include <ostream>
#include "rubik_moves.h"
	
namespace rubik_cube {

class Fixed_edges {

public:
	Fixed_edges();

	void disp(std::ostream &os = std::cout);

	friend Fixed_edges& operator*(Fixed_edges &fe, const moves &f);

	friend void apply_R(Fixed_edges &edge);
	friend void apply_L(Fixed_edges &edge);
	friend void apply_U(Fixed_edges &edge);
	friend void apply_D(Fixed_edges &edge);
	friend void apply_F(Fixed_edges &edge);
	friend void apply_B(Fixed_edges &edge);
	friend void apply_ML(Fixed_edges &edge);
	friend void apply_MR(Fixed_edges &edge);
	friend void apply_MF(Fixed_edges &edge);
	friend void apply_MB(Fixed_edges &edge);
	friend void apply_MU(Fixed_edges &edge);
	friend void apply_MD(Fixed_edges &edge);

private:
	int perm[12];
	int orient[12];


};

}


#endif
