#include "center_edges.h"

using namespace rubik_cube;

int main() {

	//all possible moves Center_edges<10>
	Center_edges<10> ce10;
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

	//all possible moves Center_edges<10>
	Center_edges<11> ce11;
	apply_L(ce11);
	apply_R(ce11);
	apply_F(ce11);
	apply_B(ce11);
	apply_U(ce11);
	apply_D(ce11);

	apply_ML<11,0>(ce11);
	apply_ML<11,1>(ce11);
	apply_ML<11,2>(ce11);
	apply_ML<11,3>(ce11);
	apply_ML<11,4>(ce11);

	apply_MR<11,0>(ce11);
	apply_MR<11,1>(ce11);
	apply_MR<11,2>(ce11);
	apply_MR<11,3>(ce11);
	apply_MR<11,4>(ce11);

	apply_MF<11,0>(ce11);
	apply_MF<11,1>(ce11);
	apply_MF<11,2>(ce11);
	apply_MF<11,3>(ce11);
	apply_MF<11,4>(ce11);

	apply_MB<11,0>(ce11);
	apply_MB<11,1>(ce11);
	apply_MB<11,2>(ce11);
	apply_MB<11,3>(ce11);
	apply_MB<11,4>(ce11);

	apply_MU<11,0>(ce11);
	apply_MU<11,1>(ce11);
	apply_MU<11,2>(ce11);
	apply_MU<11,3>(ce11);
	apply_MU<11,4>(ce11);

	apply_MD<11,0>(ce11);
	apply_MD<11,1>(ce11);
	apply_MD<11,2>(ce11);
	apply_MD<11,3>(ce11);
	apply_MD<11,4>(ce11);
	
	ce11.disp_cube();

}

