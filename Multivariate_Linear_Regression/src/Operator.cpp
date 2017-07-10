#include "Operator.h"

using namespace foscar;

template<unsigned int N, typename T>
Vector<N, T> operator*(const T s, const Vector<N, T>& x) {
	// TODO: Fill up this function properly
	Vector<N, T> y;
	for (int i = 0; i < N; ++i) {
		y(i) = s * x(i);
	}
	return y;
}

/// s = u_n * v_n (dot product)
template<unsigned int N, typename T>
T dot(const Vector<N, T>& u, const Vector<N, T>& v) {
	// TODO: Fill up this function properly
	T val = 0;
	for (int i = 0; i < N; ++i) {
		val += u(i) * v(i);
	}
	return val;
}

/// w_3 = u_3 x v_3 (cross product, only for vec3)
template<typename T>
Vector<3, T> cross(const Vector<3, T>& u, const Vector<3, T>& v) {
	// TODO: Fill up this function properly
	Vector<3, T> w;
	w(0) = u(1) * v(2) - u(2) * v(1);
	w(1) = u(2) * v(0) - u(0) * v(2);
	w(2) = u(0) * v(1) - u(1) * v(0);
	return w;
}

/// y_m = A_{mxn} * x_n
template<unsigned int M, unsigned int N, typename T>
Vector<M, T> operator*(const Matrix<M, N, T>& A, const Vector<N, T>& x) {
	// TODO: Fill up this function properly
	Vector<M, T> y, col;
	for (int i = 0; i < N; ++i) {
		A.get_ith_column(i, col);
		y += x(i) * col;
	}
	return y;
}
;

/// y_n = x_m * A_{mxn}
template<unsigned int M, unsigned int N, typename T>
Vector<N, T> operator*(const Vector<M, T>& x, const Matrix<M, N, T>& A) {
	// TODO: Fill up this function properly
	Vector<N, T> y;
	Vector<M, T> col;
	for (int i = 0; i < N; ++i) {
		A.get_ith_column(i, col);
		y(i) = dot(col, x);
	}
	return y;
}

/// C_{mxl} = A_{mxn} * B_{nxl}
template<unsigned int M, unsigned int N, unsigned int L, typename T>
Matrix<M, L, T> operator*(const Matrix<M, N, T>& A, const Matrix<N, L, T>& B) {
	// TODO: Fill up this function properly
	Matrix<M, L, T> C;
	Vector<N, T> col;
	Vector<N, T> row;
	for (int i = 0; i < M; ++i) {
		A.get_ith_row(i, row);
		for (int j = 0; j < L; ++j) {
			B.get_ith_column(j, col);
			C(i, j) = dot(row, col);
		}
	}
	return C;
}

/// ostream for vec class
template<unsigned int N, typename T>
std::ostream& operator <<(std::ostream& os, const Vector<N, T>& v) {
	// TODO: Fill up this function properly
	os << "[";
	for (int i = 0; i < N - 1; ++i) {
		os << v(i) << ", ";
	}
	os << v(N - 1);
	os << "]";

	return os;
}

/// ostream for mat class
template<unsigned int M, unsigned int N, typename T>
std::ostream& operator <<(std::ostream& os, const Matrix<M, N, T>& A) {
	// TODO: Fill up this function properly
	for (int i = 0; i < M; ++i) {
		os << "[";
		for (int j = 0; j < N - 1; ++j) {
			os << A(i, j) << ", ";
		}
		os << A(i, N - 1);
		os << "]";
		os << std::endl;
	}
	return os;
}
