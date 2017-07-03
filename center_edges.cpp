#include <iostream>
#include <iomanip>
#include <ostream>

struct center_edges_555 {
	// U: 1-4, L: 5-8, F: 9-12, R: 13-16, B: 17-20, D: 21-24
	// (idx - 1)

	// facewise
	// N: 1, E: 2, S: 3, W: 4
	int perm[24];

	center_edges_555();
	void disp(std::ostream &os = std::cout);
};

center_edges_555::center_edges_555() {
	for (int i = 0; i < 24; i++)
		perm[i] = i;
}
void center_edges_555::disp(std::ostream &os) {
	char labels[] = {'U', 'L', 'F', 'B', 'R', 'D'};
	for (int i = 0; i < 6;i++) {
		std::cout << labels[i] << ": ";
		for (int j = 0; j < 4; j++) {
			std::cout << std::setw(3) << perm[4*i+j];	
		}
		std::cout << '\n';
	}
}

void apply_L(center_edges_555 &ce) {
// (5 6 7 8)
// (idx - 1)

	int tmp = ce.perm[4];
	ce.perm[4] = ce.perm[7];
	ce.perm[7] = ce.perm[6];
	ce.perm[6] = ce.perm[5];
	ce.perm[5] = tmp;	
}

void apply_R(center_edges_555 &ce) {
// (13 14 15 16)
// (idx - 1)

	int tmp = ce.perm[12];
	ce.perm[12] = ce.perm[15];
	ce.perm[15] = ce.perm[14];
	ce.perm[14] = ce.perm[13];
	ce.perm[13] = tmp;	
}

void apply_U(center_edges_555 &ce) {
// (1  2  3  4)
// (idx - 1)

	int tmp = ce.perm[0];
	ce.perm[0] = ce.perm[3];
	ce.perm[3] = ce.perm[2];
	ce.perm[2] = ce.perm[1];
	ce.perm[1] = tmp;	
}

void apply_D(center_edges_555 &ce) {
// (21  22  23  24)
// (idx - 1)

	int tmp = ce.perm[20];
	ce.perm[20] = ce.perm[23];
	ce.perm[23] = ce.perm[22];
	ce.perm[22] = ce.perm[21];
	ce.perm[21] = tmp;	
}

void apply_F(center_edges_555 &ce) {
// (9  10  11  12)
// (idx - 1)

	int tmp = ce.perm[8];
	ce.perm[8] = ce.perm[11];
	ce.perm[11] = ce.perm[10];
	ce.perm[10] = ce.perm[9];
	ce.perm[9] = tmp;	
}

void apply_B(center_edges_555 &ce) {
// (17  18  19  20)
// (idx - 1)

	int tmp = ce.perm[16];
	ce.perm[16] = ce.perm[19];
	ce.perm[19] = ce.perm[18];
	ce.perm[18] = ce.perm[17];
	ce.perm[17] = tmp;	
}

void apply_ML(center_edges_555 &ce) {
// (UW -> FW -> DW -> BE)

	int tmp = ce.perm[3];
	ce.perm[3] = ce.perm[17];
	ce.perm[17] = ce.perm[23];
	ce.perm[23] = ce.perm[11];
	ce.perm[11] = tmp;
}

void apply_MR(center_edges_555 &ce) {
// (UE -> BW -> DE -> FE)

	int tmp = ce.perm[1];
	ce.perm[1] = ce.perm[9];
	ce.perm[9] = ce.perm[21];
	ce.perm[21] = ce.perm[19];
	ce.perm[19] = tmp;
}

void apply_MU(center_edges_555 &ce) {
// (FN -> LN -> BN -> RN)

	int tmp = ce.perm[8];
	ce.perm[8] = ce.perm[12];
	ce.perm[12] = ce.perm[16];
	ce.perm[16] = ce.perm[4];
	ce.perm[4] = tmp;
}

void apply_MD(center_edges_555 &ce) {
// (FS -> RS -> BS -> LS)

	int tmp = ce.perm[10];
	ce.perm[10] = ce.perm[6];
	ce.perm[6] = ce.perm[18];
	ce.perm[18] = ce.perm[14];
	ce.perm[14] = tmp;
}

void apply_MF(center_edges_555 &ce) {
// (US -> RW -> DN -> LE)

	int tmp = ce.perm[2];
	ce.perm[2] = ce.perm[5];
	ce.perm[5] = ce.perm[20];
	ce.perm[20] = ce.perm[15];
	ce.perm[15] = tmp;
}

void apply_MB(center_edges_555 &ce) {
// (UN -> LW -> DS -> RE)

	int tmp = ce.perm[0];
	ce.perm[0] = ce.perm[13];
	ce.perm[13] = ce.perm[22];
	ce.perm[22] = ce.perm[7];
	ce.perm[7] = tmp;
}
int signum(center_edges_555 &ec) {
	int signum = 1;
	for (int i = 0; i < 24; i++)
	for (int j = i + 1; j < 24; j++)
		if (ec.perm[i] > ec.perm[j])
			signum*=-1;

	return signum;
	
}


int main() {
	center_edges_555 new_cube;

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
