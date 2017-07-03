#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "cubeNNN.h"
#include "_cube666.h"

//
const Permutation<6> I(arr_I_6);

const Permutation<6> L(arr_L_6);
const Permutation<6> ML1(arr_ML1_6);
const Permutation<6> ML2(arr_ML2_6);
const Permutation<6> MR2(arr_MR2_6);
const Permutation<6> MR1(arr_MR1_6);
const Permutation<6> R(arr_R_6);

const Permutation<6> F(arr_F_6);
const Permutation<6> MF1(arr_MF1_6);
const Permutation<6> MF2(arr_MF2_6);
const Permutation<6> MB2(arr_MB2_6);
const Permutation<6> MB1(arr_MB1_6);
const Permutation<6> B(arr_B_6);

const Permutation<6> U(arr_U_6);
const Permutation<6> MU1(arr_MU1_6);
const Permutation<6> MU2(arr_MU2_6);
const Permutation<6> MD2(arr_MD2_6);
const Permutation<6> MD1(arr_MD1_6);
const Permutation<6> D(arr_D_6);


int main() {
	Permutation<6> cube44;

	cube44 = cube44 * I_6;





#ifdef THM17
	// Thm 17
	// move e1

	Permutation<6> e1;
	
	std::cout << "Move e1:\n";
	e1 = !ML2 * L * !U * !L * U * ML2 * !U * L * U * !L;

	e1.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";

	Permutation<6> m1;
	std::cout << "Move m:\n";

	m1 = MR2 * MR2 * B * B * D * D * !ML2 * D * D * MR2 * D * D * !MR2 * D * D * F * F * !MR2 * F * F * ML2 * B * B * MR2* MR2;

	m1.disp_perm_reduced(std::cout);
	

	

	std::cout << "\t--- Order: " << m1.order() << ", Parity: " << m1.parity() <<  " ---\n";


	Permutation<6> e2;
	
	std::cout << "Move e2:\n";
	e2 = !ML1 * L * !U * !L * U * ML1 * !U * L * U * !L;

	e1.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";

	Permutation<6> m2;
	std::cout << "Move n:\n";

	m2 = MR1 * MR1 * B * B * D * D * !ML1 * D * D * MR1 * D * D * !MR1 * D * D * F * F * !MR1 * F * F * ML1 * B * B * MR1* MR1;

	m2.disp_perm_reduced(std::cout);
	
	std::cout << "\t--- Order: " << m2.order() << ", Parity: " << m2.parity() <<  " ---\n";

#endif

#ifdef THM18
	// Thm 18
	// move p

	Permutation<6> p;

	std::cout << "Move p:\n";
	p = MF2 * MD1 * !MF2 * !MD1 * !U * MD1 * MF2 * !MD1 * !MF2 * U;

	p.disp_perm_reduced(std::cout);
	
	std::cout << "\t--- Order: " << p.order() << ", Parity: " << p.parity() <<  " ---\n";

#endif

#if 0
	// Thm 19
	// move c

	Permutation<6> c;

	std::cout << "Move c:\n";
	c = MF2 * MD2 * !MF2 * !MD2 * !U * MD2 * MF2 * !MD2 * !MF2 * U;

	c.disp_perm_reduced(std::cout);
	
	std::cout << "\t--- Order: " << c.order() << ", Parity: " << c.parity() <<  " ---\n";

#endif

#if 0

	// Move m
	Permutation<6> outcube;

	outcube = MR1*MR1 * B* B * D * D * !ML1 * D * D * MR1 * D * D * !MR1 * D * D * F * F * !MR1 * F * F * ML1 * B * B * MR1* MR1;
	outcube.disp_perm_reduced(std::cout);

	std::cout << "\t---\n";
#endif
	
#if 0
	Permutation<3> outcube;
	

	outcube.disp_cube(std::cout);

	srand(time(NULL));
	//
	for (int i = 0 ; i<50; i++) {
		int move = rand() % 12;

		switch (move) {
			case 0:
				outcube = outcube * L_3;
				break;

			case 1:
				outcube = outcube * ML_3;
				break;
			case 2:
				outcube = outcube * MR_3;
				break;
			case 3:
				outcube = outcube * R_3;
				break;
			case 4:
				outcube = outcube * U_3;
				break;
			case 5:
				outcube = outcube * MU_3;
				break;
			case 6:
				outcube = outcube * MD_3;
				break;
			case 7:
				outcube = outcube * D_3;
				break;
			case 8:
				outcube = outcube * F_3;
				break;
			case 9:
				outcube = outcube * MF_3;
				break;
			case 10:
				outcube = outcube * MB_3;
				break;
			case 11:
				outcube = outcube * B_3;
				break;
		};	
	}

		outcube.disp_cube(std::cout);

	Permutation<3> moves[24] = {
		L_3, R_3*R_3, B_3, !L_3, R_3, U_3*U_3, F_3*F_3, L_3, B_3, D_3, U_3*U_3, B_3, !L_3, R_3*R_3, B_3*B_3, !L_3, D_3*D_3, U_3, !L_3, B_3 *B_3, U_3*U_3, R_3*R_3, B_3, D_3*D_3
	};

	const int count_max = 1/*0000*/;
	int count = 0;

	while (count < count_max) {
		for (int i = 0; i < 23; i++) {
			if (outcube != I_3) {
				outcube = outcube * moves[i];
				outcube.disp_cube(std::cout);
			}
			else {
				std::cout << "Up to i-th index" << i + 1  << ".\n";
				return 0;
			}

		}
		count++;
	};

#endif
	// testing conjugation

	Permutation<6> outcube;

	outcube = MR1 * MR1 * !U * !ML1 * !ML1 * U * !MR1 * !MR1* !U * ML1 * ML1*U;

	outcube.disp_perm_reduced(std::cout);
	
	Permutation<6> outcube2;

	outcube2 = MR1 * !U * !ML1 * U * !MR1 * !U * ML1*U;

	outcube2.disp_perm_reduced(std::cout);
	
	Permutation<6> outcube3;

	outcube3 = MR1 * !U * !ML2 * U * !MR1 * !U * ML2*U;

	std::cout  << "---\n";
	outcube3.disp_perm_reduced(std::cout);

	Permutation<6> outcube4;

	outcube4 = MR1 * MR1 * !U * !ML2 * !ML2* U * !MR1 * !MR1 * !U * ML2* ML2 *U;

	std::cout  << "---\n";
	outcube4.disp_perm_reduced(std::cout);

	Permutation<6> outcube5;

	outcube5 = MR1 * MR1 * !U * !ML1 * !ML1 * U * !MR1 * !MR1 * !U * ML1 * ML1 * U;

	std::cout  << "---\n";
	outcube5.disp_perm_reduced(std::cout);


}
