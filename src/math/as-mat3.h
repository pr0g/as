#pragma once

#include <ASframework/Maths/AsMat.h>

namespace as
{

typedef Mat<float, 3, 3> float33;

__pragma(warning(push))
__pragma(warning(disable:4201))

template<> struct Mat<float, 3, 3>
{
	union
	{
		float data[3 * 3];
		struct { float3 right; float3 up; float3 forward; };
	};

	AS_INLINE float& operator[](size_t i) { return data[i]; }
	AS_INLINE const float& operator[](size_t i) const { return data[i]; }
};

__pragma(warning(pop))

AS_INLINE float33 make_float33(float3 right, float3 up, float3 forward)
{
	float33 result;
	result.right = right;
	result.up = up;
	result.forward = forward;
	return result;
}

AS_INLINE float33 make_float33(float x1, float y1, float z1,
							   float x2, float y2, float z2,
							   float x3, float y3, float z3)
{
	float33 result;
	result[0] = x1; result[1] = y1; result[2] = z1;
	result[3] = x2; result[4] = y2; result[5] = z2;
	result[6] = x3; result[7] = y3; result[8] = z3;
	return result;
}

AS_INLINE float33 axis_angle_rotation(float3 axis, float radians)
{
	float33 result;
	result[0] = cosf(radians) + ((axis.x * axis.x) * (1.0f - cosf(radians)));
	result[1] = (axis.y * axis.x * (1.0f - cosf(radians))) + (axis.z * sinf(radians));
	result[2] = (axis.z * axis.x * (1.0f - cosf(radians))) - (axis.y * sinf(radians));
	result[3] = (axis.x * axis.y) * (1.0f - cosf(radians)) - (axis.z * sinf(radians));
	result[4] = cosf(radians) + ((axis.y * axis.y) * (1.0f - cosf(radians)));
	result[5] = (axis.z * axis.y * (1.0f - cosf(radians))) + (axis.x * sinf(radians));
	result[6] = (axis.x * axis.z * (1.0f - cosf(radians))) + (axis.y * sinf(radians));
	result[7] = (axis.y * axis.z * (1.0f - cosf(radians))) - (axis.x * sinf(radians));
	result[8] = cosf(radians) + ((axis.z * axis.z) * (1.0f - cosf(radians)));
	return result;
}

AS_INLINE float33 make_rotation_xyz(float x, float y, float z)
{
	float33 result;
	result[0] =  cosf(y) * cosf(z);
	result[1] =  cosf(y) * sinf(z);
	result[2] = -sinf(y);
	result[3] = (sinf(x) * sinf(y) * cosf(z)) - (cosf(x) * sinf(z));
	result[4] = (sinf(x) * sinf(y) * sinf(z)) + (cosf(x) * cosf(z));
	result[5] =  sinf(x) * cosf(y);
	result[6] = (cosf(x) * sinf(y) * cosf(z)) + (sinf(x) * sinf(z));
	result[7] = (cosf(x) * sinf(y) * sinf(z)) - (sinf(x) * cosf(z));
	result[8] =  cosf(x) * cosf(y);
	return result;
}

AS_INLINE float33 make_rotation_zxy(float x, float y, float z)
{
	float33 result;
	result[0] =  cosf(z) * cosf(y) + sinf(x) * sinf(y) * sinf(z);
	result[1] =  sinf(z) * cosf(x);
	result[2] = -sinf(y) * cosf(z) + sinf(z) * sinf(x) * cosf(y);
	result[3] = -sinf(z) * cosf(y) + cosf(z) * sinf(x) * sinf(y);
	result[4] =  cosf(z) * cosf(x);
	result[5] = -sinf(z) * -sinf(y) + cosf(z) * sinf(x) * cosf(y);
	result[6] =  cosf(x) * sinf(y);
	result[7] = -sinf(x);
	result[8] =  cosf(x) * cosf(y);
	return result;
}

AS_INLINE float33 make_rotation_x(float radians)
{
	float33 result;
	result[0] = 1.0f;
	result[1] = 0.0f;
	result[2] = 0.0f;
	result[3] = 0.0f;
	result[4] = cosf(radians);
	result[5] = sinf(radians);
	result[6] = 0.0f;
	result[7] = -sinf(radians);
	result[8] = cosf(radians);
	return result;
}

AS_INLINE float33 make_rotation_y(float radians)
{
	float33 result;
	result[0] = cosf(radians);
	result[1] = 0.0f;
	result[2] = -sinf(radians);
	result[3] = 0.0f;
	result[4] = 1.0f;
	result[5] = 0.0f;
	result[6] = sinf(radians);
	result[7] = 0.0f;
	result[8] = cosf(radians);
	return result;
}

AS_INLINE float33 make_rotation_z(float radians)
{
	float33 result;
	result[0] = cosf(radians);
	result[1] = sinf(radians);
	result[2] = 0.0f;
	result[3] = -sinf(radians);
	result[4] = cosf(radians);
	result[5] = 0.0f;
	result[6] = 0.0f;
	result[7] = 0.0f;
	result[8] = 1.0f;
	return result;
}

}