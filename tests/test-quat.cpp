// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-math.hpp"
#include "src/math/as-quat.hpp"

// as-test
#include "as-math-output.hpp"

TEST(as_quat, multiply_equal)
{
    as::quat_t q1{ 1.0f, 2.0f, 3.0f, 4.0f };
    as::quat_t q2{ 2.0f, 4.0f, 6.0f, 8.0f };

    q1 *= q2;

    glm::quat qq1{ 1.0f, 2.0f, 3.0f, 4.0f };
    glm::quat qq2{ 2.0f, 4.0f, 6.0f, 8.0f };

    qq1 *= qq2;
    
    int i;
    i = 0;

    //glm::quat_t a = qq1 * 5.0f;
    //glm::quat_t b = 5.0f * qq1;
}