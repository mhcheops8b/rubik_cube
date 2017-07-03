// Cube444.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "_cube555.h"

int const N = 5;
#if 0
int const N2 = N * N;
struct Permutation150 {
	static const int _count = 150;
	int _components[Permutation150::_count]; // 6 * 5 x 5
						 // computes composition of permutations *this and perm_b
	Permutation150();
	//Permutation150(Permutation150 _perm);
	Permutation150(const Permutation150 &_perm);
	Permutation150(const int init[Permutation150::_count]);
//	Permutation150 operator*(const Permutation150 &perm_b);
	Permutation150 inv();
	//static const Permutation150 _I;
	//static const Permutation150 _D;

	void disp_elem(std::ostream &os, int i);
	void disp_perm(std::ostream &os);
	void disp_perm_reduced(std::ostream &os);
	void disp_cube(std::ostream &os);
	friend Permutation150 operator*(const Permutation150 &perm_a, const Permutation150 &perm_b);
	friend Permutation150 operator!(const Permutation150 &perm);

	int parity();
	int parity(int length, int subgroup[]);
	bool operator!=(const Permutation150 &perm);
};

bool Permutation150::operator!=(const Permutation150 &perm) {
	for (int i = 0; i < Permutation150::_count; i++)
		if (_components[i] != perm._components[i])
			return true;

	return false;
}

int Permutation150::parity() {
	int par = +1 ;
	for (int i = 0; i < _count - 1; i++)
	for (int j = i + 1; j < _count; j++)
		if (_components[i] > _components[j]) 
			par *= -1;

	return par;
}

int Permutation150::parity(int length, int subgroup[]) {
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

Permutation150 Permutation150::inv() {
	Permutation150 outcome;
	for (int i = 0; i < _count; i++)
		outcome._components[_components[i]] = i;
	return outcome;
}

Permutation150 operator!(const Permutation150 &perm) {
	Permutation150 outcome;
	for (int i = 0; i < Permutation150::_count; i++)
		outcome._components[perm._components[i]] = i;
	return outcome;
}

void Permutation150::disp_perm(std::ostream &os) {
	for (int i = 0; i < _count; i++)
		os << (_components[i] + 1) << ", ";
	os << '\n';
}

void Permutation150::disp_perm_reduced(std::ostream &os) {
	for (int i = 0; i < _count; i++)
		if (i != _components[i]) {
			os << i + 1 << " -> " << (_components[i] + 1) << '\n';
		}
}

void Permutation150::disp_elem(std::ostream &os, int i) {
	os << (i / N2  + 1);
}
void Permutation150::disp_cube(std::ostream &os) {
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
		for (int i = N2 + N * j; i < N2 + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 2*N2 + N * j; i < 2*N2 + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 3*N2 + N * j; i < 3*N2 + N + N * j; i++)
			disp_elem(os, inv[i]);
		for (int i = 4*N2 + N * j; i < 4*N2 + N + N * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++)
			os << " ";
		for (int i = 5*N2 + N * j; i < 5*N2 + N + 5 * j; i++)
			disp_elem(os, inv[i]);
		os << '\n';
	}

	for (int j = N - 1; j >= 0; j--) {
		for (int k = 0; k < N; k++)
			os << " ";
		for (int i = 4*N2 + N - 1 + 5 * j; i >= 4*N2 + N * j; i--)
			disp_elem(os, inv[i]);
		os << '\n';
	}
}

//TODO
const int Arr_I[Permutation150::_count] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 
	124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 
	136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 
	148, 149
};

const int Arr__L[Permutation150::_count] = {
	 50,  1,  2,  3,  4, 55,  6,  7,  8,  9, 60, 11, 12, 13, 14, 
	 65, 16, 17, 18, 19, 70, 21, 22, 23, 24, 29, 34, 39, 44, 49, 
	 28, 33, 38, 43, 48, 27, 32, 37, 42, 47, 26, 31, 36, 41, 46, 
	 25, 30, 35, 40, 45,125, 51, 52, 53, 54,130, 56, 57, 58, 59, 
	135, 61, 62, 63, 64,140, 66, 67, 68, 69,145, 71, 72, 73, 74, 
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103, 20, 
	105,106,107,108, 15,110,111,112,113, 10,115,116,117,118,  5, 
	120,121,122,123,  0,124,126,127,128,129,119,131,132,133,134, 
	114,136,137,138,139,109,141,142,143,144,104,146,147,148,149
};

const int ArrML1[Permutation150::_count] = {
	  0, 51,  2,  3,  4,  5, 56,  7,  8,  9, 10, 61, 12, 13, 14, 
	 15, 66, 17, 18, 19, 20, 71, 22, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50,126, 52, 53, 54, 55,131, 57, 58, 59,
	 60,136, 62, 63, 64, 65,141, 67, 68, 69, 70,146, 72, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102, 21,104,
	105,106,107, 16,109,110,111,112, 11,114,115,116,117,  6,119,
	120,121,122,  1,124,125,123,127,128,129,130,118,132,133,134,
	135,113,137,138,139,140,108,142,143,144,145,103,147,148,149
};

const int ArrML2[Permutation150::_count] = {
	  0,  1, 52,  3,  4,  5,  6, 57,  8,  9, 10, 11, 62, 13, 14,
	 15, 16, 67, 18, 19, 20, 21, 72, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51,127, 53, 54, 55, 56,132, 58, 59,
	 60, 61,137, 63, 64, 65, 66,142, 68, 69, 70, 71,147, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101, 22,103,104,
	105,106, 17,108,109,110,111, 12,113,114,115,116,  7,118,119,
	120,121,  2,123,124,125,126,122,128,129,130,131,117,133,134,
	135,136,112,138,139,140,141,107,143,144,145,146,102,148,149
};

const int ArrMR2[Permutation150::_count] = {
	  0,  1,122,  3,  4,  5,  6,117,  8,  9, 10, 11,112, 13, 14,
	 15, 16,107, 18, 19, 20, 21,102, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51,  2, 53, 54, 55, 56,  7, 58, 59,
	 60, 61, 12, 63, 64, 65, 66, 17, 68, 69, 70, 71, 22, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,147,103,104,
	105,106,142,108,109,110,111,137,113,114,115,116,132,118,119,
	120,121,127,123,124,125,126, 52,128,129,130,131, 57,133,134,
	135,136, 62,138,139,140,141, 67,143,144,145,146, 72,148,149
};

const int ArrMR1[Permutation150::_count] = {
	  0,  1,  2,121,  4,  5,  6,  7,116,  9, 10, 11, 12,111, 14,
	 15, 16, 17,106, 19, 20, 21, 22,101, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51, 52,  3, 54, 55, 56, 57,  8, 59,
	 60, 61, 62, 13, 64, 65, 66, 67, 18, 69, 70, 71, 72, 23, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,148,102,103,104,
	105,143,107,108,109,110,138,112,113,114,115,133,117,118,119,
	120,128,122,123,124,125,126,127, 53,129,130,131,132, 58,134,
	135,136,137, 63,139,140,141,142, 68,144,145,146,147, 73,149
};

const int Arr__R[Permutation150::_count] = {
	  0,  1,  2,  3,120,  5,  6,  7,  8,115, 10, 11, 12, 13,110,
	 15, 16, 17, 18,105, 20, 21, 22, 23,100, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51, 52, 53,  4, 55, 56, 57, 58,  9,
	 60, 61, 62, 63, 14, 65, 66, 67, 68, 19, 70, 71, 72, 73, 24,
	 79, 84, 89, 94, 99, 78, 83, 88, 93, 98, 77, 82, 87, 92, 97,
	 76, 81, 86, 91, 96, 75, 80, 85, 90, 95,149,101,102,103,104,
	144,106,107,108,109,139,111,112,113,114,134,116,117,118,119,
	129,121,122,123,124,125,126,127,128, 54,130,131,132,133, 59,
	135,136,137,138, 64,140,141,142,143, 69,145,146,147,148, 74
};

const int Arr__F[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 75, 80, 85, 90, 95, 25, 26, 27, 28, 24,
	 30, 31, 32, 33, 23, 35, 36, 37, 38, 22, 40, 41, 42, 43, 21,
	 45, 46, 47, 48, 20, 54, 59, 64, 69, 74, 53, 58, 63, 68, 73,
	 52, 57, 62, 67, 72, 51, 56, 61, 66, 71, 50, 55, 60, 65, 70,
	129, 76, 77, 78, 79,128, 81, 82, 83, 84,127, 86, 87, 88, 89,
	126, 91, 92, 93, 94,125, 96, 97, 98, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124, 29, 34, 39, 44, 49,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMF1[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 76, 81, 86, 91, 96, 20, 21, 22, 23, 24, 25, 26, 27, 19, 29,
	 30, 31, 32, 18, 34, 35, 36, 37, 17, 39, 40, 41, 42, 16, 44,
	 45, 46, 47, 15, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75,134, 77, 78, 79, 80,133, 82, 83, 84, 85,132, 87, 88, 89,
	 90,131, 92, 93, 94, 95,130, 97, 98, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129, 28, 33, 38, 43, 48,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMF2[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 77, 82, 87, 92, 97,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 14, 28, 29,
	 30, 31, 13, 33, 34, 35, 36, 12, 38, 39, 40, 41, 11, 43, 44,
	 45, 46, 10, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76,139, 78, 79, 80, 81,138, 83, 84, 85, 86,137, 88, 89,
	 90, 91,136, 93, 94, 95, 96,135, 98, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	 27, 32, 37, 42, 47,140,141,142,143,144,145,146,147,148,149
};

const int ArrMB2[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 47, 42, 37, 32, 27,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,135, 28, 29,
	 30, 31,136, 33, 34, 35, 36,137, 38, 39, 40, 41,138, 43, 44,
	 45, 46,139, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 10, 78, 79, 80, 81, 11, 83, 84, 85, 86, 12, 88, 89,
	 90, 91, 13, 93, 94, 95, 96, 14, 98, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	 97, 92, 87, 82, 77,140,141,142,143,144,145,146,147,148,149
};

const int ArrMB1[Permutation150::_count] = {
	  0,  1,  2,  3,  4, 46, 41, 36, 31, 26, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,140, 27, 28, 29,
	 30,141, 32, 33, 34, 35,142, 37, 38, 39, 40,143, 42, 43, 44,
	 45,144, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 77,  5, 79, 80, 81, 82,  6, 84, 85, 86, 87,  7, 89,
	 90, 91, 92,  8, 94, 95, 96, 97,  9, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139, 98, 93, 88, 83, 78,145,146,147,148,149
};

const int Arr__B[Permutation150::_count] = {
	 45, 40, 35, 30, 25,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,145, 26, 27, 28, 29,
	146, 31, 32, 33, 34,147, 36, 37, 38, 39,148, 41, 42, 43, 44,
	149, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 77, 78,  0, 80, 81, 82, 83,  1, 85, 86, 87, 88,  2,
	 90, 91, 92, 93,  3, 95, 96, 97, 98,  4,104,109,114,119,124,
	103,108,113,118,123,102,107,112,117,122,101,106,111,116,121,
	100,105,110,115,120,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144, 99, 94, 89, 84, 79
};

const int Arr__U[Permutation150::_count] = {
	  4,  9, 14, 19, 24,  3,  8, 13, 18, 23,  2,  7, 12, 17, 22,
	  1,  6, 11, 16, 21,  0,  5, 10, 15, 20,100,101,102,103,104,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 25, 26, 27, 28, 29, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 50, 51, 52, 53, 54, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 75, 76, 77, 78, 79,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMU1[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	105,106,107,108,109, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 30, 31, 32, 33, 34,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 77, 78, 79, 55, 56, 57, 58, 59, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,
	 80, 81, 82, 83, 84,110,111,112,113,114,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMU2[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34,110,111,112,113,114, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 35, 36, 37, 38, 39, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 60, 61, 62, 63, 64,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,
	105,106,107,108,109, 85, 86, 87, 88, 89,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMD2[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 60, 61, 62, 63, 64, 40, 41, 42, 43, 44,
	 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 85, 86, 87, 88, 89, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,110,111,112,113,114,
	 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,
	105,106,107,108,109, 35, 36, 37, 38, 39,115,116,117,118,119,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int ArrMD1[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 65, 66, 67, 68, 69,
	 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 90, 91, 92, 93, 94, 70, 71, 72, 73, 74,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	115,116,117,118,119, 95, 96, 97, 98, 99,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114, 40, 41, 42, 43, 44,
	120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
	135,136,137,138,139,140,141,142,143,144,145,146,147,148,149
};

const int Arr__D[Permutation150::_count] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	 70, 71, 72, 73, 74, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 95, 96, 97, 98, 99,
	 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	 90, 91, 92, 93, 94,120,121,122,123,124,100,101,102,103,104,
	105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
	 45, 46, 47, 48, 49,129,134,139,144,149,128,133,138,143,148,
	127,132,137,142,147,126,131,136,141,146,125,130,135,140,145
};

Permutation150::Permutation150() {
	for (int i = 0; i < _count; i++)
		_components[i] = i;
}

Permutation150::Permutation150(const Permutation150 &_perm) {
	for (int i = 0; i < _count; i++)
		_components[i] = _perm._components[i];
}

Permutation150::Permutation150(const int init[Permutation150::_count]) {
	for (int i = 0; i < _count; i++)
		_components[i] = init[i];
}

#if 0
Permutation150 Permutation150::operator*(const Permutation150 &perm_b) {
	// perm_b (*this)
	Permutation150 outcome;
	for (int i = 0; i < Permutation150::_count; i++) {
		outcome._components[i] = perm_b._components[_components[i]];
	}
	return outcome;
}
#endif

Permutation150 operator*(const Permutation150 &perm_a, const Permutation150 &perm_b) {
	// perm_b (*this)
	Permutation150 outcome;
	for (int i = 0; i < Permutation150::_count; i++) {
		outcome._components[i] = perm_b._components[perm_a._components[i]];
	}
	return outcome;
}
#endif

//
#if 0
const Permutation<5> __I(arr_I_5);

const Permutation<5> __L(arr_L_5);
const Permutation<5> ML1(arr_ML1_5);
const Permutation<5> ML2(arr_ML2_5);
const Permutation<5> MR2(arr_MR2_5);
const Permutation<5> MR1(arr_MR1_5);
const Permutation<5> __R(arr_R_5);

const Permutation<5> __F(arr_F_5);
const Permutation<5> MF1(arr_MF1_5);
const Permutation<5> MF2(arr_MF2_5);
const Permutation<5> MB2(arr_MB2_5);
const Permutation<5> MB1(arr_MB1_5);
const Permutation<5> __B(arr_B_5);

const Permutation<5> __U(arr_U_5);
const Permutation<5> MU1(arr_MU1_5);
const Permutation<5> MU2(arr_MU2_5);
const Permutation<5> MD2(arr_MD2_5);
const Permutation<5> MD1(arr_MD1_5);
const Permutation<5> __D(arr_D_5);
#endif


//struct cube4 {
//	static const int _count = 150;
//	int _cube[150]; // 6 * 4 x 4
//
//	void init();
//
//};

#if 0
bool isPermutation(const Permutation150 &perm) {
	bool flag[Permutation150::_count];
	for (int i = 0; i < Permutation150::_count; i++)
		flag[i] = false;
	
	for (int i = 0; i < Permutation150::_count; i++)
		flag[perm._components[i]] = true;

	bool has_false = false;

	for (int i = 0; i < Permutation150::_count; i++)
		if (!flag[i]) {
			has_false = true;
			std::cout << "Index: " << i << '\n';
			break;
		}
	return !has_false;
}
#endif


//void cube4::init() {
//	for (int i = 0; i < _count; i++)
//		_cube[i] = i;
//}


int main() {

	Permutation<5> outcube5;
	
	outcube5 = MR1_5 * MR1_5 *R_5 * R_5 * B_5 * B_5 * U_5 * U_5 
		 * ML1_5 * U_5 * U_5 * !MR1_5 * U_5 * U_5 *MR1_5 
		 * U_5 * U_5 * F_5 * F_5 * MR1_5 * F_5 * F_5 * !ML1_5
		 * B_5 * B_5 * R_5 * R_5 * MR1_5 * MR1_5;
	outcube5.disp_perm_reduced(std::cout);
	std::cout << "\t---\n";
	return 0;


#if 0
	Permutation150 moves[] = {
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
	
//	Permutation150 outcube;
//	Permutation150 outcube2;
//	Permutation150 outcube3;
//	Permutation150 outcube4;

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
//	outcube = __F * __D * !__F * !__D * __F * __D * !__F * !__D * __U * __D * __F * !__D * !__F * __D * __F * !__D * !__F * !__U;
	//outcube = !__R * __D * __D * __R * __D * !__R * __D * __R * __L * __D * __D * !__L * !__D * __L * !__D * !__L;

//  	outcube = MR1 * !__U * __R * __U * !MR1 * !__U * !__R * __U;

	Permutation<5> outcube;
	Permutation<5> outcube2;
	Permutation<5> outcube3;

#if 0
	outcube = __R * MR1 * !ML1 * !__L 
		* !MD1 
		* __L * ML1 * !MR1 * !__R 
		* MD1  
		* !__U 
		* !MD1 
		* __R * MR1 * !ML1 * !__L 
		* MD1 
		* __L * ML1 * !MR1 * !__R 
		* __U;
	outcube = ML2 * MD1 * !ML2 * !MD1 * !__U * MD1 * ML2 * !MD1 * !ML2 * __U;
#endif
#if 0
	outcube = __R * MR1 * !ML1 * !__L  
		*MF1 
		* __L * ML1 * !MR1 * !__R
		*MD1 * !__U * !MD1
		*__R * MR1 * !ML1 * !__L  
		*!MF1
		* __L * ML1 * !MR1 * !__R
		*__U;
#endif

#if 0

	// move z
	outcube = MF1 * MD1 * !MF1 * !MD1 * !__U * MD1 * MF1 * !MD1 * !MF1 * __U;

#endif

#if 0
	// move e
	outcube = !ML1 * 
	__L * !__U * !__L * __U * 
		ML1 * 
	!__U * __L * __U * !__L;
#endif



	// move s

#if 0
	outcube = 
		!MR1 * __D * __D * MR1 * __U * __U * 
		!MR1 * __D * __D * MR1 * __U * __U *
		!MR1 * __D * __D * MR1 * __D * __D ;
#endif

#if 0
	outcube = 
		!MR1 * __D * __D * MR1 * __U * __U * 
		!MR1 * __D * __D * MR1 * __U * __U ;
#endif
	std::cout << "Move s: \n";
	Permutation<5> s;
	s = 
		!MR1_5 * D_5 * D_5 * MR1_5 * U_5 * U_5 *
		!MR1_5 * D_5 * D_5 * MR1_5 * U_5 * U_5 *
		!MR1_5 * D_5 * D_5 * MR1_5 * D_5 * D_5;

	outcube.disp_perm_reduced(std::cout);

	int ord = 1;
	outcube = s;	
	while (outcube != I_5) {
		outcube = s * outcube;
		ord++;
	}
	std::cout << "Order of s is " << ord << ".\n";


	int centers_subgroup[] = {7,8,9,12,13,14,17,18,19,32,33,34,37,38,39,42,43,44,57,58,59,62,63,64,67,68,69,82,83,84,87,88,89,92,93,94,107,108,109,112,113,114,117,118,119,132,133,134,137,138,139,142,143,144};

	std::cout << "Partity (centers): " << outcube.parity(54, centers_subgroup) << '\n' ;

	outcube = I_5;
	for (int i = 1; i <= 12 ; i++) {
		outcube = s * outcube;
		if (! (i % 3)) {
			std::cout << "s^" << i << '\n';
			outcube.disp_perm_reduced(std::cout);
			std::cout << "--- Parity: " << outcube.parity() << "\n";

		}	
	}



//	std::cout << "Partity: " << outcube.parity() << '\n' ;



#ifdef MOVE_W
	// move w
	std::cout << "Move w1:\n";
	outcube = !MR2 * !MD1 *  MR2 *  MD1 *  __U * !MD1 * !MR2 *  MD1 *  MR2 * !__U;

	outcube.disp_perm_reduced(std::cout);
	std::cout << "\t---\n";

//	std::cout << "Move w2:\n";
//	outcube = !MR2 * !MD1 *  MR2 *  MD1 * !__U * !MD1 * !MR2 *  MD1 *  MR2 *  __U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//	std::cout << "Move w3:\n";
//	outcube = !MR2 *  MD1 *  MR2 * !MD1 *  __U *  MD1 * !MR2 * !MD1 *  MR2 * !__U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//	std::cout << "Move w4:\n";
//	outcube = !MR2 *  MD1 *  MR2 * !MD1 * !__U *  MD1 * !MR2 * !MD1 *  MR2 *  __U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//
//	std::cout << "Move w5:\n";
//	outcube =  MR2 * !MD1 * !MR2 *  MD1 *  __U * !MD1 *  MR2 *  MD1 * !MR2 * !__U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//	std::cout << "Move w6:\n";
//	outcube =  MR2 * !MD1 * !MR2 *  MD1 * !__U * !MD1 *  MR2 *  MD1 * !MR2 *  __U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//	std::cout << "Move w7:\n";
//	outcube =  MR2 *  MD1 * !MR2 * !MD1 *  __U *  MD1 *  MR2 * !MD1 * !MR2 * !__U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";
//
//	std::cout << "Move w8:\n";
//	outcube =  MR2 *  MD1 * !MR2 * !MD1 * !__U *  MD1 *  MR2 * !MD1 * !MR2 *  __U;
//
//	outcube.disp_perm_reduced(std::cout);
//	std::cout << "\t---\n";

	std::cout << "Move w1:\n";
	outcube = !__L * !ML1 * MR1 * __R * 
		!MF1 * 
		!__R * !MR1 * ML1 * __L *
		MD1 * __U * !MD1 *
		!__L * !ML1 * MR1 * __R * 
		MF1 *
		!__R * !MR1 * ML1 * __L *
		!__U;

		

	outcube.disp_perm_reduced(std::cout);
	std::cout << "\t---\n";

#endif // MOVE_W

return 0;



	outcube2 = outcube * outcube;

	outcube2.disp_perm(std::cout);
	outcube2.disp_cube(std::cout);

	outcube3 = outcube2 * outcube;

	outcube3.disp_perm(std::cout);
	outcube3.disp_cube(std::cout);
	return 0;

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
	Permutation150 shuffleCube;
	for (int i = 0; i < 32; i++) {

		int move = rand() % 24;

		shuffleCube = shuffleCube * moves[move];
	}
	shuffleCube.disp_cube(std::cout);
	shuffleCube.disp_perm(std::cout);
#endif

	return 0;

}



