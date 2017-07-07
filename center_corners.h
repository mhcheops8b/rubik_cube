#pragma once
#include "faces.h"


namespace rubik_cube {

template <int N, bool isOdd>
struct _Center_corners_Impl;

template <int N, int K, bool isOdd>
struct _Center_corners_Impl_K;

template <int N, bool isOdd>
class _Center_corners;

template <int N>
using Center_corners = _Center_corners<N, N % 2 == 1>;

template <int N, bool isOdd>
class _Center_corners {

public:
	_Center_corners();
	void init();
	void disp_perm(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);


	template <int U, bool odd>
	friend void apply_Face(_Center_corners<U, odd> &cc, const enum faces &face); 

	template <int U, bool odd>
	friend void apply_L(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend void apply_R(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend void apply_U(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend void apply_D(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend void apply_F(_Center_corners<U, odd> &cc);

	template <int U, bool odd>
	friend void apply_B(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void apply_ML(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void apply_MR(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void apply_MU(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void apply_MD(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void apply_MF(_Center_corners<U, odd> &cc);

	template <int U, int K, bool odd>
	friend void apply_MB(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend int signum(_Center_corners<U, odd> &cc);

	static const int number_of_layers;

	enum corners {NW = 0, NE = 1, SE = 2, SW = 3};
	static constexpr inline int get_index(const faces &f, const _Center_corners<N, isOdd>::corners &c) { return 4 * f + c; }
	
private:
	template <int U, bool odd>
	friend void _Center_corners_Impl<U, odd>::init(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend void _Center_corners_Impl<U, odd>::apply_Face(_Center_corners<U, odd> &cc, const enum faces &face); 

	template <int U, bool odd>
	friend void _Center_corners_Impl<U, odd>::disp_perm(_Center_corners<U, odd> &cc, std::ostream &os); 

	template <int U, bool odd>
	friend void _Center_corners_Impl<U, odd>::disp_cube(_Center_corners<U, odd> &cc, std::ostream &os); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_ML(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_MR(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_MF(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_MB(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_MU(_Center_corners<U, odd> &cc); 

	template <int U, int K, bool odd>
	friend void _Center_corners_Impl_K<U, K, odd>::apply_MD(_Center_corners<U, odd> &cc); 

	template <int U, bool odd>
	friend int _Center_corners_Impl<U, odd>::signum(_Center_corners<U, odd> &cc); 

	#if 0
	template <int U, bool isOdd>
	friend void disp_cube_Impl<U, isOdd>::disp_cube_(Center_corners<U> &cc, std::ostream &os);


	template <int U, int K>
	friend void apply_M_Impl<U, K>::apply_MR(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_M_Impl<U, K>::apply_MU(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_M_Impl<U, K>::apply_MD(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_M_Impl<U, K>::apply_MF(Center_corners<U> &cc); 

	template <int U, int K>
	friend void apply_M_Impl<U, K>::apply_MB(Center_corners<U> &cc); 
	#endif

	// U: 1-4, L: 5-8, F: 9-12, R: 13-16, B: 17-20, D: 21-24
	// (idx - 1)

	// facewise
	// NW: 1, NE: 2, SE: 3, SW: 4
	// layer>=1
	// For layer == 0 (odd cube) it is center
	int perm[isOdd ? _Center_corners_Impl<N, isOdd>::number_of_layers + 1 : _Center_corners_Impl<N, isOdd>::number_of_layers][24];

};


template <int N, bool isOdd>
const int _Center_corners<N, isOdd>::number_of_layers = _Center_corners_Impl<N, isOdd>::number_of_layers;

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::init() {
	_Center_corners_Impl<N, isOdd>::init(*this);
}

template <int N, bool isOdd>
_Center_corners<N, isOdd>::_Center_corners() {
	init();
}


template <int N, bool isOdd>
void _Center_corners<N, isOdd>::disp_perm(std::ostream &os) {
	_Center_corners_Impl<N, isOdd>::disp_perm(*this, os);//_Center_corners<N, isOdd> &cc, std::ostream &os)
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::disp_cube(std::ostream &os) {
	_Center_corners_Impl<N, isOdd>::disp_cube(*this, os);
}

template <int N, bool isOdd>
void apply_Face(_Center_corners<N, isOdd> &cc, const enum faces &face) {
	_Center_corners_Impl<N,isOdd>::apply_Face(cc, face);
}

template <int N, bool isOdd>
void apply_L(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, L);
}

template <int N, bool isOdd>
void apply_R(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, R);
}

template <int N, bool isOdd>
void apply_U(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, U);
}

template <int N, bool isOdd>
void apply_D(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, D);
}

template <int N, bool isOdd>
void apply_F(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, F);
}

template <int N, bool isOdd>
void apply_B(_Center_corners<N, isOdd> &cc) {
	apply_Face<N, isOdd>(cc, B);
}

template <int N, int K, bool isOdd>
void apply_ML(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_ML(cc);
}

template <int N, int K, bool isOdd>
void apply_MR(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MR(cc);
}

template <int N, int K, bool isOdd>
void apply_MF(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MF(cc);
}

template <int N, int K, bool isOdd>
void apply_MB(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MB(cc);
}

template <int N, int K, bool isOdd>
void apply_MU(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MU(cc);
}

template <int N, int K, bool isOdd>
void apply_MD(_Center_corners<N, isOdd> &cc) {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MD(cc);
}

template <int N, bool isOdd>
int signum(_Center_corners<N, isOdd> &cc) {
	return _Center_corners_Impl<N, isOdd>::signum(cc);
}


template<int N>
struct _Center_corners_Impl<N, true> {
	static const int number_of_layers = (N - 3) / 2;

	static void init(_Center_corners<N, true> &cc) {
		for (int i = 0; i < 6; i++)
			cc.perm[0][4 * i] = 4 * i;

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++)
			for (int i = 0; i < 24; i++)
				cc.perm[k][i] = i;
	}

	static void apply_Face(_Center_corners<N, true> &cc, const enum faces &face) {
		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {

			int tmp = cc.perm[k][4 * face];

			cc.perm[k][4 * face] = cc.perm[k][4 * face + 3];
			cc.perm[k][4 * face + 3] = cc.perm[k][4 * face + 2];
			cc.perm[k][4 * face + 2] = cc.perm[k][4 * face + 1];
			cc.perm[k][4 * face + 1] = tmp;	
		}
	}

	static int signum(_Center_corners<N, true> &cc) {
		int signum = 1;
		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
			for (int i = 0; i < 24; i++)
			for (int j = i + 1; j < 24; j++)
				if (cc.perm[k][i] > cc.perm[k][j])
					signum*=-1;
		}

		return signum;
	}

	static void disp_perm(_Center_corners<N, true> &cc, std::ostream &os) {
		os << "Layer 0 (center): \n"; 
		for (int i = 0; i < 6;i++) {
			std::cout << '\t' << face_labels[i] << ": ";
			for (int j = 0; j < 4; j++) {
				std::cout << std::setw(3) << cc.perm[0][j];	
			}
			std::cout << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
			std::cout << "Layer " << k << ":\n";
			for (int i = 0; i < 6;i++) {
				std::cout << '\t' << face_labels[i] << ": ";
				for (int j = 0; j < 4; j++) {
					std::cout << std::setw(3) << cc.perm[k][4*i+j];	
				}
				std::cout << '\n';
			}
		}
	}

	static void disp_cube(_Center_corners<N, true> &cc, std::ostream &os) {
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = _Center_corners<N, true>::number_of_layers; k >=0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ (cc.perm[k][4 * U]) / 4];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(U, _Center_corners<N,true>::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(U, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			os << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(U, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(U, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';
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
		for (int k = _Center_corners<N, true>::number_of_layers; k >= 0; k--) {
	//
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.perm[k][4 * L] / 4 ];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(L, _Center_corners<N,true>::NW)]) / 4 ];
					;
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(L, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.perm[k][4 * F] / 4 ];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(F, _Center_corners<N,true>::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(F, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.perm[k][4 * R] / 4 ];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(R, _Center_corners<N,true>::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(R, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.perm[k][4 * B] / 4 ];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(B, _Center_corners<N,true>::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(B, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
	//
			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(L, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(L, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(F, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(F, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(R, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(R, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(B, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(B, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k; t > 0; t--)
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

		for (int k = _Center_corners<N, true>::number_of_layers; k >= 0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.perm[k][4 * D] / 4 ];
			else {
				os << face_labels[ (cc.perm[k][cc.get_index(D, _Center_corners<N,true>::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.perm[k][cc.get_index(D, _Center_corners<N,true>::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';
			os << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k][cc.get_index(D, _Center_corners<N,true>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.perm[k][cc.get_index(D, _Center_corners<N,true>::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k; t > 0; t--)
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
};

template<int N>
struct _Center_corners_Impl<N, false> {
	static const int number_of_layers = (N - 2) / 2;

	static void init(_Center_corners<N, false> &cc) {
		for (int k = 0; k < _Center_corners<N, false>::number_of_layers; k++)
			for (int i = 0; i < 24; i++)
				cc.perm[k][i] = i;
	}

	static void apply_Face(_Center_corners<N, false> &cc, const enum faces &face) {
		for (int k = 0; k < _Center_corners<N, false>::number_of_layers; k++) {
			int tmp = cc.perm[k][4 * face];

			cc.perm[k][4 * face] = cc.perm[k][4 * face + 3];
			cc.perm[k][4 * face + 3] = cc.perm[k][4 * face + 2];
			cc.perm[k][4 * face + 2] = cc.perm[k][4 * face + 1];
			cc.perm[k][4 * face + 1] = tmp;	
		}
	}

	static int signum(_Center_corners<N, true> &cc) {
		int signum = 1;
		for (int k = 0; k < _Center_corners<N, false>::number_of_layers; k++) {
			for (int i = 0; i < 24; i++)
			for (int j = i + 1; j < 24; j++)
				if (cc.perm[k][i] > cc.perm[k][j])
					signum*=-1;
		}

		return signum;
	}

	static void disp_perm(_Center_corners<N, true> &cc, std::ostream &os) {
		for (int k = 0; k < _Center_corners<N, true>::number_of_layers; k++) {
			std::cout << "Layer " << k + 1 << ":\n";
			for (int i = 0; i < 6;i++) {
				std::cout << '\t' << face_labels[i] << ": ";
				for (int j = 0; j < 4; j++) {
					std::cout << std::setw(3) << cc.perm[k][4*i+j];	
				}
				std::cout << '\n';
			}
		}
	}

	static void disp_cube(_Center_corners<N, false> &cc, std::ostream &os) {
	//
		for (int i = 0; i <= N; i++)
			os << ' ';

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		for (int k = _Center_corners<N, false>::number_of_layers; k > 0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][_Center_corners<N,false>::NW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][_Center_corners<N,false>::NE]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
		for (int k = 1; k <= _Center_corners<N, false>::number_of_layers; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][_Center_corners<N,false>::SW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][_Center_corners<N,false>::SE]) / 4 ];
			
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

		for (int k = _Center_corners<N, false>::number_of_layers; k > 0; k--) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(L, _Center_corners<N,false>::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(L, _Center_corners<N,false>::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(F, _Center_corners<N,false>::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(F, _Center_corners<N,false>::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(R, _Center_corners<N,false>::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(R, _Center_corners<N,false>::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(B, _Center_corners<N,false>::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(B, _Center_corners<N,false>::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';
			os << '\n';
		}
		for (int k = 1; k <= _Center_corners<N, false>::number_of_layers; k++) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(L, _Center_corners<N,false>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(L, _Center_corners<N,false>::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(F, _Center_corners<N,false>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(F, _Center_corners<N,false>::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(R, _Center_corners<N,false>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(R, _Center_corners<N,false>::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(B, _Center_corners<N,false>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(B, _Center_corners<N,false>::SE)]) / 4 ];
			
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

		for (int k = _Center_corners<N, false>::number_of_layers; k > 0; k--) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(D, _Center_corners<N,false>::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(D, _Center_corners<N,false>::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';
			//os << '.';
			os << '\n';
		}
		for (int k = 1; k <= _Center_corners<N, false>::number_of_layers; k++) {
	//
			for (int i = 0; i <= N; i++)
				os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.perm[k - 1][cc.get_index(D, _Center_corners<N,false>::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.perm[k - 1][cc.get_index(D, _Center_corners<N,false>::SE)]) / 4 ];
			
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
};

template<int N>
struct _Center_corners_Impl_K<N, 0, true> {
	static void apply_ML(_Center_corners<N, true> &cc) {
		static_assert(N % 2 == 1, "N must be odd in order to use K = 0.");
			// centers
			// (U F D B)
			int tmp = cc.perm[0][4 * U];
			
			cc.perm[0][4 * U] = cc.perm[0][4 * B];
			cc.perm[0][4 * B] = cc.perm[0][4 * D];
			cc.perm[0][4 * D] = cc.perm[0][4 * F];
			cc.perm[0][4 * F] = tmp;

	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U B D F)
		int tmp = cc.perm[0][4 * U];
		
		cc.perm[0][4 * U] = cc.perm[0][4 * F];
		cc.perm[0][4 * F] = cc.perm[0][4 * D];
		cc.perm[0][4 * D] = cc.perm[0][4 * B];
		cc.perm[0][4 * B] = tmp;
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F L B R)
		int tmp = cc.perm[0][4 * F];
		
		cc.perm[0][4 * F] = cc.perm[0][4 * R];
		cc.perm[0][4 * R] = cc.perm[0][4 * B];
		cc.perm[0][4 * B] = cc.perm[0][4 * L];
		cc.perm[0][4 * L] = tmp;
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F R B L)
		int tmp = cc.perm[0][4 * F];
		
		cc.perm[0][4 * F] = cc.perm[0][4 * L];
		cc.perm[0][4 * L] = cc.perm[0][4 * B];
		cc.perm[0][4 * B] = cc.perm[0][4 * R];
		cc.perm[0][4 * R] = tmp;
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U R D L)
		int tmp = cc.perm[0][4 * U];
		
		cc.perm[0][4 * U] = cc.perm[0][4 * L];
		cc.perm[0][4 * L] = cc.perm[0][4 * D];
		cc.perm[0][4 * D] = cc.perm[0][4 * R];
		cc.perm[0][4 * R] = tmp;
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U L D R)
		int tmp = cc.perm[0][4 * U];
		
		cc.perm[0][4 * U] = cc.perm[0][4 * R];
		cc.perm[0][4 * R] = cc.perm[0][4 * D];
		cc.perm[0][4 * D] = cc.perm[0][4 * L];
		cc.perm[0][4 * L] = tmp;
	}
};

template <int N>
struct _Center_corners_Impl_K<N, 0, false> {
	static void apply_ML(_Center_corners<N, false> &cc) {
		static_assert(N % 2 == 1, "N must be odd in order to use K = 0.");
	}

	static void apply_MR(_Center_corners<N, false> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
	}

	static void apply_MU(_Center_corners<N, false> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
	}

	static void apply_MD(_Center_corners<N, false> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
	}

	static void apply_MF(_Center_corners<N, false> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
	}

	static void apply_MB(_Center_corners<N, false> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
	}
};

template<int N, int K>
struct _Center_corners_Impl_K<N, K, true> {
	static void apply_ML(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K][cc.get_index(U, _Center_corners<N, true>::NW)];
		cc.perm[K][cc.get_index(U, _Center_corners<N, true>::NW)] = cc.perm[K][cc.get_index(B, _Center_corners<N, true>::SE)];
		cc.perm[K][cc.get_index(B, _Center_corners<N, true>::SE)] = cc.perm[K][cc.get_index(D, _Center_corners<N, true>::NW)];
		cc.perm[K][cc.get_index(D, _Center_corners<N, true>::NW)] = cc.perm[K][cc.get_index(F, _Center_corners<N, true>::NW)];
		cc.perm[K][cc.get_index(F, _Center_corners<N, true>::NW)] = tmp;

		tmp = cc.perm[K][cc.get_index(U, _Center_corners<N, true>::SW)];
		cc.perm[K][cc.get_index(U, _Center_corners<N, true>::SW)] = cc.perm[K][cc.get_index(B, _Center_corners<N, true>::NE)];
		cc.perm[K][cc.get_index(B, _Center_corners<N, true>::NE)] = cc.perm[K][cc.get_index(D, _Center_corners<N, true>::SW)];
		cc.perm[K][cc.get_index(D, _Center_corners<N, true>::SW)] = cc.perm[K][cc.get_index(F, _Center_corners<N, true>::SW)];
		cc.perm[K][cc.get_index(F, _Center_corners<N, true>::SW) ] = tmp;
	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(F, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(B, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::SW)] = tmp;

		tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(F, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(B, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::NW) ] = tmp;
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K][get_index(F, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::NW)] = cc.perm[K][get_index(R, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::NW)] = cc.perm[K][get_index(B, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::NW)] = cc.perm[K][get_index(L, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::NW)] = tmp;

		tmp = cc.perm[K][get_index(F, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(R, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(B, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(L, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::NE)] = tmp;
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K][get_index(F, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::SW)] = cc.perm[K][get_index(L, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::SW)] = cc.perm[K][get_index(B, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::SW)] = cc.perm[K][get_index(R, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::SW)] = tmp;

		tmp = cc.perm[K][get_index(F, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(F, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(L, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(B, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(B, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(R, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::SE)] = tmp;
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");


		int tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::SW)] = cc.perm[K][get_index(L, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(R, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::NW)] = tmp;

		tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(L, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::NW)] = cc.perm[K][get_index(R, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::SW)] = tmp;
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::NW)] = cc.perm[K][get_index(R, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(L, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::SW)] = tmp;

		tmp = cc.perm[K][get_index(U, _Center_corners<N, true>::NE)];
		cc.perm[K][get_index(U, _Center_corners<N, true>::NE)] = cc.perm[K][get_index(R, _Center_corners<N, true>::SE)];
		cc.perm[K][get_index(R, _Center_corners<N, true>::SE)] = cc.perm[K][get_index(D, _Center_corners<N, true>::SW)];
		cc.perm[K][get_index(D, _Center_corners<N, true>::SW)] = cc.perm[K][get_index(L, _Center_corners<N, true>::NW)];
		cc.perm[K][get_index(L, _Center_corners<N, true>::NW)] = tmp;
	}
};

template<int N, int K>
struct _Center_corners_Impl_K<N, K, false> {
	static void apply_ML(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SW) ] = tmp;
	}

	static void apply_MR(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NW) ] = tmp;
	}

	static void apply_MU(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NE)] = tmp;
	}

	static void apply_MD(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(F, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(B, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SE)] = tmp;
	}

	static void apply_MF(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SW)] = tmp;
	}

	static void apply_MB(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		int tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NW)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::SW)] = tmp;

		tmp = cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NE)];
		cc.perm[K - 1][cc.get_index(U, _Center_corners<N, false>::NE)] = cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SE)];
		cc.perm[K - 1][cc.get_index(R, _Center_corners<N, false>::SE)] = cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SW)];
		cc.perm[K - 1][cc.get_index(D, _Center_corners<N, false>::SW)] = cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NW)];
		cc.perm[K - 1][cc.get_index(L, _Center_corners<N, false>::NW)] = tmp;
	}

};

}
