#include <iostream>
#include <iomanip>
#include "fixed_edges.h"
#include "edge_positions.h"

namespace rubik_cube {

Fixed_edges::Fixed_edges() {
	for (int i = 0; i < 12; i++) {
		perm[i] = i;
		orient[i] = 0;
	}
	
}

void Fixed_edges::disp(std::ostream &os) {
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (i + 1) << " ";
	os << '\n';

	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (perm[i] + 1) << " ";
	os << '\n';
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << orient[i] << " ";
	os << '\n';

}


void Fixed_edges::disp_cube(std::ostream &os) {
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << 'x';
	os << edge_positions[orient[2]][perm[2]].at(0);
	os << 'x';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << edge_positions[orient[3]][perm[3]].at(0);
	os << 'U';
	os << edge_positions[orient[1]][perm[1]].at(0);
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << 'x';
	os << edge_positions[orient[0]][perm[0]].at(0);
	os << 'x';
	os << '\n';

	// L
	os << 'x';
	os << edge_positions[orient[3]][perm[3]].at(1);
	os << 'x';

	os << ' ';

	// F
	os << 'x';
	os << edge_positions[orient[0]][perm[0]].at(1);
	os << 'x';

	os << ' ';

	// R
	os << 'x';
	os << edge_positions[orient[1]][perm[1]].at(1);
	os << 'x';

	os << ' ';

	// B
	os << 'x';
	os << edge_positions[orient[2]][perm[2]].at(1);
	os << 'x';
	os << '\n';

	// L
	os << edge_positions[orient[7]][perm[7]].at(0);
	os << 'L';
	os << edge_positions[orient[4]][perm[4]].at(0);

	os << ' ';

	// F
	os << edge_positions[orient[4]][perm[4]].at(1);
	os << 'F';
	os << edge_positions[orient[5]][perm[5]].at(1);

	os << ' ';

	// R
	os << edge_positions[orient[5]][perm[5]].at(0);
	os << 'R';
	os << edge_positions[orient[6]][perm[6]].at(0);

	os << ' ';

	// B
	os << edge_positions[orient[6]][perm[6]].at(1);
	os << 'B';
	os << edge_positions[orient[7]][perm[7]].at(1);
	os << '\n';

	// L
	os << 'x';
	os << edge_positions[orient[11]][perm[11]].at(1);
	os << 'x';

	os << ' ';

	// F
	os << 'x';
	os << edge_positions[orient[8]][perm[8]].at(1);
	os << 'x';

	os << ' ';

	// R
	os << 'x';
	os << edge_positions[orient[9]][perm[9]].at(1);
	os << 'x';

	os << ' ';

	// B
	os << 'x';
	os << edge_positions[orient[10]][perm[10]].at(1);
	os << 'x';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << 'x';
	os << edge_positions[orient[8]][perm[8]].at(0);
	os << 'x';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << edge_positions[orient[11]][perm[11]].at(0);
	os << 'U';
	os << edge_positions[orient[9]][perm[9]].at(0);
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << 'x';
	os << edge_positions[orient[10]][perm[10]].at(0);
	os << 'x';
	os << '\n';
}

void apply_R(Fixed_edges &edge) {
/*
	2  = + => 7
	^
	+         + 
		  v
	6 <= + =  10


	( idx -1 )

*/


	int tmp = edge.orient[5];
	
	edge.orient[5] = (edge.orient[9] + 1) % 2;
	edge.orient[9] = (edge.orient[6] + 1) % 2;
	edge.orient[6] = (edge.orient[1] + 1) % 2;
	edge.orient[1] = (tmp + 1) % 2;

	tmp = edge.perm[5];
	
	edge.perm[5] = edge.perm[9];
	edge.perm[9] = edge.perm[6];
	edge.perm[6] = edge.perm[1];
	edge.perm[1] = tmp;
}

void apply_L(Fixed_edges &edge) {
/*
	4  = + => 5
	^
	+         + 
		  v
	8 <= + =  12


	( idx -1 )

*/


	int tmp = edge.orient[7];
	
	edge.orient[7] = (edge.orient[11] + 1) % 2;
	edge.orient[11] = (edge.orient[4] + 1) % 2;
	edge.orient[4] = (edge.orient[3] + 1) % 2;
	edge.orient[3] = (tmp + 1) % 2;

	tmp = edge.perm[7];
	
	edge.perm[7] = edge.perm[11];
	edge.perm[11] = edge.perm[4];
	edge.perm[4] = edge.perm[3];
	edge.perm[3] = tmp;
}

void apply_U(Fixed_edges &edge) {
/*
	1  = + => 4
	^
	+         + 
		  v
	2 <= + =  3


	( idx -1 )

*/


	int tmp = edge.orient[1];
	
	edge.orient[1] = edge.orient[2];
	edge.orient[2] = edge.orient[3];
	edge.orient[3] = edge.orient[0];
	edge.orient[0] = tmp % 2;

	tmp = edge.perm[1];
	
	edge.perm[1] = edge.perm[2];
	edge.perm[2] = edge.perm[3];
	edge.perm[3] = edge.perm[0];
	edge.perm[0] = tmp;
}

void apply_D(Fixed_edges &edge) {
/*
	9  = + => 10
	^
	+         + 
		  v
	12 <= + =  11


	( idx -1 )

*/


	int tmp = edge.orient[11];
	
	edge.orient[11] = edge.orient[10];
	edge.orient[10] = edge.orient[9];
	edge.orient[9] = edge.orient[8];
	edge.orient[8] = tmp;

	tmp = edge.perm[11];
	
	edge.perm[11] = edge.perm[10];
	edge.perm[10] = edge.perm[9];
	edge.perm[9] = edge.perm[8];
	edge.perm[8] = tmp;
}

void apply_F(Fixed_edges &edge) {
/*
	1  = + => 6
	^
	+         + 
		  v
	5 <= + =  9


	( idx -1 )

*/


	int tmp = edge.orient[4];
	
	edge.orient[4] = edge.orient[8];
	edge.orient[8] = edge.orient[5];
	edge.orient[5] = edge.orient[0];
	edge.orient[0] = tmp;

	tmp = edge.perm[4];
	
	edge.perm[4] = edge.perm[8];
	edge.perm[8] = edge.perm[5];
	edge.perm[5] = edge.perm[0];
	edge.perm[0] = tmp;
}

void apply_B(Fixed_edges &edge) {
/*
	3  = + => 8
	^
	+         + 
		  v
	7 <= + =  11


	( idx -1 )

*/


	int tmp = edge.orient[6];
	
	edge.orient[6] = edge.orient[10];
	edge.orient[10] = edge.orient[7];
	edge.orient[7] = edge.orient[2];
	edge.orient[2] = tmp;

	tmp = edge.perm[6];
	
	edge.perm[6] = edge.perm[10];
	edge.perm[10] = edge.perm[7];
	edge.perm[7] = edge.perm[2];
	edge.perm[2] = tmp;
}

void apply_ML(Fixed_edges &edge) {
/*
	1  = + => 9
	^
	+         + 
		  v
	3 <= + =  11


	( idx -1 )

*/


	int tmp = edge.orient[2];
	
	edge.orient[2] = (edge.orient[10] + 1) % 2;
	edge.orient[10] = (edge.orient[8] + 1) % 2;
	edge.orient[8] = (edge.orient[0] + 1) % 2;
	edge.orient[0] = (tmp + 1) % 2;

	tmp = edge.perm[2];
	
	edge.perm[2] = edge.perm[10];
	edge.perm[10] = edge.perm[8];
	edge.perm[8] = edge.perm[0];
	edge.perm[0] = tmp;
}

void apply_MR(Fixed_edges &edge) {
/*
	1  = + => 3
	^
	+         + 
		  v
	9 <= + =  11


	( idx -1 )

*/


	int tmp = edge.orient[8];
	
	edge.orient[8] = (edge.orient[10] + 1) % 2;
	edge.orient[10] = (edge.orient[2] + 1) % 2;
	edge.orient[2] = (edge.orient[0] + 1) % 2;
	edge.orient[0] = (tmp + 1) % 2;

	tmp = edge.perm[8];
	
	edge.perm[8] = edge.perm[10];
	edge.perm[10] = edge.perm[2];
	edge.perm[2] = edge.perm[0];
	edge.perm[0] = tmp;
}

void apply_MF(Fixed_edges &edge) {
/*
	4  = + => 2
	^
	+         + 
		  v
	12 <= + =  10


	( idx -1 )

*/


	int tmp = edge.orient[11];
	
	edge.orient[11] = (edge.orient[9] + 1) % 2;
	edge.orient[9] = (edge.orient[1] + 1) % 2;
	edge.orient[1] = (edge.orient[3] + 1) % 2;
	edge.orient[3] = (tmp + 1) % 2;

	tmp = edge.perm[11];
	
	edge.perm[11] = edge.perm[9];
	edge.perm[9] = edge.perm[1];
	edge.perm[1] = edge.perm[3];
	edge.perm[3] = tmp;
}

void apply_MB(Fixed_edges &edge) {
/*
	4  = + => 12
	^
	+         + 
		  v
	2 <= + =  10


	( idx -1 )

*/


	int tmp = edge.orient[1];
	
	edge.orient[1] = (edge.orient[9] + 1) % 2;
	edge.orient[9] = (edge.orient[11] + 1) % 2;
	edge.orient[11] = (edge.orient[3] + 1) % 2;
	edge.orient[3] = (tmp + 1) % 2;

	tmp = edge.perm[1];
	
	edge.perm[1] = edge.perm[9];
	edge.perm[9] = edge.perm[11];
	edge.perm[11] = edge.perm[3];
	edge.perm[3] = tmp;
}

void apply_MU(Fixed_edges &edge) {
/*
	5  = + => 8
	^
	+         + 
		  v
	6 <= + =  7


	( idx -1 )

*/


	int tmp = edge.orient[5];
	
	edge.orient[5] = (edge.orient[6] + 1) % 2;
	edge.orient[6] = (edge.orient[7] + 1) % 2;
	edge.orient[7] = (edge.orient[4] + 1) % 2;
	edge.orient[4] = (tmp + 1) % 2;

	tmp = edge.perm[5];
	
	edge.perm[5] = edge.perm[6];
	edge.perm[6] = edge.perm[7];
	edge.perm[7] = edge.perm[4];
	edge.perm[4] = tmp;
}

void apply_MD(Fixed_edges &edge) {
/*
	5  = + => 6
	^
	+         + 
		  v
	8 <= + =  7


	( idx -1 )

*/


	int tmp = edge.orient[7];
	
	edge.orient[7] = (edge.orient[6] + 1) % 2;
	edge.orient[6] = (edge.orient[5] + 1) % 2;
	edge.orient[5] = (edge.orient[4] + 1) % 2;
	edge.orient[4] = (tmp + 1) % 2;

	tmp = edge.perm[7];
	
	edge.perm[7] = edge.perm[6];
	edge.perm[6] = edge.perm[5];
	edge.perm[5] = edge.perm[4];
	edge.perm[4] = tmp;
}

Fixed_edges& operator*(Fixed_edges &fe, const moves &f) {
	switch (f) {

		case U:
			apply_U(fe);
			break;

		case iU:
			apply_U(fe);
			apply_U(fe);
			apply_U(fe);
			break;

		case L:
			apply_L(fe);
			break;

		case iL:
			apply_L(fe);
			apply_L(fe);
			apply_L(fe);
			break;

		case F:
			apply_F(fe);
			break;

		case iF:
			apply_F(fe);
			apply_F(fe);
			apply_F(fe);
			break;

		case R:
			apply_R(fe);
			break;

		case iR:
			apply_R(fe);
			apply_R(fe);
			apply_R(fe);
			break;

		case B:
			apply_B(fe);
			break;

		case iB:
			apply_B(fe);
			apply_B(fe);
			apply_B(fe);
			break;

		case D:
			apply_D(fe);
			break;

		case iD:
			apply_D(fe);
			apply_D(fe);
			apply_D(fe);
			break;

		case MU:
			apply_MU(fe);
			break;

		case iMU:
			apply_MU(fe);
			apply_MU(fe);
			apply_MU(fe);
			break;

		case ML:
			apply_ML(fe);
			break;

		case iML:
			apply_ML(fe);
			apply_ML(fe);
			apply_ML(fe);
			break;

		case MF:
			apply_MF(fe);
			break;

		case iMF:
			apply_MF(fe);
			apply_MF(fe);
			apply_MF(fe);
			break;

		case MR:
			apply_MR(fe);
			break;

		case iMR:
			apply_MR(fe);
			apply_MR(fe);
			apply_MR(fe);
			break;

		case MB:
			apply_MB(fe);
			break;

		case iMB:
			apply_MB(fe);
			apply_MB(fe);
			apply_MB(fe);
			break;

		case MD:
			apply_MD(fe);
			break;

		case iMD:
			apply_MD(fe);
			apply_MD(fe);
			apply_MD(fe);
			break;
		
		default:
			std::cerr << "Unknown move\n";
			// no action applied
			break;
	}
	return fe;
}

}
