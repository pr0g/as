// gtest
#include "gtest/gtest.h"

// as
#include "as/as-math-ops.hpp"

TEST(as_point, copy_constructor){
    as::point2_t p2_a(1.0f, 5.0f);
    as::point2_t p2_b(p2_a);
}

TEST(as_point, point_sub) {
    as::point3_t a3( 10.0f, 0.0f, 10.0f);
    as::point3_t b3( 5.0f, 0.0f, 0.0f);

    as::vec3_t r3 = a3 - b3;

    as::point3_t end3 = b3 + r3;

    EXPECT_TRUE(as::point::equal(a3, end3));

    as::point2_t a2 = as::point2_t(end3.v.xy());
    as::point2_t b2 = as::point2_t(a3.v.xy());

    as::vec2_t r2 = a2 - b2;

    as::point2_t end2 = b2 + r2;

    EXPECT_TRUE(as::point::equal(end2, as::point2_t(end3.v.xy())));
}
