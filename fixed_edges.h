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
	void disp_cube(std::ostream &os = std::cout);

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
	int perm[12];
	int orient[12];
};

}


#endif
