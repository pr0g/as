namespace as
{

template<typename T>
inline T lerp(T t, T v0, T v1)
{
    return ((T)1 - t) * v0 + t * v1;
}

template<typename T>
inline T smooth_step(T t, T v0, T v1)
{
    T val = (t * t) * ((T)3 - (T)2 * t);
    return lerp(v0, v1, val);
}

template<typename T>
inline T max(T v0, T v1)
{
    return v0 > v1 ? v0 : v1;
}

template<typename T>
inline T min(T v0, T v1)
{
    return v0 < v1 ? v0 : v1;
}

template<typename T>
inline T clamp(T t, T v0, T v1)
{
    return t < v0 ? v0 : t > v1 ? v1 : t;
}

inline real deg_to_rad(real degrees)
{
    return degrees * DEG_TO_RAD;
}

inline real rad_to_deg(real radians)
{
    return radians * RAD_TO_DEG;
}

// floating point comparison by Bruce Dawson
// ref: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
inline bool equal(
    real a, real b,
    real max_diff /*= std::numeric_limits<real>::epsilon()*/,
    real max_rel_diff /*= std::numeric_limits<real>::epsilon()*/)
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