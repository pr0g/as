#include "as-helpers.test.hpp"

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers.hpp"

namespace unit_test
{

// testing
using Catch::Approx;

// types
using as::real;

// functions
using as::to_real;

TEST_CASE("float_to_real", "[as_real]")
{
  real r;
  r = to_real(3.14f);
  CHECK(r == Approx(static_cast<real>(3.14)).epsilon(g_epsilon));
}

TEST_CASE("double_to_real", "[as_real]")
{
  real r;
  r = to_real(6.28);
  CHECK(r == Approx(static_cast<real>(6.28)).epsilon(g_epsilon));
}

TEST_CASE("user_defined_literal_namespace", "[as_real]")
{
  using namespace as::literals;
  real r_1 = 1.0_r;
  real r_2 = 2.0_r;
  real expected = r_1 + r_2;
  CHECK(expected == Approx(static_cast<real>(3.0_r)).epsilon(g_epsilon));
}

} // namespace unit_test
