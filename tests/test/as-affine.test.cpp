#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine;
using as::mat3;
using as::mat4;
using as::real;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

// use float epsilon for comparisons
const real g_epsilon = real(std::numeric_limits<float>::epsilon());

TEST_CASE("affine_constructor_position_rotation", "[as_affine]")
{
  affine a;
  mat3 rotation = as::mat3_rotation_x(radians(90.0_r));
  vec3 translation = vec3(0.0_r, 2.0_r, 2.0_r);
  a = affine(rotation, translation);

  CHECK(vec_equal(translation, a.translation));
  CHECK(as::mat_equal(rotation, a.rotation));
}

TEST_CASE("affine_constructor_position", "[as_affine]")
{
  affine a;
  a = affine(vec3(1.0_r, 2.0_r, 3.0_r));

  CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(a.translation));
  CHECK(as::mat_equal(mat3::identity(), a.rotation));
}

TEST_CASE("affine_transform_dir", "[as_affine]")
{
  const affine a(
    as::mat3_rotation_y(radians(90.0_r)), vec3(5.0_r, 0.0_r, 0.0_r));

  const vec3 result = as::affine_transform_dir(a, vec3{1.0_r, 0.0_r, 0.0_r});

  CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{
  {
    const affine a = affine(mat3::identity(), vec3(5.0_r, 0.0_r, 0.0_r));

    const vec3 result =
      as::affine_inv_transform_pos(a, vec3(6.0_r, 0.0_r, 0.0_r));

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const affine a =
      affine(as::mat3_rotation_z(radians(90.0_r)), vec3(0.0_r, 10.0_r, 0.0_r));

    const vec3 result =
      as::affine_inv_transform_pos(a, vec3(5.0_r, 0.0_r, 0.0_r));

    CHECK(result.x == Approx(-10.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-5.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }
}

TEST_CASE("affine_transform_pos", "[as_affine]")
{
  const affine a =
    affine(as::mat3_rotation_y(radians(90.0_r)), vec3(5.0_r, 0.0_r, 0.0_r));

  const vec3 result = as::affine_transform_pos(a, vec3(1.0_r, 0.0_r, 0.0_r));

  CHECK(result.x == Approx(5.0_r).margin(g_epsilon));
  CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{
  {
    const affine a = affine(mat3::identity(), vec3(5.0_r, 0.0_r, 0.0_r));

    const vec3 result =
      as::affine_inv_transform_dir(a, vec3{6.0_r, 0.0_r, 0.0_r});

    CHECK(result.x == Approx(6.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const affine a =
      affine(as::mat3_rotation_z(radians(90.0_r)), vec3(0.0_r, 10.0_r, 0.0_r));

    const vec3 result =
      as::affine_inv_transform_dir(a, vec3{5.0_r, 0.0_r, 0.0_r});

    const real local_epsilon = 1.0e-6_r;
    CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
    CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
  }
}

TEST_CASE("affine_to_arr", "[as_affine]")
{
  using gsl::make_span;

  affine a(
    mat3(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r, 8.0_r, 9.0_r),
    vec3(10.0_r, 20.0_r, 30.0_r));

  real expected_affine[12];
  as::affine_to_arr(a, expected_affine);

  CHECK_THAT(make_span(expected_affine, 9), elements_are_span(a.rotation));
  CHECK_THAT(
    make_span(&expected_affine[9], 3), elements_are_span(a.translation));
}

TEST_CASE("affine_from_arr", "[as_affine]")
{
  using gsl::make_span;

  real affine_arr[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r,  5.0_r,  6.0_r,
                       7.0_r, 8.0_r, 9.0_r, 10.0_r, 20.0_r, 30.0_r};

  affine a;
  a = as::affine_from_arr(affine_arr);

  CHECK_THAT(make_span(affine_arr, 9), elements_are_span(a.rotation));
  CHECK_THAT(make_span(&affine_arr[9], 3), elements_are_span(a.translation));
}

TEST_CASE("affine_from_mat3", "[as_affine]")
{
  using gsl::make_span;

  mat3 m3(
    10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r, 60.0_r, 70.0_r, 80.0_r, 90.0_r);

  affine a;
  a = as::affine_from_mat3(m3);

  CHECK(as::mat_equal(m3, a.rotation));
  CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), elements_are_array(a.translation));
}

TEST_CASE("affine_from_mat3_vec3", "[as_affine]")
{
  using gsl::make_span;

  mat3 m3(
    10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r, 60.0_r, 70.0_r, 80.0_r, 90.0_r);
  vec3 v3(99.0_r, 98.0_r, 97.0_r);

  affine a;
  a = as::affine_from_mat3_vec3(m3, v3);

  CHECK(as::mat_equal(m3, a.rotation));
  CHECK_THAT(arr(99.0_r, 98.0_r, 97.0_r), elements_are_array(a.translation));
}

TEST_CASE("affine_from_vec3", "[as_affine]")
{
  using gsl::make_span;

  vec3 v3(99.0_r, 98.0_r, 97.0_r);

  affine a;
  a = as::affine_from_vec3(v3);

  CHECK(as::mat_equal(mat3::identity(), a.rotation));
  CHECK_THAT(arr(99.0_r, 98.0_r, 97.0_r), elements_are_array(a.translation));
}

TEST_CASE("affine_concatenation", "[as_affine]")
{
  using gsl::make_span;

  mat4 mat_a = as::mat4_from_mat3_vec3(
    as::mat3_rotation_x(radians(45.0_r)), vec3::axis_x(5.0_r));

  mat4 mat_b = as::mat4_from_mat3_vec3(
    as::mat3_rotation_y(radians(90.0_r)), vec3::axis_y(10.0_r));

  mat4 mat_c = as::mat4_from_mat3_vec3(
    as::mat3_rotation_y(radians(180.0_r)), vec3::axis_z(20.0_r));

  mat4 mat_result;
  mat_result = as::mat_mul(as::mat_mul(mat_a, mat_b), mat_c);

  affine affine_a = as::affine_from_mat4(mat_a);
  affine affine_b = as::affine_from_mat4(mat_b);
  affine affine_c = as::affine_from_mat4(mat_c);

  affine affine_result;
  affine_result = as::affine_mul(as::affine_mul(affine_a, affine_b), affine_c);

  real expected_orientation[9];
  as::mat_to_arr(affine_result.rotation, expected_orientation);

  real expected_position[3];
  vec_to_arr(affine_result.translation, expected_position);

  CHECK_THAT(
    make_span(expected_orientation),
    elements_are_span(as::mat3_from_mat4(mat_result)));

  CHECK_THAT(
    make_span(expected_position),
    elements_are_span(vec3_from_vec4(as::mat4_translation(mat_result))));
}

TEST_CASE("affine_inverse", "[as_affine]")
{
  using gsl::make_span;

  const affine a(
    as::mat3_rotation_y(radians(90.0_r)), vec3(5.0_r, 10.0_r, 20.0_r));

  const affine affine_expected_inverse(
    as::mat3_rotation_y(radians(-90.0_r)), vec3(20.0_r, -10.0_r, -5.0_r));

  real expected_affine[12];
  as::affine_to_arr(affine_expected_inverse, expected_affine);

  affine result;
  result = affine_inverse(a);

  CHECK_THAT(
    make_span(expected_affine, 9), elements_are_span(result.rotation));
  CHECK_THAT(
    make_span(&expected_affine[9], 3),
    elements_are_span(result.translation).margin(0.000001_r));
}

} // namespace unit_test
