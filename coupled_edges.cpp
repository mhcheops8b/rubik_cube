#include <iostream>
#include <iomanip>
#include "coupled_edges.h"
#include "edge_positions.h"

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
void apply_L(Coupled_edges &edge) {
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


	int tmp_a = edge.orient_a[7];
	int tmp_b = edge.orient_b[7];
	
	edge.orient_a[7] = (edge.orient_b[11] + 1) % 2;
	edge.orient_b[7] = (edge.orient_a[11] + 1) % 2;

	edge.orient_a[11] = (edge.orient_b[4] + 1) % 2;
	edge.orient_b[11] = (edge.orient_a[4] + 1) % 2;

	edge.orient_a[4] = (edge.orient_b[3] + 1) % 2;
	edge.orient_b[4] = (edge.orient_a[3] + 1) % 2;

	edge.orient_a[3] = (tmp_b + 1) % 2;
	edge.orient_b[3] = (tmp_a + 1) % 2;

	tmp_a = edge.perm_a[7];
	tmp_b = edge.perm_b[7];
	
	edge.perm_a[7] = edge.perm_b[11];
	edge.perm_b[7] = edge.perm_a[11];

	edge.perm_a[11] = edge.perm_b[4];
	edge.perm_b[11] = edge.perm_a[4];

	edge.perm_a[4] = edge.perm_b[3];
	edge.perm_b[4] = edge.perm_a[3];

	edge.perm_a[3] = tmp_b;
	edge.perm_b[3] = tmp_a;
}

void apply_R(Coupled_edges &edge) {
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


	( idx -1 )

*/


	int tmp_a = edge.orient_a[5];
	int tmp_b = edge.orient_b[5];
	
	edge.orient_a[5] = (edge.orient_b[9] + 1) % 2;
	edge.orient_b[5] = (edge.orient_a[9] + 1) % 2;

	edge.orient_a[9] = (edge.orient_b[6] + 1) % 2;
	edge.orient_b[9] = (edge.orient_a[6] + 1) % 2;

	edge.orient_a[6] = (edge.orient_b[1] + 1) % 2;
	edge.orient_b[6] = (edge.orient_a[1] + 1) % 2;

	edge.orient_a[1] = (tmp_b + 1) % 2;
	edge.orient_b[1] = (tmp_a + 1) % 2;

	tmp_a = edge.perm_a[5];
	tmp_b = edge.perm_b[5];
	
	edge.perm_a[5] = edge.perm_b[9];
	edge.perm_b[5] = edge.perm_a[9];

	edge.perm_a[9] = edge.perm_b[6];
	edge.perm_b[9] = edge.perm_a[6];

	edge.perm_a[6] = edge.perm_b[1];
	edge.perm_b[6] = edge.perm_a[1];

	edge.perm_a[1] = tmp_b;
	edge.perm_b[1] = tmp_a;
}

void apply_U(Coupled_edges &edge) {
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


	( idx -1 )

*/

	int tmp = edge.orient_a[1];
	
	edge.orient_a[1] = edge.orient_a[2];
	edge.orient_a[2] = edge.orient_a[3];
	edge.orient_a[3] = edge.orient_a[0];
	edge.orient_a[0] = tmp % 2;

	tmp = edge.perm_a[1];
	
	edge.perm_a[1] = edge.perm_a[2];
	edge.perm_a[2] = edge.perm_a[3];
	edge.perm_a[3] = edge.perm_a[0];
	edge.perm_a[0] = tmp;

	tmp = edge.orient_b[1];
	
	edge.orient_b[1] = edge.orient_b[2];
	edge.orient_b[2] = edge.orient_b[3];
	edge.orient_b[3] = edge.orient_b[0];
	edge.orient_b[0] = tmp % 2;

	tmp = edge.perm_b[1];
	
	edge.perm_b[1] = edge.perm_b[2];
	edge.perm_b[2] = edge.perm_b[3];
	edge.perm_b[3] = edge.perm_b[0];
	edge.perm_b[0] = tmp;
}

void apply_D(Coupled_edges &edge) {
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


	( idx -1 )

*/

	// a
	int tmp = edge.orient_a[11];
	
	edge.orient_a[11] = edge.orient_a[10];
	edge.orient_a[10] = edge.orient_a[9];
	edge.orient_a[9] = edge.orient_a[8];
	edge.orient_a[8] = tmp;

	tmp = edge.perm_a[11];
	
	edge.perm_a[11] = edge.perm_a[10];
	edge.perm_a[10] = edge.perm_a[9];
	edge.perm_a[9] = edge.perm_a[8];
	edge.perm_a[8] = tmp;

	// b
	tmp = edge.orient_b[11];
	
	edge.orient_b[11] = edge.orient_b[10];
	edge.orient_b[10] = edge.orient_b[9];
	edge.orient_b[9] = edge.orient_b[8];
	edge.orient_b[8] = tmp;

	tmp = edge.perm_b[11];
	
	edge.perm_b[11] = edge.perm_b[10];
	edge.perm_b[10] = edge.perm_b[9];
	edge.perm_b[9] = edge.perm_b[8];
	edge.perm_b[8] = tmp;
}

void apply_F(Coupled_edges &edge) {
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


	( idx -1 )

*/

	// a
	int tmp = edge.orient_a[4];
	
	edge.orient_a[4] = edge.orient_a[8];
	edge.orient_a[8] = edge.orient_a[5];
	edge.orient_a[5] = edge.orient_a[0];
	edge.orient_a[0] = tmp;

	tmp = edge.perm_a[4];
	
	edge.perm_a[4] = edge.perm_a[8];
	edge.perm_a[8] = edge.perm_a[5];
	edge.perm_a[5] = edge.perm_a[0];
	edge.perm_a[0] = tmp;

	// b
	tmp = edge.orient_b[4];
	
	edge.orient_b[4] = edge.orient_b[8];
	edge.orient_b[8] = edge.orient_b[5];
	edge.orient_b[5] = edge.orient_b[0];
	edge.orient_b[0] = tmp;

	tmp = edge.perm_b[4];
	
	edge.perm_b[4] = edge.perm_b[8];
	edge.perm_b[8] = edge.perm_b[5];
	edge.perm_b[5] = edge.perm_b[0];
	edge.perm_b[0] = tmp;
}

void apply_B(Coupled_edges &edge) {
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


	( idx -1 )

*/

	// a
	int tmp = edge.orient_a[6];
	
	edge.orient_a[6] = edge.orient_a[10];
	edge.orient_a[10] = edge.orient_a[7];
	edge.orient_a[7] = edge.orient_a[2];
	edge.orient_a[2] = tmp;

	tmp = edge.perm_a[6];
	
	edge.perm_a[6] = edge.perm_a[10];
	edge.perm_a[10] = edge.perm_a[7];
	edge.perm_a[7] = edge.perm_a[2];
	edge.perm_a[2] = tmp;

	// b
	tmp = edge.orient_b[6];
	
	edge.orient_b[6] = edge.orient_b[10];
	edge.orient_b[10] = edge.orient_b[7];
	edge.orient_b[7] = edge.orient_b[2];
	edge.orient_b[2] = tmp;

	tmp = edge.perm_b[6];
	
	edge.perm_b[6] = edge.perm_b[10];
	edge.perm_b[10] = edge.perm_b[7];
	edge.perm_b[7] = edge.perm_b[2];
	edge.perm_b[2] = tmp;
}

void apply_ML(Coupled_edges &edge) {
/*
	1b  = + => 9a
	^
	+         + 
		  v
	3a <= + =  11b


	( idx -1 )

*/

	int tmp = edge.orient_a[2];
	
	edge.orient_a[2] = (edge.orient_b[10] + 1) % 2;
	edge.orient_b[10] = (edge.orient_a[8] + 1) % 2;
	edge.orient_a[8] = (edge.orient_b[0] + 1) % 2;
	edge.orient_b[0] = (tmp + 1) % 2;

	tmp = edge.perm_a[2];
	
	edge.perm_a[2] = edge.perm_b[10];
	edge.perm_b[10] = edge.perm_a[8];
	edge.perm_a[8] = edge.perm_b[0];
	edge.perm_b[0] = tmp;

}

void apply_MR(Coupled_edges &edge) {
/*
	1a  = + => 3b
	^
	+         + 
		  v
	9b <= + =  11a


	( idx -1 )

*/

	int tmp = edge.orient_b[8];
	
	edge.orient_b[8] = (edge.orient_a[10] + 1) % 2;
	edge.orient_a[10] = (edge.orient_b[2] + 1) % 2;
	edge.orient_b[2] = (edge.orient_a[0] + 1) % 2;
	edge.orient_a[0] = (tmp + 1) % 2;

	tmp = edge.perm_b[8];
	
	edge.perm_b[8] = edge.perm_a[10];
	edge.perm_a[10] = edge.perm_b[2];
	edge.perm_b[2] = edge.perm_a[0];
	edge.perm_a[0] = tmp;
}

void apply_MU(Coupled_edges &edge) {
/*
	5a  = + =>  8b
	^
	+           + 
		    v
	6b <= + =   7a


	( idx -1 )

*/

	int tmp = edge.orient_b[5];
	
	edge.orient_b[5] = (edge.orient_a[6] + 1) % 2;
	edge.orient_a[6] = (edge.orient_b[7] + 1) % 2;
	edge.orient_b[7] = (edge.orient_a[4] + 1) % 2;
	edge.orient_a[4] = (tmp + 1) % 2;

	tmp = edge.perm_b[5];
	
	edge.perm_b[5] = edge.perm_a[6];
	edge.perm_a[6] = edge.perm_b[7];
	edge.perm_b[7] = edge.perm_a[4];
	edge.perm_a[4] = tmp;
}

void apply_MD(Coupled_edges &edge) {
/*
	5b  = + => 6a
	^
	+          + 
		   v
	8a <= + =  7b


	( idx -1 )

*/

	int tmp = edge.orient_a[7];
	
	edge.orient_a[7] = (edge.orient_b[6] + 1) % 2;
	edge.orient_b[6] = (edge.orient_a[5] + 1) % 2;
	edge.orient_a[5] = (edge.orient_b[4] + 1) % 2;
	edge.orient_b[4] = (tmp + 1) % 2;

	tmp = edge.perm_a[7];
	
	edge.perm_a[7] = edge.perm_b[6];
	edge.perm_b[6] = edge.perm_a[5];
	edge.perm_a[5] = edge.perm_b[4];
	edge.perm_b[4] = tmp;
}

void apply_MF(Coupled_edges &edge) {
/*
	4a  = + =>  2b
	 ^
	 +          + 
		    v
	12b <= + =  10a


	( idx -1 )

*/


	int tmp = edge.orient_b[11];
	
	edge.orient_b[11] = (edge.orient_a[9] + 1) % 2;
	edge.orient_a[9] = (edge.orient_b[1] + 1) % 2;
	edge.orient_b[1] = (edge.orient_a[3] + 1) % 2;
	edge.orient_a[3] = (tmp + 1) % 2;

	tmp = edge.perm_b[11];
	
	edge.perm_b[11] = edge.perm_a[9];
	edge.perm_a[9] = edge.perm_b[1];
	edge.perm_b[1] = edge.perm_a[3];
	edge.perm_a[3] = tmp;
}

void apply_MB(Coupled_edges &edge) {
/*
	4b  = + => 12a
	^
	+         + 
		  v
	2a <= + =  10b


	( idx -1 )

*/


	int tmp = edge.orient_a[1];
	
	edge.orient_a[1] = (edge.orient_b[9] + 1) % 2;
	edge.orient_b[9] = (edge.orient_a[11] + 1) % 2;
	edge.orient_a[11] = (edge.orient_b[3] + 1) % 2;
	edge.orient_b[3] = (tmp + 1) % 2;

	tmp = edge.perm_a[1];
	
	edge.perm_a[1] = edge.perm_b[9];
	edge.perm_b[9] = edge.perm_a[11];
	edge.perm_a[11] = edge.perm_b[3];
	edge.perm_b[3] = tmp;
}

Coupled_edges& operator*(Coupled_edges &ce, const moves &f) {
	switch(f) {

		case U:
			apply_U(ce);
			break;

		case iU:
			apply_U(ce);
			apply_U(ce);
			apply_U(ce);
			break;

		case L:
			apply_L(ce);
			break;

		case iL:
			apply_L(ce);
			apply_L(ce);
			apply_L(ce);
			break;

		case F:
			apply_F(ce);
			break;

		case iF:
			apply_F(ce);
			apply_F(ce);
			apply_F(ce);
			break;

		case R:
			apply_R(ce);
			break;

		case iR:
			apply_R(ce);
			apply_R(ce);
			apply_R(ce);
			break;

		case B:
			apply_B(ce);
			break;

		case iB:
			apply_B(ce);
			apply_B(ce);
			apply_B(ce);
			break;

		case D:
			apply_D(ce);
			break;

		case iD:
			apply_D(ce);
			apply_D(ce);
			apply_D(ce);
			break;

		case MU:
			apply_MU(ce);
			break;

		case iMU:
			apply_MU(ce);
			apply_MU(ce);
			apply_MU(ce);
			break;

		case ML:
			apply_ML(ce);
			break;

		case iML:
			apply_ML(ce);
			apply_ML(ce);
			apply_ML(ce);
			break;

		case MF:
			apply_MF(ce);
			break;

		case iMF:
			apply_MF(ce);
			apply_MF(ce);
			apply_MF(ce);
			break;

		case MR:
			apply_MR(ce);
			break;

		case iMR:
			apply_MR(ce);
			apply_MR(ce);
			apply_MR(ce);
			break;

		case MB:
			apply_MB(ce);
			break;

		case iMB:
			apply_MB(ce);
			apply_MB(ce);
			apply_MB(ce);
			break;

		case MD:
			apply_MD(ce);
			break;

		case iMD:
			apply_MD(ce);
			apply_MD(ce);
			apply_MD(ce);
			break;

		default:
			std::cerr << "Unknown move.\n";
			// no action applied
			break;
			
	}
	return ce;
}

}
