#include <iostream>
#include <iomanip>
#include "center_corners.h"
#include "center_edges_old.h"

struct cube {
	Center_corners<5> cc5;
	center_edges_odd<5> ce5;
};

int main() {
	cube test;

	apply_ML<5,0>(test.cc5);
	apply_ML<5,1>(test.ce5);

	test.cc5.disp();
	test.ce5.disp_cube();

//	Center_corners<4> cc4;
//	cc4.disp();
}
