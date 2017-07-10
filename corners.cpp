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

void Corners::apply_L() {
/*
	1  = - => 5
	^
	+         + 
		  v
	4 <= - =  8


	( idx -1 )

*/


	int tmp = orient[3];
	
	orient[3] = (orient[7] + 2) % 3;
	orient[7] = (orient[4] + 1) % 3;
	orient[4] = (orient[0] + 2) % 3;
	orient[0] = (tmp + 1) % 3;

	tmp = perm[3];
	
	perm[3] = perm[7];
	perm[7] = perm[4];
	perm[4] = perm[0];
	perm[0] = tmp;
}

void Corners::apply_R() {
/*
	2  = + => 3
	^
	-         - 
		  v
	6 <= + =  7


	( idx -1 )

*/


	int tmp = orient[5];
	
	orient[5] = (orient[6] + 1) % 3;
	orient[6] = (orient[2] + 2) % 3;
	orient[2] = (orient[1] + 1) % 3;
	orient[1] = (tmp + 2) % 3;

	tmp = perm[5];
	
	perm[5] = perm[6];
	perm[6] = perm[2];
	perm[2] = perm[1];
	perm[1] = tmp;
}




void Corners::apply_U() {
/*
	1  = 0 => 4
	^
	0         0 
		  v
	2 <= 0 =  3


	( idx -1 )

*/

	int tmp = orient[1];
	
	orient[1] = orient[2];
	orient[2] = orient[3];
	orient[3] = orient[0];
	orient[0] = tmp;

	tmp = perm[1];
	
	perm[1] = perm[2];
	perm[2] = perm[3];
	perm[3] = perm[0];
	perm[0] = tmp;
}

void Corners::apply_D() {
/*
	5  = 0 => 6
	^
	0         0 
		  v
	8 <= 0 =  7


	( idx -1 )

*/

	int tmp = orient[7];
	
	orient[7] = orient[6];
	orient[6] = orient[5];
	orient[5] = orient[4];
	orient[4] = tmp;

	tmp = perm[7];
	
	perm[7] = perm[6];
	perm[6] = perm[5];
	perm[5] = perm[4];
	perm[4] = tmp;
}

void Corners::apply_F() {
/*
	1  = + => 2
	^
	-         - 
		  v
	5 <= + =  6


	( idx -1 )

*/


	int tmp = orient[4];
	
	orient[4] = (orient[5] + 1) % 3;
	orient[5] = (orient[1] + 2) % 3;
	orient[1] = (orient[0] + 1) % 3;
	orient[0] = (tmp + 2) % 3;

	tmp = perm[4];
	
	perm[4] = perm[5];
	perm[5] = perm[1];
	perm[1] = perm[0];
	perm[0] = tmp;
}

void Corners::apply_B() {
/*
	4  = - => 8
	^
	+         + 
		  v
	3 <= - =  7


	( idx -1 )

*/
	int tmp = orient[2];
	
	orient[2] = (orient[6] + 2) % 3;
	orient[6] = (orient[7] + 1) % 3;
	orient[7] = (orient[3] + 2) % 3;
	orient[3] = (tmp + 1) % 3;

	tmp = perm[2];
	
	perm[2] = perm[6];
	perm[6] = perm[7];
	perm[7] = perm[3];
	perm[3] = tmp;
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
			c1.apply_U();
			break;

		case L:
			c1.apply_L();
			break;

		case F:
			c1.apply_F();
			break;

		case D:
			c1.apply_D();
			break;

		case R:
			c1.apply_R();
			break;

		case B:
			c1.apply_B();
			break;

		case iU:
			c1.apply_U();
			c1.apply_U();
			c1.apply_U();
			break;

		case iL:
			c1.apply_L();
			c1.apply_L();
			c1.apply_L();
			break;

		case iF:
			c1.apply_F();
			c1.apply_F();
			c1.apply_F();
			break;

		case iD:
			c1.apply_D();
			c1.apply_D();
			c1.apply_D();
			break;

		case iR:
			c1.apply_R();
			c1.apply_R();
			c1.apply_R();
			break;

		case iB:
			c1.apply_B();
			c1.apply_B();
			c1.apply_B();
			break;

		default:
			std::cerr << "Unknown move\n";
			// no action applied
			break;
	}
	return c1;
}
}
