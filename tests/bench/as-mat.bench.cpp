#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

using as::operator""_r;

TEST_CASE("as-mat", "[as_mat]")
{
  BENCHMARK_ADVANCED("as-mat-inverse")(Catch::Benchmark::Chronometer meter)
  {
    as::mat4 transform = as::mat4::from_mat3_vec3(
      as::mat3::rotation_x(as::radians(45.0_r)), as::vec3{1.0_r, 2.0_r, 3.0_r});

    meter.measure([&transform] { return as::mat::inverse(transform); });
  };
}
