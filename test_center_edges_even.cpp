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
		std:: cout << '\n';
	}
	return 0;
#endif
	center_edges<6> ce;
	ce.disp_cube();

	apply_ML<6,1>(ce);
	ce.disp_cube();

	center_edges<8> ce2;
	ce2.disp_cube();

	std::cout << "---\n";
	apply_ML<8,1>(ce2);
	ce2.disp_cube();
	std::cout << "---\n";

	center_edges<8> ce3;

	std::cout << "---\n";
	apply_MD<8,1>(ce3);
	ce3.disp_cube();
}
