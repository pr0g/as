namespace as
{

template<typename T>
AS_API constexpr T lerp(const T t, const T v0, const T v1)
{
    return (T(1) - t) * v0 + t * v1;
}

template<typename T>
AS_API constexpr T smooth_step(const T t, const T v0, const T v1)
{
    T val = (t * t) * (T(3) - T(2) * t);
    return lerp(val, v0, v1);
}

template<typename T>
AS_API constexpr T max(const T v0, const T v1)
{
    return v0 > v1 ? v0 : v1;
}

template<typename T>
AS_API constexpr T min(const T v0, const T v1)
{
    return v0 < v1 ? v0 : v1;
}

template<typename T>
AS_API constexpr T clamp(const T t, const T v0, const T v1)
{
    return t < v0 ? v0 : t > v1 ? v1 : t;
}

template<typename T>
AS_API constexpr T snap(const T in, const T step)
{
    return std::floor((in / step) + T(0.5)) * step;
}

AS_API constexpr real_t deg_to_rad(const real_t degrees)
{
    return degrees * DEG_TO_RAD;
}

AS_API constexpr real_t rad_to_deg(const real_t radians)
{
    return radians * RAD_TO_DEG;
}

// floating point comparison by Bruce Dawson
// ref:
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
AS_API inline bool equal(
    real_t a, real_t b,
    const real_t max_diff /*= std::numeric_limits<real_t>::epsilon()*/,
    const real_t max_rel_diff /*= std::numeric_limits<real_t>::epsilon()*/)
{
    // check if the numbers are really close
    // needed when comparing numbers near zero
    const real_t diff = std::abs(a - b);

    if (diff <= max_diff) {
        return true;
    }

    a = std::abs(a);
    b = std::abs(b);
    const real_t largest = b > a ? b : a;

    // find relative difference
    return diff <= largest * max_rel_diff;
}

} // namespace as
