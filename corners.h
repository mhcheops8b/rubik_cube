#pragma once

#ifndef __CORNERS_H__
#define __CORNERS_H__

#include <iostream>
#include <ostream>
#include "rubik_moves.h"

namespace rubik_cube {

class Corners {

public:
	Corners();

	void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	friend Corners &operator*(Corners &c1, const moves &f);

	friend void apply_R(Corners &corn); 
	friend void apply_L(Corners &corn); 
	friend void apply_U(Corners &corn); 
	friend void apply_D(Corners &corn); 
	friend void apply_F(Corners &corn); 
	friend void apply_B(Corners &corn); 

private:
	int perm[8];
	int orient[8];

};


}
#endif
