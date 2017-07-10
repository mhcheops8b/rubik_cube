#pragma once
#include "faces.h"
#include <utility>


namespace rubik_cube {

struct _Center_corners_consts {
	enum corners {NW = 0, NE = 1, SE = 2, SW = 3};
};

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
	friend _Center_corners_Impl<N, isOdd>;
	void apply_cycle(std::pair<int,int> (&cycle)[4]);
	void apply_cycle(std::pair<int,int> idx1, std::pair<int,int> idx2, std::pair<int,int> idx3, std::pair<int,int> idx4);

	_Center_corners();
	void init();
	void disp_perm(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	void apply_Face(const enum faces &face);

	// L move
	void apply_L();
	// R move
	void apply_R();
	// F move
	void apply_F();
	// B move
	void apply_B();
	// U move
	void apply_U();
	// D move
	void apply_D();

	// ML<K> move
	template <int K>
	void apply_ML();

	// MR<K> move
	template <int K>
	void apply_MR();

	// MF<K> move
	template <int K>
	void apply_MF();

	// MB<K> move
	template <int K>
	void apply_MB();

	// MU<K> move
	template <int K>
	void apply_MU();

	// MD<K> move
	template <int K>
	void apply_MD();

	int signum();

	static const int number_of_layers;

	static constexpr inline int get_index(const faces &f, const _Center_corners_consts::corners &c) { return 4 * f + c; }
	
private:
	// U: 1-4, L: 5-8, F: 9-12, R: 13-16, B: 17-20, D: 21-24
	// (idx - 1)

	// facewise
	// NW: 1, NE: 2, SE: 3, SW: 4
	// layer>=1
	// For layer == 0 (odd cube) it is center
	int m_perm[isOdd ? _Center_corners_Impl<N, isOdd>::number_of_layers + 1 : _Center_corners_Impl<N, isOdd>::number_of_layers][24];

};

template <int N, bool isEven>
void _Center_corners<N, isEven>::apply_cycle(std::pair<int,int> (&cycle)[4]) {

	int tmp = m_perm[cycle[3].first][cycle[3].second];
	for (int j = 2; j >= 0; j--)
		m_perm[cycle[j + 1].first][cycle[j + 1].second] = m_perm[cycle[j].first][cycle[j].second];
	m_perm[cycle[0].first][cycle[0].second] = tmp;

}

template <int N, bool isEven>
void _Center_corners<N, isEven>::apply_cycle(std::pair<int,int> idx1, std::pair<int,int> idx2, 
						std::pair<int,int> idx3, std::pair<int,int> idx4) {

	std::pair<int,int> tmp_array[] = { idx1, idx2, idx3, idx4 };

	apply_cycle(tmp_array);
}

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
	_Center_corners_Impl<N, isOdd>::disp_perm(*this, os);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::disp_cube(std::ostream &os) {
	_Center_corners_Impl<N, isOdd>::disp_cube(*this, os);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_Face(const enum faces &face) {
	_Center_corners_Impl<N,isOdd>::apply_Face(*this, face);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_L() {
	apply_Face(L);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_R() {
	apply_Face(R);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_F() {
	apply_Face(F);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_B() {
	apply_Face(B);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_U() {
	apply_Face(U);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_D() {
	apply_Face(D);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_ML() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_ML(*this);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_MR() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MR(*this);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_MF() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MF(*this);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_MB() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MB(*this);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_MU() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MU(*this);
}

template <int N, bool isOdd>
template <int K>
void _Center_corners<N, isOdd>::apply_MD() {
	_Center_corners_Impl_K<N, K, isOdd>::apply_MD(*this);
}

template <int N, bool isOdd>
int _Center_corners<N, isOdd>::signum() {
	return _Center_corners_Impl<N, isOdd>::signum(*this);
}


template<int N>
struct _Center_corners_Impl<N, true> {
	static const int number_of_layers = (N - 3) / 2;

	static void init(_Center_corners<N, true> &cc) {
		for (int i = 0; i < 6; i++)
			cc.m_perm[0][4 * i] = 4 * i;

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++)
			for (int i = 0; i < 24; i++)
				cc.m_perm[k][i] = i;
	}

	static void apply_Face(_Center_corners<N, true> &cc, const enum faces &face) {
		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {

			int tmp = cc.m_perm[k][4 * face];

			cc.m_perm[k][4 * face] = cc.m_perm[k][4 * face + 3];
			cc.m_perm[k][4 * face + 3] = cc.m_perm[k][4 * face + 2];
			cc.m_perm[k][4 * face + 2] = cc.m_perm[k][4 * face + 1];
			cc.m_perm[k][4 * face + 1] = tmp;	
		}
	}

	static int signum(_Center_corners<N, true> &cc) {
		int signum = 1;
		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
			for (int i = 0; i < 24; i++)
			for (int j = i + 1; j < 24; j++)
				if (cc.m_perm[k][i] > cc.m_perm[k][j])
					signum*=-1;
		}

		return signum;
	}

	static void disp_perm(_Center_corners<N, true> &cc, std::ostream &os) {
		os << "Layer 0 (center): \n"; 
		for (int i = 0; i < 6;i++) {
			std::cout << '\t' << face_labels[i] << ": ";
			for (int j = 0; j < 4; j++) {
				std::cout << std::setw(3) << cc.m_perm[0][j];	
			}
			std::cout << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
			std::cout << "Layer " << k << ":\n";
			for (int i = 0; i < 6;i++) {
				std::cout << '\t' << face_labels[i] << ": ";
				for (int j = 0; j < 4; j++) {
					std::cout << std::setw(3) << cc.m_perm[k][4*i+j];	
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
				os << face_labels[ (cc.m_perm[k][4 * U]) / 4];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(U, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(U, _Center_corners_consts::NE)]) / 4 ];
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

			os << face_labels[ (cc.m_perm[k][cc.get_index(U, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(U, _Center_corners_consts::SE)]) / 4 ];
		
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
				os << face_labels[ cc.m_perm[k][4 * L] / 4 ];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(L, _Center_corners_consts::NW)]) / 4 ];
					;
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(L, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.m_perm[k][4 * F] / 4 ];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(F, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(F, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.m_perm[k][4 * R] / 4 ];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(R, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(R, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << face_labels[ cc.m_perm[k][4 * B] / 4 ];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(B, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(B, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
	//
			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k][cc.get_index(L, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(L, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k][cc.get_index(F, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(F, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k][cc.get_index(R, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(R, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k][cc.get_index(B, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(B, _Center_corners_consts::SE)]) / 4 ];
		
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
				os << face_labels[ cc.m_perm[k][4 * D] / 4 ];
			else {
				os << face_labels[ (cc.m_perm[k][cc.get_index(D, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << face_labels[ (cc.m_perm[k][cc.get_index(D, _Center_corners_consts::NE)]) / 4 ];
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

			os << face_labels[ (cc.m_perm[k][cc.get_index(D, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k][cc.get_index(D, _Center_corners_consts::SE)]) / 4 ];
		
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
				cc.m_perm[k][i] = i;
	}

	static void apply_Face(_Center_corners<N, false> &cc, const enum faces &face) {
		for (int k = 0; k < _Center_corners<N, false>::number_of_layers; k++) {
			int tmp = cc.m_perm[k][4 * face];

			cc.m_perm[k][4 * face] = cc.m_perm[k][4 * face + 3];
			cc.m_perm[k][4 * face + 3] = cc.m_perm[k][4 * face + 2];
			cc.m_perm[k][4 * face + 2] = cc.m_perm[k][4 * face + 1];
			cc.m_perm[k][4 * face + 1] = tmp;	
		}
	}

	static int signum(_Center_corners<N, true> &cc) {
		int signum = 1;
		for (int k = 0; k < _Center_corners<N, false>::number_of_layers; k++) {
			for (int i = 0; i < 24; i++)
			for (int j = i + 1; j < 24; j++)
				if (cc.m_perm[k][i] > cc.m_perm[k][j])
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
					std::cout << std::setw(3) << cc.m_perm[k][4*i+j];	
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

			os << face_labels[ (cc.m_perm[k - 1][_Center_corners_consts::NW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][_Center_corners_consts::NE]) / 4 ];
			
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

			os << face_labels[ (cc.m_perm[k - 1][_Center_corners_consts::SW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][_Center_corners_consts::SE]) / 4 ];
			
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

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(L, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(L, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(F, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(F, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(R, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(R, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(B, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(B, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';
			os << '\n';
		}
		for (int k = 1; k <= _Center_corners<N, false>::number_of_layers; k++) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(L, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(L, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(F, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(F, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(R, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(R, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(B, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(B, _Center_corners_consts::SE)]) / 4 ];
			
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

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(D, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(D, _Center_corners_consts::NE)]) / 4 ];
			
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

			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(D, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << face_labels[ (cc.m_perm[k - 1][cc.get_index(D, _Center_corners_consts::SE)]) / 4 ];
			
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

		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * U),
			std::make_pair<int,int>(0, 4 * F),
			std::make_pair<int,int>(0, 4 * D),
			std::make_pair<int,int>(0, 4 * B)
		);
	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U B D F)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * U),
			std::make_pair<int,int>(0, 4 * B),
			std::make_pair<int,int>(0, 4 * D),
			std::make_pair<int,int>(0, 4 * F)
		);
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F L B R)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * F),
			std::make_pair<int,int>(0, 4 * L),
			std::make_pair<int,int>(0, 4 * B),
			std::make_pair<int,int>(0, 4 * R)
		);
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F R B L)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * F),
			std::make_pair<int,int>(0, 4 * R),
			std::make_pair<int,int>(0, 4 * B),
			std::make_pair<int,int>(0, 4 * L)
		);
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U R D L)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * U),
			std::make_pair<int,int>(0, 4 * R),
			std::make_pair<int,int>(0, 4 * D),
			std::make_pair<int,int>(0, 4 * L)
		);
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U L D R)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * U),
			std::make_pair<int,int>(0, 4 * L),
			std::make_pair<int,int>(0, 4 * D),
			std::make_pair<int,int>(0, 4 * R)
		);
	}
};

template <int N>
struct _Center_corners_Impl_K<N, 0, false> {
	typedef struct _Center_corners_Impl_K<N,0,false> type;

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
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::NE))
		);
	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::SE))
		);
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::NW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::NE))
		);
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::SW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(F, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(B, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::SE))
		);
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");


		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::SW))
		);
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(R, _Center_corners_consts::SE))
		);
	}
};

template<int N, int K>
struct _Center_corners_Impl_K<N, K, false> {
	typedef struct _Center_corners_Impl_K<N, K, false> type;

	static void apply_ML(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::NE))
		);
	}

	static void apply_MR(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::SE))
		);
	}

	static void apply_MU(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::NW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::NE))
		);
	}

	static void apply_MD(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::SW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(F, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(B, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::SE))
		);
	}

	static void apply_MF(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::NE))
		);
	}

	static void apply_MB(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(R, _Center_corners_consts::SE))
		);
	}

};

}
