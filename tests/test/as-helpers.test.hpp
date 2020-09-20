#pragma once

#include "as/as-math-ops.hpp"

#include <array>

namespace unit_test
{

// types
using as::real;

inline std::array<real, 2> arr(const real x, const real y)
{
  return std::array<real, 2>{x, y};
}

inline std::array<real, 3> arr(const real x, const real y, const real z)
{
  return std::array<real, 3>{x, y, z};
}

inline std::array<real, 4> arr(
  const real x, const real y, const real z, const real w)
{
  return std::array<real, 4>{x, y, z, w};
}

} // namespace unit_test
