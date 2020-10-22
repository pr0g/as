#pragma once

#include "as/as-math-ops.hpp"

#include <array>

namespace unit_test
{

template<typename T>
std::array<T, 2> arr(const T x, const T y)
{
  return std::array<T, 2>{x, y};
}

template<typename T>
std::array<T, 3> arr(const T x, const T y, const T z)
{
  return std::array<T, 3>{x, y, z};
}

template<typename T>
std::array<T, 4> arr(const T x, const T y, const T z, const T w)
{
  return std::array<T, 4>{x, y, z, w};
}

} // namespace unit_test
