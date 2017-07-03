#include <iostream>
#include <iomanip>
#include <ostream>
#include "center_corners.h"

int main() {

	Center_corners<5> new_cube;

	// just to instantiate all
	apply_L(new_cube);
	apply_R(new_cube);
	apply_U(new_cube);
	apply_F(new_cube);
	apply_B(new_cube);
	apply_D(new_cube);
	apply_ML<5,0>(new_cube);
	apply_MR<5,0>(new_cube);
	apply_MU<5,0>(new_cube);
	apply_MF<5,0>(new_cube);
	apply_MB<5,0>(new_cube);
	apply_MD<5,0>(new_cube);

	new_cube.disp();
	std::cout << "---\n";

	new_cube.init();
	new_cube.disp();
	std::cout << "---\n";

	// MR2 R2 B2 U2 ML U2 MR' U2 MR U2 F2 MR F2 ML' B2 R2 MR2
	apply_MR<5,0>(new_cube);
	apply_MR<5,0>(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_ML<5,0>(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR<5,0>(new_cube);
	apply_MR<5,0>(new_cube);
	apply_MR<5,0>(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR<5,0>(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_MR<5,0>(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_ML<5,0>(new_cube);
	apply_ML<5,0>(new_cube);
	apply_ML<5,0>(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_MR<5,0>(new_cube);
	apply_MR<5,0>(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	std::cout << "Sgn: " << signum(new_cube) << '\n';
	std::cout << "\t---\n";

	return 0;
}
