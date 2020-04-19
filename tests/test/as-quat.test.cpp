#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::mat3_t;
using as::quat_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;

// namespaces
namespace mat3 = as::mat3;
namespace vec3 = as::vec3;
namespace quat = as::quat;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("quat_identity", "[as_quat]")
{
    {
        quat_t q;
        q = quat_t::identity();
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }

    {
        quat_t q;
        q = quat_t(1.0f, vec3_t::zero());
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }
}

TEST_CASE("quat_addition", "[as_quat]")
{
    const quat_t quat_a{1.0f, 0.1f, 0.2f, 0.3f};
    const quat_t quat_b{1.0f, 0.2f, 0.4f, 0.6f};

    const quat_t result = quat_a + quat_b;

    CHECK(result.w == Approx(2.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.3f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.6f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.9f).epsilon(g_epsilon));
}

TEST_CASE("quat_subtraction", "[as_quat]")
{
    const quat_t quat_a{1.0f, 0.4f, 0.6f, 0.8f};
    const quat_t quat_b{1.0f, 0.2f, 0.4f, 0.6f};

    const quat_t result = quat_a - quat_b;

    CHECK(result.w == Approx(0.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.2f).epsilon(g_epsilon));
}

TEST_CASE("quat_negation", "[as_quat]")
{
    const quat_t quat_a{1.0f, 0.4f, 0.6f, 0.8f};

    const quat_t result = -quat_a;

    CHECK(result.w == Approx(-1.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(-0.4f).epsilon(g_epsilon));
    CHECK(result.y == Approx(-0.6f).epsilon(g_epsilon));
    CHECK(result.z == Approx(-0.8f).epsilon(g_epsilon));
}

TEST_CASE("quat_multiplication", "[as_quat]")
{
    const quat_t quat_a = quat::axis_angle(vec3_t::axis_x(), deg_to_rad(90.0f));
    const quat_t quat_b =
        quat::axis_angle(vec3_t::axis_y(), deg_to_rad(180.0f));

    {
        const quat_t result = quat_a * quat_b;

        CHECK(result.w == Approx(0.0f).margin(g_epsilon));
        CHECK(result.x == Approx(0.0f).margin(g_epsilon));
        CHECK(result.y == Approx(0.70711f).margin(g_epsilon));
        CHECK(result.z == Approx(0.70711f).margin(g_epsilon));
    }

    {
        quat_t quat_mut = quat_a;
        quat_mut *= quat_b;

        CHECK(quat_mut.w == Approx(0.0f).margin(g_epsilon));
        CHECK(quat_mut.x == Approx(0.0f).margin(g_epsilon));
        CHECK(quat_mut.y == Approx(0.70711f).margin(g_epsilon));
        CHECK(quat_mut.z == Approx(0.70711f).margin(g_epsilon));
    }
}

TEST_CASE("quat_conjugate", "[as_quat]")
{
    const quat_t quat = quat_t{7.0f, 4.0f, 5.0f, 9.0f};
    const quat_t result = quat::conjugate(quat);

    CHECK(result.w == Approx(7.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(-4.0f).epsilon(g_epsilon));
    CHECK(result.y == Approx(-5.0f).epsilon(g_epsilon));
    CHECK(result.z == Approx(-9.0f).epsilon(g_epsilon));
}

TEST_CASE("quat_length", "[as_quat]")
{
    const quat_t quat = quat_t{1.0f, 2.0f, 3.0f, 4.0f};
    const real_t result = quat::length(quat);

    CHECK(result == Approx(5.47722558f).epsilon(g_epsilon));
}

TEST_CASE("quat_normalize", "[as_quat]")
{
    const quat_t quat = quat_t{2.0f, 3.0f, 4.0f, 5.0f};
    const quat_t result = quat::normalize(quat);

    CHECK(result.w == Approx(0.2721655269759087f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.4082482904638630f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.5443310539518173f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.6804138174397717f).epsilon(g_epsilon));
}

TEST_CASE("quat_scale", "[as_quat]")
{
    const quat_t quat = quat_t{2.0f, 3.0f, 4.0f, 5.0f};
    const quat_t result = quat * 2.0f;

    CHECK(result.w == Approx(4.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(6.0f).epsilon(g_epsilon));
    CHECK(result.y == Approx(8.0f).epsilon(g_epsilon));
    CHECK(result.z == Approx(10.0f).epsilon(g_epsilon));
}

TEST_CASE("quat_inverse", "[as_quat]")
{
    const quat_t quat = quat_t{7.0f, 4.0f, 5.0f, 9.0f};
    const quat_t result = quat::inverse(quat);

    CHECK(result.w == Approx(0.0409357f).margin(g_epsilon));
    CHECK(result.x == Approx(-0.0233918f).margin(g_epsilon));
    CHECK(result.y == Approx(-0.0292398f).margin(g_epsilon));
    CHECK(result.z == Approx(-0.0526316f).margin(g_epsilon));
}

TEST_CASE("quat_rotate_vec", "[as_quat]")
{
    {
        const quat_t quat = quat::rotation_zxy(deg_to_rad(90.0f), 0.0f, 0.0f);
        const vec3_t result = quat::rotate(quat, vec3_t::axis_y());

        CHECK(result.x == Approx(0.0f).margin(g_epsilon));
        CHECK(result.y == Approx(0.0f).margin(g_epsilon));
        CHECK(result.z == Approx(1.0f).margin(g_epsilon));
    }

    {
        const quat_t quat = quat::rotation_zxy(
            deg_to_rad(0.0f), deg_to_rad(-90.0f), deg_to_rad(-90.0f));
        const vec3_t result = quat::rotate(quat, vec3_t::axis_y());

        CHECK(result.x == Approx(0.0f).margin(g_epsilon));
        CHECK(result.y == Approx(0.0f).margin(g_epsilon));
        CHECK(result.z == Approx(1.0f).margin(g_epsilon));
    }

    {
        const quat_t quat = quat::rotation_zxy(
            deg_to_rad(0.0f), deg_to_rad(-90.0f), deg_to_rad(-90.0f));
        const vec3_t result = quat::rotate(quat, vec3_t::axis_x());

        CHECK(result.x == Approx(0.0f).margin(g_epsilon));
        CHECK(result.y == Approx(-1.0f).margin(g_epsilon));
        CHECK(result.z == Approx(0.0f).margin(g_epsilon));
    }

    {
        const quat_t quat_x =
            quat::axis_angle(vec3_t::axis_x(), deg_to_rad(270.0f));
        const quat_t quat_z =
            quat::axis_angle(vec3_t::axis_z(), deg_to_rad(-90.0f));
        const quat_t quat_zx = quat_z * quat_x;

        const vec3_t result = quat::rotate(quat_zx, vec3_t::axis_z());

        CHECK(result.x == Approx(1.0f).margin(g_epsilon));
        CHECK(result.y == Approx(0.0f).margin(g_epsilon));
        CHECK(result.z == Approx(0.0f).margin(g_epsilon));
    }
}

TEST_CASE("quat_slerp", "[as_quat]")
{
    {
        const quat_t quat_y = quat::axis_angle(vec3_t::axis_z(), 0.0f);
        const quat_t quat_x =
            quat::axis_angle(vec3_t::axis_z(), deg_to_rad(90.0f));

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.5f);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

            CHECK(result_vec.x == Approx(0.70711f).margin(g_epsilon));
            CHECK(result_vec.y == Approx(0.70711f).margin(g_epsilon));
            CHECK(result_vec.z == Approx(0.0f).margin(g_epsilon));
        }

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.333333f);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

            CHECK(result_vec.x == Approx(0.499995f).margin(g_epsilon));
            CHECK(result_vec.y == Approx(0.86602f).margin(g_epsilon));
            CHECK(result_vec.z == Approx(0.0f).margin(g_epsilon));
        }

        {
            const quat_t result_quat = quat::slerp(quat_x, quat_y, 0.666666f);
            const vec3_t result_vec =
                quat::rotate(result_quat, vec3_t::axis_x());

            CHECK(result_vec.x == Approx(0.86602f).margin(g_epsilon));
            CHECK(result_vec.y == Approx(0.5f).margin(g_epsilon));
            CHECK(result_vec.z == Approx(0.0f).margin(g_epsilon));
        }
    }
}

TEST_CASE("quat_from_mat3", "[as-quat]")
{
    using gsl::make_span;

    {
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(45.0f), deg_to_rad(45.0f), deg_to_rad(0.0f));
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(45.0f), deg_to_rad(45.0f), deg_to_rad(0.0f));

        quat_t axis_angle_quat_from_mat;
        axis_angle_quat_from_mat = quat::from_mat3(axis_angle_mat);

        // note - checking against 0.0f requires margin
        CHECK(axis_angle_quat_from_mat.w == Approx(axis_angle_quat.w).margin(g_epsilon));
        CHECK(axis_angle_quat_from_mat.x == Approx(axis_angle_quat.x).margin(g_epsilon));
        CHECK(axis_angle_quat_from_mat.y == Approx(axis_angle_quat.y).margin(g_epsilon));
        CHECK(axis_angle_quat_from_mat.z == Approx(axis_angle_quat.z).margin(g_epsilon));
    }
}

} // namespace unit_test
