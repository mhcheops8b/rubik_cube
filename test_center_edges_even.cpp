// CE_FIX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
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

	Center_edges<5> ce_odd;
	Center_edges<6> ce_even;
	//apply_Face(L, ce_odd);
	apply_Face(ce_even, L);
	apply_Face(ce_even, R);

}


