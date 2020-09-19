#pragma once

#include "as/as-math-ops.hpp"

#include <array>

namespace unit_test
{

// types
using as::real_t;

inline std::array<real_t, 2> arr(const real_t x, const real_t y)
{
  return std::array<real_t, 2>{x, y};
}

inline std::array<real_t, 3> arr(const real_t x, const real_t y, const real_t z)
{
  return std::array<real_t, 3>{x, y, z};
}

inline std::array<real_t, 4> arr(
  const real_t x, const real_t y, const real_t z, const real_t w)
{
  return std::array<real_t, 4>{x, y, z, w};
}

} // namespace unit_test
