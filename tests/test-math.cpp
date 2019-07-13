#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "as/as-math.hpp"

using namespace as;

TEST(as_math, smoothstep)
{
    constexpr real_t real_epsilon = 1e-3f;

    const real_t quarter_value  = as::smooth_step(0.25f, 0.0f, 1.0f);
    EXPECT_NEAR(quarter_value, 0.156f, real_epsilon);

    const real_t mid_value  = as::smooth_step(0.5f, 0.0f, 1.0f);
    EXPECT_NEAR(mid_value, 0.5f, real_epsilon);

    const real_t three_quarter_value  = as::smooth_step(0.75f, 0.0f, 1.0f);
    EXPECT_NEAR(three_quarter_value, 0.844f, real_epsilon);
}

TEST(as_math, degrees_to_radians)
{
    constexpr real_t real_epsilon = 1e6f;

    EXPECT_NEAR(as::deg_to_rad(57.2958f), 1.0f, real_epsilon);
    EXPECT_NEAR(as::deg_to_rad(90.0f), 1.5708f, real_epsilon);
    EXPECT_NEAR(as::deg_to_rad(180.0f), 3.14159f, real_epsilon);
    EXPECT_NEAR(as::deg_to_rad(270.0f), 4.71239f, real_epsilon);
    EXPECT_NEAR(as::deg_to_rad(360.0f), 6.28319f, real_epsilon);
}

TEST(as_math, radians_to_degrees)
{
    constexpr real_t real_epsilon = 1e6f;

    EXPECT_NEAR(as::rad_to_deg(1.0f), 57.2958f, real_epsilon);
    EXPECT_NEAR(as::rad_to_deg(1.5708f), 90.0f, real_epsilon);
    EXPECT_NEAR(as::rad_to_deg(3.14159f), 180.0f, real_epsilon);
    EXPECT_NEAR(as::rad_to_deg(4.71239f), 270.0f, real_epsilon);
    EXPECT_NEAR(as::rad_to_deg(6.28319f), 360.0f, real_epsilon);
}
