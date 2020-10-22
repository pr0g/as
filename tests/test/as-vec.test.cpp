#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

#include <memory>

namespace unit_test
{

// types
using as::index;
using as::mat3;
using as::real;
using as::vec;
using as::vec2;
using as::vec3;
using as::vec4;

// functions
using as::radians;
using as::operator""_r;

// use float epsilon for comparisons
const real g_epsilon = real(std::numeric_limits<float>::epsilon());

TEST_CASE("vec2_initialization", "[as_vec]")
{
  // default initialization
  {
    vec2 v2;
    (void)v2;
  }

  // zero initialization
  {
    vec2 v2{};
    CHECK_THAT(arr(0.0_r, 0.0_r), elements_are_array(v2));
  }

  // value initialization
  {
    vec2 v2 = vec2();
    CHECK_THAT(arr(0.0_r, 0.0_r), elements_are_array(v2));
  }

  // direct initialization (braces)
  {
    vec2 v2{1.0_r, 2.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r), elements_are_array(v2));
  }

  // direct initialization - single argument (braces)
  {
    vec2 v2{5.0_r};
    CHECK_THAT(arr(5.0_r, 5.0_r), elements_are_array(v2));
  }

  // direct initialization (parens)
  {
    vec2 v2(5.0_r, 10.0_r);
    CHECK_THAT(arr(5.0_r, 10.0_r), elements_are_array(v2));
  }

  // direct initialization - single argument (parens)
  {
    vec2 v2;
    v2 = vec2(6.0_r);
    CHECK_THAT(arr(6.0_r, 6.0_r), elements_are_array(v2));
  }

  // direct/copy initialization (braces)
  {
    vec2 v2 = vec2{3.0_r, 4.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r), elements_are_array(v2));
  }

  // direct/copy initialization (parens)
  {
    vec2 v2 = vec2(3.0_r, 4.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r), elements_are_array(v2));
  }

  // direct/copy initialization - single argument (braces)
  {
    const real value{123.0_r};
    vec2 v2 = vec2{value};
    CHECK_THAT(arr(123.0_r, 123.0_r), elements_are_array(v2));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v2 = vec2(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r), elements_are_array(v2));
  }

  // assignment initialization - single argument (braces)
  {
    vec2 v2;
    v2 = vec2{75.0_r};
    CHECK_THAT(arr(75.0_r, 75.0_r), elements_are_array(v2));
  }

  // direct + copy initialization
  {
    vec2 vec2_a(300.0_r, 400.0_r);
    vec2 vec2_b(vec2_a);

    CHECK_THAT(arr(300.0_r, 400.0_r), elements_are_array(vec2_b));
  }

  // direct + copy initialization (assignment)
  {
    vec2 vec2_a(100.0_r, 200.0_r);
    vec2 vec2_b = vec2_a;

    CHECK_THAT(arr(100.0_r, 200.0_r), elements_are_array(vec2_b));
  }

  // direct + copy initialization (assignment)
  {
    vec2 vec2_a(500.0_r, 600.0_r);
    vec2 vec2_b;

    vec2_b = vec2_a;

    CHECK_THAT(arr(500.0_r, 600.0_r), elements_are_array(vec2_b));
  }
}

TEST_CASE("vec3_initialization", "[as_vec]")
{
  using gsl::make_span;

  // default initialization
  {
    vec3 v3;
    (void)v3;
  }

  // zero initialization
  {
    vec3 v3{};
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), elements_are_array(v3));
  }

  // value initialization
  {
    vec3 v3 = vec3();
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), elements_are_array(v3));
  }

  // direct initialization (braces)
  {
    vec3 v3{1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(v3));
  }

  // direct initialization (parens)
  {
    vec3 v3(5.0_r, 10.0_r, 15.0_r);
    CHECK_THAT(arr(5.0_r, 10.0_r, 15.0_r), elements_are_array(v3));
  }

  // direct/copy initialization (braces)
  {
    vec3 v3 = vec3{1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(v3));
  }

  // direct/copy initialization (parens)
  {
    vec3 v3 = vec3(3.0_r, 4.0_r, 5.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r), elements_are_array(v3));
  }

  // direct/copy initialization - single argument (braces)
  {
    vec3 v3 = vec3{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r), elements_are_array(v3));
  }

  // assignment initialization - single argument (braces)
  {
    vec3 v3;
    v3 = vec3{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r), elements_are_array(v3));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v3 = vec3(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r, 25.0_r), elements_are_array(v3));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec3 v3 = vec3{vec2{1.0_r, 2.0_r}, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(v3));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec2 v2 = vec2(1.0_r, 2.0_r);
    vec3 v3 = vec3(v2, 3.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(v3));
  }

  // direct + copy initialization
  {
    vec3 vec3_a(100.0_r, 200.0_r, 300.0_r);
    vec3 vec3_b(vec3_a);

    CHECK_THAT(arr(100.0_r, 200.0_r, 300.0_r), elements_are_array(vec3_b));
  }

  // direct + copy initialization
  {
    vec3 vec3_a(400.0_r, 500.0_r, 600.0_r);
    vec3 vec3_b = vec3_a;

    CHECK_THAT(arr(400.0_r, 500.0_r, 600.0_r), elements_are_array(vec3_b));
  }

  // direct + copy initialization (assignment)
  {
    vec3 vec3_a(500.0_r, 600.0_r, 700.0_r);
    vec3 vec3_b;

    vec3_b = vec3_a;

    CHECK_THAT(arr(500.0_r, 600.0_r, 700.0_r), elements_are_array(vec3_b));
  }
}

TEST_CASE("vec4_initialization", "[as_vec]")
{
  // default initialization
  {
    vec4 v4;
    (void)v4;
  }

  // zero initialization
  {
    vec4 v4{};
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r, 0.0_r), elements_are_array(v4));
  }

  // value initialization
  {
    vec4 v4 = vec4();
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r, 0.0_r), elements_are_array(v4));
  }

  // direct initialization (braces)
  {
    vec4 v4{1.0_r, 2.0_r, 3.0_r, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct initialization (parens)
  {
    vec4 v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization (braces)
  {
    vec4 v4 = vec4{3.0_r, 4.0_r, 5.0_r, 6.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r, 6.0_r), elements_are_array(v4));
  }

  // direct/copy initialization (parens)
  {
    vec4 v4 = vec4(3.0_r, 4.0_r, 5.0_r, 6.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r, 6.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - single argument (braces)
  {
    vec4 v4 = vec4{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r, 50.0_r), elements_are_array(v4));
  }

  // assignment initialization - single argument (braces)
  {
    vec4 v4;
    v4 = vec4{99.0_r};
    CHECK_THAT(arr(99.0_r, 99.0_r, 99.0_r, 99.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v4 = vec4(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r, 25.0_r, 25.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec4 v4 = vec4{vec3{1.0_r, 2.0_r, 3.0_r}, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec4 v4 = vec4(vec3(1.0_r, 2.0_r, 3.0_r), 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec4 v4 = vec4{vec2{1.0_r, 2.0_r}, vec2{3.0_r, 4.0_r}};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec4 v4 = vec4(vec2(1.0_r, 2.0_r), vec2(3.0_r, 4.0_r));
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - triple argument (braces)
  {
    vec4 v4 = vec4{vec2{1.0_r, 2.0_r}, 3.0_r, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct/copy initialization - triple argument (parens)
  {
    vec4 v4 = vec4(vec2(1.0_r, 2.0_r), 3.0_r, 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), elements_are_array(v4));
  }

  // direct + copy initialization
  {
    vec4 vec4_a(100.0_r, 200.0_r, 300.0_r, 400.0_r);
    vec4 vec4_b(vec4_a);

    CHECK_THAT(
      arr(100.0_r, 200.0_r, 300.0_r, 400.0_r), elements_are_array(vec4_b));
  }

  // direct + copy initialization
  {
    vec4 vec4_a(500.0_r, 600.0_r, 700.0_r, 800.0_r);
    vec4 vec4_b = vec4_a;

    CHECK_THAT(
      arr(500.0_r, 600.0_r, 700.0_r, 800.0_r), elements_are_array(vec4_b));
  }

  // direct + copy initialization (assignment)
  {
    vec4 vec4_a(500.0_r, 600.0_r, 700.0_r, 800.0_r);
    vec4 vec4_b;

    vec4_b = vec4_a;

    CHECK_THAT(
      arr(500.0_r, 600.0_r, 700.0_r, 800.0_r), elements_are_array(vec4_b));
  }
}

TEST_CASE("vec2_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec2 v2{};
    CHECK(v2.x == Approx(v2[0]).epsilon(g_epsilon));
    CHECK(v2.y == Approx(v2[1]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec2 v2(1.0_r, 2.0_r);
    CHECK(v2.x == Approx(v2[0]).epsilon(g_epsilon));
    CHECK(v2.y == Approx(v2[1]).epsilon(g_epsilon));
  }

  // member and const subscript operator - explicit construction
  {
    vec2 v2(1.0_r, 2.0_r);
    const real& x = v2[0];
    const real& y = v2[1];

    CHECK(v2.x == Approx(x).epsilon(g_epsilon));
    CHECK(v2.y == Approx(y).epsilon(g_epsilon));
  }
}

TEST_CASE("vec3_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec3 v3{};
    CHECK(v3.x == Approx(v3[0]).epsilon(g_epsilon));
    CHECK(v3.y == Approx(v3[1]).epsilon(g_epsilon));
    CHECK(v3.z == Approx(v3[2]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec3 v3(1.0_r, 2.0_r, 3.0_r);
    CHECK(v3.x == Approx(v3[0]).epsilon(g_epsilon));
    CHECK(v3.y == Approx(v3[1]).epsilon(g_epsilon));
    CHECK(v3.z == Approx(v3[2]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec3 v3(1.0_r, 2.0_r, 3.0_r);
    CHECK(vec2_from_vec3(v3)[0] == Approx(v3.x).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3)[1] == Approx(v3.y).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3).x == Approx(v3.x).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3).y == Approx(v3.y).epsilon(g_epsilon));
  }

  // member and const subscript operator - explicit construction
  {
    vec3 v3(1.0_r, 2.0_r, 3.0_r);
    const real& x = v3[0];
    const real& y = v3[1];
    const real& z = v3[2];

    CHECK(v3.x == Approx(x).epsilon(g_epsilon));
    CHECK(v3.y == Approx(y).epsilon(g_epsilon));
    CHECK(v3.z == Approx(z).epsilon(g_epsilon));
  }
}

TEST_CASE("vec4_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec4 v4{};
    CHECK(v4.x == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(v4.y == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(v4.z == Approx(v4[2]).epsilon(g_epsilon));
    CHECK(v4.w == Approx(v4[3]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec4 v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK(v4.x == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(v4.y == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(v4.z == Approx(v4[2]).epsilon(g_epsilon));
    CHECK(v4.w == Approx(v4[3]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec4 v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK(vec2_from_vec4(v4)[0] == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(vec2_from_vec4(v4)[1] == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[0] == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[1] == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[2] == Approx(v4[2]).epsilon(g_epsilon));
  }
}

TEST_CASE("vec2_vec3_vec4_accessors", "[as_vec]")
{
  vec2 v2(1.0_r, 2.0_r);
  vec3 v3(v2, 3.0_r);

  vec4 vec4_a(v2, 3.0_r, 4.0_r);
  vec4 vec4_b(v2, v2);
  vec4 vec4_c(v3, 4.0_r);

  // member accessors
  CHECK(vec4_a.x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_a.y == Approx(v2.y).epsilon(g_epsilon));

  CHECK(vec4_b.x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_b.y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(vec4_b.z == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_b.w == Approx(v2.y).epsilon(g_epsilon));

  CHECK(vec4_c.x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_c.y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(vec4_c.z == Approx(vec4_a.z).epsilon(g_epsilon));
  CHECK(vec4_c.w == Approx(vec4_a.w).epsilon(g_epsilon));

  CHECK(vec3_from_vec2(v2).x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec3_from_vec2(v2).y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(
    vec3_from_vec2(v2, real(3.0)).z == Approx(real(3.0)).epsilon(g_epsilon));

  CHECK(vec4_from_vec2(v2).x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_from_vec2(v2).y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec2(v2, real(3.0)).z == Approx(real(3.0)).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec2(v2, real(3.0), real(4.0)).w
    == Approx(real(4.0)).epsilon(g_epsilon));

  CHECK(vec4_from_vec3(v3).x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_from_vec3(v3).y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(vec4_from_vec3(v3).z == Approx(real(3.0)).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec3(v3, real(4.0)).w == Approx(real(4.0)).epsilon(g_epsilon));
}

TEST_CASE("const_elem_access_vec_const", "[as_vec]")
{
  using gsl::make_span;

  const vec<real, 5> vec5(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);

  const real elem_0 = vec5[0];
  const real elem_1 = vec5[1];
  const real elem_2 = vec5[2];
  const real elem_3 = vec5[3];
  const real elem_4 = vec5[4];

  const real vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
  CHECK_THAT(make_span(vec_arr), elements_are_span(vec5));
}

TEST_CASE("elem_access_vec", "[as_vec]")
{
  using gsl::make_span;
  vec<real, 5> vec5(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);

  real elem_0 = vec5[0];
  real elem_1 = vec5[1];
  real elem_2 = vec5[2];
  real elem_3 = vec5[3];
  real elem_4 = vec5[4];

  const real vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
  CHECK_THAT(make_span(vec_arr), elements_are_span(vec5));
}

TEST_CASE("const_elem_access_vec2_3_4", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec2 v2(15.0_r, 30.0_r);

    const real elem_0 = v2[0];
    const real elem_1 = v2[1];

    const real vec_arr[] = {elem_0, elem_1};
    CHECK_THAT(make_span(vec_arr), elements_are_span(v2));
  }

  {
    const vec3 v3(2.0_r, 3.0_r, 4.0_r);

    const real elem_0 = v3[0];
    const real elem_1 = v3[1];
    const real elem_2 = v3[2];

    const real vec_arr[] = {elem_0, elem_1, elem_2};
    CHECK_THAT(make_span(vec_arr), elements_are_span(v3));
  }

  {
    vec4 v4;
    v4 = vec4(10.0_r, 20.0_r, 30.0_r, 40.0_r);

    const real elem_0 = v4[0];
    const real elem_1 = v4[1];
    const real elem_2 = v4[2];
    const real elem_3 = v4[3];

    const real vec_arr[] = {elem_0, elem_1, elem_2, elem_3};
    CHECK_THAT(make_span(vec_arr), elements_are_span(v4));
  }
}

TEST_CASE("rvalue_elem_access_vec2_3_4_5", "[as_vec]")
{
  using gsl::make_span;

  auto make_vec2 = []() { return vec2{5.0_r, 10.0_r}; };
  CHECK(make_vec2()[0] == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(make_vec2()[1] == Approx(10.0_r).epsilon(g_epsilon));

  auto make_vec3 = []() { return vec3{5.0_r, 10.0_r, 15.0_r}; };
  CHECK(make_vec3()[0] == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(make_vec3()[1] == Approx(10.0_r).epsilon(g_epsilon));
  CHECK(make_vec3()[2] == Approx(15.0_r).epsilon(g_epsilon));

  auto make_vec4 = []() { return vec4{7.0_r, 14.0_r, 21.0_r, 28.0_r}; };
  CHECK(make_vec4()[0] == Approx(7.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[1] == Approx(14.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[2] == Approx(21.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[3] == Approx(28.0_r).epsilon(g_epsilon));

  auto make_vec5 = []() {
    return vec<real, 5>{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r};
  };
  CHECK(make_vec5()[0] == Approx(1.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[1] == Approx(2.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[2] == Approx(3.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[3] == Approx(4.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[4] == Approx(5.0_r).epsilon(g_epsilon));
}

TEST_CASE("vec_size", "[as_vec]")
{
  static_assert(vec2::size() == 2, "vec2 size must be 2");
  index vec2_size;
  vec2_size = vec2::size();
  vec2 v2;
  CHECK(vec2_size == 2);

  static_assert(vec3::size() == 3, "vec3 size must be 3");
  index vec3_size;
  vec3_size = vec3::size();
  vec3 v3;
  CHECK(vec3_size == static_cast<index>(3));

  static_assert(vec4::size() == 4, "vec4 size must be 4");
  index vec4_size;
  vec4_size = vec4::size();
  vec4 v4;
  CHECK(vec4_size == static_cast<index>(4));

  using short7 = vec<short, 7>;
  short7 vec_short7;
  index short7_size;
  short7_size = short7::size();
  CHECK(short7_size == static_cast<index>(7));

  using int5 = vec<int, 5>;
  int5 vec_short5;
  index int5_size = int5::size();
  CHECK(int5_size == static_cast<index>(5));
}

TEST_CASE("vec_make_from_arr", "[as_vec]")
{
  // generic make_from_arr vec2
  {
    real vec_data[2] = {2.0_r, 4.0_r};
    vec2 v2 = as::vec_from_arr(vec_data);

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));

    // won't compile (array length 2 to vec3)
    // vec3 v3 = make_from(vec_data);
  }

  // generic make_from_arr vec3
  {
    real vec_data[3] = {1.0_r, 2.0_r, 3.0_r};
    vec3 v3 = as::vec_from_arr(vec_data);

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // generic make_from_arr <char, 6>
  {
    char vec_data[6] = {11, 12, 13, 14, 15, 16};
    vec<char, 6> char_6 = as::vec_from_arr(vec_data);

    CHECK(char_6[0] == 11);
    CHECK(char_6[1] == 12);
    CHECK(char_6[2] == 13);
    CHECK(char_6[3] == 14);
    CHECK(char_6[4] == 15);
    CHECK(char_6[5] == 16);
  }

  // vec2_make_from_arr
  {
    real vec_data[2] = {2.0_r, 4.0_r};
    vec2 v2 = as::vec2_from_arr(vec_data);

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // vec3_make_from_arr
  {
    real vec_data[3] = {1.0_r, 2.0_r, 3.0_r};
    vec3 v3 = as::vec3_from_arr(vec_data);

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // vec4_make_from_arr
  {
    real vec_data[4] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    vec4 v4 = as::vec4_from_arr(vec_data);

    CHECK(v4.x == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(v4.y == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(v4.z == Approx(12.0_r).epsilon(g_epsilon));
    CHECK(v4.w == Approx(16.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("vec_make_from_ptr", "[as_vec]")
{
  // generic make_from_ptr vec2
  {
    std::unique_ptr<real[]> vec_data = std::make_unique<real[]>(2);
    vec_data[0] = 2.0_r;
    vec_data[1] = 4.0_r;
    vec2 v2 = as::vec_from_ptr<real, 2>(vec_data.get());

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // generic make_from_ptr vec3
  {
    std::unique_ptr<real[]> vec_data = std::make_unique<real[]>(3);
    vec_data[0] = 1.0_r;
    vec_data[1] = 2.0_r;
    vec_data[2] = 3.0_r;
    vec3 v3 = as::vec_from_ptr<real, 3>(vec_data.get());

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // generic make_from_ptr <char, 6>
  {
    std::unique_ptr<char[]> vec_data = std::make_unique<char[]>(6);
    vec_data[0] = 11;
    vec_data[1] = 12;
    vec_data[2] = 13;
    vec_data[3] = 14;
    vec_data[4] = 15;
    vec_data[5] = 16;
    vec<char, 6> char_6 = as::vec_from_ptr<char, 6>(vec_data.get());

    CHECK(char_6[0] == 11);
    CHECK(char_6[1] == 12);
    CHECK(char_6[2] == 13);
    CHECK(char_6[3] == 14);
    CHECK(char_6[4] == 15);
    CHECK(char_6[5] == 16);
  }

  {
    int64_t vec_data[4] = {4, 8, 12, 16};
    vec<int64_t, 4> int64_t_5 = as::vec4_from_ptr(&vec_data[0]);

    CHECK(int64_t_5[0] == 4);
    CHECK(int64_t_5[1] == 8);
    CHECK(int64_t_5[2] == 12);
    CHECK(int64_t_5[3] == 16);
  }

  // vec2_make_from_ptr
  {
    std::unique_ptr<real[]> vec_data = std::make_unique<real[]>(2);
    vec_data[0] = 2.0_r;
    vec_data[1] = 4.0_r;
    vec2 v2 = as::vec2_from_ptr(vec_data.get());

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // vec3_make_from_ptr
  {
    std::unique_ptr<real[]> vec_data = std::make_unique<real[]>(3);
    vec_data[0] = 1.0_r;
    vec_data[1] = 2.0_r;
    vec_data[2] = 3.0_r;
    vec3 v3 = as::vec3_from_ptr(vec_data.get());

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // vec4_make_from_ptr
  {
    std::unique_ptr<real[]> vec_data = std::make_unique<real[]>(4);
    vec_data[0] = 4.0_r;
    vec_data[1] = 8.0_r;
    vec_data[2] = 12.0_r;
    vec_data[3] = 16.0_r;
    vec4 v4 = as::vec4_from_ptr(vec_data.get());

    CHECK(v4.x == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(v4.y == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(v4.z == Approx(12.0_r).epsilon(g_epsilon));
    CHECK(v4.w == Approx(16.0_r).epsilon(g_epsilon));
  }

  // generic type check
  {
    std::unique_ptr<double[]> vec_data = std::make_unique<double[]>(2);
    vec_data[0] = 2.0;
    vec_data[1] = 4.0;
    // does not compile - types do not match
    // vec<char, 2> char_2 = from_ptr<char, 2>(vec_data.get());
    // vec2 v2 = from_ptr<float, 2>(vec_data.get());
    vec<double, 2> v2 = as::vec_from_ptr<double, 2>(vec_data.get());
    (void)v2;
  }
}

TEST_CASE("addition", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '+'
  {
    vec5 v;
    v = vec5{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r}
      + vec5{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r};

    CHECK(vec_equal(v, vec5(50.0_r, 50.0_r, 50.0_r, 50.0_r, 50.0_r)));
  }

  // vec operator '+='
  {
    vec5 vec1(10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r);
    vec1 += vec5(25.0_r, 15.0_r, 5.0_r, 10.0_r, 1.0_r);
    CHECK(vec_equal(vec1, vec5(35.0_r, 35.0_r, 35.0_r, 50.0_r, 51.0_r)));
  }
}

TEST_CASE("addition_vec3", "[as_vec]")
{
  // vec3 operator '+'
  {
    vec3 v;
    v = vec3{10.0_r, 20.0_r, 30.0_r} + vec3{20.0_r, 10.0_r, 0.0_r};
    CHECK(vec_equal(v, vec3(30.0_r, 30.0_r, 30.0_r)));
  }

  // vec3 operator '+='
  {
    vec3 v(10.0_r, 20.0_r, 30.0_r);
    v += vec3(25.0_r, 15.0_r, 5.0_r);
    CHECK(vec_equal(v, vec3(35.0_r, 35.0_r, 35.0_r)));
  }
}

TEST_CASE("substraction", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '-'
  {
    vec5 v;
    v = vec5{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r}
      - vec5{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r};

    CHECK(vec_equal(v, vec5(30.0_r, 10.0_r, -10.0_r, -30.0_r, -50.0_r)));
  }

  // vec operator '-='
  {
    vec5 v(10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r);
    v -= vec5(25.0_r, 15.0_r, 5.0_r, 10.0_r, 1.0_r);
    CHECK(vec_equal(v, vec5(-15.0_r, 5.0_r, 25.0_r, 30.0_r, 49.0_r)));
  }
}

TEST_CASE("substraction_vec3", "[as_vec]")
{
  // vec3 operator '-'
  {
    vec3 v;
    v = vec3{40.0_r, 30.0_r, 20.0_r} - vec3{10.0_r, 20.0_r, 30.0_r};
    CHECK(vec_equal(v, vec3(30.0_r, 10.0_r, -10.0_r)));
  }

  // vec3 operator '-='
  {
    vec3 v(10.0_r, 20.0_r, 30.0_r);
    v -= vec3(25.0_r, 15.0_r, 5.0_r);
    CHECK(vec_equal(v, vec3(-15.0_r, 5.0_r, 25.0_r)));
  }
}

TEST_CASE("negation", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  vec5 v = vec5{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r};
  vec5 neg_vec = -v;
  CHECK(vec_equal(neg_vec, vec5(-40.0_r, -30.0_r, -20.0_r, -10.0_r, -0.0_r)));
}

TEST_CASE("negation_vec3", "[as_vec]")
{
  vec3 v = vec3{20.0_r, 10.0_r, 0.0_r};
  vec3 neg_vec = -v;
  CHECK(vec_equal(neg_vec, vec3(-20.0_r, -10.0_r, -0.0_r)));
}

TEST_CASE("multiplication_scalar", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '*'
  {
    vec5 v;
    v = real(5.0) * vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    CHECK(vec_equal(v, vec5(250.0_r, 200.0_r, 125.0_r, 100.0_r, 50.0_r)));
  }

  // vec operator '*='
  {
    vec5 v = vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    v *= real(5.0);
    CHECK(vec_equal(v, vec5(250.0_r, 200.0_r, 125.0_r, 100.0_r, 50.0_r)));
  }
}

TEST_CASE("multiplication_scalar_vec3", "[as_vec]")
{
  // vec3 operator '*'
  {
    vec3 v;
    v = real(5.0) * vec3{50.0_r, 40.0_r, 25.0_r};
    CHECK(vec_equal(v, vec3(250.0_r, 200.0_r, 125.0)));
  }

  // vec3 operator '*='
  {
    vec3 v = vec3{50.0_r, 40.0_r, 25.0_r};
    v *= real(5.0);
    CHECK(vec_equal(v, vec3(250.0_r, 200.0_r, 125.0)));
  }
}

TEST_CASE("multiplication_vector", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '*'
  {
    vec5 v;
    v = vec5{2.0_r, 3.0_r, 4.0_r, 5.0_r, 0.5_r}
      * vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};

    CHECK(vec_equal(v, vec5(100.0_r, 120.0_r, 100.0_r, 100.0_r, 5.0_r)));
  }

  // vec operator '*='
  {
    vec5 vec1 = vec5{2.0_r, 3.0_r, 4.0_r, 5.0_r, 0.5_r};
    vec5 v2 = vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    vec1 *= v2;
    CHECK(vec_equal(vec1, vec5(100.0_r, 120.0_r, 100.0_r, 100.0_r, 5.0_r)));
  }
}

TEST_CASE("multiplication_vector_vec3", "[as_vec]")
{
  // vec operator '*'
  {
    vec3 v;
    v = vec3{0.5_r, 3.0_r, 4.0_r} * vec3{50.0_r, 40.0_r, 25.0_r};
    CHECK(vec_equal(v, vec3(25.0_r, 120.0_r, 100.0_r)));
  }

  // vec operator '*='
  {
    vec3 vec1 = vec3{0.5_r, 3.0_r, 4.0_r};
    vec3 v2 = vec3{50.0_r, 40.0_r, 25.0_r};
    vec1 *= v2;
    CHECK(vec_equal(vec1, vec3(25.0_r, 120.0_r, 100.0_r)));
  }
}

TEST_CASE("divide_scalar", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '/'
  {
    vec5 v;
    v = vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r} / real(5.0);
    CHECK(vec_equal(v, vec5(10.0_r, 8.0_r, 5.0_r, 4.0_r, 2.0_r)));
  }

  // vec operator '/='
  {
    vec5 v = vec5{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    v /= real(5.0_r);
    CHECK(vec_equal(v, vec5(10.0_r, 8.0_r, 5.0_r, 4.0_r, 2.0_r)));
  }
}

TEST_CASE("divide_scalar_vec3", "[as_vec]")
{
  // vec operator '/'
  {
    vec3 v;
    v = vec3{50.0_r, 40.0_r, 25.0_r} / real(5.0);
    CHECK(vec_equal(v, vec3(10.0_r, 8.0_r, 5.0_r)));
  }

  // vec operator '/='
  {
    vec3 v = vec3{50.0_r, 40.0_r, 25.0_r};
    v /= real(5.0);
    CHECK(vec_equal(v, vec3(10.0_r, 8.0_r, 5.0_r)));
  }
}

TEST_CASE("divide_vector", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // vec operator '/'
  {
    vec5 v;
    v = vec5{33.0_r, 48.0_r, 10.0_r, 120.0_r, 2.0_r}
      / vec5{3.0_r, 6.0_r, 2.0_r, 3.0_r, 0.5_r};

    CHECK(vec_equal(v, vec5(11.0_r, 8.0_r, 5.0_r, 40.0_r, 4.0_r)));
  }

  // vec operator '/='
  {
    vec5 vec1 = vec5{33.0_r, 48.0_r, 10.0_r, 120.0_r, 2.0_r};
    vec5 v2 = vec5{3.0_r, 6.0_r, 2.0_r, 3.0_r, 0.5_r};
    vec1 /= v2;
    CHECK(vec_equal(vec1, vec5(11.0_r, 8.0_r, 5.0_r, 40.0_r, 4.0_r)));
  }
}

TEST_CASE("divide_vector_vec3", "[as_vec]")
{
  // vec operator '/'
  {
    vec3 v;
    v = vec3{33.0_r, 48.0_r, 10.0_r} / vec3{3.0_r, 6.0_r, 2.0_r};
    CHECK(vec_equal(v, vec3(11.0_r, 8.0_r, 5.0_r)));
  }

  // vec operator '/='
  {
    vec3 vec1 = vec3{33.0_r, 48.0_r, 10.0_r};
    vec3 v2 = vec3{3.0_r, 6.0_r, 2.0_r};
    vec1 /= v2;
    CHECK(vec_equal(vec1, vec3(11.0_r, 8.0_r, 5.0_r)));
  }
}

TEST_CASE("dot", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  // note: comparison values calculated using - http://calculator.vhex.net
  {
    const vec5 vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);
    const vec5 v2(4.0_r, 5.0_r, 6.0_r, 8.0_r, 4.0_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(84.0_r).epsilon(g_epsilon));
  }

  {
    const vec5 vec1(-50.0_r, 20.0_r, 9.0_r, 11.0_r, 3.0_r);
    const vec5 v2(-1.0_r, -7.0_r, 4.0_r, 2.0_r, 0.5_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(-30.5).epsilon(g_epsilon));
  }

  {
    const vec5 vec1(-2.3_r, 0.1_r, 0.92_r, 0.123_r, 0.543_r);
    const vec5 v2(-1.456_r, -7.732_r, 2.491_r, -1.321_r, -0.261_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(4.563114_r).epsilon(g_epsilon));
  }
}

TEST_CASE("dot_vec3", "[as_vec]")
{
  // note: comparison values calculated using - http://calculator.vhex.net
  {
    const vec3 vec1(1.0_r, 2.0_r, 3.0_r);
    const vec3 v2(4.0_r, 5.0_r, 6.0_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(32.0_r).epsilon(g_epsilon));
  }

  {
    const vec3 vec1(-50.0_r, 20.0_r, 9.0_r);
    const vec3 v2(-1.0_r, -7.0_r, 4.0_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(-54.0_r).epsilon(g_epsilon));
  }

  {
    const vec3 vec1(-2.3_r, 0.1_r, 0.92_r);
    const vec3 v2(-1.456_r, -7.732_r, 2.491_r);

    const real dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(4.86732_r).epsilon(g_epsilon));
  }
}

TEST_CASE("axes_vec2", "[as_vec]")
{
  using gsl::make_span;

  constexpr real x_axis[] = {1.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), elements_are_span(vec2::axis_x()));

  constexpr real y_axis[] = {0.0_r, 1.0_r};
  CHECK_THAT(make_span(y_axis), elements_are_span(vec2::axis_y()));

  constexpr real zero[] = {0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), elements_are_span(vec2::zero()));

  constexpr real one[] = {1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), elements_are_span(vec2::one()));

  constexpr real max_val = std::numeric_limits<real>::max();
  constexpr real max_val_vec[] = {max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), elements_are_span(vec2::max()));

  constexpr real min_val = std::numeric_limits<real>::min();
  constexpr real min_val_vec[] = {min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), elements_are_span(vec2::min()));

  constexpr real lowest_val = std::numeric_limits<real>::lowest();
  constexpr real lowest_val_vec[] = {lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), elements_are_span(vec2::lowest()));
}

TEST_CASE("axes_vec3", "[as_vec]")
{
  using gsl::make_span;

  constexpr real x_axis[] = {1.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), elements_are_span(vec3::axis_x()));

  constexpr real y_axis[] = {0.0_r, 1.0_r, 0.0_r};
  CHECK_THAT(make_span(y_axis), elements_are_span(vec3::axis_y()));

  constexpr real z_axis[] = {0.0_r, 0.0_r, 1.0_r};
  CHECK_THAT(make_span(z_axis), elements_are_span(vec3::axis_z()));

  constexpr real zero[] = {0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), elements_are_span(vec3::zero()));

  constexpr real one[] = {1.0_r, 1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), elements_are_span(vec3::one()));

  constexpr real max_val = std::numeric_limits<real>::max();
  constexpr real max_val_vec[] = {max_val, max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), elements_are_span(vec3::max()));

  constexpr real min_val = std::numeric_limits<real>::min();
  constexpr real min_val_vec[] = {min_val, min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), elements_are_span(vec3::min()));

  constexpr real lowest_val = std::numeric_limits<real>::lowest();
  constexpr real lowest_val_vec[] = {lowest_val, lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), elements_are_span(vec3::lowest()));
}

TEST_CASE("axes_vec4", "[as_vec]")
{
  using gsl::make_span;

  constexpr real x_axis[] = {1.0_r, 0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), elements_are_span(vec4::axis_x()));

  constexpr real y_axis[] = {0.0_r, 1.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(y_axis), elements_are_span(vec4::axis_y()));

  constexpr real z_axis[] = {0.0_r, 0.0_r, 1.0_r, 0.0_r};
  CHECK_THAT(make_span(z_axis), elements_are_span(vec4::axis_z()));

  constexpr real w_axis[] = {0.0_r, 0.0_r, 0.0_r, 1.0_r};
  CHECK_THAT(make_span(w_axis), elements_are_span(vec4::axis_w()));

  constexpr real zero[] = {0.0_r, 0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), elements_are_span(vec4::zero()));

  constexpr real one[] = {1.0_r, 1.0_r, 1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), elements_are_span(vec4::one()));

  constexpr real max_val = std::numeric_limits<real>::max();
  constexpr real max_val_vec[] = {max_val, max_val, max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), elements_are_span(vec4::max()));

  constexpr real min_val = std::numeric_limits<real>::min();
  constexpr real min_val_vec[] = {min_val, min_val, min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), elements_are_span(vec4::min()));

  constexpr real lowest_val = std::numeric_limits<real>::lowest();
  constexpr real lowest_val_vec[] = {
    lowest_val, lowest_val, lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), elements_are_span(vec4::lowest()));
}

TEST_CASE("cross", "[as_vec]")
{
  // note: comparison values calculated using
  // https://www.symbolab.com/solver/vector-cross-product-calculator
  {
    vec3 vec1(1.0_r, 2.0_r, 3.0_r);
    vec3 v2(4.0_r, 5.0_r, 6.0_r);

    vec3 cross_result = vec3_cross(vec1, v2);
    CHECK(cross_result.x == Approx(-3.0_r).epsilon(g_epsilon));
    CHECK(cross_result.y == Approx(6.0_r).epsilon(g_epsilon));
    CHECK(cross_result.z == Approx(-3.0_r).epsilon(g_epsilon));
  }

  {
    vec3 vec1(1.0_r, 0.0_r, 0.0_r);
    vec3 v2(0.0_r, 1.0_r, 0.0_r);

    vec3 cross_result1 = vec3_cross(vec1, v2);
    CHECK(cross_result1.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result1.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result1.z == Approx(1.0_r).epsilon(g_epsilon));

    vec3 cross_result2 = vec3_cross(v2, vec1);
    CHECK(cross_result2.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result2.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result2.z == Approx(-1.0_r).epsilon(g_epsilon));
  }

  {
    vec3 vec1(0.0_r, 5.0_r, 0.0_r);
    vec3 v2(0.0_r, 0.0_r, 12.0_r);

    vec3 cross_result = vec3_cross(vec1, v2);
    CHECK(cross_result.x == Approx(60.0_r).epsilon(g_epsilon));
    CHECK(cross_result.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result.z == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    vec3 x(1.0_r, 0.0_r, 0.0_r);
    vec3 y(0.0_r, 1.0_r, 0.0_r);
    vec3 z(0.0_r, 0.0_r, 1.0_r);

    vec3 cross_result1 = vec3_cross(x, y);
    CHECK(cross_result1.z == Approx(1.0_r).epsilon(g_epsilon));

    vec3 cross_result2 = vec3_cross(y, z);
    CHECK(cross_result2.x == Approx(1.0_r).epsilon(g_epsilon));

    vec3 cross_result3 = vec3_cross(z, x);
    CHECK(cross_result3.y == Approx(1.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("right_and_up", "[as_vec]")
{
  {
    vec3 dir(0.0_r, 0.0_r, 1.0_r);

    vec3 across_lh;
    vec3 up_lh;
    vec3_right_and_up_lh(dir, across_lh, up_lh);

    CHECK(across_lh.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(across_lh.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(across_lh.z == Approx(0.0_r).epsilon(g_epsilon));

    CHECK(up_lh.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(up_lh.y == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(up_lh.z == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    vec3 dir(0.0_r, 0.0_r, 1.0_r);

    vec3 across_rh;
    vec3 up_rh;
    vec3_right_and_up_rh(dir, across_rh, up_rh);

    CHECK(across_rh.x == Approx(-1.0_r).epsilon(g_epsilon));
    CHECK(across_rh.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(across_rh.z == Approx(0.0_r).epsilon(g_epsilon));

    CHECK(up_rh.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(up_rh.y == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(up_rh.z == Approx(0.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("equal", "[as_vec]")
{
  {
    vec3 vec1(1.11_r, 0.3_r, 517.2_r);
    vec3 v2(1.11_r, 0.3_r, 517.2_r);

    CHECK(vec_equal(vec1, v2));
  }

  {
    vec3 vec1(1.11_r, 0.3_r, 514.2_r);
    vec3 v2(1.114_r, 0.3_r, 517.2_r);

    CHECK_FALSE(vec_equal(vec1, v2));
  }

  {
    vec3 vec1(1.11_r, 0.3_r, 514.2_r);
    vec3 v2(1.11_r, 0.311_r, 514.2_r);

    CHECK_FALSE(vec_equal(vec1, v2));
  }
}

TEST_CASE("abs", "[as_vec]")
{
  {
    vec4 v(-1.0_r, -2.0_r, -100.0_r, -7.0_r);
    vec4 result = vec_abs(v);

    vec4 vec_reference = {1.0_r, 2.0_r, 100.0_r, 7.0_r};

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4 v{1.0_r, 4.0_r, 6.0_r, 50.0_r};
    vec4 result = vec_abs(v);

    vec4 vec_reference = {1.0_r, 4.0_r, 6.0_r, 50.0_r};

    CHECK(vec_equal(vec_reference, result));
  }

  {
    using vec5 = vec<real, 5>;

    vec5 v5{-1.0_r, -2.0_r, -100.0_r, -7.0_r, -4.0_r};
    vec5 result = vec_abs(v5);

    vec5 vec_reference = {1.0_r, 2.0_r, 100.0_r, 7.0_r, 4.0_r};

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("min_vec", "[as_vec]")
{
  {
    vec4 vec1(-1.0_r, 2.0_r, -100.0_r, -7.0_r);
    vec4 v2(-10.0_r, 7.0_r, -50.0_r, -16.0_r);

    vec4 vec_reference(-10.0_r, 2.0_r, -100.0_r, -16.0_r);

    vec4 result = vec_min(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4 vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    vec4 v2(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4 vec_reference(1.0_r, 2.0_r, 3.0_r, 4.0_r);

    vec4 result = vec_min(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("min_elem", "[as_vec]")
{
  {
    vec3 v{-1.0_r, 2.0_r, -100.0_r};
    real result = vec_min_elem(v);

    CHECK(result == Approx(-100.0_r).epsilon(g_epsilon));
  }

  {
    vec3 v{1.0_r, 2.0_r, 3.0_r};
    real result = vec_min_elem(v);

    CHECK(result == Approx(1.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("max_vec", "[as_vec]")
{
  {
    vec4 vec1(-1.0_r, 2.0_r, -100.0_r, -7.0_r);
    vec4 v2(-10.0_r, 7.0_r, -50.0_r, -16.0_r);

    vec4 vec_reference(-1.0_r, 7.0_r, -50.0_r, -7.0_r);

    vec4 result = vec_max(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4 vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    vec4 v2(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4 vec_reference(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4 result = vec_max(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("max_elem", "[as_vec]")
{
  {
    vec3 v{-1.0_r, 2.0_r, -100.0_r};
    real result = vec_max_elem(v);

    CHECK(result == Approx(2.0_r).epsilon(g_epsilon));
  }

  {
    vec3 v{1.0_r, 2.0_r, 3.0_r};
    real result = vec_max_elem(v);

    CHECK(result == Approx(3.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("clamp", "[as_vec]")
{
  {
    vec3 min_val(50.0_r, 50.0_r, 50.0_r);
    vec3 max_val(100.0_r, 100.0_r, 100.0_r);

    vec3 v(20.0_r, 20.0_r, 20.0_r);

    vec3 result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, min_val));
  }

  {
    vec3 min_val(50.0_r, 50.0_r, 50.0_r);
    vec3 max_val(100.0_r, 100.0_r, 100.0_r);

    vec3 v(120.0_r, 200.0_r, 300.0_r);

    vec3 result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, max_val));
  }

  {
    vec3 min_val(50.0_r, 50.0_r, 50.0_r);
    vec3 max_val(100.0_r, 100.0_r, 100.0_r);

    vec3 v(20.0_r, 120.0_r, 20.0_r);
    vec3 vec_reference(50.0_r, 100.0_r, 50.0_r);

    vec3 result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, vec_reference));
  }

  {
    vec3 min_val(50.0_r, 50.0_r, 50.0_r);
    vec3 max_val(100.0_r, 100.0_r, 100.0_r);

    vec3 v(62.0_r, 56.0_r, 72.0_r);

    vec3 result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, v));
  }
}

TEST_CASE("saturate", "[as_vec]")
{
  {
    vec3 v(-2.0_r, 0.5_r, 1.2_r);
    vec3 result = vec_saturate(v);

    vec3 vec_reference(0.0_r, 0.5_r, 1.0_r);

    CHECK(vec_equal(result, vec_reference));
  }

  {
    vec3 v(3.0_r, 0.1_r, -1.2_r);
    vec3 result = vec_saturate(v);

    vec3 vec_reference(1.0_r, 0.1_r, 0.0_r);

    CHECK(vec_equal(result, vec_reference));
  }
}

TEST_CASE("lerp", "[as_vec]")
{
  {
    using gsl::make_span;

    vec3 start(0.0_r, 10.0_r, 20.0_r);
    vec3 end(10.0_r, 40.0_r, 100.0_r);

    vec3 result_begin = vec_mix(start, end, 0.0_r);
    vec3 result_mid = vec_mix(start, end, 0.5_r);
    vec3 result_end = vec_mix(start, end, 1.0_r);

    const real result_begin_arr[] = {0.0_r, 10.0_r, 20.0_r};
    CHECK_THAT(make_span(result_begin_arr), elements_are_span(result_begin));

    const real result_mid_arr[] = {5.0_r, 25.0_r, 60.0_r};
    CHECK_THAT(make_span(result_mid_arr), elements_are_span(result_mid));

    const real result_end_arr[] = {10.0_r, 40.0_r, 100.0_r};
    CHECK_THAT(make_span(result_end_arr), elements_are_span(result_end));
  }
}

TEST_CASE("distance", "[as_vec]")
{
  const vec3 lhs = vec3(100.0_r, 100.0_r, 100.0_r);
  const vec3 rhs = vec3(50.0_r, 50.0_r, 50.0_r);

  real distance;
  distance = vec_distance(lhs, rhs);

  CHECK(distance == Approx(86.6025403784_r).epsilon(g_epsilon));
}

TEST_CASE("normalize_and_length", "[as_vec]")
{
  const vec3 v(3.0_r, 4.0_r, 0.0_r);
  const auto [vec_normalized, length] = vec_normalize_and_length(v);

  CHECK(length == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(vec_length(vec_normalized) == Approx(1.0_r).epsilon(g_epsilon));
}

TEST_CASE("length_squared_v3", "[as_vec]")
{
  const vec3 v(3.0_r, 4.0_r, 0.0_r);
  const real length_sq = vec_length_sq(v);

  CHECK(length_sq == Approx(25.0_r).epsilon(g_epsilon));
}

TEST_CASE("length_squared_generic", "[as_vec]")
{
  using vec5 = vec<real, 5>;

  const vec5 v(3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r);
  const real length_sq = vec_length_sq(v);

  CHECK(length_sq == Approx(135.0_r).epsilon(g_epsilon));
}

TEST_CASE("select", "[as_vec]")
{
  using int3 = vec<int, 3>;

  int3 a(1, 2, 3);
  int3 b(5, 6, 7);

  using byte4 = vec<uint8_t, 4>;

  byte4 c(uint8_t(255), uint8_t(255), uint8_t(255), uint8_t(255));
  byte4 d(uint8_t(0), uint8_t(0), uint8_t(0), uint8_t(0));

  int3 result = vec_select(a, b, true);
  byte4 result_byte = vec_select(c, d, false);

  CHECK(result[0] == 1);
  CHECK(result[1] == 2);
  CHECK(result[2] == 3);

  CHECK(result_byte[0] == 0);
  CHECK(result_byte[1] == 0);
  CHECK(result_byte[2] == 0);
  CHECK(result_byte[3] == 0);
}

TEST_CASE("wedge_vec2", "[as_vec]")
{
  {
    const vec2 vec1(2.0_r, 0.0_r);
    const vec2 v2(0.0_r, 2.0_r);
    const real result = vec2_wedge(vec1, v2);

    CHECK(result == Approx(4.0_r).epsilon(g_epsilon));
  }

  {
    const vec2 vec1(10.0_r, 10.0_r);
    const vec2 v2(20.0_r, 5.0_r);
    const real result = vec2_wedge(vec1, v2);

    CHECK(result == Approx(-150.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("vec_to_arr", "[as_vec]")
{
  using gsl::make_span;

  vec<real, 5> vec5{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r};

  real vec5_arr[5];
  vec_to_arr(vec5, vec5_arr);

  CHECK_THAT(make_span(vec5_arr), elements_are_span(vec5));
}

TEST_CASE("floor", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3 v(1.8_r, 2.2_r, 3.5_r);
    const vec3 floor_vec = vec_floor(v);

    real floor_expected[] = {1.0_r, 2.0_r, 3.0_r};

    CHECK_THAT(make_span(floor_expected), elements_are_span(floor_vec));
  }

  {
    const vec4 v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4 floor_vec = vec_floor(v);

    real floor_expected[] = {-2.0_r, -3.0_r, -4.0_r, -5.0_r};

    CHECK_THAT(make_span(floor_expected), elements_are_span(floor_vec));
  }
}

TEST_CASE("ceil", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3 v(1.8_r, 2.2_r, 3.5_r);
    const vec3 ceil_vec = vec_ceil(v);

    real ceil_expected[] = {2.0_r, 3.0_r, 4.0_r};

    CHECK_THAT(make_span(ceil_expected), elements_are_span(ceil_vec));
  }

  {
    const vec4 v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4 ceil_vec = vec_ceil(v);

    real ceil_expected[] = {-1.0_r, -2.0_r, -3.0_r, -4.0_r};

    CHECK_THAT(make_span(ceil_expected), elements_are_span(ceil_vec));
  }
}

TEST_CASE("round", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3 v(1.8_r, 2.2_r, 3.5_r);
    const vec3 round_vec = vec_round(v);

    real round_expected[] = {2.0_r, 2.0_r, 4.0_r};

    CHECK_THAT(make_span(round_expected), elements_are_span(round_vec));
  }

  {
    const vec4 v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4 round_vec = vec_round(v);

    real round_expected[] = {-1.0_r, -3.0_r, -4.0_r, -4.0_r};

    CHECK_THAT(make_span(round_expected), elements_are_span(round_vec));
  }
}

TEST_CASE("snap_vec", "[as_vec]")
{
  {
    vec2 v2{70.0_r, 95.0};
    vec2 result = as::vec_snap(v2, 30.0_r);

    CHECK_THAT(arr(60.0_r, 90.0_r), elements_are_array(result));
  }

  {
    vec3 v3{1.0_r, 2.0_r, 3.0_r};
    vec3 result = as::vec_snap(v3, 0.5_r);

    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(result));
  }

  {
    using vec5 = vec<real, 5>;

    vec5 v5{5.0_r, 12.0_r, 18.0_r, 22.0_r, 1000.0_r};
    vec5 result = as::vec_snap(v5, 5.0_r);

    const auto expected =
      std::array<real, 5>{5.0_r, 10.0_r, 20.0_r, 20.0_r, 1000.0_r};

    CHECK_THAT(expected, elements_are_array(result));
  }
}

TEST_CASE("reflect", "[as_vec]")
{
  {
    const auto l = as::vec3(1.0f, -1.0f, 0.0f);
    const auto n = as::vec3(0.0f, 1.0f, 0.0f);
    const auto r = as::vec3_reflect(l, n);
    CHECK_THAT(arr(1.0_r, 1.0_r, 0.0_r), elements_are_array(r));
  }

  {
    const auto l = as::vec3(1.0f, -1.0f, 0.0f);
    const auto n = as::vec3(-1.0f, 0.0f, 0.0f);
    const auto r = as::vec3_reflect(l, n);
    CHECK_THAT(arr(-1.0_r, -1.0_r, 0.0_r), elements_are_array(r));
  }

  {
    const auto l = as::vec3(0.0f, -5.0f, -5.0f);
    const auto n = as::vec3(0.0f, -1.0f, 0.0f);
    const auto r = as::vec3_reflect(l, n);
    CHECK_THAT(arr(0.0_r, 5.0_r, -5.0_r), elements_are_array(r));
  }
}

TEST_CASE("orthogonal", "[as_vec]")
{
  {
    const auto vec = as::vec3::axis_x();

    vec3 orthogonal_vec;
    orthogonal_vec = as::vec3_orthogonal(vec);

    real dot = as::vec_dot(orthogonal_vec, vec);
    CHECK(dot == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const auto vec = as::vec3::axis_z();

    vec3 orthogonal_vec;
    orthogonal_vec = as::vec3_orthogonal(vec);

    real dot = as::vec_dot(orthogonal_vec, vec);
    CHECK(dot == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const auto vec = vec_normalize(as::vec3(-2.0_r, 4.0_r, 10.0_r));

    vec3 orthogonal_vec;
    orthogonal_vec = as::vec3_orthogonal(vec);

    real dot = as::vec_dot(orthogonal_vec, vec);
    CHECK(dot == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const auto vec = vec_normalize(as::vec3(-150.0_r, -40.0_r, 0.1_r));

    vec3 orthogonal_vec;
    orthogonal_vec = as::vec3_orthogonal(vec);

    real dot = as::vec_dot(orthogonal_vec, vec);
    CHECK(dot == Approx(0.0_r).margin(g_epsilon));
  }
}

TEST_CASE("orthonomal_basis", "[as_vec]")
{
  {
    const mat3 basis = orthonormal_basis(vec3(1.0_r, 0.0_r, 0.0_r));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), elements_are_array(as::mat3_basis_x(basis)));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), elements_are_array(as::mat3_basis_y(basis)));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), elements_are_array(as::mat3_basis_z(basis)));
  }

  {
    const mat3 basis = orthonormal_basis(vec3(0.0_r, -1.0_r, 0.0_r));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), elements_are_array(as::mat3_basis_x(basis)));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, -1.0_r), elements_are_array(as::mat3_basis_y(basis)));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), elements_are_array(as::mat3_basis_z(basis)));
  }

  {
    const mat3 basis = orthonormal_basis(vec3(0.0_r, 1.0_r, 0.0_r));
    CHECK_THAT(
      arr(0.0_r, 1.0_r, 0.0_r), elements_are_array(as::mat3_basis_x(basis)));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), elements_are_array(as::mat3_basis_y(basis)));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), elements_are_array(as::mat3_basis_z(basis)));
  }

  {
    const mat3 basis = orthonormal_basis(vec3(0.0_r, 0.0_r, 1.0_r));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), elements_are_array(as::mat3_basis_x(basis)));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), elements_are_array(as::mat3_basis_y(basis)));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), elements_are_array(as::mat3_basis_z(basis)));
  }

  {
    const mat3 basis =
      orthonormal_basis(vec_normalize(vec3(1.0_r, 1.0_r, 0.0_r)));
    CHECK_THAT(
      arr(0.707107_r, 0.707107_r, 0.000000_r),
      elements_are_array(as::mat3_basis_x(basis)).epsilon(0.001_r));
    CHECK_THAT(
      arr(-0.707107_r, 0.707107_r, 0.000000_r),
      elements_are_array(as::mat3_basis_y(basis)).epsilon(0.001_r));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), elements_are_array(as::mat3_basis_z(basis)));
  }
}

TEST_CASE("average", "[as_vec]")
{
  {
    vec2 avg = vec_average_fold(vec2{2.0_r, 2.0_r}, vec2{4.0_r, 4.0_r});
    CHECK_THAT(arr(3.0_r, 3.0_r), elements_are_array(avg));
  }

  {
    vec2 vecs[] = {vec2{2.0_r, 2.0_r}, vec2{4.0_r, 4.0_r}};
    vec2 avg = vec_average(vecs, std::size(vecs));
    CHECK_THAT(arr(3.0_r, 3.0_r), elements_are_array(avg));
  }

  {
    vec3 avg =
      vec_average_fold(vec3{3.0_r, 3.0_r, 3.0_r}, vec3{5.0_r, 5.0_r, 5.0_r});
    CHECK_THAT(arr(4.0_r, 4.0_r, 4.0_r), elements_are_array(avg));
  }

  {
    vec3 vecs[] = {vec3{3.0_r, 3.0_r, 3.0_r}, vec3{5.0_r, 5.0_r, 5.0_r}};
    vec3 avg = vec_average(vecs, std::size(vecs));
    CHECK_THAT(arr(4.0_r, 4.0_r, 4.0_r), elements_are_array(avg));
  }
}

TEST_CASE("vec_data", "[as_vec]")
{
  vec4 vec = vec4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
  real* vecp = vec_data(vec);
  CHECK(*vecp == Approx(1.0f).epsilon(g_epsilon));
  CHECK(*(vecp + 1) == Approx(2.0f).epsilon(g_epsilon));
  CHECK(*(vecp + 2) == Approx(3.0f).epsilon(g_epsilon));
  CHECK(*(vecp + 3) == Approx(4.0f).epsilon(g_epsilon));
}

TEST_CASE("vec4_translation_direction", "[as_vec]")
{
  vec3 vector3(5.0_r, 10.0_r, 15.0_r);
  const vec4 translation = vec4_translation(vector3);
  CHECK_THAT(arr(5.0_r, 10.0_r, 15.0_r, 1.0f), elements_are_array(translation));

  vec3 translation_3(5.0_r, 10.0_r, 15.0_r);
  vec4 expected_direction(translation_3, 0.0f);
  const vec4 direction = vec4_direction(vector3);
  CHECK_THAT(arr(5.0_r, 10.0_r, 15.0_r, 0.0f), elements_are_array(direction));

  CHECK_THAT(expected_direction, elements_are(direction));
  CHECK_THAT(arr(5.0_r, 10.0_r, 15.0_r, 0.0f), elements_are_array(direction));
}

template<typename T, index d>
std::string print_vec(const as::vec<T, d>& vec)
{
  std::stringstream ss;
  ss << "{ ";
  for (index i = 0; i < d - 1; ++i) {
    ss << std::to_string(vec[i]) << ", ";
  }
  ss << std::to_string(vec[d - 1]) << " }";
  return ss.str();
}

} // namespace unit_test

namespace Catch
{
template<>
struct StringMaker<as::vec2>
{
  static std::string convert(const as::vec2& vec)
  {
    return unit_test::print_vec(vec);
  }
};
template<>
struct StringMaker<as::vec3>
{
  static std::string convert(const as::vec3& vec)
  {
    return unit_test::print_vec(vec);
  }
};
template<>
struct StringMaker<as::vec4>
{
  static std::string convert(const as::vec4& vec)
  {
    return unit_test::print_vec(vec);
  }
};
} // namespace Catch

// explicit instantiations (for coverage)

// types
template struct as::vec<as::real, 2>;
template struct as::vec<as::real, 3>;
template struct as::vec<as::real, 4>;
template struct as::vec<as::real, 5>;

#ifdef __GNUC__
// constructor
template as::vec<as::real, 5>::vec(
  as::real, as::real, as::real, as::real, as::real) noexcept;
#endif // __GNUC__

// operators
template const as::vec<as::real, 5> as::operator+(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template const as::vec<as::real, 5> as::operator-(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template const as::vec<as::real, 5> as::operator-(const as::vec<as::real, 5>&);
template const as::vec<as::real, 5> as::operator*(
  const as::vec<as::real, 5>&, as::real);
template const as::vec<as::real, 5> as::operator*(
  as::real, const as::vec<as::real, 5>&);
template const as::vec<as::real, 5> as::operator*(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template const as::vec<as::real, 5> as::operator/(
  const as::vec<as::real, 5>&, as::real);
template const as::vec<as::real, 5> as::operator/(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);

// functions
template void as::vec_to_arr(
  const as::vec<as::real, 5>& v, as::real (&data)[5]);
template as::real as::vec_dot(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template std::tuple<as::vec<as::real, 5>, as::real> as::
  vec_normalize_and_length(const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_min(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template as::real as::vec_min_elem(const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_max(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&);
template as::real as::vec_max_elem(const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_abs(const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_clamp(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&,
  const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_saturate(const as::vec<as::real, 5>&);
template as::vec<as::real, 5> as::vec_mix(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&, as::real);
template as::vec<as::real, 5> as::vec_select(
  const as::vec<as::real, 5>&, const as::vec<as::real, 5>&, bool);
template as::vec<as::real, 5> as::vec_average(
  const as::vec<as::real, 5>* v, as::index);
template auto as::vec_average_fold<as::vec<as::real, 5>, as::vec<as::real, 5>>(
  as::vec<as::real, 5>&&, as::vec<as::real, 5>&&);
template as::real* as::vec_data(as::vec<as::real, 5>&);
template const as::real* as::vec_const_data(const as::vec<as::real, 5>&);
template as::vec<as::real, 4> as::vec4_translation(const as::vec<as::real, 3>&);
template as::vec<as::real, 4> as::vec4_direction(const as::vec<as::real, 3>&);
