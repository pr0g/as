#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math.hpp"

namespace unit_test
{

// types
using as::real_t;

// functions
using as::deg_to_rad;
using as::max;
using as::min;
using as::rad_to_deg;
using as::smooth_step;
using as::operator""_r;

const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("max", "[as_math]")
{
    const real_t a = 5.0_r;
    const real_t b = 2.0_r;

    {
        const real_t max_result = max(a, b);
        CHECK(max_result == Approx(a).epsilon(g_epsilon));
    }

    {
        const real_t max_result = max(b, a);
        CHECK(max_result == Approx(a).epsilon(g_epsilon));
    }

    {
        const real_t aa = 5.0_r;
        const real_t max_result = max(aa, a);
        CHECK(max_result == Approx(aa).epsilon(g_epsilon));
    }
}

TEST_CASE("min", "[as_math]")
{
    const real_t a = 10.0_r;
    const real_t b = 5.0_r;

    {
        const real_t min_result = min(a, b);
        CHECK(min_result == Approx(b).epsilon(g_epsilon));
    }

    {
        const real_t min_result = min(b, a);
        CHECK(min_result == Approx(b).epsilon(g_epsilon));
    }

    {
        const real_t bb = 5.0_r;
        const real_t max_result = min(bb, b);
        CHECK(max_result == Approx(bb).epsilon(g_epsilon));
    }
}

TEST_CASE("smoothstep", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3_r;

    real_t quarter_value;
    quarter_value = smooth_step(0.25_r, 0.0_r, 1.0_r);
    CHECK(quarter_value == Approx(0.15625_r).epsilon(real_epsilon));

    real_t mid_value;
    mid_value = smooth_step(0.5_r, 0.0_r, 1.0_r);
    CHECK(mid_value == Approx(0.5_r).epsilon(real_epsilon));

    real_t three_quarter_value;
    three_quarter_value = smooth_step(0.75_r, 0.0_r, 1.0_r);
    CHECK(three_quarter_value == Approx(0.84375_r).epsilon(real_epsilon));
}

TEST_CASE("degrees_to_radians", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3_r;

    CHECK(deg_to_rad(57.2958_r) == Approx(1.0_r).epsilon(real_epsilon));
    CHECK(deg_to_rad(90.0_r) == Approx(1.5708_r).epsilon(real_epsilon));
    CHECK(deg_to_rad(180.0_r) == Approx(3.14159_r).epsilon(real_epsilon));
    CHECK(deg_to_rad(270.0_r) == Approx(4.71239_r).epsilon(real_epsilon));
    CHECK(deg_to_rad(360.0_r) == Approx(6.28319_r).epsilon(real_epsilon));
}

TEST_CASE("radians_to_degrees", "[as_math]")
{
    constexpr real_t real_epsilon = 1e-3_r;

    CHECK(rad_to_deg(1.0_r) == Approx(57.2958_r).epsilon(real_epsilon));
    CHECK(rad_to_deg(1.5708_r) == Approx(90.0_r).epsilon(real_epsilon));
    CHECK(rad_to_deg(3.14159_r) == Approx(180.0_r).epsilon(real_epsilon));
    CHECK(rad_to_deg(4.71239_r) == Approx(270.0_r).epsilon(real_epsilon));
    CHECK(rad_to_deg(6.28319_r) == Approx(360.0_r).epsilon(real_epsilon));
}

TEST_CASE("snap", "[as_math]")
{
    {
        const float result = as::snap(4.0_r, 10.0_r);
        CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
    }

    {
        const float result = as::snap(6.0_r, 10.0_r);
        CHECK(result == Approx(10.0_r).epsilon(g_epsilon));
    }

    {
        const float result = as::snap(1.0_r, 2.0_r);
        CHECK(result == Approx(2.0_r).epsilon(g_epsilon));
    }

    {
        const float result = as::snap(0.99f, 2.0_r);
        CHECK(result == Approx(0.0_r).epsilon(g_epsilon));
    }

    {
        const float result = as::snap(22.0_r, 20.0_r);
        CHECK(result == Approx(20.0_r).epsilon(g_epsilon));
    }

    {
        const float result = as::snap(32.0_r, 20.0_r);
        CHECK(result == Approx(40.0_r).epsilon(g_epsilon));
    }
}

} // namespace unit_test

// explicit instantiations (for coverage)
template as::real_t as::smooth_step(as::real_t t, as::real_t v0, as::real_t v1);
