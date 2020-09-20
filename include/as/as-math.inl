namespace as
{

template<typename T>
AS_API constexpr T lerp(const T t, const T begin, const T end)
{
  return (T(1) - t) * begin + t * end;
}

template<typename T>
AS_API constexpr T smooth_step(const T t, const T begin, const T end)
{
  const T val = t * t * (T(3) - T(2) * t);
  return lerp(val, begin, end);
}

template<typename T>
AS_API constexpr T smoother_step(const T t, const T begin, const T end)
{
  const T val = t * t * t * (t * (t * T(6) - T(15)) + T(10));
  return lerp(val, begin, end);
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
AS_API constexpr T clamp(const T in, const T low, const T high)
{
  return in < low ? low : in > high ? high : in;
}

template<typename T>
AS_API constexpr T snap(const T in, const T step)
{
  return std::floor((in / step) + T(0.5)) * step;
}

AS_API constexpr real_t deg_to_rad(const real_t degrees)
{
  constexpr real_t k_deg_to_rad = kPi / 180.0_r;
  return degrees * k_deg_to_rad;
}

AS_API constexpr real_t rad_to_deg(const real_t radians)
{
  constexpr real_t k_rad_to_deg = 180.0_r / kPi;
  return radians * k_rad_to_deg;
}

// floating p comparison by Bruce Dawson
// ref:
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
AS_API inline bool almost_equal(
  const real_t a, const real_t b,
  const real_t max_diff /*= std::numeric_limits<real_t>::epsilon()*/,
  const real_t max_rel_diff /*= std::numeric_limits<real_t>::epsilon()*/)
{
  // check if the numbers are really close
  // needed when comparing numbers near zero
  const real_t diff = std::abs(a - b);

  if (diff <= max_diff) {
    return true;
  }

  const real_t largest = max(std::abs(a), std::abs(b));

  // find relative difference
  return diff <= largest * max_rel_diff;
}

} // namespace as
