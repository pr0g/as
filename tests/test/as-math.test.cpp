#include "as/as-math.hpp"
#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch_test_macros.hpp"

namespace unit_test
{

// testing
using Catch::Approx;

// types
using as::real;

// functions
using as::degrees;
using as::inverse_mix;
using as::max;
using as::min;
using as::mix;
using as::radians;
using as::smooth_step;
using as::smoother_step;
using as::snap;
using as::operator""_r;

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
  quarter_value = mix(0.0_r, 1.0_r, smooth_step(0.25_r));
  CHECK(quarter_value == Approx(0.15625_r).epsilon(real_epsilon));

  real mid_value;
  mid_value = mix(0.0_r, 1.0_r, smooth_step(0.5_r));
  CHECK(mid_value == Approx(0.5_r).epsilon(real_epsilon));

  real three_quarter_value;
  three_quarter_value = mix(0.0_r, 1.0_r, smooth_step(0.75_r));
  CHECK(three_quarter_value == Approx(0.84375_r).epsilon(real_epsilon));
}

TEST_CASE("smoother_step", "[as_math]")
{
  constexpr real real_epsilon = 1e-3_r;

  real ten_percent_value;
  ten_percent_value = mix(0.0_r, 1.0_r, smoother_step(0.1_r));
  CHECK(ten_percent_value == Approx(0.00856_r).epsilon(real_epsilon));

  real quarter_value;
  quarter_value = mix(0.0_r, 1.0_r, smoother_step(0.25_r));
  CHECK(quarter_value == Approx(0.10351_r).epsilon(real_epsilon));

  real mid_value;
  mid_value = mix(0.0_r, 1.0_r, smoother_step(0.5_r));
  CHECK(mid_value == Approx(0.5_r).epsilon(real_epsilon));

  real three_quarter_value;
  three_quarter_value = mix(0.0_r, 1.0_r, smoother_step(0.75_r));
  CHECK(three_quarter_value == Approx(0.89648_r).epsilon(real_epsilon));

  real ninety_percent_value;
  ninety_percent_value = mix(0.0_r, 1.0_r, smoother_step(0.9_r));
  CHECK(ninety_percent_value == Approx(0.99144_r).epsilon(real_epsilon));
}

TEST_CASE("mix", "[as_math]")
{
  {
    int expected;
    expected = mix(0, 10, 0.5_r);
    CHECK(expected == 5);
  }

  {
    real expected;
    expected = mix(0.0_r, 100.0_r, 0.0_r);
    CHECK(expected == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = mix(0.0_r, 100.0_r, 1.0_r);
    CHECK(expected == Approx(100.0_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = mix(0.5_r, 1.0_r, 0.2_r);
    CHECK(expected == Approx(0.6_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = mix(0.0_r, 10.0_r, 1.2_r);
    CHECK(expected == Approx(12.0_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = mix(0.0_r, 10.0_r, -0.2_r);
    CHECK(expected == Approx(-2.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("inverse_mix", "[as_math]")
{
  {
    real expected;
    expected = inverse_mix(0, 10, 5);
    CHECK(expected == Approx(0.5_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = inverse_mix(0.0_r, 100.0_r, 0.0_r);
    CHECK(expected == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = inverse_mix(0.0_r, 100.0_r, 100.0_r);
    CHECK(expected == Approx(1.0_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = inverse_mix(5, 10, 9);
    CHECK(expected == Approx(0.8_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = inverse_mix(2.0_r, 6.0_r, 0.0_r);
    CHECK(expected == Approx(-0.5_r).epsilon(g_epsilon));
  }

  {
    real expected;
    expected = inverse_mix(10.0_r, 20.0_r, 25.0_r);
    CHECK(expected == Approx(1.5_r).epsilon(g_epsilon));
  }
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
    const real result = snap(4.0_r, 10.0_r);
    CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    const real result = snap(6.0_r, 10.0_r);
    CHECK(result == Approx(10.0_r).epsilon(g_epsilon));
  }

  {
    const real result = snap(1.0_r, 2.0_r);
    CHECK(result == Approx(2.0_r).epsilon(g_epsilon));
  }

  {
    const real result = snap(0.99_r, 2.0_r);
    CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    const real result = snap(22.0_r, 20.0_r);
    CHECK(result == Approx(20.0_r).epsilon(g_epsilon));
  }

  {
    const real result = snap(32.0_r, 20.0_r);
    CHECK(result == Approx(40.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("sign", "[as_math]")
{
  real minus_one;
  minus_one = as::sign(-5.0_r);
  CHECK(minus_one == Approx(-1.0_r).epsilon(g_epsilon));

  real zero;
  zero = as::sign(-0.0_r);
  CHECK(zero == Approx(0.0_r).epsilon(g_epsilon));

  real negative_zero;
  negative_zero = as::sign(-0.0_r);
  CHECK(negative_zero == Approx(0.0_r).epsilon(g_epsilon));

  real one;
  one = as::sign(10.0_r);
  CHECK(one == Approx(1.0_r).epsilon(g_epsilon));
}

TEST_CASE("fract", "[as_math]")
{
  constexpr real real_epsilon = 1e-5_r;

  {
    real result;
    result = as::fract(103.4_r);
    CHECK(result == Approx(0.4_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract(-2.1_r);
    CHECK(result == Approx(0.9_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract(-3.5_r);
    CHECK(result == Approx(0.5_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract(-4.7_r);
    CHECK(result == Approx(0.3_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract(0.0_r);
    CHECK(result == Approx(0.0_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract(0.342_r);
    CHECK(result == Approx(0.342_r).epsilon(real_epsilon));
  }
}

TEST_CASE("fract_abs", "[as_math]")
{
  constexpr real real_epsilon = 1e-5_r;

  {
    real result;
    result = as::fract_abs(-50.4_r);
    CHECK(result == Approx(0.4_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract_abs(-2.1_r);
    CHECK(result == Approx(0.1_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract_abs(9.2_r);
    CHECK(result == Approx(0.2_r).epsilon(real_epsilon));
  }
}

TEST_CASE("fract_abs_signed", "[as_math]")
{
  constexpr real real_epsilon = 1e-5_r;

  {
    real result;
    result = as::fract_abs_signed(-50.4_r);
    CHECK(result == Approx(-0.4_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract_abs_signed(-2.1_r);
    CHECK(result == Approx(-0.1_r).epsilon(real_epsilon));
  }

  {
    real result;
    result = as::fract_abs_signed(9.2_r);
    CHECK(result == Approx(0.2_r).epsilon(real_epsilon));
  }
}

} // namespace unit_test

// explicit instantiations (for coverage)
template as::real as::smooth_step(as::real t);
template as::real as::smoother_step(as::real t);
template as::real as::fract(as::real t);
