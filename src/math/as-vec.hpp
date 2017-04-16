#pragma once

#include "core/as-types.hpp"
#include "core/as-assert.hpp"

#include "as-math.hpp"

namespace as
{

template<typename T, size_t n>
struct Vec
{
	T data[n];
	AS_INLINE T& operator[](size_t i) { return data[i]; }
	AS_INLINE const T& operator[](size_t i) const { return data[i]; }

	Vec() {}
	Vec(Vec&&) = default;
	Vec(const Vec&) = default;
	Vec& operator=(const Vec&) = default;

	template< typename... > struct typelist;
	template <typename... Args, typename = std::enable_if_t<!std::is_same<typelist<Vec>, typelist<std::decay_t<Args>...>>::value>>
	Vec(Args&&... args) : data{ std::forward<Args>(args)... } {}
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

	explicit Vec() {}
	constexpr explicit Vec(real xy) : x(xy), y(xy) {}
	constexpr explicit Vec(real x, real y) : x(x), y(y) {}
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

	explicit Vec() {}
	constexpr explicit Vec(real xyz) : x(xyz), y(xyz), z(xyz) {}
	constexpr explicit Vec(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
	constexpr explicit Vec(real x, real y, real z) : x(x), y(y), z(z) {}
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

	explicit Vec() {}
	constexpr explicit Vec(real xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	constexpr explicit Vec(const v3& xyz, real w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	constexpr explicit Vec(const v2& xy, real z, real w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr explicit Vec(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}
};

template<typename T, size_t n>
AS_INLINE const T* data(const Vec<T, n>& vec)
{
	return vec.data;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> make_from(const T(&data)[n])
{
	Vec<T, n> result;
	memcpy(result.data, data, sizeof(T) * n);
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> make_from(const T* data)
{
	Vec<T, n> result;
	memcpy(result.data, data, sizeof(T) * n);
	return result;
}

template<typename T>
AS_INLINE v2 make_v2_from(const T* data)
{
	return make_from<T, 2>(data);
}

template<typename T>
AS_INLINE v3 make_v3_from(const T* data)
{
	return make_from<T, 3>(data);
}

template<typename T>
AS_INLINE v4 make_v4_from(const T* data)
{
	return make_from<T, 4>(data);
}

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
	return sqrt(length_squared(vec));
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

template<typename T, size_t n>
AS_INLINE bool equal(const Vec<T, n>& lhs, const Vec<T, n>& rhs, real epsilon = REAL_EPSILON)
{
	bool eq = true;
	for (size_t i = 0; i < n; ++i) {
		eq &= equal(lhs[i], rhs[i], epsilon, epsilon);
		if (!eq) { break; }
	}
	return eq;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> min(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = min(lhs[i], rhs[i]);
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE T min_elem(const Vec<T, n>& vec)
{
	T val = vec[0];
	for (size_t i = 1; i < n; ++i) {
		val = min(val, vec[i]);
	}
	return val;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> max(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = max(lhs[i], rhs[i]);
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE T max_elem(const Vec<T, n>& vec)
{
	T val = vec[0];
	for (size_t i = 1; i < n; ++i) {
		val = max(val, vec[i]);
	}
	return val;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> abs(const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = absr(vec[i]);
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> clamp(const Vec<T, n>& vec, const Vec<T, n>& min, const Vec<T, n>& max)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = clamp( vec[ i ], min[ i ], max[ i ] );
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> saturate(const Vec<T, n>& vec)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = clamp( vec[ i ], 0.0f, 1.0f );
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> lerp(T t, const Vec<T, n>& v0, const Vec<T, n>& v1)
{
	Vec<T, n> result;
	for (size_t i = 0; i < n; ++i) {
		result[ i ] = lerp(t, v0[i], v1[i]);
	}
	return result;
}

template<typename T, size_t n>
AS_INLINE Vec<T, n> select(const Vec<T, n>& v0, const Vec<T, n>& v1, bool select0)
{
	return select0 ? v0 : v1;
}

// constants

const v2 v2_x(1.0f, 0.0f);
const v2 v2_y(0.0f, 1.0f);
const v2 v2_zero(0.0f, 0.0f);
const v2 v2_one(1.0f, 1.0f);
const v2 v2_max(REAL_MAX, REAL_MAX);
const v2 v2_min(REAL_MIN, REAL_MIN);

const v3 v3_x(1.0f, 0.0f, 0.0f);
const v3 v3_y(0.0f, 1.0f, 0.0f);
const v3 v3_z(0.0f, 0.0f, 1.0f);
const v3 v3_zero(0.0f, 0.0f, 0.0f);
const v3 v3_one(1.0f, 1.0f, 1.0f);
const v3 v3_max(REAL_MAX, REAL_MAX, REAL_MAX);
const v3 v3_min(REAL_MIN, REAL_MIN, REAL_MIN);

const v4 v4_x(1.0f, 0.0f, 0.0f, 0.0f);
const v4 v4_y(0.0f, 1.0f, 0.0f, 0.0f);
const v4 v4_z(0.0f, 0.0f, 1.0f, 0.0f);
const v4 v4_w(0.0f, 0.0f, 0.0f, 1.0f);
const v4 v4_zero(0.0f, 0.0f, 0.0f, 0.0f);
const v4 v4_one(1.0f, 1.0f, 1.0f, 1.0f);
const v4 v4_max(REAL_MAX, REAL_MAX, REAL_MAX, REAL_MAX);
const v4 v4_min(REAL_MIN, REAL_MIN, REAL_MIN, REAL_MIN);

AS_INLINE v3 cross(const v3& lhs, const v3& rhs)
{
	v3 result;
	result[0] = lhs.y * rhs.z - lhs.z * rhs.y;
	result[1] = lhs.z * rhs.x - lhs.x * rhs.z;
	result[2] = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

// note: will not work if dir == +/-world_up
AS_INLINE void right_and_up_lh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_y)
{
	AS_ASSERT_DESC( !equal(dir, world_up), "dir and world_up are equal");

	across = cross(dir, world_up);
	up = normalize(cross(across, dir));
	across = normalize(cross(up, dir));
}

// note: will not work if dir == +/-world_up
AS_INLINE void right_and_up_rh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_y)
{
	AS_ASSERT_DESC( !equal(dir, world_up), "dir and world_up are equal");

	across = cross(dir, world_up);
	up = normalize(cross(across, dir));
	across = normalize(cross(dir, up));
}

}