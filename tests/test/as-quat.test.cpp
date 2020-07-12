#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat3_t;
using as::quat_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace affine = as::affine;
namespace mat3 = as::mat3;
namespace vec3 = as::vec3;
namespace quat = as::quat;

// use float epsilon for comparisons
const real_t g_epsilon = 1e-6_r;

TEST_CASE("quat_identity", "[as_quat]")
{
    {
        quat_t q;
        q = quat_t::identity();
        CHECK(q.x == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.y == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.z == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.w == Approx(1.0_r).epsilon(g_epsilon));
    }

    {
        quat_t q;
        q = quat_t(1.0_r, vec3_t::zero());
        CHECK(q.x == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.y == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.z == Approx(0.0_r).epsilon(g_epsilon));
        CHECK(q.w == Approx(1.0_r).epsilon(g_epsilon));
    }
}

TEST_CASE("quat_addition", "[as_quat]")
{
    const quat_t quat_a{1.0_r, 0.1_r, 0.2_r, 0.3_r};
    const quat_t quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

    const quat_t result = quat_a + quat_b;

    CHECK(result.w == Approx(2.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.3_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.6_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.9_r).epsilon(g_epsilon));
}

TEST_CASE("quat_subtraction", "[as_quat]")
{
    const quat_t quat_a{1.0_r, 0.4_r, 0.6_r, 0.8_r};
    const quat_t quat_b{1.0_r, 0.2_r, 0.4_r, 0.6_r};

    const quat_t result = quat_a - quat_b;

    CHECK(result.w == Approx(0.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.2_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.2_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.2_r).epsilon(g_epsilon));
}

TEST_CASE("quat_negation", "[as_quat]")
{
    const quat_t quat_a{1.0_r, 0.4_r, 0.6_r, 0.8_r};

    const quat_t result = -quat_a;

    CHECK(result.w == Approx(-1.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(-0.4_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(-0.6_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(-0.8_r).epsilon(g_epsilon));
}

TEST_CASE("quat_multiplication", "[as_quat]")
{
    const quat_t quat_a =
        quat::axis_angle(vec3_t::axis_x(), deg_to_rad(90.0_r));
    const quat_t quat_b =
        quat::axis_angle(vec3_t::axis_y(), deg_to_rad(180.0_r));

    {
        const quat_t result = quat_a * quat_b;

        CHECK(result.w == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.70711_r).margin(g_epsilon));
        CHECK(result.z == Approx(0.70711_r).margin(g_epsilon));
    }

    {
        quat_t quat_mut = quat_a;
        quat_mut *= quat_b;

        CHECK(quat_mut.w == Approx(0.0_r).margin(g_epsilon));
        CHECK(quat_mut.x == Approx(0.0_r).margin(g_epsilon));
        CHECK(quat_mut.y == Approx(0.70711_r).margin(g_epsilon));
        CHECK(quat_mut.z == Approx(0.70711_r).margin(g_epsilon));
    }
}

TEST_CASE("quat_conjugate", "[as_quat]")
{
    const quat_t quat = quat_t{7.0_r, 4.0_r, 5.0_r, 9.0_r};
    const quat_t result = quat::conjugate(quat);

    CHECK(result.w == Approx(7.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(-4.0_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(-5.0_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(-9.0_r).epsilon(g_epsilon));
}

TEST_CASE("quat_length", "[as_quat]")
{
    const quat_t quat = quat_t{1.0_r, 2.0_r, 3.0_r, 4.0_r};
    const real_t result = quat::length(quat);

    CHECK(result == Approx(5.47722558_r).epsilon(g_epsilon));
}

TEST_CASE("quat_normalize", "[as_quat]")
{
    const quat_t quat = quat_t{2.0_r, 3.0_r, 4.0_r, 5.0_r};
    const quat_t result = quat::normalize(quat);

    CHECK(result.w == Approx(0.2721655269759087_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.4082482904638630_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.5443310539518173_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.6804138174397717_r).epsilon(g_epsilon));
}

TEST_CASE("quat_scale", "[as_quat]")
{
    const quat_t quat = quat_t{2.0_r, 3.0_r, 4.0_r, 5.0_r};
    const quat_t result = quat * 2.0_r;

    CHECK(result.w == Approx(4.0_r).epsilon(g_epsilon));
    CHECK(result.x == Approx(6.0_r).epsilon(g_epsilon));
    CHECK(result.y == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(result.z == Approx(10.0_r).epsilon(g_epsilon));
}

TEST_CASE("quat_inverse", "[as_quat]")
{
    const quat_t quat = quat_t{7.0_r, 4.0_r, 5.0_r, 9.0_r};
    const quat_t result = quat::inverse(quat);

    CHECK(result.w == Approx(0.0409357_r).margin(g_epsilon));
    CHECK(result.x == Approx(-0.0233918_r).margin(g_epsilon));
    CHECK(result.y == Approx(-0.0292398_r).margin(g_epsilon));
    CHECK(result.z == Approx(-0.0526316_r).margin(g_epsilon));
}

TEST_CASE("quat_rotate_vec", "[as_quat]")
{
    {
        const quat_t quat =
            quat::rotation_zxy(deg_to_rad(90.0_r), 0.0_r, 0.0_r);
        const vec3_t result = quat::rotate(quat, vec3_t::axis_y());

        CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(1.0_r).margin(g_epsilon));
    }

    {
        const quat_t quat = quat::rotation_zxy(
            deg_to_rad(0.0_r), deg_to_rad(-90.0_r), deg_to_rad(-90.0_r));
        const vec3_t result = quat::rotate(quat, vec3_t::axis_y());

        CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(1.0_r).margin(g_epsilon));
    }

    {
        const quat_t quat = quat::rotation_zxy(
            deg_to_rad(0.0_r), deg_to_rad(-90.0_r), deg_to_rad(-90.0_r));
        const vec3_t result = quat::rotate(quat, vec3_t::axis_x());

        CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(-1.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
        const quat_t quat_x =
            quat::axis_angle(vec3_t::axis_x(), deg_to_rad(270.0_r));
        const quat_t quat_z =
            quat::axis_angle(vec3_t::axis_z(), deg_to_rad(-90.0_r));
        const quat_t quat_zx = quat_z * quat_x;

        const vec3_t result = quat::rotate(quat_zx, vec3_t::axis_z());

        CHECK(result.x == Approx(1.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
    }
}

TEST_CASE("quat_slerp", "[as_quat]")
{
    {
        const quat_t quat_y = quat::axis_angle(vec3_t::axis_z(), 0.0_r);
        const quat_t quat_x =
            quat::axis_angle(vec3_t::axis_z(), deg_to_rad(90.0_r));

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.5_r);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

            CHECK(result_vec.x == Approx(0.70711_r).margin(g_epsilon));
            CHECK(result_vec.y == Approx(0.70711_r).margin(g_epsilon));
            CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
        }

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.333333_r);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

            CHECK(result_vec.x == Approx(0.499995_r).margin(g_epsilon));
            CHECK(result_vec.y == Approx(0.86602_r).margin(g_epsilon));
            CHECK(result_vec.z == Approx(0.0_r).margin(g_epsilon));
        }

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.666666_r);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

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
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(45.0_r), deg_to_rad(45.0_r), deg_to_rad(0.0_r));
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(45.0_r), deg_to_rad(45.0_r), deg_to_rad(0.0_r));

        quat_t axis_angle_quat_from_mat;
        axis_angle_quat_from_mat = quat::from_mat3(axis_angle_mat);

        vec3_t vec{1.0_r, 0.0_r, 0.0_r};
        vec3_t result_matrix =
            affine::transform_dir(affine_t(axis_angle_mat), vec);
        vec3_t result_quat = as::quat::rotate(axis_angle_quat, vec);
        vec3_t result_quat_from_mat =
            as::quat::rotate(axis_angle_quat_from_mat, vec);

        CHECK(as::vec::equal(result_matrix, result_quat, g_epsilon));
        CHECK(as::vec::equal(result_matrix, result_quat_from_mat, g_epsilon));
    }

    {
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(95.0_r), deg_to_rad(180.0_r), deg_to_rad(0.0_r));
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(95.0_r), deg_to_rad(180.0_r), deg_to_rad(0.0_r));

        quat_t axis_angle_quat_from_mat;
        axis_angle_quat_from_mat = quat::from_mat3(axis_angle_mat);

        vec3_t vec{1.0_r, 1.0_r, 0.0_r};
        vec3_t result_matrix =
            affine::transform_dir(affine_t(axis_angle_mat), vec);
        vec3_t result_quat = as::quat::rotate(axis_angle_quat, vec);
        vec3_t result_quat_from_mat =
            as::quat::rotate(axis_angle_quat_from_mat, vec);

        CHECK(as::vec::equal(result_matrix, result_quat, g_epsilon));
        CHECK(as::vec::equal(result_matrix, result_quat_from_mat, g_epsilon));
    }

    {
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(0.0_r), deg_to_rad(95.0_r), deg_to_rad(180.0_r));
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(0.0_r), deg_to_rad(95.0_r), deg_to_rad(180.0_r));

        quat_t axis_angle_quat_from_mat;
        axis_angle_quat_from_mat = quat::from_mat3(axis_angle_mat);

        vec3_t vec{1.0_r, 0.0_r, 1.0_r};
        vec3_t result_matrix =
            affine::transform_dir(affine_t(axis_angle_mat), vec);
        vec3_t result_quat = as::quat::rotate(axis_angle_quat, vec);
        vec3_t result_quat_from_mat =
            as::quat::rotate(axis_angle_quat_from_mat, vec);

        CHECK(as::vec::equal(result_matrix, result_quat, g_epsilon));
        CHECK(as::vec::equal(result_matrix, result_quat_from_mat, g_epsilon));
    }

    {
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(95.0_r), deg_to_rad(0.0_r), deg_to_rad(180.0_r));
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(95.0_r), deg_to_rad(0.0_r), deg_to_rad(180.0_r));

        quat_t axis_angle_quat_from_mat;
        axis_angle_quat_from_mat = quat::from_mat3(axis_angle_mat);

        vec3_t vec{1.0_r, 1.0_r, 1.0_r};
        vec3_t result_matrix =
            affine::transform_dir(affine_t(axis_angle_mat), vec);
        vec3_t result_quat = as::quat::rotate(axis_angle_quat, vec);
        vec3_t result_quat_from_mat =
            as::quat::rotate(axis_angle_quat_from_mat, vec);

        CHECK(as::vec::equal(result_matrix, result_quat, g_epsilon));
        CHECK(as::vec::equal(result_matrix, result_quat_from_mat, g_epsilon));
    }
}

} // namespace unit_test
