/*
	----------------------------------------------
	| XX | 36 | 37 | 38 | 39 | 40 | 41 | 42 | XX |
	----------------------------------------------
	| 63 | XX | 16 | 17 | 18 | 19 | 20 | XX | 43 |
	----------------------------------------------
	| 62 | 35 | XX |  4 |  5 |  6 | XX | 21 | 44 |
	----------------------------------------------
	| 61 | 34 | 15 | XX |  0 | XX |  7 | 22 | 45 |
	----------------------------------------------
	| 60 | 33 | 14 |  3 | XX |  1 |  8 | 23 | 46 |
	----------------------------------------------
	| 59 | 32 | 13 | XX |  2 | XX |  9 | 24 | 47 |
	----------------------------------------------
	| 58 | 31 | XX | 12 | 11 | 10 | XX | 25 | 48 |
	----------------------------------------------
	| 57 | XX | 30 | 29 | 28 | 27 | 26 | XX | 49 |
	----------------------------------------------
	| XX | 56 | 55 | 54 | 53 | 52 | 51 | 50 | XX |
	----------------------------------------------

Face 
  - kth layer indices: 4(k-1)^2 -> 4(k-1)^2 + 4*(2k - 1) - 1

  Rot +: i -> (i + 2*k - 1) mod (2k)^2
  Rot -: i -> (i - 2*k + 1) mod (2k)^2

U idx -> (Rot -) L idx
L idx -> (Rot +) U idx

U idx -> F idx
U idx -> D idx

U idx -> (Rot +) R idx
R idx -> (Rot -) U idx

U idx -> (Rot 180) B idx
B idx -> (Rot 180) U idx

---
ML k: 
*/

#include <iostream>
#include <iomanip>
#include <ostream>
#include "faces.h"

template <int N>
constexpr int number_of_layers = (N - 3) / 2;

template <int N>
constexpr int number_of_indices = 24 * number_of_layers<N> * number_of_layers<N>;


template <int N>
struct center_edges_odd {
	int perm[number_of_indices<N>];

	center_edges_odd();
	//void disp(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);

	enum ce_faces {U = 0, L = 1, F = 2, R = 3, B = 4, D = 5};
};

template <int N>
center_edges_odd<N>::center_edges_odd() {
	for (int i = 0; i < number_of_indices<N>; i++)
		perm[i] = i;
}




constexpr int NO(int layer, int index) 
{ return 4 * (layer - 1) * (layer - 1) + index - 1; }
constexpr int EA(int layer, int index) 
{ return 4 * (layer - 1) * (layer - 1) +      2 * layer - 1  + index - 1; }
constexpr int SO(int layer, int index) 
{ return 4 * (layer - 1) * (layer - 1) + 2 * (2 * layer - 1) + index - 1; } 
constexpr int WE(int layer, int index) 
{ return 4 * (layer - 1) * (layer - 1) + 3 * (2 * layer - 1) + index - 1; }


template<int N>
constexpr int NF(enum center_edges_odd<N>::ce_faces f, int layer, int index) 
{ return f * 4 * number_of_layers<N>*number_of_layers<N> + NO(layer, index); }

template<int N>
constexpr int EF(enum center_edges_odd<N>::ce_faces f, int layer, int index) 
{ return f * 4 * number_of_layers<N>*number_of_layers<N> + EA(layer, index); }

template<int N>
constexpr int SF(enum center_edges_odd<N>::ce_faces f, int layer, int index) 
{ return f * 4 * number_of_layers<N>*number_of_layers<N> + SO(layer, index); }

template<int N>
constexpr int WF(enum center_edges_odd<N>::ce_faces f, int layer, int index) 
{ return f * 4 * number_of_layers<N>*number_of_layers<N> + WE(layer, index); }

template <int N>
void apply_cycle(center_edges_odd<N> &ce, int (&cycle)[4]) {

	int tmp = ce.perm[cycle[3]];
	for (int j = 2; j >= 0; j--)
		ce.perm[cycle[j + 1]] = ce.perm[cycle[j]];
	ce.perm[cycle[0]] = tmp;

}

template <int N>
void apply_cycle(center_edges_odd<N> &ce, int idx1, int idx2, int idx3, int idx4) {

	int tmp_array[]={idx1, idx2, idx3, idx4};

	apply_cycle<N>(ce, tmp_array);
}

template <int N>
void apply_cycle0(center_edges_odd<N> &ce, int idx1, int idx2, int idx3, int idx4) {

	int tmp = ce.perm[idx1];

	ce.perm[idx1] = ce.perm[idx4];
	ce.perm[idx4] = ce.perm[idx3];
	ce.perm[idx3] = ce.perm[idx2];
	ce.perm[idx2] = tmp;

}

template <int N>
void apply_Face(center_edges_odd<N> &ce, enum center_edges_odd<N>::ce_faces f) {
#ifdef MOVE_DEBUG
	const static char ce_face_titles[] ={'U', 'L', 'F', 'R', 'B', 'D'};
#endif
	for (int i = 0; i < number_of_layers<N>; i++) {
		for (int j = 0; j < 2*i + 1; j++) {
#ifdef MOVE_DEBUG
			std::cout << "   ";
			std::cout << ce_face_titles[f] << ">N(" << i + 1 << ", " << j + 1 << ") -> "
				  << ce_face_titles[f] << ">E(" << i + 1 << ", " << j + 1 << ") -> "
				  << ce_face_titles[f] << ">S(" << i + 1 << ", " << j + 1 << ") -> "
				  << ce_face_titles[f] << ">W(" << i + 1 << ", " << j + 1 << ")"
				  << "\n"; 		
		
			std::cout << "   ";
			std::cout << "(" 
				  << NF<N>(f, i + 1, j + 1) << ", "
				  << EF<N>(f, i + 1, j + 1) << ", "
				  << SF<N>(f, i + 1, j + 1) << ", "
				  << WF<N>(f, i + 1, j + 1) << ")"
				  << "\n"; 		
#endif

			apply_cycle(ce, 
				NF<N>(f, i + 1, j + 1), 
				EF<N>(f, i + 1, j + 1), 
				SF<N>(f, i + 1, j + 1), 
				WF<N>(f, i + 1, j + 1));
		}
	}	
}

template <int N>
void apply_U(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::U);
}

template <int N>
void apply_D(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::D);
}
template <int N>
void apply_L(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::L);
}
template <int N>
void apply_R(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::R);
}
template <int N>
void apply_F(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::F);
}
template <int N>
void apply_B(center_edges_odd<N> &ce) {
	apply_Face<N>(ce, center_edges_odd<N>::B);
}

template <int N, int K>
void apply_ML(center_edges_odd<N> &ce) {

	// U face cubes

	// West cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>W(" << K << ", " << (t + 1) << ") -> "
			  << "F>W(" << K << ", " << (t + 1) << ") -> "
			  << "D>W(" << K << ", " << (t + 1) << ") -> "
			  << "B>E(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << WF<N>(center_edges_odd<N>::U, K, t + 1) << ", "
			  << WF<N>(center_edges_odd<N>::F, K, t + 1) << ", "
			  << WF<N>(center_edges_odd<N>::D, K, t + 1) << ", "
			  << EF<N>(center_edges_odd<N>::B, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			WF<N>(center_edges_odd<N>::U, K, t + 1), 
			WF<N>(center_edges_odd<N>::F, K, t + 1), 
			WF<N>(center_edges_odd<N>::D, K, t + 1), 
			EF<N>(center_edges_odd<N>::B, K, t + 1));
	}

	// North cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>N(" << t << ", " << (t - K) << ") -> "
			  << "F>N(" << t << ", " << (t - K) << ") -> "
			  << "D>N(" << t << ", " << (t - K) << ") -> "
			  << "B>S(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << NF<N>(center_edges_odd<N>::U, t, t - K) << ", "
			  << NF<N>(center_edges_odd<N>::F, t, t - K) << ", "
			  << NF<N>(center_edges_odd<N>::D, t, t - K) << ", "
			  << SF<N>(center_edges_odd<N>::B, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  NF<N>(center_edges_odd<N>::U, t, t - K),
			  NF<N>(center_edges_odd<N>::F, t, t - K),
			  NF<N>(center_edges_odd<N>::D, t, t - K),
			  SF<N>(center_edges_odd<N>::B, t, t - K));
	}

	// South cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>S(" << t << ", " << (t + K) << ") -> "
			  << "F>S(" << t << ", " << (t + K) << ") -> "
			  << "D>S(" << t << ", " << (t + K) << ") -> "
			  << "B>N(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << SF<N>(center_edges_odd<N>::U, t, t + K) << ", "
			  << SF<N>(center_edges_odd<N>::F, t, t + K) << ", "
			  << SF<N>(center_edges_odd<N>::D, t, t + K) << ", "
			  << NF<N>(center_edges_odd<N>::B, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  SF<N>(center_edges_odd<N>::U, t, t + K),
			  SF<N>(center_edges_odd<N>::F, t, t + K),
			  SF<N>(center_edges_odd<N>::D, t, t + K),
			  NF<N>(center_edges_odd<N>::B, t, t + K));
	}

}

template <int N, int K>
void apply_MR(center_edges_odd<N> &ce) {

	// U face cubes

	// East cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>E(" << K << ", " << (t + 1) << ") -> "
			  << "B>W(" << K << ", " << (t + 1) << ") -> "
			  << "D>E(" << K << ", " << (t + 1) << ") -> "
			  << "F>E(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << EF<N>(center_edges_odd<N>::U, K, t + 1) << ", "
			  << WF<N>(center_edges_odd<N>::B, K, t + 1) << ", "
			  << EF<N>(center_edges_odd<N>::D, K, t + 1) << ", "
			  << EF<N>(center_edges_odd<N>::F, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  EF<N>(center_edges_odd<N>::U, K, t + 1),
			  WF<N>(center_edges_odd<N>::B, K, t + 1),
			  EF<N>(center_edges_odd<N>::D, K, t + 1),
			  EF<N>(center_edges_odd<N>::F, K, t + 1));
	}

	// North cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>N(" << t << ", " << (t - K) << ") -> "
			  << "B>S(" << t << ", " << (t - K) << ") -> "
			  << "D>N(" << t << ", " << (t - K) << ") -> "
			  << "F>S(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << NF<N>(center_edges_odd<N>::U, t, t - K) << ", "
			  << SF<N>(center_edges_odd<N>::B, t, t - K) << ", "
			  << NF<N>(center_edges_odd<N>::D, t, t - K) << ", "
			  << NF<N>(center_edges_odd<N>::F, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  NF<N>(center_edges_odd<N>::U, t, t - K),
			  SF<N>(center_edges_odd<N>::B, t, t - K),
			  NF<N>(center_edges_odd<N>::D, t, t - K),
			  NF<N>(center_edges_odd<N>::F, t, t - K));
	}

	// South cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "U>S(" << t << ", " << (t + K) << ") -> "
			  << "B>N(" << t << ", " << (t + K) << ") -> "
			  << "D>S(" << t << ", " << (t + K) << ") -> "
			  << "F>S(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << SF<N>(center_edges_odd<N>::U, t, t + K) << ", "
			  << NF<N>(center_edges_odd<N>::B, t, t + K) << ", "
			  << SF<N>(center_edges_odd<N>::D, t, t + K) << ", "
			  << SF<N>(center_edges_odd<N>::F, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  SF<N>(center_edges_odd<N>::U, t, t + K),
			  NF<N>(center_edges_odd<N>::B, t, t + K),
			  SF<N>(center_edges_odd<N>::D, t, t + K),
			  SF<N>(center_edges_odd<N>::F, t, t + K));
	}
}

template <int N>
void disp_face(center_edges_odd<N> &ce, enum center_edges_odd<N>::ce_faces f, std::ostream &os =std::cout) {

	for (int k = number_of_layers<N>; k >=0; k--) {

		for (int r = 0 ; r < number_of_layers<N> - k; r++) {
			os << ' ' << std::setw(3) << ce.perm[WF<N>(f, number_of_layers<N> - r, number_of_layers<N> + k - r)] << ' ';
		}

		os << " xxx ";

		for (int r = 0; r < 2 *k - 1; r++)
			os << ' ' << std::setw(3) << ce.perm[NF<N>(f, k, r + 1)] << ' ';

		if (k != 0)		
			os << " xxx ";

		for (int r = number_of_layers<N> - k ; r> 0; r--) {
			os << ' ' << std::setw(3) << ce.perm[EF<N>(f, number_of_layers<N> - r + 1, number_of_layers<N> - k - r + 1)] << ' ';
		}

		os << '\n';
	}

	for (int k = 1; k <= number_of_layers<N>; k++) {

		for (int r = 0 ; r < number_of_layers<N> - k; r++) {
			os << ' ' << std::setw(3) << ce.perm[WF<N>(f, number_of_layers<N> - r, number_of_layers<N> - k - r)] << ' ';
		}

		os << " xxx ";

		for (int r = 2 * k - 1; r > 0; r--)
			os << ' ' << std::setw(3) << ce.perm[SF<N>(f, k, r)] << ' ';

		os << " xxx ";

		for (int r = number_of_layers<N> - k ; r> 0; r--) {
			os << ' ' << std::setw(3) << ce.perm[EF<N>(f, number_of_layers<N> - r + 1, number_of_layers<N> + k - r + 1)] << ' ';
		}

		os << '\n';
	}
}

template <int N, int K>
void apply_MF(center_edges_odd<N> &ce) {

	// R face cubes

	// West cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "R>W(" << K << ", " << (t + 1) << ") -> "
			  << "D>N(" << K << ", " << (t + 1) << ") -> "
			  << "L>E(" << K << ", " << (t + 1) << ") -> "
			  << "U>S(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << WF<N>(center_edges_odd<N>::R, K, t + 1) << ", "
			  << NF<N>(center_edges_odd<N>::D, K, t + 1) << ", "
			  << EF<N>(center_edges_odd<N>::L, K, t + 1) << ", "
			  << SF<N>(center_edges_odd<N>::U, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			WF<N>(center_edges_odd<N>::R, K, t + 1), 
			NF<N>(center_edges_odd<N>::D, K, t + 1), 
			EF<N>(center_edges_odd<N>::L, K, t + 1), 
			SF<N>(center_edges_odd<N>::U, K, t + 1));
	}

	// North cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "R>N(" << t << ", " << (t - K) << ") -> "
			  << "D>E(" << t << ", " << (t - K) << ") -> "
			  << "L>S(" << t << ", " << (t - K) << ") -> "
			  << "U>W(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << NF<N>(center_edges_odd<N>::R, t, t - K) << ", "
			  << EF<N>(center_edges_odd<N>::D, t, t - K) << ", "
			  << SF<N>(center_edges_odd<N>::L, t, t - K) << ", "
			  << WF<N>(center_edges_odd<N>::U, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  NF<N>(center_edges_odd<N>::R, t, t - K),
			  EF<N>(center_edges_odd<N>::D, t, t - K),
			  SF<N>(center_edges_odd<N>::L, t, t - K),
			  WF<N>(center_edges_odd<N>::U, t, t - K));
	}

	// South cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "R>S(" << t << ", " << (t + K) << ") -> "
			  << "D>W(" << t << ", " << (t + K) << ") -> "
			  << "L>N(" << t << ", " << (t + K) << ") -> "
			  << "U>E(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << SF<N>(center_edges_odd<N>::R, t, t + K) << ", "
			  << WF<N>(center_edges_odd<N>::D, t, t + K) << ", "
			  << NF<N>(center_edges_odd<N>::L, t, t + K) << ", "
			  << EF<N>(center_edges_odd<N>::U, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  SF<N>(center_edges_odd<N>::R, t, t + K),
			  WF<N>(center_edges_odd<N>::D, t, t + K),
			  NF<N>(center_edges_odd<N>::L, t, t + K),
			  EF<N>(center_edges_odd<N>::U, t, t + K));
	}

}

template <int N, int K>
void apply_MB(center_edges_odd<N> &ce) {

	// L face cubes

	// West cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "L>W(" << K << ", " << (t + 1) << ") -> "
			  << "D>S(" << K << ", " << (t + 1) << ") -> "
			  << "R>E(" << K << ", " << (t + 1) << ") -> "
			  << "U>N(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << WF<N>(center_edges_odd<N>::L, K, t + 1) << ", "
			  << SF<N>(center_edges_odd<N>::D, K, t + 1) << ", "
			  << EF<N>(center_edges_odd<N>::R, K, t + 1) << ", "
			  << NF<N>(center_edges_odd<N>::U, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			WF<N>(center_edges_odd<N>::L, K, t + 1), 
			SF<N>(center_edges_odd<N>::D, K, t + 1), 
			EF<N>(center_edges_odd<N>::R, K, t + 1), 
			NF<N>(center_edges_odd<N>::U, K, t + 1));
	}

	// North cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "L>N(" << t << ", " << (t - K) << ") -> "
			  << "D>W(" << t << ", " << (t - K) << ") -> "
			  << "R>S(" << t << ", " << (t - K) << ") -> "
			  << "U>E(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << NF<N>(center_edges_odd<N>::L, t, t - K) << ", "
			  << WF<N>(center_edges_odd<N>::D, t, t - K) << ", "
			  << SF<N>(center_edges_odd<N>::R, t, t - K) << ", "
			  << EF<N>(center_edges_odd<N>::U, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  NF<N>(center_edges_odd<N>::L, t, t - K),
			  WF<N>(center_edges_odd<N>::D, t, t - K),
			  SF<N>(center_edges_odd<N>::R, t, t - K),
			  EF<N>(center_edges_odd<N>::U, t, t - K));
	}

	// South cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "L>S(" << t << ", " << (t + K) << ") -> "
			  << "D>E(" << t << ", " << (t + K) << ") -> "
			  << "R>N(" << t << ", " << (t + K) << ") -> "
			  << "U>W(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << SF<N>(center_edges_odd<N>::L, t, t + K) << ", "
			  << EF<N>(center_edges_odd<N>::D, t, t + K) << ", "
			  << NF<N>(center_edges_odd<N>::R, t, t + K) << ", "
			  << WF<N>(center_edges_odd<N>::U, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  SF<N>(center_edges_odd<N>::L, t, t + K),
			  EF<N>(center_edges_odd<N>::D, t, t + K),
			  NF<N>(center_edges_odd<N>::R, t, t + K),
			  WF<N>(center_edges_odd<N>::U, t, t + K));
	}

}

template <int N, int K>
void apply_MD(center_edges_odd<N> &ce) {

	// F face cubes

	// South cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>S(" << K << ", " << (t + 1) << ") -> "
			  << "R>S(" << K << ", " << (t + 1) << ") -> "
			  << "B>S(" << K << ", " << (t + 1) << ") -> "
			  << "L>S(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << SF<N>(center_edges_odd<N>::F, K, t + 1) << ", "
			  << SF<N>(center_edges_odd<N>::R, K, t + 1) << ", "
			  << SF<N>(center_edges_odd<N>::B, K, t + 1) << ", "
			  << SF<N>(center_edges_odd<N>::L, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			SF<N>(center_edges_odd<N>::F, K, t + 1), 
			SF<N>(center_edges_odd<N>::R, K, t + 1), 
			SF<N>(center_edges_odd<N>::B, K, t + 1), 
			SF<N>(center_edges_odd<N>::L, K, t + 1));
	}

	// West cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>W(" << t << ", " << (t - K) << ") -> "
			  << "R>W(" << t << ", " << (t - K) << ") -> "
			  << "B>W(" << t << ", " << (t - K) << ") -> "
			  << "L>W(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << WF<N>(center_edges_odd<N>::F, t, t - K) << ", "
			  << WF<N>(center_edges_odd<N>::R, t, t - K) << ", "
			  << WF<N>(center_edges_odd<N>::B, t, t - K) << ", "
			  << WF<N>(center_edges_odd<N>::L, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  WF<N>(center_edges_odd<N>::F, t, t - K),
			  WF<N>(center_edges_odd<N>::R, t, t - K),
			  WF<N>(center_edges_odd<N>::B, t, t - K),
			  WF<N>(center_edges_odd<N>::L, t, t - K));
	}

	// East cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>E(" << t << ", " << (t + K) << ") -> "
			  << "R>E(" << t << ", " << (t + K) << ") -> "
			  << "B>E(" << t << ", " << (t + K) << ") -> "
			  << "L>E(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << EF<N>(center_edges_odd<N>::F, t, t + K) << ", "
			  << EF<N>(center_edges_odd<N>::R, t, t + K) << ", "
			  << EF<N>(center_edges_odd<N>::B, t, t + K) << ", "
			  << EF<N>(center_edges_odd<N>::L, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  EF<N>(center_edges_odd<N>::F, t, t + K),
			  EF<N>(center_edges_odd<N>::R, t, t + K),
			  EF<N>(center_edges_odd<N>::B, t, t + K),
			  EF<N>(center_edges_odd<N>::L, t, t + K));
	}

}

template <int N, int K>
void apply_MU(center_edges_odd<N> &ce) {

	// F face cubes

	// North cubes 	
	for (int t = 0; t < 2 * K - 1; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>N(" << K << ", " << (t + 1) << ") -> "
			  << "L>N(" << K << ", " << (t + 1) << ") -> "
			  << "B>N(" << K << ", " << (t + 1) << ") -> "
			  << "R>N(" << K << ", " << (t + 1) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << NF<N>(center_edges_odd<N>::F, K, t + 1) << ", "
			  << NF<N>(center_edges_odd<N>::L, K, t + 1) << ", "
			  << NF<N>(center_edges_odd<N>::B, K, t + 1) << ", "
			  << NF<N>(center_edges_odd<N>::R, K, t + 1) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			NF<N>(center_edges_odd<N>::F, K, t + 1), 
			NF<N>(center_edges_odd<N>::L, K, t + 1), 
			NF<N>(center_edges_odd<N>::B, K, t + 1), 
			NF<N>(center_edges_odd<N>::R, K, t + 1));
	}

	// West cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>W(" << t << ", " << (t + K) << ") -> "
			  << "L>W(" << t << ", " << (t + K) << ") -> "
			  << "B>W(" << t << ", " << (t + K) << ") -> "
			  << "R>W(" << t << ", " << (t + K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << WF<N>(center_edges_odd<N>::F, t, t + K) << ", "
			  << WF<N>(center_edges_odd<N>::L, t, t + K) << ", "
			  << WF<N>(center_edges_odd<N>::B, t, t + K) << ", "
			  << WF<N>(center_edges_odd<N>::R, t, t + K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  WF<N>(center_edges_odd<N>::F, t, t + K),
			  WF<N>(center_edges_odd<N>::L, t, t + K),
			  WF<N>(center_edges_odd<N>::B, t, t + K),
			  WF<N>(center_edges_odd<N>::R, t, t + K));
	}

	// East cubes
	for (int t = K + 1; t <= number_of_layers<N>; t++) {
#ifdef MOVE_DEBUG
		std::cout << "   ";
		std::cout << "F>E(" << t << ", " << (t - K) << ") -> "
			  << "L>E(" << t << ", " << (t - K) << ") -> "
			  << "B>E(" << t << ", " << (t - K) << ") -> "
			  << "R>E(" << t << ", " << (t - K) << ")"
			  << "\n"; 		

		std::cout << "   ";
		std::cout << "(" 
			  << EF<N>(center_edges_odd<N>::F, t, t - K) << ", "
			  << EF<N>(center_edges_odd<N>::L, t, t - K) << ", "
			  << EF<N>(center_edges_odd<N>::B, t, t - K) << ", "
			  << EF<N>(center_edges_odd<N>::R, t, t - K) << ")"
			  << "\n"; 		
#endif

		apply_cycle(ce, 
			  EF<N>(center_edges_odd<N>::F, t, t - K),
			  EF<N>(center_edges_odd<N>::L, t, t - K),
			  EF<N>(center_edges_odd<N>::B, t, t - K),
			  EF<N>(center_edges_odd<N>::R, t, t - K));
	}

}

template <int N>
int signum(center_edges_odd<N> &ec) {
	int signum = 1;

	for (int i = 0; i < number_of_indices<N>; i++)
	for (int j = i + 1; j < number_of_indices<N>; j++)
		if (ec.perm[i] > ec.perm[j])
			signum*=-1;

	return signum;
	
}

template <int N>
void center_edges_odd<N>::disp_cube(std::ostream &os) {
	os << "U Face:\n";
	disp_face(*this, center_edges_odd<N>::U, os);
	os << "L Face:\n";
	disp_face(*this, center_edges_odd<N>::L, os);
	os << "F Face:\n";
	disp_face(*this, center_edges_odd<N>::F, os);
	os << "R Face:\n";
	disp_face(*this, center_edges_odd<N>::R, os);
	os << "B Face:\n";
	disp_face(*this, center_edges_odd<N>::B, os);
	os << "D Face:\n";
	disp_face(*this, center_edges_odd<N>::D, os);
}
