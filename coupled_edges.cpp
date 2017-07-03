#include <iostream>
#include <iomanip>
#include "coupled_edges.h"

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

}
