#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "as/as-math-ops.hpp"

#include <memory>

using namespace as;

const real_t epsilon = std::numeric_limits<real_t>::epsilon();

TEST(as_vec, vec2_initialization)
{
    // default initialization
    {
        vec2_t vec2;
        (void)vec2;
    }

    // zero initialization
    {
        vec2_t vec2{};
        EXPECT_EQ(vec2.x, 0.0f);
        EXPECT_EQ(vec2.y, 0.0f);
    }

    // value initialization
    {
        vec2_t vec2 = vec2_t();
        EXPECT_EQ(vec2.x, 0.0f);
        EXPECT_EQ(vec2.y, 0.0f);
    }

    // direct initialization (braces)
    {
        vec2_t vec2{1.0f, 2.0f};
        EXPECT_EQ(vec2.x, 1.0f);
        EXPECT_EQ(vec2.y, 2.0f);
    }

    // direct initialization - single argument (braces)
    {
        vec2_t vec2{5.0f};
        EXPECT_EQ(vec2.x, 5.0f);
        EXPECT_EQ(vec2.y, 5.0f);
    }

    // direct initialization (parens)
    {
        vec2_t vec2(5.0f, 10.0f);
        EXPECT_EQ(vec2.x, 5.0f);
        EXPECT_EQ(vec2.y, 10.0f);
    }

    // direct initialization - single argument (parens)
    {
        vec2_t vec2;
        vec2 = vec2_t(5.0f);
        EXPECT_EQ(vec2.x, 5.0f);
        EXPECT_EQ(vec2.y, 5.0f);
    }

    // direct/copy initialization (braces)
    {
        vec2_t vec2 = vec2_t{3.0f, 4.0f};
        EXPECT_EQ(vec2.x, 3.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // direct/copy initialization (parens)
    {
        vec2_t vec2 = vec2_t(3.0f, 4.0f);
        EXPECT_EQ(vec2.x, 3.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        const real_t value { 123.0f };
        vec2_t vec2 = vec2_t{ value };
        EXPECT_EQ(vec2.x, 123.0f);
        EXPECT_EQ(vec2.y, 123.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        vec2_t vec2 = vec2_t(25.0f);
        EXPECT_EQ(vec2.x, 25.0f);
        EXPECT_EQ(vec2.y, 25.0f);
    }

    // assignment initialization - single argument (braces)
    {
        vec2_t vec2;
        vec2 = vec2_t{ 75.0f };
        EXPECT_EQ(vec2.x, 75.0f);
        EXPECT_EQ(vec2.y, 75.0f);
    }

    // direct + copy initialization
    {
        vec2_t vec2_a(300.0f, 400.0f);
        vec2_t vec2_b(vec2_a);

        EXPECT_EQ(vec2_b.x, 300.0f);
        EXPECT_EQ(vec2_b.y, 400.0f);
    }

    // direct + copy initialization (assignment)
    {
        vec2_t vec2_a(100.0f, 200.0f);
        vec2_t vec2_b = vec2_a;

        EXPECT_EQ(vec2_b.x, 100.0f);
        EXPECT_EQ(vec2_b.y, 200.0f);
    }

    // direct + copy initialization (assignment)
    {
        vec2_t vec2_a(500.0f, 600.0f);
        vec2_t vec2_b;

        vec2_b = vec2_a;

        EXPECT_EQ(vec2_b.x, 500.0f);
        EXPECT_EQ(vec2_b.y, 600.0f);
    }
}

TEST(as_vec, vec3_initialization)
{
    // default initialization
    {
        vec3_t vec3;
        (void)vec3;
    }

    // zero initialization
    {
        vec3_t vec3{};
        EXPECT_EQ(vec3.x, 0.0f);
        EXPECT_EQ(vec3.y, 0.0f);
        EXPECT_EQ(vec3.z, 0.0f);
    }

    // value initialization
    {
        vec3_t vec3 = vec3_t();
        EXPECT_EQ(vec3.x, 0.0f);
        EXPECT_EQ(vec3.y, 0.0f);
        EXPECT_EQ(vec3.z, 0.0f);
    }

    // direct initialization (braces)
    {
        vec3_t vec3{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct initialization (parens)
    {
        vec3_t vec3(5.0f, 10.0f, 15.0f);
        EXPECT_EQ(vec3.x, 5.0f);
        EXPECT_EQ(vec3.y, 10.0f);
        EXPECT_EQ(vec3.z, 15.0f);
    }

    // direct/copy initialization (braces)
    {
        vec3_t vec3 = vec3_t{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct/copy initialization (parens)
    {
        vec3_t vec3 = vec3_t(3.0f, 4.0f, 5.0f);
        EXPECT_EQ(vec3.x, 3.0f);
        EXPECT_EQ(vec3.y, 4.0f);
        EXPECT_EQ(vec3.z, 5.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        vec3_t vec3 = vec3_t{ 50.0f };
        EXPECT_EQ(vec3.x, 50.0f);
        EXPECT_EQ(vec3.y, 50.0f);
        EXPECT_EQ(vec3.z, 50.0f);
    }

    // assignment initialization - single argument (braces)
    {
        vec3_t vec3;
        vec3 = vec3_t{ 50.0f };
        EXPECT_EQ(vec3.x, 50.0f);
        EXPECT_EQ(vec3.y, 50.0f);
        EXPECT_EQ(vec3.z, 50.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        vec3_t vec3 = vec3_t(25.0f);
        EXPECT_EQ(vec3.x, 25.0f);
        EXPECT_EQ(vec3.y, 25.0f);
        EXPECT_EQ(vec3.z, 25.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        vec3_t vec3 = vec3_t{vec2_t{1.0f, 2.0f}, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        vec2_t vec2 = vec2_t(1.0f, 2.0f);
        vec3_t vec3 = vec3_t(vec2, 3.0f);
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct + copy initialization
    {
        vec3_t vec3_a(100.0f, 200.0f, 300.0f);
        vec3_t vec3_b(vec3_a);

        EXPECT_EQ(vec3_b.x, 100.0f);
        EXPECT_EQ(vec3_b.y, 200.0f);
        EXPECT_EQ(vec3_b.z, 300.0f);
    }

    // direct + copy initialization
    {
        vec3_t vec3_a(400.0f, 500.0f, 600.0f);
        vec3_t vec3_b = vec3_a;

        EXPECT_EQ(vec3_b.x, 400.0f);
        EXPECT_EQ(vec3_b.y, 500.0f);
        EXPECT_EQ(vec3_b.z, 600.0f);
    }

    // direct + copy initialization (assignment)
    {
        vec3_t vec3_a(500.0f, 600.0f, 700.0f);
        vec3_t vec3_b;

        vec3_b = vec3_a;

        EXPECT_EQ(vec3_b.x, 500.0f);
        EXPECT_EQ(vec3_b.y, 600.0f);
        EXPECT_EQ(vec3_b.z, 700.0f);
    }
}

TEST(as_vec, vec4_initialization)
{
    // default initialization
    {
        vec4_t vec4;
        (void)vec4;
    }

    // zero initialization
    {
        vec4_t vec4{};
        EXPECT_EQ(vec4.x, 0.0f);
        EXPECT_EQ(vec4.y, 0.0f);
        EXPECT_EQ(vec4.z, 0.0f);
        EXPECT_EQ(vec4.w, 0.0f);
    }

    // value initialization
    {
        vec4_t vec4 = vec4_t();
        EXPECT_EQ(vec4.x, 0.0f);
        EXPECT_EQ(vec4.y, 0.0f);
        EXPECT_EQ(vec4.z, 0.0f);
        EXPECT_EQ(vec4.w, 0.0f);
    }

    // direct initialization (braces)
    {
        vec4_t vec4{1.0f, 2.0f, 3.0f, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct initialization (parens)
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization (braces)
    {
        vec4_t vec4 = vec4_t{3.0f, 4.0f, 5.0f, 6.0f};
        EXPECT_EQ(vec4.x, 3.0f);
        EXPECT_EQ(vec4.y, 4.0f);
        EXPECT_EQ(vec4.z, 5.0f);
        EXPECT_EQ(vec4.w, 6.0f);
    }

    // direct/copy initialization (parens)
    {
        vec4_t vec4 = vec4_t(3.0f, 4.0f, 5.0f, 6.0f);
        EXPECT_EQ(vec4.x, 3.0f);
        EXPECT_EQ(vec4.y, 4.0f);
        EXPECT_EQ(vec4.z, 5.0f);
        EXPECT_EQ(vec4.w, 6.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        vec4_t vec4 = vec4_t{50.0f};
        EXPECT_EQ(vec4.x, 50.0f);
        EXPECT_EQ(vec4.y, 50.0f);
        EXPECT_EQ(vec4.z, 50.0f);
        EXPECT_EQ(vec4.w, 50.0f);
    }

    // assignment initialization - single argument (braces)
    {
        vec4_t vec4;
        vec4 = vec4_t{ 99.0f };
        EXPECT_EQ(vec4.x, 99.0f);
        EXPECT_EQ(vec4.y, 99.0f);
        EXPECT_EQ(vec4.z, 99.0f);
        EXPECT_EQ(vec4.w, 99.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        vec4_t vec4 = vec4_t(25.0f);
        EXPECT_EQ(vec4.x, 25.0f);
        EXPECT_EQ(vec4.y, 25.0f);
        EXPECT_EQ(vec4.z, 25.0f);
        EXPECT_EQ(vec4.w, 25.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        vec4_t vec4 = vec4_t{vec3_t{1.0f, 2.0f, 3.0f}, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        vec4_t vec4 = vec4_t(vec3_t(1.0f, 2.0f, 3.0f), 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        vec4_t vec4 = vec4_t{vec2_t{1.0f, 2.0f}, vec2_t{3.0f, 4.0f}};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        vec4_t vec4 = vec4_t(vec2_t(1.0f, 2.0f), vec2_t(3.0f, 4.0f));
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - triple argument (braces)
    {
        vec4_t vec4 = vec4_t{vec2_t{1.0f, 2.0f}, 3.0f, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - triple argument (parens)
    {
        vec4_t vec4 = vec4_t(vec2_t(1.0f, 2.0f), 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct + copy initialization
    {
        vec4_t vec4_a(100.0f, 200.0f, 300.0f, 400.0f);
        vec4_t vec4_b(vec4_a);

        EXPECT_EQ(vec4_b.x, 100.0f);
        EXPECT_EQ(vec4_b.y, 200.0f);
        EXPECT_EQ(vec4_b.z, 300.0f);
        EXPECT_EQ(vec4_b.w, 400.0f);
    }

    // direct + copy initialization
    {
        vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        vec4_t vec4_b = vec4_a;

        EXPECT_EQ(vec4_b.x, 500.0f);
        EXPECT_EQ(vec4_b.y, 600.0f);
        EXPECT_EQ(vec4_b.z, 700.0f);
        EXPECT_EQ(vec4_b.w, 800.0f);
    }

    // direct + copy initialization (assignment)
    {
        vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        vec4_t vec4_b;

        vec4_b = vec4_a;

        EXPECT_EQ(vec4_b.x, 500.0f);
        EXPECT_EQ(vec4_b.y, 600.0f);
        EXPECT_EQ(vec4_b.z, 700.0f);
        EXPECT_EQ(vec4_b.w, 800.0f);
    }
}

TEST(as_vec, vec2_accessors)
{
    // member and subscript operator - zero initializer
    {
        vec2_t vec2{};
        EXPECT_EQ(vec2.x, vec2[0]);
        EXPECT_EQ(vec2.y, vec2[1]);
    }

    // member and subscript operator - explicit construction
    {
        vec2_t vec2(1.0f, 2.0f);
        EXPECT_EQ(vec2.x, vec2[0]);
        EXPECT_EQ(vec2.y, vec2[1]);
    }

    // member pointer and subscript operator - explicit construction
    {
        vec2_t vec2(1.0f, 2.0f);
        EXPECT_EQ(vec2.elems()[0], vec2[0]);
        EXPECT_EQ(vec2.elems()[1], vec2[1]);
    }

    // member and const subscript operator - explicit construction
    {
        vec2_t vec2(1.0f, 2.0f);
        const real_t& x = vec2[0];
        const real_t& y = vec2[1];

        EXPECT_FLOAT_EQ(vec2.x, x);
        EXPECT_FLOAT_EQ(vec2.y, y);
    }
}

TEST(as_vec, vec3_accessors)
{
    // member and subscript operator - zero initializer
    {
        vec3_t vec3{};
        EXPECT_EQ(vec3.x, vec3[0]);
        EXPECT_EQ(vec3.y, vec3[1]);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // member and subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        EXPECT_EQ(vec3.x, vec3[0]);
        EXPECT_EQ(vec3.y, vec3[1]);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // member and subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        EXPECT_EQ(vec3.xy()[0], vec3.x);
        EXPECT_EQ(vec3.xy()[1], vec3.y);
        EXPECT_EQ(vec3.xy().x, vec3.x);
        EXPECT_EQ(vec3.xy().y, vec3.y);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // member pointer and subscript operator - explicit construction
    {
        vec3_t vec3(2.0f, 4.0f, 6.0f);
        EXPECT_EQ(vec3.elems()[0], vec3[0]);
        EXPECT_EQ(vec3.elems()[1], vec3[1]);
        EXPECT_EQ(vec3.elems()[2], vec3[2]);
    }

    // member and const subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        const real_t& x = vec3[0];
        const real_t& y = vec3[1];
        const real_t& z = vec3[2];

        EXPECT_FLOAT_EQ(vec3.x, x);
        EXPECT_FLOAT_EQ(vec3.y, y);
        EXPECT_FLOAT_EQ(vec3.z, z);
    }
}

TEST(as_vec, vec4_accessors)
{
    // member and subscript operator - zero initializer
    {
        vec4_t vec4{};
        EXPECT_EQ(vec4.x, vec4[0]);
        EXPECT_EQ(vec4.y, vec4[1]);
        EXPECT_EQ(vec4.z, vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // member and subscript operator - explicit construction
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, vec4[0]);
        EXPECT_EQ(vec4.y, vec4[1]);
        EXPECT_EQ(vec4.z, vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // member and subscript operator - explicit construction
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.xy()[0], vec4[0]);
        EXPECT_EQ(vec4.xy()[1], vec4[1]);
        EXPECT_EQ(vec4.zw()[0], vec4[2]);
        EXPECT_EQ(vec4.zw()[1], vec4[3]);
        EXPECT_EQ(vec4.xyz()[0], vec4[0]);
        EXPECT_EQ(vec4.xyz()[1], vec4[1]);
        EXPECT_EQ(vec4.xyz()[2], vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // member pointer and subscript operator - explicit construction
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.elems()[0], vec4[0]);
        EXPECT_EQ(vec4.elems()[1], vec4[1]);
        EXPECT_EQ(vec4.elems()[2], vec4[2]);
        EXPECT_EQ(vec4.elems()[3], vec4[3]);
    }
}

TEST(as_vec, vec2_vec3_vec4_accessors)
{
    vec2_t vec2(1.0f, 2.0f);
    vec3_t vec3(vec2, 3.0f);

    vec4_t vec4_a(vec2, 3.0f, 4.0f);
    vec4_t vec4_b(vec2, vec2);
    vec4_t vec4_c(vec3, 4.0f);

    // member accessors
    EXPECT_EQ(vec4_a.x, vec2.x);
    EXPECT_EQ(vec4_a.y, vec2.y);

    EXPECT_EQ(vec4_b.x, vec2.x);
    EXPECT_EQ(vec4_b.y, vec2.y);
    EXPECT_EQ(vec4_b.z, vec2.x);
    EXPECT_EQ(vec4_b.w, vec2.y);

    EXPECT_EQ(vec4_c.x, vec2.x);
    EXPECT_EQ(vec4_c.y, vec2.y);
    EXPECT_EQ(vec4_c.z, vec4_a.z);
    EXPECT_EQ(vec4_c.w, vec4_a.w);
}

TEST(as_vec, const_elem_access)
{
    using ::testing::ElementsAreArray;

    const vec_t<real_t, 5> vec5(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);

    const real_t elem_0 = vec5[0];
    const real_t elem_1 = vec5[1];
    const real_t elem_2 = vec5[2];
    const real_t elem_3 = vec5[3];
    const real_t elem_4 = vec5[4];

    const real_t vec_arr[] = { elem_0, elem_1, elem_2, elem_3, elem_4 };
    EXPECT_THAT(vec_arr, ElementsAreArray(vec5.elems(), 5));
}

TEST(as_vec, const_elem_access_v2_v3_v4)
{
    using ::testing::ElementsAreArray;

    {
        const vec2_t vec2(15.0f, 30.0f);

        const real_t elem_0 = vec2[0];
        const real_t elem_1 = vec2[1];

        const real_t vec_arr[] = { elem_0, elem_1 };
        EXPECT_THAT(vec_arr, ElementsAreArray(vec2.elems(), 2));
    }

    {
        const vec3_t vec3(2.0f, 3.0f, 4.0f);

        const real_t elem_0 = vec3[0];
        const real_t elem_1 = vec3[1];
        const real_t elem_2 = vec3[2];

        const real_t vec_arr[] = { elem_0, elem_1, elem_2 };
        EXPECT_THAT(vec_arr, ElementsAreArray(vec3.elems(), 3));
    }

    {
        vec4_t vec4;
        vec4 = vec4_t(10.0f, 20.0f, 30.0f, 40.0f);

        const real_t elem_0 = vec4[0];
        const real_t elem_1 = vec4[1];
        const real_t elem_2 = vec4[2];
        const real_t elem_3 = vec4[3];

        const real_t vec_arr[] = { elem_0, elem_1, elem_2, elem_3 };
        EXPECT_THAT(vec_arr, ElementsAreArray(vec4.elems(), 4));
    }
}

TEST(as_vec, vec_size)
{
    size_t vec2_size = vec2_t::size;
    vec2_t vec2;
    size_t vec2_inst_size = vec::size(vec2);
    EXPECT_EQ(vec2_size, static_cast<size_t>(2));
    EXPECT_EQ(vec2_inst_size, vec2_size);

    size_t vec3_size = vec3_t::size;
    vec3_t vec3;
    size_t vec3_inst_size = vec::size(vec3);
    EXPECT_EQ(vec3_size, static_cast<size_t>(3));
    EXPECT_EQ(vec3_inst_size, vec3_size);

    size_t vec4_size = vec4_t::size;
    vec4_t vec4;
    size_t vec4_inst_size = vec::size(vec4);
    EXPECT_EQ(vec4_size, static_cast<size_t>(4));
    EXPECT_EQ(vec4_inst_size, vec4_size);

    using short7 = vec_t<short, 7>;
    short7 vec_short7;
    size_t vec_short7_inst_size = vec::size(vec_short7);
    size_t short7_size = short7::size;
    EXPECT_EQ(short7_size, static_cast<size_t>(7));
    EXPECT_EQ(vec_short7_inst_size, short7_size);

    using int5 = vec_t<int, 5>;
    int5 vec_short5;
    size_t vec_short5_inst_size = vec::size(vec_short5);
    size_t int5_size = int5::size;
    EXPECT_EQ(int5_size, static_cast<size_t>(5));
    EXPECT_EQ(vec_short5_inst_size, int5_size);
}

TEST(as_vec, vec_data)
{
    // data mutable
    {
        vec2_t vec2(5.0f, 10.0f);
        real_t *data = vec::data(vec2);

        EXPECT_EQ(data[0], 5.0f);
        EXPECT_EQ(data[1], 10.0f);
    }

    // data const
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        const real_t* data = vec::const_data(vec4);

        EXPECT_EQ(data[0], 1.0f);
        EXPECT_EQ(data[1], 2.0f);
        EXPECT_EQ(data[2], 3.0f);
        EXPECT_EQ(data[3], 4.0f);
    }

    // r-value - will not compile
    {
        // data(vec3_t(1.0f, 2.0f, 3.0f));
    }

    // data mutable
    {
        vec2_t vec2(20.0f, 40.0f);
        real_t* data = vec::data(vec2);

        EXPECT_EQ(data[0], 20.0f);
        EXPECT_EQ(data[1], 40.0f);

        data[0] = 100.0f;
        data[1] = 200.0f;

        EXPECT_EQ(vec2.x, 100.0f);
        EXPECT_EQ(vec2.y, 200.0f);
    }

    // generic data mutable
    {
        using int5 = vec_t<int, 5>;
        int5 int5_vec{ 11, 12, 13, 14, 15 };
        int* data = vec::data(int5_vec);

        EXPECT_EQ(int5_vec[0], 11);
        EXPECT_EQ(int5_vec[1], 12);
        EXPECT_EQ(int5_vec[2], 13);
        EXPECT_EQ(int5_vec[3], 14);
        EXPECT_EQ(int5_vec[4], 15);

        data[3] = 22;

        EXPECT_EQ(int5_vec[3], 22);
    }

    // data const
    {
        using short7 = vec_t<short, 7>;
        short7 short7_vec{
            (short)11, (short)22, (short)33, (short)44,
            (short)55, (short)66, (short)77 };
        const short* data = vec::const_data(short7_vec);

        EXPECT_EQ(short7_vec[0], 11);
        EXPECT_EQ(short7_vec[1], 22);
        EXPECT_EQ(short7_vec[2], 33);
        EXPECT_EQ(short7_vec[3], 44);
        EXPECT_EQ(short7_vec[4], 55);
        EXPECT_EQ(short7_vec[5], 66);
        EXPECT_EQ(short7_vec[6], 77);

        for (size_t i = 0; i < short7::size; ++i) {
            EXPECT_EQ(short7_vec[i], data[i]);
        }
    }
}

TEST(as_vec, vec_make_from_arr)
{
    // generic make_from_arr vec2_t
    {
        real_t data[2] = { 2.0f, 4.0f };
        vec2_t vec2 = vec::from_arr(data);

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);

        // won't compile (array length 2 to vec3_t)
        // vec3_t vec3 = make_from(data);
    }

    // generic make_from_arr vec3_t
    {
        real_t data[3] = { 1.0f, 2.0f, 3.0f };
        vec3_t vec3 = vec::from_arr(data);

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // generic make_from_arr <char, 6>
    {
        char data[6] = { 11, 12, 13, 14, 15, 16 };
        vec_t<char, 6> char_6 = vec::from_arr(data);

        EXPECT_EQ(char_6[0], 11);
        EXPECT_EQ(char_6[1], 12);
        EXPECT_EQ(char_6[2], 13);
        EXPECT_EQ(char_6[3], 14);
        EXPECT_EQ(char_6[4], 15);
        EXPECT_EQ(char_6[5], 16);
    }

    // vec2::make_from_arr
    {
        real_t data[2] = { 2.0f, 4.0f };
        vec2_t vec2 = vec2::from_arr(data);

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // vec3_make_from_arr
    {
        real_t data[3] = { 1.0f, 2.0f, 3.0f };
        vec3_t vec3 = vec3::from_arr(data);

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // vec4_make_from_arr
    {
        real_t data[4] = { 4.0f, 8.0f, 12.0f, 16.0f };
        vec4_t vec4 = vec4::from_arr(data);

        EXPECT_EQ(vec4.x, 4.0f);
        EXPECT_EQ(vec4.y, 8.0f);
        EXPECT_EQ(vec4.z, 12.0f);
        EXPECT_EQ(vec4.w, 16.0f);
    }
}

TEST(as_vec, vec_make_from_ptr)
{
    // generic make_from_ptr vec2_t
    {
        std::unique_ptr<real_t[]> data = std::make_unique<real_t[]>(2);
        data[0] = 2.0f;
        data[1] = 4.0f;
        vec2_t vec2 = vec::from_ptr<real_t, 2>(data.get());

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // generic make_from_ptr vec3_t
    {
        std::unique_ptr<real_t[]> data = std::make_unique<real_t[]>(3);
        data[0] = 1.0f;
        data[1] = 2.0f;
        data[2] = 3.0f;
        vec3_t vec3 = vec::from_ptr<real_t, 3>(data.get());

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // generic make_from_ptr <char, 6>
    {
        std::unique_ptr<char[]> data = std::make_unique<char[]>(6);
        data[0] = 11;
        data[1] = 12;
        data[2] = 13;
        data[3] = 14;
        data[4] = 15;
        data[5] = 16;
        vec_t<char, 6> char_6 = vec::from_ptr<char, 6>(data.get());

        EXPECT_EQ(char_6[0], 11);
        EXPECT_EQ(char_6[1], 12);
        EXPECT_EQ(char_6[2], 13);
        EXPECT_EQ(char_6[3], 14);
        EXPECT_EQ(char_6[4], 15);
        EXPECT_EQ(char_6[5], 16);
    }

    // vec2::make_from_ptr
    {
        std::unique_ptr<real_t[]> data = std::make_unique<real_t[]>(2);
        data[0] = 2.0f;
        data[1] = 4.0f;
        vec2_t vec2 = vec2::from_ptr(data.get());

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // vec3_make_from_ptr
    {
        std::unique_ptr<real_t[]> data = std::make_unique<real_t[]>(3);
        data[0] = 1.0f;
        data[1] = 2.0f;
        data[2] = 3.0f;
        vec3_t vec3 = vec3::from_ptr(data.get());

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // vec4_make_from_ptr
    {
        std::unique_ptr<real_t[]> data = std::make_unique<real_t[]>(4);
        data[0] = 4.0f;
        data[1] = 8.0f;
        data[2] = 12.0f;
        data[3] = 16.0f;
        vec4_t vec4 = vec4::from_ptr(data.get());

        EXPECT_EQ(vec4.x, 4.0f);
        EXPECT_EQ(vec4.y, 8.0f);
        EXPECT_EQ(vec4.z, 12.0f);
        EXPECT_EQ(vec4.w, 16.0f);
    }

    // generic type check
    {
        std::unique_ptr<double[]> data = std::make_unique<double[]>(2);
        data[0] = 2.0f;
        data[1] = 4.0f;
        // does not compile - types do not match
        // vec_t<char, 2> char_2 = from_ptr<char, 2>(data.get());
        // vec2_t vec2 = from_ptr<float, 2>(data.get());
        vec_t<double, 2> vec2 = vec::from_ptr<double, 2>(data.get());
        (void)vec2;
    }
}

TEST(as_vec, addition)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '+'
    {
        vec5_t vec = vec5_t{10.0f, 20.0f, 30.0f, 40.0f, 50.0f} + vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f};
        EXPECT_TRUE(vec::equal(vec, vec5_t(50.0f, 50.0f, 50.0f, 50.0f, 50.0f))) << "vec operator '+' invalid";
    }

    // vec_t operator '+='
    {
        vec5_t vec1(10.0f, 20.0f, 30.0f, 40.0f, 50.0f);
        vec1 += vec5_t(25.0f, 15.0f, 5.0f, 10.0f, 1.0f);
        EXPECT_TRUE(vec::equal(vec1, vec5_t(35.0f, 35.0f, 35.0f, 50.0f, 51.0f))) << "vec operator '+=' invalid";
    }
}

TEST(as_vec, addition_vec3)
{
    // vec3_t operator '+'
    {
        vec3_t vec = vec3_t{10.0f, 20.0f, 30.0f} + vec3_t{20.0f, 10.0f, 0.0f};
        EXPECT_TRUE(vec::equal(vec, vec3_t(30.0f, 30.0f, 30.0f))) << "vec operator '+' invalid";
    }

    // vec3_t operator '+='
    {
        vec3_t vec1(10.0f, 20.0f, 30.0f);
        vec1 += vec3_t(25.0f, 15.0f, 5.0f);
        EXPECT_TRUE(vec::equal(vec1, vec3_t(35.0f, 35.0f, 35.0f))) << "vec operator '+=' invalid";
    }
}

TEST(as_vec, substraction)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '-'
    {
        vec5_t vec = vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f} - vec5_t{10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
        EXPECT_TRUE(vec::equal(vec, vec5_t(30.0f, 10.0f, -10.0f, -30.0f, -50.0f))) << "vec operator '-' invalid";
    }

    // vec_t operator '-='
    {
        vec5_t vec1(10.0f, 20.0f, 30.0f, 40.0f, 50.0f);
        vec1 -= vec5_t(25.0f, 15.0f, 5.0f, 10.0f, 1.0f);
        EXPECT_TRUE(vec::equal(vec1, vec5_t(-15.0f, 5.0f, 25.0f, 30.0f, 49.0f))) << "vec operator '-=' invalid";
    }
}

TEST(as_vec, substraction_vec3)
{
    // vec3_t operator '-'
    {
        vec3_t vec = vec3_t{40.0f, 30.0f, 20.0f} - vec3_t{10.0f, 20.0f, 30.0f};
        EXPECT_TRUE(vec::equal(vec, vec3_t(30.0f, 10.0f, -10.0f))) << "vec operator '-' invalid";
    }

    // vec3_t operator '-='
    {
        vec3_t vec1(10.0f, 20.0f, 30.0f);
        vec1 -= vec3_t(25.0f, 15.0f, 5.0f);
        EXPECT_TRUE(vec::equal(vec1, vec3_t(-15.0f, 5.0f, 25.0f))) << "vec operator '-=' invalid";
    }
}

TEST(as_vec, negation)
{
    using vec5_t = vec_t<real_t, 5>;

    vec5_t vec = vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f};
    vec5_t neg_vec = -vec;
    EXPECT_TRUE(vec::equal(neg_vec, vec5_t(-40.0f, -30.0f, -20.0f, -10.0f, -0.0f)));
}

TEST(as_vec, negation_vec3)
{
    vec3_t vec = vec3_t{20.0f, 10.0f, 0.0f};
    vec3_t neg_vec = -vec;
    EXPECT_TRUE(vec::equal(neg_vec, vec3_t(-20.0f, -10.0f, -0.0f)));
}

TEST(as_vec, multiplication_scalar)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '*'
    {
        vec5_t vec = 5.0f * vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        EXPECT_TRUE(vec::equal(vec, vec5_t(250.0f, 200.0f, 125.0, 100.0f, 50.0f)));
    }

    // vec_t operator '*='
    {
        vec5_t vec = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        vec *= 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec5_t(250.0f, 200.0f, 125.0, 100.0f, 50.0f)));
    }
}

TEST(as_vec, multiplication_scalar_vec3)
{
    // vec3_t operator '*'
    {
        vec3_t vec = 5.0f * vec3_t{50.0f, 40.0f, 25.0f};
        EXPECT_TRUE(vec::equal(vec, vec3_t(250.0f, 200.0f, 125.0)));
    }

    // vec3_t operator '*='
    {
        vec3_t vec = vec3_t{50.0f, 40.0f, 25.0f};
        vec *= 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec3_t(250.0f, 200.0f, 125.0)));
    }
}

TEST(as_vec, multiplication_vector)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '*'
    {
        vec5_t vec = vec5_t{ 2.0f, 3.0f, 4.0f, 5.0f, 0.5f } * vec5_t{ 50.0f, 40.0f, 25.0f, 20.0f, 10.0f };
        EXPECT_TRUE(vec::equal(vec, vec5_t(100.0f, 120.0f, 100.0f, 100.0f, 5.0f)));
    }

    // vec_t operator '*='
    {
        vec5_t vec1 = vec5_t{ 2.0f, 3.0f, 4.0f, 5.0f, 0.5f };
        vec5_t vec2 = vec5_t{ 50.0f, 40.0f, 25.0f, 20.0f, 10.0f };
        vec1 *= vec2;
        EXPECT_TRUE(vec::equal(vec1, vec5_t(100.0f, 120.0f, 100.0f, 100.0f, 5.0f)));
    }
}

TEST(as_vec, multiplication_vector_vec3)
{
    // vec_t operator '*'
    {
        vec3_t vec = vec3_t{ 0.5f, 3.0f, 4.0f } * vec3_t{ 50.0f, 40.0f, 25.0f };
        EXPECT_TRUE(vec::equal(vec, vec3_t(25.0f, 120.0f, 100.0f)));
    }

    // vec_t operator '*='
    {
        vec3_t vec1 = vec3_t{ 0.5f, 3.0f, 4.0f };
        vec3_t vec2 = vec3_t{ 50.0f, 40.0f, 25.0f };
        vec1 *= vec2;
        EXPECT_TRUE(vec::equal(vec1, vec3_t(25.0f, 120.0f, 100.0f)));
    }
}

TEST(as_vec, divide_scalar)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '/'
    {
        vec5_t vec = vec5_t{ 50.0f, 40.0f, 25.0f, 20.0f, 10.0f } / 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec5_t(10.0f, 8.0f, 5.0f, 4.0f, 2.0f)));
    }

    // vec_t operator '/='
    {
        vec5_t vec = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        vec /= 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec5_t(10.0f, 8.0f, 5.0f, 4.0f, 2.0f)));
    }
}

TEST(as_vec, divide_scalar_vec3)
{
    // vec_t operator '/'
    {
        vec3_t vec = vec3_t{ 50.0f, 40.0f, 25.0f } / 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec3_t(10.0f, 8.0f, 5.0f)));
    }

    // vec_t operator '/='
    {
        vec3_t vec = vec3_t{50.0f, 40.0f, 25.0f};
        vec /= 5.0f;
        EXPECT_TRUE(vec::equal(vec, vec3_t(10.0f, 8.0f, 5.0f)));
    }
}

TEST(as_vec, divide_vector)
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '/'
    {
        vec5_t vec = vec5_t{ 33.0f, 48.0f, 10.0f, 120.0f, 2.0f } / vec5_t{ 3.0f, 6.0f, 2.0f, 3.0f, 0.5f };
        EXPECT_TRUE(vec::equal(vec, vec5_t(11.0f, 8.0f, 5.0f, 40.0f, 4.0f)));
    }

    // vec_t operator '/='
    {
        vec5_t vec1 = vec5_t{ 33.0f, 48.0f, 10.0f, 120.0f, 2.0f };
        vec5_t vec2 = vec5_t{ 3.0f, 6.0f, 2.0f, 3.0f, 0.5f };
        vec1 /= vec2;
        EXPECT_TRUE(vec::equal(vec1, vec5_t(11.0f, 8.0f, 5.0f, 40.0f, 4.0f)));
    }
}

TEST(as_vec, divide_vector_vec3)
{
    // vec_t operator '/'
    {
        vec3_t vec = vec3_t{ 33.0f, 48.0f, 10.0f } / vec3_t{ 3.0f, 6.0f, 2.0f };
        EXPECT_TRUE(vec::equal(vec, vec3_t(11.0f, 8.0f, 5.0f)));
    }

    // vec_t operator '/='
    {
        vec3_t vec1 = vec3_t{ 33.0f, 48.0f, 10.0f };
        vec3_t vec2 = vec3_t{ 3.0f, 6.0f, 2.0f };
        vec1 /= vec2;
        EXPECT_TRUE(vec::equal(vec1, vec3_t(11.0f, 8.0f, 5.0f)));
    }
}

TEST(as_vec, dot)
{
    // note: comparison values calculated using - http://calculator.vhex.net
    {
        vec3_t vec1(1.0f, 2.0f, 3.0f);
        vec3_t vec2(4.0f, 5.0f, 6.0f);

        real_t dot_result = vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, 32.0f, epsilon) << "vec::dot failed";
    }

    {
        vec3_t vec1(-50.0f, 20.0f, 9.0f);
        vec3_t vec2(-1.0f, -7.0f, 4.0f);

        real_t dot_result = vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, -54.0f, epsilon) << "vec::dot failed";
    }

    {
        vec3_t vec1(-27.367f, 0.1165f, 0.921f);
        vec3_t vec2(-123.456f, -7.732f, 2.491f);

        real_t dot_result = vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, 3380.013785f, epsilon) << "vec::dot failed";
    }
}

TEST(as_vec, cross)
{
    // note: comparison values calculated using https://www.symbolab.com/solver/vector-cross-product-calculator
    {
        vec3_t vec1(1.0f, 2.0f, 3.0f);
        vec3_t vec2(4.0f, 5.0f, 6.0f);

        vec3_t cross_result = vec3::cross(vec1, vec2);
        EXPECT_NEAR(cross_result.x, -3.0f, epsilon) << "vec::cross failed";
        EXPECT_NEAR(cross_result.y, 6.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result.z, -3.0f, epsilon) << "vec::cross failed";;
    }

    {
        vec3_t vec1(1.0f, 0.0f, 0.0f);
        vec3_t vec2(0.0f, 1.0f, 0.0f);

        vec3_t cross_result1 = vec3::cross(vec1, vec2);
        EXPECT_NEAR(cross_result1.x, 0.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result1.y, 0.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result1.z, 1.0f, epsilon) << "vec::cross failed";;

        vec3_t cross_result2 = vec3::cross(vec2, vec1);
        EXPECT_NEAR(cross_result2.x, 0.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result2.y, 0.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result2.z, -1.0f, epsilon) << "vec::cross failed";;
    }

    {
        vec3_t vec1(0.0f, 5.0f, 0.0f);
        vec3_t vec2(0.0f, 0.0f, 12.0f);

        vec3_t cross_result = vec3::cross(vec1, vec2);
        EXPECT_NEAR(cross_result.x, 60.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result.y, 0.0f, epsilon) << "vec::cross failed";;
        EXPECT_NEAR(cross_result.z, 0.0f, epsilon) << "vec::cross failed";;
    }

    {
        vec3_t x(1.0f, 0.0f, 0.0f);
        vec3_t y(0.0f, 1.0f, 0.0f);
        vec3_t z(0.0f, 0.0f, 1.0f);

        vec3_t cross_result1 = vec3::cross(x, y);
        EXPECT_NEAR(cross_result1.z, 1.0f, epsilon) << "vec::cross failed";;

        vec3_t cross_result2 = vec3::cross(y, z);
        EXPECT_NEAR(cross_result2.x, 1.0f, epsilon) << "vec::cross failed";;

        vec3_t cross_result3 = vec3::cross(z, x);
        EXPECT_NEAR(cross_result3.y, 1.0f, epsilon) << "vec::cross failed";;
    }
}

TEST(as_vec, right_and_up)
{
    {
        vec3_t dir(0.0f, 0.0f, 1.0f);

        vec3_t across_lh, up_lh;
        vec3::right_and_up_lh(dir, across_lh, up_lh);

        EXPECT_NEAR(across_lh.x, 1.0f, epsilon) << "vec3::right_and_up_lh failed";
        EXPECT_NEAR(across_lh.y, 0.0f, epsilon) << "vec3::right_and_up_lh failed";
        EXPECT_NEAR(across_lh.z, 0.0f, epsilon) << "vec3::right_and_up_lh failed";

        EXPECT_NEAR(up_lh.x, 0.0f, epsilon) << "vec3::right_and_up_lh failed";
        EXPECT_NEAR(up_lh.y, 1.0f, epsilon) << "vec3::right_and_up_lh failed";
        EXPECT_NEAR(up_lh.z, 0.0f, epsilon) << "vec3::right_and_up_lh failed";
    }

    {
        vec3_t dir(0.0f, 0.0f, 1.0f);

        vec3_t across_rh, up_rh;
        vec3::right_and_up_rh(dir, across_rh, up_rh);

        EXPECT_NEAR(across_rh.x, -1.0f, epsilon) << "vec3::right_and_up_rh failed";
        EXPECT_NEAR(across_rh.y, 0.0f, epsilon) << "vec3::right_and_up_rh failed";
        EXPECT_NEAR(across_rh.z, 0.0f, epsilon) << "vec3::right_and_up_rh failed";

        EXPECT_NEAR(up_rh.x, 0.0f, epsilon) << "vec3::right_and_up_rh failed";
        EXPECT_NEAR(up_rh.y, 1.0f, epsilon) << "vec3::right_and_up_rh failed";
        EXPECT_NEAR(up_rh.z, 0.0f, epsilon) << "vec3::right_and_up_rh failed";
    }
}

TEST(as_vec, equal)
{
    {
        vec3_t vec1(1.11f, 0.3f, 517.2f);
        vec3_t vec2(1.11f, 0.3f, 517.2f);

        EXPECT_TRUE(vec::equal(vec1, vec2)) << "vec::equal failed";
    }

    {
        vec3_t vec1(1.11f, 0.3f, 514.2f);
        vec3_t vec2(1.114f, 0.3f, 517.2f);

        EXPECT_FALSE(vec::equal(vec1, vec2)) << "vec::equal failed";
    }

    {
        vec3_t vec1(1.11f, 0.3f, 514.2f);
        vec3_t vec2(1.11f, 0.311f, 514.2f);

        EXPECT_FALSE(vec::equal(vec1, vec2)) << "vec::equal failed";
    }
}

TEST(as_vec, abs)
{
    {
        vec4_t vec(-1.0f, -2.0f, -100.0f, -7.0f);
        vec4_t result = vec::abs(vec);

        vec4_t vec_reference = { 1.0f, 2.0f, 100.0f, 7.0f };

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::abs failed";
    }

    {
        vec4_t vec{ 1.0f, 4.0f, 6.0f, 50.0f };
        vec4_t result = vec::abs(vec);

        vec4_t vec_reference = { 1.0f, 4.0f, 6.0f, 50.0f };

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::abs failed";
    }
}

TEST(as_vec, min)
{
    {
        vec4_t vec1(-1.0f, 2.0f, -100.0f, -7.0f);
        vec4_t vec2(-10.0f, 7.0f, -50.0f, -16.0f);

        vec4_t vec_reference(-10.0f, 2.0f, -100.0f, -16.0f);

        vec4_t result = vec::min(vec1, vec2);

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::min failed";
    }

    {
        vec4_t vec1(1.0f, 2.0f, 3.0f, 4.0f);
        vec4_t vec2(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t vec_reference(1.0f, 2.0f, 3.0f, 4.0f);

        vec4_t result = vec::min(vec1, vec2);

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::min failed";
    }
}

TEST(as_vec, min_elem)
{
    {
        vec3_t vec{ -1.0f, 2.0f, -100.0f };
        real_t result = vec::min_elem(vec);

        EXPECT_TRUE(result == -100.0f) << "vec::min_elem failed";
    }

    {
        vec3_t vec{ 1.0f, 2.0f, 3.0f };
        real_t result = vec::min_elem(vec);

        EXPECT_TRUE(result == 1.0f) << "vec::min_elem failed";
    }
}

TEST(as_vec, max)
{
    {
        vec4_t vec1(-1.0f, 2.0f, -100.0f, -7.0f);
        vec4_t vec2(-10.0f, 7.0f, -50.0f, -16.0f);

        vec4_t vec_reference(-1.0f, 7.0f, -50.0f, -7.0f);

        vec4_t result = vec::max(vec1, vec2);

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::max failed";
    }

    {
        vec4_t vec1(1.0f, 2.0f, 3.0f, 4.0f);
        vec4_t vec2(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t vec_reference(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t result = vec::max(vec1, vec2);

        EXPECT_TRUE(vec::equal(vec_reference, result)) << "vec::max failed";
    }
}

TEST(as_vec, max_elem)
{
    {
        vec3_t vec{ -1.0f, 2.0f, -100.0f };
        real_t result = vec::max_elem(vec);

        EXPECT_TRUE(result == 2.0f) << "vec::max_elem failed";
    }

    {
        vec3_t vec{ 1.0f, 2.0f, 3.0f };
        real_t result = vec::max_elem(vec);

        EXPECT_TRUE(result == 3.0f) << "vec::max_elem failed";
    }
}

TEST(as_vec, clamp)
{
    {
        vec3_t min(50.0f, 50.0f, 50.0f);
        vec3_t max(100.0f, 100.0f, 100.0f);

        vec3_t vec(20.0f, 20.0f, 20.0f);

        vec3_t result = vec::clamp(vec, min, max);

        EXPECT_TRUE(vec::equal(result, min)) << "vec::clamp failed";
    }

    {
        vec3_t min(50.0f, 50.0f, 50.0f);
        vec3_t max(100.0f, 100.0f, 100.0f);

        vec3_t vec(120.0f, 200.0f, 300.0f);

        vec3_t result = vec::clamp(vec, min, max);

        EXPECT_TRUE(vec::equal(result, max)) << "vec::clamp failed";
    }

    {
        vec3_t min(50.0f, 50.0f, 50.0f);
        vec3_t max(100.0f, 100.0f, 100.0f);

        vec3_t vec(20.0f, 120.0f, 20.0f);
        vec3_t vec_reference(50.0f, 100.0f, 50.0f);

        vec3_t result = vec::clamp(vec, min, max);

        EXPECT_TRUE(vec::equal(result, vec_reference)) << "vec::clamp failed";
    }

    {
        vec3_t min(50.0f, 50.0f, 50.0f);
        vec3_t max(100.0f, 100.0f, 100.0f);

        vec3_t vec(62.0f, 56.0f, 72.0f);

        vec3_t result = vec::clamp(vec, min, max);

        EXPECT_TRUE(vec::equal(result, vec)) << "vec::clamp failed";
    }
}

TEST(as_vec, saturate)
{
    {
        vec3_t vec(-2.0f, 0.5f, 1.2f);
        vec3_t result = vec::saturate(vec);

        vec3_t vec_reference(0.0f, 0.5f, 1.0f);

        EXPECT_TRUE(vec::equal(result, vec_reference)) << "vec::saturate failed";
    }

    {
        vec3_t vec(3.0f, 0.1f, -1.2f);
        vec3_t result = vec::saturate(vec);

        vec3_t vec_reference(1.0f, 0.1f, 0.0f);

        EXPECT_TRUE(vec::equal(result, vec_reference)) << "vec::saturate failed";
    }
}

// ---

TEST(as_vec, lerp)
{
    {
        vec3_t start(0.0f, 10.0f, 20.0f);
        vec3_t end(10.0f, 40.0f, 100.0f);

        vec3_t result_begin = vec::lerp(0.0f, start, end);
        vec3_t result_mid = vec::lerp(0.5f, start, end);
        vec3_t result_end = vec::lerp(1.0f, start, end);

        EXPECT_TRUE(result_begin.x == 0.0f && result_begin.y == 10.0f && result_begin.z == 20.0f) << "vec lerp failed";
        EXPECT_TRUE(result_mid.x == 5.0f && result_mid.y == 25.0f && result_mid.z == 60.0f) << "vec lerp failed";
        EXPECT_TRUE(result_end.x == 10.0f && result_end.y == 40.0f && result_end.z == 100.0f) << "vec lerp failed";
    }
}

TEST(as_vec, normalize_return_length)
{
    {
        vec3_t vec(3.0f, 4.0f, 0.0f);
        vec3_t vec_normalized;
        real_t length = vec::normalize_return_length(vec, vec_normalized);

        EXPECT_FLOAT_EQ(length, 5.0f) << "vec::normalize_return_length failed - length";
        EXPECT_FLOAT_EQ(vec::length(vec_normalized), 1.0f) << "vec::normalize_return_length failed - normalize";
    }
}

TEST(as_vec, select) {
    using int3 = vec_t<int, 3>;

    int3 a(1, 2, 3);
    int3 b(5, 6, 7);

    using byte4 = vec_t<u8, 4>;

    byte4 c((u8)255, (u8)255, (u8)255, (u8)255);
    byte4 d((u8)0, (u8)0, (u8)0, (u8)0);

    int3 result = vec::select(a, b, true);
    byte4 result_byte = vec::select(c, d, false);

    EXPECT_TRUE(result[0] == 1 && result[1] == 2 && result[2] == 3) << "vec select failed";
    EXPECT_TRUE(result_byte[0] == 0 && result_byte[1] == 0 && result_byte[2] == 0 && result_byte[3] == 0) << "vec select failed";
}
