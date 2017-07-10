#include "center_edges.h"

using namespace rubik_cube;

int main() {

	//all possible moves Center_edges<10>
	Center_edges<10> ce10;
	ce10.apply_L();
	ce10.apply_R();
	ce10.apply_F();
	ce10.apply_B();
	ce10.apply_U();
	ce10.apply_D();

	ce10.apply_ML<1>();
	ce10.apply_ML<2>();
	ce10.apply_ML<3>();
	ce10.apply_ML<4>();

	ce10.apply_MR<1>();
	ce10.apply_MR<2>();
	ce10.apply_MR<3>();
	ce10.apply_MR<4>();

	ce10.apply_MF<1>();
	ce10.apply_MF<2>();
	ce10.apply_MF<3>();
	ce10.apply_MF<4>();

	ce10.apply_MB<1>();
	ce10.apply_MB<2>();
	ce10.apply_MB<3>();
	ce10.apply_MB<4>();

	ce10.apply_MU<1>();
	ce10.apply_MU<2>();
	ce10.apply_MU<3>();
	ce10.apply_MU<4>();

	ce10.apply_MD<1>();
	ce10.apply_MD<2>();
	ce10.apply_MD<3>();
	ce10.apply_MD<4>();
	
	ce10.disp_cube();

	//all possible moves Center_edges<10>
	Center_edges<11> ce11;
	ce11.apply_L();
	ce11.apply_R();
	ce11.apply_F();
	ce11.apply_B();
	ce11.apply_U();
	ce11.apply_D();

	ce11.apply_ML<0>();
	ce11.apply_ML<1>();
	ce11.apply_ML<2>();
	ce11.apply_ML<3>();
	ce11.apply_ML<4>();

	ce11.apply_MR<0>();
	ce11.apply_MR<1>();
	ce11.apply_MR<2>();
	ce11.apply_MR<3>();
	ce11.apply_MR<4>();

	ce11.apply_MF<0>();
	ce11.apply_MF<1>();
	ce11.apply_MF<2>();
	ce11.apply_MF<3>();
	ce11.apply_MF<4>();

	ce11.apply_MB<0>();
	ce11.apply_MB<1>();
	ce11.apply_MB<2>();
	ce11.apply_MB<3>();
	ce11.apply_MB<4>();

	ce11.apply_MU<0>();
	ce11.apply_MU<1>();
	ce11.apply_MU<2>();
	ce11.apply_MU<3>();
	ce11.apply_MU<4>();

	ce11.apply_MD<0>();
	ce11.apply_MD<1>();
	ce11.apply_MD<2>();
	ce11.apply_MD<3>();
	ce11.apply_MD<4>();
	
	ce11.disp_cube();

}

