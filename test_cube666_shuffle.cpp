#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "_cube666.h"

int main() {
	srand(time(NULL));
	static Permutation<6> moves[] = {
		L_6, R_6, F_6, B_6, U_6, D_6,
		ML1_6, ML2_6, MR1_6, MR2_6,
		MF1_6, MF2_6, MB1_6, MB2_6,
		MU1_6, MU2_6, MD1_6, MD2_6	
	};
	Permutation<6> cube;
	for (int i = 0; i < 340; i++) {
		int power = (rand() % 3) + 1;
		int move = (rand() % 18);
		
		for (int j = 0; j < power;j++)
			cube = cube * moves[move];
		
	}

	cube.disp_cube(std::cout);
	std::cout << "----\n";
	cube.disp_perm(std::cout);
	return 0;
}

