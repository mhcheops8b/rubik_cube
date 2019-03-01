#include <iostream>
#include <iomanip>
#include "coupled_edges.h"
#include "edge_positions.h"
#include "faces.h"

namespace rubik_cube {

Coupled_edges::Coupled_edges() {
	init();
}

void Coupled_edges::init() {
	for (int i = 0; i < 12; i++) {
		perm_a[i] = perm_b[i] = i;
		orient_a[i] = orient_b[i] = 0;
	}
		
}

void Coupled_edges::disp(std::ostream &os) {

	os << "  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (i + 1) << " ";
	os << '\n';

	os << "a:";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (perm_a[i] + 1) << " ";
	os << "\n  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << orient_a[i] << " ";
	os << '\n';

	os << "b:";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (perm_b[i] + 1) << " ";
	os << "\n  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << orient_b[i] << " ";
	os << '\n';

}

void Coupled_edges::disp_cube(std::ostream &os) {
//
	for (int i = 0; i < 6; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient_a[2]][perm_a[2]].at(0);
	os << '.';
	os << edge_positions[orient_b[2]][perm_b[2]].at(0);
	os << '.';
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << edge_positions[orient_b[3]][perm_b[3]].at(0);
	os << "...";
	os << edge_positions[orient_a[1]][perm_a[1]].at(0);
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << "..U..";
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << edge_positions[orient_a[3]][perm_a[3]].at(0);
	os << "...";
	os << edge_positions[orient_b[1]][perm_b[1]].at(0);
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient_b[0]][perm_b[0]].at(0);
	os << '.';
	os << edge_positions[orient_a[0]][perm_a[0]].at(0);
	os << '.';
	os << '\n';

//
	os << '.';
	os << edge_positions[orient_b[3]][perm_b[3]].at(1);
	os << '.';
	os << edge_positions[orient_a[3]][perm_a[3]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_b[0]][perm_b[0]].at(1);
	os << '.';
	os << edge_positions[orient_a[0]][perm_a[0]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_b[1]][perm_b[1]].at(1);
	os << '.';
	os << edge_positions[orient_a[1]][perm_a[1]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_b[2]][perm_b[2]].at(1);
	os << '.';
	os << edge_positions[orient_a[2]][perm_a[2]].at(1);
	os << '.';
	os << '\n';

//

	os << edge_positions[orient_b[7]][perm_b[7]].at(0);
	os << "...";
	os << edge_positions[orient_a[4]][perm_a[4]].at(0);

	os << ' ';

	os << edge_positions[orient_a[4]][perm_a[4]].at(1);
	os << "...";
	os << edge_positions[orient_b[5]][perm_b[5]].at(1);

	os << ' ';

	os << edge_positions[orient_b[5]][perm_b[5]].at(0);
	os << "...";
	os << edge_positions[orient_a[6]][perm_a[6]].at(0);

	os << ' ';

	os << edge_positions[orient_a[6]][perm_a[6]].at(1);
	os << "...";
	os << edge_positions[orient_b[7]][perm_b[7]].at(1);

	os << '\n';
//
	os << "..L.. ..F.. ..R.. ..B..";
	os << '\n';
//

	os << edge_positions[orient_a[7]][perm_a[7]].at(0);
	os << "...";
	os << edge_positions[orient_b[4]][perm_b[4]].at(0);

	os << ' ';

	os << edge_positions[orient_b[4]][perm_b[4]].at(1);
	os << "...";
	os << edge_positions[orient_a[5]][perm_a[5]].at(1);

	os << ' ';

	os << edge_positions[orient_a[5]][perm_a[5]].at(0);
	os << "...";
	os << edge_positions[orient_b[6]][perm_b[6]].at(0);

	os << ' ';

	os << edge_positions[orient_b[6]][perm_b[6]].at(1);
	os << "...";
	os << edge_positions[orient_a[7]][perm_a[7]].at(1);

	os << '\n';

//
	os << '.';
	os << edge_positions[orient_a[11]][perm_a[11]].at(1);
	os << '.';
	os << edge_positions[orient_b[11]][perm_b[11]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_a[8]][perm_a[8]].at(1);
	os << '.';
	os << edge_positions[orient_b[8]][perm_b[8]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_a[9]][perm_a[9]].at(1);
	os << '.';
	os << edge_positions[orient_b[9]][perm_b[9]].at(1);
	os << '.';

	os << ' ';

	os << '.';
	os << edge_positions[orient_a[10]][perm_a[10]].at(1);
	os << '.';
	os << edge_positions[orient_b[10]][perm_b[10]].at(1);
	os << '.';
	os << '\n';

//
	for (int i = 0; i < 6; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient_a[8]][perm_a[8]].at(0);
	os << '.';
	os << edge_positions[orient_b[8]][perm_b[8]].at(0);
	os << '.';
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << edge_positions[orient_b[11]][perm_b[11]].at(0);
	os << "...";
	os << edge_positions[orient_a[9]][perm_a[9]].at(0);
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << "..D..";
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << edge_positions[orient_a[11]][perm_a[11]].at(0);
	os << "...";
	os << edge_positions[orient_b[9]][perm_b[9]].at(0);
	os << '\n';

	for (int i = 0; i < 6; i++)
		os << ' ';
	os << '.';
	os << edge_positions[orient_b[10]][perm_b[10]].at(0);
	os << '.';
	os << edge_positions[orient_a[10]][perm_a[10]].at(0);
	os << '.';
	os << '\n';

#if 0
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
#endif
}

void Coupled_edges::to_perm24(int (&perm)[24]) {
	
	for (int i = 0; i < 12; i++) {
		perm[i] = (orient_a[i] == 0 ? perm_a[i]: 12 + perm_a[i]);
		perm[12+i] = (orient_b[i] == 0 ? 12 + perm_b[i] : perm_b[i]);
	}
}


void Coupled_edges::disp_perm24() {
	int perm_inv[24];

	to_perm24(perm_inv);

	for (int i = 0; i < 24; i++) {
		std::cout << std::setw(3) << i + 1 << " ";
	}
	std::cout << '\n';

	for (int i = 0; i < 24; i++) {
		std::cout << std::setw(3) << perm_inv[i] + 1 << " ";
	}
	std::cout << '\n';
}

int Coupled_edges::perm24_signum() {
	int perm_inv[24];

	to_perm24(perm_inv);

	int signum = 1;
	for (int i = 0; i < 24; i++)
	for (int j = i + 1; j < 24; j++)
		if (perm_inv[i]>perm_inv[j])
			signum*=-1;

	return signum;
	
}
void Coupled_edges::apply_L() {
/*
	4b  = + =>  5a
	^
	+           + 
		    v
	8a <= + =  12b

	4a  = + =>  5b
	^
	+           + 
		    v
	8b <= + =  12a


	( idx - 1 )

*/


	int tmp_a = orient_a[7];
	int tmp_b = orient_b[7];
	
	orient_a[7] = (orient_b[11] + 1) % 2;
	orient_b[7] = (orient_a[11] + 1) % 2;

	orient_a[11] = (orient_b[4] + 1) % 2;
	orient_b[11] = (orient_a[4] + 1) % 2;

	orient_a[4] = (orient_b[3] + 1) % 2;
	orient_b[4] = (orient_a[3] + 1) % 2;

	orient_a[3] = (tmp_b + 1) % 2;
	orient_b[3] = (tmp_a + 1) % 2;

	tmp_a = perm_a[7];
	tmp_b = perm_b[7];
	
	perm_a[7] = perm_b[11];
	perm_b[7] = perm_a[11];

	perm_a[11] = perm_b[4];
	perm_b[11] = perm_a[4];

	perm_a[4] = perm_b[3];
	perm_b[4] = perm_a[3];

	perm_a[3] = tmp_b;
	perm_b[3] = tmp_a;
}

void Coupled_edges::apply_R() {
/*
	2a  = + =>  7b
	^
	+           + 
		    v
	6b <= + =  10a

	2b  = + =>  7a
	^
	+           + 
		    v
	6a <= + =  10b


	( idx - 1 )

*/


	int tmp_a = orient_a[5];
	int tmp_b = orient_b[5];
	
	orient_a[5] = (orient_b[9] + 1) % 2;
	orient_b[5] = (orient_a[9] + 1) % 2;

	orient_a[9] = (orient_b[6] + 1) % 2;
	orient_b[9] = (orient_a[6] + 1) % 2;

	orient_a[6] = (orient_b[1] + 1) % 2;
	orient_b[6] = (orient_a[1] + 1) % 2;

	orient_a[1] = (tmp_b + 1) % 2;
	orient_b[1] = (tmp_a + 1) % 2;

	tmp_a = perm_a[5];
	tmp_b = perm_b[5];
	
	perm_a[5] = perm_b[9];
	perm_b[5] = perm_a[9];

	perm_a[9] = perm_b[6];
	perm_b[9] = perm_a[6];

	perm_a[6] = perm_b[1];
	perm_b[6] = perm_a[1];

	perm_a[1] = tmp_b;
	perm_b[1] = tmp_a;
}

void Coupled_edges::apply_U() {
/*
	1a  = + => 4a
	^
	+          + 
		   v
	2a <= + =  3a

	1b  = + => 4b
	^
	+          + 
		   v
	2b <= + =  3b


	( idx - 1 )

*/

	int tmp = orient_a[1];
	
	orient_a[1] = orient_a[2];
	orient_a[2] = orient_a[3];
	orient_a[3] = orient_a[0];
	orient_a[0] = tmp % 2;

	tmp = perm_a[1];
	
	perm_a[1] = perm_a[2];
	perm_a[2] = perm_a[3];
	perm_a[3] = perm_a[0];
	perm_a[0] = tmp;

	tmp = orient_b[1];
	
	orient_b[1] = orient_b[2];
	orient_b[2] = orient_b[3];
	orient_b[3] = orient_b[0];
	orient_b[0] = tmp % 2;

	tmp = perm_b[1];
	
	perm_b[1] = perm_b[2];
	perm_b[2] = perm_b[3];
	perm_b[3] = perm_b[0];
	perm_b[0] = tmp;
}

void Coupled_edges::apply_D() {
/*
	9a  = + =>  10a
	^
	+            + 
		     v
	12a <= + =  11a

	9b  = + =>  10b
	^
	+            + 
		     v
	12b <= + =  11b


	( idx - 1 )

*/

	// a
	int tmp = orient_a[11];
	
	orient_a[11] = orient_a[10];
	orient_a[10] = orient_a[9];
	orient_a[9] = orient_a[8];
	orient_a[8] = tmp;

	tmp = perm_a[11];
	
	perm_a[11] = perm_a[10];
	perm_a[10] = perm_a[9];
	perm_a[9] = perm_a[8];
	perm_a[8] = tmp;

	// b
	tmp = orient_b[11];
	
	orient_b[11] = orient_b[10];
	orient_b[10] = orient_b[9];
	orient_b[9] = orient_b[8];
	orient_b[8] = tmp;

	tmp = perm_b[11];
	
	perm_b[11] = perm_b[10];
	perm_b[10] = perm_b[9];
	perm_b[9] = perm_b[8];
	perm_b[8] = tmp;
}

void Coupled_edges::apply_F() {
/*
	1a  = + => 6a
	^
	+          + 
		   v
	5a <= + =  9a

	1b  = + => 6b
	^
	+          + 
		   v
	5b <= + =  9b


	( idx - 1 )

*/

	// a
	int tmp = orient_a[4];
	
	orient_a[4] = orient_a[8];
	orient_a[8] = orient_a[5];
	orient_a[5] = orient_a[0];
	orient_a[0] = tmp;

	tmp = perm_a[4];
	
	perm_a[4] = perm_a[8];
	perm_a[8] = perm_a[5];
	perm_a[5] = perm_a[0];
	perm_a[0] = tmp;

	// b
	tmp = orient_b[4];
	
	orient_b[4] = orient_b[8];
	orient_b[8] = orient_b[5];
	orient_b[5] = orient_b[0];
	orient_b[0] = tmp;

	tmp = perm_b[4];
	
	perm_b[4] = perm_b[8];
	perm_b[8] = perm_b[5];
	perm_b[5] = perm_b[0];
	perm_b[0] = tmp;
}

void Coupled_edges::apply_B() {
/*
	3a  = + =>  8a
	^
	+           + 
		    v
	7a <= + =  11a

	3b  = + =>  8b
	^
	+           + 
		    v
	7b <= + =  11b


	( idx - 1 )

*/

	// a
	int tmp = orient_a[6];
	
	orient_a[6] = orient_a[10];
	orient_a[10] = orient_a[7];
	orient_a[7] = orient_a[2];
	orient_a[2] = tmp;

	tmp = perm_a[6];
	
	perm_a[6] = perm_a[10];
	perm_a[10] = perm_a[7];
	perm_a[7] = perm_a[2];
	perm_a[2] = tmp;

	// b
	tmp = orient_b[6];
	
	orient_b[6] = orient_b[10];
	orient_b[10] = orient_b[7];
	orient_b[7] = orient_b[2];
	orient_b[2] = tmp;

	tmp = perm_b[6];
	
	perm_b[6] = perm_b[10];
	perm_b[10] = perm_b[7];
	perm_b[7] = perm_b[2];
	perm_b[2] = tmp;
}

void Coupled_edges::apply_ML() {
/*
	1b  = + => 9a
	^
	+         + 
		  v
	3a <= + =  11b


	( idx - 1 )

*/

	int tmp = orient_a[2];
	
	orient_a[2] = (orient_b[10] + 1) % 2;
	orient_b[10] = (orient_a[8] + 1) % 2;
	orient_a[8] = (orient_b[0] + 1) % 2;
	orient_b[0] = (tmp + 1) % 2;

	tmp = perm_a[2];
	
	perm_a[2] = perm_b[10];
	perm_b[10] = perm_a[8];
	perm_a[8] = perm_b[0];
	perm_b[0] = tmp;

}

void Coupled_edges::apply_MR() {
/*
	1a  = + => 3b
	^
	+         + 
		  v
	9b <= + =  11a


	( idx - 1 )

*/

	int tmp = orient_b[8];
	
	orient_b[8] = (orient_a[10] + 1) % 2;
	orient_a[10] = (orient_b[2] + 1) % 2;
	orient_b[2] = (orient_a[0] + 1) % 2;
	orient_a[0] = (tmp + 1) % 2;

	tmp = perm_b[8];
	
	perm_b[8] = perm_a[10];
	perm_a[10] = perm_b[2];
	perm_b[2] = perm_a[0];
	perm_a[0] = tmp;
}

void Coupled_edges::apply_MU() {
/*
	5a  = + =>  8b
	^
	+           + 
		    v
	6b <= + =   7a


	( idx - 1 )

*/

	int tmp = orient_b[5];
	
	orient_b[5] = (orient_a[6] + 1) % 2;
	orient_a[6] = (orient_b[7] + 1) % 2;
	orient_b[7] = (orient_a[4] + 1) % 2;
	orient_a[4] = (tmp + 1) % 2;

	tmp = perm_b[5];
	
	perm_b[5] = perm_a[6];
	perm_a[6] = perm_b[7];
	perm_b[7] = perm_a[4];
	perm_a[4] = tmp;
}

void Coupled_edges::apply_MD() {
/*
	5b  = + => 6a
	^
	+          + 
		   v
	8a <= + =  7b


	( idx - 1 )

*/

	int tmp = orient_a[7];
	
	orient_a[7] = (orient_b[6] + 1) % 2;
	orient_b[6] = (orient_a[5] + 1) % 2;
	orient_a[5] = (orient_b[4] + 1) % 2;
	orient_b[4] = (tmp + 1) % 2;

	tmp = perm_a[7];
	
	perm_a[7] = perm_b[6];
	perm_b[6] = perm_a[5];
	perm_a[5] = perm_b[4];
	perm_b[4] = tmp;
}

void Coupled_edges::apply_MF() {
/*
	4a  = + =>  2b
	 ^
	 +          + 
		    v
	12b <= + =  10a


	( idx -1 )

*/


	int tmp = orient_b[11];
	
	orient_b[11] = (orient_a[9] + 1) % 2;
	orient_a[9] = (orient_b[1] + 1) % 2;
	orient_b[1] = (orient_a[3] + 1) % 2;
	orient_a[3] = (tmp + 1) % 2;

	tmp = perm_b[11];
	
	perm_b[11] = perm_a[9];
	perm_a[9] = perm_b[1];
	perm_b[1] = perm_a[3];
	perm_a[3] = tmp;
}

void Coupled_edges::apply_MB() {
/*
	4b  = + => 12a
	^
	+         + 
		  v
	2a <= + =  10b


	( idx - 1 )

*/


	int tmp = orient_a[1];
	
	orient_a[1] = (orient_b[9] + 1) % 2;
	orient_b[9] = (orient_a[11] + 1) % 2;
	orient_a[11] = (orient_b[3] + 1) % 2;
	orient_b[3] = (tmp + 1) % 2;

	tmp = perm_a[1];
	
	perm_a[1] = perm_b[9];
	perm_b[9] = perm_a[11];
	perm_a[11] = perm_b[3];
	perm_b[3] = tmp;
}

Coupled_edges& operator*(Coupled_edges &ce, const moves &f) {
	switch(f) {

		case U:
			ce.apply_U();
			break;

		case iU:
			ce.apply_U();
			ce.apply_U();
			ce.apply_U();
			break;

		case L:
			ce.apply_L();
			break;

		case iL:
			ce.apply_L();
			ce.apply_L();
			ce.apply_L();
			break;

		case F:
			ce.apply_F();
			break;

		case iF:
			ce.apply_F();
			ce.apply_F();
			ce.apply_F();
			break;

		case R:
			ce.apply_R();
			break;

		case iR:
			ce.apply_R();
			ce.apply_R();
			ce.apply_R();
			break;

		case B:
			ce.apply_B();
			break;

		case iB:
			ce.apply_B();
			ce.apply_B();
			ce.apply_B();
			break;

		case D:
			ce.apply_D();
			break;

		case iD:
			ce.apply_D();
			ce.apply_D();
			ce.apply_D();
			break;

		case MU:
			ce.apply_MU();
			break;

		case iMU:
			ce.apply_MU();
			ce.apply_MU();
			ce.apply_MU();
			break;

		case ML:
			ce.apply_ML();
			break;

		case iML:
			ce.apply_ML();
			ce.apply_ML();
			ce.apply_ML();
			break;

		case MF:
			ce.apply_MF();
			break;

		case iMF:
			ce.apply_MF();
			ce.apply_MF();
			ce.apply_MF();
			break;

		case MR:
			ce.apply_MR();
			break;

		case iMR:
			ce.apply_MR();
			ce.apply_MR();
			ce.apply_MR();
			break;

		case MB:
			ce.apply_MB();
			break;

		case iMB:
			ce.apply_MB();
			ce.apply_MB();
			ce.apply_MB();
			break;

		case MD:
			ce.apply_MD();
			break;

		case iMD:
			ce.apply_MD();
			ce.apply_MD();
			ce.apply_MD();
			break;

		default:
			std::cerr << "Unknown move.\n";
			// no action applied
			break;
			
	}
	return ce;
}
	void Coupled_edges::toPermutationN() {
		// a positions
		for (int i = 0; i < 12; i++) {
			std::cout << edge_positions[orient_a[i]][perm_a[i]] << (orient_a[i]==0? 'a':'b') << "->" << edge_positions[0][i] << "a\n";

			for (int j = 0; j < 2; j++) {
				int idx1 = get_index(perm_a[i], edge_positions[orient_a[i]][perm_a[i]].at(j), orient_a[i] == 1, 4, 1),
				idx2 = get_index(i, edge_positions[0][i].at(j), false, 4, 1);
				if (idx1 != idx2)
					std::cout << idx1 << "->" << idx2 << ", ";

			}
			std::cout << '\n';
			
		}

		// b positions
		for (int i = 0; i < 12; i++) {
			std::cout << edge_positions[orient_b[i]][perm_b[i]] << (orient_b[i]==0? 'b':'a') << "->" << edge_positions[0][i] << "b\n";

			for (int j = 0; j < 2; j++) {
				int idx1 = get_index(perm_b[i], edge_positions[orient_b[i]][perm_b[i]].at(j), orient_b[i] == 0, 4, 1),
				idx2 = get_index(i, edge_positions[0][i].at(j), true, 4, 1);
				if (idx1 != idx2)
					std::cout << idx1 << "->" << idx2 << ", ";

			}
			std::cout << '\n';
		}
	}

	int Coupled_edges::get_index(int position, char face, bool ab, int cube_dim, int layer) { 
		int plus = (cube_dim % 2 == 0? cube_dim / 2: (cube_dim + 1) / 2)  + layer - 1,
		minus = (cube_dim % 2 == 0? cube_dim / 2: (cube_dim - 1) /2) - layer,
		index = 0;
		if (ab) {
			//swap + and - for b positions
			int tmp = plus;
			plus = minus;
			minus = tmp;
		}
		// a positions
		switch (position) {
			// UF = U(n,+)F(1,+)
			case 0:
				switch (face) {
					case 'U':
						index = Faces::U * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + plus;
						break;
					case 'F':
						index = Faces::F * cube_dim * cube_dim + plus;
						break;
					default:
						break;
				};
				break;
			// UR = U(-,n)R(1,+)
			case 1:
				switch (face) {
					case 'U':
						index = Faces::U * cube_dim * cube_dim + minus * cube_dim + (cube_dim - 1);
						break;
					case 'R':
						index = Faces::R * cube_dim * cube_dim + plus;
						break;
					default:
						break;
				};
				break;
			// UB = U(1,-)B(1,+)
			case 2:
				switch (face) {
					case 'U':
						index = Faces::U * cube_dim * cube_dim + minus;
						break;
					case 'B':
						index = Faces::B * cube_dim * cube_dim + plus;
						break;
					default:
						break;
				};
				break;
			// UL = U(+,1)L(1,+)
			case 3:
				switch (face) {
					case 'U':
						index = Faces::U * cube_dim * cube_dim + plus * cube_dim;
						break;
					case 'L':
						index = Faces::L * cube_dim * cube_dim + plus;
						break;
					default:
						break;
				};
				break;
			// LF = L(-,n)F(-,1)
			case 4:
				switch (face) {
					case 'L':
						index = Faces::L * cube_dim * cube_dim + minus * cube_dim + (cube_dim - 1);
						break;
					case 'F':
						index = Faces::F * cube_dim * cube_dim + minus * cube_dim;
						break;
					default:
						break;
				};
				break;
			// FR = F(+,n)R(+,1)
			case 5:
				switch (face) {
					case 'F':
						index = Faces::R * cube_dim * cube_dim + plus * cube_dim + (cube_dim - 1);
						break;
					case 'R':
						index = Faces::R * cube_dim * cube_dim + plus * cube_dim;
						break;
					default:
						break;
				};
				break;
			// RB = R(-,n)B(-,1)
			case 6:
				switch (face) {
					case 'R':
						index = Faces::R * cube_dim * cube_dim + minus * cube_dim + (cube_dim - 1);
						break;
					case 'B':
						index = Faces::B * cube_dim * cube_dim + minus * cube_dim;
						break;
					default:
						break;
				};
				break;
			// BL = B(+,n)L(+,1)
			case 7:
				switch (face) {
					case 'B':
						index = Faces::B * cube_dim * cube_dim + plus * cube_dim + (cube_dim - 1);
						break;
					case 'L':
						index = Faces::L * cube_dim * cube_dim + plus * cube_dim;
						break;
					default:
						break;
				};
				break;
			// FD = F(n,-)D(1,-)
			case 8:
				switch (face) {
					case 'F':
						index = Faces::F * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + minus;// plus;
						break;
					case 'D':
						index = Faces::D * cube_dim * cube_dim + minus;
						break;
					default:
						break;
				};
				break;
			// DR = D(-,n)R(n,-)
			case 9:
				switch (face) {
					case 'D':
						index = Faces::D * cube_dim * cube_dim + minus * cube_dim  + cube_dim - 1;
						break;
					case 'R':
						index = Faces::R * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + minus;
						break;
					default:
						break;
				};
				break;
			// DB = D(n,+)B(n,-)
			case 10:
				switch (face) {
					case 'D':
						index = Faces::D * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + plus;
						break;
					case 'B':
						index = Faces::B * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + minus;
						break;
					default:
						break;
				};
				break;
			// DL = D(+,1)L(n,-)
			case 11:
				switch (face) {
					case 'D':
						index = Faces::D * cube_dim * cube_dim + plus * cube_dim;
						break;
					case 'L':
						index = Faces::L * cube_dim * cube_dim + (cube_dim - 1) * cube_dim + minus;
						break;
					default:
						break;
				};
				break;

			default:
				break;		
		};

		return index;
	}

}
