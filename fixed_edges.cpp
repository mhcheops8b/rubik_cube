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
	os << '.';
	os << edge_positions[orient[2]][perm[2]].at(0);
	os << '.';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << edge_positions[orient[3]][perm[3]].at(0);
	os << 'U';
	os << edge_positions[orient[1]][perm[1]].at(0);
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient[0]][perm[0]].at(0);
	os << '.';
	os << '\n';

	// L
	os << '.';
	os << edge_positions[orient[3]][perm[3]].at(1);
	os << '.';

	os << ' ';

	// F
	os << '.';
	os << edge_positions[orient[0]][perm[0]].at(1);
	os << '.';

	os << ' ';

	// R
	os << '.';
	os << edge_positions[orient[1]][perm[1]].at(1);
	os << '.';

	os << ' ';

	// B
	os << '.';
	os << edge_positions[orient[2]][perm[2]].at(1);
	os << '.';
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
	os << '.';
	os << edge_positions[orient[11]][perm[11]].at(1);
	os << '.';

	os << ' ';

	// F
	os << '.';
	os << edge_positions[orient[8]][perm[8]].at(1);
	os << '.';

	os << ' ';

	// R
	os << '.';
	os << edge_positions[orient[9]][perm[9]].at(1);
	os << '.';

	os << ' ';

	// B
	os << '.';
	os << edge_positions[orient[10]][perm[10]].at(1);
	os << '.';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient[8]][perm[8]].at(0);
	os << '.';
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << edge_positions[orient[11]][perm[11]].at(0);
	os << 'D';
	os << edge_positions[orient[9]][perm[9]].at(0);
	os << '\n';

	for (int i = 0; i < 4; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient[10]][perm[10]].at(0);
	os << '.';
	os << '\n';
}

void Fixed_edges::apply_R() {
/*
	2  = + => 7
	^
	+         + 
		  v
	6 <= + =  10


	( idx -1 )

*/


	int tmp = orient[5];
	
	orient[5] = (orient[9] + 1) % 2;
	orient[9] = (orient[6] + 1) % 2;
	orient[6] = (orient[1] + 1) % 2;
	orient[1] = (tmp + 1) % 2;

	tmp = perm[5];
	
	perm[5] = perm[9];
	perm[9] = perm[6];
	perm[6] = perm[1];
	perm[1] = tmp;
}

void Fixed_edges::apply_L() {
/*
	4  = + => 5
	^
	+         + 
		  v
	8 <= + =  12


	( idx -1 )

*/


	int tmp = orient[7];
	
	orient[7] = (orient[11] + 1) % 2;
	orient[11] = (orient[4] + 1) % 2;
	orient[4] = (orient[3] + 1) % 2;
	orient[3] = (tmp + 1) % 2;

	tmp = perm[7];
	
	perm[7] = perm[11];
	perm[11] = perm[4];
	perm[4] = perm[3];
	perm[3] = tmp;
}

void Fixed_edges::apply_U() {
/*
	1  = + => 4
	^
	+         + 
		  v
	2 <= + =  3


	( idx -1 )

*/


	int tmp = orient[1];
	
	orient[1] = orient[2];
	orient[2] = orient[3];
	orient[3] = orient[0];
	orient[0] = tmp % 2;

	tmp = perm[1];
	
	perm[1] = perm[2];
	perm[2] = perm[3];
	perm[3] = perm[0];
	perm[0] = tmp;
}

void Fixed_edges::apply_D() {
/*
	9  = + => 10
	^
	+         + 
		  v
	12 <= + =  11


	( idx -1 )

*/


	int tmp = orient[11];
	
	orient[11] = orient[10];
	orient[10] = orient[9];
	orient[9] = orient[8];
	orient[8] = tmp;

	tmp = perm[11];
	
	perm[11] = perm[10];
	perm[10] = perm[9];
	perm[9] = perm[8];
	perm[8] = tmp;
}

void Fixed_edges::apply_F() {
/*
	1  = + => 6
	^
	+         + 
		  v
	5 <= + =  9


	( idx -1 )

*/


	int tmp = orient[4];
	
	orient[4] = orient[8];
	orient[8] = orient[5];
	orient[5] = orient[0];
	orient[0] = tmp;

	tmp = perm[4];
	
	perm[4] = perm[8];
	perm[8] = perm[5];
	perm[5] = perm[0];
	perm[0] = tmp;
}

void Fixed_edges::apply_B() {
/*
	3  = + => 8
	^
	+         + 
		  v
	7 <= + =  11


	( idx -1 )

*/


	int tmp = orient[6];
	
	orient[6] = orient[10];
	orient[10] = orient[7];
	orient[7] = orient[2];
	orient[2] = tmp;

	tmp = perm[6];
	
	perm[6] = perm[10];
	perm[10] = perm[7];
	perm[7] = perm[2];
	perm[2] = tmp;
}

void Fixed_edges::apply_ML() {
/*
	1  = + => 9
	^
	+         + 
		  v
	3 <= + =  11


	( idx -1 )

*/


	int tmp = orient[2];
	
	orient[2] = (orient[10] + 1) % 2;
	orient[10] = (orient[8] + 1) % 2;
	orient[8] = (orient[0] + 1) % 2;
	orient[0] = (tmp + 1) % 2;

	tmp = perm[2];
	
	perm[2] = perm[10];
	perm[10] = perm[8];
	perm[8] = perm[0];
	perm[0] = tmp;
}

void Fixed_edges::apply_MR() {
/*
	1  = + => 3
	^
	+         + 
		  v
	9 <= + =  11


	( idx -1 )

*/


	int tmp = orient[8];
	
	orient[8] = (orient[10] + 1) % 2;
	orient[10] = (orient[2] + 1) % 2;
	orient[2] = (orient[0] + 1) % 2;
	orient[0] = (tmp + 1) % 2;

	tmp = perm[8];
	
	perm[8] = perm[10];
	perm[10] = perm[2];
	perm[2] = perm[0];
	perm[0] = tmp;
}

void Fixed_edges::apply_MF() {
/*
	4  = + => 2
	^
	+         + 
		  v
	12 <= + =  10


	( idx -1 )

*/


	int tmp = orient[11];
	
	orient[11] = (orient[9] + 1) % 2;
	orient[9] = (orient[1] + 1) % 2;
	orient[1] = (orient[3] + 1) % 2;
	orient[3] = (tmp + 1) % 2;

	tmp = perm[11];
	
	perm[11] = perm[9];
	perm[9] = perm[1];
	perm[1] = perm[3];
	perm[3] = tmp;
}

void Fixed_edges::apply_MB() {
/*
	4  = + => 12
	^
	+         + 
		  v
	2 <= + =  10


	( idx -1 )

*/


	int tmp = orient[1];
	
	orient[1] = (orient[9] + 1) % 2;
	orient[9] = (orient[11] + 1) % 2;
	orient[11] = (orient[3] + 1) % 2;
	orient[3] = (tmp + 1) % 2;

	tmp = perm[1];
	
	perm[1] = perm[9];
	perm[9] = perm[11];
	perm[11] = perm[3];
	perm[3] = tmp;
}

void Fixed_edges::apply_MU() {
/*
	5  = + => 8
	^
	+         + 
		  v
	6 <= + =  7


	( idx -1 )

*/


	int tmp = orient[5];
	
	orient[5] = (orient[6] + 1) % 2;
	orient[6] = (orient[7] + 1) % 2;
	orient[7] = (orient[4] + 1) % 2;
	orient[4] = (tmp + 1) % 2;

	tmp = perm[5];
	
	perm[5] = perm[6];
	perm[6] = perm[7];
	perm[7] = perm[4];
	perm[4] = tmp;
}

void Fixed_edges::apply_MD() {
/*
	5  = + => 6
	^
	+         + 
		  v
	8 <= + =  7


	( idx -1 )

*/


	int tmp = orient[7];
	
	orient[7] = (orient[6] + 1) % 2;
	orient[6] = (orient[5] + 1) % 2;
	orient[5] = (orient[4] + 1) % 2;
	orient[4] = (tmp + 1) % 2;

	tmp = perm[7];
	
	perm[7] = perm[6];
	perm[6] = perm[5];
	perm[5] = perm[4];
	perm[4] = tmp;
}

Fixed_edges& operator*(Fixed_edges &fe, const moves &f) {
	switch (f) {

		case U:
			fe.apply_U();
			break;

		case iU:
			fe.apply_U();
			fe.apply_U();
			fe.apply_U();
			break;

		case L:
			fe.apply_L();
			break;

		case iL:
			fe.apply_L();
			fe.apply_L();
			fe.apply_L();
			break;

		case F:
			fe.apply_F();
			break;

		case iF:
			fe.apply_F();
			fe.apply_F();
			fe.apply_F();
			break;

		case R:
			fe.apply_R();
			break;

		case iR:
			fe.apply_R();
			fe.apply_R();
			fe.apply_R();
			break;

		case B:
			fe.apply_B();
			break;

		case iB:
			fe.apply_B();
			fe.apply_B();
			fe.apply_B();
			break;

		case D:
			fe.apply_D();
			break;

		case iD:
			fe.apply_D();
			fe.apply_D();
			fe.apply_D();
			break;

		case MU:
			fe.apply_MU();
			break;

		case iMU:
			fe.apply_MU();
			fe.apply_MU();
			fe.apply_MU();
			break;

		case ML:
			fe.apply_ML();
			break;

		case iML:
			fe.apply_ML();
			fe.apply_ML();
			fe.apply_ML();
			break;

		case MF:
			fe.apply_MF();
			break;

		case iMF:
			fe.apply_MF();
			fe.apply_MF();
			fe.apply_MF();
			break;

		case MR:
			fe.apply_MR();
			break;

		case iMR:
			fe.apply_MR();
			fe.apply_MR();
			fe.apply_MR();
			break;

		case MB:
			fe.apply_MB();
			break;

		case iMB:
			fe.apply_MB();
			fe.apply_MB();
			fe.apply_MB();
			break;

		case MD:
			fe.apply_MD();
			break;

		case iMD:
			fe.apply_MD();
			fe.apply_MD();
			fe.apply_MD();
			break;
		
		default:
			std::cerr << "Unknown move\n";
			// no action applied
			break;
	}
	return fe;
}

}
