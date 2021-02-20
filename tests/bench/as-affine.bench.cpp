#include "as/as-math-ops.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "catch2/catch_test_macros.hpp"

using as::operator""_r;

TEST_CASE("as-affine", "[as_affine]")
{
  BENCHMARK_ADVANCED("as-affine-inverse")(Catch::Benchmark::Chronometer meter)
  {
    as::affine a = as::affine{
      as::mat3_rotation_x(as::radians(45.0_r)), as::vec3(1.0_r, 2.0_r, 3.0_r)};

    meter.measure([&a] { return as::affine_inverse(a); });
  };
}
