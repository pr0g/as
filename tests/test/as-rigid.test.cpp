#include "as-helpers.test.hpp"
#include "as/as-math-ops.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch_test_macros.hpp"

namespace unit_test
{

// testing
using Catch::Approx;

// types
using as::affine;
using as::mat3;
using as::mat4;
using as::quat;
using as::real;
using as::rigid;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

// use float epsilon for comparisons
const real g_epsilon = real(std::numeric_limits<float>::epsilon());

static_assert(std::is_trivial_v<rigid>);
static_assert(std::is_standard_layout_v<rigid>);
static_assert(std::is_pod_v<rigid>);

TEST_CASE("rigid_constructor_position_rotation", "[as_rigid]")
{
  rigid r;
  quat rotation = as::quat_rotation_x(radians(90.0_r));
  vec3 translation = vec3(0.0_r, 2.0_r, 2.0_r);
  r = rigid(rotation, translation);

  CHECK(vec_near(translation, r.translation));
  CHECK(as::quat_near(rotation, r.rotation));
}

TEST_CASE("rigid_constructor_position", "[as_rigid]")
{
  rigid r;
  r = rigid(vec3(1.0_r, 2.0_r, 3.0_r));

  CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(r.translation));
  CHECK(as::quat_near(quat::identity(), r.rotation));
}

TEST_CASE("rigid_transform_dir", "[as_rigid]")
{
  const rigid r(
    as::quat_rotation_y(radians(90.0_r)), vec3(5.0_r, 0.0_r, 0.0_r));

  const vec3 result = as::rigid_transform_dir(r, vec3{1.0_r, 0.0_r, 0.0_r});

  CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("rigid_inv_transform_pos", "[as_rigid]")
{
  {
    const rigid r = rigid(quat::identity(), vec3(5.0_r, 0.0_r, 0.0_r));

    const vec3 result =
      as::rigid_inv_transform_pos(r, vec3(6.0_r, 0.0_r, 0.0_r));

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const rigid r =
      rigid(as::quat_rotation_z(radians(90.0_r)), vec3(0.0_r, 10.0_r, 0.0_r));

    const vec3 result =
      as::rigid_inv_transform_pos(r, vec3(5.0_r, 0.0_r, 0.0_r));

    CHECK(result.x == Approx(-10.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-5.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }
}

TEST_CASE("rigid_transform_pos", "[as_rigid]")
{
  const rigid r =
    rigid(as::quat_rotation_y(radians(90.0_r)), vec3(5.0_r, 0.0_r, 0.0_r));

  const vec3 result = as::rigid_transform_pos(r, vec3(1.0_r, 0.0_r, 0.0_r));

  CHECK(result.x == Approx(5.0_r).margin(g_epsilon));
  CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
  CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("rigid_inv_transform_dir", "[as_rigid]")
{
  {
    const rigid r = rigid(quat::identity(), vec3(5.0_r, 0.0_r, 0.0_r));

    const vec3 result =
      as::rigid_inv_transform_dir(r, vec3{6.0_r, 0.0_r, 0.0_r});

    CHECK(result.x == Approx(6.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const rigid r =
      rigid(as::quat_rotation_z(radians(90.0_r)), vec3(0.0_r, 10.0_r, 0.0_r));

    const vec3 result =
      as::rigid_inv_transform_dir(r, vec3{5.0_r, 0.0_r, 0.0_r});

    const real local_epsilon = 1.0e-6_r;
    CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
    CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
  }
}

TEST_CASE("rigid_to_arr", "[as_rigid]")
{
  using gsl::make_span;

  rigid r(
    quat(1.0_r, 2.0_r, 3.0_r, 4.0_r),
    vec3(10.0_r, 20.0_r, 30.0_r));

  real expected_rigid[7];
  as::rigid_to_arr(r, expected_rigid);

  CHECK_THAT(make_span(expected_rigid, 4), elements_are_span(r.rotation));
  CHECK_THAT(
    make_span(&expected_rigid[4], 3), elements_are_span(r.translation));
}

TEST_CASE("rigid_from_arr", "[as_rigid]")
{
  using gsl::make_span;

  real rigid_arr[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r,  5.0_r,  6.0_r, 7.0_r};

  rigid r;
  r = as::rigid_from_arr(rigid_arr);

  CHECK_THAT(make_span(rigid_arr, 4), elements_are_span(r.rotation));
  CHECK_THAT(make_span(&rigid_arr[4], 3), elements_are_span(r.translation));
}

TEST_CASE("rigid_from_quat", "[as_rigid]")
{
  using gsl::make_span;

  quat q(10.0_r, 20.0_r, 30.0_r, 40.0_r);

  rigid r;
  r = as::rigid_from_quat(q);

  CHECK(as::quat_near(q, r.rotation));
  CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), elements_are_array(r.translation));
}

TEST_CASE("rigid_from_quat_vec3", "[as_rigid]")
{
  quat q(10.0_r, 20.0_r, 30.0_r, 40.0_r);
  vec3 v3(99.0_r, 98.0_r, 97.0_r);

  rigid r;
  r = as::rigid_from_quat_vec3(q, v3);

  CHECK(as::quat_near(q, r.rotation));
  CHECK_THAT(arr(99.0_r, 98.0_r, 97.0_r), elements_are_array(r.translation));
}

TEST_CASE("rigid_from_vec3", "[as_rigid]")
{
  vec3 v3(99.0_r, 98.0_r, 97.0_r);

  rigid r;
  r = as::rigid_from_vec3(v3);

  CHECK(as::quat_near(quat::identity(), r.rotation));
  CHECK_THAT(arr(99.0_r, 98.0_r, 97.0_r), elements_are_array(r.translation));
}

TEST_CASE("rigid_concatenation", "[as_rigid]")
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

  rigid rigid_a = as::rigid_from_mat4(mat_a);
  rigid rigid_b = as::rigid_from_mat4(mat_b);
  rigid rigid_c = as::rigid_from_mat4(mat_c);

  rigid rigid_result;
  rigid_result = as::rigid_mul(as::rigid_mul(rigid_a, rigid_b), rigid_c);

  real expected_orientation[4];
  as::quat_to_arr(rigid_result.rotation, expected_orientation);

  real expected_position[3];
  vec_to_arr(rigid_result.translation, expected_position);

  CHECK(as::quat_near(
    rigid_result.rotation, as::quat_from_mat3(mat3_from_mat4(mat_result))));

  CHECK_THAT(
    make_span(expected_position),
    elements_are_span(as::mat4_translation(mat_result)).margin(0.000001_r));
}

TEST_CASE("rigid_inverse", "[as_rigid]")
{
  using gsl::make_span;

  const rigid r(
    as::quat_rotation_y(radians(90.0_r)), vec3(5.0_r, 10.0_r, 20.0_r));

  const rigid rigid_expected_inverse(
    as::quat_rotation_y(radians(-90.0_r)), vec3(20.0_r, -10.0_r, -5.0_r));

  real expected_rigid[7];
  as::rigid_to_arr(rigid_expected_inverse, expected_rigid);

  rigid result;
  result = rigid_inverse(r);

  CHECK_THAT(make_span(expected_rigid, 4), elements_are_span(result.rotation));
  CHECK_THAT(
    make_span(&expected_rigid[4], 3),
    elements_are_span(result.translation));
}

TEST_CASE("rigid_from_affine", "[as_rigid]")
{
  affine a = affine(as::mat3_rotation_y(as::radians(90.0_r)), as::vec3(5.0_r, 0.0_r, 10.0_r));
  rigid r = rigid_from_affine(a);

  vec3 result_affine = as::affine_transform_pos(a, vec3::axis_x(5.0_r));
  vec3 result_rigid = as::rigid_transform_pos(r, vec3::axis_x(5.0_r));

  CHECK_THAT(result_affine, elements_are(result_rigid));
}

TEST_CASE("rigid_identity", "[as_rigid]")
{
  rigid r;
  r = rigid::identity();

  CHECK_THAT(r.rotation, elements_are(quat::identity()));
  CHECK_THAT(r.translation, elements_are(vec3::zero()));
}

} // namespace unit_test
