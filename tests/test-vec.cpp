// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-math.hpp"
#include "src/math/as-vec.hpp"
#include "src/math/as-math-type-ops.hpp"

// as-test
#include "as-math-output.hpp"

// std
#include <memory>

const as::real_t epsilon = std::numeric_limits<as::real_t>::epsilon();

TEST(as_vec, vec2_initialization)
{
    // default initialization
    {
        as::vec2_t vec2;
        AS_UNUSED(vec2);
    }

    // zero initialization
    {
        as::vec2_t vec2{};
        EXPECT_EQ(vec2.x, 0.0f);
        EXPECT_EQ(vec2.y, 0.0f);
    }

    // value initialization
    {
        as::vec2_t vec2 = as::vec2_t();
        EXPECT_EQ(vec2.x, 0.0f);
        EXPECT_EQ(vec2.y, 0.0f);
    }

    // direct initialization (braces)
    {
        as::vec2_t vec2{1.0f, 2.0f};
        EXPECT_EQ(vec2.x, 1.0f);
        EXPECT_EQ(vec2.y, 2.0f);
    }

    // direct initialization (parens)
    {
        as::vec2_t vec2(5.0f, 10.0f);
        EXPECT_EQ(vec2.x, 5.0f);
        EXPECT_EQ(vec2.y, 10.0f);
    }

    // direct/copy initialization (braces)
    {
        as::vec2_t vec2 = as::vec2_t{3.0f, 4.0f};
        EXPECT_EQ(vec2.x, 3.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // direct/copy initialization (parens)
    {
        as::vec2_t vec2 = as::vec2_t(3.0f, 4.0f);
        EXPECT_EQ(vec2.x, 3.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        as::vec2_t vec2 = as::vec2_t{123.0f};
        EXPECT_EQ(vec2.x, 123.0f);
        EXPECT_EQ(vec2.y, 123.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        as::vec2_t vec2 = as::vec2_t(25.0f);
        EXPECT_EQ(vec2.x, 25.0f);
        EXPECT_EQ(vec2.y, 25.0f);
    }

    // direct + copy initialization
    {
        as::vec2_t vec2_a(300.0f, 400.0f);
        as::vec2_t vec2_b(vec2_a);

        EXPECT_EQ(vec2_b.x, 300.0f);
        EXPECT_EQ(vec2_b.y, 400.0f);
    }

    // direct + copy initialization (assignment)
    {
        as::vec2_t vec2_a(100.0f, 200.0f);
        as::vec2_t vec2_b = vec2_a;

        EXPECT_EQ(vec2_b.x, 100.0f);
        EXPECT_EQ(vec2_b.y, 200.0f);
    }

    // direct + copy initialization (assignment)
    {
        as::vec2_t vec2_a(500.0f, 600.0f);
        as::vec2_t vec2_b;

        vec2_b = vec2_a;

        EXPECT_EQ(vec2_b.x, 500.0f);
        EXPECT_EQ(vec2_b.y, 600.0f);
    }
}

TEST(as_vec, vec3_initialization)
{
    // default initialization
    {
        as::vec3_t vec3;
        AS_UNUSED(vec3);
    }

    // zero initialization
    {
        as::vec3_t vec3{};
        EXPECT_EQ(vec3.x, 0.0f);
        EXPECT_EQ(vec3.y, 0.0f);
        EXPECT_EQ(vec3.z, 0.0f);
    }

    // value initialization
    {
        as::vec3_t vec3 = as::vec3_t();
        EXPECT_EQ(vec3.x, 0.0f);
        EXPECT_EQ(vec3.y, 0.0f);
        EXPECT_EQ(vec3.z, 0.0f);
    }

    // direct initialization (braces)
    {
        as::vec3_t vec3{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct initialization (parens)
    {
        as::vec3_t vec3(5.0f, 10.0f, 15.0f);
        EXPECT_EQ(vec3.x, 5.0f);
        EXPECT_EQ(vec3.y, 10.0f);
        EXPECT_EQ(vec3.z, 15.0f);
    }

    // direct/copy initialization (braces)
    {
        as::vec3_t vec3 = as::vec3_t{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct/copy initialization (parens)
    {
        as::vec3_t vec3 = as::vec3_t(3.0f, 4.0f, 5.0f);
        EXPECT_EQ(vec3.x, 3.0f);
        EXPECT_EQ(vec3.y, 4.0f);
        EXPECT_EQ(vec3.z, 5.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        as::vec3_t vec3 = as::vec3_t{50.0f};
        EXPECT_EQ(vec3.x, 50.0f);
        EXPECT_EQ(vec3.y, 50.0f);
        EXPECT_EQ(vec3.z, 50.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        as::vec3_t vec3 = as::vec3_t(25.0f);
        EXPECT_EQ(vec3.x, 25.0f);
        EXPECT_EQ(vec3.y, 25.0f);
        EXPECT_EQ(vec3.z, 25.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        as::vec3_t vec3 = as::vec3_t{as::vec2_t{1.0f, 2.0f}, 3.0f};
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        as::vec3_t vec3 = as::vec3_t(as::vec2_t(1.0f, 2.0f), 3.0f);
        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // direct + copy initialization
    {
        as::vec3_t vec3_a(100.0f, 200.0f, 300.0f);
        as::vec3_t vec3_b(vec3_a);

        EXPECT_EQ(vec3_b.x, 100.0f);
        EXPECT_EQ(vec3_b.y, 200.0f);
        EXPECT_EQ(vec3_b.z, 300.0f);
    }

    // direct + copy initialization
    {
        as::vec3_t vec3_a(400.0f, 500.0f, 600.0f);
        as::vec3_t vec3_b = vec3_a;

        EXPECT_EQ(vec3_b.x, 400.0f);
        EXPECT_EQ(vec3_b.y, 500.0f);
        EXPECT_EQ(vec3_b.z, 600.0f);
    }

    // direct + copy initialization (assignment)
    {
        as::vec3_t vec3_a(500.0f, 600.0f, 700.0f);
        as::vec3_t vec3_b;

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
        as::vec4_t vec4;
        AS_UNUSED(vec4);
    }

    // zero initialization
    {
        as::vec4_t vec4{};
        EXPECT_EQ(vec4.x, 0.0f);
        EXPECT_EQ(vec4.y, 0.0f);
        EXPECT_EQ(vec4.z, 0.0f);
        EXPECT_EQ(vec4.w, 0.0f);
    }

    // value initialization
    {
        as::vec4_t vec4 = as::vec4_t();
        EXPECT_EQ(vec4.x, 0.0f);
        EXPECT_EQ(vec4.y, 0.0f);
        EXPECT_EQ(vec4.z, 0.0f);
        EXPECT_EQ(vec4.w, 0.0f);
    }

    // direct initialization (braces)
    {
        as::vec4_t vec4{1.0f, 2.0f, 3.0f, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct initialization (parens)
    {
        as::vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization (braces)
    {
        as::vec4_t vec4 = as::vec4_t{3.0f, 4.0f, 5.0f, 6.0f};
        EXPECT_EQ(vec4.x, 3.0f);
        EXPECT_EQ(vec4.y, 4.0f);
        EXPECT_EQ(vec4.z, 5.0f);
        EXPECT_EQ(vec4.w, 6.0f);
    }

    // direct/copy initialization (parens)
    {
        as::vec4_t vec4 = as::vec4_t(3.0f, 4.0f, 5.0f, 6.0f);
        EXPECT_EQ(vec4.x, 3.0f);
        EXPECT_EQ(vec4.y, 4.0f);
        EXPECT_EQ(vec4.z, 5.0f);
        EXPECT_EQ(vec4.w, 6.0f);
    }

    // direct/copy initialization - single argument (braces)
    {
        as::vec4_t vec4 = as::vec4_t{50.0f};
        EXPECT_EQ(vec4.x, 50.0f);
        EXPECT_EQ(vec4.y, 50.0f);
        EXPECT_EQ(vec4.z, 50.0f);
        EXPECT_EQ(vec4.w, 50.0f);
    }

    // direct/copy initialization - single argument (parens)
    {
        as::vec4_t vec4 = as::vec4_t(25.0f);
        EXPECT_EQ(vec4.x, 25.0f);
        EXPECT_EQ(vec4.y, 25.0f);
        EXPECT_EQ(vec4.z, 25.0f);
        EXPECT_EQ(vec4.w, 25.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        as::vec4_t vec4 = as::vec4_t{as::vec3_t{1.0f, 2.0f, 3.0f}, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        as::vec4_t vec4 = as::vec4_t(as::vec3_t(1.0f, 2.0f, 3.0f), 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (braces)
    {
        as::vec4_t vec4 = as::vec4_t{as::vec2_t{1.0f, 2.0f}, as::vec2_t{3.0f, 4.0f}};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - double argument (parens)
    {
        as::vec4_t vec4 = as::vec4_t(as::vec2_t(1.0f, 2.0f), as::vec2_t(3.0f, 4.0f));
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - triple argument (braces)
    {
        as::vec4_t vec4 = as::vec4_t{as::vec2_t{1.0f, 2.0f}, 3.0f, 4.0f};
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct/copy initialization - triple argument (parens)
    {
        as::vec4_t vec4 = as::vec4_t(as::vec2_t(1.0f, 2.0f), 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, 1.0f);
        EXPECT_EQ(vec4.y, 2.0f);
        EXPECT_EQ(vec4.z, 3.0f);
        EXPECT_EQ(vec4.w, 4.0f);
    }

    // direct + copy initialization
    {
        as::vec4_t vec4_a(100.0f, 200.0f, 300.0f, 400.0f);
        as::vec4_t vec4_b(vec4_a);

        EXPECT_EQ(vec4_b.x, 100.0f);
        EXPECT_EQ(vec4_b.y, 200.0f);
        EXPECT_EQ(vec4_b.z, 300.0f);
        EXPECT_EQ(vec4_b.w, 400.0f);
    }

    // direct + copy initialization
    {
        as::vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        as::vec4_t vec4_b = vec4_a;

        EXPECT_EQ(vec4_b.x, 500.0f);
        EXPECT_EQ(vec4_b.y, 600.0f);
        EXPECT_EQ(vec4_b.z, 700.0f);
        EXPECT_EQ(vec4_b.w, 800.0f);
    }

    // direct + copy initialization (assignment)
    {
        as::vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        as::vec4_t vec4_b;

        vec4_b = vec4_a;

        EXPECT_EQ(vec4_b.x, 500.0f);
        EXPECT_EQ(vec4_b.y, 600.0f);
        EXPECT_EQ(vec4_b.z, 700.0f);
        EXPECT_EQ(vec4_b.w, 800.0f);
    }
}

TEST(as_vec, vec2_accessors)
{
    // anonymous struct and subscript operator - zero initializer
    {
        as::vec2_t vec2{};
        EXPECT_EQ(vec2.x, vec2[0]);
        EXPECT_EQ(vec2.y, vec2[1]);
    }

    // anonymous struct and subscript operator - explicit construction
    {
        as::vec2_t vec2(1.0f, 2.0f);
        EXPECT_EQ(vec2.x, vec2[0]);
        EXPECT_EQ(vec2.y, vec2[1]);
    }

    // anonymous struct and internal element array - explicit construction
    {
        as::vec2_t vec2(1.0f, 2.0f);
        EXPECT_EQ(vec2.elems()[0], vec2[0]);
        EXPECT_EQ(vec2.elems()[1], vec2[1]);
    }
}

TEST(as_vec, vec3_accessors)
{
    // anonymous struct and subscript operator - zero initializer
    {
        as::vec3_t vec3{};
        EXPECT_EQ(vec3.x, vec3[0]);
        EXPECT_EQ(vec3.y, vec3[1]);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // anonymous struct and subscript operator - explicit construction
    {
        as::vec3_t vec3(1.0f, 2.0f, 3.0f);
        EXPECT_EQ(vec3.x, vec3[0]);
        EXPECT_EQ(vec3.y, vec3[1]);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // anonymous struct and subscript operator - explicit construction
    {
        as::vec3_t vec3(1.0f, 2.0f, 3.0f);
        EXPECT_EQ(vec3.xy()[0], vec3.x);
        EXPECT_EQ(vec3.xy()[1], vec3.y);
        EXPECT_EQ(vec3.xy().x, vec3.x);
        EXPECT_EQ(vec3.xy().y, vec3.y);
        EXPECT_EQ(vec3.z, vec3[2]);
    }

    // anonymous struct and internal element array - explicit construction
    {
        as::vec3_t vec3(2.0f, 4.0f, 6.0f);
        EXPECT_EQ(vec3.elems()[0], vec3[0]);
        EXPECT_EQ(vec3.elems()[1], vec3[1]);
        EXPECT_EQ(vec3.elems()[2], vec3[2]);
    }
}

TEST(as_vec, vec4_accessors)
{
    // anonymous struct and subscript operator - zero initializer
    {
        as::vec4_t vec4{};
        EXPECT_EQ(vec4.x, vec4[0]);
        EXPECT_EQ(vec4.y, vec4[1]);
        EXPECT_EQ(vec4.z, vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // anonymous struct and subscript operator - explicit construction
    {
        as::vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.x, vec4[0]);
        EXPECT_EQ(vec4.y, vec4[1]);
        EXPECT_EQ(vec4.z, vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // anonymous struct and subscript operator - explicit construction
    {
        as::vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.xy()[0], vec4[0]);
        EXPECT_EQ(vec4.xy()[1], vec4[1]);
        EXPECT_EQ(vec4.zw()[0], vec4[2]);
        EXPECT_EQ(vec4.zw()[1], vec4[3]);
        EXPECT_EQ(vec4.xyz()[0], vec4[0]);
        EXPECT_EQ(vec4.xyz()[1], vec4[1]);
        EXPECT_EQ(vec4.xyz()[2], vec4[2]);
        EXPECT_EQ(vec4.w, vec4[3]);
    }

    // anonymous struct and internal element array - explicit construction
    {
        as::vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        EXPECT_EQ(vec4.elems()[0], vec4[0]);
        EXPECT_EQ(vec4.elems()[1], vec4[1]);
        EXPECT_EQ(vec4.elems()[2], vec4[2]);
        EXPECT_EQ(vec4.elems()[3], vec4[3]);
    }
}

TEST(as_vec, vec2_vec3_vec4_accessors)
{
    as::vec2_t vec2(1.0f, 2.0f);
    as::vec3_t vec3(vec2, 3.0f);

    as::vec4_t vec4_a(vec2, 3.0f, 4.0f);
    as::vec4_t vec4_b(vec2, vec2);
    as::vec4_t vec4_c(vec3, 4.0f);

    // anonymous struct accessors
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

TEST(as_vec, vec_size)
{
    size_t vec2_size = as::vec2_t::size;
    as::vec2_t vec2;
    size_t vec2_inst_size = as::vec::size(vec2);
    EXPECT_EQ(vec2_size, static_cast<size_t>(2));
    EXPECT_EQ(vec2_inst_size, vec2_size);

    size_t vec3_size = as::vec3_t::size;
    as::vec3_t vec3;
    size_t vec3_inst_size = as::vec::size(vec3);
    EXPECT_EQ(vec3_size, static_cast<size_t>(3));
    EXPECT_EQ(vec3_inst_size, vec3_size);

    size_t vec4_size = as::vec4_t::size;
    as::vec4_t vec4;
    size_t vec4_inst_size = as::vec::size(vec4);
    EXPECT_EQ(vec4_size, static_cast<size_t>(4));
    EXPECT_EQ(vec4_inst_size, vec4_size);

    using short7 = as::Vec<short, 7>;
    short7 vec_short7;
    size_t vec_short7_inst_size = as::vec::size(vec_short7);
    size_t short7_size = short7::size;
    EXPECT_EQ(short7_size, static_cast<size_t>(7));
    EXPECT_EQ(vec_short7_inst_size, short7_size);

    using int5 = as::Vec<int, 5>;
    int5 vec_short5;
    size_t vec_short5_inst_size = as::vec::size(vec_short5);
    size_t int5_size = int5::size;
    EXPECT_EQ(int5_size, static_cast<size_t>(5));
    EXPECT_EQ(vec_short5_inst_size, int5_size);
}

TEST(as_vec, vec_data)
{
    // data mutable
    {
        as::vec2_t vec2(5.0f, 10.0f);
        as::real_t *data = as::vec::data(vec2);

        EXPECT_EQ(data[0], 5.0f);
        EXPECT_EQ(data[1], 10.0f);
    }

    // data const
    {
        as::vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        const as::real_t* data = as::vec::const_data(vec4);

        EXPECT_EQ(data[0], 1.0f);
        EXPECT_EQ(data[1], 2.0f);
        EXPECT_EQ(data[2], 3.0f);
        EXPECT_EQ(data[3], 4.0f);
    }

    // r-value - will not compile
    {
        // as::data(as::vec3_t(1.0f, 2.0f, 3.0f));
    }

    // data mutable
    {
        as::vec2_t vec2(20.0f, 40.0f);
        as::real_t* data = as::vec::data(vec2);

        EXPECT_EQ(data[0], 20.0f);
        EXPECT_EQ(data[1], 40.0f);

        data[0] = 100.0f;
        data[1] = 200.0f;

        EXPECT_EQ(vec2.x, 100.0f);
        EXPECT_EQ(vec2.y, 200.0f);
    }

    // generic data mutable
    {
        using int5 = as::Vec<int, 5>;
        int5 int5_vec{ 11, 12, 13, 14, 15 };
        int* data = as::vec::data(int5_vec);

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
        using short7 = as::Vec<short, 7>;
        short7 short7_vec{
            (short)11, (short)22, (short)33, (short)44,
            (short)55, (short)66, (short)77 };
        const short* data = as::vec::const_data(short7_vec);

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
        as::real_t data[2] = { 2.0f, 4.0f };
        as::vec2_t vec2 = as::vec::from_arr(data);

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);

        // won't compile (array length 2 to as::vec3_t)
        // as::vec3_t vec3 = as::make_from(data);
    }

    // generic make_from_arr vec3_t
    {
        as::real_t data[3] = { 1.0f, 2.0f, 3.0f };
        as::vec3_t vec3 = as::vec::from_arr(data);

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // generic make_from_arr <char, 6>
    {
        char data[6] = { 11, 12, 13, 14, 15, 16 };
        as::Vec<char, 6> char_6 = as::vec::from_arr(data);

        EXPECT_EQ(char_6[0], 11);
        EXPECT_EQ(char_6[1], 12);
        EXPECT_EQ(char_6[2], 13);
        EXPECT_EQ(char_6[3], 14);
        EXPECT_EQ(char_6[4], 15);
        EXPECT_EQ(char_6[5], 16);
    }

    // vec2::make_from_arr
    {
        as::real_t data[2] = { 2.0f, 4.0f };
        as::vec2_t vec2 = as::vec2::from_arr(data);

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // vec3_make_from_arr
    {
        as::real_t data[3] = { 1.0f, 2.0f, 3.0f };
        as::vec3_t vec3 = as::vec3::from_arr(data);

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // vec4_make_from_arr
    {
        as::real_t data[4] = { 4.0f, 8.0f, 12.0f, 16.0f };
        as::vec4_t vec4 = as::vec4::from_arr(data);

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
        std::unique_ptr<as::real_t[]> data = std::make_unique<as::real_t[]>(2);
        data[0] = 2.0f;
        data[1] = 4.0f;
        as::vec2_t vec2 = as::vec::from_ptr<as::real_t, 2>(data.get());

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // generic make_from_ptr vec3_t
    {
        std::unique_ptr<as::real_t[]> data = std::make_unique<as::real_t[]>(3);
        data[0] = 1.0f;
        data[1] = 2.0f;
        data[2] = 3.0f;
        as::vec3_t vec3 = as::vec::from_ptr<as::real_t, 3>(data.get());

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
        as::Vec<char, 6> char_6 = as::vec::from_ptr<char, 6>(data.get());

        EXPECT_EQ(char_6[0], 11);
        EXPECT_EQ(char_6[1], 12);
        EXPECT_EQ(char_6[2], 13);
        EXPECT_EQ(char_6[3], 14);
        EXPECT_EQ(char_6[4], 15);
        EXPECT_EQ(char_6[5], 16);
    }

    // vec2::make_from_ptr
    {
        std::unique_ptr<as::real_t[]> data = std::make_unique<as::real_t[]>(2);
        data[0] = 2.0f;
        data[1] = 4.0f;
        as::vec2_t vec2 = as::vec2::from_ptr(data.get());

        EXPECT_EQ(vec2.x, 2.0f);
        EXPECT_EQ(vec2.y, 4.0f);
    }

    // vec3_make_from_ptr
    {
        std::unique_ptr<as::real_t[]> data = std::make_unique<as::real_t[]>(3);
        data[0] = 1.0f;
        data[1] = 2.0f;
        data[2] = 3.0f;
        as::vec3_t vec3 = as::vec3::from_ptr(data.get());

        EXPECT_EQ(vec3.x, 1.0f);
        EXPECT_EQ(vec3.y, 2.0f);
        EXPECT_EQ(vec3.z, 3.0f);
    }

    // vec4_make_from_ptr
    {
        std::unique_ptr<as::real_t[]> data = std::make_unique<as::real_t[]>(4);
        data[0] = 4.0f;
        data[1] = 8.0f;
        data[2] = 12.0f;
        data[3] = 16.0f;
        as::vec4_t vec4 = as::vec4::from_ptr(data.get());

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
        // as::Vec<char, 2> char_2 = as::from_ptr<char, 2>(data.get());
        // as::vec2_t vec2 = as::from_ptr<float, 2>(data.get());
    }
}

TEST(as_vec, dot)
{
    // note: comparison values calculated using - http://calculator.vhex.net
    {
        as::vec3_t vec1(1.0f, 2.0f, 3.0f);
        as::vec3_t vec2(4.0f, 5.0f, 6.0f);

        as::real_t dot_result = as::vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, 32.0f, epsilon);
    }

    {
        as::vec3_t vec1(-50.0f, 20.0f, 9.0f);
        as::vec3_t vec2(-1.0f, -7.0f, 4.0f);

        as::real_t dot_result = as::vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, -54.0f, epsilon);
    }

    {
        as::vec3_t vec1(-27.367f, 0.1165f, 0.921f);
        as::vec3_t vec2(-123.456f, -7.732f, 2.491f);

        as::real_t dot_result = as::vec::dot(vec1, vec2);
        EXPECT_NEAR(dot_result, 3380.013785f, epsilon);
    }
}

// ------

TEST(as_vec, cross)
{
    glm::vec3 glm_a = glm::vec3(1.0f, 2.0f, 3.0f);
    glm::vec3 glm_b = glm::vec3(4.0f, 3.0f, 2.0f);

    glm::vec3 glm_ab_result = glm::cross(glm_a, glm_b);

    as::vec3_t as_a = as::vec3_t(1.0f, 2.0f, 3.0f);
    as::vec3_t as_b = as::vec3_t(4.0f, 3.0f, 2.0f);

    as::vec3_t as_ab_result = as::vec3::cross(as_a, as_b);

    EXPECT_TRUE(as::equal(as_ab_result.x, glm_ab_result.x));
    EXPECT_TRUE(as::equal(as_ab_result.y, glm_ab_result.y));
    EXPECT_TRUE(as::equal(as_ab_result.z, glm_ab_result.z));
}

TEST(as_vec, right_and_up)
{
    as::vec3_t dir(0.0f, 0.0f, -1.0f);

    printf("dir - x: %f, y: %f, z: %f\n", dir.x, dir.y, dir.z);

    {
        as::vec3_t across_lh, up_lh;
        as::vec3::right_and_up_lh(dir, across_lh, up_lh);

        printf("right lh - x: %f, y: %f, z: %f\n", across_lh.x, across_lh.y, across_lh.z);
        printf("up lh - x: %f, y: %f, z: %f\n", up_lh.x, up_lh.y, up_lh.z);
    }

    {
        as::vec3_t across_rh, up_rh;
        as::vec3::right_and_up_rh(dir, across_rh, up_rh);

        printf("right rh - x: %f, y: %f, z: %f\n", across_rh.x, across_rh.y, across_rh.z);
        printf("up rh - x: %f, y: %f, z: %f\n", up_rh.x, up_rh.y, up_rh.z);
    }
}

TEST(as_vec, constants) {
    // todo
}

TEST(as_vec, equal) {
    as::vec3_t a(1.11f, 0.3f, 517.2f);
    as::vec3_t b(1.11f, 0.3f, 517.2f);

    EXPECT_TRUE(as::vec::equal(a, b)) << "vector equality check for equal vectors failed";

    as::vec3_t c(1.11f, 0.3f, 514.2f);
    as::vec3_t d(1.114f, 0.3f, 517.2f);

    EXPECT_FALSE(as::vec::equal(a, c)) << "vector equality check for different vectors failed";
    EXPECT_FALSE(as::vec::equal(a, d)) << "vector equality check for different vectors failed";
    EXPECT_FALSE(as::vec::equal(b, c)) << "vector equality check for different vectors failed";
}

TEST(as_vec, init_compat) {
    glm::vec3 glm_a(1.0f, 2.0f, 3.0f);

    as::real_t data[3] = { 1.0f, 2.0f, 3.0f };
    as::vec3_t as_a = as::vec::from_arr(data);
    as::vec3_t as_b = as::vec::from_ptr<float, 3>(glm::value_ptr(glm_a));
    as::vec3_t as_c = as::vec3_t(as::vec::from_ptr<as::real_t, 3>(as::vec::data(as_a)));
    as::vec3_t as_d = as::vec3_t(as::vec3::from_ptr(as::vec::data(as_a)));

    as::real_t data_vec4[4] = { 5.0f, 12.0f, 100.0f, 0.999f };
    as::vec4_t as_vec4 = as::vec4_t(as::vec4::from_arr(data_vec4));
    as::vec4_t as_vec4_2 = as::vec4_t(as::vec4::from_ptr(as::vec::data(as_vec4)));

    print_vec3(as_a);
    print_vec3(as_b);
    print_vec3(as_c);
    print_vec3(as_d);
    print_vec4(as_vec4);
    print_vec4(as_vec4_2);
}

TEST(as_vec, abs) {
    as::vec4_t v(-1.0f, 2.0f, -100.0f, -7.0f);
    as::vec4_t r = as::vec::abs(v);

    bool is_abs = true;
    for(size_t i = 0; i < 4; ++i) {
        is_abs &= r[i] >= 0.0f;
    }

    EXPECT_TRUE(is_abs) << "as::vec abs failed";
}

TEST(as_vec, min) {
    as::vec4_t v1(-1.0f, 2.0f, -100.0f, -7.0f);
    as::vec4_t vec2_t(-10.0f, 7.0f, -50.0f, -16.0f);

    as::vec4_t r = as::vec::min(v1, vec2_t);

    EXPECT_TRUE(r.x == -10.0f && r.y == 2.0f && r.z == -100.0f && r.w == -16.0f) << "as::vec min failed";
}

TEST(as_vec, min_elem) {
    as::vec4_t v(-1.0f, 2.0f, -100.0f, -7.0f);
    as::real_t min = as::vec::min_elem(v);

    EXPECT_TRUE(min == -100.0f) << "as::vec min_elem failed";
}

TEST(as_vec, max) {
    as::vec4_t v1(-1.0f, 2.0f, -100.0f, -7.0f);
    as::vec4_t vec2_t(-10.0f, 7.0f, -50.0f, -16.0f);

    as::vec4_t r = as::vec::max(v1, vec2_t);

    EXPECT_TRUE(r.x == -1.0f && r.y == 7.0f && r.z == -50.0f && r.w == -7.0f) << "as::vec max failed";
}

TEST(as_vec, max_elem) {
    as::vec4_t v(-1.0f, 2.0f, -100.0f, -7.0f);
    as::real_t max = as::vec::max_elem(v);

    EXPECT_TRUE(max == 2.0f) << "as::vec max_elem failed";
}

TEST(as_vec, clamp) {
    as::vec3_t min(100.0f, 50.0f, -100.0f);
    as::vec3_t max(200.0f, 1000.0f, -50.0f);

    as::vec3_t v(50.0f, 1020.0f, -75.0f);

    as::vec3_t result = as::vec::clamp(v, min, max);

    EXPECT_TRUE(result.x == 100.0f && result.y == 1000.0f && result.z == -75.0f) << "as::vec clamp failed";
}

TEST(as_vec, saturate) {
    as::vec3_t v(-2.0f, 0.5f, 1.2f);

    as::vec3_t result = as::vec::saturate(v);

    EXPECT_TRUE(result.x == 0.0f && result.y == 0.5f && result.z == 1.0f) << "as::vec saturate failed";
}

TEST(as_vec, lerp) {
    as::vec3_t start(0.0f, 10.0f, 20.0f);
    as::vec3_t end(10.0f, 40.0f, 100.0f);

    as::vec3_t result_begin = as::vec::lerp(0.0f, start, end);
    as::vec3_t result_mid = as::vec::lerp(0.5f, start, end);
    as::vec3_t result_end = as::vec::lerp(1.0f, start, end);

    EXPECT_TRUE(result_begin.x == 0.0f && result_begin.y == 10.0f && result_begin.z == 20.0f) << "as::vec lerp failed";
    EXPECT_TRUE(result_mid.x == 5.0f && result_mid.y == 25.0f && result_mid.z == 60.0f) << "as::vec lerp failed";
    EXPECT_TRUE(result_end.x == 10.0f && result_end.y == 40.0f && result_end.z == 100.0f) << "as::vec lerp failed";
}

TEST(as_vec, select) {
    using int3 = as::Vec<int, 3>;

    int3 a(1, 2, 3);
    int3 b(5, 6, 7);

    using byte4 = as::Vec<as::byte, 4>;

    byte4 c((as::byte)255, (as::byte)255, (as::byte)255, (as::byte)255);
    byte4 d((as::byte)0, (as::byte)0, (as::byte)0, (as::byte)0);

    using float3 = as::Vec<float, 3>;

    float3 x(1.0f, 2.0f, 3.0f);
    float3 y(4.0f, 5.0f, 6.0f);

    int3 result = as::vec::select(a, b, true);
    byte4 result_byte = as::vec::select(c, d, false);

    int3 e{8, 9, 10};
    int3 f({11, 12, 13});
    int3 g(11, 12, 13);

    //int3 h = int3{1};
    //int3 i = int3{1, 2};

    // implicit conversions are allowed
    int3 k = { 5, 6, 7 };
    int3 l = { 1 };
    //int3 m = 2;

    printf("v = x: %d, y: %d, z: %d\n", e[0], e[1], e[2]);
    printf("v = x: %d, y: %d, z: %d\n", f[0], f[1], f[2]);

    EXPECT_TRUE(result[0] == 1 && result[1] == 2 && result[2] == 3) << "as::vec select failed";
    EXPECT_TRUE(result_byte[0] == 0 && result_byte[1] == 0 && result_byte[2] == 0 && result_byte[3] == 0) << "as::vec select failed";
}