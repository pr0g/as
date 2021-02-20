#include "as/as-math-ops.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "catch2/catch_test_macros.hpp"

using as::operator""_r;

TEST_CASE("as-mat", "[as_mat]")
{
  BENCHMARK_ADVANCED("as-mat-inverse")(Catch::Benchmark::Chronometer meter)
  {
    as::mat4 transform = as::mat4_from_mat3_vec3(
      as::mat3_rotation_x(as::radians(45.0_r)), as::vec3{1.0_r, 2.0_r, 3.0_r});

    meter.measure([&transform] { return as::mat_inverse(transform); });
  };
}
