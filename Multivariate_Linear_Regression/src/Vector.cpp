#include "Vector.h"
#include <algorithm>

using namespace foscar;

template<unsigned int N, typename T>
Vector<N, T>::Vector() {
	set_to_zero();
}
template<unsigned int N, typename T>
Vector<N, T>::Vector(const T elem) {
	// TODO: Fill up this function properly
	std::fill(val, val + N, elem);
}
template<unsigned int N, typename T>
Vector<N, T>::Vector(const T s, const T t) :
Vector<N, T>::Vector() {
	// TODO: Fill up this function properly
	val[0] = s;
	val[1] = t;
}
template<unsigned int N, typename T>
Vector<N, T>::Vector(const T s, const T t, const T u) :
Vector<N, T>::Vector() {
	// TODO: Fill up this function properly
	val[0] = s;
	val[1] = t;
	val[2] = u;
}
template<unsigned int N, typename T>
Vector<N, T>::Vector(const T s, const T t, const T u, const T v) :
Vector<N, T>::Vector() {
	// TODO: Fill up this function properly
	val[0] = s;
	val[1] = t;
	val[2] = u;
	val[3] = v;
}
template<unsigned int N, typename T>
Vector<N, T>::Vector(const Vector<N, T>& other) {
	// TODO: Fill up this function properly
	std::copy(other.val, other.val + N, val);
}
template<unsigned int N, typename T>
Vector<N, T>& Vector<N, T>::operator=(const Vector<N, T>& other) {
	// TODO: Fill up this function properly
	for (int i = 0; i < N; ++i) {
		val[i] = other.val[i];
	}
	return *this;
}
template<unsigned int N, typename T>
T& Vector<N, T>::operator()(unsigned int i) {
	// TODO: Fill up this function properly
	return val[i];
}
template<unsigned int N, typename T>
const T& Vector<N, T>::operator()(unsigned int i) const {
	// TODO: Fill up this function properly
	return val[i];
}

// type casting operators
template<unsigned int N, typename T>
Vector<N, T>::operator const T*() const {
	return val;
}
template<unsigned int N, typename T>
Vector<N, T>::operator T*() {
	return val;
}
template<unsigned int N, typename T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& other) {
	// TODO: Fill up this function properly
	for (int i = 0; i < N; ++i) {
		val[i] += other.val[i];
	}
	return *this;
}
template<unsigned int N, typename T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& other) {
	// TODO: Fill up this function properly
	for (int i = 0; i < N; ++i) {
		val[i] -= other.val[i];
	}
	return *this;
}
template<unsigned int N, typename T>
void Vector<N, T>::set_to_zero() {
	// TODO: Fill up this function properly
	std::fill(val, val + N, 0);
}
template<unsigned int N, typename T>
T Vector<N, T>::length() {
	T sum = 0;
	for (int i = 0; i < N; i++) {
		sum += val[i] * val[i];
	}
	return sqrt(sum);
}
template<unsigned int N, typename T>
Vector<N, T>& Vector<N, T>::normalize(void) {
	T len = this->length();
	for (int i = 0; i < N; i++)
		val[i] /= len;
	return *this;
}
