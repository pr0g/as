#pragma once

#include <ASframework/Maths/AsMat.h>

namespace as
{

typedef Mat<float, 4, 4> float44;

__pragma(warning(push))
__pragma(warning(disable:4201))

template<> struct Mat<float, 4, 4>
{
	union
	{
		float data[4 * 4];
		struct { float4 right; float4 up; float4 forward; float4 position; };
	};

	AS_INLINE float& operator[](size_t i) { return data[i]; }
	AS_INLINE const float& operator[](size_t i) const { return data[i]; }
};

__pragma(warning(pop))

AS_INLINE float44 make_float44(float4 right, float4 up, float4 forward, float4 position)
{
	float44 result;
	result.right = right;
	result.up = up;
	result.forward = forward;
	result.position = position;
	return result;
}

AS_INLINE float44 make_float44(float x1, float y1, float z1, float w1,
							   float x2, float y2, float z2, float w2,
							   float x3, float y3, float z3, float w3,
							   float x4, float y4, float z4, float w4)
{
	float44 result;
	result[0] = x1; result[1] = y1; result[2] = z1; result[3] = w1;
	result[3] = x2; result[5] = y2; result[6] = z2; result[7] = w2;
	result[8] = x3; result[9] = y3; result[10] = z3; result[11] = w3;
	result[12] = x4; result[13] = y4; result[14] = z4; result[15] = w4;
	return result;
}

// OpenGL Default
AS_INLINE float44 make_perspective_gl_rh(float fovy, float aspect, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float e = 1.0f / tanf(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = -((f + n) / (f - n));
	result[11] = -1.0f;
	result[14] = -((2.0f * f * n) / (f - n));

	return result;
}

AS_INLINE float44 make_perspective_gl_lh(float fovy, float aspect, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float e = 1.0f / tanf(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = ((f + n) / (f - n));
	result[11] = 1.0f;
	result[14] = -((2.0f * f * n) / (f - n));

	return result;
}

// DirectX Default
AS_INLINE float44 make_perspective_d3d_lh(float fovy, float aspect, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float e = 1.0f / tanf(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = f / (f - n);
	result[11] = 1.0f;
	result[14] = -((f * n) / (f - n));

	return result;
}

AS_INLINE float44 make_perspective_d3d_rh(float fovy, float aspect, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float e = 1.0f / tanf(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = -f / (f - n);
	result[11] = -1.0f;
	result[14] = -((f * n) / (f - n));

	return result;
}

// OpenGL Default
AS_INLINE float44 make_ortho_gl_rh(float l, float r, float b, float t, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float x = 1.0f / (r - l);
	float y = 1.0f / (t - b);
	float z = 1.0f / (f - n);

	result[0] = 2.0f * x;
	result[5] = 2.0f * y;
	result[10] = -2.0f * z;
	result[12] = -(l + r) * x;
	result[13] = -(b + t) * y;
	result[14] = -(n + f) * z;
	result[15] = 1.0f;

	return result;
}

// DirectX Default
AS_INLINE float44 make_ortho_d3d_lh(float l, float r, float b, float t, float n, float f)
{
	float44 result;
	ZeroMemory(&result, sizeof(result));

	float x = 1.0f / (r - l);
	float y = 1.0f / (t - b);
	float z = 1.0f / (f - n);

	result[0] = 2.0f * x;
	result[5] = 2.0f * y;
	result[10] = z;
	result[12] = -(l + r) * x;
	result[13] = -(b + t) * y;
	result[14] = -n * z;
	result[15] = 1.0f;

	return result;
}

}