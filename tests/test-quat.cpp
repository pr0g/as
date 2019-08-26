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
    using namespace gsl;

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
    using namespace gsl;

    const quat_t quat_a{ 1.0f, 0.4f, 0.6f, 0.8f };
    const quat_t quat_b{ 1.0f, 0.2f, 0.4f, 0.6f };

    const quat_t result = quat_a - quat_b;

    CHECK(result.w == Approx(0.0f).epsilon(g_epsilon));
    CHECK(result.x == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.y == Approx(0.2f).epsilon(g_epsilon));
    CHECK(result.z == Approx(0.2f).epsilon(g_epsilon));
}

TEST_CASE("quat_multiplication", "[as_quat]")
{
    using namespace gsl;

    const quat_t quat_a =
        as::quat::axis_angle(as::vec3::axis_x(), as::deg_to_rad(90.0f));
    const quat_t quat_b =
        as::quat::axis_angle(as::vec3::axis_y(), as::deg_to_rad(180.0f));

    const quat_t result = quat_a * quat_b;

    CHECK(result.w == Approx(0.0f).margin(std::numeric_limits<float>::epsilon()));
    CHECK(result.x == Approx(0.0f).margin(std::numeric_limits<float>::epsilon()));
    CHECK(result.y == Approx(0.70711f).margin(std::numeric_limits<float>::epsilon()));
    CHECK(result.z == Approx(0.70711f).margin(std::numeric_limits<float>::epsilon()));
}
