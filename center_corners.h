#include "faces.h"

// N >= 5
// number of ks = (N-3)/2
template <int N>
constexpr int number_of_layers=(N % 2 == 1 ? (N-3)/2: (N-2)/2);

template <int N>
class Center_corners {

public:
	Center_corners();
	void init();
	void disp(std::ostream &os = std::cout);

	void disp_cube(std::ostream &os = std::cout);

	template <int U>
	friend void apply_face(Center_corners<U> &cc, const enum faces &face); 

	template <int U>
	friend void apply_L(Center_corners<U> &cc); 

	template <int U>
	friend void apply_R(Center_corners<U> &cc); 

	template <int U>
	friend void apply_U(Center_corners<U> &cc); 

	template <int U>
	friend void apply_D(Center_corners<U> &cc); 

	template <int U>
	friend void apply_F(Center_corners<U> &cc);

	template <int U>
	friend void apply_B(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_ML(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_MR(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_MU(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_MD(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_MF(Center_corners<U> &cc);

	template <int U, int K>
	friend void apply_MB(Center_corners<U> &cc); 

	template <int U>
	friend int signum(Center_corners<U> &cc);
	
private:
	// U: 1-4, L: 5-8, F: 9-12, R: 13-16, B: 17-20, D: 21-24
	// (idx - 1)

	// facewise
	// NW: 1, NE: 2, SE: 3, SW: 4
	// layer>=1
	// For layer == 0 (odd cube) it is center
	int perm[N % 2 ? number_of_layers<N> + 1 : number_of_layers<N>][24];

};

template <int N>
void Center_corners<N>::init() {
	if (N % 2) {
		for (int i = 0; i < 6; i++)
			perm[0][4 * i] = 4 * i;

		for (int k = 1; k <= number_of_layers<N>; k++)
			for (int i = 0; i < 24; i++)
				perm[k][i] = i;
	}
	else {
		for (int k = 0; k < number_of_layers<N>; k++)
			for (int i = 0; i < 24; i++)
				perm[k][i] = i;
	}
}

template <int N>
Center_corners<N>::Center_corners() {
	init();
	/*for (int k = 0; k < number_of_layers<N>; k++)
	for (int i = 0; i < 24; i++)
		perm[k][i] = i;*/
}


template <int N>
void Center_corners<N>::disp(std::ostream &os) {
	static char labels[] = {'U', 'L', 'F', 'B', 'R', 'D'};
	for (int k = 0; k < number_of_layers<N>; k++) {
		std::cout << "Layer " << k + 1 << ":\n";
		for (int i = 0; i < 6;i++) {
			std::cout << '\t' << labels[i] << ": ";
			for (int j = 0; j < 4; j++) {
				std::cout << std::setw(3) << perm[k][4*i+j];	
			}
			std::cout << '\n';
		}
	}
}

//			  U,L,F, R, B, D
//static int face_idxs[] = {0,4,8,12,16,20};
//enum faces {U = 0, L = 4, F = 8, R = 12, B = 16, D = 20};
enum corners {NW = 0, NE = 1, SE = 2, SW = 3};
inline constexpr int get_index(faces f, corners c) { return 4 * f + c; }
const char labels[] = {'U', 'L', 'F', 'R', 'B', 'D'};

template <int N>
void Center_corners<N>::disp_cube(std::ostream &os) {
	if (N % 2) {

		// odd
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = number_of_layers<N>; k >=0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ (perm[k][4 * U]) / 4];
			else {
				os << labels[ (perm[k][NW]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][NE]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}

		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][SW]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][SE]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
	//
		for (int i = 0; i <= N; i++)
			os << ' ';
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';
	//
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

	//
		for (int k = number_of_layers<N>; k >=0; k--) {
	//
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ perm[k][4 * L] / 4 ];
			else {
				os << labels[ (perm[k][get_index(L, NW)]) / 4 ];
					;
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][get_index(L, NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ perm[k][4 * F] / 4 ];
			else {
				os << labels[ (perm[k][get_index(F, NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][get_index(F, NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ perm[k][4 * R] / 4 ];
			else {
				os << labels[ (perm[k][get_index(R, NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][get_index(R, NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ perm[k][4 * B] / 4 ];
			else {
				os << labels[ (perm[k][get_index(B, NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][get_index(B, NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << '\n';
		}

		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][get_index(L, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][get_index(L, SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][get_index(F, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][get_index(F, SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][get_index(R, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][get_index(R, SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][get_index(B, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][get_index(B, SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << '\n';
		}
		
	//
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';


	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = number_of_layers<N>; k >=0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << labels[ perm[k][4 * D] / 4 ];
			else {
				os << labels[ (perm[k][get_index(D, NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << labels[ (perm[k][get_index(D, NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}

		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << labels[ (perm[k][get_index(D, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << labels[ (perm[k][get_index(D, SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
	//
		for (int i = 0; i <= N; i++)
			os << ' ';
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';
	}
	else {
		// even
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = number_of_layers<N>; k > 0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][NW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][NE]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][SW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][SE]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

	//
		for (int k = 0 ; k < 3; k++) {
		
			for (int i = 0; i < N; i++)
				os << '.';
			
			os << ' ';
		}
		for (int i = 0; i < N; i++)
				os << '.';
		os << '\n';

		for (int k = number_of_layers<N>; k > 0; k--) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(L, NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(L, NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(F, NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(F, NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(R, NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(R, NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(B, NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(B, NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';
			os << '\n';
		}
		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(L, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(L, SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(F, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(F, SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(R, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(R, SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(B, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(B, SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << '\n';
		}
	//
		for (int k = 0 ; k < 3; k++) {
		
			for (int i = 0; i < N; i++)
				os << '.';
			
			os << ' ';
		}
		for (int i = 0; i < N; i++)
				os << '.';
		os << '\n';

	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = number_of_layers<N>; k > 0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(D, NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(D, NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
		for (int k = 1; k <= number_of_layers<N>; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << labels[ (perm[k - 1][get_index(D, SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << labels[ (perm[k - 1][get_index(D, SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';


	}


}



template <int N>
void apply_face(Center_corners<N> &cc, const enum faces &face) {

	for (int k = 1; k <= number_of_layers<N>; k++) {

		int tmp = cc.perm[k][4 * face];

		cc.perm[k][4 * face] = cc.perm[k][4 * face + 3];
		cc.perm[k][4 * face + 3] = cc.perm[k][4 * face + 2];
		cc.perm[k][4 * face + 2] = cc.perm[k][4 * face + 1];
		cc.perm[k][4 * face + 1] = tmp;	
	}
}

template <int N>
void apply_L(Center_corners<N> &cc) {
	apply_face<N>(cc, L);
}

template <int N>
void apply_R(Center_corners<N> &cc) {
	apply_face<N>(cc, R);
}

template <int N>
void apply_U(Center_corners<N> &cc) {
	apply_face<N>(cc, U);
}

template <int N>
void apply_D(Center_corners<N> &cc) {
	apply_face<N>(cc, D);
}

template <int N>
void apply_F(Center_corners<N> &cc) {
	apply_face<N>(cc, F);
}

template <int N>
void apply_B(Center_corners<N> &cc) {
	apply_face<N>(cc, B);
}


// first layer is 0 for odd 1 for even
template <int N, int K>
void apply_ML(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");
//	static_assert(K > 0, "K must be greater than 0");
// (U-NW, F-NW, D-NW, B-SE)
// (U-SW, F-SW, D-SW, B-NE)
	constexpr int IDX = (N % 2 ? K : K - 1);

	if (K == 0) {
		if (N % 2) {
			// centers
			// (U F D B)
			int tmp = cc.perm[K][4 * U];
			
			cc.perm[K][4 * U] = cc.perm[K][4 * B];
			cc.perm[K][4 * B] = cc.perm[K][4 * D];
			cc.perm[K][4 * D] = cc.perm[K][4 * F];
			cc.perm[K][4 * F] = tmp;
		}
		else {
			std::cerr << "No action taken, for N = " << N << " value K = " << K << " is not allowed.\n";
		}
		
	}
	else {

		int tmp = cc.perm[IDX][get_index(U, NW)];
		cc.perm[IDX][get_index(U, NW)] = cc.perm[IDX][get_index(B, SE)];
		cc.perm[IDX][get_index(B, SE)] = cc.perm[IDX][get_index(D, NW)];
		cc.perm[IDX][get_index(D, NW)] = cc.perm[IDX][get_index(F, NW)];
		cc.perm[IDX][get_index(F, NW)] = tmp;

		tmp = cc.perm[IDX][get_index(U, SW)];
		cc.perm[IDX][get_index(U, SW)] = cc.perm[IDX][get_index(B, NE)];
		cc.perm[IDX][get_index(B, NE)] = cc.perm[IDX][get_index(D, SW)];
		cc.perm[IDX][get_index(D, SW)] = cc.perm[IDX][get_index(F, SW)];
		cc.perm[IDX][get_index(F, SW) ] = tmp;
	}
}

template <int N, int K>
void apply_MR(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");
// (U-NE, B-SW, D-NE, F-NE)
// (U-SE, B-NW, D-SE, F-SE)

	constexpr int IDX=(N % 2 ? K : K - 1);

	if (K == 0) {
		// centers
		static_assert(N % 2, "N must be odd in order to use K = 0");
		// (U B D F)
		int tmp = cc.perm[K][4 * U];
		
		cc.perm[K][4 * U] = cc.perm[K][4 * F];
		cc.perm[K][4 * F] = cc.perm[K][4 * D];
		cc.perm[K][4 * D] = cc.perm[K][4 * B];
		cc.perm[K][4 * B] = tmp;
		
	}
	else {

		int tmp = cc.perm[IDX][get_index(U, NE)];
		cc.perm[IDX][get_index(U, NE)] = cc.perm[IDX][get_index(F, NE)];
		cc.perm[IDX][get_index(F, NE)] = cc.perm[IDX][get_index(D, NE)];
		cc.perm[IDX][get_index(D, NE)] = cc.perm[IDX][get_index(B, SW)];
		cc.perm[IDX][get_index(B, SW)] = tmp;

		tmp = cc.perm[IDX][get_index(U, SE)];
		cc.perm[IDX][get_index(U, SE)] = cc.perm[IDX][get_index(F, SE)];
		cc.perm[IDX][get_index(F, SE)] = cc.perm[IDX][get_index(D, SE)];
		cc.perm[IDX][get_index(D, SE)] = cc.perm[IDX][get_index(B, NW)];
		cc.perm[IDX][get_index(B, NW) ] = tmp;
	}
}

template <int N, int K>
void apply_MU(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");
	// (F-NW, L-NW, B-NW, R-NW)
	// (F-NE, L-NE, B-NE, R-NE)

	constexpr int IDX=(N % 2 ? K : K - 1);

	if (K == 0) {
		// centers
		static_assert(N % 2, "N must be odd in order to use K = 0");
		// (F L B R)
		int tmp = cc.perm[K][4 * F];
		
		cc.perm[K][4 * F] = cc.perm[K][4 * R];
		cc.perm[K][4 * R] = cc.perm[K][4 * B];
		cc.perm[K][4 * B] = cc.perm[K][4 * L];
		cc.perm[K][4 * L] = tmp;
		
	}
	else {
		int tmp = cc.perm[IDX][get_index(F, NW)];
		cc.perm[IDX][get_index(F, NW)] = cc.perm[IDX][get_index(R, NW)];
		cc.perm[IDX][get_index(R, NW)] = cc.perm[IDX][get_index(B, NW)];
		cc.perm[IDX][get_index(B, NW)] = cc.perm[IDX][get_index(L, NW)];
		cc.perm[IDX][get_index(L, NW)] = tmp;

		tmp = cc.perm[IDX][get_index(F, NE)];
		cc.perm[IDX][get_index(F, NE)] = cc.perm[IDX][get_index(R, NE)];
		cc.perm[IDX][get_index(R, NE)] = cc.perm[IDX][get_index(B, NE)];
		cc.perm[IDX][get_index(B, NE)] = cc.perm[IDX][get_index(L, NE)];
		cc.perm[IDX][get_index(L, NE)] = tmp;
	}
}

template <int N, int K>
void apply_MD(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");

	// (F-SW, R-SW, B-SW, L-SW)
	// (F-SE, R-SE, B-SE, L-SE)

	constexpr int IDX=(N % 2 ? K : K - 1);

	if (K == 0) {
		// centers
		static_assert(N % 2, "N must be odd in order to use K = 0");
		// (F R B L)
		int tmp = cc.perm[K][4 * F];
		
		cc.perm[K][4 * F] = cc.perm[K][4 * L];
		cc.perm[K][4 * L] = cc.perm[K][4 * B];
		cc.perm[K][4 * B] = cc.perm[K][4 * R];
		cc.perm[K][4 * R] = tmp;
		
	}
	else {
		int tmp = cc.perm[IDX][get_index(F, SW)];
		cc.perm[IDX][get_index(F, SW)] = cc.perm[IDX][get_index(L, SW)];
		cc.perm[IDX][get_index(L, SW)] = cc.perm[IDX][get_index(B, SW)];
		cc.perm[IDX][get_index(B, SW)] = cc.perm[IDX][get_index(R, SW)];
		cc.perm[IDX][get_index(R, SW)] = tmp;

		tmp = cc.perm[IDX][get_index(F, SE)];
		cc.perm[IDX][get_index(F, SE)] = cc.perm[IDX][get_index(L, SE)];
		cc.perm[IDX][get_index(L, SE)] = cc.perm[IDX][get_index(B, SE)];
		cc.perm[IDX][get_index(B, SE)] = cc.perm[IDX][get_index(R, SE)];
		cc.perm[IDX][get_index(R, SE)] = tmp;
	}
}

template <int N, int K>
void apply_MF(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");

	// (U-SW, R-NW, D-NE, L-SE)
	// (U-SE, R-SW, D-NW, L-NE)

	constexpr int IDX=(N % 2 ? K : K - 1);

	if (K == 0) {
		// centers
		static_assert(N % 2, "N must be odd in order to use K = 0");
		// (U R D L)
		int tmp = cc.perm[K][4 * U];
		
		cc.perm[K][4 * U] = cc.perm[K][4 * L];
		cc.perm[K][4 * L] = cc.perm[K][4 * D];
		cc.perm[K][4 * D] = cc.perm[K][4 * R];
		cc.perm[K][4 * R] = tmp;
		
	}
	else {
		int tmp = cc.perm[IDX][get_index(U, SW)];
		cc.perm[IDX][get_index(U, SW)] = cc.perm[IDX][get_index(L, SE)];
		cc.perm[IDX][get_index(L, SE)] = cc.perm[IDX][get_index(D, NE)];
		cc.perm[IDX][get_index(D, NE)] = cc.perm[IDX][get_index(R, NW)];
		cc.perm[IDX][get_index(R, NW)] = tmp;

		tmp = cc.perm[IDX][get_index(U, SE)];
		cc.perm[IDX][get_index(U, SE)] = cc.perm[IDX][get_index(L, NE)];
		cc.perm[IDX][get_index(L, NE)] = cc.perm[IDX][get_index(D, NW)];
		cc.perm[IDX][get_index(D, NW)] = cc.perm[IDX][get_index(R, SW)];
		cc.perm[IDX][get_index(R, SW)] = tmp;
	}
}

template <int N, int K>
void apply_MB(Center_corners<N> &cc) {
	static_assert(K <= number_of_layers<N>, "K must be less than or equal to number_of_layers<N>");

	// (U-NW, L-SW, D-SE, R-NE)
	// (U-NE, L-NW, D-SW, R-SE)

	constexpr int IDX=(N % 2 ? K : K - 1);

	if (K == 0) {
		// centers
		static_assert(N % 2, "N must be odd in order to use K = 0");
		// (U L D R)
		int tmp = cc.perm[K][4 * U];
		
		cc.perm[K][4 * U] = cc.perm[K][4 * R];
		cc.perm[K][4 * R] = cc.perm[K][4 * D];
		cc.perm[K][4 * D] = cc.perm[K][4 * L];
		cc.perm[K][4 * L] = tmp;
		
	}
	else {
		int tmp = cc.perm[IDX][get_index(U, NW)];
		cc.perm[IDX][get_index(U, NW)] = cc.perm[IDX][get_index(R, NE)];
		cc.perm[IDX][get_index(R, NE)] = cc.perm[IDX][get_index(D, SE)];
		cc.perm[IDX][get_index(D, SE)] = cc.perm[IDX][get_index(L, SW)];
		cc.perm[IDX][get_index(L, SW)] = tmp;

		tmp = cc.perm[IDX][get_index(U, NE)];
		cc.perm[IDX][get_index(U, NE)] = cc.perm[IDX][get_index(R, SE)];
		cc.perm[IDX][get_index(R, SE)] = cc.perm[IDX][get_index(D, SW)];
		cc.perm[IDX][get_index(D, SW)] = cc.perm[IDX][get_index(L, NW)];
		cc.perm[IDX][get_index(L, NW)] = tmp;
	}
}

template <int N>
int signum(Center_corners<N> &cc) {
	int signum = 1;
	for (int k = 0; k < number_of_layers<N>; k++) {
		for (int i = 0; i < 24; i++)
		for (int j = i + 1; j < 24; j++)
			if (cc.perm[k][i] > cc.perm[k][j])
				signum*=-1;
	}

	return signum;
}

