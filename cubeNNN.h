#pragma once
#ifndef __CUBENNN_H__
#define __CUBENNN_H__

#include <ostream>
#include <iostream>

template<int N>
struct Permutation {
	static const int _count = 6 * N * N;
	int _components[Permutation::_count]; // 6 * N x N

	Permutation();
	Permutation(const Permutation &_perm);
	Permutation(const int init[Permutation::_count]);
	Permutation inv();

	void disp_elem(std::ostream &os, int i);
	void disp_perm(std::ostream &os = std::cout);
	void disp_perm_reduced(std::ostream &os = std::cout);
	void disp_cube(std::ostream &os = std::cout);
	void disp_cube_fancy(std::ostream &os = std::cout);

	template<int U>
	friend Permutation<U> operator*(const Permutation<U> &perm_a, const Permutation<U> &perm_b);

	template<int U>
	friend Permutation<U> operator!(const Permutation<U> &perm);

	int parity();
	int parity(int length, int subgroup[]);

	bool operator!=(const Permutation &perm);
	bool operator==(const Permutation &perm);
	bool is_identity();
	int order();
	
};

// abstract interface - must be defined for particular N

// U towards B
template <int N>
void orient_x(Permutation<N> &cu);

// U towards F
template <int N>
void orient_x_prime(Permutation<N> &cu);

// F towards L
template <int N>
void orient_y(Permutation<N> &cu);

// F towards R
template <int N>
void orient_y_prime(Permutation<N> &cu);

// U towards R
template <int N>
void orient_z(Permutation<N> &cu);

// U towards R
template <int N>
void orient_z_prime(Permutation<N> &cu);
//

template<int N>
bool Permutation<N>::is_identity() {
	for (int i = 0; i < _count; i++) {
		if (_components[i] != i)
			return false;	
	}

	return true;
	
}

template<int N>
bool Permutation<N>::operator!=(const Permutation<N> &perm) {
	for (int i = 0; i < _count; i++) {
		if (_components[i] != perm._components[i])
			return true;	
	}

	return false;
}

template<int N>
bool Permutation<N>::operator==(const Permutation<N> &perm) {
	return !(*this!=perm);
}

template<int N>
int Permutation<N>::order() {
	int ord = 1;

	Permutation<N> res = *this;
	
	while (!res.is_identity()) {
		res = *this * res;
		ord++;
	}

	return ord;

}

template<int N>
Permutation<N>::Permutation() {
	for (int i = 0; i < _count; i++)
		_components[i] = i;
}

template<int N>
Permutation<N>::Permutation(const Permutation<N> &_perm) {
	for (int i = 0; i < _count; i++)
		_components[i] = _perm._components[i];
}

template<int N>
Permutation<N>::Permutation(const int init[Permutation<N>::_count]) {
	for (int i = 0; i < _count; i++)
		_components[i] = init[i];
}

template<int N>
Permutation<N> Permutation<N>::inv() {
	Permutation<N> outcome;
	for (int i = 0; i < _count; i++)
		outcome._components[_components[i]] = i;
	return outcome;
}


template<int N>
int Permutation<N>::parity() {
	int par = +1 ;
	for (int i = 0; i < _count - 1; i++)
	for (int j = i + 1; j < _count; j++)
		if (_components[i] > _components[j]) 
			par *= -1;

	return par;
}

template<int N>
int Permutation<N>::parity(int length, int subgroup[]) {
	int par = +1 ;
	for (int i = 0; i < length - 1; i++)
	for (int j = i + 1; j < length; j++)
		if (
	(subgroup[i] < subgroup[j] && _components[subgroup[i]] > _components[subgroup[j]]) 
||
	(subgroup[i] > subgroup[j] && _components[subgroup[i]] < _components[subgroup[j]])
		 ) 
			par *= -1;

	return par;
}


template<int N>
Permutation<N> operator!(const Permutation<N> &perm) {
	Permutation<N> outcome;
	for (int i = 0; i < Permutation<N>::_count; i++)
		outcome._components[perm._components[i]] = i;
	return outcome;
}

template<int N>
Permutation<N> operator*(const Permutation<N> &perm_a, const Permutation<N> &perm_b) {
	// perm_b (*this)
	Permutation<N> outcome;
	for (int i = 0; i < Permutation<N>::_count; i++) {
		outcome._components[i] = perm_b._components[perm_a._components[i]];
	}
	return outcome;
}

template<int N>
void Permutation<N>::disp_perm(std::ostream &os) {
	for (int i = 0; i < _count; i++)
		os << (_components[i] + 1) << ", ";
	os << '\n';
}

template<int N>
void Permutation<N>::disp_perm_reduced(std::ostream &os) {
	for (int i = 0; i < _count; i++)
		if (i != _components[i]) {
			os << i + 1 << " -> " << (_components[i] + 1) << '\n';
		}
}

template<int N>
void Permutation<N>::disp_elem(std::ostream &os, int i) {
	os << (i / (N * N)  + 1);
}

template<int N>
void Permutation<N>::disp_cube(std::ostream &os) {
	int inv[_count];
	for (int i = 0; i < _count; i++)
		inv[_components[i]] = i;
	
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++)
			os << " ";
		for (int i = 0 + N * j; i < N + N* j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}
	
	for (int j = 0 ; j < N; j++) {
		for (int i = N * N + N * j; i < N * N + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 2 * N * N + N * j; i < 2 * N * N + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 3 * N * N + N * j; i < 3 * N * N + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 4 * N * N + N * j; i < 4 * N * N + N + N * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++)
			os << " ";
		for (int i = 5* N *N + N * j; i < 5 * N * N + N + N * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = N - 1; j >= 0; j--) {
		for (int k = 0; k < N; k++)
			os << " ";
		for (int i = 4 * N * N + N - 1 + N * j; i >= 4 * N * N + N * j; i--)
			disp_elem(os, inv[i]);
		os << '\n';
	}
}

template<int N>
void Permutation<N>::disp_cube_fancy(std::ostream &os) {
	int inv[_count];
	for (int i = 0; i < _count; i++)
		inv[_components[i]] = i;
	
	for (int j = 0; j < N; j++) {
		if (j % 2 == 0) {
			for (int k = 0; k < N + N / 2 + 2; k++)
				os << " ";
			for (int k = 0; k < N + N / 2 + 3; k++)
				os << "-";
			os << '\n';
		}
		for (int k = 0; k < N + N / 2 + 2; k++)
			os << " ";
		os << "| ";
		for (int i = 0 + N * j; i < N + N* j; i++) {
			disp_elem(os, inv[i]);
			if (i % 2)
				os << " ";
		}
		os << "|";

		os << '\n';
	}
	
	for (int j = 0 ; j < N; j++) {
		if (j % 2 == 0) {
			for (int j = 0; j < 6*N + 9; j++)
				os << "-";
			os << '\n';
		}
		os << "| ";
		for (int i = N * N + N * j; i < N * N + N + N * j; i++) {
			disp_elem(os, inv[i]);
			if (i % 2)
				os << " ";
		}
		os << "| ";
		for (int i = 2 * N * N + N * j; i < 2 * N * N + N + N * j; i++) {
			disp_elem(os, inv[i]);
			if (i % 2)
				os << " ";
		}
		os << "| ";
		for (int i = 3 * N * N + N * j; i < 3 * N * N + N + N * j; i++) {
			disp_elem(os, inv[i]);
			if (i % 2)
				os << " ";
		}
		os << "| ";
		for (int i = 4 * N * N + N * j; i < 4 * N * N + N + N * j; i++) {
			disp_elem(os, inv[i]);
	
			if (i % 2)
				os << " ";
		}
		os << "|";
		os << '\n';
	}

	for (int j = 0; j < 6*N + 9;j++)
		os << "-";
	os << '\n';

	for (int j = 0; j < N; j++) {
		if (j && j % 2 == 0) {
			for (int k = 0; k < N + N / 2 + 2; k++)
				os << " ";
			for (int k = 0; k < N + N / 2 + 3; k++)
				os << "-";
			os << '\n';
		}
		for (int k = 0; k < N + N / 2 + 2; k++)
			os << " ";
		os << "| ";
		for (int i = 5* N *N + N * j; i < 5 * N * N + N + N * j; i++) {
			disp_elem(os, inv[i]);

			if (i % 2)
				os << " ";
		}
		os << "|";
		os << '\n';
	}

	for (int j = N - 1; j >= 0; j--) {
		if (j % 2 == 1) {
			for (int k = 0; k < N + N / 2 + 2; k++)
				os << " ";
			for (int k = 0; k < N + N / 2 + 3; k++)
				os << "-";
			os << '\n';
		}
		for (int k = 0; k < N + N / 2 + 2; k++)
			os << " ";
		int t = 0;
		os << "| ";
		for (int i = 4 * N * N + N - 1 + N * j; i >= 4 * N * N + N * j; i--) {
			disp_elem(os, inv[i]);
			if (t % 2)
				os << " ";
			t = 1- t;
		}

		os << '|';
		os << '\n';

	}
		for (int k = 0; k < N + N / 2 + 2; k++)
			os << " ";
		for (int k = 0; k < N + N / 2 + 3; k++)
			os << "-";
		os << '\n';
}

#endif
