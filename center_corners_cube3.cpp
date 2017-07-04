#include <iostream>
#include <iomanip>
#include <ostream>
#include "center_corners.h"

int main() {
	Center_corners<5> cube;

//	cube.disp();
	cube.disp_cube();

	apply_ML<5,0>(cube);
	cube.disp_cube();

	apply_ML<5,1>(cube);
	cube.disp_cube();

	apply_MR<5,0>(cube);
	cube.disp_cube();

	Center_corners<4> cube1;
	cube1.disp_cube();

	apply_ML<4,1>(cube1);
	cube1.disp_cube();

	apply_MR<4,1>(cube1);
	cube1.disp_cube();

	apply_MU<4,1>(cube1);
	cube1.disp_cube();

	apply_MD<4,1>(cube1);
	cube1.disp_cube();
	apply_MF<4,1>(cube1);
	cube1.disp_cube();
	apply_MB<4,1>(cube1);
	cube1.disp_cube();


	return 0;
}
