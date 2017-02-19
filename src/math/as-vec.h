#pragma once

#include <cmath>

#include "core/as-types.h"

namespace as
{

template<typename T, int n>
struct Vec
{
	T data[n];
	AS_INLINE T& operator[](int i) { return data[i]; }
	AS_INLINE const T& operator[](int i) const { return data[i]; }
};

typedef Vec<real, 2> v2;
typedef Vec<real, 3> v3;
typedef Vec<real, 4> v4;

template<> struct Vec<real, 2>
{
	union
	{
		real data[2];
		struct { real x; real y; };
	};

	AS_INLINE real& operator[](int i) { return data[i]; }
	AS_INLINE const real& operator[](int i) const { return data[i]; }
};

template<> struct Vec<real, 3>
{
	union
	{
		real data[3];
		struct { real x; real y; real z; };
		v2 xy;
	};

	AS_INLINE real& operator[](int i) { return data[i]; }
	AS_INLINE const real& operator[](int i) const { return data[i]; }
};

template<> struct Vec<real, 4>
{
	union
	{
		real data[4];
		struct { real x; real y; real z; real w; };
		struct { real r; real g; real b; real a; };
		v2 xy;
		v3 xyz;
		v3 rgb;
	};

	AS_INLINE real& operator[](int i) { return data[i]; }
	AS_INLINE const real& operator[](int i) const { return data[i]; }
};

template<typename T, int n>
AS_INLINE T dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	T result = 0;
	for (size_t i = 0; i < n; ++i) {
		result += lhs[i] * rhs[i];
	}
	return result;
}

template<typename T, int n>
AS_INLINE T length_squared(const Vec<T, n>& vec)
{
	T result = 0;
	for (size_t i = 0; i < n; ++i) {
		result += vec[i] * vec[i];
	}
	return result;
}

template<typename T, int n>
AS_INLINE T length(const Vec<T, n>& vec)
{
	return std::sqrt(length_squared(vec));
}

template<typename T, int n>
AS_INLINE Vec<T, n> normalize(const Vec<T, n>& vec)
{
	T len = length(vec);
	return vec / len;
}

template<typename T, int n>
AS_INLINE T normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out)
{
	T len = length(vec);
	out = vec / len;
	return len;
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = lhs[i] + rhs[i];
	}
	return result;
}

template<typename T, int n>
AS_INLINE Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	for (size_t i = 0; i < n; ++i) {
		lhs[i] += rhs[i];
	}
	return lhs;
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = lhs[i] - rhs[i];
	}
	return result;
}

template<typename T, int n>
AS_INLINE Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	for (size_t i = 0; i < n; ++i) {
		lhs[i] -= rhs[i];
	}
	return lhs;
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = -vec[i];
	}
	return result;
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator*(const Vec<T, n>& vec, T val)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] * val;
	}
	return result;
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator*(T val, const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] * val;
	}
	return result;
}

template<typename T, int n>
AS_INLINE void operator*=(Vec<T, n>& vec, T val)
{
	for (size_t i = 0; i < n; ++i) {
		vec[i] *= val;
	}
}

template<typename T, int n>
AS_INLINE Vec<T, n> operator/(const Vec<T, n>& vec, T val)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] / val;
	}
	return result;
}

template<typename T, int n>
AS_INLINE void operator/=(Vec<T, n>& vec, T val)
{
	for (size_t i = 0; i < n; ++i) {
		vec[i] /= val;
	}
}

AS_INLINE v2 make_v2(real x, real y)
{
	v2 result;
	result[0] = x;
	result[1] = y;
	return result;
}

AS_INLINE v2 make_v2(real val)
{
	v2 result;
	result[0] = val;
	result[1] = val;
	return result;
}

AS_INLINE v3 make_v3(real x, real y, real z)
{
	v3 result;
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return result;
}

AS_INLINE v3 make_v3(real val)
{
	v3 result;
	result[0] = val;
	result[1] = val;
	result[2] = val;
	return result;
}

AS_INLINE v3 cross(const v3& lhs, const v3& rhs)
{
	v3 result;
	result[0] = lhs.y * rhs.z - lhs.z * rhs.y;
	result[1] = lhs.z * rhs.x - lhs.x * rhs.z;
	result[2] = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

AS_INLINE v4 make_v4(real x, real y, real z, real w)
{
	v4 result;
	result[0] = x;
	result[1] = y;
	result[2] = z;
	result[3] = w;
	return result;
}

AS_INLINE v4 make_v4(real val)
{
	v4 result;
	result[0] = val;
	result[1] = val;
	result[2] = val;
	result[3] = val;
	return result;
}

AS_INLINE v4 make_v4(const v3& xyz, real w)
{
	v4 result;
	result[0] = xyz.x;
	result[1] = xyz.y;
	result[2] = xyz.z;
	result[3] = w;
	return result;
}

extern const v3 v3_x;
extern const v3 v3_y;
extern const v3 v3_z;
extern const v3 v3_zero;
extern const v3 v3_one;

}