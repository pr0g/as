#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat3_t;
using as::mat4_t;
using as::point3_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// use float epsilon for comparisons
const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("affine_constructor_position_rotation", "[as_affine]")
{
  affine_t affine;
  mat3_t rotation = as::mat3_rotation_x(deg_to_rad(90.0_r));
  vec3_t translation = vec3_t(0.0_r, 2.0_r, 2.0_r);
  affine = affine_t(rotation, translation);

  CHECK(vec_equal(translation, affine.translation));
  CHECK(as::mat_equal(rotation, affine.rotation));
}

TEST_CASE("affine_constructor_position", "[as_affine]")
{
  affine_t affine;
  affine = affine_t(vec3_t(1.0_r, 2.0_r, 3.0_r));

  CHECK_THAT(
    arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(affine.translation, 3));
  CHECK(as::mat_equal(mat3_t::identity(), affine.rotation));
}

TEST_CASE("affine_transform_dir", "[as_affine]")
{
  const affine_t affine(
    as::mat3_rotation_y(deg_to_rad(90.0_r)), vec3_t(5.0_r, 0.0_r, 0.0_r));

  const vec3_t result =
    as::affine_transform_dir(affine, vec3_t{1.0_r, 0.0_r, 0.0_r});

  CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{
  {
    const affine_t affine =
      affine_t(mat3_t::identity(), vec3_t(5.0_r, 0.0_r, 0.0_r));

    const point3_t result =
      as::affine_inv_transform_pos(affine, point3_t{6.0_r, 0.0_r, 0.0_r});

    CHECK(result.as_vec().x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.as_vec().y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.as_vec().z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const affine_t affine = affine_t(
      as::mat3_rotation_z(deg_to_rad(90.0_r)), vec3_t(0.0_r, 10.0_r, 0.0_r));

    const point3_t result =
      as::affine_inv_transform_pos(affine, point3_t{5.0_r, 0.0_r, 0.0_r});

    CHECK(result.as_vec().x == Approx(-10.0_r).margin(g_epsilon));
    CHECK(result.as_vec().y == Approx(-5.0_r).margin(g_epsilon));
    CHECK(result.as_vec().z == Approx(0.0_r).margin(g_epsilon));
  }
}

TEST_CASE("affine_transform_pos", "[as_affine]")
{
  const affine_t affine = affine_t(
    as::mat3_rotation_y(deg_to_rad(90.0_r)), vec3_t(5.0_r, 0.0_r, 0.0_r));

  const point3_t result =
    as::affine_transform_pos(affine, point3_t(1.0_r, 0.0_r, 0.0_r));

  CHECK(result.as_vec().x == Approx(5.0_r).margin(g_epsilon));
  CHECK(result.as_vec().y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.as_vec().z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{
  {
    const affine_t affine =
      affine_t(mat3_t::identity(), vec3_t(5.0_r, 0.0_r, 0.0_r));

    const vec3_t result =
      as::affine_inv_transform_dir(affine, vec3_t{6.0_r, 0.0_r, 0.0_r});

    CHECK(result.x == Approx(6.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const affine_t affine = affine_t(
      as::mat3_rotation_z(deg_to_rad(90.0_r)), vec3_t(0.0_r, 10.0_r, 0.0_r));

    const vec3_t result =
      as::affine_inv_transform_dir(affine, vec3_t{5.0_r, 0.0_r, 0.0_r});

    const real_t local_epsilon = 1.0e-6_r;
    CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
    CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
  }
}

TEST_CASE("affine_to_arr", "[as_affine]")
{
  using gsl::make_span;

  affine_t affine(
    mat3_t(1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r, 8.0_r, 9.0_r),
    vec3_t(10.0_r, 20.0_r, 30.0_r));

  real_t expected_affine[12];
  as::affine_to_arr(affine, expected_affine);

  CHECK_THAT(
    make_span(expected_affine, 9), make_elements_sub(affine.rotation, 9));
  CHECK_THAT(
    make_span(&expected_affine[9], 3),
    make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_from_arr", "[as_affine]")
{
  using gsl::make_span;

  real_t affine_arr[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r,  5.0_r,  6.0_r,
                         7.0_r, 8.0_r, 9.0_r, 10.0_r, 20.0_r, 30.0_r};

  affine_t affine;
  affine = as::affine_from_arr(affine_arr);

  CHECK_THAT(make_span(affine_arr, 9), make_elements_sub(affine.rotation, 9));
  CHECK_THAT(
    make_span(&affine_arr[9], 3), make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_from_mat3", "[as_affine]")
{
  using gsl::make_span;

  mat3_t mat3{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r,
              60.0_r, 70.0_r, 80.0_r, 90.0_r};

  affine_t affine;
  affine = as::affine_from(mat3);

  CHECK(as::mat_equal(mat3, affine.rotation));
  CHECK_THAT(
    arr(0.0_r, 0.0_r, 0.0_r), make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_from_mat3_vec3", "[as_affine]")
{
  using gsl::make_span;

  mat3_t mat3(
    10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r, 60.0_r, 70.0_r, 80.0_r, 90.0_r);
  vec3_t vec3(99.0_r, 98.0_r, 97.0_r);

  affine_t affine;
  affine = as::affine_from(mat3, vec3);

  CHECK(as::mat_equal(mat3, affine.rotation));
  CHECK_THAT(
    arr(99.0_r, 98.0_r, 97.0_r), make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_from_vec3", "[as_affine]")
{
  using gsl::make_span;

  vec3_t vec3(99.0_r, 98.0_r, 97.0_r);

  affine_t affine;
  affine = as::affine_from(vec3);

  CHECK(as::mat_equal(mat3_t::identity(), affine.rotation));
  CHECK_THAT(
    arr(99.0_r, 98.0_r, 97.0_r), make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_from_point3", "[as_affine]")
{
  using gsl::make_span;

  point3_t point3{5.0_r, 10.0_r, 15.0_r};

  affine_t affine;
  affine = as::affine_from(point3);

  CHECK(as::mat_equal(mat3_t::identity(), affine.rotation));
  CHECK_THAT(
    arr(5.0_r, 10.0_r, 15.0_r), make_elements_sub(affine.translation, 3));
}

TEST_CASE("affine_concatenation", "[as_affine]")
{
  using gsl::make_span;

  mat4_t mat_a = as::from_mat3_vec3(
    as::mat3_rotation_x(deg_to_rad(45.0_r)), vec3_t::axis_x(5.0_r));

  mat4_t mat_b = as::from_mat3_vec3(
    as::mat3_rotation_y(deg_to_rad(90.0_r)), vec3_t::axis_y(10.0_r));

  mat4_t mat_c = as::from_mat3_vec3(
    as::mat3_rotation_y(deg_to_rad(180.0_r)), vec3_t::axis_z(20.0_r));

  mat4_t mat_result;
  mat_result = as::mat_mul(as::mat_mul(mat_a, mat_b), mat_c);

  affine_t affine_a = as::affine_from(mat_a);
  affine_t affine_b = as::affine_from(mat_b);
  affine_t affine_c = as::affine_from(mat_c);

  affine_t affine_result;
  affine_result = as::affine_mul(as::affine_mul(affine_a, affine_b), affine_c);

  real_t expected_orientation[9];
  as::mat_to_arr(affine_result.rotation, expected_orientation);

  real_t expected_position[3];
  vec_to_arr(affine_result.translation, expected_position);

  CHECK_THAT(
    make_span(expected_orientation),
    make_elements_sub(as::mat3_from_mat4(mat_result), 9));

  CHECK_THAT(
    make_span(expected_position),
    make_elements_sub(vec3_from_vec4(as::mat4_translation(mat_result)), 3));
}

TEST_CASE("affine_inverse", "[as_affine]")
{
  using gsl::make_span;

  const affine_t affine(
    as::mat3_rotation_y(deg_to_rad(90.0_r)), vec3_t(5.0_r, 10.0_r, 20.0_r));

  const affine_t affine_expected_inverse(
    as::mat3_rotation_y(deg_to_rad(-90.0_r)), vec3_t(20.0_r, -10.0_r, -5.0_r));

  real_t expected_affine[12];
  as::affine_to_arr(affine_expected_inverse, expected_affine);

  affine_t result;
  result = affine_inverse(affine);

  CHECK_THAT(
    make_span(expected_affine, 9), make_elements_sub(result.rotation, 9));
  CHECK_THAT(
    make_span(&expected_affine[9], 3),
    make_elements_sub(result.translation, 3).margin(0.000001_r));
}

} // namespace unit_test
