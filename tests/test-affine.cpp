// gtest
#include "gtest/gtest.h"

#include "src/math/as-affine.hpp"

TEST(as_affine, constructor)
{
    as::v3 pos = as::v3::zero();
    as::m33 rot = as::m33::rotation_zxy(0.0f, 0.0f, 0.0f);
    
    as::affine affine{ rot, pos };

    int i;
    i = 0;
}