#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdio.h>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

namespace foscar {
/// y_n = s * x_n
template<unsigned int N, typename T>
Vector<N, T> operator*(const T s, const Vector<N, T>& x);
/// s = u_n * v_n (dot product)
template<unsigned int N, typename T>
T dot(const Vector<N, T>& u, const Vector<N, T>& v);
/// w_3 = u_3 x v_3 (cross product, only for vec3)
template<typename T>
Vector<3, T> cross(const Vector<3, T>& u, const Vector<3, T>& v);
/// y_m = A_{mxn} * x_n
template<unsigned int M, unsigned int N, typename T>
Vector<M, T> operator*(const Matrix<M, N, T>& A, const Vector<N, T>& x);
/// y_n = x_m * A_{mxn}
template<unsigned int M, unsigned int N, typename T>
Vector<N, T> operator*(const Vector<M, T>& x, const Matrix<M, N, T>& A);
/// C_{mxl} = A_{mxn} * B_{nxl}
template<unsigned int M, unsigned int N, unsigned int L, typename T>
Matrix<M, L, T> operator*(const Matrix<M, N, T>& A, const Matrix<N, L, T>& B);
/// ostream for vec class
template<unsigned int N, typename T>
std::ostream& operator <<(std::ostream& os, const Vector<N, T>& v);
/// ostream for mat class
template<unsigned int M, unsigned int N, typename T>
std::ostream& operator <<(std::ostream& os, const Matrix<M, N, T>& A);
}

#endif // KMUVCL_GRAPHICS_OPERATOR_HPP
