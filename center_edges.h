#pragma once

/*
// odd
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

// even
-----------------------------------------
| XX | 24 | 25 | 26 | 27 | 28 | 29 | XX |
-----------------------------------------
| 47 | XX |  8 |  9 | 10 | 11 | XX | 30 |
-----------------------------------------
| 46 | 23 | XX |  0 |  1 | XX | 12 | 31 |
-----------------------------------------
| 45 | 22 |  7 | XX | XX |  2 | 13 | 32 |
-----------------------------------------
| 44 | 21 |  6 | XX | XX |  3 | 14 | 33 |
-----------------------------------------
| 43 | 20 | XX |  5 |  4 | XX | 15 | 34 | 
-----------------------------------------
| 42 | XX | 19 | 18 | 17 | 16 | XX | 35 |
-----------------------------------------
| XX | 41 | 40 | 39 | 38 | 37 | 36 | XX |
-----------------------------------------

*/

#include <iostream>
#include <ostream>
#include "faces.h"
#include "cubeNNN.h"
#include <math.h>

namespace rubik_cube {

template <int N, bool isEven> struct _Center_edges_Impl;
template <int N, int K, bool isEven> struct _Center_edges_Impl_K;
template <int N, bool isEven> class _Center_edges;

template <int N>
using Center_edges = _Center_edges<N, N % 2 == 0>;

template <int N, bool isEven>
class _Center_edges {

public:
	friend _Center_edges_Impl<N, isEven>;

	_Center_edges();
	void disp_cube(std::ostream &os = std::cout);
	void disp_perm(std::ostream &os = std::cout);

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

	static const int number_of_indices;
	static const int number_of_indices_per_face;
	static const int number_of_layers;

	// north center edges
	static inline int NF(int layer, int index);

	// east center edges
	static inline int EF(int layer, int index);

	// south center edges
	static inline int SF(int layer, int index);

	// west center edges
	static inline int WF(int layer, int index);

	// north center edges wrt to face
	static inline int face_NF(const enum Faces::faces &f, int layer, int index);
	// east center edges wrt to face
	static inline int face_EF(const enum Faces::faces &f, int layer, int index);
	// south center edges wrt to face
	static inline int face_SF(const enum Faces::faces &f, int layer, int index);
	// west center edges wrt to face
	static inline int face_WF(const enum Faces::faces &f, int layer, int index);

	//
	void apply_Face(const enum Faces::faces &f);
	//
	void apply_cycle(int(&cycle)[4]);
	//
	void apply_cycle(int idx1, int idx2, int idx3, int idx4);


	//
	void toPermutationN();
	//
	Permutation<N> toPermutationN(Permutation<N> &in);
private:
	int m_perm[_Center_edges_Impl<N,isEven>::number_of_indices];
};

template <int N, bool isEven>
const int _Center_edges<N, isEven>::number_of_indices = _Center_edges_Impl<N,isEven>::number_of_indices;

template <int N, bool isEven>
const int _Center_edges<N, isEven>::number_of_indices_per_face = _Center_edges_Impl<N,isEven>::number_of_indices_per_face;

template <int N, bool isEven>
const int _Center_edges<N, isEven>::number_of_layers = _Center_edges_Impl<N,isEven>::number_of_layers;

template <int N, bool isEven>
_Center_edges<N, isEven>::_Center_edges() {
	_Center_edges_Impl<N, isEven>::_center_edges_impl(*this);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::disp_cube(std::ostream &os) {
	_Center_edges_Impl<N, isEven>::disp_cube_impl(*this, os);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::disp_perm(std::ostream &os) {
	for (int i = 0; i < _Center_edges<N, isEven>::number_of_indices; i++)
		os << m_perm[i] <<  ", ";

	os << '\n';
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::NF(int layer, int index) {
	return _Center_edges_Impl<N, isEven>::NF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::EF(int layer, int index) {
	return _Center_edges_Impl<N, isEven>::EF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::SF(int layer, int index) {
	return _Center_edges_Impl<N, isEven>::SF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::WF(int layer, int index) {
	return _Center_edges_Impl<N, isEven>::WF(layer, index);
}

// indices wrt to face
template <int N, bool isEven>
inline int _Center_edges<N, isEven>::face_NF(const enum Faces::faces &f, int layer, int index) {
	return f * _Center_edges<N, isEven>::number_of_indices_per_face
		 + _Center_edges<N, isEven>::NF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::face_EF(const enum Faces::faces &f, int layer, int index) {
	return f * _Center_edges<N, isEven>::number_of_indices_per_face
		 + _Center_edges<N, isEven>::EF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::face_SF(const enum Faces::faces &f, int layer, int index) {
	return f * _Center_edges<N, isEven>::number_of_indices_per_face
		 +_Center_edges<N, isEven>::SF(layer, index);
}

template <int N, bool isEven>
inline int _Center_edges<N, isEven>::face_WF(const enum Faces::faces &f, int layer, int index) {
	return f * _Center_edges<N, isEven>::number_of_indices_per_face 
		 + _Center_edges<N, isEven>::WF(layer, index);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::toPermutationN() {
	_Center_edges_Impl<N, isEven>::toPermutationN(*this);
}

template <int N, bool isEven>
Permutation<N> _Center_edges<N, isEven>::toPermutationN(Permutation<N> &in) {
	return _Center_edges_Impl<N, isEven>::toPermutationN(*this, in);

}

template<int N>
struct _Center_edges_Impl<N, false> {

	static const int number_of_indices = 6 * (N - 3) * (N - 3);
	static const int number_of_indices_per_face = (N - 3) * (N - 3);
	static const int number_of_layers = (N - 3) / 2;

	static inline  int NF(int layer, int index)
	{
		return 4 * (layer - 1) * (layer - 1) 
			+ index;
	}

	static inline int EF(int layer, int index)
	{
		return 4 * (layer - 1) * (layer - 1) 
			+ 2 * layer - 1 + index;
	}

	static inline int SF(int layer, int index)
	{
		return 4 * (layer - 1) * (layer - 1) 
			+ 2 * (2 * layer - 1) + index;
	}

	static inline int WF(int layer, int index)
	{
		return 4 * (layer - 1) * (layer - 1) 
			+ 3 * (2 * layer - 1) + index;
	}

	static void _center_edges_impl(_Center_edges<N, false> &ce) {
		static_assert(N % 2 == 1, "N must be odd.");
		static_assert(N >= 5, "There are no center edges for smaller cubes thant 5x5x5.");

		for (int i = 0; i < _Center_edges<N, false>::number_of_indices; i++)
			ce.m_perm[i] = i;
	}

	static void apply_Face(_Center_edges<N, false> &ce, const enum Faces::faces &f) {
	
		for (int i = 0; i < number_of_layers; i++) {
			for (int j = 0; j < 2 * i + 1; j++) {
				ce.apply_cycle(
					_Center_edges<N, false>::face_NF(f, i + 1, j),
					_Center_edges<N, false>::face_EF(f, i + 1, j),
					_Center_edges<N, false>::face_SF(f, i + 1, j),
					_Center_edges<N, false>::face_WF(f, i + 1, j));
			}
		}
	}

	static void disp_cube_impl(_Center_edges<N, false> &ce, std::ostream &os) {
	// U face
		//skip
		for (int i = 0; i <=N; i++)
			os << ' ';

		// 1st line
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// upper half
		for (int k = _Center_edges<N, false>::number_of_layers; k >= 0; k--) {
			//skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::U, t, k + t - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::U, k, t)] 
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::U, t, t - k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';
			os << '\n';


		}

		// lower half
		for (int k = 1; k <= _Center_edges<N, false>::number_of_layers; k++) {
			//skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::U, t, t - k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::U, k, t)]
							/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::U, t, t + k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';
			os << '\n';


		}

		//skip
		for (int i = 0; i <=N; i++)
			os << ' ';

		// last line
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

	// LFRB faces
		// 1st line
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// upper half
		for (int k = _Center_edges<N, false>::number_of_layers; k >= 0; k--) {
			os << '.';

			// L
			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::L, t, k + t - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::L, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::L, t, t - k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			os << '.';

			// F
			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::F, t, k + t - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::F, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::F, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			os << '.';

			// R
			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::R, t, k + t - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::R, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::R, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			os << '.';

			// B
			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::B, t, k + t - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::B, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::B, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << '\n';


		}

		// lower half
		for (int k = 1; k <= _Center_edges<N, false>::number_of_layers; k++) {
			// L
			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::L, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::L, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::L, t, t + k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			// F
			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::F, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::F, k, t)]
							/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::F, t, t + k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			// R
			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::R, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::R, k, t)]
							/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::R, t, t + k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';

			os << ' ';

			// B
			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::B, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::B, k, t)]
						/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::B, t, t + k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';
			os << '\n';


		}

		// last line
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

	// D face
		//skip
		for (int i = 0; i <=N; i++)
			os << ' ';

		// 1st line
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// upper half
		for (int k = _Center_edges<N, false>::number_of_layers; k >= 0; k--) {
			//skip
			for (int i = 0; i <=N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::D, t, k + t - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			if (k != 0) {
				for (int t = 0; t < 2 * k - 1; t++)
					os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_NF(Faces::D, k, t)]
								/ _Center_edges<N, false>::number_of_indices_per_face ];
				
				os << '.';
			}

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::D, t, t - k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';
			os << '\n';


		}

		// lower half
		for (int k = 1; k <= _Center_edges<N, false>::number_of_layers; k++) {
			//skip
			for (int i = 0; i <=N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, false>::number_of_layers; t > k; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_WF(Faces::D, t, t - k - 1)]
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
				
			os << '.';

			for (int t = 2 * k - 2; t >=0; t--)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_SF(Faces::D, k, t)]
							/ _Center_edges<N, false>::number_of_indices_per_face ];
			
			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, false>::number_of_layers;  t++)
				os << Faces::labels[ ce.m_perm[_Center_edges<N, false>::face_EF(Faces::D, t, t + k - 1)] 
							/ _Center_edges<N, false>::number_of_indices_per_face ]; 
			
			os << '.';
			os << '\n';


		}

		//skip
		for (int i = 0; i <=N; i++)
			os << ' ';

		// last line
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';


	}

	static void compute_values(int orig_idx, 
		int &face, int &layer, int &direction, int &dir_idx) {
		
			face = orig_idx / _Center_edges_Impl<N, false>::number_of_indices_per_face;

			int p_face_idx = orig_idx % _Center_edges_Impl<N, false>::number_of_indices_per_face;

			int s = floor(sqrt(p_face_idx)) / 2;
			layer = s + 1;

			int layer_idx = p_face_idx - 4*s*s;

			direction = layer_idx / (2 * s + 1);
			dir_idx = layer_idx % (2 * s + 1);
	}

	static int adjustment(int layer, int direction, int dir_idx) {
		int adj = 0;
		switch (direction) {
			// North
			case 0:
				adj = -(layer + 1) * N + dir_idx - layer;
				break;

			// East
			case 1:
				adj = (dir_idx - layer) * N + layer + 1;
				break;
			// South
			case 2:
				adj = (layer + 1) * N + layer - dir_idx;
				break;
			// West
			case 3:
				adj = (layer - dir_idx) * N - layer - 1;
				break;
			default:
				break;
		};

		return adj;
	}


	static void toPermutationN(_Center_edges<N, false> &ce) {
		static const char dir_labels[] = {'N', 'E', 'S', 'W'};
		for (int i = 0; i < 6; i++) { // faces
			for (int j = 0; j < _Center_edges_Impl<N, false>::number_of_indices_per_face; j++) { // per face indices
				int idx = _Center_edges_Impl<N, false>::number_of_indices_per_face * i + j;
				int p_value1 = ce.m_perm[idx];
				int p_value2 = idx;
				int face1, face2, layer1,layer2,direction1,direction2,dir_idx1,dir_idx2;

				_Center_edges_Impl<N, false>::compute_values(p_value1, face1, layer1, direction1, dir_idx1);
				_Center_edges_Impl<N, false>::compute_values(p_value2, face2, layer2, direction2, dir_idx2);

				int idx1, idx2;
				idx1 = idx2 = N * (N - 1) / 2 + (N - 1) / 2;
				idx1 += face1 * N * N;
				idx2 += face2 * N * N;

				idx1 += _Center_edges_Impl<N, false>::adjustment(layer1 - 1, direction1, dir_idx1);
				idx2 += _Center_edges_Impl<N, false>::adjustment(layer2 - 1, direction2, dir_idx2);
				if (idx1 != idx2) {
					std::cout << Faces::labels[face1] << "(" << layer1 << ", " << dir_labels[ direction1 ] << ", " << dir_idx1 << ") -> " 	
						  << Faces::labels[face2] << "(" << layer2 << ", " << dir_labels[ direction2 ] << ", " << dir_idx2 << ")\n";

					std::cout << idx1 << " -> " << idx2 << '\n';
				}
			}
		}
	}

	static Permutation<N> toPermutationN(_Center_edges<N, false> &ce, Permutation<N> &in) {
		Permutation<N> output(in);

		for (int i = 0; i < 6; i++) { // faces
			for (int j = 0; j < _Center_edges_Impl<N, false>::number_of_indices_per_face; j++) { // per face indices
				int idx = _Center_edges_Impl<N, false>::number_of_indices_per_face * i + j;
				int p_value1 = ce.m_perm[idx];
				int p_value2 = idx;
				int face1, face2, layer1,layer2,direction1,direction2,dir_idx1,dir_idx2;

				_Center_edges_Impl<N, false>::compute_values(p_value1, face1, layer1, direction1, dir_idx1);
				_Center_edges_Impl<N, false>::compute_values(p_value2, face2, layer2, direction2, dir_idx2);

				int idx1, idx2;
				idx1 = idx2 = N * (N - 1) / 2 + (N - 1) / 2;
				idx1 += face1 * N * N;
				idx2 += face2 * N * N;

				idx1 += _Center_edges_Impl<N, false>::adjustment(layer1 - 1, direction1, dir_idx1);
				idx2 += _Center_edges_Impl<N, false>::adjustment(layer2 - 1, direction2, dir_idx2);
				if (idx1 != idx2) 
					output._components[idx1] = in._components[idx2];

			}
		}
		return output;
	}

};

template<int N>
struct _Center_edges_Impl<N, true> {
	static const int number_of_indices_per_face = (N - 2) * (N - 4);
	static const int number_of_indices = 6 * number_of_indices_per_face;
	static const int number_of_layers = (N - 2) / 2;


	static inline int NF(int layer, int index) {
		return 4 * (layer - 1) * (layer - 2)
			+ index;
	}

	static inline int EF(int layer, int index) {
		return 4 * (layer - 1) * (layer - 2)
			+ 2 * (layer - 1) + index;
	}

	static inline int SF(int layer, int index) {
		return 4 * (layer - 1) * (layer - 2)
			+ 2 * 2 * (layer - 1) + index;
	}

	static inline int WF(int layer, int index)
	{
		return 4 * (layer - 1) * (layer - 2)
			+ 3 * 2 * (layer - 1) + index;
	}


	static void _center_edges_impl(_Center_edges<N, true> &ce) {

		static_assert(N % 2 == 0, "N must be even.");
		static_assert(N >= 6, "There are no center edges for smaller cubes thant 6x6x6.");

		for (int i = 0; i < _Center_edges<N, true>::number_of_indices; i++)
			ce.m_perm[i] = i;
	}
	
	static void apply_Face(_Center_edges<N, true> &ce, const enum Faces::faces &f) {
		for (int k = 2; k <= _Center_edges<N, true>::number_of_layers; k++) {
			for (int t = 0; t < 2 * k - 2; t++) {
				//			 NF  ->  EF  ->  SF  ->  WF
				//			k, t -> k, t -> k, t -> k, t
				ce.apply_cycle(
					_Center_edges<N, true>::face_NF(f, k, t),
					_Center_edges<N, true>::face_EF(f, k, t),
					_Center_edges<N, true>::face_SF(f, k, t),
					_Center_edges<N, true>::face_WF(f, k, t)
				);

			}
		}

	}

	static void disp_cube_impl(_Center_edges<N, true> &ce, std::ostream &os) {
		// U Face

		// 1st row

		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';
		//
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// 2nd -... row
		for (int k = _Center_edges<N, true>::number_of_layers; k > 0; k--) {
			// skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::U, t, t + k - 2)] 
 								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::U, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::U, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';
		}

		// row + 1 - last - 1
		for (int k = 1; k <= _Center_edges<N, true>::number_of_layers; k++) {
			// skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::U, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::U, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::U, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';

		}
		// last row

		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';
		//
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		//LFRB face
		// 1st row

		//
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}

		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// 2nd -... row
		for (int k = _Center_edges<N, true>::number_of_layers; k > 0; k--) {

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::L, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::L, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::L, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::F, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::F, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::F, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::R, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::R, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::R, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::B, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::B, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::B, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';
		}

		// row + 1 - last - 1
		for (int k = 1; k <= _Center_edges<N, true>::number_of_layers; k++) {

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::L, t, t - k - 1)] 
							/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::L, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::L, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::F, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::F, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::F, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::R, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::R, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::R, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';

			os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::B, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::B, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::B, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';

		}
		// last row

		
		//
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < N; i++)
				os << '.';
			os << ' ';
		}
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		//D face
		// 1st row

		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';
		//
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';

		// 2nd -... row
		for (int k = _Center_edges<N, true>::number_of_layers; k > 0; k--) {
			// skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::D, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 0; t < 2 * (k - 1); t++)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_NF(Faces::D, k, t)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::D, t, t - k - 1)] 
							/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';
		}

		// row + 1 - last - 1
		for (int k = 1; k <= _Center_edges<N, true>::number_of_layers; k++) {
			// skip
			for (int i = 0; i <= N; i++)
				os << ' ';

			os << '.';

			for (int t = _Center_edges<N, true>::number_of_layers; t > k; t--) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_WF(Faces::D, t, t - k - 1)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}
			os << '.';

			// middle
			for (int t = 2 * (k - 1) - 1; t >= 0; t--)
				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_SF(Faces::D, k, t)] 
						/ _Center_edges<N, true>::number_of_indices_per_face];

			os << '.';

			for (int t = k + 1; t <= _Center_edges<N, true>::number_of_layers; t++) {

				os << Faces::labels[ce.m_perm[_Center_edges<N, true>::face_EF(Faces::D, t, t + k - 2)] 
								/ _Center_edges<N, true>::number_of_indices_per_face];

			}

			os << '.';
			os << '\n';

		}
		// last row

		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';
		//
		for (int i = 0; i < N; i++)
			os << '.';
		os << '\n';
	}

	static void compute_values(int orig_idx, 
		int &face, int &layer, int &direction, int &dir_idx) {
		
			face = orig_idx / _Center_edges_Impl<N, true>::number_of_indices_per_face;

			int p_face_idx = orig_idx % _Center_edges_Impl<N, true>::number_of_indices_per_face;

			layer = (floor(sqrt(p_face_idx + 1)) + 1) / 2;

			int layer_idx = p_face_idx - 4 * layer * (layer - 1);

			direction = layer_idx / (2 * layer);
			dir_idx = layer_idx % (2 * layer);
	}

	static int adjustment(int layer, int direction, int dir_idx) {
		int adj = 0;
		switch (direction) {
			// North
			case 0:
				adj = -layer * N + dir_idx - layer + 1;
				break;

			// East
			case 1:
				adj = (dir_idx - layer + 1) * N + layer + 1;
				break;
			// South
			case 2:
				adj = (layer + 1) * N + layer - dir_idx;
				break;
			// West
			case 3:
				adj = (layer - dir_idx) * N - layer;
				break;
			default:
				break;
		};

		return adj;
	}


	static void toPermutationN(_Center_edges<N, true> &ce) {
		static const char dir_labels[] = {'N', 'E', 'S', 'W'};
		for (int i = 0; i < 6; i++) { // faces
			for (int j = 0; j < _Center_edges_Impl<N, true>::number_of_indices_per_face; j++) { // per face indices
				int idx = _Center_edges_Impl<N, true>::number_of_indices_per_face * i + j;
				int p_value1 = ce.m_perm[idx];
				int p_value2 = idx;
				int face1, face2, layer1,layer2,direction1,direction2,dir_idx1,dir_idx2;

				_Center_edges_Impl<N, true>::compute_values(p_value1, face1, layer1, direction1, dir_idx1);
				_Center_edges_Impl<N, true>::compute_values(p_value2, face2, layer2, direction2, dir_idx2);

				int idx1, idx2;
				idx1 = idx2 = (N / 2 - 1) * N + (N / 2 - 1);
				idx1 += face1 * N * N;
				idx2 += face2 * N * N;

				idx1 += _Center_edges_Impl<N, true>::adjustment(layer1, direction1, dir_idx1);
				idx2 += _Center_edges_Impl<N, true>::adjustment(layer2, direction2, dir_idx2);
				if (idx1 != idx2) {
					std::cout << Faces::labels[face1] << "(" << layer1 << ", " << dir_labels[ direction1 ] << ", " << dir_idx1 << ") -> " 	
						  << Faces::labels[face2] << "(" << layer2 << ", " << dir_labels[ direction2 ] << ", " << dir_idx2 << ")\n";

					std::cout << idx1 << " -> " << idx2 << '\n';
				}
			}
		}
	}

	static Permutation<N> toPermutationN(_Center_edges<N, true> &ce, Permutation<N> &in) {
		Permutation<N> output(in);

		for (int i = 0; i < 6; i++) { // faces
			for (int j = 0; j < _Center_edges_Impl<N, true>::number_of_indices_per_face; j++) { // per face indices
				int idx = _Center_edges_Impl<N, true>::number_of_indices_per_face * i + j;
				int p_value1 = ce.m_perm[idx];
				int p_value2 = idx;
				int face1, face2, layer1,layer2,direction1,direction2,dir_idx1,dir_idx2;

				_Center_edges_Impl<N, true>::compute_values(p_value1, face1, layer1, direction1, dir_idx1);
				_Center_edges_Impl<N, true>::compute_values(p_value2, face2, layer2, direction2, dir_idx2);

				int idx1, idx2;
				idx1 = idx2 = (N / 2 - 1) * N + (N / 2 - 1);
				idx1 += face1 * N * N;
				idx2 += face2 * N * N;

				idx1 += _Center_edges_Impl<N, true>::adjustment(layer1, direction1, dir_idx1);
				idx2 += _Center_edges_Impl<N, true>::adjustment(layer2, direction2, dir_idx2);
				if (idx1 != idx2) 
					output._components[idx1] = in._components[idx2];
			}
		}

		return output;
	}
};

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_cycle(int(&cycle)[4]) {

	int tmp = m_perm[cycle[3]];
	for (int j = 2; j >= 0; j--)
		m_perm[cycle[j + 1]] = m_perm[cycle[j]];
	m_perm[cycle[0]] = tmp;

}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_cycle(int idx1, int idx2, int idx3, int idx4) {

	int tmp_array[] = { idx1, idx2, idx3, idx4 };

	apply_cycle(tmp_array);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_Face(const enum Faces::faces &f) {
	_Center_edges_Impl<N, isEven>::apply_Face(*this, f);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_L() {
	apply_Face(Faces::L);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_R() {
	apply_Face(Faces::R);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_F() {
	apply_Face(Faces::F);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_B() {
	apply_Face(Faces::B);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_U() {
	apply_Face(Faces::U);
}

template <int N, bool isEven>
void _Center_edges<N, isEven>::apply_D() {
	apply_Face(Faces::D);
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_ML() {
	_Center_edges_Impl_K<N, K, isEven>::apply_ML(*this);
	
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_MR() {
	_Center_edges_Impl_K<N, K, isEven>::apply_MR(*this);
	
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_MF() {
	_Center_edges_Impl_K<N, K, isEven>::apply_MF(*this);
	
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_MB() {
	_Center_edges_Impl_K<N, K, isEven>::apply_MB(*this);
	
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_MU() {
	_Center_edges_Impl_K<N, K, isEven>::apply_MU(*this);
	
}

template <int N, bool isEven>
template <int K>
void _Center_edges<N, isEven>::apply_MD() {
	_Center_edges_Impl_K<N, K, isEven>::apply_MD(*this);
	
}

template <int N, int K>
struct _Center_edges_Impl_K<N, K, false> {

	static void apply_ML(_Center_edges<N, false> &ce) {
		static_assert(K >= 0, "K must be non-negative.");
		static_assert(K <= _Center_edges_Impl<N, false>::number_of_layers, "K must be less than or equal to number of layers.");

		// U face cubes

		// West cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {

			ce.apply_cycle(
				_Center_edges<N, false>::face_WF(Faces::U, K, t),
				_Center_edges<N, false>::face_WF(Faces::F, K, t),
				_Center_edges<N, false>::face_WF(Faces::D, K, t),
				_Center_edges<N, false>::face_EF(Faces::B, K, t)
			);
		}

		// North cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_NF(Faces::U, t, t - K - 1),
				_Center_edges<N, false>::face_NF(Faces::F, t, t - K - 1),
				_Center_edges<N, false>::face_NF(Faces::D, t, t - K - 1),
				_Center_edges<N, false>::face_SF(Faces::B, t, t - K - 1)
			);
		}

		// South cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_SF(Faces::U, t, t + K - 1),
				_Center_edges<N, false>::face_SF(Faces::F, t, t + K - 1),
				_Center_edges<N, false>::face_SF(Faces::D, t, t + K - 1),
				_Center_edges<N, false>::face_NF(Faces::B, t, t + K - 1)
			);
		}

	}

	static void apply_MR(_Center_edges<N, false> &ce) {
		static_assert(K >= 0, "K must be non-negative.");
		static_assert(K <= _Center_edges_Impl<N, false>::number_of_layers, "K must be less than or equal to number of layers.");

		// U face cubes

		// East cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_EF(Faces::U, K, t),
				_Center_edges<N, false>::face_WF(Faces::B, K, t),
				_Center_edges<N, false>::face_EF(Faces::D, K, t),
				_Center_edges<N, false>::face_EF(Faces::F, K, t)
			);
		}

		// North cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_NF(Faces::U, t, t + K - 1),
				_Center_edges<N, false>::face_SF(Faces::B, t, t + K - 1),
				_Center_edges<N, false>::face_NF(Faces::D, t, t + K - 1),
				_Center_edges<N, false>::face_NF(Faces::F, t, t + K - 1)
			);
		}

		// South cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_SF(Faces::U, t, t - K - 1),
				_Center_edges<N, false>::face_NF(Faces::B, t, t - K - 1),
				_Center_edges<N, false>::face_SF(Faces::D, t, t - K - 1),
				_Center_edges<N, false>::face_SF(Faces::F, t, t - K - 1)
			);
		}
	}

	static void apply_MF(_Center_edges<N, false> &ce) {

		// R face cubes

		// West cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_WF(Faces::R, K, t),
				_Center_edges<N, false>::face_NF(Faces::D, K, t),
				_Center_edges<N, false>::face_EF(Faces::L, K, t),
				_Center_edges<N, false>::face_SF(Faces::U, K, t)
			);
		}

		// North cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_NF(Faces::R, t, t - K - 1),
				_Center_edges<N, false>::face_EF(Faces::D, t, t - K - 1),
				_Center_edges<N, false>::face_SF(Faces::L, t, t - K - 1),
				_Center_edges<N, false>::face_WF(Faces::U, t, t - K - 1)
			);
		}

		// South cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_SF(Faces::R, t, t + K - 1),
				_Center_edges<N, false>::face_WF(Faces::D, t, t + K - 1),
				_Center_edges<N, false>::face_NF(Faces::L, t, t + K - 1),
				_Center_edges<N, false>::face_EF(Faces::U, t, t + K - 1)
			);
		}

	}

	static void apply_MB(_Center_edges<N, false> &ce) {

		// L face cubes

		// West cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_WF(Faces::L, K, t),
				_Center_edges<N, false>::face_SF(Faces::D, K, t),
				_Center_edges<N, false>::face_EF(Faces::R, K, t),
				_Center_edges<N, false>::face_NF(Faces::U, K, t)
			);
		}

		// North cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_NF(Faces::L, t, t - K - 1),
				_Center_edges<N, false>::face_WF(Faces::D, t, t - K - 1),
				_Center_edges<N, false>::face_SF(Faces::R, t, t - K - 1),
				_Center_edges<N, false>::face_EF(Faces::U, t, t - K - 1)
			);
		}

		// South cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_SF(Faces::L, t, t + K - 1),
				_Center_edges<N, false>::face_EF(Faces::D, t, t + K - 1),
				_Center_edges<N, false>::face_NF(Faces::R, t, t + K - 1),
				_Center_edges<N, false>::face_WF(Faces::U, t, t + K - 1)
			);
		}

	}

	static void apply_MU(_Center_edges<N, false> &ce) {

		// F face cubes

		// North cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_NF(Faces::F, K, t),
				_Center_edges<N, false>::face_NF(Faces::L, K, t),
				_Center_edges<N, false>::face_NF(Faces::B, K, t),
				_Center_edges<N, false>::face_NF(Faces::R, K, t)
			);
		}

		// West cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_WF(Faces::F, t, t + K - 1),
				_Center_edges<N, false>::face_WF(Faces::L, t, t + K - 1),
				_Center_edges<N, false>::face_WF(Faces::B, t, t + K - 1),
				_Center_edges<N, false>::face_WF(Faces::R, t, t + K - 1)
			);
		}

		// East cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_EF(Faces::F, t, t - K - 1),
				_Center_edges<N, false>::face_EF(Faces::L, t, t - K - 1),
				_Center_edges<N, false>::face_EF(Faces::B, t, t - K - 1),
				_Center_edges<N, false>::face_EF(Faces::R, t, t - K - 1)
			);
		}

	}

	static void apply_MD(_Center_edges<N, false> &ce) {

		// F face cubes

		// South cubes 	
		for (int t = 0; t < 2 * K - 1; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_SF(Faces::F, K, t),
				_Center_edges<N, false>::face_SF(Faces::R, K, t),
				_Center_edges<N, false>::face_SF(Faces::B, K, t),
				_Center_edges<N, false>::face_SF(Faces::L, K, t)
			);
		}

		// West cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_WF(Faces::F, t, t - K - 1),
				_Center_edges<N, false>::face_WF(Faces::R, t, t - K - 1),
				_Center_edges<N, false>::face_WF(Faces::B, t, t - K - 1),
				_Center_edges<N, false>::face_WF(Faces::L, t, t - K - 1)
			);
		}

		// East cubes
		for (int t = K + 1; t <= _Center_edges<N, false>::number_of_layers; t++) {
			ce.apply_cycle(
				_Center_edges<N, false>::face_EF(Faces::F, t, t + K - 1),
				_Center_edges<N, false>::face_EF(Faces::R, t, t + K - 1),
				_Center_edges<N, false>::face_EF(Faces::B, t, t + K - 1),
				_Center_edges<N, false>::face_EF(Faces::L, t, t + K - 1)
			);
		}

	}
};


template <int N, int K>
struct _Center_edges_Impl_K<N, K, true> {
	static void apply_ML(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_NF(Faces::U, k, k - K - 1),
				_Center_edges<N, true>::face_NF(Faces::F, k, k - K - 1),
				_Center_edges<N, true>::face_NF(Faces::D, k, k - K - 1),	
				_Center_edges<N, true>::face_SF(Faces::B, k, k - K - 1)
			);
		}
		for (int k = 2 * K - 3; k >= 0; k--) {
			// U-WF(K, k) -> F-WF(K, k) -> D-WF(K, k) -> B-EF(K, k)

			ce.apply_cycle(
				_Center_edges<N, true>::face_WF(Faces::U, K, k),	
				_Center_edges<N, true>::face_WF(Faces::F, K, k),
				_Center_edges<N, true>::face_WF(Faces::D, K, k),
				_Center_edges<N, true>::face_EF(Faces::B, K, k)
			);
		}

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {


			ce.apply_cycle(
				_Center_edges<N, true>::face_SF(Faces::U, k, k + K - 2), 
				_Center_edges<N, true>::face_SF(Faces::F, k, k + K - 2),
				_Center_edges<N, true>::face_SF(Faces::D, k, k + K - 2),
				_Center_edges<N, true>::face_NF(Faces::B, k, k + K - 2)
			);
		}

	}

	static void apply_MR(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_NF(Faces::U, k, k + K - 2),	
				_Center_edges<N, true>::face_SF(Faces::B, k, k + K - 2),
				_Center_edges<N, true>::face_NF(Faces::D, k, k + K - 2),
				_Center_edges<N, true>::face_NF(Faces::F, k, k + K - 2)
			);
		}
		for (int k = 2 * K - 3; k >= 0; k--) {
			// U-WF(K, k) -> F-WF(K, k) -> D-WF(K, k) -> B-EF(K, k)

			ce.apply_cycle(
				_Center_edges<N, true>::face_EF(Faces::U, K, k),	
				_Center_edges<N, true>::face_WF(Faces::B, K, k),
				_Center_edges<N, true>::face_EF(Faces::D, K, k),
				_Center_edges<N, true>::face_EF(Faces::F, K, k)
			);
		}

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_SF(Faces::U, k, k - K - 1),	
				_Center_edges<N, true>::face_NF(Faces::B, k, k - K - 1),
				_Center_edges<N, true>::face_SF(Faces::D, k, k - K - 1),
				_Center_edges<N, true>::face_SF(Faces::F, k, k - K - 1)
			);
		}

	}

	static void apply_MF(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_NF(Faces::R, k, k - K - 1),	
				_Center_edges<N, true>::face_EF(Faces::D, k, k - K - 1),
				_Center_edges<N, true>::face_SF(Faces::L, k, k - K - 1),	
				_Center_edges<N, true>::face_WF(Faces::U, k, k - K - 1)
			);

		}

		for (int k = 2 * K - 3; k >= 0; k--) {
			ce.apply_cycle(
				_Center_edges<N, true>::face_WF(Faces::R, K, k),
				_Center_edges<N, true>::face_NF(Faces::D, K, k),	
				_Center_edges<N, true>::face_EF(Faces::L, K, k),
				_Center_edges<N, true>::face_SF(Faces::U, K, k)
			);
		}

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_SF(Faces::R, k, k + K - 2),
				_Center_edges<N, true>::face_WF(Faces::D, k, k + K - 2),
				_Center_edges<N, true>::face_NF(Faces::L, k, k + K - 2),
				_Center_edges<N, true>::face_EF(Faces::U, k, k + K - 2)
			);
	
		}

	}

	static void apply_MB(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_NF(Faces::R, k, k + K - 2),
				_Center_edges<N, true>::face_WF(Faces::U, k, k + K - 2),	
				_Center_edges<N, true>::face_SF(Faces::L, k, k + K - 2),
				_Center_edges<N, true>::face_EF(Faces::D, k, k + K - 2)
			);
		}

		for (int k = 2 * K - 3; k >= 0; k--) {
			ce.apply_cycle(
				_Center_edges<N, true>::face_EF(Faces::R, K, k),
				_Center_edges<N, true>::face_NF(Faces::U, K, k),
				_Center_edges<N, true>::face_WF(Faces::L, K, k),
				_Center_edges<N, true>::face_SF(Faces::D, K, k)
			);

		}

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_SF(Faces::R, k, k - K - 1),
				_Center_edges<N, true>::face_EF(Faces::U, k, k - K - 1),
				_Center_edges<N, true>::face_NF(Faces::L, k, k - K - 1),
				_Center_edges<N, true>::face_WF(Faces::D, k, k - K - 1)
			);
		}

	}

	static void apply_MU(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_WF(Faces::F, k, k + K - 2),
				_Center_edges<N, true>::face_WF(Faces::L, k, k + K - 2),
				_Center_edges<N, true>::face_EF(Faces::B, k, k - K - 1),
				_Center_edges<N, true>::face_WF(Faces::R, k, k + K - 2)	
			);
		}


		for (int k = 2 * K - 3; k >= 0; k--) {
			ce.apply_cycle(
				_Center_edges<N, true>::face_NF(Faces::F, K, k),
				_Center_edges<N, true>::face_NF(Faces::L, K, k),
				_Center_edges<N, true>::face_NF(Faces::B, K, 2 * K - 3 - k),
				_Center_edges<N, true>::face_NF(Faces::R, K, k)
			);
		}


		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_EF(Faces::F, k, k - K - 1),
				_Center_edges<N, true>::face_EF(Faces::L, k, k - K - 1),
				_Center_edges<N, true>::face_WF(Faces::B, k, k + K - 2),
				_Center_edges<N, true>::face_EF(Faces::R, k, k - K - 1)
			);
		}

	}

	static void apply_MD(_Center_edges<N, true> &ce) {
		static_assert(K >= 1, "K must be positive.");
		static_assert(K <= _Center_edges_Impl<N, true>::number_of_layers, "K must less than number of layers.");

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_WF(Faces::F, k, k - K - 1),	
				_Center_edges<N, true>::face_WF(Faces::R, k, k - K - 1),
				_Center_edges<N, true>::face_EF(Faces::B, k, k + K - 2), 
				_Center_edges<N, true>::face_WF(Faces::L, k, k - K - 1)
			);
		}

		for (int k = 2 * K - 3; k >= 0; k--) {
			ce.apply_cycle(
				_Center_edges<N, true>::face_SF(Faces::F, K, k),
				_Center_edges<N, true>::face_SF(Faces::R, K, k),	
				_Center_edges<N, true>::face_SF(Faces::B, K, 2 * K - 3 - k),	
				_Center_edges<N, true>::face_SF(Faces::L, K, k)
			);
		}

		for (int k = _Center_edges<N, true>::number_of_layers; k > K; k--) {

			ce.apply_cycle(
				_Center_edges<N, true>::face_EF(Faces::F, k, k + K - 2),
				_Center_edges<N, true>::face_EF(Faces::R, k, k + K - 2),
				_Center_edges<N, true>::face_WF(Faces::B, k, k - K - 1),
				_Center_edges<N, true>::face_EF(Faces::L, k, k + K - 2)
			);

		}
	}


};

}
