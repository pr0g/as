// gtest
#include "gtest/gtest.h"

// as
#include "src/math/as-vec-type.hpp"
#include "src/math/as-point-type.hpp"

// as-test
#include "as-math-output.hpp"

TEST(as_point, copy_constructor){
    as::point2 p2_a(1.0f, 5.0f);
    as::point2 p2_b(p2_a);

    print_v2(p2_b.v);
}

TEST(as_point, point_sub) {
    as::p3 a3( 10.0f, 0.0f, 10.0f);
    as::p3 b3( 5.0f, 0.0f, 0.0f);

    as::v3 r3 = a3 - b3;

    as::p3 end3 = b3 + r3;

    print_v3(a3.v);
    print_v3(end3.v);

    EXPECT_TRUE(as::equal(a3, end3));

    as::p2 a2 = end3.xy;
    as::p2 b2 = a3.xy;

    as::v2 r2 = a2 - b2;

    as::p2 end2 = b2 + r2;

    EXPECT_TRUE(as::equal(end2, end3.xy));
}