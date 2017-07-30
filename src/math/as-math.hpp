#pragma once

#include "src/core/as-types.hpp"

// to get rid of stupid global namespace min and max
// (probably brought in by a lib at this point - need
// rebuild with NOMINMAX - TODO)
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace as
{

const real PI = 3.14159265358979323846f;
const real DEG_TO_RAD = PI / 180.0f;
const real RAD_TO_DEG = 180.0f / PI;

template<typename T>
AS_INLINE T lerp(T t, T v0, T v1)
{
    return ((T)1 - t) * v0 + t * v1;
}

template<typename T>
AS_INLINE T smooth_step(T t, T v0, T v1)
{
    T val = (t * t) * ((T)3 - (T)2 * t);
    return lerp(v0, v1, val);
}

template<typename T>
AS_INLINE T max(T v0, T v1)
{
    return v0 > v1 ? v0 : v1;
}

template<typename T>
AS_INLINE T min(T v0, T v1)
{
    return v0 < v1 ? v0 : v1;
}

template<typename T>
AS_INLINE T clamp(T t, T v0, T v1)
{
    return t < v0 ? v0 : t > v1 ? v1 : t;
}

AS_INLINE real degToRad(real degrees)
{
    return degrees * DEG_TO_RAD;
}

AS_INLINE real radToDeg(real radians)
{
    return radians * RAD_TO_DEG;
}

// floating point comparison by Bruce Dawson
// ref: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
AS_INLINE bool equal(real a, real b, real max_diff = REAL_EPSILON, real max_rel_diff = REAL_EPSILON)
{
    // check if the numbers are really close
    // needed when comparing numbers near zero
    real diff = absr(a - b);
    if (diff <= max_diff) {
        return true;
    }

    a = absr( a );
    b = absr( b );
    real largest = ( b > a ) ? b : a;

    // find relative difference
    return diff <= largest * max_rel_diff;
}

}