#include <iostream>
#include <iomanip>
#include <ostream>

struct center_corners_555 {
	// U: 1-4, L: 5-8, F: 9-12, R: 13-16, B: 17-20, D: 21-24
	// (idx - 1)

	// facewise
	// NW: 1, NE: 2, SE: 3, SW: 4
	int perm[24];

	center_corners_555();
	void disp(std::ostream &os = std::cout);
};

center_corners_555::center_corners_555() {
	for (int i = 0; i < 24; i++)
		perm[i] = i;
}
void center_corners_555::disp(std::ostream &os) {
	char labels[] = {'U', 'L', 'F', 'B', 'R', 'D'};
	for (int i = 0; i < 6;i++) {
		os << labels[i] << ": ";
		for (int j = 0; j < 4; j++) {
			os << std::setw(3) << perm[4*i+j];	
		}
		os << '\n';
	}
}

void apply_L(center_corners_555 &cc) {
// NW -> NE -> SE -> SW -> cycle
// (5 6 7 8)
// (idx - 1)

	int tmp = cc.perm[4];
	cc.perm[4] = cc.perm[7];
	cc.perm[7] = cc.perm[6];
	cc.perm[6] = cc.perm[5];
	cc.perm[5] = tmp;	
}


void apply_R(center_corners_555 &cc) {
// NW -> NE -> SE -> SW -> cycle
// (13 14 15 16)
// (idx - 1)

	int tmp = cc.perm[12];
	cc.perm[12] = cc.perm[15];
	cc.perm[15] = cc.perm[14];
	cc.perm[14] = cc.perm[13];
	cc.perm[13] = tmp;	
}

void apply_U(center_corners_555 &cc) {
// NW -> NE -> SE -> SW -> cycle
// (1  2  3  4)
// (idx - 1)

	int tmp = cc.perm[0];
	cc.perm[0] = cc.perm[3];
	cc.perm[3] = cc.perm[2];
	cc.perm[2] = cc.perm[1];
	cc.perm[1] = tmp;	
}

void apply_D(center_corners_555 &cc) {
// NW -> NE -> SE -> SW -> cycle
// (21  22  23  24)
// (idx - 1)

	int tmp = cc.perm[20];
	cc.perm[20] = cc.perm[23];
	cc.perm[23] = cc.perm[22];
	cc.perm[22] = cc.perm[21];
	cc.perm[21] = tmp;	
}

void apply_F(center_corners_555 &cc) {
// (9  10  11  12)
// (idx - 1)

	int tmp = cc.perm[8];
	cc.perm[8] = cc.perm[11];
	cc.perm[11] = cc.perm[10];
	cc.perm[10] = cc.perm[9];
	cc.perm[9] = tmp;	
}

void apply_B(center_corners_555 &cc) {
// (17  18  19  20)
// (idx - 1)

	int tmp = cc.perm[16];
	cc.perm[16] = cc.perm[19];
	cc.perm[19] = cc.perm[18];
	cc.perm[18] = cc.perm[17];
	cc.perm[17] = tmp;	
}


void apply_ML(center_corners_555 &cc) {
// (U-NW, F-NW, D-NW, B-SE)
// (U-SW, F-SW, D-SW, B-NE)

	int tmp = cc.perm[0];
	cc.perm[0] = cc.perm[18];
	cc.perm[18] = cc.perm[20];
	cc.perm[20] = cc.perm[8];
	cc.perm[8] = tmp;

	tmp = cc.perm[3];
	cc.perm[3] = cc.perm[17];
	cc.perm[17] = cc.perm[23];
	cc.perm[23] = cc.perm[11];
	cc.perm[11] = tmp;
}

void apply_MR(center_corners_555 &cc) {
// (U-NE, B-SW, D-NE, F-NE)
// (U-SE, B-NW, D-SE, F-SE)

	int tmp = cc.perm[1];
	cc.perm[1] = cc.perm[9];
	cc.perm[9] = cc.perm[21];
	cc.perm[21] = cc.perm[19];
	cc.perm[19] = tmp;

	tmp = cc.perm[2];
	cc.perm[2] = cc.perm[10];
	cc.perm[10] = cc.perm[22];
	cc.perm[22] = cc.perm[16];
	cc.perm[16] = tmp;
}

void apply_MU(center_corners_555 &cc) {
// (F-NW, L-NW, B-NW, R-NW)
// (F-NE, L-NE, B-NE, R-NE)

	int tmp = cc.perm[8];
	cc.perm[8] = cc.perm[12];
	cc.perm[12] = cc.perm[16];
	cc.perm[16] = cc.perm[4];
	cc.perm[4] = tmp;

	tmp = cc.perm[9];
	cc.perm[9] = cc.perm[13];
	cc.perm[13] = cc.perm[17];
	cc.perm[17] = cc.perm[5];
	cc.perm[5] = tmp;
}

void apply_MD(center_corners_555 &cc) {
// (F-SW, R-SW, B-SW, L-SW)
// (F-SE, R-SE, B-SE, L-SE)

	int tmp = cc.perm[11];
	cc.perm[11] = cc.perm[7];
	cc.perm[7] = cc.perm[19];
	cc.perm[19] = cc.perm[15];
	cc.perm[15] = tmp;

	tmp = cc.perm[10];
	cc.perm[10] = cc.perm[6];
	cc.perm[6] = cc.perm[18];
	cc.perm[18] = cc.perm[14];
	cc.perm[14] = tmp;
}

void apply_MF(center_corners_555 &cc) {
// (U-SW, R-NW, D-NE, L-SE)
// (U-SE, R-SW, D-NW, L-NE)

	int tmp = cc.perm[3];
	cc.perm[3] = cc.perm[6];
	cc.perm[6] = cc.perm[21];
	cc.perm[21] = cc.perm[12];
	cc.perm[12] = tmp;

	tmp = cc.perm[2];
	cc.perm[2] = cc.perm[5];
	cc.perm[5] = cc.perm[20];
	cc.perm[20] = cc.perm[15];
	cc.perm[15] = tmp;
}

void apply_MB(center_corners_555 &cc) {
// (U-NW, L-SW, D-SE, R-NE)
// (U-NE, L-NW, D-SW, R-SE)

	int tmp = cc.perm[0];
	cc.perm[0] = cc.perm[13];
	cc.perm[13] = cc.perm[22];
	cc.perm[22] = cc.perm[7];
	cc.perm[7] = tmp;

	tmp = cc.perm[1];
	cc.perm[1] = cc.perm[14];
	cc.perm[14] = cc.perm[23];
	cc.perm[23] = cc.perm[4];
	cc.perm[4] = tmp;
}


int signum(center_corners_555 &cc) {
	int signum = 1;
	for (int i = 0; i < 24; i++)
	for (int j = i + 1; j < 24; j++)
		if (cc.perm[i] > cc.perm[j])
			signum*=-1;

	return signum;
	
}



int main() {

	center_corners_555 new_cube;

	new_cube.disp();
	std::cout << "\t---\n";

	// MR2 R2 B2 U2 ML U2 MR' U2 MR U2 F2 MR F2 ML' B2 R2 MR2
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_ML(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_MR(new_cube);
	apply_U(new_cube);
	apply_U(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_MR(new_cube);
	apply_F(new_cube);
	apply_F(new_cube);
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_ML(new_cube);
	apply_B(new_cube);
	apply_B(new_cube);
	apply_R(new_cube);
	apply_R(new_cube);
	apply_MR(new_cube);
	apply_MR(new_cube);
	new_cube.disp();
	std::cout << "\t---\n";
	std::cout << "Sgn: " << signum(new_cube) << '\n';
	std::cout << "\t---\n";

	return 0;
}
