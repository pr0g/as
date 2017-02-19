#pragma once

#include "as-mat.h"

namespace as
{

typedef Mat<real, 3, 3> m33;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real, 3, 3>
{
	union
	{
		real data[3 * 3];
		struct { v3 right; v3 up; v3 forward; };
	};

	AS_INLINE real& operator[](size_t i) { return data[i]; }
	AS_INLINE const real& operator[](size_t i) const { return data[i]; }
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

AS_INLINE m33 make_m33(v3 right, v3 up, v3 forward)
{
	m33 result;
	result.right = right;
	result.up = up;
	result.forward = forward;
	return result;
}

AS_INLINE m33 make_m33(real x1, real y1, real z1,
							   real x2, real y2, real z2,
							   real x3, real y3, real z3)
{
	m33 result;
	result[0] = x1; result[1] = y1; result[2] = z1;
	result[3] = x2; result[4] = y2; result[5] = z2;
	result[6] = x3; result[7] = y3; result[8] = z3;
	return result;
}

AS_INLINE m33 axis_angle_rotation(v3 axis, real radians)
{
	m33 result;
	result[0] = cosr(radians) + ((axis.x * axis.x) * (1.0f - cosr(radians)));
	result[1] = (axis.y * axis.x * (1.0f - cosr(radians))) + (axis.z * sinr(radians));
	result[2] = (axis.z * axis.x * (1.0f - cosr(radians))) - (axis.y * sinr(radians));
	result[3] = (axis.x * axis.y) * (1.0f - cosr(radians)) - (axis.z * sinr(radians));
	result[4] = cosr(radians) + ((axis.y * axis.y) * (1.0f - cosr(radians)));
	result[5] = (axis.z * axis.y * (1.0f - cosr(radians))) + (axis.x * sinr(radians));
	result[6] = (axis.x * axis.z * (1.0f - cosr(radians))) + (axis.y * sinr(radians));
	result[7] = (axis.y * axis.z * (1.0f - cosr(radians))) - (axis.x * sinr(radians));
	result[8] = cosr(radians) + ((axis.z * axis.z) * (1.0f - cosr(radians)));
	return result;
}

AS_INLINE m33 make_rotation_xyz(real x, real y, real z)
{
	m33 result;
	result[0] =  cosr(y) * cosr(z);
	result[1] =  cosr(y) * sinr(z);
	result[2] = -sinr(y);
	result[3] = (sinr(x) * sinr(y) * cosr(z)) - (cosr(x) * sinr(z));
	result[4] = (sinr(x) * sinr(y) * sinr(z)) + (cosr(x) * cosr(z));
	result[5] =  sinr(x) * cosr(y);
	result[6] = (cosr(x) * sinr(y) * cosr(z)) + (sinr(x) * sinr(z));
	result[7] = (cosr(x) * sinr(y) * sinr(z)) - (sinr(x) * cosr(z));
	result[8] =  cosr(x) * cosr(y);
	return result;
}

AS_INLINE m33 make_rotation_zxy(real x, real y, real z)
{
	m33 result;
	result[0] =  cosr(z) * cosr(y) + sinr(x) * sinr(y) * sinr(z);
	result[1] =  sinr(z) * cosr(x);
	result[2] = -sinr(y) * cosr(z) + sinr(z) * sinr(x) * cosr(y);
	result[3] = -sinr(z) * cosr(y) + cosr(z) * sinr(x) * sinr(y);
	result[4] =  cosr(z) * cosr(x);
	result[5] = -sinr(z) * -sinr(y) + cosr(z) * sinr(x) * cosr(y);
	result[6] =  cosr(x) * sinr(y);
	result[7] = -sinr(x);
	result[8] =  cosr(x) * cosr(y);
	return result;
}

AS_INLINE m33 make_rotation_x(real radians)
{
	m33 result;
	result[0] = 1.0f;
	result[1] = 0.0f;
	result[2] = 0.0f;
	result[3] = 0.0f;
	result[4] = cosr(radians);
	result[5] = sinr(radians);
	result[6] = 0.0f;
	result[7] = -sinr(radians);
	result[8] = cosr(radians);
	return result;
}

AS_INLINE m33 make_rotation_y(real radians)
{
	m33 result;
	result[0] = cosr(radians);
	result[1] = 0.0f;
	result[2] = -sinr(radians);
	result[3] = 0.0f;
	result[4] = 1.0f;
	result[5] = 0.0f;
	result[6] = sinr(radians);
	result[7] = 0.0f;
	result[8] = cosr(radians);
	return result;
}

AS_INLINE m33 make_rotation_z(real radians)
{
	m33 result;
	result[0] = cosr(radians);
	result[1] = sinr(radians);
	result[2] = 0.0f;
	result[3] = -sinr(radians);
	result[4] = cosr(radians);
	result[5] = 0.0f;
	result[6] = 0.0f;
	result[7] = 0.0f;
	result[8] = 1.0f;
	return result;
}

}