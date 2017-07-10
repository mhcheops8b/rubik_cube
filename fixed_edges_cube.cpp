#include <iostream>
#include <iomanip>
#include "fixed_edges.h"

using namespace rubik_cube;

int main() {
	Fixed_edges new_cube;

	new_cube.disp();
	new_cube.disp_cube();

#if 0
	std::cout << "--\n";
	apply_L(new_cube);
	new_cube.disp();

	std::cout << "--\n";
	apply_L(new_cube);
	new_cube.disp();

	std::cout << "--\n";
	apply_L(new_cube);
	new_cube.disp();

	std::cout << "--\n";
	apply_L(new_cube);
	new_cube.disp();
#endif

	std::cout << "--\n";
	new_cube.apply_ML();
	new_cube.apply_ML();
	new_cube.apply_ML();
	new_cube.apply_L();
	new_cube.apply_U();
	new_cube.apply_U();
	new_cube.apply_U();
	new_cube.apply_L();
	new_cube.apply_L();
	new_cube.apply_L();
	new_cube.apply_U();
	new_cube.apply_ML();
	new_cube.apply_U();
	new_cube.apply_U();
	new_cube.apply_U();
	new_cube.apply_L();
	new_cube.apply_U();
	new_cube.apply_L();
	new_cube.apply_L();
	new_cube.apply_L();

	new_cube.disp();
	new_cube.disp_cube();
	

#if 0

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
#endif
	return 0;
}
