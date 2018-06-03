// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-math.hpp"
#include "src/math/as-quat.hpp"

TEST(as_quat, multiply_equal)
{
    as::quat_t q1{ 1.0f, 2.0f, 3.0f, 4.0f };
    as::quat_t q2{ 2.0f, 4.0f, 6.0f, 8.0f };

    q1 *= q2;

    as::quat_t q_sub = q2 - q1;
    AS_UNUSED(q_sub);

    glm::quat qq1{ 1.0f, 2.0f, 3.0f, 4.0f };
    glm::quat qq2{ 2.0f, 4.0f, 6.0f, 8.0f };

    qq1 *= qq2;

    as::quat_t neg_q = -q1;
    AS_UNUSED(neg_q);

    int i;
    i = 0;
    (void)i;

    //glm::quat_t a = qq1 * 5.0f;
    //glm::quat_t b = 5.0f * qq1;
}