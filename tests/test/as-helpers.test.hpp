#pragma once

#include "as/as-math-ops.hpp"
#include "catch2/catch_tostring.hpp"

#include <array>
#include <sstream>

namespace unit_test
{

template<typename T>
constexpr bool trivial_standard_layout_check()
{
  static_assert(std::is_trivially_copyable_v<T>);
  static_assert(std::is_trivially_constructible_v<T>);
  static_assert(std::is_trivially_default_constructible_v<T>);
  static_assert(std::is_trivially_copy_constructible_v<T>);
  static_assert(std::is_trivially_move_constructible_v<T>);
  static_assert(std::is_trivially_assignable_v<T&, T>);
  static_assert(std::is_trivially_copy_assignable_v<T>);
  static_assert(std::is_trivially_move_assignable_v<T>);
  static_assert(std::is_trivially_destructible_v<T>);
  static_assert(std::is_standard_layout_v<T>);

  return true;
}

template<typename T>
std::array<T, 2> arr(const T x, const T y)
{
  return std::array<T, 2>{{x, y}};
}

template<typename T>
std::array<T, 3> arr(const T x, const T y, const T z)
{
  return std::array<T, 3>{{x, y, z}};
}

template<typename T>
std::array<T, 4> arr(const T x, const T y, const T z, const T w)
{
  return std::array<T, 4>{{x, y, z, w}};
}

template<typename T, as::index d>
std::string print_vec(const as::vec<T, d>& vec)
{
  std::stringstream ss;
  ss << "{ ";
  for (as::index i = 0; i < d - 1; ++i) {
    ss << std::to_string(vec[i]) << ", ";
  }
  ss << std::to_string(vec[d - 1]) << " }";
  return ss.str();
}

} // namespace unit_test

namespace Catch
{

template<>
struct StringMaker<as::vec2>
{
  static std::string convert(const as::vec2& vec)
  {
    return unit_test::print_vec(vec);
  }
};

template<>
struct StringMaker<as::vec3>
{
  static std::string convert(const as::vec3& vec)
  {
    return unit_test::print_vec(vec);
  }
};

template<>
struct StringMaker<as::vec4>
{
  static std::string convert(const as::vec4& vec)
  {
    return unit_test::print_vec(vec);
  }
};

} // namespace Catch
