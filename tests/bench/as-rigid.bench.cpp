#include "as/as-math-ops.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

using as::operator""_r;

TEST_CASE("as-rigid", "[as_rigid]")
{
  BENCHMARK_ADVANCED("as-rigid-inverse")(Catch::Benchmark::Chronometer meter)
  {
    as::rigid r = as::rigid{
      as::quat_rotation_axis(as::vec3::axis_x(), as::radians(45.0_r)),
      as::vec3(1.0_r, 2.0_r, 3.0_r)};

    meter.measure([&r] { return as::rigid_inverse(r); });
  };
}
