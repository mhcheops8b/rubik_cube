#pragma once

#ifndef __CORNERS_H__
#define __CORNERS_H__

#include <iostream>
#include <ostream>
#include <string>
#include "rubik_moves.h"

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
private:
	int perm[8];
	int orient[8];
};


}
#endif
