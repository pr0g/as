#include "as/as-math-ops.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

using as::operator""_r;

TEST_CASE("as-vec", "[as_vec]")
{
  BENCHMARK("as-vec-dot")
  {
    return as::vec_dot(
      as::vec3{1.0_r, 2.0_r, 3.0_r}, as::vec3{5.0_r, 6.0_r, 7.0_r});
  };

  BENCHMARK("as-vec-min-elem")
  {
    return as::vec_min_elem(as::vec3{5.0_r, 2.0_r, 3.0_r});
  };

  BENCHMARK("as-vec-min-elem-algo")
  {
    as::vec3 a{5.0_r, 2.0_r, 3.0_r};
    return std::min_element(as::begin(a), as::end(a));
  };
}
