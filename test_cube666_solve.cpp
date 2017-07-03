#include <iostream>
#include "_cube666.h"

int main() {
	int perm_cube[] = {
		 36,  83,  33, 140, 137, 108,   6,   7, 160,  98, 100,  24,  32, 130, 123,  15, 
		199, 146,  53,  91, 165, 195, 206, 203, 214,  82, 189, 135,  43, 186, 179, 173,
		 39,  17,   1, 107, 149,  37,  74,  84, 175, 210,   4,  97, 196,  26, 187, 109,
		212,  13, 201,  56,  27, 198,  54, 207,  93,  57,  45,  48,  34, 169, 157,  52,
		 25, 112,  72, 101,  23, 125, 155, 215,  66,  60,  18, 111, 148, 185,  29, 136,
		  8, 153,  64, 119,  68,  58,  86, 164,  99,  69, 161,  55,  87, 122,  85, 183,
		 11, 118,  22, 152,  79, 103, 143,  31, 131,   2,  96, 102, 138,  70, 141,   3,
		 40,  35, 150, 154,  19, 170, 205, 178, 192,  81,  92, 129, 188,  90, 105,  44,
		 14,  20,   9, 104, 181,  28, 117,  16, 208,  67, 180, 209,  95, 213,  47, 144,
		 77, 168, 197,  75, 114,   0, 211,  61,  80, 134,  46, 145,  59, 166,  50, 128,
		 63, 177, 182, 124, 200, 159, 193, 167, 204, 115, 121, 116, 133,  76, 113, 184,
		120,  38, 191,  30, 174,  73, 162, 147,  65,  71,  42, 151,  88,  62,  10, 142,
		156,  49, 158, 194, 163, 126, 110, 127,  21,  51,  94, 176, 132, 172, 202, 171,
		190,  78,  41, 139,  12,  89, 106,   5
	};


	Permutation<6> cube(perm_cube);
	std::cout << "---\n";
	std::cout << "\tOriginal cube:\n";
	std::cout << "\t\t U\n";
	std::cout << "\t\tLFRB\n";
	std::cout << "\t\t D\n";
	std::cout << "\t\t B'\n";
	std::cout << "---\n";

	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "Build 2x2 centers - F2 L6 U5 (since UFL conrner is such):\n";
	std::cout << "---\n";
	std::cout << "\tMove center 22 piece on L to the F\n";
	std::cout << "\t\tMD2 * F^2 * MD2\'\n";
	std::cout << "---\n";

	cube = cube * MD2_6 * F_6 * F_6 * MD2_6 * MD2_6 * MD2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";

	std::cout << "\tMove remaining center 2 on D to F\n";
	std::cout << "\t\tF * MR2 * F * MR2\'\n";
	std::cout << "---\n";
	cube = cube * F_6 * MR2_6 * F_6 * MR2_6 * MR2_6 * MR2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 6 on D to L\n";
	std::cout << "\t\tMF2 L' MF2'\n";
	std::cout << "---\n";
	cube = cube * MF2_6 * L_6 * L_6 * L_6 * MF2_6 * MF2_6 * MF2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 6 on B to L\n";
	std::cout << "\t\tMU2' L' MU2\n";
	std::cout << "---\n";
	cube = cube * MU2_6 * MU2_6 * MU2_6 * L_6 * L_6 * L_6 * MU2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 6 on U to L\n";
	std::cout << "\t\tL MF2' L' MF2\n";
	std::cout << "---\n";
	cube = cube * L_6 * MF2_6 * MF2_6 * MF2_6 * L_6 * L_6 * L_6 * MF2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 5 on R to U\n";
	std::cout << "\t\tU' MF2' U' MF2\n";
	std::cout << "---\n";
	cube = cube * U_6 * U_6 * U_6 * MF2_6 * MF2_6 * MF2_6 * U_6 * U_6 * U_6 * MF2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 5 on D to U\n";
	std::cout << "\t\tU' MB2^2 U^2 MB2^2\n";
	std::cout << "---\n";
	cube = cube * U_6 * U_6 * U_6 * MB2_6 * MB2_6 * U_6 * U_6 * MB2_6 * MB2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 5 on B to U\n";
	std::cout << "\t\tU^2 MR2' U MR2\n";
	std::cout << "---\n";
	cube = cube * U_6 * U_6 * MR2_6 * MR2_6 * MR2_6 * U_6 * MR2_6 ;
	cube.disp_cube_fancy(std::cout);
	std::cout << std::endl;
	std::cout << "---\n";
	std::cout << "\tBuilding remaining centers R1 B4 D3:\n";
	std::cout << "\tMove center 11 on B to R\n";
	std::cout << "\t\tR^2 MD2' R^2 MD2\n";
	std::cout << "---\n";
	cube = cube * R_6 * R_6 * MD2_6 * MD2_6 * MD2_6 * R_6 * R_6 * MD2_6 ;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 33 (UL, DL) on B to D\n";
	std::cout << "\t\tMR2 D^2 MR2'\n";
	std::cout << "---\n";
	cube = cube * MR2_6 * D_6 * D_6 * MR2_6 * MR2_6 * MR2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMove center 3 on B to D\n";
	std::cout << "\t\tD' ML2' D' ML2\n";
	std::cout << "---\n";
	cube = cube * D_6 * D_6 * D_6 * ML2_6 * ML2_6 * ML2_6 * D_6 * D_6 * D_6 * ML2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tTest move, moving RB2D2 5 to U face\n";
	std::cout << "\t() is three cycle FR1D2 -> UR2B1 -> FR2U1\n";
	std::cout << "\t\tU MD2' (MR1 U' MR2 U MR1' U' MR2') MD2\n";
	std::cout << "---\n";
	cube = cube * U_6 * MD2_6 * MD2_6 * MD2_6 * MR1_6 * U_6 * U_6 * U_6 * MR2_6 * U_6 * MR1_6 * MR1_6 * MR1_6 * U_6 * U_6 * U_6 * MR2_6 * MR2_6 * MR2_6 * MD2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "Building center color crosses:\n";
	std::cout << "---\n";
	std::cout << "\tMoving BR1D1 2 to F face\n"; 
	std::cout << "\t\tMD1^2 F MD1^2\n";
	std::cout << "---\n";
	cube = cube * MD1_6 * MD1_6 * F_6 * MD1_6 * MD1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving UR1B1 2 to F face\n"; 
	std::cout << "\t\tF^2 MR1' F' MR1\n";
	std::cout << "---\n";
	cube = cube * F_6 * F_6 * MR1_6 * MR1_6 * MR1_6 * F_6 * F_6 * F_6 * MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DL1F1 2 to F face\n"; 
	std::cout << "\t\tF' ML1' F ML1\n";
	std::cout << "---\n";
	cube = cube * F_6 * F_6 * F_6 *  ML1_6 * ML1_6 * ML1_6 * F_6 * ML1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BR1D1 1 to R face\n"; 
	std::cout << "\t\tMD1' R' MD1 R\n";
	std::cout << "---\n";
	cube = cube * MD1_6 * MD1_6 * MD1_6 * R_6 * R_6 * R_6 * MD1_6 * R_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LF1D1 1 to R face\n"; 
	std::cout << "\t\tMD1^2 R' MD1^2\n";
	std::cout << "---\n";
	cube = cube * MD1_6 * MD1_6 * R_6 * R_6 * R_6 * MD1_6 * MD1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving UB1R1 1 to R face\n"; 
	std::cout << "\t\tMB1' R MB1\n";
	std::cout << "---\n";
	cube = cube * MB1_6 * MB1_6 * MB1_6 * R_6 * MB1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DL1B1 1 to R face\n"; 
	std::cout << "\t\tMB1 R MB1'\n";
	std::cout << "---\n";
	cube = cube * MB1_6 * R_6 * MB1_6 * MB1_6 * MB1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LF1D1 5 to U face\n"; 
	std::cout << "\t\tMF1 U' MF1' U\n";
	std::cout << "---\n";
	cube = cube * MF1_6 * !U_6 * !MF1_6 * U_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LF1U1 5 to U face\n"; 
	std::cout << "\t\tMF1 U' MF1' U'\n";
	std::cout << "---\n";
	cube = cube * MF1_6 * !U_6 * !MF1_6 * !U_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LB1D1 5 to U face\n"; 
	std::cout << "\t\tMB1' U' MB1' U\n";
	std::cout << "---\n";
	cube = cube * !MB1_6 * !U_6 * MB1_6 * U_6 ;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BD1R1 5 to U face\n"; 
	std::cout << "\t\tMR1' U' MR1'\n";
	std::cout << "---\n";
	cube = cube * !MR1_6 * !U_6 * MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF1L1 and DB1L1 4s to B face\n"; 
	std::cout << "\t\tB ML1 B^2 ML1'\n";
	std::cout << "---\n";
	cube = cube * B_6 * ML1_6 * B_6 * B_6 * !ML1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF1L1 and DF1R1 6s to L face\n"; 
	std::cout << "\t\tMF1 L^2 MF1' L\n";
	std::cout << "---\n";
	cube = cube * MF1_6 * L_6 * L_6 * !MF1_6 * L_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DB1L1 6 to L face\n"; 
	std::cout << "\t\tMB1' L MB1\n";
	std::cout << "---\n";
	cube = cube * !MB1_6 * L_6 * MB1_6; 
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "Finishing centers:\n";
	std::cout << "---\n";
	std::cout << "\tMoving FR2D1 5 to U face\n"; 
	std::cout << "\t\tF' (MR1 * U' ML2' U MR1 U' ML2) U\n";
	std::cout << "---\n";
	cube = cube * !F_6 * MR1_6 * !U_6 * !ML2_6 * U_6 * !MR1_6 * !U_6 * ML2_6 * U_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LU2B1 5 to U face\n"; 
	std::cout << "\t\t(MB1' U MF2 U' MB1 U MF2)\n";
	std::cout << "---\n";
	cube = cube * !MB1_6 * U_6 * MF2_6 * !U_6 * MB1_6 * U_6 * !MF2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving RU2F1 5 to U face\n"; 
	std::cout << "\t\t(MF1' U MB2 U' MF1 U MB2)\n";
	std::cout << "---\n";
	cube = cube * !MF1_6 * U_6 * MB2_6 * !U_6 * MF1_6 * U_6 * !MB2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving RD2F1 5 to U face\n"; 
	std::cout << "\t\t(MF1' U MF2' U' MF1 U MF2)\n";
	std::cout << "---\n";
	cube = cube * !MF1_6 * U_6 * !MF2_6 * !U_6 * MF1_6 * U_6 * MF2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DL2B1 5 to U face\n"; 
	std::cout << "\t\tU (ML1^2 !U ML2^2 U ML1^2 U' ML2^2)\n";
	std::cout << "---\n";
	cube = cube * U_6 * ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6 * U_6 * ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DB2L1 5 to U face\n"; 
	std::cout << "\t\tU (ML1^2 U' MR2^2 U ML1^2 U' MR2^2)\n";
	std::cout << "---\n";
	cube = cube * U_6 * ML1_6 * ML1_6 * !U_6 * MR2_6 * MR2_6 * U_6 * ML1_6 * ML1_6 * !U_6 * MR2_6 * MR2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF2L1 5 to U face\n"; 
	std::cout << "\t\tU^2 (ML1^2 U' ML2^2 U ML1^2 U' ML2^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 * U_6 *  ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6 * U_6 * ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BR2U1 5 to U face\n"; 
	std::cout << "\t\t(MR2' U' MR1' U MR2 U' MR1)\n";
	std::cout << "---\n";

	cube = cube * !MR2_6 * !U_6 * !MR1_6 * U_6 * MR2_6 * !U_6 * MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tOrient cube x - move U face toward B\n"; 
	std::cout << "\t\tx\n";
	std::cout << "---\n";
	// perform x -> rotate cube U_6 toward B_6
	cube = cube * !L_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * R_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FD2R1 2 to U face\n"; 
	std::cout << "\t\t(MR2 U' MR1 U MR2' U' MR1')\n";
	std::cout << "---\n";
	cube = cube * MR2_6 * !U_6 * MR1_6 * U_6 * !MR2_6 * !U_6 * !MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving RF2D1 and RB2D1 2s to U face\n"; 
	std::cout << "\t\tMD1' (MR2 U' MR1 U MR2' U' MR1') U (ML2' U' MR1 U ML2 U' MR1') MD1\n";
	std::cout << "---\n";
	cube = cube * !MD1_6
		* MR2_6 * !U_6 * MR1_6 * U_6 * !MR2_6 * !U_6 * !MR1_6
		* U_6
		* !ML2_6 * !U_6 * MR1_6 * U_6 * ML2_6 * !U_6 * !MR1_6
		* MD1_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LB2U1 2 to U face\n"; 
	std::cout << "\t\tU^2 MU1' (ML2' U' ML1' U ML2 U' ML1) MU1\n";
	std::cout << "---\n";

	cube = cube * U_6 * U_6 * !MU1_6
		* !ML2_6 * !U_6 * !ML1_6 * U_6 * ML2_6 * !U_6 * ML1_6
		* MU1_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LD2F1 2 to U face\n"; 
	std::cout << "\t\tMD2 (MR1 U' MR2 U MR1' U' MR2') MD2'\n";
	std::cout << "---\n";

	cube = cube 
		* MD2_6 
		* MR1_6 * !U_6 * MR2_6 * U_6 * !MR1_6 * !U_6 * !MR2_6
		* !MD2_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF2R1 2 to U face\n"; 
	std::cout << "\t\tU^2 (MR1^2 U' ML2' U MR1^2 U' ML2)'\n";
	std::cout << "---\n";

	cube = cube 
		* U_6 * U_6 * MR1_6 * MR1_6 * !U_6 * !ML2_6 * U_6 * MR1_6 * MR1_6 * !U_6 * ML2_6 ;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF2R1 2 to U face\n"; 
	std::cout << "\t\tMU2' (ML1' U' ML2' U ML1 U' ML2)\n";
	std::cout << "---\n";

	cube = cube 
		* !MU2_6
		* !ML1_6 * !U_6 * !ML2_6 * U_6 * ML1_6 * !U_6 * ML2_6 
		* MU2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\t\tx\n";
	std::cout << "---\n";
	cube = cube * !L_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * R_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FR2U1 3 to U face\n"; 
	std::cout << "\t\t(MR2 U' ML1' U MR2' U' ML1)\n";
	std::cout << "---\n";
	cube = cube * MR2_6 * !U_6 * !ML1_6 * U_6 * !MR2_6 * !U_6 * ML1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FR2D1 3 to U face\n"; 
	std::cout << "\t\tU (MR2 U ML1' U' MR2' U ML1)\n";
	std::cout << "---\n";
	cube = cube * U_6 * MR2_6 * U_6 * !ML1_6 * !U_6 * !MR2_6 * U_6 * ML1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving RU2F1 3 to U face\n"; 
	std::cout << "\t\tMU2 (ML1' U MR2 U' ML1 U MR2') MU2'\n";
	std::cout << "---\n";
	cube = cube * MU2_6 
		* !ML1_6 * U_6 * MR2_6 * !U_6 * ML1_6 * U_6 * !MR2_6
		* !MU2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving LD2B1 3 to U face\n"; 
	std::cout << "\t\tMD2 (ML1' U' MR2 U ML1 U' MR2') MD2'\n";
	std::cout << "---\n";

	cube = cube * MD2_6 
		* !ML1_6 * !U_6 * MR2_6 * U_6 * ML1_6 * !U_6 * !MR2_6
		* !MD2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tOrient cube x and y' = F face toward R face\n"; 
	std::cout << "\t\tx y'\n";
	std::cout << "---\n";

	// perform x -> rotate cube U_6 toward B_6
	cube = cube * !L_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * R_6;
	// perform y' -> rotate cube F_6 toward R_6
	cube = cube * !U_6 * !MU1_6 * !MU2_6 * MD2_6 * MD1_6 * D_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FR2U1 4 to U face\n"; 
	std::cout << "\t\t(MR2 U' ML1' U MR2' U' ML1)\n";
	std::cout << "---\n";
	cube = cube 
		* MR2_6 * !U_6 * !ML1_6 * U_6 * !MR2_6 * !U_6 * ML1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FR2D1 4 to U face\n"; 
	std::cout << "\t\t(MR2 U' MR1 U MR2' U' MR1')\n";
	std::cout << "---\n";

	cube = cube 
		* MR2_6 * !U_6 * MR1_6 * U_6 * !MR2_6 * !U_6 * !MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FR2D1 4 to U face\n"; 
	std::cout << "\t\t(MR2 U' MR1 U MR2' U' MR1')\n";
	std::cout << "---\n";

	cube = cube * !U_6 
		* MR2_6 * !U_6 * MR1_6 * U_6 * !MR2_6 * !U_6 * !MR1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BL2U1 4 to U face\n"; 
	std::cout << "\t\tU MU1^2 (MR2 U' ML1' U MR2' U' ML1) MU1^2\n";
	std::cout << "---\n";

	cube = cube * U_6 
		* MU1_6 * MU1_6 
		* MR2_6 * !U_6 * !ML1_6 * U_6 * !MR2_6 * !U_6 * ML1_6
		* MU1_6 * MU1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BL2U1 4 to U face (unnecessary move)\n"; 
	std::cout << "\t\tU^2 MU1^2 (MR2 U' ML1' U MR2' U' ML1) MU1^2\n";
	std::cout << "---\n";

	cube = cube * U_6  * U_6
		* MU1_6 * MU1_6 
		* MR2_6 * !U_6 * !ML1_6 * U_6 * !MR2_6 * !U_6 * ML1_6
		* MU1_6 * MU1_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BR2U1 4 to U face\n"; 
	std::cout << "\t\tU MU1^2 (ML2' U' ML1' U ML2 U' ML1) MU1^2\n";
	std::cout << "---\n";

	cube = cube * U_6  
		* MU1_6 * MU1_6 
		* !ML2_6 * !U_6 * !ML1_6 * U_6 * ML2_6 * !U_6 * ML1_6
		* MU1_6 * MU1_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving FU2L1 4 to U face\n"; 
	std::cout << "\t\t(ML1' U' ML2' U ML1 U' ML2)\n";
	std::cout << "---\n";

	cube = cube 
		* !ML1_6 * !U_6 * !ML2_6 * U_6 * ML1_6 * !U_6 * ML2_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving BD2L1 4 to U face\n"; 
	std::cout << "\t\tB^2 (MR1' U' MR2 U MR1 U' MR2')\n";
	std::cout << "---\n";

	cube = cube * B_6 * B_6 
		* !MR1_6 * !U_6 * MR2_6 * U_6 * MR1_6 * !U_6 * !MR2_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tOrient cube U toward B\n";
	std::cout << "\tx\n";
	std::cout << "---\n";
	// perform x -> rotate cube U_6 toward B_6
	cube = cube * !L_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * R_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DB2R1 6 to U face\n"; 
	std::cout << "\t\tU' (MR1^2 U' MR2^2 U MR1^2 U' MR2^2)\n";
	std::cout << "---\n";

	cube = cube * !U_6 
		* MR1_6 * MR1_6 * !U_6 * MR2_6 * MR2_6 * U_6 * MR1_6 * MR1_6 * !U_6 * MR2_6 * MR2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DF2L1 6 to U face\n"; 
	std::cout << "\t\tU (ML1^2 U' ML2^2 U ML1^2 U' ML2^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 
		* ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6 * U_6 * ML1_6 * ML1_6 * !U_6 * ML2_6 * ML2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving DB2L1 6 to U face\n"; 
	std::cout << "\t\tU (ML1^2 U' MR2^2 U ML1^2 U' MR2^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 

		* ML1_6 * ML1_6 * !U_6 * MR2_6 * MR2_6 * U_6 * ML1_6 * ML1_6 * !U_6 * MR2_6 * MR2_6;
;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "Fixing middle edges:\n";
	std::cout << "---\n";
	std::cout << "\tMoving 41 middle edge cubelets together\n"; 
	std::cout << "\t() moves FLD2 to FRU2\n"; 
	std::cout << "\t\tR F^2 (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * R_6 * F_6 * F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 31 middle edge cubelets together\n"; 
	std::cout << "\t\tR D' F' R' F' U F' (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";
	cube = cube * R_6 * !D_6 * !F_6 * R_6 * R_6 *R_6 * !F_6 * U_6 * !F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;
		
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tR U'\n";
	std::cout << "---\n";

	cube = cube * R_6 * !U_6 ;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMoving 45 middle edge cubelets together\n"; 
	std::cout << "\t\t() moves RDF2 to RUF2\n";
	std::cout << "\t\t(MF2 D R' B D' R MF2')\n";
	std::cout << "---\n";
	cube = cube 
		* MF2_6 * D_6 * !R_6 * B_6 * !D_6 * R_6 * !MF2_6
;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 21 middle edge cubelets together\n"; 
	std::cout << "\t\tx F' (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";
	// perform x -> rotate cube U_6 toward B_6
	cube = cube * !L_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * R_6;
	//
	cube = cube * !F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 63 middle edge cubelets together\n"; 
	std::cout << "\t\tL R (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * L_6 * R_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 62 middle edge cubelets together\n"; 
	std::cout << "\t\tD' R L' F U' F' (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * !D_6 * R_6 * !L_6 * F_6 * !U_6 * !F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 65 middle edge cubelets together\n"; 
	std::cout << "\t\tR F^2 (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * R_6 * F_6 * F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 52 middle edge cubelets together\n"; 
	std::cout << "\t\tD' R (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * !D_6 * R_6 
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 64 middle edge cubelets together\n"; 
	std::cout << "\t\tF' L R F' U F (MD2 R F' U R' F MD2')\n";
	std::cout << "---\n";

	cube = cube * !F_6 * L_6 * R_6 * !F_6 * U_6 * F_6
		* MD2_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD2_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tMoving 52 outer edge cubelets together\n"; 
	std::cout << "\t() moves FLD1 to FRU1\n";
	std::cout << "\t\tU L (MD1 R F' U R' F MD1')\n";
	std::cout << "---\n";

	cube = cube * U_6 * L_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 52 edge\n"; 
	std::cout << "\t() moves UFL2-UFR2 pair to UBL2-UBR2 pair\n";
	std::cout << "\t\tF' x U^2\n\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * !F_6 * R_6 * MR1_6 * MR2_6 * !ML2_6 * !ML1_6 * !L_6 * U_6 * U_6
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 52 edge\n"; 
	std::cout << "\t\tF' U F U' F\n\t\t(MD1 R F'U R' F MD1')\n\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";


	cube = cube * !F_6 * U_6 * F_6 * !U_6 * F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		* U_6 * U_6 * L_6 * F_6 * R_6 * MR1_6 * MR2_6 * !ML2_6 * !ML1_6 * !L_6 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 21 edge\n"; 
	std::cout << "\t\tU' F' U F'\n\t\t(MD1 R F'U R' F MD1')\n\t\tx\n\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * !U_6 * !F_6 * U_6 * !F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		 * !F_6 * R_6 * !R_6 * !D_6 * F_6 * F_6;

	orient_x(cube);
	cube = cube
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 32 edge\n"; 
	std::cout << "\t\tF U' x\n\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * F_6 * !U_6;
	orient_x(cube);
	cube = cube 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 63 edge\n"; 
	std::cout << "\t\tL F' L' (MD1 R F' U R' F MD1') U^2 L F x\n\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * L_6 * !F_6 * !L_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		* U_6 * U_6 * L_6 * F_6;
	orient_x(cube);
	cube = cube 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;

	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 31 edge\n"; 
	std::cout << "\t\tL' F U' F' (MD1 R F' U R' F MD1')\n";
	std::cout << "---\n";

	cube = cube * !L_6 * F_6 * !U_6 * !F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 41 edge\n"; 
	std::cout << "\t\tL' F L (MD1 R F' U R' F MD1')\n";
	std::cout << "---\n";


	cube = cube * !L_6 * !F_6 * L_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
; 
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 51 edge\n"; 
	std::cout << "\t\tD U F' (MD1 R F' U R' F MD1') B F x\n";
	std::cout << "\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * D_6 * U_6 * !F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		* B_6 * F_6;
	orient_x(cube);
	cube = cube 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 43 edge\n"; 
	std::cout << "\ty = orient cube F towards L\n"; 
	std::cout << "\t\tU R^2 L F^2 (MD1 R F' U R' F MD1') y D^2 F x\n";
	std::cout << "\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 * R_6 * R_6 * L_6 * F_6 * F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		* U_6 * MU1_6 * MU2_6 * !MD2_6 * !MD1_6 * D_6
		* F_6
		;
	orient_x(cube);
	cube = cube 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 62 edge\n"; 
	std::cout << "\tx' = orient cube U towards F\n"; 
	std::cout << "\t\tx' R' F R (MD1 R F' U R' F MD1') F' x\n";
	std::cout << "\t\t(R MR1 R MR1 B^2 R' MR1' U^2 R' MR1'\n\t\t U^2 B^2 R' MR1' B^2 R MR1 B^2\n\t\t R' MR1' B^2 R MR1 R MR1 B^2)\n";
	std::cout << "---\n";


	orient_x(cube);
	orient_x(cube);
	orient_x(cube);
	cube = cube * !R_6 * !F_6 * R_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6
		*!F_6

	;// * !L_6 * B_6 * F_6 * F_6;
	orient_x(cube);
	cube = cube 
		* R_6 * MR1_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * U_6 * U_6 * !R_6 * !MR1_6 * U_6 * U_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * MR1_6 * B_6 * B_6 * !R_6 * !MR1_6 * B_6 * B_6 * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 65 edge\n"; 
	std::cout << "\tU^2 D U F' L F^2 (MD1 R F' U R' F MD1')\n"; 
	std::cout << "---\n";

	cube = cube * U_6 * U_6 * D_6 * U_6 * !F_6 * L_6 * F_6 * F_6
		* MD1_6 * R_6 * !F_6 * U_6 * !R_6 * F_6 * !MD1_6

	;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tFixing 54 edge\n"; 
	std::cout << "\t() flips UFL2-UFR2 edge\n"; 
	std::cout << "\t\tF (R^2 MR1^2 B^2 U^2 ML1 U^2 MR1' U^2 MR1 U^2 F^2 MR1 F^2 ML1' B^2 MR1^2 R^2)\n";
	std::cout << "---\n";

	cube = cube * F_6;

	cube = cube * R_6 * R_6 * MR1_6 * MR1_6 * B_6 * B_6 * U_6 * U_6 * ML1_6 * U_6 * U_6 * !MR1_6 * U_6 * U_6 * MR1_6 * U_6 * U_6 * F_6 * F_6 * MR1_6 * F_6 * F_6 * !ML1_6 * B_6 * B_6 * MR1_6 * MR1_6 * R_6 * R_6;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "Solving as 3x3x3 cube:\n"; 
	std::cout << "---\n";
	std::cout << "\t???\n"; 
	std::cout << "\t\tU^2\n"; 
	std::cout << "---\n";

	cube = cube * U_6 * U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t???\n"; 
	std::cout << "\t\tU' R U\n"; 
	std::cout << "---\n";
	cube = cube * !U_6 * R_6 * U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t???\n"; 
	std::cout << "\t\tF L' F'\n"; 
	std::cout << "---\n";
	cube = cube * F_6 * !L_6 * !F_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t???\n"; 
	std::cout << "\t\tF' R F\n"; 
	std::cout << "---\n";
	cube = cube * !F_6 * R_6 * F_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMoving FRB corner (526) into correct position (UFL)\n"; 
	std::cout << "\t\tD U L' D L U'\n"; 
	std::cout << "---\n";
	cube = cube * D_6 * U_6 * !L_6 * D_6 * L_6 * !U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMoving LBD corner (546) into correct position (UBL)\n"; 
	std::cout << "\t\tD^2 U' L D' L' U\n"; 
	std::cout << "---\n";
	cube = cube * D_6 * D_6 * !U_6 * L_6 * !D_6 * !L_6 * U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMoving BLF corner (541) into correct position (UBR)\n"; 
	std::cout << "\t\tR' D^2 R D' U R' D R U' | \n"; 
	std::cout << "---\n";
	cube = cube * !R_6 * D_6 * D_6 * R_6 * !D_6 * U_6 * !R_6 * D_6 * R_6 * !U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tPut bottom 12 block via incorrect UFR to middle layer - FRU1-...-FRB1\n"; 
	std::cout << "\t(xy block should be on the face with y color\n";
	std::cout << "\t which on F face, x color in on R face\n"; 
	std::cout << "\t unsolved up corner piece is in the position UFR\n)\n"; 
	std::cout << "\t\tD R' D R\n"; 
	std::cout << "---\n";
	cube = cube * D_6 * !R_6 * D_6 * R_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMove corner piece to U face (not very good move)\n"; 
	std::cout << "\t\tD U F' D R' D R\n"; 
	std::cout << "---\n";
	cube = cube * D_6 * U_6 * !F_6 * D_6 * F_6 * !U_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix rotated UFR corner piece\n"; 
	std::cout << "\t\tR' D R D' R' D R\n"; 
	std::cout << "---\n";
	cube = cube * !R_6 * D_6 * R_6 * !D_6 * !R_6 * D_6 * R_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t\tD F D' F' D' R' D R\n"; 
	std::cout << "\tor equivalently\n"; 
	std::cout << "\t\ty (D L D' L' D' F' D F) y'\n"; 
	std::cout << "---\n";
//	cube = cube * D_6 * F_6 * !D_6 * !F_6 * !D_6 * !R_6 * D_6 * R_6
//		;
	orient_y(cube);
	cube = cube * D_6 * L_6 * !D_6 * !L_6 * !D_6 * !F_6 * D_6 * F_6;
	orient_y_prime(cube);
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t\ty^2\n"; 
	std::cout << "---\n";
	orient_y(cube);
	orient_y(cube);
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tMove middle piece 41 to B face\n";
	std::cout << "\t(It actually inserts 13 from B to FRU1-FRU2-FRB2-FRB1)\n";
	std::cout << "\t\tD (D' R' D R D F D' F')\n";
	cube = cube * !R_6 * D_6 * R_6  * D_6 * F_6 * !D_6 * !F_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix middle FLU1-FLU2-FLB2-FLB1 block (41) \n";
	std::cout << "\t\tD^2 (D L D' L' D' F' D F)\n"; 
	std::cout << "---\n";
	cube = cube * D_6 * D_6 
		* D_6 * L_6 * !D_6 * !L_6 * !D_6 * !F_6 * D_6 * F_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix middle FRU1-FRU2-FRB2-FRB1 block (46) \n";
	std::cout << "\t\tD^2 (D' R' D R D F D' F')\n";
	std::cout << "---\n";
	cube = cube * D_6 * D_6 * !D_6 * !R_6 * D_6 * R_6 * D_6 * F_6 * !D_6 * !F_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\t() swaps FDL and FDR corners\n";
	std::cout << "\t\tD' (L R' D B D' B' L' D' R)\n";
	std::cout << "---\n";


	cube = cube * !D_6 *  L_6 * !R_6 * D_6 * B_6 * !D_6 * !B_6 * !L_6 * !D_6 * R_6  // * L_6 * !B_6 * !L_6 * !D_6 * R_6	
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix bottom corner orientation\n";
	std::cout << "\t(Correctly oriented piece if any should be put into FBL corner)\n";
	std::cout << "\t\t(R' D^2 R D R' D R L D^2 L' D' L D' L')\n";
	std::cout << "---\n";
	cube = cube * !R_6 * D_6 * D_6 * R_6 * D_6 * !R_6 * D_6 * R_6 * L_6 * D_6 * D_6 * !L_6 * !D_6 * L_6 * !D_6 * !L_6
		;

	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix bottom corner orientation\n";
	std::cout << "\t(Correctly oriented piece if any should be put into FBL corner)\n";
	std::cout << "\t\t(R' D^2 R D R' D R L D^2 L' D' L D' L')\n";
	std::cout << "---\n";
	cube = cube * !R_6 * D_6 * D_6 * R_6 * D_6 * !R_6 * D_6 * R_6 * L_6 * D_6 * D_6 * !L_6 * !D_6 * L_6 * !D_6 * !L_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tPut correctly oriented adjacent bottom corners to L face\n";
	std::cout << "\t\ty\n";
	std::cout << "---\n";
		orient_y(cube);
		
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tFix bottom corner orientation DRF-DRB\n";
	std::cout << "\t\t(R' D^2 R D R' D R L D^2 L' D' L D' L')\n";
	std::cout << "---\n";

	cube = cube * !R_6 * D_6 * D_6 * R_6 * D_6 * !R_6 * D_6 * R_6 * L_6 * D_6 * D_6 * !L_6 * !D_6 * L_6 * !D_6 * !L_6
		;
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tOrient U towards R twice (turn cube upside down)\n";
	std::cout << "\t\tz^2\n";
	std::cout << "---\n";
		orient_z(cube);
		orient_z(cube);
	cube.disp_cube_fancy(std::cout);

	std::cout << "---\n";
	std::cout << "\tOrient bottom (now top) layer\n";
	std::cout << "\t(There could be several cases\n";

	std::cout <<"\t  .X. ... .X. ...\n";
	std::cout <<"\t  ..X X.X X.X ...\n";
	std::cout <<"\t  ... ... .X. ...\n";
	std::cout <<"\t)\n"; 




	std::cout << "\t\tU (ML1 ML2 !MR2 !MR1 U ML!' ML2' MR2 MR1 \n";
	std::cout << "\t\t   U ML1 ML2 !MR2 !MR1 U ML!' ML2' MR2 MR1 \n";
	std::cout << "\t\t   U ML1 ML2 !MR2 !MR1 U ML!' ML2' MR2 MR1 \n";
	std::cout << "\t\t   U^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 * ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6  * ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6 * !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6 * ML1_6 * ML2_6 * !MR2_6 * !MR1_6 * U_6* !ML1_6 * !ML2_6 * MR2_6 * MR1_6 * U_6 * U_6 
		;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\t\ty\n";
	std::cout << "---\n";
		orient_y(cube);
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
	std::cout << "\tSwapping UFL1-UFL2-UFR2-UFR1 (32s) and UBL1-UBL2-UBR2-UBR1 (34s) pieces\n";
	std::cout << "\t\t(U^2 MU1^2 MU2^2 R^2 MR1^2 MR2^2 U^2 MR2^2 \n";
	std::cout << "\t\t MR1^2 U^2 MR2^2 MR1^2 R^2 MU2^2 MU1^2 U^2)\n";
	std::cout << "---\n";

	cube = cube * U_6 * MU1_6 * MU2_6 * U_6 * MU1_6 * MU2_6 * MR2_6 * MR1_6 * R_6 * MR2_6 * MR1_6 * R_6 * U_6 * U_6 * MR2_6 * MR1_6 * MR2_6 * MR1_6 * U_6 * U_6 * MR2_6 * MR1_6 * R_6 * MR2_6 * MR1_6 * R_6 * MU2_6 *MU1_6 *U_6 * MU2_6 * MU1_6 * U_6
	;
	cube.disp_cube_fancy(std::cout);
	std::cout << "---\n";
return 0;
}
