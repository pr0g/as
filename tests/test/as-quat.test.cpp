#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine;
using as::mat3;
using as::quat;
using as::real;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

// use float epsilon for comparisons
const real g_epsilon = 1e-6_r;

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
  const quat q = quat{2.0_r, 3.0_r, 4.0_r, 5.0_r};
  const quat result = q * 2.0_r;

  CHECK(result.w == Approx(4.0_r).epsilon(g_epsilon));
  CHECK(result.x == Approx(6.0_r).epsilon(g_epsilon));
  CHECK(result.y == Approx(8.0_r).epsilon(g_epsilon));
  CHECK(result.z == Approx(10.0_r).epsilon(g_epsilon));
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
    const quat q =
      as::quat_rotation_xyz(radians(90.0_r), radians(0.0_r), radians(0.0_r));
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
    const quat quat_x = quat_rotation_axis(vec3::axis_x(), radians(270.0_r));
    const quat quat_z = quat_rotation_axis(vec3::axis_z(), radians(-90.0_r));
    const quat quat_zx = quat_z * quat_x;

    const vec3 result = quat_rotate(quat_zx, vec3::axis_z());

    CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
  }
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
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

    CHECK(as::vec_equal(result_matrix, result_quat, g_epsilon));
    CHECK(as::vec_equal(result_matrix, result_quat_from_mat, g_epsilon));
  }
}

} // namespace unit_test
