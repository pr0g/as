#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math.hpp"

namespace unit_test
{

// types
using as::real;

// functions
using as::radians;
using as::max;
using as::min;
using as::degrees;
using as::smooth_step;
using as::smoother_step;
using as::operator""_r;

const real g_epsilon = real(std::numeric_limits<float>::epsilon());

TEST_CASE("max", "[as_math]")
{
  const real a = 5.0_r;
  const real b = 2.0_r;

  {
    const real max_result = max(a, b);
    CHECK(max_result == Approx(a).epsilon(g_epsilon));
  }

  {
    const real max_result = max(b, a);
    CHECK(max_result == Approx(a).epsilon(g_epsilon));
  }

  {
    const real aa = 5.0_r;
    const real max_result = max(aa, a);
    CHECK(max_result == Approx(aa).epsilon(g_epsilon));
  }
}

TEST_CASE("min", "[as_math]")
{
  const real a = 10.0_r;
  const real b = 5.0_r;

  {
    const real min_result = min(a, b);
    CHECK(min_result == Approx(b).epsilon(g_epsilon));
  }

  {
    const real min_result = min(b, a);
    CHECK(min_result == Approx(b).epsilon(g_epsilon));
  }

  {
    const real bb = 5.0_r;
    const real max_result = min(bb, b);
    CHECK(max_result == Approx(bb).epsilon(g_epsilon));
  }
}

TEST_CASE("smooth_step", "[as_math]")
{
  constexpr real real_epsilon = 1e-3_r;

  real quarter_value;
  quarter_value = smooth_step(0.25_r, 0.0_r, 1.0_r);
  CHECK(quarter_value == Approx(0.15625_r).epsilon(real_epsilon));

  real mid_value;
  mid_value = smooth_step(0.5_r, 0.0_r, 1.0_r);
  CHECK(mid_value == Approx(0.5_r).epsilon(real_epsilon));

  real three_quarter_value;
  three_quarter_value = smooth_step(0.75_r, 0.0_r, 1.0_r);
  CHECK(three_quarter_value == Approx(0.84375_r).epsilon(real_epsilon));
}

TEST_CASE("smoother_step", "[as_math]")
{
  constexpr real real_epsilon = 1e-3_r;

  real ten_percent_value;
  ten_percent_value = smoother_step(0.1_r, 0.0_r, 1.0_r);
  CHECK(ten_percent_value == Approx(0.00856_r).epsilon(real_epsilon));

  real quarter_value;
  quarter_value = smoother_step(0.25_r, 0.0_r, 1.0_r);
  CHECK(quarter_value == Approx(0.10351_r).epsilon(real_epsilon));

  real mid_value;
  mid_value = smoother_step(0.5_r, 0.0_r, 1.0_r);
  CHECK(mid_value == Approx(0.5_r).epsilon(real_epsilon));

  real three_quarter_value;
  three_quarter_value = smoother_step(0.75_r, 0.0_r, 1.0_r);
  CHECK(three_quarter_value == Approx(0.89648_r).epsilon(real_epsilon));

  real ninety_percent_value;
  ninety_percent_value = smoother_step(0.9_r, 0.0_r, 1.0_r);
  CHECK(ninety_percent_value == Approx(0.99144_r).epsilon(real_epsilon));
}

TEST_CASE("degrees_to_radians", "[as_math]")
{
  constexpr real real_epsilon = 1e-3_r;

  CHECK(radians(57.2958_r) == Approx(1.0_r).epsilon(real_epsilon));
  CHECK(radians(90.0_r) == Approx(1.5708_r).epsilon(real_epsilon));
  CHECK(radians(180.0_r) == Approx(3.14159_r).epsilon(real_epsilon));
  CHECK(radians(270.0_r) == Approx(4.71239_r).epsilon(real_epsilon));
  CHECK(radians(360.0_r) == Approx(6.28319_r).epsilon(real_epsilon));
}

TEST_CASE("radians_to_degrees", "[as_math]")
{
  constexpr real real_epsilon = 1e-3_r;

  CHECK(degrees(1.0_r) == Approx(57.2958_r).epsilon(real_epsilon));
  CHECK(degrees(1.5708_r) == Approx(90.0_r).epsilon(real_epsilon));
  CHECK(degrees(3.14159_r) == Approx(180.0_r).epsilon(real_epsilon));
  CHECK(degrees(4.71239_r) == Approx(270.0_r).epsilon(real_epsilon));
  CHECK(degrees(6.28319_r) == Approx(360.0_r).epsilon(real_epsilon));
}

TEST_CASE("snap", "[as_math]")
{
  {
    const real result = as::snap(4.0_r, 10.0_r);
    CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    const real result = as::snap(6.0_r, 10.0_r);
    CHECK(result == Approx(10.0_r).epsilon(g_epsilon));
  }

  {
    const real result = as::snap(1.0_r, 2.0_r);
    CHECK(result == Approx(2.0_r).epsilon(g_epsilon));
  }

  {
    const real result = as::snap(0.99_r, 2.0_r);
    CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    const real result = as::snap(22.0_r, 20.0_r);
    CHECK(result == Approx(20.0_r).epsilon(g_epsilon));
  }

  {
    const real result = as::snap(32.0_r, 20.0_r);
    CHECK(result == Approx(40.0_r).epsilon(g_epsilon));
  }
}

} // namespace unit_test

// explicit instantiations (for coverage)
template as::real as::smooth_step(as::real t, as::real v0, as::real v1);
template as::real as::smoother_step(as::real t, as::real v0, as::real v1);
