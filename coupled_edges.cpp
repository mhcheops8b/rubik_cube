#include <iostream>
#include <iomanip>
#include "coupled_edges.h"

coupled_edges::coupled_edges(): ea(), eb() {
	
}

void coupled_edges::disp(std::ostream &os) {
	os << "  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (i + 1) << " ";
	os << '\n';

	os << "a:";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (ea.perm[i] + 1) << " ";
	os << "\n  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << ea.orient[i] << " ";
	os << '\n';

	os << "b:";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << (eb.perm[i] + 1) << " ";
	os << "\n  ";
	for (int i = 0; i < 12; i++)
		os << std::setw(3) << eb.orient[i] << " ";
	os << '\n';

}

void coupled_edges::disp_perm24() {
	int perm_inv[24];

	for (int i = 0; i < 12; i++) {
		perm_inv[i] = (ea.orient[i] == 0 ? ea.perm[i]: 12+ea.perm[i]);
		perm_inv[12+i] = (eb.orient[i] == 0 ? 12+eb.perm[i] : eb.perm[i]);
	}

	for (int i = 0; i < 24; i++) {
		std::cout << std::setw(3) << i + 1 << " ";
	}
	std::cout << '\n';

	for (int i = 0; i < 24; i++) {
		std::cout << std::setw(3) << perm_inv[i] + 1 << " ";
	}
	std::cout << '\n';
}

int coupled_edges::perm24_signum() {
	int perm_inv[24];

	for (int i = 0; i < 12; i++) {
		perm_inv[i] = (ea.orient[i] == 0 ? ea.perm[i]: 12+ea.perm[i]);
		perm_inv[12+i] = (eb.orient[i] == 0 ? 12+eb.perm[i] : eb.perm[i]);
	}

	int signum = 1;
	for (int i = 0; i < 24; i++)
	for (int j = i + 1; j < 24; j++)
		if (perm_inv[i]>perm_inv[j])
			signum*=-1;

	return signum;
	
}
void apply_L(coupled_edges &edge) {
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


	( idx -1 )

*/


	int tmp_a = edge.ea.orient[7];
	int tmp_b = edge.eb.orient[7];
	
	edge.ea.orient[7] = (edge.eb.orient[11] + 1) % 2;
	edge.eb.orient[7] = (edge.ea.orient[11] + 1) % 2;

	edge.ea.orient[11] = (edge.eb.orient[4] + 1) % 2;
	edge.eb.orient[11] = (edge.ea.orient[4] + 1) % 2;

	edge.ea.orient[4] = (edge.eb.orient[3] + 1) % 2;
	edge.eb.orient[4] = (edge.ea.orient[3] + 1) % 2;

	edge.ea.orient[3] = (tmp_b + 1) % 2;
	edge.eb.orient[3] = (tmp_a + 1) % 2;

	tmp_a = edge.ea.perm[7];
	tmp_b = edge.eb.perm[7];
	
	edge.ea.perm[7] = edge.eb.perm[11];
	edge.eb.perm[7] = edge.ea.perm[11];

	edge.ea.perm[11] = edge.eb.perm[4];
	edge.eb.perm[11] = edge.ea.perm[4];

	edge.ea.perm[4] = edge.eb.perm[3];
	edge.eb.perm[4] = edge.ea.perm[3];

	edge.ea.perm[3] = tmp_b;
	edge.eb.perm[3] = tmp_a;
}

void apply_R(coupled_edges &edge) {
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


	int tmp_a = edge.ea.orient[5];
	int tmp_b = edge.eb.orient[5];
	
	edge.ea.orient[5] = (edge.eb.orient[9] + 1) % 2;
	edge.eb.orient[5] = (edge.ea.orient[9] + 1) % 2;

	edge.ea.orient[9] = (edge.eb.orient[6] + 1) % 2;
	edge.eb.orient[9] = (edge.ea.orient[6] + 1) % 2;

	edge.ea.orient[6] = (edge.eb.orient[1] + 1) % 2;
	edge.eb.orient[6] = (edge.ea.orient[1] + 1) % 2;

	edge.ea.orient[1] = (tmp_b + 1) % 2;
	edge.eb.orient[1] = (tmp_a + 1) % 2;

	tmp_a = edge.ea.perm[5];
	tmp_b = edge.eb.perm[5];
	
	edge.ea.perm[5] = edge.eb.perm[9];
	edge.eb.perm[5] = edge.ea.perm[9];

	edge.ea.perm[9] = edge.eb.perm[6];
	edge.eb.perm[9] = edge.ea.perm[6];

	edge.ea.perm[6] = edge.eb.perm[1];
	edge.eb.perm[6] = edge.ea.perm[1];

	edge.ea.perm[1] = tmp_b;
	edge.eb.perm[1] = tmp_a;
}

void apply_U(coupled_edges &edge) {
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

	apply_U(edge.ea);
	apply_U(edge.eb);
}

void apply_D(coupled_edges &edge) {
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

	apply_D(edge.ea);
	apply_D(edge.eb);
}

void apply_F(coupled_edges &edge) {
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


	apply_F(edge.ea);
	apply_F(edge.eb);
}

void apply_B(coupled_edges &edge) {
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
	apply_B(edge.ea);
	apply_B(edge.eb);
}

void apply_ML(coupled_edges &edge) {
/*
	1b  = + => 9a
	^
	+         + 
		  v
	3a <= + =  11b


	( idx -1 )

*/

	int tmp = edge.ea.orient[2];
	
	edge.ea.orient[2] = (edge.eb.orient[10] + 1) % 2;
	edge.eb.orient[10] = (edge.ea.orient[8] + 1) % 2;
	edge.ea.orient[8] = (edge.eb.orient[0] + 1) % 2;
	edge.eb.orient[0] = (tmp + 1) % 2;

	tmp = edge.ea.perm[2];
	
	edge.ea.perm[2] = edge.eb.perm[10];
	edge.eb.perm[10] = edge.ea.perm[8];
	edge.ea.perm[8] = edge.eb.perm[0];
	edge.eb.perm[0] = tmp;

}

void apply_MR(coupled_edges &edge) {
/*
	1a  = + => 3b
	^
	+         + 
		  v
	9b <= + =  11a


	( idx -1 )

*/

	int tmp = edge.eb.orient[8];
	
	edge.eb.orient[8] = (edge.ea.orient[10] + 1) % 2;
	edge.ea.orient[10] = (edge.eb.orient[2] + 1) % 2;
	edge.eb.orient[2] = (edge.ea.orient[0] + 1) % 2;
	edge.ea.orient[0] = (tmp + 1) % 2;

	tmp = edge.eb.perm[8];
	
	edge.eb.perm[8] = edge.ea.perm[10];
	edge.ea.perm[10] = edge.eb.perm[2];
	edge.eb.perm[2] = edge.ea.perm[0];
	edge.ea.perm[0] = tmp;
}

void apply_MU(coupled_edges &edge) {
/*
	5a  = + =>  8b
	^
	+           + 
		    v
	6b <= + =   7a


	( idx -1 )

*/

	int tmp = edge.eb.orient[5];
	
	edge.eb.orient[5] = (edge.ea.orient[6] + 1) % 2;
	edge.ea.orient[6] = (edge.eb.orient[7] + 1) % 2;
	edge.eb.orient[7] = (edge.ea.orient[4] + 1) % 2;
	edge.ea.orient[4] = (tmp + 1) % 2;

	tmp = edge.eb.perm[5];
	
	edge.eb.perm[5] = edge.ea.perm[6];
	edge.ea.perm[6] = edge.eb.perm[7];
	edge.eb.perm[7] = edge.ea.perm[4];
	edge.ea.perm[4] = tmp;
}

void apply_MD(coupled_edges &edge) {
/*
	5b  = + => 6a
	^
	+          + 
		   v
	8a <= + =  7b


	( idx -1 )

*/

	int tmp = edge.ea.orient[7];
	
	edge.ea.orient[7] = (edge.eb.orient[6] + 1) % 2;
	edge.eb.orient[6] = (edge.ea.orient[5] + 1) % 2;
	edge.ea.orient[5] = (edge.eb.orient[4] + 1) % 2;
	edge.eb.orient[4] = (tmp + 1) % 2;

	tmp = edge.ea.perm[7];
	
	edge.ea.perm[7] = edge.eb.perm[6];
	edge.eb.perm[6] = edge.ea.perm[5];
	edge.ea.perm[5] = edge.eb.perm[4];
	edge.eb.perm[4] = tmp;
}

void apply_MF(coupled_edges &edge) {
/*
	4a  = + =>  2b
	 ^
	 +          + 
		    v
	12b <= + =  10a


	( idx -1 )

*/


	int tmp = edge.eb.orient[11];
	
	edge.eb.orient[11] = (edge.ea.orient[9] + 1) % 2;
	edge.ea.orient[9] = (edge.eb.orient[1] + 1) % 2;
	edge.eb.orient[1] = (edge.ea.orient[3] + 1) % 2;
	edge.ea.orient[3] = (tmp + 1) % 2;

	tmp = edge.eb.perm[11];
	
	edge.eb.perm[11] = edge.ea.perm[9];
	edge.ea.perm[9] = edge.eb.perm[1];
	edge.eb.perm[1] = edge.ea.perm[3];
	edge.ea.perm[3] = tmp;
}

void apply_MB(coupled_edges &edge) {
/*
	4b  = + => 12a
	^
	+         + 
		  v
	2a <= + =  10b


	( idx -1 )

*/


	int tmp = edge.ea.orient[1];
	
	edge.ea.orient[1] = (edge.eb.orient[9] + 1) % 2;
	edge.eb.orient[9] = (edge.ea.orient[11] + 1) % 2;
	edge.ea.orient[11] = (edge.eb.orient[3] + 1) % 2;
	edge.eb.orient[3] = (tmp + 1) % 2;

	tmp = edge.ea.perm[1];
	
	edge.ea.perm[1] = edge.eb.perm[9];
	edge.eb.perm[9] = edge.ea.perm[11];
	edge.ea.perm[11] = edge.eb.perm[3];
	edge.eb.perm[3] = tmp;
}


