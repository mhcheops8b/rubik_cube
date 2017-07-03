#include <iostream>
#include <iomanip>
#include "fixed_edges.h"

int main() {
	fixed_edges new_cube;

	new_cube.disp();

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
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_L(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	apply_U(new_cube);
	apply_ML(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_L(new_cube);
	apply_U(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);
	apply_L(new_cube);

	new_cube.disp();
	

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
