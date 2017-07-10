#include "Matrix.h"
#include <algorithm>

using namespace foscar;

template <unsigned int M, unsigned int N, typename T>
Matrix<M, N, T>::Matrix() {
	set_to_zero();
}

template <unsigned int M, unsigned int N, typename T>
Matrix<M, N, T>::Matrix(const T elem)
{
	std::fill(val, val + M*N, elem);
}
template <unsigned int M, unsigned int N, typename T>
T& Matrix<M, N, T>::operator()(unsigned int r, unsigned int c) {
	// TODO: Fill up this function properly
	// Notice: The Matrixrix is column major
	return val[r + c * M];
}
template <unsigned int M, unsigned int N, typename T>
const T& Matrix<M, N, T>::operator()(unsigned int r, unsigned int c) const {
	// TODO: Fill up this function properly
	// Notice: The Matrixrix is column major
	return val[r + c * M];
}

// type casting operator
template <unsigned int M, unsigned int N, typename T>
Matrix<M, N, T>::operator const T*() const {
	return val;
}
template <unsigned int M, unsigned int N, typename T>
Matrix<M, N, T>::operator T*() {
	return val;
}
template <unsigned int M, unsigned int N, typename T>
void Matrix<M, N, T>::set_to_zero() {
	// TODO: Fill up this function properly
	std::fill(val, val + M * N, 0);
}
template <unsigned int M, unsigned int N, typename T>
void Matrix<M, N, T>::get_ith_column(unsigned int i, Vector<M, T>& col) const {
	// TODO: Fill up this function properly
	for (unsigned int j = 0; j < M; ++j) {
		col(j) = (*this)(j, i);
	}
}
template <unsigned int M, unsigned int N, typename T>
void Matrix<M, N, T>::set_ith_column(unsigned int i, const Vector<M, T>& col) {
	// TODO: Fill up this function properly
	for (unsigned int j = 0; j < M; ++j) {
		(*this)(j, i) = col(j);
	}
}
template <unsigned int M, unsigned int N, typename T>
void Matrix<M, N, T>::get_ith_row(unsigned int i, Vector<N, T>& row) const {
	// TODO: Fill up this function properly
	for (unsigned int j = 0; j < N; ++j) {
		row(j) = (*this)(i, j);
	}
}
template <unsigned int M, unsigned int N, typename T>
void Matrix<M, N, T>::set_ith_row(unsigned int i, const Vector<N, T>& row) {
	// TODO: Fill up this function properly
	for (unsigned int j = 0; j < N; ++j) {
		(*this)(i, j) = row(j);
	}
}
template <unsigned int M, unsigned int N, typename T>
Matrix<N, M, T> Matrix<M, N, T>::transpose() const {
	// TODO: Fill up this function properly
	Matrix < N, M, T > trans;
	Vector < M, T > col;
	for (int i = 0; i < N; i++) {
		get_ith_column(i, col);
		trans.set_ith_row(i, col);
	}
	return trans;
}
