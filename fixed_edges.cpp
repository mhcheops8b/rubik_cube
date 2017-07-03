#include <iostream>
#include <iomanip>
#include "fixed_edges.h"


fixed_edges::fixed_edges() {
	for (int i = 0; i < 12; i++) {
		perm[i] = i;
		orient[i] = 0;
	}
	
}

void fixed_edges::disp(std::ostream &os) {
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

void apply_R(fixed_edges &edge) {
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

void apply_L(fixed_edges &edge) {
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

void apply_U(fixed_edges &edge) {
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

void apply_D(fixed_edges &edge) {
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

void apply_F(fixed_edges &edge) {
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

void apply_B(fixed_edges &edge) {
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

void apply_ML(fixed_edges &edge) {
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

void apply_MR(fixed_edges &edge) {
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

void apply_MF(fixed_edges &edge) {
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

void apply_MB(fixed_edges &edge) {
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

void apply_MU(fixed_edges &edge) {
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

void apply_MD(fixed_edges &edge) {
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
