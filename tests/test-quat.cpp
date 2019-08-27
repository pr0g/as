#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

using namespace as;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("quat_identity", "[as_quat]")
{
    {
        quat_t q;
        q = quat::identity();
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }

    {
        quat_t q;
        q = quat_t(1.0f, vec3::zero());
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }
}

TEST_CASE("quat_addition", "[as_quat]")
{
    const quat_t quat_a{ 1.0f, 0.1f, 0.2f, 0.3f };
    const quat_t quat_b{ 1.0f, 0.2f, 0.4f, 0.6f };

    const quat_t result = quat_a + quat_b;

    CHECK(result.w == Approx(2.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.3f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.6f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.9f).epsilon(g_epsilon));
}

TEST_CASE("quat_subtraction", "[as_quat]")
{
    const quat_t quat_a{ 1.0f, 0.4f, 0.6f, 0.8f };
    const quat_t quat_b{ 1.0f, 0.2f, 0.4f, 0.6f };

    const quat_t result = quat_a - quat_b;

    CHECK(result.w == Approx(0.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.2f).epsilon(g_epsilon));
}

TEST_CASE("quat_negation", "[as_quat]")
{
    const quat_t quat_a{ 1.0f, 0.4f, 0.6f, 0.8f };

    const quat_t result = -quat_a;

    CHECK(result.w == Approx(-1.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(-0.4f).epsilon(g_epsilon));
    CHECK(result.y == Approx(-0.6f).epsilon(g_epsilon));
    CHECK(result.z == Approx(-0.8f).epsilon(g_epsilon));
}

TEST_CASE("quat_multiplication", "[as_quat]")
{
    const quat_t quat_a =
        as::quat::axis_angle(as::vec3::axis_x(), as::deg_to_rad(90.0f));
    const quat_t quat_b =
        as::quat::axis_angle(as::vec3::axis_y(), as::deg_to_rad(180.0f));


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
    const quat_t quat = quat_t{ 7.0f, 4.0f, 5.0f, 9.0f };
    const quat_t result = as::quat::conjugate(quat);

    CHECK(result.w == Approx(7.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(-4.0f).epsilon(g_epsilon));
    CHECK(result.y == Approx(-5.0f).epsilon(g_epsilon));
    CHECK(result.z == Approx(-9.0f).epsilon(g_epsilon));
}

TEST_CASE("quat_length", "[as_quat]")
{
    const quat_t quat = quat_t{ 1.0f, 2.0f, 3.0f, 4.0f };
    const real_t result = as::quat::length(quat);

    CHECK(result == Approx(5.47722558f).epsilon(g_epsilon));
}

TEST_CASE("quat_normalize", "[as_quat]")
{
    const quat_t quat = quat_t{ 2.0f, 3.0f, 4.0f, 5.0f };
    const quat_t result = as::quat::normalize(quat);

    CHECK(result.w == Approx(0.2721655269759087f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.4082482904638630f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.5443310539518173f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.6804138174397717f).epsilon(g_epsilon));
}

TEST_CASE("quat_scale", "[as_quat]")
{
    const quat_t quat = quat_t{ 2.0f, 3.0f, 4.0f, 5.0f };
    const quat_t result = quat * 2.0f;

    CHECK(result.w == Approx(4.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(6.0f).epsilon(g_epsilon));
    CHECK(result.y == Approx(8.0f).epsilon(g_epsilon));
    CHECK(result.z == Approx(10.0f).epsilon(g_epsilon));
}

TEST_CASE("quat_inverse", "[as_quat]")
{
    const quat_t quat = quat_t{ 7.0f, 4.0f, 5.0f, 9.0f };
    const quat_t result = as::quat::inverse(quat);

    CHECK(result.w == Approx(0.0409357f).margin(g_epsilon));
    CHECK(result.x == Approx(-0.0233918f).margin(g_epsilon));
    CHECK(result.y == Approx(-0.0292398f).margin(g_epsilon));
    CHECK(result.z == Approx(-0.0526316f).margin(g_epsilon));
}
