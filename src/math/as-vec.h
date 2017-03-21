#pragma once

#include <cmath>

#include "core/as-types.h"

namespace as
{

template<typename T, size_t n>
struct Vec
{
	T data[n];
	AS_INLINE T& operator[](size_t i) { return data[i]; }
	AS_INLINE const T& operator[](size_t i) const { return data[i]; }
};

using v2 = Vec<real, 2>;
using v3 = Vec<real, 3>;
using v4 = Vec<real, 4>;

template<> struct Vec<real, 2>
{
	union
	{
		real data[2];
		struct { real x; real y; };
	};

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }

	explicit Vec<real, 2>() {}
	explicit Vec<real, 2>(real xy) : x(xy), y(xy) {}
	explicit Vec<real, 2>(real x, real y) : x(x), y(y) {}
};

template<> struct Vec<real, 3>
{
	union
	{
		real data[3];
		struct { real x; real y; real z; };
		v2 xy;
	};

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }

	explicit Vec<real, 3>() {}
	explicit Vec<real, 3>(real xyz) : x(xyz), y(xyz), z(xyz) {}
	explicit Vec<real, 3>(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
	explicit Vec<real, 3>(real x, real y, real z) : x(x), y(y), z(z) {}

	v2 as_v2() const { return v2( x, y ); }
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

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }

	explicit Vec<real, 4>() {}
	explicit Vec<real, 4>(real xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	explicit Vec<real, 4>(const v3& xyz, real w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	explicit Vec<real, 4>(const v2& xy, real z, real w) : x(xy.x), y(xy.y), z(z), w(w) {}
	explicit Vec<real, 4>(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}

	v3 as_v3() const { return v3( x, y, z ); }
};

template<typename T, size_t n>
AS_INLINE T dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	T result = 0;
	for (size_t i = 0; i < n; ++i) {
		result += lhs[i] * rhs[i];
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE T length_squared(const Vec<T, n>& vec)
{
	T result = 0;
	for (size_t i = 0; i < n; ++i) {
		result += vec[i] * vec[i];
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE T length(const Vec<T, n>& vec)
{
	return std::sqrt(length_squared(vec));
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> normalize(const Vec<T, n>& vec)
{
	T len = length(vec);
	return vec / len;
}

template<typename T, size_t n>
AS_INLINE T normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out)
{
	T len = length(vec);
	out = vec / len;
	return len;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = lhs[i] + rhs[i];
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	for (size_t i = 0; i < n; ++i) {
		lhs[i] += rhs[i];
	}
	return lhs;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = lhs[i] - rhs[i];
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	for (size_t i = 0; i < n; ++i) {
		lhs[i] -= rhs[i];
	}
	return lhs;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = -vec[i];
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator*(const Vec<T, n>& vec, T val)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] * val;
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator*(T val, const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] * val;
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE void operator*=(Vec<T, n>& vec, T val)
{
	for (size_t i = 0; i < n; ++i) {
		vec[i] *= val;
	}
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator/(const Vec<T, n>& vec, T val)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[i] = vec[i] / val;
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE void operator/=(Vec<T, n>& vec, T val)
{
	for (size_t i = 0; i < n; ++i) {
		vec[i] /= val;
	}
}

// constants

extern const v3 v3_x;
extern const v3 v3_y;
extern const v3 v3_z;
extern const v3 v3_zero;
extern const v3 v3_one;

AS_INLINE v3 cross(const v3& lhs, const v3& rhs)
{
	v3 result;
	result[0] = lhs.y * rhs.z - lhs.z * rhs.y;
	result[1] = lhs.z * rhs.x - lhs.x * rhs.z;
	result[2] = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

AS_INLINE v3 across_and_up(const v3& dir, v3& across, v3& up, const v3& initial_up = v3_y)
{
	// v3 rel_up = 
	return v3_zero;
}

}