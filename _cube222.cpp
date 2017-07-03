#include "cubeNNN.h"

const int arr_I_2[Permutation<2>::_count] = {
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
};

const int arr_L_2[Permutation<2>::_count] = {
  8,  1, 10,  3,  5,  7,  4,  6, 20,  9, 22, 11, 12, 13, 14, 15, 16,  2, 18,  0, 19, 21, 17, 23
};

const int arr_R_2[Permutation<2>::_count] = {
  0, 18,  2, 16,  4,  5,  6,  7,  8,  1, 10,  3, 13, 15, 12, 14, 23, 17, 21, 19, 20,  9, 22, 11
};

const int arr_F_2[Permutation<2>::_count] = {
  0,  1, 12, 14,  4,  3,  6,  2,  9, 11,  8, 10, 21, 13, 20, 15, 16, 17, 18, 19,  5,  7, 22, 23
};

const int arr_B_2[Permutation<2>::_count] = {
  6,  4,  2,  3, 22,  5, 23,  7,  8,  9, 10, 11, 12,  0, 14,  1, 17, 19, 16, 18, 20, 21, 15, 13
};

const int arr_U_2[Permutation<2>::_count] = {
  1,  3,  0,  2, 16, 17,  6,  7,  4,  5, 10, 11,  8,  9, 14, 15, 12, 13, 18, 19, 20, 21, 22, 23
};

const int arr_D_2[Permutation<2>::_count] = {
  0,  1,  2,  3,  4,  5, 10, 11,  8,  9, 14, 15, 12, 13, 18, 19, 16, 17,  6,  7, 21, 23, 20, 22
};

const Permutation<2> I_2(arr_I_2);
const Permutation<2> L_2(arr_L_2);
const Permutation<2> R_2(arr_R_2);
const Permutation<2> F_2(arr_F_2);
const Permutation<2> B_2(arr_B_2);
const Permutation<2> U_2(arr_U_2);
const Permutation<2> D_2(arr_D_2);

// U towards B
template<>
void orient_x<2>(Permutation<2> &cu) {
	cu = cu * R_2 * !L_2;
}

// U towards F
template<>
void orient_x_prime<2>(Permutation<2> &cu) {
	cu = cu * !R_2 * L_2;
}

// F towards L
template<>
void orient_y<2>(Permutation<2> &cu) {
	cu = cu * U_2 * !D_2;
}

// F towards R
template<>
void orient_y_prime<2>(Permutation<2> &cu) {
	cu = cu * !U_2 * D_2;
}

// U towards R
template<>
void orient_z<2>(Permutation<2> &cu) {
	cu = cu * F_2 * !B_2;
}

// U towards R
template<>
void orient_z_prime<2>(Permutation<2> &cu) {
	cu = cu * !F_2 * B_2;
}
