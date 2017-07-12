#include <iostream>
#include <iomanip>
#include "center_corners.h"
#include "center_edges.h"
#include "corners.h"
#include "fixed_edges.h"

struct cube333 {
	rubik_cube::Corners c;
	rubik_cube::Fixed_edges fe;

	void disp_cube(std::ostream &os = std::cout);
	void apply_L();
};

void cube333::disp_cube(std::ostream &os) {
	os << "Corners:\n";
	c.disp_cube();
	os << "Edges:\n";
	fe.disp_cube();
}

void cube333::apply_L() {
	c.apply_L();
	fe.apply_L();
}


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


	cube333 stdcube;
	stdcube.c.disp();
	std::cout << "------------\n";
	stdcube.disp_cube();
	std::cout << "------------\n";

	stdcube.apply_L();
	stdcube.c.disp();
	std::cout << "------------\n";
	stdcube.disp_cube();
}
