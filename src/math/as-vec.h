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

typedef Vec<float, 2> float2;
typedef Vec<float, 3> float3;
typedef Vec<float, 4> float4;

template<> struct Vec<float, 2>
{
	union
	{
		float data[2];
		struct { float x; float y; };
	};

	AS_INLINE float& operator[](int i) { return data[i]; }
	AS_INLINE const float& operator[](int i) const { return data[i]; }
};

template<> struct Vec<float, 3>
{
	union
	{
		float data[3];
		struct { float x; float y; float z; };
		float2 xy;
	};

	AS_INLINE float& operator[](int i) { return data[i]; }
	AS_INLINE const float& operator[](int i) const { return data[i]; }

	static const float3 right;
	static const float3 up;
	static const float3 forward;
};

template<> struct Vec<float, 4>
{
	union
	{
		float data[4];
		struct { float x; float y; float z; float w; };
		struct { float r; float g; float b; float a; };
		float2 xy;
		float3 xyz;
		float3 rgb;
	};

	AS_INLINE float& operator[](int i) { return data[i]; }
	AS_INLINE const float& operator[](int i) const { return data[i]; }
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
AS_INLINE float normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out)
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

AS_INLINE float2 make_float2(float x, float y)
{
	float2 result;
	result[0] = x;
	result[1] = y;
	return result;
}

AS_INLINE float2 make_float2(float val)
{
	float2 result;
	result[0] = val;
	result[1] = val;
	return result;
}

AS_INLINE float3 make_float3(float x, float y, float z)
{
	float3 result;
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return result;
}

AS_INLINE float3 make_float3(float val)
{
	float3 result;
	result[0] = val;
	result[1] = val;
	result[2] = val;
	return result;
}

AS_INLINE float3 cross(const float3& lhs, const float3& rhs)
{
	float3 result;
	result[0] = lhs.y * rhs.z - lhs.z * rhs.y;
	result[1] = lhs.z * rhs.x - lhs.x * rhs.z;
	result[2] = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

AS_INLINE float4 make_float4(float x, float y, float z, float w)
{
	float4 result;
	result[0] = x;
	result[1] = y;
	result[2] = z;
	result[3] = w;
	return result;
}

AS_INLINE float4 make_float4(float val)
{
	float4 result;
	result[0] = val;
	result[1] = val;
	result[2] = val;
	result[3] = val;
	return result;
}

AS_INLINE float4 make_float4(const float3& xyz, float w)
{
	float4 result;
	result[0] = xyz.x;
	result[1] = xyz.y;
	result[2] = xyz.z;
	result[3] = w;
	return result;
}

}