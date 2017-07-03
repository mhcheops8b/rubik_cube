#include <iostream>
#include <iomanip>
#include "center_edges.h"

int main() {
	
	center_edges_odd<5> cu5;

	cu5.disp_cube();
	std::cout << "\t---\n";

#if 0
// test moves
	apply_MR<5,1>(cu5);
	cu5.disp_cube();
	std::cout << "\t---\n";
return 0;
#endif



	apply_MR<5,1>(cu5);
	apply_MR<5,1>(cu5);
	apply_R(cu5);
	apply_R(cu5);
	apply_B(cu5);
	apply_B(cu5);
	apply_U(cu5);
	apply_U(cu5);
	apply_ML<5,1>(cu5);
	apply_U(cu5);
	apply_U(cu5);
	apply_MR<5,1>(cu5);
	apply_MR<5,1>(cu5);
	apply_MR<5,1>(cu5);
	apply_U(cu5);
	apply_U(cu5);
	apply_MR<5,1>(cu5);
	apply_U(cu5);
	apply_U(cu5);
	apply_F(cu5);
	apply_F(cu5);
	apply_MR<5,1>(cu5);
	apply_F(cu5);
	apply_F(cu5);
	apply_ML<5,1>(cu5);
	apply_ML<5,1>(cu5);
	apply_ML<5,1>(cu5);
	apply_B(cu5);
	apply_B(cu5);
	apply_R(cu5);
	apply_R(cu5);
	apply_MR<5,1>(cu5);
	apply_MR<5,1>(cu5);
	cu5.disp_cube();
	std::cout << "Sgn: " << signum(cu5) << '\n';
	std::cout << "\t---\n";
	return 0;
	


//	center_edges_odd<5> cu5;
//	center_edges_odd<7> cu7;
//	center_edges_odd<9> cu9;

//	disp_face(cu9, U);
//	cu9.disp_cube();
//return 0;

//	center_edges_odd<5> cu5;
//	std::cout << "\tCube 5\n";
//	apply_Face(cu5, U);
//
//	center_edges_odd<7> cu7;
//	std::cout << "\tCube 7\n";
//	apply_Face(cu7, L);
//	center_edges_odd<9> cu9;
//	std::cout << "\tCube 9\n";
//	apply_Face(cu9, F);
//
//	apply_U(cu5);
//	apply_L(cu7);
//	apply_B(cu9);
//	apply_F(cu9);
//	apply_R(cu7);
//	apply_D(cu7);
//	center_edges_odd<5> cu5;
//	std::cout << "\tCube 5\n";
//	std::cout << "MD0:\n";
//	apply_MD<5,0>(cu5);
//	std::cout << "MD1:\n";
//	apply_MD<5,1>(cu5);
//
//	center_edges_odd<7> cu7;
//	std::cout << "\tCube 7\n";
//	std::cout << "MD0:\n";
//	apply_MD<7,0>(cu7);
//	std::cout << "MD1:\n";
//	apply_MD<7,1>(cu7);
//	std::cout << "MD2:\n";
//	apply_MD<7,2>(cu7);
//
//	center_edges_odd<9> cu9;
//	std::cout << "\tCube 9\n";
//	std::cout << "MD0:\n";
//	apply_MD<9,0>(cu9);
//	std::cout << "MD1:\n";
//	apply_MD<9,1>(cu9);
//	std::cout << "MD2:\n";
//	apply_MD<9,2>(cu9);
//	std::cout << "MD3:\n";
//	apply_MD<9,3>(cu9);

//	center_edges_odd<5> cu5;
//	std::cout << "\tCube 5\n";
//	std::cout << "MU0:\n";
//	apply_MU<5,0>(cu5);
//	std::cout << "MU1:\n";
//	apply_MU<5,1>(cu5);
//
//	center_edges_odd<7> cu7;
//	std::cout << "\tCube 7\n";
//	std::cout << "MU0:\n";
//	apply_MU<7,0>(cu7);
//	std::cout << "MU1:\n";
//	apply_MU<7,1>(cu7);
//	std::cout << "MU2:\n";
//	apply_MU<7,2>(cu7);
//
//	center_edges_odd<9> cu9;
//	std::cout << "\tCube 9\n";
//	std::cout << "MU0:\n";
//	apply_MU<9,0>(cu9);
//	std::cout << "MU1:\n";
//	apply_MU<9,1>(cu9);
//	std::cout << "MU2:\n";
//	apply_MU<9,2>(cu9);
//	std::cout << "MU3:\n";
//	apply_MU<9,3>(cu9);
	
//	center_edges_odd<5> cu5;
//	std::cout << "\tCube 5\n";
//	std::cout << "MB0:\n";
//	apply_MB<5,0>(cu5);
//	std::cout << "MB1:\n";
//	apply_MB<5,1>(cu5);
//
//	center_edges_odd<7> cu7;
//	std::cout << "\tCube 7\n";
//	std::cout << "MB0:\n";
//	apply_MB<7,0>(cu7);
//	std::cout << "MB1:\n";
//	apply_MB<7,1>(cu7);
//	std::cout << "MB2:\n";
//	apply_MB<7,2>(cu7);


//	center_edges_odd<5> cu5;
//	std::cout << "\tCube 5\n";
//	std::cout << "MF0:\n";
//	apply_MF<5,0>(cu5);
//	std::cout << "MF1:\n";
//	apply_MF<5,1>(cu5);
//
//	center_edges_odd<7> cu7;
//	std::cout << "\tCube 7\n";
//	std::cout << "MF0:\n";
//	apply_MF<7,0>(cu7);
//	std::cout << "MF1:\n";
//	apply_MF<7,1>(cu7);
//	std::cout << "MF2:\n";
//	apply_MF<7,2>(cu7);

//	std::cout << "ML0:\n";
//	apply_ML<5,0>(cu5);
//	std::cout << "ML1:\n";
//	apply_ML<5,1>(cu5);
//	std::cout << "MR0:\n";
//	apply_MR<5,0>(cu5);
//	std::cout << "MR1:\n";
//	apply_MR<5,1>(cu5);

return 0;
#if 0
	center_edges_odd<7> cu7;

	std::cout << "\tCube 7\n";
	std::cout << "ML0:\n";
	apply_ML<7,0>(cu7);
	std::cout << "ML1:\n";
	apply_ML<7,1>(cu7);
	std::cout << "ML2:\n";
	apply_ML<7,2>(cu7);

	center_edges_odd<9> cu9;

	std::cout << "\tCube 9\n";
	std::cout << "ML0:\n";
	apply_ML<9,0>(cu9);
	std::cout << "ML1:\n";
	apply_ML<9,1>(cu9);
	std::cout << "ML2:\n";
	apply_ML<9,2>(cu9);



	return 0;
#endif
}
