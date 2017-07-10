#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

namespace foscar {
template <unsigned int M, unsigned int N, typename T>
class Matrix {
public:
	Matrix();
	Matrix(const T elem);
	T& operator()(unsigned int r, unsigned int c);
	const T& operator()(unsigned int r, unsigned int c) const;
	// type casting operator
	operator const T*() const;
	operator T*();
	void set_to_zero();
	void get_ith_column(unsigned int i, Vector<M, T>& col) const;
	void set_ith_column(unsigned int i, const Vector<M, T>& col);
	void get_ith_row(unsigned int i, Vector<N, T>& row) const;
	void set_ith_row(unsigned int i, const Vector<N, T>& row);
	Matrix<N, M, T> transpose() const;
protected:
	T val[M * N];   // column major
};

typedef Matrix<3, 3, float> mat3x3f;
typedef Matrix<3, 3, double> mat3x3d;

typedef Matrix<4, 4, float> mat4x4f;
typedef Matrix<4, 4, double> mat4x4d;
}

#endif
