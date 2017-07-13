#pragma once
#include "faces.h"
#include <utility>
#include "cubeNNN.h"


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
	void apply_Face(const enum Faces::faces &face);

	void toPermutationN();
	Permutation<N> toPermutationN(Permutation<N> &in);

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

	static constexpr inline int get_index(const Faces::faces &f, const _Center_corners_consts::corners &c) { return 4 * f + c; }
	
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
void _Center_corners<N, isOdd>::apply_Face(const enum Faces::faces &face) {
	_Center_corners_Impl<N,isOdd>::apply_Face(*this, face);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_L() {
	apply_Face(Faces::L);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_R() {
	apply_Face(Faces::R);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_F() {
	apply_Face(Faces::F);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_B() {
	apply_Face(Faces::B);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_U() {
	apply_Face(Faces::U);
}

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::apply_D() {
	apply_Face(Faces::D);
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

template <int N, bool isOdd>
void _Center_corners<N, isOdd>::toPermutationN() {
	_Center_corners_Impl<N,isOdd>::toPermutationN(*this);
}

template <int N, bool isOdd>
Permutation<N> _Center_corners<N, isOdd>::toPermutationN(Permutation<N> &in) {
	return _Center_corners_Impl<N,isOdd>::toPermutationN(*this, in);
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

	static void apply_Face(_Center_corners<N, true> &cc, const enum Faces::faces &face) {
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
			std::cout << '\t' << Faces::labels[i] << ": ";
			for (int j = 0; j < 4; j++) {
				std::cout << std::setw(3) << cc.m_perm[0][j];	
			}
			std::cout << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
			std::cout << "Layer " << k << ":\n";
			for (int i = 0; i < 6;i++) {
				std::cout << '\t' << Faces::labels[i] << ": ";
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
				os << Faces::labels[ (cc.m_perm[k][4 * Faces::U]) / 4];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::U, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::U, _Center_corners_consts::NE)]) / 4 ];
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

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::U, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::U, _Center_corners_consts::SE)]) / 4 ];
		
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
				os << Faces::labels[ cc.m_perm[k][4 * Faces::L] / 4 ];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::L, _Center_corners_consts::NW)]) / 4 ];
					;
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::L, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';
			if (k == 0)
				os << Faces::labels[ cc.m_perm[k][4 * Faces::F] / 4 ];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::F, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::F, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << Faces::labels[ cc.m_perm[k][4 * Faces::R] / 4 ];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::R, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::R, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';
			if (k == 0)
				os << Faces::labels[ cc.m_perm[k][4 * Faces::B] / 4 ];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::B, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::B, _Center_corners_consts::NE)]) / 4 ];
			}     
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << '\n';
		}

		for (int k = 1; k <= _Center_corners<N, true>::number_of_layers; k++) {
	//
			for (int t = (N - 1)/2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::L, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::L, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::F, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::F, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k ; t>0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::R, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::R, _Center_corners_consts::SE)]) / 4 ];
		
			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = (N - 1)/2 - k; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::B, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::B, _Center_corners_consts::SE)]) / 4 ];
		
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
				os << Faces::labels[ cc.m_perm[k][4 * Faces::D] / 4 ];
			else {
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::D, _Center_corners_consts::NW)]) / 4 ];
				for (int s = 0; s < 2* k - 1; s++)
					os << '.';
				os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::D, _Center_corners_consts::NE)]) / 4 ];
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

			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::D, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 1; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k][cc.get_index(Faces::D, _Center_corners_consts::SE)]) / 4 ];
		
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

	static int adjustments(int direction, int layer) {
		int adj = 0;
	
		switch (direction) {
			// NW
			case 0:
				adj = - layer * N - layer;
				break;
			// NE
			case 1:
				adj = - layer * N + layer;
				break;
			// SE
			case 2:
				adj = + layer * N + layer;
				break;

			// SE
			case 3:
				adj = + layer * N - layer;
				break;
			default:
				break;
		};
		return adj;
	}
	static void toPermutationN(_Center_corners<N, true> &cc) {
		// k = 0
		for (int i = 0; i < 6; i++) {
			int idx = 4 * i;

			int face = cc.m_perm[0][idx] / 4;
			int direction = cc.m_perm[0][idx] % 4;

			std::cout << Faces::labels[face] << "(" << 0 << ", " << direction <<") -> " 
				<< Faces::labels[i] << "(" << 0 << ", " << 0 << ")\n";
	
			int idx1 = face * N * N + (N - 1) /2 * N + (N - 1) /2;
			int idx2 = i * N * N + (N - 1) /2 * N + (N - 1) /2;
			if (idx1 != idx2)
				std::cout << idx1 << "->" << idx2 << '\n';

		}
		for (int k = 1 ; k <=_Center_corners_Impl<N, true>::number_of_layers; k++) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					int idx = 4 * i + j;

					int face = cc.m_perm[k][idx] / 4;
					int direction = cc.m_perm[k][idx] % 4;

					std::cout << Faces::labels[face] << "(" << k << ", " << direction <<") -> " 
						<< Faces::labels[i] << "(" << k << ", " << j << ")\n";
					
					int idx1 = face * N * N + (N - 1) /2 * N + (N - 1) /2;
					int idx2 = i * N * N + (N - 1) /2 * N + (N - 1) /2;
					idx1 += _Center_corners_Impl<N,true>::adjustments(direction, k);
					idx2 += _Center_corners_Impl<N,true>::adjustments(j, k);

					if (idx1 != idx2)
						std::cout << idx1 << "->" << idx2 << '\n';

				}

			}
		}	
	}

	static Permutation<N> toPermutationN(_Center_corners<N, true> &cc, Permutation<N> &in) {
		Permutation<N> output(in);

		// k = 0
		for (int i = 0; i < 6; i++) {
			int idx = 4 * i;

			int face = cc.m_perm[0][idx] / 4;
	
			int idx1 = face * N * N + (N - 1) /2 * N + (N - 1) /2;
			int idx2 = i * N * N + (N - 1) /2 * N + (N - 1) /2;
			if (idx1 != idx2)
				output._components[idx1] = in._components[idx2];

		}
		for (int k = 1 ; k <=_Center_corners_Impl<N, true>::number_of_layers; k++) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					int idx = 4 * i + j;

					int face = cc.m_perm[k][idx] / 4;
					int direction = cc.m_perm[k][idx] % 4;

					
					int idx1 = face * N * N + (N - 1) /2 * N + (N - 1) /2;
					int idx2 = i * N * N + (N - 1) /2 * N + (N - 1) /2;
					idx1 += _Center_corners_Impl<N,true>::adjustments(direction, k);
					idx2 += _Center_corners_Impl<N,true>::adjustments(j, k);

					if (idx1 != idx2)
						output._components[idx1] = in._components[idx2];
				}

			}
		}	
		return output;
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

	static void apply_Face(_Center_corners<N, false> &cc, const enum Faces::faces &face) {
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
				std::cout << '\t' << Faces::labels[i] << ": ";
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

			os << Faces::labels[ (cc.m_perm[k - 1][_Center_corners_consts::NW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][_Center_corners_consts::NE]) / 4 ];
			
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

			os << Faces::labels[ (cc.m_perm[k - 1][_Center_corners_consts::SW]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][_Center_corners_consts::SE]) / 4 ];
			
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

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::L, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::L, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::F, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::F, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::R, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::R, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::B, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::B, _Center_corners_consts::NE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';
			os << '\n';
		}
		for (int k = 1; k <= _Center_corners<N, false>::number_of_layers; k++) {
	//
			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::L, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::L, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::F, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::F, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::R, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::R, _Center_corners_consts::SE)]) / 4 ];
			
			for (int t = N / 2 - k; t > 0; t--)
				os << '.';

			os << ' ';

			for (int t = N / 2 - k ; t > 0; t--)
				os << '.';

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::B, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::B, _Center_corners_consts::SE)]) / 4 ];
			
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

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::D, _Center_corners_consts::NW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::D, _Center_corners_consts::NE)]) / 4 ];
			
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

			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::D, _Center_corners_consts::SW)]) / 4 ];
			for (int s = 0; s < 2* k - 2; s++)
				os << '.';
			os << Faces::labels[ (cc.m_perm[k - 1][cc.get_index(Faces::D, _Center_corners_consts::SE)]) / 4 ];
			
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

	static int adjustments(int direction, int layer) {
		int adj = 0;
		
		switch (direction) {
			// NW
			case 0:
				adj = -(layer - 1) * N - (layer - 1);
				break;
			// NE
			case 1:
				adj = - (layer - 1) * N + layer;
				break;
			// SE
			case 2:
				adj = layer * N + layer;
				break;
			// SW
			case 3:
				adj = layer * N - (layer - 1);
				break;
			default:
				break;
		};
		return adj;
	}

	static void toPermutationN(_Center_corners<N, false> &cc) {
		for (int k = 0; k < _Center_corners_Impl<N, false>::number_of_layers; k++) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					int idx = 4 * i + j;

					int face = cc.m_perm[k][idx] / 4;
					int direction = cc.m_perm[k][idx] % 4;

					std::cout << Faces::labels[face] << "(" << k << ", " << direction << ") -> "
						<< Faces::labels[i] << "(" << k << ", " << j << ")\n";

					int idx1 = face * N * N + (N / 2 - 1) * N + (N / 2 - 1);
					int idx2 = i * N * N + (N / 2 - 1) * N + (N / 2 - 1);
					idx1 += _Center_corners_Impl<N, false>::adjustments(direction, k + 1);
					idx2 += _Center_corners_Impl<N, false>::adjustments(j, k + 1);

					if (idx1 != idx2)
						std::cout << idx1 << "->" << idx2 << '\n';

				}

			}
		}
	}

	static Permutation<N> toPermutationN(_Center_corners<N, false> &cc, Permutation<N> &in) {
		Permutation<N> output(in);
		for (int k = 0; k < _Center_corners_Impl<N, false>::number_of_layers; k++) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					int idx = 4 * i + j;

					int face = cc.m_perm[k][idx] / 4;
					int direction = cc.m_perm[k][idx] % 4;

					//std::cout << Faces::labels[face] << "(" << k << ", " << direction << ") -> "
						//<< Faces::labels[i] << "(" << k << ", " << j << ")\n";

					int idx1 = face * N * N + (N / 2 - 1) * N + (N / 2 - 1);
					int idx2 = i * N * N + (N / 2 - 1) * N + (N / 2 - 1);
					idx1 += _Center_corners_Impl<N, false>::adjustments(direction, k + 1);
					idx2 += _Center_corners_Impl<N, false>::adjustments(j, k + 1);

					if (idx1 != idx2)
						output._components[idx1] = in._components[idx2];
						//std::cout << idx1 << "->" << idx2 << '\n';

				}

			}
		}
		return output;
	}
};

template<int N>
struct _Center_corners_Impl_K<N, 0, true> {
	static void apply_ML(_Center_corners<N, true> &cc) {
		static_assert(N % 2 == 1, "N must be odd in order to use K = 0.");
		// centers
		// (U F D B)

		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::U),
			std::make_pair<int,int>(0, 4 * Faces::F),
			std::make_pair<int,int>(0, 4 * Faces::D),
			std::make_pair<int,int>(0, 4 * Faces::B)
		);
	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U B D F)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::U),
			std::make_pair<int,int>(0, 4 * Faces::B),
			std::make_pair<int,int>(0, 4 * Faces::D),
			std::make_pair<int,int>(0, 4 * Faces::F)
		);
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F L B R)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::F),
			std::make_pair<int,int>(0, 4 * Faces::L),
			std::make_pair<int,int>(0, 4 * Faces::B),
			std::make_pair<int,int>(0, 4 * Faces::R)
		);
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (F R B L)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::F),
			std::make_pair<int,int>(0, 4 * Faces::R),
			std::make_pair<int,int>(0, 4 * Faces::B),
			std::make_pair<int,int>(0, 4 * Faces::L)
		);
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U R D L)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::U),
			std::make_pair<int,int>(0, 4 * Faces::R),
			std::make_pair<int,int>(0, 4 * Faces::D),
			std::make_pair<int,int>(0, 4 * Faces::L)
		);
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(N % 2, "N must be odd in order to use K = 0.");
		// centers
		// (U L D R)
		cc.apply_cycle(
			std::make_pair<int,int>(0, 4 * Faces::U),
			std::make_pair<int,int>(0, 4 * Faces::L),
			std::make_pair<int,int>(0, 4 * Faces::D),
			std::make_pair<int,int>(0, 4 * Faces::R)
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
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::NE))
		);
	}

	static void apply_MR(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::SE))
		);
	}

	static void apply_MU(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::NW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::NE))
		);
	}

	static void apply_MD(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::SW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::F, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::B, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::SE))
		);
	}

	static void apply_MF(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");


		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::SW))
		);
	}

	static void apply_MB(_Center_corners<N, true> &cc) {
		static_assert(K <= _Center_corners_Impl<N, true>::number_of_layers, "K must be less than or equal to _Center_corners<N, true>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K, cc.get_index(Faces::U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K, cc.get_index(Faces::L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K, cc.get_index(Faces::R, _Center_corners_consts::SE))
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
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::NE))
		);
	}

	static void apply_MR(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::SE))
		);
	}

	static void apply_MU(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::NW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::NE))
		);
	}

	static void apply_MD(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::SW))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::F, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::B, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::SE))
		);
	}

	static void apply_MF(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::SE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::NE))
		);
	}

	static void apply_MB(_Center_corners<N, false> &cc) {
		static_assert(K <= _Center_corners_Impl<N, false>::number_of_layers, "K must be less than or equal to _Center_corners<N, false>::number_of_layers");
		static_assert(K > 0, "K must be greater than 0");

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::SE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::NE))
		);

		cc.apply_cycle(
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::U, _Center_corners_consts::NE)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::L, _Center_corners_consts::NW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::D, _Center_corners_consts::SW)),
			std::make_pair<int,int>(K - 1, cc.get_index(Faces::R, _Center_corners_consts::SE))
		);
	}

};

}
