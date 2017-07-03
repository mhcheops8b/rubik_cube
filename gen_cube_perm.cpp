#include <iostream>
#include <iomanip>
#include <array>

const int N = 2;
const int N2 = N * N;

typedef std::array<int, 6 * N2> t_Arr;

inline int compute_idx(int face, int row, int col) {
	return	face * N2 + row * N + col;
}


void RotL_face(t_Arr &arr, int face) {
	for (int j = 0; j < N / 2; j++)
		for (int i = j; i < N - j - 1; i++)  {

			arr[compute_idx(face, j, i)] = 
			compute_idx(face, i, N - 1 - j);

			arr[compute_idx(face, i, N - 1 - j)] =
			compute_idx(face, N - 1 - j, N - 1 - i);

			arr[compute_idx(face, N - 1 - j, N - 1 - i)] =
			compute_idx(face, N - 1 - i, j);

			arr[compute_idx(face, N - 1 - i, j)] = 
			compute_idx(face, j, i);

#if DEBUG
			std::cout << "Cycle: (";
			std::cout << compute_idx(face, j, i) << ", " <<
				     compute_idx(face, i, N - 1 - j) << ", " <<
				compute_idx(face, N - 1 - j, N - 1 - i) << ", " <<
				compute_idx(face, N - 1 - i, j) << ")\n";
#endif
		}
}

void RotR_face(t_Arr &arr, int face) {
	for (int j = 0; j < N / 2; j++)
		for (int i = j; i < N - j - 1; i++)  {

			arr[compute_idx(face, j, i)] = 
			compute_idx(face, N - 1 - i, j);

			arr[compute_idx(face, N - 1 - i, j)] = 
			compute_idx(face, N - 1 - j, N - 1 - i);

			arr[compute_idx(face, N - 1 - j, N - 1 - i)] =
			compute_idx(face, i, N - 1 - j);

			arr[compute_idx(face, i, N - 1 - j)] =
			compute_idx(face, j, i);

			std::cout << "Cycle: (";
			std::cout << 
			compute_idx(face, j, i) << ", " <<
							     
			compute_idx(face, N - 1 - i, j) << ", " <<
							
			compute_idx(face, N - 1 - j, N - 1 - i) << ", " <<
							
			compute_idx(face, i, N - 1 - j) << ")\n";
		}
}

void RotL_band(t_Arr &arr, int col) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(0, i, col)] =
			compute_idx(2, i, col);
		arr[compute_idx(2, i, col)] =
			compute_idx(5, i, col);

		arr[compute_idx(5, i, col)] = 
			compute_idx(4, N - 1 - i, N - 1 - col);
			
		arr[compute_idx(4, N - 1 - i, N - 1 - col)] =
			compute_idx(0, i, col);
	}
}

void RotR_band(t_Arr &arr, int col) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(0, i, col)] =
			compute_idx(4, N - 1 - i, N - 1 - col);

		arr[compute_idx(4, N - 1 - i, N - 1 - col)] =
			compute_idx(5, i, col);


		arr[compute_idx(5, i, col)] = 
			compute_idx(2, i, col);

		arr[compute_idx(2, i, col)] =
			compute_idx(0, i, col);
	}
}

void RotF_band(t_Arr &arr, int row) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(0, row, i)] = 
			compute_idx(3, i, N - 1 - row);

		arr[compute_idx(3, i, N - 1 - row)] = 
			compute_idx(5, N - 1 - row, N - 1 - i);

		arr[compute_idx(5, N - 1 - row, N - 1 - i)] = 
			compute_idx(1, N - 1 - i, row);

		arr[compute_idx(1, N - 1 - i, row)] = 
			compute_idx(0, row, i);
	}

}

void RotB_band(t_Arr &arr, int row) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(0, row, i)] = 
			compute_idx(1, N - 1 - i, row);

		arr[compute_idx(1, N - 1 - i, row)] = 
			compute_idx(5, N - 1 - row, N - 1 - i);

		arr[compute_idx(5, N - 1 - row, N - 1 - i)] = 
			compute_idx(3, i, N - 1 - row);

		arr[compute_idx(3, i, N - 1 - row)] = 
			compute_idx(0, row, i);
	}

}


void RotU_band(t_Arr &arr, int row) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(1, row, i)] = 
			compute_idx(4, row, i);

		arr[compute_idx(4, row, i)] = 
			compute_idx(3, row, i);

		arr[compute_idx(3, row, i)] = 
			compute_idx(2, row, i);

		arr[compute_idx(2, row, i)] = 
			compute_idx(1, row, i);
	}

}

void RotD_band(t_Arr &arr, int row) {
	for (int i = 0; i < N; i++) {
		arr[compute_idx(1, row, i)] = 
			compute_idx(2, row, i);

		arr[compute_idx(2, row, i)] = 
			compute_idx(3, row, i);

		arr[compute_idx(3, row, i)] = 
			compute_idx(4, row, i);

		arr[compute_idx(4, row, i)] = 
			compute_idx(1, row, i);
	}

}

void init(t_Arr &arr) {
	for (int i = 0 ; i < 6 * N * N; i++)
		arr[i] = i;
}

void disp(t_Arr &arr) {
	for (int i = 0; i < 6 * N * N ; i++)
		std::cout << std::setw(3) << (arr[i]) << ",";
	std::cout << '\n';
}

template <int N>
void gen_cube_moves() {
	t_Arr myarr;	

	// _L move
	std::cout << "__L:\n";	
	init(myarr);
	RotL_face(myarr, 1);
	RotL_band(myarr, 0);
	disp(myarr);

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MLi move
			std::cout << "ML" << i + 1 << ":\n";	
			init(myarr);
			RotL_band(myarr, i + 1);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i < N / 2 ; i++) {
			// MLi move
			std::cout << "ML" << i << ":\n";	
			init(myarr);
			RotL_band(myarr, i);
			disp(myarr);
			
		}
	}

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MRi move
			std::cout << "MR" << i + 1 << ":\n";	
			init(myarr);
			RotR_band(myarr, N - 2 - i);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i < N /2 ; i++) {
			// MLi move
			std::cout << "MR" << i << ":\n";	
			init(myarr);
			RotR_band(myarr, N - 1 - i);
			disp(myarr);
			
		}
	}

	// _R move
	std::cout << "__R:\n";	
	init(myarr);
	RotL_face(myarr, 3);
	RotR_band(myarr, N - 1);
	disp(myarr);


	// _F move
	std::cout << "__F:\n";	
	init(myarr);
	RotL_face(myarr, 2);
	RotF_band(myarr, N - 1);
	disp(myarr);
	// checked

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MFi move
			std::cout << "MF" << i + 1 << ":\n";	
			init(myarr);
			RotF_band(myarr, N - 2 - i);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i < N /2 ; i++) {
			// MFi move
			std::cout << "MF" << i << ":\n";	
			init(myarr);
			RotF_band(myarr, N - 1 - i);
			disp(myarr);
			
		}
	}

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MBi move
			std::cout << "MB" << i + 1 << ":\n";	
			init(myarr);
			RotB_band(myarr, i + 1);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i <  N / 2 ; i++) {
			// MBi move
			std::cout << "MB" << i << ":\n";	
			init(myarr);
			RotB_band(myarr, i);
			disp(myarr);
			
		}
	}

	// B move
	std::cout << "__B:\n";	
	init(myarr);
	RotL_face(myarr, 4);
	RotB_band(myarr, 0);
	disp(myarr);

	// _U move
	std::cout << "__U:\n";	
	init(myarr);
	RotL_face(myarr, 0);
	RotU_band(myarr, 0);
	disp(myarr);

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MUi move
			std::cout << "MU" << i + 1 << ":\n";	
			init(myarr);
			RotU_band(myarr, i + 1);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i < N / 2 ; i++) {
			// MUi move
			std::cout << "MU" << i << ":\n";	
			init(myarr);
			RotU_band(myarr, i);
			disp(myarr);
			
		}
	}

	if (N % 2) { // N is odd

		for (int i = 0; i < (N - 1) / 2 ; i++) {
			// MDi move
			std::cout << "MD" << i + 1 << ":\n";	
			init(myarr);
			RotD_band(myarr, N - 2 - i);
			disp(myarr);
			
		}
	}
	else { // N is even
		for (int i = 1; i < N / 2 ; i++) {
			// MDi move
			std::cout << "MD" << i << ":\n";	
			init(myarr);
			RotD_band(myarr, N - 1 - i);
			disp(myarr);
			
		}
	}

	// _D move
	std::cout << "__D:\n";	
	init(myarr);
	RotL_face(myarr, 5);
	RotD_band(myarr, N - 1);
	disp(myarr);
	// checked
}

#if 0
template<>
void gen_cube_moves<6>() {
	t_Arr myarr;	

	// _L move
	std::cout << "__L:\n";	
	init(myarr);
	RotL_face(myarr, 1);
	RotL_band(myarr, 0);
	disp(myarr);

	// ML1 move
	std::cout << "ML1:\n";	
	init(myarr);
	RotL_band(myarr, 1);
	// checked
	disp(myarr);

	// ML2 move 
	std::cout << "ML2:\n";	
	init(myarr);
	RotL_band(myarr, 2);
	disp(myarr);
	// checked

	// MR2 move
	std::cout << "MR2:\n";	
	init(myarr);
	RotR_band(myarr, 3);
	disp(myarr);
	// checked

	// MR move
	std::cout << "MR1:\n";	
	init(myarr);
	RotR_band(myarr, 4);
	disp(myarr);
	// checked

	// _R move
	std::cout << "__R:\n";	
	init(myarr);
	RotL_face(myarr, 3);
	RotR_band(myarr, 5);
	disp(myarr);
	// checked

	// _F move
	std::cout << "__F:\n";	
	init(myarr);
	RotL_face(myarr, 2);
	RotF_band(myarr, 5);
	disp(myarr);
	// checked

	// MF move
	std::cout << "MF1:\n";	
	init(myarr);
	RotF_band(myarr, 4);
	disp(myarr);
	// checked

	// MF move
	std::cout << "MF2:\n";	
	init(myarr);
	RotF_band(myarr, 3);
	disp(myarr);


	std::cout << "MB2:\n";	
	init(myarr);
	RotB_band(myarr, 2);
	disp(myarr);


	// MB move
	std::cout << "MB1:\n";	
	init(myarr);
	RotB_band(myarr, 1);
	disp(myarr);

	// B move
	std::cout << "__B:\n";	
	init(myarr);
	RotL_face(myarr, 4);
	RotB_band(myarr, 0);
	disp(myarr);

	// _U move
	std::cout << "__U:\n";	
	init(myarr);
	RotL_face(myarr, 0);
	RotU_band(myarr, 0);
	disp(myarr);
	// checked

	// MU move
	std::cout << "MU1:\n";	
	init(myarr);
	RotU_band(myarr, 1);
	disp(myarr);
	// checked

	std::cout << "MU2:\n";	
	init(myarr);
	RotU_band(myarr, 2);
	disp(myarr);

	std::cout << "MD2:\n";	
	init(myarr);
	RotD_band(myarr, 3);
	disp(myarr);

	// MD move
	std::cout << "MD1:\n";	
	init(myarr);
	RotD_band(myarr, 4);
	disp(myarr);
	// checked

	// _D move
	std::cout << "__D:\n";	
	init(myarr);
	RotL_face(myarr, 5);
	RotD_band(myarr, 5);
	disp(myarr);
	// checked

}
#endif

int main() {

	gen_cube_moves<N>();
return 0;

	t_Arr myarr;	



// Cube 4 moves

	// _L move
	// RotL_face(myarr, 1);
	// RotL_band(myarr, 0);
	// checked

	// ML move
	// RotL_band(myarr, 1);
	// checked

	// MR move
	// RotR_band(myarr, 2);
	// checked

	// _R move
	// RotL_face(myarr, 3);
	// RotR_band(myarr, 3);
	// checked

	// _F move
	// RotF_band(myarr, 3);
	// RotL_face(myarr, 2);
	// checked

	// MF move
	// RotF_band(myarr, 2);
	// checked

	// MB move
	// RotB_band(myarr, 1);
	// checked

	// B move
	// RotL_face(myarr, 4);
	// RotB_band(myarr, 0);
	// checked

	// _U move
	// RotL_face(myarr, 0);
	// RotU_band(myarr, 0);
	// checked

	// MU move
	// RotU_band(myarr, 1);
	// checked

	// MD move
	// RotD_band(myarr, 2);
	// checked

	// _D move
	//RotL_face(myarr, 5);
	//RotD_band(myarr, 3);
	// checked

// end Cube 4 moves

	
//// Cube 5 moves
//
//	// _L move
//	std::cout << "__L:\n";	
//	init(myarr);
//	RotL_face(myarr, 1);
//	RotL_band(myarr, 0);
//	disp(myarr);
//
//	// ML1 move
//	std::cout << "ML1:\n";	
//	init(myarr);
//	RotL_band(myarr, 1);
//	// checked
//	disp(myarr);
//
//	// ML2 move = MR2' move
//	std::cout << "ML2:\n";	
//	init(myarr);
//	RotL_band(myarr, 2);
//	disp(myarr);
//	// checked
//
//	// MR2 move
//	std::cout << "MR2:\n";	
//	init(myarr);
//	RotR_band(myarr, 2);
//	disp(myarr);
//	// checked
//
//	// MR move
//	std::cout << "MR1:\n";	
//	init(myarr);
//	RotR_band(myarr, 3);
//	disp(myarr);
//	// checked
//
//	// _R move
//	std::cout << "__R:\n";	
//	init(myarr);
//	RotL_face(myarr, 3);
//	RotR_band(myarr, 4);
//	disp(myarr);
//	// checked
//
//	// _F move
//	std::cout << "__F:\n";	
//	init(myarr);
//	RotL_face(myarr, 2);
//	RotF_band(myarr, 4);
//	disp(myarr);
//	// checked
//
//	// MF move
//	std::cout << "MF1:\n";	
//	init(myarr);
//	RotF_band(myarr, 3);
//	disp(myarr);
//	// checked
//
//	// MF move
//	std::cout << "MF2:\n";	
//	init(myarr);
//	RotF_band(myarr, 2);
//	disp(myarr);
//
//
//	std::cout << "MB2:\n";	
//	init(myarr);
//	RotB_band(myarr, 2);
//	disp(myarr);
//
//
//	// MB move
//	std::cout << "MB1:\n";	
//	init(myarr);
//	RotB_band(myarr, 1);
//	disp(myarr);
//
//	// B move
//	std::cout << "__B:\n";	
//	init(myarr);
//	RotL_face(myarr, 4);
//	RotB_band(myarr, 0);
//	disp(myarr);
//
//	// _U move
//	std::cout << "__U:\n";	
//	init(myarr);
//	RotL_face(myarr, 0);
//	RotU_band(myarr, 0);
//	disp(myarr);
//	// checked
//
//	// MU move
//	std::cout << "MU1:\n";	
//	init(myarr);
//	RotU_band(myarr, 1);
//	disp(myarr);
//	// checked
//
//	std::cout << "MU2:\n";	
//	init(myarr);
//	RotU_band(myarr, 2);
//	disp(myarr);
//
//	std::cout << "MD2:\n";	
//	init(myarr);
//	RotD_band(myarr, 2);
//	disp(myarr);
//
//	// MD move
//	std::cout << "MD1:\n";	
//	init(myarr);
//	RotD_band(myarr, 3);
//	disp(myarr);
//	// checked
//
//	// _D move
//	std::cout << "__D:\n";	
//	init(myarr);
//	RotL_face(myarr, 5);
//	RotD_band(myarr, 4);
//	disp(myarr);
//	// checked
//
//// end Cube 5 moves

// Cube 6 moves

	// _L move
	std::cout << "__L:\n";	
	init(myarr);
	RotL_face(myarr, 1);
	RotL_band(myarr, 0);
	disp(myarr);

	// ML1 move
	std::cout << "ML1:\n";	
	init(myarr);
	RotL_band(myarr, 1);
	// checked
	disp(myarr);

	// ML2 move 
	std::cout << "ML2:\n";	
	init(myarr);
	RotL_band(myarr, 2);
	disp(myarr);
	// checked

	// MR2 move
	std::cout << "MR2:\n";	
	init(myarr);
	RotR_band(myarr, 3);
	disp(myarr);
	// checked

	// MR move
	std::cout << "MR1:\n";	
	init(myarr);
	RotR_band(myarr, 4);
	disp(myarr);
	// checked

	// _R move
	std::cout << "__R:\n";	
	init(myarr);
	RotL_face(myarr, 3);
	RotR_band(myarr, 5);
	disp(myarr);
	// checked

	// _F move
	std::cout << "__F:\n";	
	init(myarr);
	RotL_face(myarr, 2);
	RotF_band(myarr, 5);
	disp(myarr);
	// checked

	// MF move
	std::cout << "MF1:\n";	
	init(myarr);
	RotF_band(myarr, 4);
	disp(myarr);
	// checked

	// MF move
	std::cout << "MF2:\n";	
	init(myarr);
	RotF_band(myarr, 3);
	disp(myarr);


	std::cout << "MB2:\n";	
	init(myarr);
	RotB_band(myarr, 2);
	disp(myarr);


	// MB move
	std::cout << "MB1:\n";	
	init(myarr);
	RotB_band(myarr, 1);
	disp(myarr);

	// B move
	std::cout << "__B:\n";	
	init(myarr);
	RotL_face(myarr, 4);
	RotB_band(myarr, 0);
	disp(myarr);

	// _U move
	std::cout << "__U:\n";	
	init(myarr);
	RotL_face(myarr, 0);
	RotU_band(myarr, 0);
	disp(myarr);
	// checked

	// MU move
	std::cout << "MU1:\n";	
	init(myarr);
	RotU_band(myarr, 1);
	disp(myarr);
	// checked

	std::cout << "MU2:\n";	
	init(myarr);
	RotU_band(myarr, 2);
	disp(myarr);

	std::cout << "MD2:\n";	
	init(myarr);
	RotD_band(myarr, 3);
	disp(myarr);

	// MD move
	std::cout << "MD1:\n";	
	init(myarr);
	RotD_band(myarr, 4);
	disp(myarr);
	// checked

	// _D move
	std::cout << "__D:\n";	
	init(myarr);
	RotL_face(myarr, 5);
	RotD_band(myarr, 5);
	disp(myarr);
	// checked

// end Cube 6 moves


}

