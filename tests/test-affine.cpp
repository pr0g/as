// gtest
#include "gtest/gtest.h"

#include "src/math/as-math-type-ops.hpp"
#include "src/math/as-affine-type.hpp"

TEST(as_affine, constructor)
{
    as::v3 pos = as::v3_zero();
    as::m33 rot = as::m33_rotation_zxy(0.0f, 0.0f, 0.0f);
    
    as::affine affine{ rot, pos };

    int i;
    i = 0;
}