#include "corners.h"

namespace rubik_cube {

static const std::string positions[3][8] = {
	{"UFL", "URF", "UBR", "ULB", "DLF", "DFR", "DRB", "DBL"},
	{"LUF", "FUR", "RUB", "BUL", "FDL", "RDF", "BDR", "LDB"},
	{"UFL", "URF", "UBR", "ULB", "DLF", "DFR", "DRB", "DBL"},
};

Corners::Corners() {
	for (int i = 0; i < 8; i++) {
		perm[i] = i;
		orient[i] = 0;
	}
	
}

void Corners::disp_cube(std::ostream &os) {
//	const static moves positions[] =
//	1: UFL 2: URF 3: UBR 4: ULB
//	5: DLF 6: DFR 7: DRB 8: DBL
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << positions[orient[3]][perm[3]].at(0);
	os << '.';
	os << positions[orient[2]][perm[2]].at(0);
	os << '\n';
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << ".U.\n";
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << positions[orient[0]][perm[0]].at(0);
	os << '.';
	os << positions[orient[1]][perm[1]].at(0);
	os << '\n';

//
	os << positions[orient[0]][perm[0]].at(2);
	os << '.';
	os << positions[orient[0]][perm[0]].at(2);
	os << ' ';
	os << positions[orient[0]][perm[0]].at(1);
	os << '.';
	os << positions[orient[1]][perm[1]].at(2);
	os << ' ';
	os << positions[orient[1]][perm[1]].at(1);
	os << '.';
	os << positions[orient[2]][perm[2]].at(2);
	os << ' ';
	os << positions[orient[2]][perm[2]].at(1);
	os << '.';
	os << positions[orient[3]][perm[3]].at(2);
	os << '\n';

	os << ".L. .F. .R. .B.";
	os << '\n';

//
	
	os << positions[orient[7]][perm[7]].at(2);
	os << '.';
	os << positions[orient[4]][perm[4]].at(1);
	os << ' ';
	os << positions[orient[4]][perm[4]].at(2);
	os << '.';
	os << positions[orient[5]][perm[5]].at(1);
	os << ' ';
	os << positions[orient[5]][perm[5]].at(2);
	os << '.';
	os << positions[orient[6]][perm[6]].at(1);
	os << ' ';
	os << positions[orient[6]][perm[6]].at(2);
	os << '.';
	os << positions[orient[7]][perm[7]].at(1);
	os << '\n';
	

//
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << positions[orient[4]][perm[4]].at(0);
	os << '.';
	os << positions[orient[5]][perm[5]].at(0);
	os << '\n';
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << ".D.\n";
	for (int i = 0; i < 4; i++)
		os << ' ';
	os << positions[orient[7]][perm[7]].at(0);
	os << '.';
	os << positions[orient[6]][perm[6]].at(0);
	os << '\n';
	
	

}

void apply_R(Corners &corn) {
/*
	2  = + => 3
	^
	-         - 
		  v
	6 <= + =  7


	( idx -1 )

*/


	int tmp = corn.orient[5];
	
	corn.orient[5] = (corn.orient[6] + 1) % 3;
	corn.orient[6] = (corn.orient[2] + 2) % 3;
	corn.orient[2] = (corn.orient[1] + 1) % 3;
	corn.orient[1] = (tmp + 2) % 3;

	tmp = corn.perm[5];
	
	corn.perm[5] = corn.perm[6];
	corn.perm[6] = corn.perm[2];
	corn.perm[2] = corn.perm[1];
	corn.perm[1] = tmp;
}

void apply_L(Corners &corn) {
/*
	1  = - => 5
	^
	+         + 
		  v
	4 <= - =  8


	( idx -1 )

*/


	int tmp = corn.orient[3];
	
	corn.orient[3] = (corn.orient[7] + 2) % 3;
	corn.orient[7] = (corn.orient[4] + 1) % 3;
	corn.orient[4] = (corn.orient[0] + 2) % 3;
	corn.orient[0] = (tmp + 1) % 3;

	tmp = corn.perm[3];
	
	corn.perm[3] = corn.perm[7];
	corn.perm[7] = corn.perm[4];
	corn.perm[4] = corn.perm[0];
	corn.perm[0] = tmp;
}


void apply_U(Corners &corn) {
/*
	1  = 0 => 4
	^
	0         0 
		  v
	2 <= 0 =  3


	( idx -1 )

*/

	int tmp = corn.orient[1];
	
	corn.orient[1] = corn.orient[2];
	corn.orient[2] = corn.orient[3];
	corn.orient[3] = corn.orient[0];
	corn.orient[0] = tmp;

	tmp = corn.perm[1];
	
	corn.perm[1] = corn.perm[2];
	corn.perm[2] = corn.perm[3];
	corn.perm[3] = corn.perm[0];
	corn.perm[0] = tmp;
}

void apply_D(Corners &corn) {
/*
	5  = 0 => 6
	^
	0         0 
		  v
	8 <= 0 =  7


	( idx -1 )

*/

	int tmp = corn.orient[7];
	
	corn.orient[7] = corn.orient[6];
	corn.orient[6] = corn.orient[5];
	corn.orient[5] = corn.orient[4];
	corn.orient[4] = tmp;

	tmp = corn.perm[7];
	
	corn.perm[7] = corn.perm[6];
	corn.perm[6] = corn.perm[5];
	corn.perm[5] = corn.perm[4];
	corn.perm[4] = tmp;
}

void apply_F(Corners &corn) {
/*
	1  = + => 2
	^
	-         - 
		  v
	5 <= + =  6


	( idx -1 )

*/


	int tmp = corn.orient[4];
	
	corn.orient[4] = (corn.orient[5] + 1) % 3;
	corn.orient[5] = (corn.orient[1] + 2) % 3;
	corn.orient[1] = (corn.orient[0] + 1) % 3;
	corn.orient[0] = (tmp + 2) % 3;

	tmp = corn.perm[4];
	
	corn.perm[4] = corn.perm[5];
	corn.perm[5] = corn.perm[1];
	corn.perm[1] = corn.perm[0];
	corn.perm[0] = tmp;
}

void apply_B(Corners &corn) {
/*
	4  = - => 8
	^
	+         + 
		  v
	3 <= - =  7


	( idx -1 )

*/


	int tmp = corn.orient[2];
	
	corn.orient[2] = (corn.orient[6] + 2) % 3;
	corn.orient[6] = (corn.orient[7] + 1) % 3;
	corn.orient[7] = (corn.orient[3] + 2) % 3;
	corn.orient[3] = (tmp + 1) % 3;

	tmp = corn.perm[2];
	
	corn.perm[2] = corn.perm[6];
	corn.perm[6] = corn.perm[7];
	corn.perm[7] = corn.perm[3];
	corn.perm[3] = tmp;
}




void Corners::disp(std::ostream &os) {
	for (int i = 0; i < 8; i++)
		os << (i + 1) << " ";
	os << '\n';

	for (int i = 0; i < 8; i++)
		os << (perm[i] + 1) << " ";
	os << '\n';
	for (int i = 0; i < 8; i++)
		os << orient[i] << " ";
	os << '\n';

}



Corners& operator*(Corners &c1, const moves &f) {
	switch (f) {
		case U:
			apply_U(c1);
			break;

		case L:
			apply_L(c1);
			break;

		case F:
			apply_F(c1);
			break;

		case D:
			apply_D(c1);
			break;

		case R:
			apply_R(c1);
			break;

		case B:
			apply_B(c1);
			break;

		case iU:
			apply_U(c1);
			apply_U(c1);
			apply_U(c1);
			break;

		case iL:
			apply_L(c1);
			apply_L(c1);
			apply_L(c1);
			break;

		case iF:
			apply_F(c1);
			apply_F(c1);
			apply_F(c1);
			break;

		case iD:
			apply_D(c1);
			apply_D(c1);
			apply_D(c1);
			break;

		case iR:
			apply_R(c1);
			apply_R(c1);
			apply_R(c1);
			break;

		case iB:
			apply_B(c1);
			apply_B(c1);
			apply_B(c1);
			break;

		default:
			std::cerr << "Unknown move\n";
			// no action applied
			break;
	}
	return c1;
}
}
