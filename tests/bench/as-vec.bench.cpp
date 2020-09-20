#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

using as::operator""_r;

TEST_CASE("as-vec", "[as_vec]")
{
  BENCHMARK("as-vec-dot")
  {
    return as::vec_dot(
      as::vec3{1.0_r, 2.0_r, 3.0_r}, as::vec3{5.0_r, 6.0_r, 7.0_r});
  };
}
