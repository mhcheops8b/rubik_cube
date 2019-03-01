#include <iostream>
#include <iomanip>
#include "center_corners.h"
#include "center_edges.h"
#include "corners.h"
#include "fixed_edges.h"

struct cube333 {
	rubik_cube::Corners c;
	rubik_cube::Fixed_edges fe;
	rubik_cube::Center_corners<3> cc;

	cube333(): c(), fe(), cc(){}
	void disp_cube(std::ostream &os = std::cout);
	void apply_L();
	void apply_R();
	void apply_F();
	void apply_B();
	void apply_U();
	void apply_D();

	void apply_ML();
	void apply_MR();
	void apply_MF();
	void apply_MB();
	void apply_MU();
	void apply_MD();
};

void cube333::disp_cube(std::ostream &os) {
	Permutation<3> out;
	out = c.toPermutationN<3>(out);
	out = fe.toPermutationN<3>(out);
	out = cc.toPermutationN(out);
	out.disp_cube(os);

//	cc.toPermutationN();

#if 0
	os << "Corners:\n";
	c.disp_cube();
	os << "Edges:\n";
	fe.disp_cube();
	os << "-----------------\n";
	fe.toPermutationN(3);
	os << "-----------------\n";
	os << "Centers:\n";
	cc.disp_cube();
#endif
}

void cube333::apply_L() {
	c.apply_L();
	fe.apply_L();
}
void cube333::apply_R() {
	c.apply_R();
	fe.apply_R();
}
void cube333::apply_F() {
	c.apply_F();
	fe.apply_F();
}
void cube333::apply_B() {
	c.apply_B();
	fe.apply_B();
}
void cube333::apply_U() {
	c.apply_U();
	fe.apply_U();
}
void cube333::apply_D() {
	c.apply_D();
	fe.apply_D();
}

void cube333::apply_ML() {
	fe.apply_ML();
	cc.apply_ML<0>();
}

void cube333::apply_MR() {
	fe.apply_MR();
	cc.apply_MR<0>();
}

void cube333::apply_MF() {
	fe.apply_MF();
	cc.apply_MF<0>();
}

void cube333::apply_MB() {
	fe.apply_MB();
	cc.apply_MB<0>();
}

void cube333::apply_MU() {
	fe.apply_MU();
	cc.apply_MU<0>();
}

void cube333::apply_MD() {
	fe.apply_MD();
	cc.apply_MD<0>();
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

	stdcube.apply_ML();
	stdcube.c.disp();
	std::cout << "------------\n";
	stdcube.disp_cube();
}
