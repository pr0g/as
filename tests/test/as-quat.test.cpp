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
using as::quat;
using as::real;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

static const real g_epsilon = 1e-6_r;

[[maybe_unused]] constexpr auto quat_type_check =
  unit_test::trivial_standard_layout_check<quat>();

TEST_CASE("quat_identity", "[as_quat]")
{
  {
    quat q;
    q = quat::identity();
    CHECK(q.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.z == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.w == Approx(1.0_r).epsilon(g_epsilon));
  }

  {
    quat q;
    q = quat(1.0_r, vec3::zero());
    CHECK(q.x == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.y == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.z == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q.w == Approx(1.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("quat_addition", "[as_quat]")
{
  const quat quat_a{1.0_r, 0.1_r, 0.2_r, 0.3_r};
  const quat quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

  const quat result = quat_a + quat_b;

  CHECK(result.w == Approx(2.0_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(0.3_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(0.6_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(0.9_r).epsilon(g_epsilon));
}

TEST_CASE("quat_assignment_addition", "[as_quat]")
{
  quat quat_a{1.0_r, 0.1_r, 0.2_r, 0.3_r};
  const quat quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

  quat_a += quat_b;

  CHECK(quat_a.w == Approx(2.0_r).epsilon(g_epsilon));
  CHECK(quat_a.x == Approx(0.3_r).epsilon(g_epsilon));
  CHECK(quat_a.y == Approx(0.6_r).epsilon(g_epsilon));
  CHECK(quat_a.z == Approx(0.9_r).epsilon(g_epsilon));
}

TEST_CASE("quat_subtraction", "[as_quat]")
{
  const quat quat_a{1.0_r, 0.4_r, 0.6_r, 0.8_r};
  const quat quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

  const quat result = quat_a - quat_b;

  CHECK(result.w == Approx(0.0_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(0.2_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(0.2_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(0.2_r).epsilon(g_epsilon));
}

TEST_CASE("quat_assignment_subtraction", "[as_quat]")
{
  quat quat_a{1.0_r, 0.4_r, 0.6_r, 0.8_r};
  const quat quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

  quat_a -= quat_b;

  CHECK(quat_a.w == Approx(0.0_r).epsilon(g_epsilon));
  CHECK(quat_a.x == Approx(0.2_r).epsilon(g_epsilon));
  CHECK(quat_a.y == Approx(0.2_r).epsilon(g_epsilon));
  CHECK(quat_a.z == Approx(0.2_r).epsilon(g_epsilon));
}

TEST_CASE("quat_negation", "[as_quat]")
{
  const quat quat_a{1.0_r, 0.4_r, 0.6_r, 0.8_r};

  const quat result = -quat_a;

  CHECK(result.w == Approx(-1.0_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(-0.4_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(-0.6_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(-0.8_r).epsilon(g_epsilon));
}

TEST_CASE("quat_multiplication", "[as_quat]")
{
  const quat quat_a = quat_rotation_axis(vec3::axis_x(), radians(90.0_r));
  const quat quat_b = quat_rotation_axis(vec3::axis_y(), radians(180.0_r));

  {
    const quat result = quat_a * quat_b;

    CHECK(result.w == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.70711_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.70711_r).margin(g_epsilon));
  }

  {
    quat quat_mut = quat_a;
    quat_mut *= quat_b;

    CHECK(quat_mut.w == Approx(0.0_r).margin(g_epsilon));
    CHECK(quat_mut.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(quat_mut.y == Approx(0.70711_r).margin(g_epsilon));
    CHECK(quat_mut.z == Approx(0.70711_r).margin(g_epsilon));
  }
}

TEST_CASE("quat_conjugate", "[as_quat]")
{
  const quat q = quat{7.0_r, 4.0_r, 5.0_r, 9.0_r};
  const quat result = quat_conjugate(q);

  CHECK(result.w == Approx(7.0_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(-4.0_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(-5.0_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(-9.0_r).epsilon(g_epsilon));
}

TEST_CASE("quat_length", "[as_quat]")
{
  const quat q = quat{1.0_r, 2.0_r, 3.0_r, 4.0_r};
  const real result = quat_length(q);

  CHECK(result == Approx(5.47722558_r).epsilon(g_epsilon));
}

TEST_CASE("quat_normalize", "[as_quat]")
{
  const quat q = quat{2.0_r, 3.0_r, 4.0_r, 5.0_r};
  const quat result = quat_normalize(q);

  CHECK(result.w == Approx(0.2721655269759087_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(0.4082482904638630_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(0.5443310539518173_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(0.6804138174397717_r).epsilon(g_epsilon));
}

TEST_CASE("quat_scale", "[as_quat]")
{
  {
    const quat q = quat{2.0_r, 3.0_r, 4.0_r, 5.0_r};
    const quat result = q * 2.0_r;

    CHECK(result.w == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(6.0_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(10.0_r).epsilon(g_epsilon));
  }

  {
    const quat q = quat{4.0_r, 5.0_r, 6.0_r, 7.0_r};
    const quat result = 3.0_r * q;

    CHECK(result.w == Approx(12.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(15.0_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(18.0_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(21.0_r).epsilon(g_epsilon));
  }
}

TEST_CASE("quat_inverse", "[as_quat]")
{
  const quat q = quat{7.0_r, 4.0_r, 5.0_r, 9.0_r};
  const quat result = quat_inverse(q);

  CHECK(result.w == Approx(0.0409357_r).margin(g_epsilon));
  CHECK(result.x == Approx(-0.0233918_r).margin(g_epsilon));
  CHECK(result.y == Approx(-0.0292398_r).margin(g_epsilon));
  CHECK(result.z == Approx(-0.0526316_r).margin(g_epsilon));
}

TEST_CASE("quat_rotate_vec", "[as_quat]")
{
  {
    const quat q = as::quat_rotation_zxy(radians(90.0_r), 0.0_r, 0.0_r);
    const vec3 result = quat_rotate(q, vec3::axis_y());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(1.0_r).margin(g_epsilon));
  }

  {
    const quat q =
      as::quat_rotation_zxy(radians(0.0_r), radians(-90.0_r), radians(-90.0_r));
    const vec3 result = quat_rotate(q, vec3::axis_y());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(1.0_r).margin(g_epsilon));
  }

  {
    const quat q =
      as::quat_rotation_zxy(radians(0.0_r), radians(-90.0_r), radians(-90.0_r));
    const vec3 result = quat_rotate(q, vec3::axis_x());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-1.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat q = as::quat_rotation_zxy(
      vec3(radians(0.0_r), radians(-90.0_r), radians(-90.0_r)));
    const vec3 result = quat_rotate(q, vec3::axis_x());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-1.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat q =
      as::quat_rotation_xyz(radians(90.0_r), radians(0.0_r), radians(0.0_r));
    const vec3 result = quat_rotate(q, vec3::axis_z());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-1.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat q = as::quat_rotation_xyz(
      vec3(radians(90.0_r), radians(0.0_r), radians(0.0_r)));
    const vec3 result = quat_rotate(q, vec3::axis_z());

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(-1.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat q =
      as::quat_rotation_xyz(radians(90.0_r), radians(0.0_r), radians(90.0_r));
    const vec3 result = quat_rotate(q, vec3::axis_z());

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat q = as::quat_rotation_xyz(
      vec3(radians(90.0_r), radians(0.0_r), radians(90.0_r)));
    const vec3 result = quat_rotate(q, vec3::axis_z());

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }

  {
    const quat quat_x = quat_rotation_axis(vec3::axis_x(), radians(270.0_r));
    const quat quat_z = quat_rotation_axis(vec3::axis_z(), radians(-90.0_r));
    const quat quat_zx = quat_z * quat_x;

    const vec3 result = quat_rotate(quat_zx, vec3::axis_z());

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }
}

TEST_CASE("quat_nlerp", "[as_quat]")
{
  const quat quat_y = quat_rotation_axis(vec3::axis_z(), 0.0_r);
  const quat quat_x = quat_rotation_axis(vec3::axis_z(), radians(90.0_r));

  const quat result_quat = quat_nlerp(quat_x, quat_y, 0.5_r);
  const vec3 result_vec = quat_rotate(result_quat, vec3::axis_x());

  CHECK(result_vec.x == Approx(0.60355_r).margin(g_epsilon));
  CHECK(result_vec.y == Approx(0.60355_r).margin(g_epsilon));
  CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
}

TEST_CASE("quat_slerp", "[as_quat]")
{
  {
    const quat quat_y = quat_rotation_axis(vec3::axis_z(), 0.0_r);
    const quat quat_x = quat_rotation_axis(vec3::axis_z(), radians(90.0_r));

    {
      const quat result_quat = quat_slerp(quat_x, quat_y, 0.5_r);
      const vec3 result_vec = quat_rotate(result_quat, vec3::axis_x());

      CHECK(result_vec.x == Approx(0.70711_r).margin(g_epsilon));
      CHECK(result_vec.y == Approx(0.70711_r).margin(g_epsilon));
      CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
      const quat result_quat = quat_slerp(quat_x, quat_y, 0.333333_r);
      const vec3 result_vec = quat_rotate(result_quat, vec3::axis_x());

      CHECK(result_vec.x == Approx(0.499995_r).margin(g_epsilon));
      CHECK(result_vec.y == Approx(0.86602_r).margin(g_epsilon));
      CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
      const quat result_quat = quat_slerp(quat_x, quat_y, 0.666666_r);
      const vec3 result_vec = quat_rotate(result_quat, vec3::axis_x());

      CHECK(result_vec.x == Approx(0.86602_r).margin(g_epsilon));
      CHECK(result_vec.y == Approx(0.5_r).margin(g_epsilon));
      CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
    }
  }

  {
    const quat quat_y = quat_rotation_axis(vec3::axis_y(), radians(90.0_r));
    const quat quat_x = quat_rotation_axis(vec3::axis_y(), radians(90.0_r));

    {
      const quat result_quat = quat_slerp(quat_x, quat_y, 0.0_r);

      CHECK(result_quat.x == Approx(quat_y.x).margin(g_epsilon));
      CHECK(result_quat.y == Approx(quat_y.y).margin(g_epsilon));
      CHECK(result_quat.z == Approx(quat_y.z).margin(g_epsilon));
      CHECK(result_quat.w == Approx(quat_y.w).margin(g_epsilon));
    }

    {
      const quat result_quat = quat_slerp(quat_x, quat_y, 1.0_r);

      CHECK(result_quat.x == Approx(quat_x.x).margin(g_epsilon));
      CHECK(result_quat.y == Approx(quat_x.y).margin(g_epsilon));
      CHECK(result_quat.z == Approx(quat_x.z).margin(g_epsilon));
      CHECK(result_quat.w == Approx(quat_x.w).margin(g_epsilon));
    }
  }
}

TEST_CASE("quat_from_mat3", "[as_quat]")
{
  using gsl::make_span;

  {
    quat rotation_axis_quat =
      as::quat_rotation_zxy(radians(45.0_r), radians(45.0_r), radians(0.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_zxy(radians(45.0_r), radians(45.0_r), radians(0.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 0.0_r, 0.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_xyz(radians(45.0_r), radians(45.0_r), radians(0.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_xyz(radians(45.0_r), radians(45.0_r), radians(0.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 0.0_r, 0.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_zxy(radians(95.0_r), radians(180.0_r), radians(0.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_zxy(radians(95.0_r), radians(180.0_r), radians(0.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 1.0_r, 0.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_xyz(radians(95.0_r), radians(180.0_r), radians(0.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_xyz(radians(95.0_r), radians(180.0_r), radians(0.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 1.0_r, 0.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_zxy(radians(0.0_r), radians(95.0_r), radians(180.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_zxy(radians(0.0_r), radians(95.0_r), radians(180.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 0.0_r, 1.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_xyz(radians(0.0_r), radians(95.0_r), radians(180.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_xyz(radians(0.0_r), radians(95.0_r), radians(180.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 0.0_r, 1.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_zxy(radians(95.0_r), radians(0.0_r), radians(180.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_zxy(radians(95.0_r), radians(0.0_r), radians(180.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 1.0_r, 1.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }

  {
    quat rotation_axis_quat =
      as::quat_rotation_xyz(radians(95.0_r), radians(0.0_r), radians(180.0_r));
    mat3 rotation_axis_mat =
      as::mat3_rotation_xyz(radians(95.0_r), radians(0.0_r), radians(180.0_r));

    quat rotation_axis_quat_from_mat;
    rotation_axis_quat_from_mat = quat_from_mat3(rotation_axis_mat);

    vec3 v{1.0_r, 1.0_r, 1.0_r};
    vec3 result_matrix = affine_transform_dir(affine(rotation_axis_mat), v);
    vec3 result_quat = as::quat_rotate(rotation_axis_quat, v);
    vec3 result_quat_from_mat = as::quat_rotate(rotation_axis_quat_from_mat, v);

    CHECK(as::vec_near(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_near(result_matrix, result_quat_from_mat, g_epsilon));
  }
}

TEST_CASE("quat_near", "[as_quat]")
{
  {
    quat q0(1.0_r, 2.0_r, 3.0_r, 4.0_r);
    quat q1(1.0_r, -2.0_r, 3.0_r, 4.0_r);
    CHECK(!as::quat_near(q0, q1, g_epsilon));
  }

  {
    quat q0(1.0_r, -2.0_r, 3.0_r, -4.0_r);
    quat q1(1.0_r, -2.0_r, 3.0_r, -4.0_r);
    CHECK(as::quat_near(q0, q1, g_epsilon));
  }

  {
    quat q0(1.0_r, -2.0_r, -3.0_r, -4.0_r);
    quat q1(-1.0_r, 2.0_r, 3.0_r, 4.0_r);
    CHECK(as::quat_near(q0, q1, g_epsilon));
  }
}

TEST_CASE("quat_iterator", "[as_quat]")
{
  const real w = quat(3.0_r, 4.0_r, 5.0_r, 6.0_r)[0];
  CHECK(w == Approx(3.0_r).epsilon(g_epsilon));

  {
    const quat q = quat::identity();
    auto result = std::min_element(cbegin(q), cend(q));
    CHECK(*result == Approx(0.0_r).epsilon(g_epsilon));
  }

  {
    quat q = quat::identity();
    std::reverse(begin(q), end(q));
    CHECK(q[0] == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q[1] == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q[2] == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(q[3] == Approx(1.0_r).epsilon(g_epsilon));
  }
}

} // namespace unit_test
