// gtest
#include "gtest/gtest.h"

#include "src/math/as-math-ops.hpp"
#include "src/math/as-affine.hpp"

TEST(as_affine_t, constructor)
{
    as::vec3_t pos = as::vec3::zero();
    as::mat33_t rot = as::mat33::rotation_zxy(0.0f, 0.0f, 0.0f);
    
    as::affine_t affine_t{ rot, pos };

    int i;
    i = 0;
    (void)i;
}