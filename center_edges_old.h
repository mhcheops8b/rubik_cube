#pragma once
#include <iostream>
#include <iomanip>

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

	enum ce_faces { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
};

template <int N>
center_edges_odd<N>::center_edges_odd() {
	for (int i = 0; i < number_of_indices<N>; i++)
		perm[i] = i;
}




constexpr int NO(int layer, int index)
{
	return 4 * (layer - 1) * (layer - 1) + index - 1;
}
constexpr int EA(int layer, int index)
{
	return 4 * (layer - 1) * (layer - 1) + 2 * layer - 1 + index - 1;
}
constexpr int SO(int layer, int index)
{
	return 4 * (layer - 1) * (layer - 1) + 2 * (2 * layer - 1) + index - 1;
}
constexpr int WE(int layer, int index)
{
	return 4 * (layer - 1) * (layer - 1) + 3 * (2 * layer - 1) + index - 1;
}


template<int N>
constexpr int NF(enum center_edges_odd<N>::ce_faces f, int layer, int index)
{
	return f * 4 * number_of_layers<N>*number_of_layers<N> +NO(layer, index);
}

template<int N>
constexpr int EF(enum center_edges_odd<N>::ce_faces f, int layer, int index)
{
	return f * 4 * number_of_layers<N>*number_of_layers<N> +EA(layer, index);
}

template<int N>
constexpr int SF(enum center_edges_odd<N>::ce_faces f, int layer, int index)
{
	return f * 4 * number_of_layers<N>*number_of_layers<N> +SO(layer, index);
}

template<int N>
constexpr int WF(enum center_edges_odd<N>::ce_faces f, int layer, int index)
{
	return f * 4 * number_of_layers<N>*number_of_layers<N> +WE(layer, index);
}

template <int N>
void apply_cycle(center_edges_odd<N> &ce, int(&cycle)[4]) {

	int tmp = ce.perm[cycle[3]];
	for (int j = 2; j >= 0; j--)
		ce.perm[cycle[j + 1]] = ce.perm[cycle[j]];
	ce.perm[cycle[0]] = tmp;

}

template <int N>
void apply_cycle(center_edges_odd<N> &ce, int idx1, int idx2, int idx3, int idx4) {

	int tmp_array[] = { idx1, idx2, idx3, idx4 };

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
	const static char ce_face_titles[] = { 'U', 'L', 'F', 'R', 'B', 'D' };
#endif
	for (int i = 0; i < number_of_layers<N>; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
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
			NF<N>(center_edges_odd<N>::U, t, t + K),
			SF<N>(center_edges_odd<N>::B, t, t + K),
			NF<N>(center_edges_odd<N>::D, t, t + K),
			NF<N>(center_edges_odd<N>::F, t, t + K));
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
			SF<N>(center_edges_odd<N>::U, t, t - K),
			NF<N>(center_edges_odd<N>::B, t, t - K),
			SF<N>(center_edges_odd<N>::D, t, t - K),
			SF<N>(center_edges_odd<N>::F, t, t - K));
	}
}

template <int N>
void disp_face(center_edges_odd<N> &ce, const enum center_edges_odd<N>::ce_faces &f, std::ostream &os = std::cout) {
	for (int k = number_of_layers<N>; k >= 0; k--) {

		for (int r = 0; r < number_of_layers<N> -k; r++) {
			os << ' ' << std::setw(3) << ce.perm[WF<N>(f, number_of_layers<N> -r, number_of_layers<N> +k - r)] << ' ';
		}

		os << " xxx ";

		for (int r = 0; r < 2 * k - 1; r++)
			os << ' ' << std::setw(3) << ce.perm[NF<N>(f, k, r + 1)] << ' ';

		if (k != 0)
			os << " xxx ";

		for (int r = number_of_layers<N> -k; r> 0; r--) {
			os << ' ' << std::setw(3) << ce.perm[EF<N>(f, number_of_layers<N> -r + 1, number_of_layers<N> -k - r + 1)] << ' ';
		}

		os << '\n';
	}

	for (int k = 1; k <= number_of_layers<N>; k++) {

		for (int r = 0; r < number_of_layers<N> -k; r++) {
			os << ' ' << std::setw(3) << ce.perm[WF<N>(f, number_of_layers<N> -r, number_of_layers<N> -k - r)] << ' ';
		}

		os << " xxx ";

		for (int r = 2 * k - 1; r > 0; r--)
			os << ' ' << std::setw(3) << ce.perm[SF<N>(f, k, r)] << ' ';

		os << " xxx ";

		for (int r = number_of_layers<N> -k; r> 0; r--) {
			os << ' ' << std::setw(3) << ce.perm[EF<N>(f, number_of_layers<N> -r + 1, number_of_layers<N> +k - r + 1)] << ' ';
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
				signum *= -1;

	return signum;

}

template <int N>
void center_edges_odd<N>::disp_cube(std::ostream &os) {
	os << "U Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::U, os);
	os << "L Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::L, os);
	os << "F Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::F, os);
	os << "R Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::R, os);
	os << "B Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::B, os);
	os << "D Face:\n";
	disp_face<N>(*this, center_edges_odd<N>::D, os);
}
//-------------------------------------------
// Even cube
//-------------------------------------------
#include "faces.h"

template <int N>
constexpr int number_of_indices_even = 6 * (N - 2) * (N - 4);


template <int N>
constexpr int number_of_indices_per_face_even = (N - 2) * (N - 4);

template <int N>
constexpr int number_of_layers_even = (N - 2) / 2;

template <int N, bool isEven>
struct center_edges_even {
	int perm[number_of_indices_even<N>];

	center_edges_even();
	void disp_cube(std::ostream &os = std::cout);

	template<int U>
	friend void apply_Face(const faces &f, center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_L(center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_R(center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_F(center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_B(center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_U(center_edges_even<U, isEven> &ce);

	template<int U>
	friend void apply_D(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_ML(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_MR(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_MF(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_MB(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_MU(center_edges_even<U, isEven> &ce);

	template <int U, int K>
	friend void apply_MD(center_edges_even<U, isEven> &ce);

};

template <int N, bool isEven>
center_edges_even<N, isEven>::center_edges_even() {
	static_assert(N % 2 == 0, "N must be even.");
	static_assert(N >= 6, "There are no center edges for smaller cubes thant 6x6x6.");

	for (int i = 0; i < number_of_indices_even<N>; i++)
		perm[i] = i;
}

template <int N>
inline int WF_even(int layer, int index) {
	return 4 * (layer - 1) * (layer - 2)
		+ 3 * 2 * (layer - 1) + index;
}

template <int N>
inline int NF_even(int layer, int index) {
	return 4 * (layer - 1) * (layer - 2)
		+ index;
}

template <int N>
inline int EF_even(int layer, int index) {
	return 4 * (layer - 1) * (layer - 2)
		+ 2 * (layer - 1) + index;
}

template <int N>
inline int SF_even(int layer, int index) {
	return 4 * (layer - 1) * (layer - 2)
		+ 2 * 2 * (layer - 1) + index;
}

template <int N>
inline int face_NF_even(const faces &f, int layer, int index) {
	return f * number_of_indices_per_face_even<N> +NF_even<N>(layer, index);
}

template <int N>
inline int face_EF_even(const faces &f, int layer, int index) {
	return f * number_of_indices_per_face_even<N> +EF_even<N>(layer, index);
}

template <int N>
inline int face_WF_even(const faces &f, int layer, int index) {
	return f * number_of_indices_per_face_even<N> +WF_even<N>(layer, index);
}

template <int N>
inline int face_SF_even(const faces &f, int layer, int index) {
	return f * number_of_indices_per_face_even<N> +SF_even<N>(layer, index);
}


template<int N, bool isEven>
void center_edges_even<N, isEven>::disp_cube(std::ostream &os) {
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
	for (int k = number_of_layers_even<N>; k > 0; k--) {
		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(U, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// padding middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(U, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(U, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';
		os << '\n';
	}

	// row + 1 - last - 1
	for (int k = 1; k <= number_of_layers_even<N>; k++) {
		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(U, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(U, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(U, t, t + k - 2)] / number_of_indices_per_face_even<N>];

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
	for (int k = number_of_layers_even<N>; k > 0; k--) {

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(L, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(L, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(L, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(F, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(F, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(F, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(R, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(R, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(R, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(B, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(B, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(B, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';
		os << '\n';
	}

	// row + 1 - last - 1
	for (int k = 1; k <= number_of_layers_even<N>; k++) {

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(L, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(L, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(L, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(F, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(F, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(F, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(R, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(R, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(R, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}

		os << '.';

		os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(B, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(B, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(B, t, t + k - 2)] / number_of_indices_per_face_even<N>];

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
	for (int k = number_of_layers_even<N>; k > 0; k--) {
		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(D, t, t + k - 2)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 0; t < 2 * (k - 1); t++)
			os << face_labels[perm[face_NF_even<N>(D, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(D, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}

		os << '.';
		os << '\n';
	}

	// row + 1 - last - 1
	for (int k = 1; k <= number_of_layers_even<N>; k++) {
		// skip
		for (int i = 0; i <= N; i++)
			os << ' ';

		os << '.';

		for (int t = number_of_layers_even<N>; t > k; t--) {

			os << face_labels[perm[face_WF_even<N>(D, t, t - k - 1)] / number_of_indices_per_face_even<N>];

		}
		os << '.';

		// middle
		for (int t = 2 * (k - 1) - 1; t >= 0; t--)
			os << face_labels[perm[face_SF_even<N>(D, k, t)] / number_of_indices_per_face_even<N>];

		os << '.';

		for (int t = k + 1; t <= number_of_layers_even<N>; t++) {

			os << face_labels[perm[face_EF_even<N>(D, t, t + k - 2)] / number_of_indices_per_face_even<N>];

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

template <int N>
void apply_Face(const faces &f, center_edges_even<N, true> &ce) {
	for (int k = 2; k <= number_of_layers_even<N>; k++) {
		for (int t = 0; t < 2 * k; t++) {
			//			 NF  ->  EF  ->  SF  ->  WF
			//			k, t -> k, t -> k, t -> k, t
			int tmp = ce.perm[face_NF_even<N>(f, k, t)];

			ce.perm[face_NF_even<N>(f, k, t)] = ce.perm[face_WF_even<N>(f, k, t)];
			ce.perm[face_WF_even<N>(f, k, t)] = ce.perm[face_SF_even<N>(f, k, t)];
			ce.perm[face_SF_even<N>(f, k, t)] = ce.perm[face_EF_even<N>(f, k, t)];
			ce.perm[face_EF_even<N>(f, k, t)] = tmp;

		}
	}

}

template <int N>
void apply_L(center_edges_even<N, true> &ce) {
	apply_Face(L, ce);
}

template <int N>
void apply_R(center_edges_even<N, true> &ce) {
	apply_Face(R, ce);
}

template <int N>
void apply_F(center_edges_even<N, true> &ce) {
	apply_Face(F, ce);
}

template <int N>
void apply_B(center_edges_even<N, true> &ce) {
	apply_Face(B, ce);
}

template <int N>
void apply_U(center_edges_even<N, true> &ce) {
	apply_Face(U, ce);
}

template <int N>
void apply_D(center_edges_even<N, true> &ce) {
	apply_Face(D, ce);
}

template <int N, int K>
void apply_ML(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_NF_even<N>(U, k, k - K - 1)];

		ce.perm[face_NF_even<N>(U, k, k - K - 1)] =
			ce.perm[face_SF_even<N>(B, k, k - K - 1)];

		ce.perm[face_SF_even<N>(B, k, k - K - 1)] =
			ce.perm[face_NF_even<N>(D, k, k - K - 1)];

		ce.perm[face_NF_even<N>(D, k, k - K - 1)] =
			ce.perm[face_NF_even<N>(F, k, k - K - 1)];

		ce.perm[face_NF_even<N>(F, k, k - K - 1)] = tmp;
	}
	for (int k = 2 * K - 3; k >= 0; k--) {
		// U-WF(K, k) -> F-WF(K, k) -> D-WF(K, k) -> B-EF(K, k)

		int tmp = ce.perm[face_WF_even<N>(U, K, k)];

		ce.perm[face_WF_even<N>(U, K, k)] = ce.perm[face_EF_even<N>(B, K, k)];
		ce.perm[face_EF_even<N>(B, K, k)] = ce.perm[face_WF_even<N>(D, K, k)];
		ce.perm[face_WF_even<N>(D, K, k)] = ce.perm[face_WF_even<N>(F, K, k)];
		ce.perm[face_WF_even<N>(F, K, k)] = tmp;
	}

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_SF_even<N>(U, k, k + K - 2)];

		ce.perm[face_SF_even<N>(U, k, k + K - 2)] =
			ce.perm[face_NF_even<N>(B, k, k + K - 2)];

		ce.perm[face_NF_even<N>(B, k, k + K - 2)] =
			ce.perm[face_SF_even<N>(D, k, k + K - 2)];

		ce.perm[face_SF_even<N>(D, k, k + K - 2)] =
			ce.perm[face_SF_even<N>(F, k, k + K - 2)];

		ce.perm[face_SF_even<N>(F, k, k + K - 2)] = tmp;
	}

}

template <int N, int K>
void apply_MR(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_NF_even<N>(U, k, k + K - 2)];

		ce.perm[face_NF_even<N>(U, k, k + K - 2)] =
			ce.perm[face_NF_even<N>(F, k, k + K - 2)];

		ce.perm[face_NF_even<N>(F, k, k + K - 2)] =
			ce.perm[face_NF_even<N>(D, k, k + K - 2)];

		ce.perm[face_NF_even<N>(D, k, k + K - 2)] =
			ce.perm[face_SF_even<N>(B, k, k + K - 2)];

		ce.perm[face_SF_even<N>(B, k, k + K - 2)] = tmp;
	}
	for (int k = 2 * K - 3; k >= 0; k--) {
		// U-WF(K, k) -> F-WF(K, k) -> D-WF(K, k) -> B-EF(K, k)

		int tmp = ce.perm[face_EF_even<N>(U, K, k)];

		ce.perm[face_EF_even<N>(U, K, k)] = ce.perm[face_EF_even<N>(F, K, k)];
		ce.perm[face_EF_even<N>(F, K, k)] = ce.perm[face_EF_even<N>(D, K, k)];
		ce.perm[face_EF_even<N>(D, K, k)] = ce.perm[face_WF_even<N>(B, K, k)];
		ce.perm[face_WF_even<N>(B, K, k)] = tmp;
	}

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_SF_even<N>(U, k, k - K - 1)];

		ce.perm[face_SF_even<N>(U, k, k - K - 1)] =
			ce.perm[face_SF_even<N>(F, k, k - K - 1)];

		ce.perm[face_SF_even<N>(F, k, k - K - 1)] =
			ce.perm[face_SF_even<N>(D, k, k - K - 1)];

		ce.perm[face_SF_even<N>(D, k, k - K - 1)] =
			ce.perm[face_NF_even<N>(B, k, k - K - 1)];

		ce.perm[face_NF_even<N>(B, k, k - K - 1)] = tmp;
	}

}

template <int N, int K>
void apply_MF(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_NF_even<N>(R, k, k - K - 1)];

		ce.perm[face_NF_even<N>(R, k, k - K - 1)] =
			ce.perm[face_WF_even<N>(U, k, k - K - 1)];

		ce.perm[face_WF_even<N>(U, k, k - K - 1)] =
			ce.perm[face_SF_even<N>(L, k, k - K - 1)];

		ce.perm[face_SF_even<N>(L, k, k - K - 1)] =
			ce.perm[face_EF_even<N>(D, k, k - K - 1)];

		ce.perm[face_EF_even<N>(D, k, k - K - 1)] = tmp;
	}

	for (int k = 2 * K - 3; k >= 0; k--) {
		int tmp = ce.perm[face_WF_even<N>(R, K, k)];

		ce.perm[face_WF_even<N>(R, K, k)] = ce.perm[face_SF_even<N>(U, K, k)];
		ce.perm[face_SF_even<N>(U, K, k)] = ce.perm[face_EF_even<N>(L, K, k)];
		ce.perm[face_EF_even<N>(L, K, k)] = ce.perm[face_NF_even<N>(D, K, k)];
		ce.perm[face_NF_even<N>(D, K, k)] = tmp;
	}

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_SF_even<N>(R, k, k + K - 2)];

		ce.perm[face_SF_even<N>(R, k, k + K - 2)] =
			ce.perm[face_EF_even<N>(U, k, k + K - 2)];

		ce.perm[face_EF_even<N>(U, k, k + K - 2)] =
			ce.perm[face_NF_even<N>(L, k, k + K - 2)];

		ce.perm[face_NF_even<N>(L, k, k + K - 2)] =
			ce.perm[face_WF_even<N>(D, k, k + K - 2)];

		ce.perm[face_WF_even<N>(D, k, k + K - 2)] = tmp;
	}

}

template <int N, int K>
void apply_MB(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_NF_even<N>(R, k, k + K - 2)];

		ce.perm[face_NF_even<N>(R, k, k + K - 2)] =
			ce.perm[face_EF_even<N>(D, k, k + K - 2)];

		ce.perm[face_EF_even<N>(D, k, k + K - 2)] =
			ce.perm[face_SF_even<N>(L, k, k + K - 2)];

		ce.perm[face_SF_even<N>(L, k, k + K - 2)] =
			ce.perm[face_WF_even<N>(U, k, k + K - 2)];

		ce.perm[face_WF_even<N>(U, k, k + K - 2)] = tmp;
	}

	for (int k = 2 * K - 3; k >= 0; k--) {
		int tmp = ce.perm[face_EF_even<N>(R, K, k)];

		ce.perm[face_EF_even<N>(R, K, k)] = ce.perm[face_SF_even<N>(D, K, k)];
		ce.perm[face_SF_even<N>(D, K, k)] = ce.perm[face_WF_even<N>(L, K, k)];
		ce.perm[face_WF_even<N>(L, K, k)] = ce.perm[face_NF_even<N>(U, K, k)];
		ce.perm[face_NF_even<N>(U, K, k)] = tmp;
	}

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_SF_even<N>(R, k, k - K - 1)];

		ce.perm[face_SF_even<N>(R, k, k - K - 1)] =
			ce.perm[face_WF_even<N>(D, k, k - K - 1)];

		ce.perm[face_WF_even<N>(D, k, k - K - 1)] =
			ce.perm[face_NF_even<N>(L, k, k - K - 1)];

		ce.perm[face_NF_even<N>(L, k, k - K - 1)] =
			ce.perm[face_EF_even<N>(U, k, k - K - 1)];

		ce.perm[face_EF_even<N>(U, k, k - K - 1)] = tmp;
	}

}

template <int N, int K>
void apply_MU(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_WF_even<N>(F, k, k + K - 2)];

		ce.perm[face_WF_even<N>(F, k, k + K - 2)] =
			ce.perm[face_WF_even<N>(R, k, k + K - 2)];

		ce.perm[face_WF_even<N>(R, k, k + K - 2)] =
			ce.perm[face_EF_even<N>(B, k, k - K - 1)];

		ce.perm[face_EF_even<N>(B, k, k - K - 1)] =
			ce.perm[face_WF_even<N>(L, k, k + K - 2)];

		ce.perm[face_WF_even<N>(L, k, k + K - 2)] = tmp;
	}


	for (int k = 2 * K - 3; k >= 0; k--) {
		int tmp = ce.perm[face_NF_even<N>(F, K, k)];

		ce.perm[face_NF_even<N>(F, K, k)] = ce.perm[face_NF_even<N>(R, K, k)];
		ce.perm[face_NF_even<N>(R, K, k)] = ce.perm[face_NF_even<N>(B, K, 2 * K - 3 - k)];
		ce.perm[face_NF_even<N>(B, K, 2 * K - 3 - k)] = ce.perm[face_NF_even<N>(L, K, k)];
		ce.perm[face_NF_even<N>(L, K, k)] = tmp;
	}


	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_EF_even<N>(F, k, k - K - 1)];

		ce.perm[face_EF_even<N>(F, k, k - K - 1)] =
			ce.perm[face_EF_even<N>(R, k, k - K - 1)];

		ce.perm[face_EF_even<N>(R, k, k - K - 1)] =
			ce.perm[face_WF_even<N>(B, k, k + K - 2)];

		ce.perm[face_WF_even<N>(B, k, k + K - 2)] =
			ce.perm[face_EF_even<N>(L, k, k - K - 1)];

		ce.perm[face_EF_even<N>(L, k, k - K - 1)] = tmp;
	}

}

template <int N, int K>
void apply_MD(center_edges_even<N, true> &ce) {
	static_assert(K >= 1, "K must be positive.");
	static_assert(K <= number_of_layers_even<N>, "K must less than number of layers.");

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_WF_even<N>(F, k, k - K - 1)];

		ce.perm[face_WF_even<N>(F, k, k - K - 1)] =
			ce.perm[face_WF_even<N>(L, k, k - K - 1)];

		ce.perm[face_WF_even<N>(L, k, k - K - 1)] =
			ce.perm[face_EF_even<N>(B, k, k + K - 2)];

		ce.perm[face_EF_even<N>(B, k, k + K - 2)] =
			ce.perm[face_WF_even<N>(R, k, k - K - 1)];

		ce.perm[face_WF_even<N>(R, k, k - K - 1)] = tmp;
	}

	for (int k = 2 * K - 3; k >= 0; k--) {
		int tmp = ce.perm[face_SF_even<N>(F, K, k)];

		ce.perm[face_SF_even<N>(F, K, k)] = ce.perm[face_SF_even<N>(L, K, k)];
		ce.perm[face_SF_even<N>(L, K, k)] = ce.perm[face_SF_even<N>(B, K, 2 * K - 3 - k)];
		ce.perm[face_SF_even<N>(B, K, 2 * K - 3 - k)] = ce.perm[face_SF_even<N>(R, K, k)];
		ce.perm[face_SF_even<N>(R, K, k)] = tmp;
	}

	for (int k = number_of_layers_even<N>; k > K; k--) {

		int tmp = ce.perm[face_EF_even<N>(F, k, k + K - 2)];

		ce.perm[face_EF_even<N>(F, k, k + K - 2)] =
			ce.perm[face_EF_even<N>(L, k, k + K - 2)];

		ce.perm[face_EF_even<N>(L, k, k + K - 2)] =
			ce.perm[face_WF_even<N>(B, k, k - K - 1)];

		ce.perm[face_WF_even<N>(B, k, k - K - 1)] =
			ce.perm[face_EF_even<N>(R, k, k + K - 2)];

		ce.perm[face_EF_even<N>(R, k, k + K - 2)] = tmp;
	}
}

//template <int N>
//using center_edges=center_edges_even<N, true>;

