#include <iostream>
#include <ostream>
#include <string>

#include "corners.h"

using namespace rubik_cube;

#if 0
void orient_corners(corners &new_cube) {

	// R'
	apply_R(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	// D2
	apply_D(new_cube);
	apply_D(new_cube);
	// R
	apply_R(new_cube);
	// D
	apply_D(new_cube);
	// R'
	apply_R(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	// D
	apply_D(new_cube);
	// R
	apply_R(new_cube);
	// L
	apply_L(new_cube);
	// D2
	apply_D(new_cube);
	apply_D(new_cube);
	// L'
	apply_L(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	// D'
	apply_D(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	// L
	apply_L(new_cube);
	// D'
	apply_D(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	// L'
	apply_L(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
}
#endif

int main() {

	Corners new_cubeTTT;
	new_cubeTTT.disp();
	new_cubeTTT.disp_cube();
	std::cout << '\n';
	new_cubeTTT = new_cubeTTT * iL;// * L;
	new_cubeTTT.disp();

	new_cubeTTT.disp_cube();
	
	
	return 0;
	
#if 0
	
	corners new_cube;
	orient_corners(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	orient_corners(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	orient_corners(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";

	return 0;
#endif

#if 0
	corners new_cube;

	new_cube.disp();

	//std::cout << "--\n";
	//apply_L(new_cube);
	//new_cube.disp();

	//return 0;

	std::cout << "--\n";
	apply_L(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_D(new_cube);
	apply_B(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	apply_D(new_cube);
	apply_R(new_cube);

	new_cube.disp();

	return 0;
#endif
}
