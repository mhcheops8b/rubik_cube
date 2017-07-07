// CE_FIX.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <iostream>
#include "center_edges_old.h"
#include "center_edges.h"

int main() {

#if 0
	for (int k = number_of_layers_even<8>; k > 0; k--) {

		for (int t = number_of_layers_even<8>; t > k; t--) {

			//			t-th layer, WF, index, t + k - 2

			//			os << perm[] layer 3-t, face WF, index 2*k -3 - t

			std::cout << WF_even<8>(t, t + k - 2) << " (" << t << ", " << t + k - 2 << ") ";
		}
		std::cout << '\n';
	}
	return 0;
#endif
	center_edges_even<6, true> ce;
	ce.disp_cube();

	apply_ML<6, 1>(ce);
	ce.disp_cube();

	center_edges_even<8, true> ce2;
	ce2.disp_cube();

	std::cout << "---\n";
	apply_ML<8, 1>(ce2);
	ce2.disp_cube();
	std::cout << "---\n";

	center_edges_even<8, true> ce3;

	std::cout << "---\n";
	apply_MD<8, 1>(ce3);
	ce3.disp_cube();

#if 0
///
	Center_edges<7> ce_odd;

	ce_odd.disp_cube();
	std::cout << "----\n";
	apply_MF<7,2>(ce_odd);

//	apply_L(ce_odd);
//	apply_F(ce_odd);
	ce_odd.disp_cube();
#endif


	std::cout << "----\n";
	rubik_cube::Center_edges<8> ce_even;
	ce_even.disp_cube();
	std::cout << "----\n";
//	apply_ML<6,1>(ce_even);
	apply_MF<8,3>(ce_even);
	ce_even.disp_cube();
	//std::cout << "----\n";
	
	//apply_Face(L, ce_odd);
//	apply_Face(ce_even, L);
//	apply_Face(ce_even, R);
//	apply_L(ce_even);
//	apply_R(ce_even);
//	apply_F(ce_even);
//	apply_B(ce_even);
//	apply_U(ce_even);
//	apply_D(ce_even);
//
//	apply_ML<5,1>(ce_odd);

	ce_even.disp_perm();
	//all possible moves
	rubik_cube::Center_edges<10> ce10;
	apply_L(ce10);
	apply_R(ce10);
	apply_F(ce10);
	apply_B(ce10);
	apply_U(ce10);
	apply_D(ce10);

	apply_ML<10,1>(ce10);
	apply_ML<10,2>(ce10);
	apply_ML<10,3>(ce10);
	apply_ML<10,4>(ce10);

	apply_MR<10,1>(ce10);
	apply_MR<10,2>(ce10);
	apply_MR<10,3>(ce10);
	apply_MR<10,4>(ce10);

	apply_MF<10,1>(ce10);
	apply_MF<10,2>(ce10);
	apply_MF<10,3>(ce10);
	apply_MF<10,4>(ce10);

	apply_MB<10,1>(ce10);
	apply_MB<10,2>(ce10);
	apply_MB<10,3>(ce10);
	apply_MB<10,4>(ce10);

	apply_MU<10,1>(ce10);
	apply_MU<10,2>(ce10);
	apply_MU<10,3>(ce10);
	apply_MU<10,4>(ce10);

	apply_MD<10,1>(ce10);
	apply_MD<10,2>(ce10);
	apply_MD<10,3>(ce10);
	apply_MD<10,4>(ce10);
	
	ce10.disp_cube();

}

