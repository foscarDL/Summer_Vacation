#ifndef VECTOR_H
#define VECTOR_H
namespace foscar {
template<unsigned int N, typename T>
class Vector {
public:
	Vector();
	Vector(const T elem);
	Vector(const T s, const T t);
	Vector(const T s, const T t, const T u);
	Vector(const T s, const T t, const T u, const T v);
	Vector(const Vector<N, T>& other);
	Vector& operator=(const Vector<N, T>& other);
	T& operator()(unsigned int i);
	const T& operator()(unsigned int i) const;
	// type casting operators
	operator const T*() const;
	operator T*();
	Vector& operator+=(const Vector<N, T>& other);
	Vector& operator-=(const Vector<N, T>& other);
	void set_to_zero();
	T length();
	Vector& normalize(void);
protected:
	T val[N];
};

// typedeftemplate <unsigned int M, unsigned int N, typename T>
typedef Vector<2, int> vec2i;
typedef Vector<2, float> vec2f;
typedef Vector<2, double> vec2d;

typedef Vector<3, int> vec3i;
typedef Vector<3, float> vec3f;
typedef Vector<3, double> vec3d;

typedef Vector<4, int> vec4i;
typedef Vector<4, float> vec4f;
typedef Vector<4, double> vec4d;
}
#endif
