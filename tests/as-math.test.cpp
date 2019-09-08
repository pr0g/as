#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math.hpp"

using namespace as;

const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("max", "[as_math]")
{
    const real_t a = 5.0f;
    const real_t b = 2.0f;

    {
        const real_t max_result = as::max(a, b);
        CHECK(max_result == Approx(a).epsilon(g_epsilon));
    }

    {
        const real_t max_result = as::max(b, a);
        CHECK(max_result == Approx(a).epsilon(g_epsilon));
    }

    {
        const real_t aa = 5.0f;
        const real_t max_result = as::max(aa, a);
        CHECK(max_result == Approx(aa).epsilon(g_epsilon));
    }
}

TEST_CASE("min", "[as_math]")
{
    const real_t a = 10.0f;
    const real_t b = 5.0f;

    {
        const real_t min_result = as::min(a, b);
        CHECK(min_result == Approx(b).epsilon(g_epsilon));
    }

    {
        const real_t min_result = as::min(b, a);
        CHECK(min_result == Approx(b).epsilon(g_epsilon));
    }

    {
        const real_t bb = 5.0f;
        const real_t max_result = as::min(bb, b);
        CHECK(max_result == Approx(bb).epsilon(g_epsilon));
    }
}

TEST_CASE("smoothstep", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3f;

    const real_t quarter_value  = as::smooth_step(0.25f, 0.0f, 1.0f);
    CHECK(quarter_value == Approx(0.15625f).epsilon(real_epsilon));

    const real_t mid_value  = as::smooth_step(0.5f, 0.0f, 1.0f);
    CHECK(mid_value == Approx(0.5f).epsilon(real_epsilon));

    const real_t three_quarter_value  = as::smooth_step(0.75f, 0.0f, 1.0f);
    CHECK(three_quarter_value == Approx(0.84375f).epsilon(real_epsilon));
}

TEST_CASE("degrees_to_radians", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3f;

    CHECK(as::deg_to_rad(57.2958f) == Approx(1.0f).epsilon(real_epsilon));
    CHECK(as::deg_to_rad(90.0f) == Approx(1.5708f).epsilon(real_epsilon));
    CHECK(as::deg_to_rad(180.0f) == Approx(3.14159f).epsilon(real_epsilon));
    CHECK(as::deg_to_rad(270.0f) == Approx(4.71239f).epsilon(real_epsilon));
    CHECK(as::deg_to_rad(360.0f) == Approx(6.28319f).epsilon(real_epsilon));
}

TEST_CASE("radians_to_degrees", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3f;

    CHECK(as::rad_to_deg(1.0f) == Approx(57.2958f).epsilon(real_epsilon));
    CHECK(as::rad_to_deg(1.5708f) == Approx(90.0f).epsilon(real_epsilon));
    CHECK(as::rad_to_deg(3.14159f) == Approx(180.0f).epsilon(real_epsilon));
    CHECK(as::rad_to_deg(4.71239f) == Approx(270.0f).epsilon(real_epsilon));
    CHECK(as::rad_to_deg(6.28319f) == Approx(360.0f).epsilon(real_epsilon));
}

// explicit instantiations (for coverage)
template real_t as::smooth_step(real_t t, real_t v0, real_t v1);
