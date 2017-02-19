#pragma once

#include <ASframework/Maths/AsMat.h>

namespace as
{

typedef Mat<real, 4, 4> m44;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real, 4, 4>
{
	union
	{
		real data[4 * 4];
		struct { real4 right; real4 up; real4 forward; real4 position; };
	};

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }
};

__pragma(warning(pop))

AS_INLINE m44 make_m44(real4 right, real4 up, real4 forward, real4 position)
{
	m44 result;
	result.right = right;
	result.up = up;
	result.forward = forward;
	result.position = position;
	return result;
}

AS_INLINE m44 make_m44(real x1, real y1, real z1, real w1,
							   real x2, real y2, real z2, real w2,
							   real x3, real y3, real z3, real w3,
							   real x4, real y4, real z4, real w4)
{
	m44 result;
	result[0] = x1; result[1] = y1; result[2] = z1; result[3] = w1;
	result[3] = x2; result[5] = y2; result[6] = z2; result[7] = w2;
	result[8] = x3; result[9] = y3; result[10] = z3; result[11] = w3;
	result[12] = x4; result[13] = y4; result[14] = z4; result[15] = w4;
	return result;
}

// OpenGL Default
AS_INLINE m44 make_perspective_gl_rh(real fovy, real aspect, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = -((f + n) / (f - n));
	result[11] = -1.0f;
	result[14] = -((2.0f * f * n) / (f - n));

	return result;
}

AS_INLINE m44 make_perspective_gl_lh(real fovy, real aspect, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = ((f + n) / (f - n));
	result[11] = 1.0f;
	result[14] = -((2.0f * f * n) / (f - n));

	return result;
}

// DirectX Default
AS_INLINE m44 make_perspective_d3d_lh(real fovy, real aspect, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = f / (f - n);
	result[11] = 1.0f;
	result[14] = -((f * n) / (f - n));

	return result;
}

AS_INLINE m44 make_perspective_d3d_rh(real fovy, real aspect, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = -f / (f - n);
	result[11] = -1.0f;
	result[14] = -((f * n) / (f - n));

	return result;
}

// OpenGL Default
AS_INLINE m44 make_ortho_gl_rh(real l, real r, real b, real t, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real x = 1.0f / (r - l);
	real y = 1.0f / (t - b);
	real z = 1.0f / (f - n);

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
AS_INLINE m44 make_ortho_d3d_lh(real l, real r, real b, real t, real n, real f)
{
	m44 result;
	ZeroMemory(&result, sizeof(result));

	real x = 1.0f / (r - l);
	real y = 1.0f / (t - b);
	real z = 1.0f / (f - n);

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