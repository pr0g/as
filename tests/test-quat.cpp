// gtest
#include "gtest/gtest.h"

// as
#include "as/as-math.hpp"
#include "as/as-quat.hpp"

TEST(as_quat, multiply_equal)
{
    as::quat_t q1{ 1.0f, 2.0f, 3.0f, 4.0f };
    as::quat_t q2{ 2.0f, 4.0f, 6.0f, 8.0f };

    q1 *= q2;

    as::quat_t q_sub = q2 - q1;
    (void)q_sub;

    as::quat_t neg_q = -q1;
    (void)neg_q;
}
