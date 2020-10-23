namespace as
{

template<typename T>
AS_API constexpr T mix(const T begin, const T end, const T t)
{
  return (T(1.0) - t) * begin + t * end;
}

template<typename T>
AS_API constexpr T smooth_step(const T t)
{
  return t * t * (T(3.0) - T(2.0) * t);
}

template<typename T>
AS_API constexpr T smoother_step(const T t)
{
  return t * t * t * (t * (t * T(6.0) - T(15.0)) + T(10.0));
}

template<typename T>
AS_API constexpr T sign(const T x)
{
  if (x > T(0.0)) {
    return T(1.0);
  }

  if (x < T(0.0)) {
    return T(-1.0);
  }

  return T(0.0);
}

template<typename T>
AS_API constexpr T snap(const T in, const T step)
{
  return std::floor((in / step) + T(0.5)) * step;
}

AS_API constexpr real radians(const real degrees)
{
  constexpr real deg_to_rad = k_pi / 180.0_r;
  return degrees * deg_to_rad;
}

AS_API constexpr real degrees(const real radians)
{
  constexpr real rad_to_deg = 180.0_r / k_pi;
  return radians * rad_to_deg;
}

// floating p comparison by Bruce Dawson
// ref:
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
AS_API inline bool almost_equal(
  const real a, const real b,
  const real max_diff /*= std::numeric_limits<real>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<real>::epsilon()*/)
{
  // check if the numbers are really close
  // needed when comparing numbers near zero
  const real diff = std::abs(a - b);

  if (diff <= max_diff) {
    return true;
  }

  const real largest = max(std::abs(a), std::abs(b));

  // find relative difference
  return diff <= largest * max_rel_diff;
}

} // namespace as
