#include <iostream>
#include <iomanip>

#include "corners.h"
#include "center_corners.h"
#include "coupled_edges.h"

struct cube444 {
	rubik_cube::Corners c;
	rubik_cube::Coupled_edges e;
	rubik_cube::Center_corners<4> cc;

	cube444(): c(), e(), cc(){}
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

void cube444::disp_cube(std::ostream &os) {
	Permutation<4> out;
	out = c.toPermutationN<4>(out);
	out = e.toPermutationN<4>(out);
	out = cc.toPermutationN(out);
	out.disp_cube_fancy();
	//cc.toPermutationN();
}

void cube444::apply_L() {
	c.apply_L();
	e.apply_L();
}
void cube444::apply_R() {
	c.apply_R();
	e.apply_R();
}
void cube444::apply_F() {
	c.apply_F();
	e.apply_F();
}
void cube444::apply_B() {
	c.apply_B();
	e.apply_B();
}
void cube444::apply_U() {
	c.apply_U();
	e.apply_U();
}
void cube444::apply_D() {
	c.apply_D();
	e.apply_D();
}

void cube444::apply_ML() {
	e.apply_ML();
	cc.apply_ML<1>();
}

void cube444::apply_MR() {
	e.apply_MR();
	cc.apply_MR<1>();
}

void cube444::apply_MF() {
	e.apply_MF();
	cc.apply_MF<1>();
}

void cube444::apply_MB() {
	e.apply_MB();
	cc.apply_MB<1>();
}

void cube444::apply_MU() {
	e.apply_MU();
	cc.apply_MU<1>();
}

void cube444::apply_MD() {
	e.apply_MD();
	cc.apply_MD<1>();
}



int main() {
	cube444 std4cube;
	std4cube.c.disp();
	std::cout << "------------\n";
	std4cube.disp_cube();
	std::cout << "------------\n";

	std4cube.apply_ML();
	//std4cube.c.disp();
	std::cout << "------------\n";
	std4cube.disp_cube();
}
