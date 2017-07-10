#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include "Vector.h"
#include "Matrix.h"
#include "Operator.h"

namespace foscar {
template <typename T>
Matrix<4, 4, T> translate(T dx, T dy, T dz);
template<typename T>
Matrix<4, 4, T> rotate(T angle, T x, T y, T z);
template<typename T>
Matrix<4, 4, T> scale(T sx, T sy, T sz);
template<typename T>
Matrix<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ,
		T upX, T upY, T upZ);
template<typename T>
Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal);
template<typename T>
Matrix<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal);
template<typename T>
Matrix<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar);
#endif
