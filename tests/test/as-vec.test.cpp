#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

#include <memory>

namespace unit_test
{

// types
using as::index_t;
using as::mat3_t;
using as::point3_t;
using as::real_t;
using as::vec2_t;
using as::vec3_t;
using as::vec4_t;
using as::vec_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// use float epsilon for comparisons
const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("vec2_initialization", "[as_vec]")
{
  // default initialization
  {
    vec2_t v2;
    (void)v2;
  }

  // zero initialization
  {
    vec2_t v2{};
    CHECK_THAT(arr(0.0_r, 0.0_r), make_elements_sub(v2, 2));
  }

  // value initialization
  {
    vec2_t v2 = vec2_t();
    CHECK_THAT(arr(0.0_r, 0.0_r), make_elements_sub(v2, 2));
  }

  // direct initialization (braces)
  {
    vec2_t v2{1.0_r, 2.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r), make_elements_sub(v2, 2));
  }

  // direct initialization - single argument (braces)
  {
    vec2_t v2{5.0_r};
    CHECK_THAT(arr(5.0_r, 5.0_r), make_elements_sub(v2, 2));
  }

  // direct initialization (parens)
  {
    vec2_t v2(5.0_r, 10.0_r);
    CHECK_THAT(arr(5.0_r, 10.0_r), make_elements_sub(v2, 2));
  }

  // direct initialization - single argument (parens)
  {
    vec2_t v2;
    v2 = vec2_t(6.0_r);
    CHECK_THAT(arr(6.0_r, 6.0_r), make_elements_sub(v2, 2));
  }

  // direct/copy initialization (braces)
  {
    vec2_t v2 = vec2_t{3.0_r, 4.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r), make_elements_sub(v2, 2));
  }

  // direct/copy initialization (parens)
  {
    vec2_t v2 = vec2_t(3.0_r, 4.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r), make_elements_sub(v2, 2));
  }

  // direct/copy initialization - single argument (braces)
  {
    const real_t value{123.0_r};
    vec2_t v2 = vec2_t{value};
    CHECK_THAT(arr(123.0_r, 123.0_r), make_elements_sub(v2, 2));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v2 = vec2_t(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r), make_elements_sub(v2, 2));
  }

  // assignment initialization - single argument (braces)
  {
    vec2_t v2;
    v2 = vec2_t{75.0_r};
    CHECK_THAT(arr(75.0_r, 75.0_r), make_elements_sub(v2, 2));
  }

  // direct + copy initialization
  {
    vec2_t vec2_a(300.0_r, 400.0_r);
    vec2_t vec2_b(vec2_a);

    CHECK_THAT(arr(300.0_r, 400.0_r), make_elements_sub(vec2_b, 2));
  }

  // direct + copy initialization (assignment)
  {
    vec2_t vec2_a(100.0_r, 200.0_r);
    vec2_t vec2_b = vec2_a;

    CHECK_THAT(arr(100.0_r, 200.0_r), make_elements_sub(vec2_b, 2));
  }

  // direct + copy initialization (assignment)
  {
    vec2_t vec2_a(500.0_r, 600.0_r);
    vec2_t vec2_b;

    vec2_b = vec2_a;

    CHECK_THAT(arr(500.0_r, 600.0_r), make_elements_sub(vec2_b, 2));
  }
}

TEST_CASE("vec3_initialization", "[as_vec]")
{
  using gsl::make_span;

  // default initialization
  {
    vec3_t v3;
    (void)v3;
  }

  // zero initialization
  {
    vec3_t v3{};
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), make_elements_sub(v3, 3));
  }

  // value initialization
  {
    vec3_t v3 = vec3_t();
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), make_elements_sub(v3, 3));
  }

  // direct initialization (braces)
  {
    vec3_t v3{1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(v3, 3));
  }

  // direct initialization (parens)
  {
    vec3_t v3(5.0_r, 10.0_r, 15.0_r);
    CHECK_THAT(arr(5.0_r, 10.0_r, 15.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization (braces)
  {
    vec3_t v3 = vec3_t{1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization (parens)
  {
    vec3_t v3 = vec3_t(3.0_r, 4.0_r, 5.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization - single argument (braces)
  {
    vec3_t v3 = vec3_t{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r), make_elements_sub(v3, 3));
  }

  // assignment initialization - single argument (braces)
  {
    vec3_t v3;
    v3 = vec3_t{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v3 = vec3_t(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r, 25.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec3_t v3 = vec3_t{vec2_t{1.0_r, 2.0_r}, 3.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(v3, 3));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec2_t v2 = vec2_t(1.0_r, 2.0_r);
    vec3_t v3 = vec3_t(v2, 3.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(v3, 3));
  }

  // direct + copy initialization
  {
    vec3_t vec3_a(100.0_r, 200.0_r, 300.0_r);
    vec3_t vec3_b(vec3_a);

    CHECK_THAT(arr(100.0_r, 200.0_r, 300.0_r), make_elements_sub(vec3_b, 3));
  }

  // direct + copy initialization
  {
    vec3_t vec3_a(400.0_r, 500.0_r, 600.0_r);
    vec3_t vec3_b = vec3_a;

    CHECK_THAT(arr(400.0_r, 500.0_r, 600.0_r), make_elements_sub(vec3_b, 3));
  }

  // direct + copy initialization (assignment)
  {
    vec3_t vec3_a(500.0_r, 600.0_r, 700.0_r);
    vec3_t vec3_b;

    vec3_b = vec3_a;

    CHECK_THAT(arr(500.0_r, 600.0_r, 700.0_r), make_elements_sub(vec3_b, 3));
  }
}

TEST_CASE("vec4_initialization", "[as_vec]")
{
  // default initialization
  {
    vec4_t v4;
    (void)v4;
  }

  // zero initialization
  {
    vec4_t v4{};
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r, 0.0_r), make_elements_sub(v4, 4));
  }

  // value initialization
  {
    vec4_t v4 = vec4_t();
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r, 0.0_r), make_elements_sub(v4, 4));
  }

  // direct initialization (braces)
  {
    vec4_t v4{1.0_r, 2.0_r, 3.0_r, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct initialization (parens)
  {
    vec4_t v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization (braces)
  {
    vec4_t v4 = vec4_t{3.0_r, 4.0_r, 5.0_r, 6.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r, 6.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization (parens)
  {
    vec4_t v4 = vec4_t(3.0_r, 4.0_r, 5.0_r, 6.0_r);
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r, 6.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - single argument (braces)
  {
    vec4_t v4 = vec4_t{50.0_r};
    CHECK_THAT(arr(50.0_r, 50.0_r, 50.0_r, 50.0_r), make_elements_sub(v4, 4));
  }

  // assignment initialization - single argument (braces)
  {
    vec4_t v4;
    v4 = vec4_t{99.0_r};
    CHECK_THAT(arr(99.0_r, 99.0_r, 99.0_r, 99.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - single argument (parens)
  {
    auto v4 = vec4_t(25.0_r);
    CHECK_THAT(arr(25.0_r, 25.0_r, 25.0_r, 25.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec4_t v4 = vec4_t{vec3_t{1.0_r, 2.0_r, 3.0_r}, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec4_t v4 = vec4_t(vec3_t(1.0_r, 2.0_r, 3.0_r), 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - double argument (braces)
  {
    vec4_t v4 = vec4_t{vec2_t{1.0_r, 2.0_r}, vec2_t{3.0_r, 4.0_r}};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - double argument (parens)
  {
    vec4_t v4 = vec4_t(vec2_t(1.0_r, 2.0_r), vec2_t(3.0_r, 4.0_r));
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - triple argument (braces)
  {
    vec4_t v4 = vec4_t{vec2_t{1.0_r, 2.0_r}, 3.0_r, 4.0_r};
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct/copy initialization - triple argument (parens)
  {
    vec4_t v4 = vec4_t(vec2_t(1.0_r, 2.0_r), 3.0_r, 4.0_r);
    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r, 4.0_r), make_elements_sub(v4, 4));
  }

  // direct + copy initialization
  {
    vec4_t vec4_a(100.0_r, 200.0_r, 300.0_r, 400.0_r);
    vec4_t vec4_b(vec4_a);

    CHECK_THAT(
      arr(100.0_r, 200.0_r, 300.0_r, 400.0_r), make_elements_sub(vec4_b, 4));
  }

  // direct + copy initialization
  {
    vec4_t vec4_a(500.0_r, 600.0_r, 700.0_r, 800.0_r);
    vec4_t vec4_b = vec4_a;

    CHECK_THAT(
      arr(500.0_r, 600.0_r, 700.0_r, 800.0_r), make_elements_sub(vec4_b, 4));
  }

  // direct + copy initialization (assignment)
  {
    vec4_t vec4_a(500.0_r, 600.0_r, 700.0_r, 800.0_r);
    vec4_t vec4_b;

    vec4_b = vec4_a;

    CHECK_THAT(
      arr(500.0_r, 600.0_r, 700.0_r, 800.0_r), make_elements_sub(vec4_b, 4));
  }
}

TEST_CASE("vec2_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec2_t v2{};
    CHECK(v2.x == Approx(v2[0]).epsilon(g_epsilon));
    CHECK(v2.y == Approx(v2[1]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec2_t v2(1.0_r, 2.0_r);
    CHECK(v2.x == Approx(v2[0]).epsilon(g_epsilon));
    CHECK(v2.y == Approx(v2[1]).epsilon(g_epsilon));
  }

  // member and const subscript operator - explicit construction
  {
    vec2_t v2(1.0_r, 2.0_r);
    const real_t& x = v2[0];
    const real_t& y = v2[1];

    CHECK(v2.x == Approx(x).epsilon(g_epsilon));
    CHECK(v2.y == Approx(y).epsilon(g_epsilon));
  }
}

TEST_CASE("vec3_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec3_t v3{};
    CHECK(v3.x == Approx(v3[0]).epsilon(g_epsilon));
    CHECK(v3.y == Approx(v3[1]).epsilon(g_epsilon));
    CHECK(v3.z == Approx(v3[2]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec3_t v3(1.0_r, 2.0_r, 3.0_r);
    CHECK(v3.x == Approx(v3[0]).epsilon(g_epsilon));
    CHECK(v3.y == Approx(v3[1]).epsilon(g_epsilon));
    CHECK(v3.z == Approx(v3[2]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec3_t v3(1.0_r, 2.0_r, 3.0_r);
    CHECK(vec2_from_vec3(v3)[0] == Approx(v3.x).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3)[1] == Approx(v3.y).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3).x == Approx(v3.x).epsilon(g_epsilon));
    CHECK(vec2_from_vec3(v3).y == Approx(v3.y).epsilon(g_epsilon));
  }

  // member and const subscript operator - explicit construction
  {
    vec3_t v3(1.0_r, 2.0_r, 3.0_r);
    const real_t& x = v3[0];
    const real_t& y = v3[1];
    const real_t& z = v3[2];

    CHECK(v3.x == Approx(x).epsilon(g_epsilon));
    CHECK(v3.y == Approx(y).epsilon(g_epsilon));
    CHECK(v3.z == Approx(z).epsilon(g_epsilon));
  }
}

TEST_CASE("vec4_accessors", "[as_vec]")
{
  // member and subscript operator - zero initializer
  {
    vec4_t v4{};
    CHECK(v4.x == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(v4.y == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(v4.z == Approx(v4[2]).epsilon(g_epsilon));
    CHECK(v4.w == Approx(v4[3]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec4_t v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK(v4.x == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(v4.y == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(v4.z == Approx(v4[2]).epsilon(g_epsilon));
    CHECK(v4.w == Approx(v4[3]).epsilon(g_epsilon));
  }

  // member and subscript operator - explicit construction
  {
    vec4_t v4(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK(vec2_from_vec4(v4)[0] == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(vec2_from_vec4(v4)[1] == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[0] == Approx(v4[0]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[1] == Approx(v4[1]).epsilon(g_epsilon));
    CHECK(vec3_from_vec4(v4)[2] == Approx(v4[2]).epsilon(g_epsilon));
  }
}

TEST_CASE("vec2_vec3_vec4_accessors", "[as_vec]")
{
  vec2_t v2(1.0_r, 2.0_r);
  vec3_t v3(v2, 3.0_r);

  vec4_t vec4_a(v2, 3.0_r, 4.0_r);
  vec4_t vec4_b(v2, v2);
  vec4_t vec4_c(v3, 4.0_r);

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
    vec3_from_vec2(v2, real_t(3.0)).z
    == Approx(real_t(3.0)).epsilon(g_epsilon));

  CHECK(vec4_from_vec2(v2).x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_from_vec2(v2).y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec2(v2, real_t(3.0)).z
    == Approx(real_t(3.0)).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec2(v2, real_t(3.0), real_t(4.0)).w
    == Approx(real_t(4.0)).epsilon(g_epsilon));

  CHECK(vec4_from_vec3(v3).x == Approx(v2.x).epsilon(g_epsilon));
  CHECK(vec4_from_vec3(v3).y == Approx(v2.y).epsilon(g_epsilon));
  CHECK(vec4_from_vec3(v3).z == Approx(real_t(3.0)).epsilon(g_epsilon));
  CHECK(
    vec4_from_vec3(v3, real_t(4.0)).w
    == Approx(real_t(4.0)).epsilon(g_epsilon));
}

TEST_CASE("const_elem_access_vec_const", "[as_vec]")
{
  using gsl::make_span;

  const vec_t<real_t, 5> vec5(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);

  const real_t elem_0 = vec5[0];
  const real_t elem_1 = vec5[1];
  const real_t elem_2 = vec5[2];
  const real_t elem_3 = vec5[3];
  const real_t elem_4 = vec5[4];

  const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
  CHECK_THAT(make_span(vec_arr), make_elements_sub(vec5, 5));
}

TEST_CASE("elem_access_vec", "[as_vec]")
{
  using gsl::make_span;
  vec_t<real_t, 5> vec5(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);

  real_t elem_0 = vec5[0];
  real_t elem_1 = vec5[1];
  real_t elem_2 = vec5[2];
  real_t elem_3 = vec5[3];
  real_t elem_4 = vec5[4];

  const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
  CHECK_THAT(make_span(vec_arr), make_elements_sub(vec5, 5));
}

TEST_CASE("const_elem_access_vec2_3_4", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec2_t v2(15.0_r, 30.0_r);

    const real_t elem_0 = v2[0];
    const real_t elem_1 = v2[1];

    const real_t vec_arr[] = {elem_0, elem_1};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(v2, 2));
  }

  {
    const vec3_t v3(2.0_r, 3.0_r, 4.0_r);

    const real_t elem_0 = v3[0];
    const real_t elem_1 = v3[1];
    const real_t elem_2 = v3[2];

    const real_t vec_arr[] = {elem_0, elem_1, elem_2};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(v3, 3));
  }

  {
    vec4_t v4;
    v4 = vec4_t(10.0_r, 20.0_r, 30.0_r, 40.0_r);

    const real_t elem_0 = v4[0];
    const real_t elem_1 = v4[1];
    const real_t elem_2 = v4[2];
    const real_t elem_3 = v4[3];

    const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(v4, 4));
  }
}

TEST_CASE("rvalue_elem_access_vec2_3_4_5", "[as_vec]")
{
  using gsl::make_span;

  auto make_vec2 = []() { return vec2_t{5.0_r, 10.0_r}; };
  CHECK(make_vec2()[0] == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(make_vec2()[1] == Approx(10.0_r).epsilon(g_epsilon));

  auto make_vec3 = []() { return vec3_t{5.0_r, 10.0_r, 15.0_r}; };
  CHECK(make_vec3()[0] == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(make_vec3()[1] == Approx(10.0_r).epsilon(g_epsilon));
  CHECK(make_vec3()[2] == Approx(15.0_r).epsilon(g_epsilon));

  auto make_vec4 = []() { return vec4_t{7.0_r, 14.0_r, 21.0_r, 28.0_r}; };
  CHECK(make_vec4()[0] == Approx(7.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[1] == Approx(14.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[2] == Approx(21.0_r).epsilon(g_epsilon));
  CHECK(make_vec4()[3] == Approx(28.0_r).epsilon(g_epsilon));

  auto make_vec5 = []() {
    return vec_t<real_t, 5>{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r};
  };
  CHECK(make_vec5()[0] == Approx(1.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[1] == Approx(2.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[2] == Approx(3.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[3] == Approx(4.0_r).epsilon(g_epsilon));
  CHECK(make_vec5()[4] == Approx(5.0_r).epsilon(g_epsilon));
}

TEST_CASE("vec_size", "[as_vec]")
{
  static_assert(vec2_t::size() == 2, "vec2_t size must be 2");
  index_t vec2_size;
  vec2_size = vec2_t::size();
  vec2_t v2;
  index_t vec2_inst_size;
  vec2_inst_size = vec_size(v2);
  CHECK(vec2_size == 2);
  CHECK(vec2_inst_size == vec2_size);

  static_assert(vec3_t::size() == 3, "vec3_t size must be 3");
  index_t vec3_size;
  vec3_size = vec3_t::size();
  vec3_t v3;
  index_t vec3_inst_size;
  vec3_inst_size = vec_size(v3);
  CHECK(vec3_size == static_cast<index_t>(3));
  CHECK(vec3_inst_size == Approx(vec3_size).epsilon(g_epsilon));

  static_assert(vec4_t::size() == 4, "vec4_t size must be 4");
  index_t vec4_size;
  vec4_size = vec4_t::size();
  vec4_t v4;
  index_t vec4_inst_size;
  vec4_inst_size = vec_size(v4);
  CHECK(vec4_size == static_cast<index_t>(4));
  CHECK(vec4_inst_size == Approx(vec4_size).epsilon(g_epsilon));

  using short7 = vec_t<short, 7>;
  short7 vec_short7;
  index_t vec_short7_inst_size;
  vec_short7_inst_size = vec_size(vec_short7);
  index_t short7_size;
  short7_size = short7::size();
  CHECK(short7_size == static_cast<index_t>(7));
  CHECK(vec_short7_inst_size == Approx(short7_size).epsilon(g_epsilon));

  using int5 = vec_t<int, 5>;
  int5 vec_short5;
  index_t vec_short5_inst_size;
  vec_short5_inst_size = vec_size(vec_short5);
  index_t int5_size = int5::size();
  CHECK(int5_size == static_cast<index_t>(5));
  CHECK(vec_short5_inst_size == Approx(int5_size).epsilon(g_epsilon));
}

TEST_CASE("vec_make_from_arr", "[as_vec]")
{
  // generic make_from_arr vec2_t
  {
    real_t vec_data[2] = {2.0_r, 4.0_r};
    vec2_t v2 = as::vec_from_arr(vec_data);

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));

    // won't compile (array length 2 to vec3_t)
    // vec3_t v3 = make_from(vec_data);
  }

  // generic make_from_arr vec3_t
  {
    real_t vec_data[3] = {1.0_r, 2.0_r, 3.0_r};
    vec3_t v3 = as::vec_from_arr(vec_data);

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // generic make_from_arr <char, 6>
  {
    char vec_data[6] = {11, 12, 13, 14, 15, 16};
    vec_t<char, 6> char_6 = as::vec_from_arr(vec_data);

    CHECK(char_6[0] == 11);
    CHECK(char_6[1] == 12);
    CHECK(char_6[2] == 13);
    CHECK(char_6[3] == 14);
    CHECK(char_6[4] == 15);
    CHECK(char_6[5] == 16);
  }

  // vec2_make_from_arr
  {
    real_t vec_data[2] = {2.0_r, 4.0_r};
    vec2_t v2 = as::vec2_from_arr(vec_data);

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // vec3_make_from_arr
  {
    real_t vec_data[3] = {1.0_r, 2.0_r, 3.0_r};
    vec3_t v3 = as::vec3_from_arr(vec_data);

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // vec4_make_from_arr
  {
    real_t vec_data[4] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    vec4_t v4 = as::vec4_from_arr(vec_data);

    CHECK(v4.x == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(v4.y == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(v4.z == Approx(12.0_r).epsilon(g_epsilon));
    CHECK(v4.w == Approx(16.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("vec_make_from_ptr", "[as_vec]")
{
  // generic make_from_ptr vec2_t
  {
    std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(2);
    vec_data[0] = 2.0_r;
    vec_data[1] = 4.0_r;
    vec2_t v2 = as::vec_from_ptr<real_t, 2>(vec_data.get());

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // generic make_from_ptr vec3_t
  {
    std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(3);
    vec_data[0] = 1.0_r;
    vec_data[1] = 2.0_r;
    vec_data[2] = 3.0_r;
    vec3_t v3 = as::vec_from_ptr<real_t, 3>(vec_data.get());

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
    vec_t<char, 6> char_6 = as::vec_from_ptr<char, 6>(vec_data.get());

    CHECK(char_6[0] == 11);
    CHECK(char_6[1] == 12);
    CHECK(char_6[2] == 13);
    CHECK(char_6[3] == 14);
    CHECK(char_6[4] == 15);
    CHECK(char_6[5] == 16);
  }

  {
    int64_t vec_data[4] = {4, 8, 12, 16};
    vec_t<int64_t, 4> int64_t_5 = as::vec4_from_ptr(&vec_data[0]);

    CHECK(int64_t_5[0] == 4);
    CHECK(int64_t_5[1] == 8);
    CHECK(int64_t_5[2] == 12);
    CHECK(int64_t_5[3] == 16);
  }

  // vec2_make_from_ptr
  {
    std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(2);
    vec_data[0] = 2.0_r;
    vec_data[1] = 4.0_r;
    vec2_t v2 = as::vec2_from_ptr(vec_data.get());

    CHECK(v2.x == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v2.y == Approx(4.0_r).epsilon(g_epsilon));
  }

  // vec3_make_from_ptr
  {
    std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(3);
    vec_data[0] = 1.0_r;
    vec_data[1] = 2.0_r;
    vec_data[2] = 3.0_r;
    vec3_t v3 = as::vec3_from_ptr(vec_data.get());

    CHECK(v3.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(v3.y == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(v3.z == Approx(3.0_r).epsilon(g_epsilon));
  }

  // vec4_make_from_ptr
  {
    std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(4);
    vec_data[0] = 4.0_r;
    vec_data[1] = 8.0_r;
    vec_data[2] = 12.0_r;
    vec_data[3] = 16.0_r;
    vec4_t v4 = as::vec4_from_ptr(vec_data.get());

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
    // vec_t<char, 2> char_2 = from_ptr<char, 2>(vec_data.get());
    // vec2_t v2 = from_ptr<float, 2>(vec_data.get());
    vec_t<double, 2> v2 = as::vec_from_ptr<double, 2>(vec_data.get());
    (void)v2;
  }
}

TEST_CASE("addition", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '+'
  {
    vec5_t v = vec5_t{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r}
             + vec5_t{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r};

    CHECK(vec_equal(v, vec5_t(50.0_r, 50.0_r, 50.0_r, 50.0_r, 50.0_r)));
  }

  // vec_t operator '+='
  {
    vec5_t vec1(10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r);
    vec1 += vec5_t(25.0_r, 15.0_r, 5.0_r, 10.0_r, 1.0_r);
    CHECK(vec_equal(vec1, vec5_t(35.0_r, 35.0_r, 35.0_r, 50.0_r, 51.0_r)));
  }
}

TEST_CASE("addition_vec3", "[as_vec]")
{
  // vec3_t operator '+'
  {
    vec3_t v = vec3_t{10.0_r, 20.0_r, 30.0_r} + vec3_t{20.0_r, 10.0_r, 0.0_r};
    CHECK(vec_equal(v, vec3_t(30.0_r, 30.0_r, 30.0_r)));
  }

  // vec3_t operator '+='
  {
    vec3_t v(10.0_r, 20.0_r, 30.0_r);
    v += vec3_t(25.0_r, 15.0_r, 5.0_r);
    CHECK(vec_equal(v, vec3_t(35.0_r, 35.0_r, 35.0_r)));
  }
}

TEST_CASE("substraction", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '-'
  {
    vec5_t v = vec5_t{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r}
             - vec5_t{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r};

    CHECK(vec_equal(v, vec5_t(30.0_r, 10.0_r, -10.0_r, -30.0_r, -50.0_r)));
  }

  // vec_t operator '-='
  {
    vec5_t v(10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r);
    v -= vec5_t(25.0_r, 15.0_r, 5.0_r, 10.0_r, 1.0_r);
    CHECK(vec_equal(v, vec5_t(-15.0_r, 5.0_r, 25.0_r, 30.0_r, 49.0_r)));
  }
}

TEST_CASE("substraction_vec3", "[as_vec]")
{
  // vec3_t operator '-'
  {
    vec3_t v = vec3_t{40.0_r, 30.0_r, 20.0_r} - vec3_t{10.0_r, 20.0_r, 30.0_r};
    CHECK(vec_equal(v, vec3_t(30.0_r, 10.0_r, -10.0_r)));
  }

  // vec3_t operator '-='
  {
    vec3_t v(10.0_r, 20.0_r, 30.0_r);
    v -= vec3_t(25.0_r, 15.0_r, 5.0_r);
    CHECK(vec_equal(v, vec3_t(-15.0_r, 5.0_r, 25.0_r)));
  }
}

TEST_CASE("negation", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  vec5_t v = vec5_t{40.0_r, 30.0_r, 20.0_r, 10.0_r, 0.0_r};
  vec5_t neg_vec = -v;
  CHECK(vec_equal(neg_vec, vec5_t(-40.0_r, -30.0_r, -20.0_r, -10.0_r, -0.0_r)));
}

TEST_CASE("negation_vec3", "[as_vec]")
{
  vec3_t v = vec3_t{20.0_r, 10.0_r, 0.0_r};
  vec3_t neg_vec = -v;
  CHECK(vec_equal(neg_vec, vec3_t(-20.0_r, -10.0_r, -0.0_r)));
}

TEST_CASE("multiplication_scalar", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '*'
  {
    vec5_t v;
    v = real_t(5.0) * vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    CHECK(vec_equal(v, vec5_t(250.0_r, 200.0_r, 125.0_r, 100.0_r, 50.0_r)));
  }

  // vec_t operator '*='
  {
    vec5_t v = vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    v *= real_t(5.0);
    CHECK(vec_equal(v, vec5_t(250.0_r, 200.0_r, 125.0_r, 100.0_r, 50.0_r)));
  }
}

TEST_CASE("multiplication_scalar_vec3", "[as_vec]")
{
  // vec3_t operator '*'
  {
    vec3_t v;
    v = real_t(5.0) * vec3_t{50.0_r, 40.0_r, 25.0_r};
    CHECK(vec_equal(v, vec3_t(250.0_r, 200.0_r, 125.0)));
  }

  // vec3_t operator '*='
  {
    vec3_t v = vec3_t{50.0_r, 40.0_r, 25.0_r};
    v *= real_t(5.0);
    CHECK(vec_equal(v, vec3_t(250.0_r, 200.0_r, 125.0)));
  }
}

TEST_CASE("multiplication_vector", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '*'
  {
    vec5_t v;
    v = vec5_t{2.0_r, 3.0_r, 4.0_r, 5.0_r, 0.5_r}
      * vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};

    CHECK(vec_equal(v, vec5_t(100.0_r, 120.0_r, 100.0_r, 100.0_r, 5.0_r)));
  }

  // vec_t operator '*='
  {
    vec5_t vec1 = vec5_t{2.0_r, 3.0_r, 4.0_r, 5.0_r, 0.5_r};
    vec5_t v2 = vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    vec1 *= v2;
    CHECK(vec_equal(vec1, vec5_t(100.0_r, 120.0_r, 100.0_r, 100.0_r, 5.0_r)));
  }
}

TEST_CASE("multiplication_vector_vec3", "[as_vec]")
{
  // vec_t operator '*'
  {
    vec3_t v;
    v = vec3_t{0.5_r, 3.0_r, 4.0_r} * vec3_t{50.0_r, 40.0_r, 25.0_r};
    CHECK(vec_equal(v, vec3_t(25.0_r, 120.0_r, 100.0_r)));
  }

  // vec_t operator '*='
  {
    vec3_t vec1 = vec3_t{0.5_r, 3.0_r, 4.0_r};
    vec3_t v2 = vec3_t{50.0_r, 40.0_r, 25.0_r};
    vec1 *= v2;
    CHECK(vec_equal(vec1, vec3_t(25.0_r, 120.0_r, 100.0_r)));
  }
}

TEST_CASE("divide_scalar", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '/'
  {
    vec5_t v;
    v = vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r} / real_t(5.0);
    CHECK(vec_equal(v, vec5_t(10.0_r, 8.0_r, 5.0_r, 4.0_r, 2.0_r)));
  }

  // vec_t operator '/='
  {
    vec5_t v = vec5_t{50.0_r, 40.0_r, 25.0_r, 20.0_r, 10.0_r};
    v /= real_t(5.0_r);
    CHECK(vec_equal(v, vec5_t(10.0_r, 8.0_r, 5.0_r, 4.0_r, 2.0_r)));
  }
}

TEST_CASE("divide_scalar_vec3", "[as_vec]")
{
  // vec_t operator '/'
  {
    vec3_t v;
    v = vec3_t{50.0_r, 40.0_r, 25.0_r} / real_t(5.0);
    CHECK(vec_equal(v, vec3_t(10.0_r, 8.0_r, 5.0_r)));
  }

  // vec_t operator '/='
  {
    vec3_t v = vec3_t{50.0_r, 40.0_r, 25.0_r};
    v /= real_t(5.0);
    CHECK(vec_equal(v, vec3_t(10.0_r, 8.0_r, 5.0_r)));
  }
}

TEST_CASE("divide_vector", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // vec_t operator '/'
  {
    vec5_t v;
    v = vec5_t{33.0_r, 48.0_r, 10.0_r, 120.0_r, 2.0_r}
      / vec5_t{3.0_r, 6.0_r, 2.0_r, 3.0_r, 0.5_r};

    CHECK(vec_equal(v, vec5_t(11.0_r, 8.0_r, 5.0_r, 40.0_r, 4.0_r)));
  }

  // vec_t operator '/='
  {
    vec5_t vec1 = vec5_t{33.0_r, 48.0_r, 10.0_r, 120.0_r, 2.0_r};
    vec5_t v2 = vec5_t{3.0_r, 6.0_r, 2.0_r, 3.0_r, 0.5_r};
    vec1 /= v2;
    CHECK(vec_equal(vec1, vec5_t(11.0_r, 8.0_r, 5.0_r, 40.0_r, 4.0_r)));
  }
}

TEST_CASE("divide_vector_vec3", "[as_vec]")
{
  // vec_t operator '/'
  {
    vec3_t v;
    v = vec3_t{33.0_r, 48.0_r, 10.0_r} / vec3_t{3.0_r, 6.0_r, 2.0_r};
    CHECK(vec_equal(v, vec3_t(11.0_r, 8.0_r, 5.0_r)));
  }

  // vec_t operator '/='
  {
    vec3_t vec1 = vec3_t{33.0_r, 48.0_r, 10.0_r};
    vec3_t v2 = vec3_t{3.0_r, 6.0_r, 2.0_r};
    vec1 /= v2;
    CHECK(vec_equal(vec1, vec3_t(11.0_r, 8.0_r, 5.0_r)));
  }
}

TEST_CASE("dot", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  // note: comparison values calculated using - http://calculator.vhex.net
  {
    const vec5_t vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r);
    const vec5_t v2(4.0_r, 5.0_r, 6.0_r, 8.0_r, 4.0_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(84.0_r).epsilon(g_epsilon));
  }

  {
    const vec5_t vec1(-50.0_r, 20.0_r, 9.0_r, 11.0_r, 3.0_r);
    const vec5_t v2(-1.0_r, -7.0_r, 4.0_r, 2.0_r, 0.5_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(-30.5).epsilon(g_epsilon));
  }

  {
    const vec5_t vec1(-2.3_r, 0.1_r, 0.92_r, 0.123_r, 0.543_r);
    const vec5_t v2(-1.456_r, -7.732_r, 2.491_r, -1.321_r, -0.261_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(4.563114_r).epsilon(g_epsilon));
  }
}

TEST_CASE("dot_vec3", "[as_vec]")
{
  // note: comparison values calculated using - http://calculator.vhex.net
  {
    const vec3_t vec1(1.0_r, 2.0_r, 3.0_r);
    const vec3_t v2(4.0_r, 5.0_r, 6.0_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(32.0_r).epsilon(g_epsilon));
  }

  {
    const vec3_t vec1(-50.0_r, 20.0_r, 9.0_r);
    const vec3_t v2(-1.0_r, -7.0_r, 4.0_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(-54.0_r).epsilon(g_epsilon));
  }

  {
    const vec3_t vec1(-2.3_r, 0.1_r, 0.92_r);
    const vec3_t v2(-1.456_r, -7.732_r, 2.491_r);

    const real_t dot_result = vec_dot(vec1, v2);
    CHECK(dot_result == Approx(4.86732_r).epsilon(g_epsilon));
  }
}

TEST_CASE("axes_vec2", "[as_vec]")
{
  using gsl::make_span;

  constexpr real_t x_axis[] = {1.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), make_elements_sub(vec2_t::axis_x(), 2));

  constexpr real_t y_axis[] = {0.0_r, 1.0_r};
  CHECK_THAT(make_span(y_axis), make_elements_sub(vec2_t::axis_y(), 2));

  constexpr real_t zero[] = {0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), make_elements_sub(vec2_t::zero(), 2));

  constexpr real_t one[] = {1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), make_elements_sub(vec2_t::one(), 2));

  constexpr real_t max_val = std::numeric_limits<real_t>::max();
  constexpr real_t max_val_vec[] = {max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), make_elements_sub(vec2_t::max(), 2));

  constexpr real_t min_val = std::numeric_limits<real_t>::min();
  constexpr real_t min_val_vec[] = {min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), make_elements_sub(vec2_t::min(), 2));

  constexpr real_t lowest_val = std::numeric_limits<real_t>::lowest();
  constexpr real_t lowest_val_vec[] = {lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), make_elements_sub(vec2_t::lowest(), 2));
}

TEST_CASE("axes_vec3", "[as_vec]")
{
  using gsl::make_span;

  constexpr real_t x_axis[] = {1.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), make_elements_sub(vec3_t::axis_x(), 3));

  constexpr real_t y_axis[] = {0.0_r, 1.0_r, 0.0_r};
  CHECK_THAT(make_span(y_axis), make_elements_sub(vec3_t::axis_y(), 3));

  constexpr real_t z_axis[] = {0.0_r, 0.0_r, 1.0_r};
  CHECK_THAT(make_span(z_axis), make_elements_sub(vec3_t::axis_z(), 3));

  constexpr real_t zero[] = {0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), make_elements_sub(vec3_t::zero(), 3));

  constexpr real_t one[] = {1.0_r, 1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), make_elements_sub(vec3_t::one(), 3));

  constexpr real_t max_val = std::numeric_limits<real_t>::max();
  constexpr real_t max_val_vec[] = {max_val, max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), make_elements_sub(vec3_t::max(), 3));

  constexpr real_t min_val = std::numeric_limits<real_t>::min();
  constexpr real_t min_val_vec[] = {min_val, min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), make_elements_sub(vec3_t::min(), 3));

  constexpr real_t lowest_val = std::numeric_limits<real_t>::lowest();
  constexpr real_t lowest_val_vec[] = {lowest_val, lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), make_elements_sub(vec3_t::lowest(), 3));
}

TEST_CASE("axes_vec4", "[as_vec]")
{
  using gsl::make_span;

  constexpr real_t x_axis[] = {1.0_r, 0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(x_axis), make_elements_sub(vec4_t::axis_x(), 4));

  constexpr real_t y_axis[] = {0.0_r, 1.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(y_axis), make_elements_sub(vec4_t::axis_y(), 4));

  constexpr real_t z_axis[] = {0.0_r, 0.0_r, 1.0_r, 0.0_r};
  CHECK_THAT(make_span(z_axis), make_elements_sub(vec4_t::axis_z(), 4));

  constexpr real_t w_axis[] = {0.0_r, 0.0_r, 0.0_r, 1.0_r};
  CHECK_THAT(make_span(w_axis), make_elements_sub(vec4_t::axis_w(), 4));

  constexpr real_t zero[] = {0.0_r, 0.0_r, 0.0_r, 0.0_r};
  CHECK_THAT(make_span(zero), make_elements_sub(vec4_t::zero(), 4));

  constexpr real_t one[] = {1.0_r, 1.0_r, 1.0_r, 1.0_r};
  CHECK_THAT(make_span(one), make_elements_sub(vec4_t::one(), 4));

  constexpr real_t max_val = std::numeric_limits<real_t>::max();
  constexpr real_t max_val_vec[] = {max_val, max_val, max_val, max_val};
  CHECK_THAT(make_span(max_val_vec), make_elements_sub(vec4_t::max(), 4));

  constexpr real_t min_val = std::numeric_limits<real_t>::min();
  constexpr real_t min_val_vec[] = {min_val, min_val, min_val, min_val};
  CHECK_THAT(make_span(min_val_vec), make_elements_sub(vec4_t::min(), 4));

  constexpr real_t lowest_val = std::numeric_limits<real_t>::lowest();
  constexpr real_t lowest_val_vec[] = {
    lowest_val, lowest_val, lowest_val, lowest_val};
  CHECK_THAT(make_span(lowest_val_vec), make_elements_sub(vec4_t::lowest(), 4));
}

TEST_CASE("cross", "[as_vec]")
{
  // note: comparison values calculated using
  // https://www.symbolab.com/solver/vector-cross-product-calculator
  {
    vec3_t vec1(1.0_r, 2.0_r, 3.0_r);
    vec3_t v2(4.0_r, 5.0_r, 6.0_r);

    vec3_t cross_result = vec3_cross(vec1, v2);
    CHECK(cross_result.x == Approx(-3.0_r).epsilon(g_epsilon));
    CHECK(cross_result.y == Approx(6.0_r).epsilon(g_epsilon));
    CHECK(cross_result.z == Approx(-3.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t vec1(1.0_r, 0.0_r, 0.0_r);
    vec3_t v2(0.0_r, 1.0_r, 0.0_r);

    vec3_t cross_result1 = vec3_cross(vec1, v2);
    CHECK(cross_result1.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result1.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result1.z == Approx(1.0_r).epsilon(g_epsilon));

    vec3_t cross_result2 = vec3_cross(v2, vec1);
    CHECK(cross_result2.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result2.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result2.z == Approx(-1.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t vec1(0.0_r, 5.0_r, 0.0_r);
    vec3_t v2(0.0_r, 0.0_r, 12.0_r);

    vec3_t cross_result = vec3_cross(vec1, v2);
    CHECK(cross_result.x == Approx(60.0_r).epsilon(g_epsilon));
    CHECK(cross_result.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(cross_result.z == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t x(1.0_r, 0.0_r, 0.0_r);
    vec3_t y(0.0_r, 1.0_r, 0.0_r);
    vec3_t z(0.0_r, 0.0_r, 1.0_r);

    vec3_t cross_result1 = vec3_cross(x, y);
    CHECK(cross_result1.z == Approx(1.0_r).epsilon(g_epsilon));

    vec3_t cross_result2 = vec3_cross(y, z);
    CHECK(cross_result2.x == Approx(1.0_r).epsilon(g_epsilon));

    vec3_t cross_result3 = vec3_cross(z, x);
    CHECK(cross_result3.y == Approx(1.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("right_and_up", "[as_vec]")
{
  {
    vec3_t dir(0.0_r, 0.0_r, 1.0_r);

    vec3_t across_lh;
    vec3_t up_lh;
    vec3_right_and_up_lh(dir, across_lh, up_lh);

    CHECK(across_lh.x == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(across_lh.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(across_lh.z == Approx(0.0_r).epsilon(g_epsilon));

    CHECK(up_lh.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(up_lh.y == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(up_lh.z == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t dir(0.0_r, 0.0_r, 1.0_r);

    vec3_t across_rh;
    vec3_t up_rh;
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
    vec3_t vec1(1.11_r, 0.3_r, 517.2_r);
    vec3_t v2(1.11_r, 0.3_r, 517.2_r);

    CHECK(vec_equal(vec1, v2));
  }

  {
    vec3_t vec1(1.11_r, 0.3_r, 514.2_r);
    vec3_t v2(1.114_r, 0.3_r, 517.2_r);

    CHECK_FALSE(vec_equal(vec1, v2));
  }

  {
    vec3_t vec1(1.11_r, 0.3_r, 514.2_r);
    vec3_t v2(1.11_r, 0.311_r, 514.2_r);

    CHECK_FALSE(vec_equal(vec1, v2));
  }
}

TEST_CASE("abs", "[as_vec]")
{
  {
    vec4_t v(-1.0_r, -2.0_r, -100.0_r, -7.0_r);
    vec4_t result = vec_abs(v);

    vec4_t vec_reference = {1.0_r, 2.0_r, 100.0_r, 7.0_r};

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4_t v{1.0_r, 4.0_r, 6.0_r, 50.0_r};
    vec4_t result = vec_abs(v);

    vec4_t vec_reference = {1.0_r, 4.0_r, 6.0_r, 50.0_r};

    CHECK(vec_equal(vec_reference, result));
  }

  {
    using vec5_t = vec_t<real_t, 5>;

    vec5_t vec5{-1.0_r, -2.0_r, -100.0_r, -7.0_r, -4.0_r};
    vec5_t result = vec_abs(vec5);

    vec5_t vec_reference = {1.0_r, 2.0_r, 100.0_r, 7.0_r, 4.0_r};

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("min_vec", "[as_vec]")
{
  {
    vec4_t vec1(-1.0_r, 2.0_r, -100.0_r, -7.0_r);
    vec4_t v2(-10.0_r, 7.0_r, -50.0_r, -16.0_r);

    vec4_t vec_reference(-10.0_r, 2.0_r, -100.0_r, -16.0_r);

    vec4_t result = vec_min(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4_t vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    vec4_t v2(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4_t vec_reference(1.0_r, 2.0_r, 3.0_r, 4.0_r);

    vec4_t result = vec_min(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("min_elem", "[as_vec]")
{
  {
    vec3_t v{-1.0_r, 2.0_r, -100.0_r};
    real_t result = vec_min_elem(v);

    CHECK(result == Approx(-100.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t v{1.0_r, 2.0_r, 3.0_r};
    real_t result = vec_min_elem(v);

    CHECK(result == Approx(1.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("max_vec", "[as_vec]")
{
  {
    vec4_t vec1(-1.0_r, 2.0_r, -100.0_r, -7.0_r);
    vec4_t v2(-10.0_r, 7.0_r, -50.0_r, -16.0_r);

    vec4_t vec_reference(-1.0_r, 7.0_r, -50.0_r, -7.0_r);

    vec4_t result = vec_max(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }

  {
    vec4_t vec1(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    vec4_t v2(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4_t vec_reference(2.0_r, 3.0_r, 4.0_r, 5.0_r);

    vec4_t result = vec_max(vec1, v2);

    CHECK(vec_equal(vec_reference, result));
  }
}

TEST_CASE("max_elem", "[as_vec]")
{
  {
    vec3_t v{-1.0_r, 2.0_r, -100.0_r};
    real_t result = vec_max_elem(v);

    CHECK(result == Approx(2.0_r).epsilon(g_epsilon));
  }

  {
    vec3_t v{1.0_r, 2.0_r, 3.0_r};
    real_t result = vec_max_elem(v);

    CHECK(result == Approx(3.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("clamp", "[as_vec]")
{
  {
    vec3_t min_val(50.0_r, 50.0_r, 50.0_r);
    vec3_t max_val(100.0_r, 100.0_r, 100.0_r);

    vec3_t v(20.0_r, 20.0_r, 20.0_r);

    vec3_t result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, min_val));
  }

  {
    vec3_t min_val(50.0_r, 50.0_r, 50.0_r);
    vec3_t max_val(100.0_r, 100.0_r, 100.0_r);

    vec3_t v(120.0_r, 200.0_r, 300.0_r);

    vec3_t result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, max_val));
  }

  {
    vec3_t min_val(50.0_r, 50.0_r, 50.0_r);
    vec3_t max_val(100.0_r, 100.0_r, 100.0_r);

    vec3_t v(20.0_r, 120.0_r, 20.0_r);
    vec3_t vec_reference(50.0_r, 100.0_r, 50.0_r);

    vec3_t result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, vec_reference));
  }

  {
    vec3_t min_val(50.0_r, 50.0_r, 50.0_r);
    vec3_t max_val(100.0_r, 100.0_r, 100.0_r);

    vec3_t v(62.0_r, 56.0_r, 72.0_r);

    vec3_t result = vec_clamp(v, min_val, max_val);

    CHECK(vec_equal(result, v));
  }
}

TEST_CASE("saturate", "[as_vec]")
{
  {
    vec3_t v(-2.0_r, 0.5_r, 1.2_r);
    vec3_t result = vec_saturate(v);

    vec3_t vec_reference(0.0_r, 0.5_r, 1.0_r);

    CHECK(vec_equal(result, vec_reference));
  }

  {
    vec3_t v(3.0_r, 0.1_r, -1.2_r);
    vec3_t result = vec_saturate(v);

    vec3_t vec_reference(1.0_r, 0.1_r, 0.0_r);

    CHECK(vec_equal(result, vec_reference));
  }
}

TEST_CASE("lerp", "[as_vec]")
{
  {
    using gsl::make_span;

    vec3_t start(0.0_r, 10.0_r, 20.0_r);
    vec3_t end(10.0_r, 40.0_r, 100.0_r);

    vec3_t result_begin = vec_lerp(real_t(0.0), start, end);
    vec3_t result_mid = vec_lerp(real_t(0.5), start, end);
    vec3_t result_end = vec_lerp(real_t(1.0), start, end);

    const real_t result_begin_arr[] = {0.0_r, 10.0_r, 20.0_r};
    CHECK_THAT(make_span(result_begin_arr), make_elements_sub(result_begin, 3));

    const real_t result_mid_arr[] = {5.0_r, 25.0_r, 60.0_r};
    CHECK_THAT(make_span(result_mid_arr), make_elements_sub(result_mid, 3));

    const real_t result_end_arr[] = {10.0_r, 40.0_r, 100.0_r};
    CHECK_THAT(make_span(result_end_arr), make_elements_sub(result_end, 3));
  }
}

TEST_CASE("normalize_and_length", "[as_vec]")
{
  const vec3_t v(3.0_r, 4.0_r, 0.0_r);
  const auto [vec_normalized, length] = vec_normalize_and_length(v);

  CHECK(length == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(vec_length(vec_normalized) == Approx(1.0_r).epsilon(g_epsilon));
}

TEST_CASE("length_squared_v3", "[as_vec]")
{
  const vec3_t v(3.0_r, 4.0_r, 0.0_r);
  const real_t length_sq = vec_length_sq(v);

  CHECK(length_sq == Approx(25.0_r).epsilon(g_epsilon));
}

TEST_CASE("length_squared_generic", "[as_vec]")
{
  using vec5_t = vec_t<real_t, 5>;

  const vec5_t v(3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r);
  const real_t length_sq = vec_length_sq(v);

  CHECK(length_sq == Approx(135.0_r).epsilon(g_epsilon));
}

TEST_CASE("select", "[as_vec]")
{
  using int3 = vec_t<int, 3>;

  int3 a(1, 2, 3);
  int3 b(5, 6, 7);

  using byte4 = vec_t<uint8_t, 4>;

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
    const vec2_t vec1(2.0_r, 0.0_r);
    const vec2_t v2(0.0_r, 2.0_r);
    const real_t result = vec2_wedge(vec1, v2);

    CHECK(result == Approx(4.0_r).epsilon(g_epsilon));
  }

  {
    const vec2_t vec1(10.0_r, 10.0_r);
    const vec2_t v2(20.0_r, 5.0_r);
    const real_t result = vec2_wedge(vec1, v2);

    CHECK(result == Approx(-150.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("vec_to_arr", "[as_vec]")
{
  using gsl::make_span;

  vec_t<real_t, 5> vec5{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r};

  real_t vec5_arr[5];
  vec_to_arr(vec5, vec5_arr);

  CHECK_THAT(make_span(vec5_arr), make_elements_sub(vec5, 5));
}

TEST_CASE("floor", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3_t v(1.8_r, 2.2_r, 3.5_r);
    const vec3_t floor_vec = vec_floor(v);

    real_t floor_expected[] = {1.0_r, 2.0_r, 3.0_r};

    CHECK_THAT(make_span(floor_expected), make_elements_sub(floor_vec, 3));
  }

  {
    const vec4_t v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4_t floor_vec = vec_floor(v);

    real_t floor_expected[] = {-2.0_r, -3.0_r, -4.0_r, -5.0_r};

    CHECK_THAT(make_span(floor_expected), make_elements_sub(floor_vec, 4));
  }
}

TEST_CASE("ceil", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3_t v(1.8_r, 2.2_r, 3.5_r);
    const vec3_t ceil_vec = vec_ceil(v);

    real_t ceil_expected[] = {2.0_r, 3.0_r, 4.0_r};

    CHECK_THAT(make_span(ceil_expected), make_elements_sub(ceil_vec, 3));
  }

  {
    const vec4_t v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4_t ceil_vec = vec_ceil(v);

    real_t ceil_expected[] = {-1.0_r, -2.0_r, -3.0_r, -4.0_r};

    CHECK_THAT(make_span(ceil_expected), make_elements_sub(ceil_vec, 4));
  }
}

TEST_CASE("round", "[as_vec]")
{
  using gsl::make_span;

  {
    const vec3_t v(1.8_r, 2.2_r, 3.5_r);
    const vec3_t round_vec = vec_round(v);

    real_t round_expected[] = {2.0_r, 2.0_r, 4.0_r};

    CHECK_THAT(make_span(round_expected), make_elements_sub(round_vec, 3));
  }

  {
    const vec4_t v(-1.3_r, -2.6_r, -3.9_r, -4.1_r);
    const vec4_t round_vec = vec_round(v);

    real_t round_expected[] = {-1.0_r, -3.0_r, -4.0_r, -4.0_r};

    CHECK_THAT(make_span(round_expected), make_elements_sub(round_vec, 4));
  }
}

TEST_CASE("point3_to_vec4", "[as_vec]")
{
  point3_t p3{2.0_r, 4.0_r, 6.0_r};

  vec4_t actual_vec4;
  actual_vec4 = vec4_from_point3(p3);

  CHECK_THAT(
    arr(2.0_r, 4.0_r, 6.0_r, 1.0_r), make_elements_sub(actual_vec4, 4));
}

TEST_CASE("snap_vec", "[as_vec]")
{
  {
    vec2_t v2{70.0_r, 95.0};
    vec2_t result = as::vec_snap(v2, 30.0_r);

    CHECK_THAT(arr(60.0_r, 90.0_r), make_elements_sub(result, 2));
  }

  {
    vec3_t v3{1.0_r, 2.0_r, 3.0_r};
    vec3_t result = as::vec_snap(v3, 0.5_r);

    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(result, 3));
  }

  {
    using vec5_t = vec_t<real_t, 5>;

    vec5_t vec5{5.0_r, 12.0_r, 18.0_r, 22.0_r, 1000.0_r};
    vec5_t result = as::vec_snap(vec5, 5.0_r);

    const auto expected =
      std::array<real_t, 5>{5.0_r, 10.0_r, 20.0_r, 20.0_r, 1000.0_r};

    CHECK_THAT(expected, make_elements_sub(result, 5));
  }
}

TEST_CASE("orthonomal_basis", "[as_vec]")
{
  {
    const mat3_t basis = orthonormal_basis(vec3_t(1.0_r, 0.0_r, 0.0_r));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), make_elements_sub(as::mat3_basis_x(basis), 3));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), make_elements_sub(as::mat3_basis_y(basis), 3));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), make_elements_sub(as::mat3_basis_z(basis), 3));
  }

  {
    const mat3_t basis = orthonormal_basis(vec3_t(0.0_r, -1.0_r, 0.0_r));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), make_elements_sub(as::mat3_basis_x(basis), 3));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, -1.0_r), make_elements_sub(as::mat3_basis_y(basis), 3));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), make_elements_sub(as::mat3_basis_z(basis), 3));
  }

  {
    const mat3_t basis = orthonormal_basis(vec3_t(0.0_r, 1.0_r, 0.0_r));
    CHECK_THAT(
      arr(0.0_r, 1.0_r, 0.0_r), make_elements_sub(as::mat3_basis_x(basis), 3));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), make_elements_sub(as::mat3_basis_y(basis), 3));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), make_elements_sub(as::mat3_basis_z(basis), 3));
  }

  {
    const mat3_t basis = orthonormal_basis(vec3_t(0.0_r, 0.0_r, 1.0_r));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), make_elements_sub(as::mat3_basis_x(basis), 3));
    CHECK_THAT(
      arr(0.0_r, -1.0_r, 0.0_r), make_elements_sub(as::mat3_basis_y(basis), 3));
    CHECK_THAT(
      arr(1.0_r, 0.0_r, 0.0_r), make_elements_sub(as::mat3_basis_z(basis), 3));
  }

  {
    const mat3_t basis =
      orthonormal_basis(vec_normalize(vec3_t(1.0_r, 1.0_r, 0.0_r)));
    CHECK_THAT(
      arr(0.707107_r, 0.707107_r, 0.000000_r),
      make_elements_sub(as::mat3_basis_x(basis), 3).epsilon(0.001_r));
    CHECK_THAT(
      arr(-0.707107_r, 0.707107_r, 0.000000_r),
      make_elements_sub(as::mat3_basis_y(basis), 3).epsilon(0.001_r));
    CHECK_THAT(
      arr(0.0_r, 0.0_r, 1.0_r), make_elements_sub(as::mat3_basis_z(basis), 3));
  }
}

} // namespace unit_test

// explicit instantiations (for coverage)

// types
template struct as::vec_t<as::real_t, 2>;
template struct as::vec_t<as::real_t, 3>;
template struct as::vec_t<as::real_t, 4>;
template struct as::vec_t<as::real_t, 5>;

#ifdef __GNUC__
// constructor
template as::vec_t<as::real_t, 5>::vec_t(
  as::real_t, as::real_t, as::real_t, as::real_t, as::real_t) noexcept;
#endif // __GNUC__

// operators
template const as::vec_t<as::real_t, 5> as::operator+(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator-(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator-(
  const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator*(
  const as::vec_t<as::real_t, 5>&, as::real_t);
template const as::vec_t<as::real_t, 5> as::operator*(
  as::real_t, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator*(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator/(
  const as::vec_t<as::real_t, 5>&, as::real_t);
template const as::vec_t<as::real_t, 5> as::operator/(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);

// functions
template void as::vec_to_arr(
  const as::vec_t<as::real_t, 5>& v, as::real_t (&data)[5]);
template as::index_t as::vec_size<as::real_t, 5>(
  const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec_dot(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template std::tuple<as::vec_t<as::real_t, 5>, as::real_t> as::
  vec_normalize_and_length(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_min(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec_min_elem(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_max(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec_max_elem(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_abs(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_clamp(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&,
  const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_saturate(
  const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_lerp(
  as::real_t t, const as::vec_t<as::real_t, 5>&,
  const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec_select(
  const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&, bool);
