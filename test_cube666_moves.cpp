#include <iostream>
#include "_cube666.h"

int main() {

	Permutation<6> cube;

	orient_z(cube);
	orient_z(cube);
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tCU  = middle block U towards F\n";
	std::cout << "\tCU' = middle block U towards B\n";
	std::cout << "\tCU U CU' U CU U |xx| CU' U CU U CU' U |U^2|\n";
	std::cout << "---\n";
	cube = cube
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6  
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6 
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6
		* U_6 * U_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";

	cube = I_6;
	orient_z(cube);
	orient_z(cube);
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tCU  = middle block U towards F\n";
	std::cout << "\tCU' = middle block U towards B\n";
	std::cout << "\tCU U CU' U CU U |U| CU' U CU U CU' U |U|\n";
	std::cout << "---\n";
	cube = cube
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6  
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* U_6
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6 
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6
		* U_6 
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";


	cube = I_6;
	orient_z(cube);
	orient_z(cube);
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tCU  = middle block U towards F\n";
	std::cout << "\tCU' = middle block U towards B\n";
	std::cout << "\tCU U CU' U CU U |U^2| CU' U CU U CU' U |xx|\n";
	std::cout << "---\n";
	cube = cube
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6  
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* U_6 * U_6
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6 
		* ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 
		* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";

	cube = I_6;
	std::cout << "---\n";
	std::cout << "\tMR1 U' MR2 U MR1' U' MR2' U\n";
	std::cout << "---\n";
	// 23 -> 82 -> 95
	cube = cube * MR1_6 * U_6 * U_6 * U_6 * MR2_6 * U_6 * MR1_6 * MR1_6 * MR1_6 * U_6 * U_6 * U_6 * MR2_6 * MR2_6 * MR2_6 * U_6;
	cube.disp_perm_reduced(std::cout);
	std::cout << "---\n";
	cube.disp_cube_fancy(std::cout);

	std::cout << "-----------------------------------------------------\n";

	cube = I_6;
	// 10 -> 86 -> 82
	std::cout << "---\n";
	std::cout << "\tMR2 U' ML1' U MR2' U' ML1 U\n";
	std::cout << "---\n";
	cube = cube * MR2_6 * U_6 * U_6 * U_6 * ML1_6 * ML1_6 * ML1_6 *  U_6 * MR2_6 * MR2_6 * MR2_6 * U_6 * U_6 * U_6 * ML1_6 * U_6;
	cube.disp_perm_reduced(std::cout);
	std::cout << "---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";


	cube = I_6;
	std::cout << "---\n";
	std::cout << "\tMR2 U' ML2' U MR2' U' ML2 U\n";
	std::cout << "---\n";
	cube = cube * MR2_6 * U_6 * U_6 * U_6 * ML2_6 * ML2_6 * ML2_6 *  U_6 * MR2_6 * MR2_6 * MR2_6 * U_6 * U_6 * U_6 * ML2_6 * U_6;
	cube.disp_perm_reduced(std::cout);
	std::cout << "---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";

	
	cube = I_6;
	std::cout << "---\n";
	std::cout << "\tMR1 U' ML2' U MR1' U' ML2 U\n";
	std::cout << "---\n";
	cube = cube * MR1_6 * U_6 * U_6 * U_6 * ML2_6 * ML2_6 * ML2_6 *  U_6 * MR1_6 * MR1_6 * MR1_6 * U_6 * U_6 * U_6 * ML2_6 * U_6;
	cube.disp_perm_reduced(std::cout);
	std::cout << "---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";

	// Thm 16
	Permutation<6> outcube;
	std::cout << "---\n";
	std::cout << "\tcommutator [a,b] = a b a' b'\n";
	std::cout << "\t(thm16 move1) m16_1 = [[MF1,MD1],U']\n";
	std::cout << "---\n";

	outcube = MF1_6 * MD1_6 * !MF1_6 * !MD1_6 * !U_6 * MD1_6 * MF1_6 * !MD1_6 * !MF1_6 * U_6;

	outcube.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";
	outcube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tm16_1^2\n";
	std::cout << "---\n";
	cube = outcube * outcube;
	cube.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "\t---\n";
	std::cout << "\tm16_1^3\n";
	std::cout << "\t---\n";
	cube = cube * outcube;
	cube.disp_perm_reduced(std::cout);
	std::cout << "\t---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";

	std::cout << "---\n";
	std::cout << "\t(thm16 move2) m16_2 = [[MF2,MD2],U']\n";
	std::cout << "---\n";

	outcube = MF2_6 * MD2_6 * !MF2_6 * !MD2_6 * !U_6 * MD2_6 * MF2_6 * !MD2_6 * !MF2_6 * U_6;

	outcube.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";
	outcube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tm16_2^2\n";
	std::cout << "---\n";
	cube = outcube * outcube;
	cube.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "\t---\n";
	std::cout << "\tm16_2^3\n";
	std::cout << "\t---\n";
	cube = cube * outcube;
	cube.disp_perm_reduced(std::cout);
	std::cout << "\t---\n";
	cube.disp_cube_fancy(std::cout);
	std::cout << "-----------------------------------------------------\n";


	return 0;
}
