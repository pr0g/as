#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

using as::operator""_r;

TEST_CASE("as-affine", "[as_affine]")
{
  BENCHMARK_ADVANCED("as-affine-inverse")(Catch::Benchmark::Chronometer meter)
  {
    as::affine_t affine = as::affine_t{
      as::mat3::rotation_x(as::deg_to_rad(45.0_r)),
      as::point3_t{1.0_r, 2.0_r, 3.0_r}};

    meter.measure([&affine] { return as::inverse(affine); });
  };
}
