#include <iostream>
#include <iomanip>
#include "center_corners.h"
#include "center_edges.h"

struct cube {
	rubik_cube::Center_corners<5> cc5;
	rubik_cube::Center_edges<5> ce5;
};

int main() {
	cube test;

	test.cc5.apply_ML<0>();
	test.ce5.apply_ML<1>();

	test.cc5.disp_perm();
	test.ce5.disp_cube();

	rubik_cube::Center_corners<4> cc4;
	cc4.disp_cube();
}
