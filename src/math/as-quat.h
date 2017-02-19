#pragma once

#include <ASframework/Maths/AsVec.h>

namespace as
{

__pragma(warning(push))
__pragma(warning(disable:4201))

struct quat
{
	union
	{
		float data[4];
		struct { float r; float i; float j; float k; };
	};

	AS_INLINE float& operator[](int i) { return data[i]; }
	AS_INLINE const float& operator[](int i) const { return data[i]; }
};

__pragma(warning(pop))

AS_INLINE quat make_quat(float r, float i, float j, float k)
{
	quat result { r, i, j, k };
	return result;
}

AS_INLINE quat make_quat(float r, const float3& ijk)
{
	quat result{ r, ijk.x, ijk.y, ijk.z };
	return result;
}

AS_INLINE quat identity()
{
	quat result{ 1, 0, 0, 0 };
	return result;
}

AS_INLINE quat operator*(const quat& a, const quat& b)
{
	return make_quat(a.r*b.r - a.i*b.i - a.j*b.j - a.k*b.k,
					 a.r*b.i + a.i*b.r + a.j*b.k - a.k*b.j,
					 a.r*b.j + a.j*b.r + a.k*b.i - a.i*b.k,
					 a.r*b.k + a.k*b.r + a.i*b.j - a.j*b.i);
}

AS_INLINE quat operator*=(quat& a, quat& b)
{
	a = a * b;
	return a;
}

AS_INLINE quat operator+(const quat& a, const quat& b)
{
	quat result;
	for (int i = 0; i < 4; ++i) {
		result.data[i] = a.data[i] + b.data[i];
	}
	return result;
}

AS_INLINE quat operator/(float a, const quat& b)
{
	quat result;
	for (size_t i = 0; i < 4; ++i) {
		result.data[i] = a / b.data[i];
	}
	return result;
}

AS_INLINE quat operator/(const quat& a, float b)
{
	quat result;
	for (int i = 0; i < 4; ++i) {
		result.data[i] = a.data[i] / b;
	}
	return result;
}

AS_INLINE quat operator*(float a, const quat& b)
{
	quat result;
	for (size_t i = 0; i < 4; ++i) {
		result.data[i] = a * b.data[i];
	}
	return result;
}

AS_INLINE quat operator*(const quat& a, float b)
{
	quat result;
	for (int i = 0; i < 4; ++i) {
		result.data[i] = a.data[i] * b;
	}
	return result;
}

AS_INLINE float dot(const quat& a, const quat& b)
{
	return a.r*b.r + a.i*b.i + a.j*b.j + a.k*b.k;
}

AS_INLINE float lengthSquared(const quat& a)
{
	return dot(a, a);
}

AS_INLINE float length(const quat& a)
{
	return std::sqrt(lengthSquared(a));
}

AS_INLINE quat normalize(const quat& a)
{
	return a / length(a);
}

AS_INLINE quat conjugate(const quat& a)
{
	return make_quat(a.r, -a.i, -a.j, -a.k);
}

AS_INLINE quat inverse(const quat& a)
{
	return conjugate(a) / lengthSquared(a);
}

AS_INLINE float3 rotate(const quat& q, const float3& v)
{
	quat t = { 0, v.x, v.y, v.z };
	quat quat_result = q * t * conjugate(q);
	return make_float3(quat_result.i, quat_result.j, quat_result.k);
}

AS_INLINE quat quat_rotation_axis_angle(const float3& axis, float radians)
{
	float sinHalfTheta = sinf(0.5f * radians);
	float cosHalfTheta = cosf(0.5f * radians);

	return make_quat(cosHalfTheta, axis * sinHalfTheta);
}

AS_INLINE quat quat_rotation_zxy(float x, float y, float z)
{
	float sinHalfX = sinf(0.5f * x);
	float cosHalfX = cosf(0.5f * x);
	float sinHalfY = sinf(0.5f * y);
	float cosHalfY = cosf(0.5f * y);
	float sinHalfZ = sinf(0.5f * z);
	float cosHalfZ = cosf(0.5f * z);

	quat quatX = make_quat(cosHalfX, sinHalfX, 0, 0);
	quat quatY = make_quat(cosHalfY, 0, sinHalfY, 0);
	quat quatZ = make_quat(cosHalfZ, 0, 0, sinHalfZ);

	return quatY * quatX * quatZ;
}

quat slerp(const quat& a, const quat& b, float u)
{
	float theta = acosf(dot(a, b));
	return (a * sinf((1.0f - u) * theta) + b * sinf(u * theta)) / sinf(theta);
}

}