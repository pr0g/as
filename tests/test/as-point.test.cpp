#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::point2;
using as::point3;
using as::real;
using as::vec2;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

// use float epsilon for comparisons
const real g_epsilon = real(std::numeric_limits<float>::epsilon());

TEST_CASE("point2_initialization", "[as_point]")
{
  {
    point2 p2;
    p2 = point2{2.0_r, 4.0_r};

    CHECK(p2[0] == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(p2[1] == Approx(4.0_r).epsilon(g_epsilon));
  }

  {
    point2 p2;
    p2 = point2{5.0_r};

    CHECK(p2[0] == Approx(5.0_r).epsilon(g_epsilon));
    CHECK(p2[1] == Approx(5.0_r).epsilon(g_epsilon));
  }

  {
    vec2 v2 = vec2{10.0_r, 20.0_r};

    point2 p2;
    p2 = point2{v2};

    CHECK(p2[0] == Approx(10.0_r).epsilon(g_epsilon));
    CHECK(p2[1] == Approx(20.0_r).epsilon(g_epsilon));
  }

  {
    auto make_point = []() { return point2{1.0_r, 2.0_r}; };

    CHECK(make_point()[0] == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(make_point()[1] == Approx(2.0_r).epsilon(g_epsilon));
  }

  {
    const point2 p2 = point2{20.0_r, 40.0_r};

    const real& x = p2[0];
    const real& y = p2[1];

    CHECK(x == Approx(20.0_r).epsilon(g_epsilon));
    CHECK(y == Approx(40.0_r).epsilon(g_epsilon));
  }

  {
    point2 p2;
    p2 = point2::zero();

    CHECK(p2.as_vec().x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(p2.as_vec().y == Approx(0.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("point3_initialization", "[as_point]")
{
  {
    point3 p3;
    p3 = point3{2.0_r, 4.0_r, 6.0_r};

    CHECK(p3[0] == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(p3[1] == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(p3[2] == Approx(6.0_r).epsilon(g_epsilon));
  }

  {
    point3 p3;
    p3 = point3{5.0_r};

    CHECK(p3[0] == Approx(5.0_r).epsilon(g_epsilon));
    CHECK(p3[1] == Approx(5.0_r).epsilon(g_epsilon));
    CHECK(p3[2] == Approx(5.0_r).epsilon(g_epsilon));
  }

  {
    vec3 v3 = vec3{10.0_r, 20.0_r, 30.0_r};

    point3 p3;
    p3 = point3{v3};

    CHECK(p3[0] == Approx(10.0_r).epsilon(g_epsilon));
    CHECK(p3[1] == Approx(20.0_r).epsilon(g_epsilon));
    CHECK(p3[2] == Approx(30.0_r).epsilon(g_epsilon));
  }

  {
    vec2 v2 = vec2{10.0_r, 20.0_r};
    real real = 30.0_r;

    point3 p3;
    p3 = point3{v2, real};

    CHECK(p3[0] == Approx(10.0_r).epsilon(g_epsilon));
    CHECK(p3[1] == Approx(20.0_r).epsilon(g_epsilon));
    CHECK(p3[2] == Approx(30.0_r).epsilon(g_epsilon));
  }

  {
    auto make_point = [] { return point3{1.0_r, 2.0_r, 3.0_r}; };

    CHECK(make_point()[0] == Approx(1.0_r).epsilon(g_epsilon));
    CHECK(make_point()[1] == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(make_point()[2] == Approx(3.0_r).epsilon(g_epsilon));
  }

  {
    const point3 p3 = point3{20.0_r, 40.0_r, 60.0_r};

    const real& x = p3[0];
    const real& y = p3[1];
    const real& z = p3[2];

    CHECK(x == Approx(20.0_r).epsilon(g_epsilon));
    CHECK(y == Approx(40.0_r).epsilon(g_epsilon));
    CHECK(z == Approx(60.0_r).epsilon(g_epsilon));
  }

  {
    point3 p3;
    p3 = point3::zero();

    CHECK(p3.as_vec().x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(p3.as_vec().y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(p3.as_vec().z == Approx(0.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("point_sizes", "[as_point]")
{
  CHECK(point2::size() == 2);
  CHECK(point3::size() == 3);
}

TEST_CASE("point2_equals", "[as_point]")
{
  {
    const point2 point2_a = point2{12.0_r, 14.0_r};
    const point2 point2_b = point2{12.0_r, 14.0_r};

    CHECK(point_equal(point2_a, point2_b));
  }

  {
    const point2 point2_a = point2{5.0_r, 6.0_r};
    const point2 point2_b = point2{4.9_r, 6.1_r};

    CHECK(!point_equal(point2_a, point2_b));
  }
}

TEST_CASE("point3_equals", "[as_point]")
{
  {
    const point3 point3_a = point3{20.0_r, 40.0_r, 60.0_r};
    const point3 point3_b = point3{20.0_r, 40.0_r, 60.0_r};

    CHECK(point_equal(point3_a, point3_b));
  }

  {
    const point3 point3_a = point3{20.0_r, 40.0_r, 60.0_r};
    const point3 point3_b = point3{19.0_r, 40.0_r, 60.0_r};

    CHECK(!point_equal(point3_a, point3_b));
  }
}

TEST_CASE("point2_addition", "[as_point]")
{
  using gsl::make_span;

  const point2 p2 = point2{18.0_r, 22.0_r};
  const vec2 v2 = vec2{32.0_r, 28.0_r};

  const point2 result = p2 + v2;

  const real result_ref_arr[] = {50.0_r, 50.0_r};
  CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));

  point2 result_mut = {};
  result_mut += vec2{1.0_r, 2.0_r};

  const real result_ref_arr_mut[] = {1.0_r, 2.0_r};
  CHECK_THAT(make_span(result_ref_arr_mut), make_elements_sub(result_mut, 2));
}

TEST_CASE("point3_addition", "[as_point]")
{
  using gsl::make_span;

  const point3 p3 = point3{20.0_r, 40.0_r, 60.0_r};
  const vec3 v3 = vec3{80.0_r, 60.0_r, 40.0_r};

  const point3 result = p3 + v3;

  const real result_ref_arr[] = {100.0_r, 100.0_r, 100.0_r};
  CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));

  point3 result_mut = {};
  result_mut += vec3{1.0_r, 2.0_r, 3.0_r};

  const real result_ref_arr_mut[] = {1.0_r, 2.0_r, 3.0_r};
  CHECK_THAT(make_span(result_ref_arr_mut), make_elements_sub(result_mut, 3));
}

TEST_CASE("point2_substraction", "[as_point]")
{
  using gsl::make_span;

  {
    const point2 point2_a = point2{18.0_r, 22.0_r};
    const point2 point2_b = point2{32.0_r, 28.0_r};

    const vec2 result = point2_b - point2_a;

    const real result_ref_arr[] = {14.0_r, 6.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));
  }

  {
    const point2 p2 = point2{18.0_r, 22.0_r};
    const vec2 v2 = vec2{32.0_r, 28.0_r};

    const point2 result = p2 - v2;

    const real result_ref_arr[] = {-14.0_r, -6.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));
  }

  {
    const point2 p2 = point2{18.0_r, 22.0_r};
    const vec2 v2 = vec2{32.0_r, 28.0_r};

    point2 result_mut = p2;
    result_mut -= v2;

    const real result_ref_arr[] = {-14.0_r, -6.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result_mut, 2));
  }
}

TEST_CASE("point3_substraction", "[as_point]")
{
  using gsl::make_span;

  {
    const point3 point3_a = point3{20.0_r, 40.0_r, 60.0_r};
    const point3 point3_b = point3{80.0_r, 60.0_r, 40.0_r};

    const vec3 result = point3_b - point3_a;

    const real result_ref_arr[] = {60.0_r, 20.0_r, -20.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));
  }

  {
    const point3 p3 = point3{80.0_r, 60.0_r, 40.0_r};
    const vec3 v3 = vec3{20.0_r, 40.0_r, 60.0_r};

    const point3 result = p3 - v3;

    const real result_ref_arr[] = {60.0_r, 20.0_r, -20.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));
  }

  {
    const point3 p3 = point3{80.0_r, 60.0_r, 40.0_r};
    const vec3 v3 = vec3{20.0_r, 40.0_r, 60.0_r};

    point3 result_mut = p3;
    result_mut -= v3;

    const real result_ref_arr[] = {60.0_r, 20.0_r, -20.0_r};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result_mut, 3));
  }
}

TEST_CASE("point_axes", "[as_point]")
{
  CHECK_THAT(arr(2.0_r, 0.0_r), make_elements_sub(point2::axis_x(2.0_r), 2));
  CHECK_THAT(arr(0.0_r, 5.0_r), make_elements_sub(point2::axis_y(5.0_r), 2));

  CHECK_THAT(
    arr(2.0_r, 0.0_r, 0.0_r), make_elements_sub(point3::axis_x(2.0_r), 3));
  CHECK_THAT(
    arr(0.0_r, 5.0_r, 0.0_r), make_elements_sub(point3::axis_y(5.0_r), 3));
  CHECK_THAT(
    arr(0.0_r, 0.0_r, 10.0_r), make_elements_sub(point3::axis_z(10.0_r), 3));
}

TEST_CASE("point_negate", "[as_point]")
{
  {
    point2 before1{1.0_r, 2.0_r};
    CHECK_THAT(arr(-1.0_r, -2.0_r), make_elements_sub(-before1, 2));

    point2 before2{-3.0_r, -4.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r), make_elements_sub(-before2, 2));
  }

  {
    point3 before1{1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(arr(-1.0_r, -2.0_r, -3.0_r), make_elements_sub(-before1, 3));

    point3 before2{-3.0_r, -4.0_r, -5.0_r};
    CHECK_THAT(arr(3.0_r, 4.0_r, 5.0_r), make_elements_sub(-before2, 3));
  }
}

TEST_CASE("point_average", "[as_point]")
{
  {
    point2 avg = point_average_fold(point2{2.0_r, 2.0_r}, point2{4.0_r, 4.0_r});
    CHECK_THAT(arr(3.0_r, 3.0_r), make_elements_sub(avg, 2));
  }

  {
    point2 points[] = {point2{2.0_r, 2.0_r}, point2{4.0_r, 4.0_r}};
    point2 avg = point_average(points, std::size(points));
    CHECK_THAT(arr(3.0_r, 3.0_r), make_elements_sub(avg, 2));
  }

  {
    point3 avg = point_average_fold(
      point3{3.0_r, 3.0_r, 3.0_r}, point3{5.0_r, 5.0_r, 5.0_r});
    CHECK_THAT(arr(4.0_r, 4.0_r, 4.0_r), make_elements_sub(avg, 3));
  }

  {
    point3 points[] = {
      point3{3.0_r, 3.0_r, 3.0_r}, point3{5.0_r, 5.0_r, 5.0_r}};
    point3 avg = point_average(points, std::size(points));
    CHECK_THAT(arr(4.0_r, 4.0_r, 4.0_r), make_elements_sub(avg, 3));
  }
}

} // namespace unit_test
