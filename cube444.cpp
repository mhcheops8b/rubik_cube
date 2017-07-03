// Cube444.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "_cube444.h"

#if 0
struct Permutation96 {
	static const int _count = 96;
	int _components[96]; // 6 * 4 x 4
						 // computes composition of permutations *this and perm_b
	Permutation96();
	//Permutation96(Permutation96 _perm);
	Permutation96(const Permutation96 &_perm);
	Permutation96(const int init[Permutation96::_count]);
//	Permutation96 operator*(const Permutation96 &perm_b);
	Permutation96 inv();
	//static const Permutation96 _I;
	//static const Permutation96 _D;

	void disp_elem(std::ostream &os, int i);
	void disp_perm(std::ostream &os);
	void disp_cube(std::ostream &os);
	friend Permutation96 operator*(const Permutation96 &perm_a, const Permutation96 &perm_b);
	friend Permutation96 operator!(const Permutation96 &perm);

	bool isIdentity();
};

bool Permutation96::isIdentity() {
	for (int i = 0; i < _count; i++)
		if (_components[i] != i)
			return false;

	return true;
}

Permutation96 Permutation96::inv() {
	Permutation96 outcome;
	for (int i = 0; i < _count; i++)
		outcome._components[_components[i]] = i;
	return outcome;
}

Permutation96 operator!(const Permutation96 &perm) {
	Permutation96 outcome;
	for (int i = 0; i < Permutation96::_count; i++)
		outcome._components[perm._components[i]] = i;
	return outcome;
}

void Permutation96::disp_perm(std::ostream &os) {
	for (int i = 0; i < _count; i++)
		os << (_components[i] + 1) << ", ";
	os << '\n';
}

void Permutation96::disp_elem(std::ostream &os, int i) {
	os << (i / 16  + 1);
}
void Permutation96::disp_cube(std::ostream &os) {
	int inv[_count];
	for (int i = 0; i < _count; i++)
		inv[_components[i]] = i;
	
	for (int j = 0; j < 4; j++) {
		os << "    ";
		for (int i = 0 + 4 * j; i < 4 + 4* j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}
	
	for (int j = 0 ; j < 4; j++) {
		for (int i = 16 + 4*j; i < 20 + 4 * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 32 + 4 * j; i < 36 + 4 * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 48 + 4 * j; i < 52 + 4 * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 64 + 4 * j; i < 68 + 4 * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = 0; j < 4; j++) {
		os << "    ";
		for (int i = 80 + 4 * j; i < 84 + 4 * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = 3; j >= 0; j--) {
		os << "    ";
		for (int i = 67 + 4 * j; i >= 64 + 4 * j; i--)
			disp_elem(os, inv[i]);
		os << '\n';
	}
}

const int Arr_I[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
};

const int Arr_L[Permutation96::_count] = {
	32, 1, 2, 3,36, 5, 6, 7,40, 9,10,11,44,13,14,15,19,23,27,31,
	18,22,26,30,17,21,25,29,16,20,24,28,80,33,34,35,84,37,38,39,
	88,41,42,43,92,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,66,12,68,69,70, 8,72,73,74, 4,76,77,78, 0,
	79,81,82,83,75,85,86,87,71,89,90,91,67,93,94,95
};

const int ArrML[Permutation96::_count] = {
	0,33, 2, 3, 4,37, 6, 7, 8,41,10,11,12,45,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,30,31,32,81,34,35,36,85,38,39,
	40,89,42,43,44,93,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,13,67,68,69, 9,71,72,73, 5,75,76,77, 1,79,
	80,78,82,83,84,74,86,87,88,70,90,91,92,66,94,95
};

const int ArrMR[Permutation96::_count] = {
	0, 1,77, 3, 4, 5,73, 7, 8, 9,69,11,12,13,65,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,30,31,32,33, 2,35,36,37, 6,39,
	40,41,10,43,44,45,14,47,48,49,50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,94,66,67,68,90,70,71,72,86,74,75,76,82,78,79,
	80,81,34,83,84,85,38,87,88,89,42,91,92,93,46,95
};

const int Arr_R[Permutation96::_count] = {
	0, 1, 2,76, 4, 5, 6,72, 8, 9,10,68,12,13,14,64,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,30,31,32,33,34, 3,36,37,38, 7,
	40,41,42,11,44,45,46,15,51,55,59,63,50,54,58,62,49,53,57,61,
	48,52,56,60,95,65,66,67,91,69,70,71,87,73,74,75,83,77,78,79,
	80,81,82,35,84,85,86,39,88,89,90,43,92,93,94,47
};

const int Arr_F[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,48,52,56,60,16,17,18,15,
	20,21,22,14,24,25,26,13,28,29,30,12,35,39,43,47,34,38,42,46,
	33,37,41,45,32,36,40,44,83,49,50,51,82,53,54,55,81,57,58,59,
	80,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	19,23,27,31,84,85,86,87,88,89,90,91,92,93,94,95
};

const int ArrMF[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7,49,53,57,61,12,13,14,15,16,17,11,19,
	20,21,10,23,24,25, 9,27,28,29, 8,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,87,50,51,52,86,54,55,56,85,58,59,
	60,84,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,18,22,26,30,88,89,90,91,92,93,94,95
};

const int ArrMB[Permutation96::_count] = {
	0, 1, 2, 3,29,25,21,17, 8, 9,10,11,12,13,14,15,16,88,18,19,
	20,89,22,23,24,90,26,27,28,91,30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49, 4,51,52,53, 5,55,56,57, 6,59,
	60,61, 7,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,62,58,54,50,92,93,94,95
};

const int Arr_B[Permutation96::_count] = {
	28,24,20,16, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,92,17,18,19,
	93,21,22,23,94,25,26,27,95,29,30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49,50, 0,52,53,54, 1,56,57,58, 2,
	60,61,62, 3,67,71,75,79,66,70,74,78,65,69,73,77,64,68,72,76,
	80,81,82,83,84,85,86,87,88,89,90,91,63,59,55,51
};

const int Arr_U[Permutation96::_count] = {
	3, 7,11,15, 2, 6,10,14, 1, 5,  9,13, 0, 4, 8,12,64,65,66,67,
	20,21,22,23,24,25,26,27,28,29,30,31,16,17,18,19,36,37,38,39,
	40,41,42,43,44,45,46,47,32,33,34,35,52,53,54,55,56,57,58,59,
	60,61,62,63,48,49,50,51,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
};

const int ArrMU[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
	68,69,70,71,24,25,26,27,28,29,30,31,32,33,34,35,20,21,22,23,
	40,41,42,43,44,45,46,47,48,49,50,51,36,37,38,39,56,57,58,59,
	60,61,62,63,64,65,66,67,52,53,54,55,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
};

const int ArrMD[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,40,41,42,43,28,29,30,31,32,33,34,35,36,37,38,39,
	56,57,58,59,44,45,46,47,48,49,50,51,52,53,54,55,72,73,74,75,
	60,61,62,63,64,65,66,67,68,69,70,71,24,25,26,27,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
};

const int Arr_D[Permutation96::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,44,45,46,47,32,33,34,35,36,37,38,39,
	40,41,42,43,60,61,62,63,48,49,50,51,52,53,54,55,56,57,58,59,
	76,77,78,79,64,65,66,67,68,69,70,71,72,73,74,75,28,29,30,31,
	83,87,91,95,82,86,90,94,81,85,89,93,80,84,88,92
};

Permutation96::Permutation96() {
	for (int i = 0; i < _count; i++)
		_components[i] = i;
}

Permutation96::Permutation96(const Permutation96 &_perm) {
	for (int i = 0; i < _count; i++)
		_components[i] = _perm._components[i];
}

Permutation96::Permutation96(const int init[Permutation96::_count]) {
	for (int i = 0; i < _count; i++)
		_components[i] = init[i];
}

#if 0
Permutation96 Permutation96::operator*(const Permutation96 &perm_b) {
	// perm_b (*this)
	Permutation96 outcome;
	for (int i = 0; i < Permutation96::_count; i++) {
		outcome._components[i] = perm_b._components[_components[i]];
	}
	return outcome;
}
#endif

Permutation96 operator*(const Permutation96 &perm_a, const Permutation96 &perm_b) {
	// perm_b (*this)
	Permutation96 outcome;
	for (int i = 0; i < Permutation96::_count; i++) {
		outcome._components[i] = perm_b._components[perm_a._components[i]];
	}
	return outcome;
}
#endif

//
const Permutation<4> _I(arr_I_4);
const Permutation<4> _L(arr_L_4);
const Permutation<4> ML(arr_ML_4);
const Permutation<4> MR(arr_MR_4);
const Permutation<4> _R(arr_R_4);
const Permutation<4> _F(arr_F_4);
const Permutation<4> MF(arr_MF_4);
const Permutation<4> MB(arr_MB_4);
const Permutation<4> _B(arr_B_4);
const Permutation<4> _U(arr_U_4);
const Permutation<4> MU(arr_MU_4);
const Permutation<4> MD(arr_MD_4);
const Permutation<4> _D(arr_D_4);


#if 0
struct cube4 {
	static const int _count = 96;
	int _cube[96]; // 6 * 4 x 4

	void init();

};

bool isPermutation(const Permutation96 &perm) {
	bool flag[Permutation96::_count];
	for (int i = 0; i < Permutation96::_count; i++)
		flag[i] = false;
	
	for (int i = 0; i < Permutation96::_count; i++)
		flag[perm._components[i]] = true;

	bool has_false = false;

	for (int i = 0; i < Permutation96::_count; i++)
		if (!flag[i]) {
			has_false = true;
			std::cout << "Index: " << i << '\n';
			break;
		}
	return !has_false;
}


void cube4::init() {
	for (int i = 0; i < _count; i++)
		_cube[i] = i;
}

const Permutation96 c4_moves[] = {
	_L, !_L, ML, !ML, MR, !MR, _R, !_R, 
	_U, !_U, MU, !MU, MD, !MD, _D, !_D,
	_F, !_F, MF, !MF, MB, !MB, _B, !_B
};


void solve_rec(int cur_length, int *move_index, const int max_length, const Permutation96 &start_permutation) {

	if (cur_length == max_length) {
		// apply moves
		Permutation96 outcube = start_permutation;
		for (int i = 0; i < max_length; i++) {
			outcube = outcube * c4_moves[move_index[i]];
		}
		if (outcube.isIdentity()) {
			for (int i = 0; i < max_length; i++)
				std::cout << move_index[i] << " ";

			std::cout << '\n';

		}

	}
	else {
		for (int i = 0; i < 24; i++) {
			move_index[cur_length] = i;
			solve_rec(cur_length + 1, move_index, max_length, start_permutation);
		}
	}
}

#endif
int main() {

#if 0
	Permutation96 moves[] = {
		_L, !_L, ML, !ML, MR, !MR, _R, !_R, 
		_U, !_U, MU, !MU, MD, !MD, _D, !_D,
		_F, !_F, MF, !MF, MB, !MB, _B, !_B};
#endif

	//
	// MOVES:
	// _L,ML,MR,_R ; left, middle left, middle right, right
	// _F,MF,MB,_B ; front, middle front, middle back, back
	// _U,MU,MD,_D ; up, middle up, middle down, down


	// _L permutation:
	// 	(17 20 32 29) (18 24 31 25) (19 28 30 21) (22 23 27 26)
	// 	(33 81 80 1) (5 37 85 76) (9 41 89 72) (13 45 93 68)
	//std::cout << _L._components[0] << '\n';
	/*if (isPermutation(_D))
		std::cout << "OK" << '\n';
	else
		std::cout << "Problem!" << '\n';*/
	
	Permutation<4> cube;
	cube = cube * !_L;
	cube.disp_cube_fancy(std::cout);
	Permutation<4> outcube;
	Permutation<4> outcube2;
	Permutation<4> outcube3;
	Permutation<4> outcube4;

	//outcube = cube * MF * MD * MF.inv() * MD.inv()*_U.inv()*MD*MF*MD.inv() *MF.inv()*_U;
	//outcube = cube * MF * MD * !MF * !MD * !_U * MD * MF * !MD * !MF * _U;
//	outcube2 = cube * ML.inv() * _L * _U.inv() * _L.inv() * _U * ML * _U.inv() * _L * _U *_L.inv();

//	outcube3 = cube * _F * _D * _F.inv() * _D.inv() * _U.inv() * _D * _F * _D.inv() * _F.inv() * _U;
//	outcube4 = outcube3 * outcube3;
	//uu.disp_perm(std::cout);
	
	//ML.disp_cube(std::cout);
	//test.disp_perm(std::cout);
	//test.disp_cube(std::cout);
	//uu.disp_cube(std::cout);
	//outcube.disp_cube(std::cout);
//	outcube  = outcube * !_F * _U * _B * !_U * _F * _U * !_B * !_U;
	//outcube = _F * _D * !_F * !_D * _F * _D * !_F * !_D * _U * _D * _F * !_D * !_F * _D * _F * !_D * !_F * !_U;
	
//	outcube = _F * _F * !MR * _F * _F * MR * MR * _F * _F * MR * _F * _F;
//	outcube = _U * _U * !MB * !MU * MD * MB * _U * _U * !MB * _U * !MD * MB;

//	outcube = MR * MR * _B * _B * _D * _D * !ML * _D * _D * MR * _D * _D * !MR * _D * _D * _F * _F * !MR * _F * _F * ML * _B * _B * MR * MR;

	outcube = _R * _R * MR * MR * _B * _B * _U * _U * ML * _U * _U * !MR * _U * _U * MR * _U * _U * _F * _F * MR * _F * _F * !ML * _B * _B * MR * MR * _R * _R;
	outcube.disp_perm(std::cout);
	outcube.disp_cube(std::cout);

#if 0
	outcube2 = outcube * outcube;

	outcube2.disp_perm(std::cout);
	outcube2.disp_cube(std::cout);

	outcube3 = outcube2 * outcube;

	outcube3.disp_perm(std::cout);
	outcube3.disp_cube(std::cout);
#endif

#if 0
	Permutation96 perm1 = _I;
	int move_index[50];

	perm1._components[45] = 81; perm1._components[46] = 82; perm1._components[81] = 45; perm1._components[82] = 46;

	solve_rec(0, move_index, 7, perm1);
#endif

#if 0
	outcube2.disp_perm(std::cout);
	outcube2.disp_cube(std::cout);
	
//	outcube3.disp_perm(std::cout);
//	outcube3.disp_perm(std::cout);

	outcube4.disp_cube(std::cout);
	outcube4.disp_cube(std::cout);
#endif	

#if 0
	srand(time(NULL));
	Permutation96 shuffleCube;
	for (int i = 0; i < 32; i++) {

		int move = rand() % 24;

		shuffleCube = shuffleCube * moves[move];
	}
	shuffleCube.disp_cube(std::cout);
	shuffleCube.disp_perm(std::cout);
#endif

	return 0;

}



