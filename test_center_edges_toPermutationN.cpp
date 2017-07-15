#include "center_edges.h"
#include "cubeNNN.h"

int main() {

	rubik_cube::Center_edges<6> ce;
	ce.toPermutationN();
	std::cout << "----------------\n";
	ce.apply_ML<1>();
	std::cout << "----------------\n";
	ce.toPermutationN();
	std::cout << "----------------\n";
	Permutation<6> cube;
	cube = ce.toPermutationN(cube);
	cube.disp_cube();


	rubik_cube::Center_edges<5> ce5;

	ce5.toPermutationN();
	std::cout << "----------------\n";
	ce5.apply_ML<0>();
	ce5.toPermutationN();
	std::cout << "----------------\n";
	ce5.disp_cube();
	std::cout << "----------------\n";
	Permutation<5> cube5;
	cube5 = ce5.toPermutationN(cube5);
	cube5.disp_cube();

	return 0;
}
