#include <iostream>
#include <iomanip>
#include "coupled_edges.h"

using namespace rubik_cube;

int main() {
	Coupled_edges new_cube;

	new_cube.disp();
	new_cube.disp_cube();
	std::cout << "\t---\n";

//	apply_F(new_cube);
//	new_cube.disp();
//	std::cout << "\t---\n";
//	apply_F(new_cube);
//	new_cube.disp();
//	std::cout << "\t---\n";
//	apply_F(new_cube);
//	new_cube.disp();
//	std::cout << "\t---\n";
//	apply_F(new_cube);
//	new_cube.disp();
//	std::cout << "\t---\n";
//return 0;
#if 0
	apply_MR(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	apply_MR(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	apply_MR(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	apply_MR(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	return 0;
#endif

#if 0
	// U2 MU2 R2 MR2 U2 MR2 U2 MR2 R2 U2 MU2

	apply_U(new_cube);
	apply_U(new_cube);
	apply_MU(new_cube);
	apply_MU(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MU(new_cube);
	apply_MU(new_cube);
	new_cube.disp();
#endif

	// MR2 R2 B2 U2 ML U2 MR' U2 MR U2 F2 MR F2 ML' B2 R2 MR2
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_ML(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_MR(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	new_cube.disp();
	new_cube.disp_cube();
	std::cout << "\t---\n";
	new_cube.disp_perm24();
	std::cout << "\t---\n";
	std::cout << "Sgn: " << new_cube.perm24_signum() << '\n';


	return 0;
}
