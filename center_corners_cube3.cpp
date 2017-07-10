#include <iostream>
#include <iomanip>
#include <ostream>
#include "center_corners.h"

using namespace rubik_cube;

int main() {
	Center_corners<5> cube;

//	cube.disp();
	cube.disp_cube();

	cube.apply_ML<0>();
	cube.disp_cube();

	cube.apply_ML<1>();
	cube.disp_cube();

	cube.apply_MR<0>();
	cube.disp_cube();

	Center_corners<4> cube1;
	cube1.disp_cube();

	cube1.apply_ML<1>();
	cube1.disp_cube();

	cube1.apply_MR<1>();
	cube1.disp_cube();

	cube1.apply_MU<1>();
	cube1.disp_cube();

	cube1.apply_MD<1>();
	cube1.disp_cube();

	cube1.apply_MF<1>();
	cube1.disp_cube();

	cube1.apply_MB<1>();
	cube1.disp_cube();

	return 0;
}
