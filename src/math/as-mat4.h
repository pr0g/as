#pragma once

#include "as-mat.h"
#include "as-mat3.h"

namespace as
{

using m44 = Mat<real, 4, 4>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real, 4, 4>
{
	union
	{
		real data[4 * 4];
		real data_cr[4][4];
		struct { real x0; real y0; real z0; real w0; 
				 real x1; real y1; real z1; real w1;
				 real x2; real y2; real z2; real w2;
				 real x3; real y3; real z3; real w3; };
		struct { v4 v_0; v4 v_1; v4 v_2; v4 v_3; };
		struct { v4 v[4]; };
	};

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }

	explicit Mat<real, 4, 4>() {}
	explicit Mat<real, 4, 4>(const real(&data_)[16]) { 
		for ( size_t i = 0; i < 16; ++i ) { data[ i ] = data_[ i ]; }
	}
	explicit Mat<real, 4, 4>(const real* data_) { 
		for ( size_t i = 0; i < 16; ++i ) { data[ i ] = data_[ i ]; }
	}
	constexpr explicit Mat<real, 4, 4>(real x0, real y0, real z0, real w0, real x1, real y1, real z1, real w1, real x2, real y2, real z2, real w2, real x3, real y3, real z3, real w3)
		:  x0(x0), y0(y0), z0(z0), w0(w1), x1(x1), y1(y1), z1(z1), w1(w1), x2(x2), y2(y2), z2(z2), w2(w2), x3(x3), y3(y3), z3(z3), w3(w3) {}
	constexpr explicit Mat<real, 4, 4>(const v4& v_0, const v4& v_1, const v4& v_2, const v4& v_3)
		: v_0(v_0), v_1(v_1), v_2(v_2), v_3(v_3) {}
	constexpr explicit Mat<real, 4, 4>(const m33& mat, const v3& vec) : v_0(mat.v_0, 0.0f), v_1(mat.v_1, 0.0f), v_2(mat.v_2, 0.0f), v_3(vec, 1.0f) {}
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

// openGL default
AS_INLINE m44 make_perspective_gl_rh(real fovy, real aspect, real n, real f)
{
	m44 result;
	memset(&result, 0, sizeof(result));

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
	memset(&result, 0, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = ((f + n) / (f - n));
	result[11] = 1.0f;
	result[14] = -((2.0f * f * n) / (f - n));

	return result;
}

// directX default
AS_INLINE m44 make_perspective_d3d_lh(real fovy, real aspect, real n, real f)
{
	m44 result;
	memset(&result, 0, sizeof(result));

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
	memset(&result, 0, sizeof(result));

	real e = 1.0f / tanr(fovy * 0.5f);

	result[0] = e / aspect;
	result[5] = e;
	result[10] = -f / (f - n);
	result[11] = -1.0f;
	result[14] = -((f * n) / (f - n));

	return result;
}

// openGL default
AS_INLINE m44 make_ortho_gl_rh(real l, real r, real b, real t, real n, real f)
{
	m44 result;
	memset(&result, 0, sizeof(result));

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

// directx default
AS_INLINE m44 make_ortho_d3d_lh(real l, real r, real b, real t, real n, real f)
{
	m44 result;
	memset(&result, 0, sizeof(result));

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