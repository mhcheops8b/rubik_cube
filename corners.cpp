#include "corners.h"
#include "faces.h"

namespace rubik_cube {

const std::string Corners::positions[3][8] = {
	{"UFL", "URF", "UBR", "ULB", "DLF", "DFR", "DRB", "DBL"},
	{"LUF", "FUR", "RUB", "BUL", "FDL", "RDF", "BDR", "LDB"},
	{"FLU", "RFU", "BRU", "LBU", "LFD", "FRD", "RBD", "BLD"}
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

int Corners::get_index(int position, char face, int cube_dim) {
	int index = 0;
	switch (position) {
		case 0:
			// UFL = U(n,1)F(1,1)L(1,n)
			switch (face) {
				case 'U':
					index = Faces::U * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				case 'F':
					index = Faces::F * cube_dim * cube_dim;
					break;
				case 'L':
					index = Faces::L * cube_dim * cube_dim + cube_dim - 1;
					break;
				default:
					break;
			};
			break;
		case 1:
			// URF = U(n,n)R(1,1)F(1,n)
			switch (face) {
				case 'U':
					index = Faces::U * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'R':
					index = Faces::R * cube_dim * cube_dim;
					break;
				case 'F':
					index = Faces::F * cube_dim * cube_dim + cube_dim - 1;
					break;
				default:
					break;
			};
			break;
		case 2:
			// UBR = U(1,n)B(1,1)R(1,n)
			switch (face) {
				case 'U':
					index = Faces::U * cube_dim * cube_dim + (cube_dim - 1);
					break;
				case 'B':
					index = Faces::B * cube_dim * cube_dim;
					break;
				case 'R':
					index = Faces::R * cube_dim * cube_dim + cube_dim - 1;
					break;
				default:
					break;
			};
			break;
		case 3:
			// ULB = U(1,1)L(1,1)B(1,n)
			switch (face) {
				case 'U':
					index = Faces::U * cube_dim * cube_dim;
					break;
				case 'L':
					index = Faces::L * cube_dim * cube_dim;
					break;
				case 'B':
					index = Faces::B * cube_dim * cube_dim + cube_dim - 1;
					break;
				default:
					break;
			};
			break;
		case 4:
			// DLF = D(1,1)L(n,n)F(n,1)
			switch (face) {
				case 'D':
					index = Faces::D * cube_dim * cube_dim;
					break;
				case 'L':
					index = Faces::L * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'F':
					index = Faces::F * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				default:
					break;
			};
			break;
		case 5:
			// DFR = D(1,n)F(n,n)R(n,1)
			switch (face) {
				case 'D':
					index = Faces::D * cube_dim * cube_dim + cube_dim - 1;
					break;
				case 'F':
					index = Faces::F * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'R':
					index = Faces::R * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				default:
					break;
			};
			break;
		case 6:
			// DRB = D(n,n)R(n,n)B(n,1)
			switch (face) {
				case 'D':
					index = Faces::D * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'R':
					index = Faces::R * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'B':
					index = Faces::B * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				default:
					break;
			};
			break;
		case 7:
			// DBL = D(n,1)B(n,n)L(n,1)
			switch (face) {
				case 'D':
					index = Faces::D * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				case 'B':
					index = Faces::B * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + (cube_dim - 1);
					break;
				case 'L':
					index = Faces::L * cube_dim * cube_dim + (cube_dim - 1) * cube_dim;
					break;
				default:
					break;
			};
			break;

		default:
//			std::cerr << "Unknown position, (0 - 7) are allowed.\n";
			break;
	};
	
	return index;
}

void Corners::toPermutationN() {

	for (int i = 0; i < 8; i++) {
		std::cout << "perm: " << perm[i] << ", orient: " << orient[i] << '\n';
		std::cout << Corners::positions[orient[i]][perm[i]] << "->" << Corners::positions[0][i] << "\n";

		for (int j = 0; j < 3; j++) {
			int idx1 = get_index(perm[i], positions[orient[i]][perm[i]].at(j), 2),
			idx2 = get_index(i, positions[0][i].at(j), 2);

			if (idx1 != idx2) 
				std::cout << idx1 << "->" << idx2 << ", ";
		
		}
		std:: cout << '\n';
	}

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
