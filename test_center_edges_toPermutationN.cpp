#include "center_edges.h"
#include "cubeNNN.h"

int main() {

	rubik_cube::Center_edges<6> ce;
	ce.toPermutationN();

	ce.apply_ML<1>();
	ce.toPermutationN();

	Permutation<6> cube;
	cube = ce.toPermutationN(cube);
	cube.disp_cube();
#if 0
	rubik_cube::Center_edges<5> ce;

//	ce.toPermutationN();

	ce.apply_ML<0>();
//	ce.toPermutationN();
	ce.disp_cube();
	std::cout << "----------------\n";
	Permutation<5> cube;
	cube = ce.toPermutationN(cube);
	cube.disp_cube();
#endif

	return 0;
}
