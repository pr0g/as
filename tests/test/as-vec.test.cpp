#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

#include <memory>

namespace unit_test
{

// types
using as::index_t;
using as::point3_t;
using as::real_t;
using as::u8;
using as::vec2_t;
using as::vec3_t;
using as::vec4_t;
using as::vec_t;

// functions
using as::deg_to_rad;

// namespaces
namespace vec = as::vec;
namespace vec2 = as::vec2;
namespace vec3 = as::vec3;
namespace vec4 = as::vec4;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("vec2_initialization", "[as_vec]")
{
    // default initialization
    {
        vec2_t vec2;
        (void)vec2;
    }

    // zero initialization
    {
        vec2_t vec2{};
        CHECK(vec2.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(0.0f).epsilon(g_epsilon));
    }

    // value initialization
    {
        vec2_t vec2 = vec2_t();
        CHECK(vec2.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(0.0f).epsilon(g_epsilon));
    }

    // direct initialization (braces)
    {
        vec2_t vec2{1.0f, 2.0f};
        CHECK(vec2.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(2.0f).epsilon(g_epsilon));
    }

    // direct initialization - single argument (braces)
    {
        vec2_t vec2{5.0f};
        CHECK(vec2.x == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(5.0f).epsilon(g_epsilon));
    }

    // direct initialization (parens)
    {
        vec2_t vec2(5.0f, 10.0f);
        CHECK(vec2.x == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(10.0f).epsilon(g_epsilon));
    }

    // direct initialization - single argument (parens)
    {
        vec2_t vec2;
        vec2 = vec2_t(5.0f);
        CHECK(vec2.x == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(5.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (braces)
    {
        vec2_t vec2 = vec2_t{3.0f, 4.0f};
        CHECK(vec2.x == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (parens)
    {
        vec2_t vec2 = vec2_t(3.0f, 4.0f);
        CHECK(vec2.x == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (braces)
    {
        const real_t value{123.0f};
        vec2_t vec2 = vec2_t{value};
        CHECK(vec2.x == Approx(123.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(123.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (parens)
    {
        vec2_t vec2 = vec2_t(25.0f);
        CHECK(vec2.x == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(25.0f).epsilon(g_epsilon));
    }

    // assignment initialization - single argument (braces)
    {
        vec2_t vec2;
        vec2 = vec2_t{75.0f};
        CHECK(vec2.x == Approx(75.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(75.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization
    {
        vec2_t vec2_a(300.0f, 400.0f);
        vec2_t vec2_b(vec2_a);

        CHECK(vec2_b.x == Approx(300.0f).epsilon(g_epsilon));
        CHECK(vec2_b.y == Approx(400.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization (assignment)
    {
        vec2_t vec2_a(100.0f, 200.0f);
        vec2_t vec2_b = vec2_a;

        CHECK(vec2_b.x == Approx(100.0f).epsilon(g_epsilon));
        CHECK(vec2_b.y == Approx(200.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization (assignment)
    {
        vec2_t vec2_a(500.0f, 600.0f);
        vec2_t vec2_b;

        vec2_b = vec2_a;

        CHECK(vec2_b.x == Approx(500.0f).epsilon(g_epsilon));
        CHECK(vec2_b.y == Approx(600.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("vec3_initialization", "[as_vec]")
{
    // default initialization
    {
        vec3_t vec3;
        (void)vec3;
    }

    // zero initialization
    {
        vec3_t vec3{};
        CHECK(vec3.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(0.0f).epsilon(g_epsilon));
    }

    // value initialization
    {
        vec3_t vec3 = vec3_t();
        CHECK(vec3.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(0.0f).epsilon(g_epsilon));
    }

    // direct initialization (braces)
    {
        vec3_t vec3{1.0f, 2.0f, 3.0f};
        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // direct initialization (parens)
    {
        vec3_t vec3(5.0f, 10.0f, 15.0f);
        CHECK(vec3.x == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(10.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(15.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (braces)
    {
        vec3_t vec3 = vec3_t{1.0f, 2.0f, 3.0f};
        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (parens)
    {
        vec3_t vec3 = vec3_t(3.0f, 4.0f, 5.0f);
        CHECK(vec3.x == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(4.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(5.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (braces)
    {
        vec3_t vec3 = vec3_t{50.0f};
        CHECK(vec3.x == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(50.0f).epsilon(g_epsilon));
    }

    // assignment initialization - single argument (braces)
    {
        vec3_t vec3;
        vec3 = vec3_t{50.0f};
        CHECK(vec3.x == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(50.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (parens)
    {
        vec3_t vec3 = vec3_t(25.0f);
        CHECK(vec3.x == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(25.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (braces)
    {
        vec3_t vec3 = vec3_t{vec2_t{1.0f, 2.0f}, 3.0f};
        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (parens)
    {
        vec2_t vec2 = vec2_t(1.0f, 2.0f);
        vec3_t vec3 = vec3_t(vec2, 3.0f);
        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization
    {
        vec3_t vec3_a(100.0f, 200.0f, 300.0f);
        vec3_t vec3_b(vec3_a);

        CHECK(vec3_b.x == Approx(100.0f).epsilon(g_epsilon));
        CHECK(vec3_b.y == Approx(200.0f).epsilon(g_epsilon));
        CHECK(vec3_b.z == Approx(300.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization
    {
        vec3_t vec3_a(400.0f, 500.0f, 600.0f);
        vec3_t vec3_b = vec3_a;

        CHECK(vec3_b.x == Approx(400.0f).epsilon(g_epsilon));
        CHECK(vec3_b.y == Approx(500.0f).epsilon(g_epsilon));
        CHECK(vec3_b.z == Approx(600.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization (assignment)
    {
        vec3_t vec3_a(500.0f, 600.0f, 700.0f);
        vec3_t vec3_b;

        vec3_b = vec3_a;

        CHECK(vec3_b.x == Approx(500.0f).epsilon(g_epsilon));
        CHECK(vec3_b.y == Approx(600.0f).epsilon(g_epsilon));
        CHECK(vec3_b.z == Approx(700.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("vec4_initialization", "[as_vec]")
{
    // default initialization
    {
        vec4_t vec4;
        (void)vec4;
    }

    // zero initialization
    {
        vec4_t vec4{};
        CHECK(vec4.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(0.0f).epsilon(g_epsilon));
    }

    // value initialization
    {
        vec4_t vec4 = vec4_t();
        CHECK(vec4.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(0.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(0.0f).epsilon(g_epsilon));
    }

    // direct initialization (braces)
    {
        vec4_t vec4{1.0f, 2.0f, 3.0f, 4.0f};
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct initialization (parens)
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (braces)
    {
        vec4_t vec4 = vec4_t{3.0f, 4.0f, 5.0f, 6.0f};
        CHECK(vec4.x == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(4.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(6.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization (parens)
    {
        vec4_t vec4 = vec4_t(3.0f, 4.0f, 5.0f, 6.0f);
        CHECK(vec4.x == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(4.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(5.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(6.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (braces)
    {
        vec4_t vec4 = vec4_t{50.0f};
        CHECK(vec4.x == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(50.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(50.0f).epsilon(g_epsilon));
    }

    // assignment initialization - single argument (braces)
    {
        vec4_t vec4;
        vec4 = vec4_t{99.0f};
        CHECK(vec4.x == Approx(99.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(99.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(99.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(99.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - single argument (parens)
    {
        vec4_t vec4 = vec4_t(25.0f);
        CHECK(vec4.x == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(25.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(25.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (braces)
    {
        vec4_t vec4 = vec4_t{vec3_t{1.0f, 2.0f, 3.0f}, 4.0f};
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (parens)
    {
        vec4_t vec4 = vec4_t(vec3_t(1.0f, 2.0f, 3.0f), 4.0f);
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (braces)
    {
        vec4_t vec4 = vec4_t{vec2_t{1.0f, 2.0f}, vec2_t{3.0f, 4.0f}};
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - double argument (parens)
    {
        vec4_t vec4 = vec4_t(vec2_t(1.0f, 2.0f), vec2_t(3.0f, 4.0f));
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - triple argument (braces)
    {
        vec4_t vec4 = vec4_t{vec2_t{1.0f, 2.0f}, 3.0f, 4.0f};
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct/copy initialization - triple argument (parens)
    {
        vec4_t vec4 = vec4_t(vec2_t(1.0f, 2.0f), 3.0f, 4.0f);
        CHECK(vec4.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(3.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(4.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization
    {
        vec4_t vec4_a(100.0f, 200.0f, 300.0f, 400.0f);
        vec4_t vec4_b(vec4_a);

        CHECK(vec4_b.x == Approx(100.0f).epsilon(g_epsilon));
        CHECK(vec4_b.y == Approx(200.0f).epsilon(g_epsilon));
        CHECK(vec4_b.z == Approx(300.0f).epsilon(g_epsilon));
        CHECK(vec4_b.w == Approx(400.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization
    {
        vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        vec4_t vec4_b = vec4_a;

        CHECK(vec4_b.x == Approx(500.0f).epsilon(g_epsilon));
        CHECK(vec4_b.y == Approx(600.0f).epsilon(g_epsilon));
        CHECK(vec4_b.z == Approx(700.0f).epsilon(g_epsilon));
        CHECK(vec4_b.w == Approx(800.0f).epsilon(g_epsilon));
    }

    // direct + copy initialization (assignment)
    {
        vec4_t vec4_a(500.0f, 600.0f, 700.0f, 800.0f);
        vec4_t vec4_b;

        vec4_b = vec4_a;

        CHECK(vec4_b.x == Approx(500.0f).epsilon(g_epsilon));
        CHECK(vec4_b.y == Approx(600.0f).epsilon(g_epsilon));
        CHECK(vec4_b.z == Approx(700.0f).epsilon(g_epsilon));
        CHECK(vec4_b.w == Approx(800.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("vec2_accessors", "[as_vec]")
{
    // member and subscript operator - zero initializer
    {
        vec2_t vec2{};
        CHECK(vec2.x == Approx(vec2[0]).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(vec2[1]).epsilon(g_epsilon));
    }

    // member and subscript operator - explicit construction
    {
        vec2_t vec2(1.0f, 2.0f);
        CHECK(vec2.x == Approx(vec2[0]).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(vec2[1]).epsilon(g_epsilon));
    }

    // member and const subscript operator - explicit construction
    {
        vec2_t vec2(1.0f, 2.0f);
        const real_t& x = vec2[0];
        const real_t& y = vec2[1];

        CHECK(vec2.x == Approx(x).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(y).epsilon(g_epsilon));
    }
}

TEST_CASE("vec3_accessors", "[as_vec]")
{
    // member and subscript operator - zero initializer
    {
        vec3_t vec3{};
        CHECK(vec3.x == Approx(vec3[0]).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(vec3[1]).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(vec3[2]).epsilon(g_epsilon));
    }

    // member and subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        CHECK(vec3.x == Approx(vec3[0]).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(vec3[1]).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(vec3[2]).epsilon(g_epsilon));
    }

    // member and subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        CHECK(vec3.xy()[0] == Approx(vec3.x).epsilon(g_epsilon));
        CHECK(vec3.xy()[1] == Approx(vec3.y).epsilon(g_epsilon));
        CHECK(vec3.xy().x == Approx(vec3.x).epsilon(g_epsilon));
        CHECK(vec3.xy().y == Approx(vec3.y).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(vec3[2]).epsilon(g_epsilon));
    }

    // member and const subscript operator - explicit construction
    {
        vec3_t vec3(1.0f, 2.0f, 3.0f);
        const real_t& x = vec3[0];
        const real_t& y = vec3[1];
        const real_t& z = vec3[2];

        CHECK(vec3.x == Approx(x).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(y).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(z).epsilon(g_epsilon));
    }
}

TEST_CASE("vec4_accessors", "[as_vec]")
{
    // member and subscript operator - zero initializer
    {
        vec4_t vec4{};
        CHECK(vec4.x == Approx(vec4[0]).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(vec4[1]).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(vec4[2]).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(vec4[3]).epsilon(g_epsilon));
    }

    // member and subscript operator - explicit construction
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        CHECK(vec4.x == Approx(vec4[0]).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(vec4[1]).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(vec4[2]).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(vec4[3]).epsilon(g_epsilon));
    }

    // member and subscript operator - explicit construction
    {
        vec4_t vec4(1.0f, 2.0f, 3.0f, 4.0f);
        CHECK(vec4.xy()[0] == Approx(vec4[0]).epsilon(g_epsilon));
        CHECK(vec4.xy()[1] == Approx(vec4[1]).epsilon(g_epsilon));
        CHECK(vec4.zw()[0] == Approx(vec4[2]).epsilon(g_epsilon));
        CHECK(vec4.zw()[1] == Approx(vec4[3]).epsilon(g_epsilon));
        CHECK(vec4.xyz()[0] == Approx(vec4[0]).epsilon(g_epsilon));
        CHECK(vec4.xyz()[1] == Approx(vec4[1]).epsilon(g_epsilon));
        CHECK(vec4.xyz()[2] == Approx(vec4[2]).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(vec4[3]).epsilon(g_epsilon));
    }
}

TEST_CASE("vec2_vec3_vec4_accessors", "[as_vec]")
{
    vec2_t vec2(1.0f, 2.0f);
    vec3_t vec3(vec2, 3.0f);

    vec4_t vec4_a(vec2, 3.0f, 4.0f);
    vec4_t vec4_b(vec2, vec2);
    vec4_t vec4_c(vec3, 4.0f);

    // member accessors
    CHECK(vec4_a.x == Approx(vec2.x).epsilon(g_epsilon));
    CHECK(vec4_a.y == Approx(vec2.y).epsilon(g_epsilon));

    CHECK(vec4_b.x == Approx(vec2.x).epsilon(g_epsilon));
    CHECK(vec4_b.y == Approx(vec2.y).epsilon(g_epsilon));
    CHECK(vec4_b.z == Approx(vec2.x).epsilon(g_epsilon));
    CHECK(vec4_b.w == Approx(vec2.y).epsilon(g_epsilon));

    CHECK(vec4_c.x == Approx(vec2.x).epsilon(g_epsilon));
    CHECK(vec4_c.y == Approx(vec2.y).epsilon(g_epsilon));
    CHECK(vec4_c.z == Approx(vec4_a.z).epsilon(g_epsilon));
    CHECK(vec4_c.w == Approx(vec4_a.w).epsilon(g_epsilon));
}

TEST_CASE("const_elem_access_vec_const", "[as_vec]")
{
    using gsl::make_span;

    const vec_t<real_t, 5> vec5(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);

    const real_t elem_0 = vec5[0];
    const real_t elem_1 = vec5[1];
    const real_t elem_2 = vec5[2];
    const real_t elem_3 = vec5[3];
    const real_t elem_4 = vec5[4];

    const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(vec5, 5));
}

TEST_CASE("elem_access_vec", "[as_vec]")
{
    using gsl::make_span;
    vec_t<real_t, 5> vec5(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);

    real_t elem_0 = vec5[0];
    real_t elem_1 = vec5[1];
    real_t elem_2 = vec5[2];
    real_t elem_3 = vec5[3];
    real_t elem_4 = vec5[4];

    const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3, elem_4};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(vec5, 5));
}

TEST_CASE("const_elem_access_vec2_3_4", "[as_vec]")
{
    using gsl::make_span;

    {
        const vec2_t vec2(15.0f, 30.0f);

        const real_t elem_0 = vec2[0];
        const real_t elem_1 = vec2[1];

        const real_t vec_arr[] = {elem_0, elem_1};
        CHECK_THAT(make_span(vec_arr), make_elements_sub(vec2, 2));
    }

    {
        const vec3_t vec3(2.0f, 3.0f, 4.0f);

        const real_t elem_0 = vec3[0];
        const real_t elem_1 = vec3[1];
        const real_t elem_2 = vec3[2];

        const real_t vec_arr[] = {elem_0, elem_1, elem_2};
        CHECK_THAT(make_span(vec_arr), make_elements_sub(vec3, 3));
    }

    {
        vec4_t vec4;
        vec4 = vec4_t(10.0f, 20.0f, 30.0f, 40.0f);

        const real_t elem_0 = vec4[0];
        const real_t elem_1 = vec4[1];
        const real_t elem_2 = vec4[2];
        const real_t elem_3 = vec4[3];

        const real_t vec_arr[] = {elem_0, elem_1, elem_2, elem_3};
        CHECK_THAT(make_span(vec_arr), make_elements_sub(vec4, 4));
    }
}

TEST_CASE("rvalue_elem_access_vec2_3_4_5", "[as_vec]")
{
    using gsl::make_span;

    auto make_vec2 = []() { return vec2_t{5.0f, 10.0f}; };
    CHECK(make_vec2()[0] == Approx(5.0f).epsilon(g_epsilon));
    CHECK(make_vec2()[1] == Approx(10.0f).epsilon(g_epsilon));

    auto make_vec3 = []() { return vec3_t{5.0f, 10.0f, 15.0f}; };
    CHECK(make_vec3()[0] == Approx(5.0f).epsilon(g_epsilon));
    CHECK(make_vec3()[1] == Approx(10.0f).epsilon(g_epsilon));
    CHECK(make_vec3()[2] == Approx(15.0f).epsilon(g_epsilon));

    auto make_vec4 = []() { return vec4_t{7.0f, 14.0f, 21.0f, 28.0f}; };
    CHECK(make_vec4()[0] == Approx(7.0f).epsilon(g_epsilon));
    CHECK(make_vec4()[1] == Approx(14.0f).epsilon(g_epsilon));
    CHECK(make_vec4()[2] == Approx(21.0f).epsilon(g_epsilon));
    CHECK(make_vec4()[3] == Approx(28.0f).epsilon(g_epsilon));

    auto make_vec5 = []() {
        return vec_t<real_t, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    };
    CHECK(make_vec5()[0] == Approx(1.0f).epsilon(g_epsilon));
    CHECK(make_vec5()[1] == Approx(2.0f).epsilon(g_epsilon));
    CHECK(make_vec5()[2] == Approx(3.0f).epsilon(g_epsilon));
    CHECK(make_vec5()[3] == Approx(4.0f).epsilon(g_epsilon));
    CHECK(make_vec5()[4] == Approx(5.0f).epsilon(g_epsilon));
}

TEST_CASE("vec_size", "[as_vec]")
{
    static_assert(vec2_t::size() == 2, "vec2_t size must be 2");
    index_t vec2_size;
    vec2_size = vec2_t::size();
    vec2_t vec2;
    index_t vec2_inst_size = vec::size(vec2);
    CHECK(vec2_size == 2);
    CHECK(vec2_inst_size == vec2_size);

    static_assert(vec3_t::size() == 3, "vec3_t size must be 3");
    index_t vec3_size;
    vec3_size = vec3_t::size();
    vec3_t vec3;
    index_t vec3_inst_size = vec::size(vec3);
    CHECK(vec3_size == static_cast<index_t>(3));
    CHECK(vec3_inst_size == Approx(vec3_size).epsilon(g_epsilon));

    static_assert(vec4_t::size() == 4, "vec4_t size must be 4");
    index_t vec4_size;
    vec4_size = vec4_t::size();
    vec4_t vec4;
    index_t vec4_inst_size = vec::size(vec4);
    CHECK(vec4_size == static_cast<index_t>(4));
    CHECK(vec4_inst_size == Approx(vec4_size).epsilon(g_epsilon));

    using short7 = vec_t<short, 7>;
    short7 vec_short7;
    index_t vec_short7_inst_size = vec::size(vec_short7);
    index_t short7_size;
    short7_size = short7::size();
    CHECK(short7_size == static_cast<index_t>(7));
    CHECK(vec_short7_inst_size == Approx(short7_size).epsilon(g_epsilon));

    using int5 = vec_t<int, 5>;
    int5 vec_short5;
    index_t vec_short5_inst_size = vec::size(vec_short5);
    index_t int5_size = int5::size();
    CHECK(int5_size == static_cast<index_t>(5));
    CHECK(vec_short5_inst_size == Approx(int5_size).epsilon(g_epsilon));
}

TEST_CASE("vec_make_from_arr", "[as_vec]")
{
    // generic make_from_arr vec2_t
    {
        real_t vec_data[2] = {2.0f, 4.0f};
        vec2_t vec2 = vec::from_arr(vec_data);

        CHECK(vec2.x == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));

        // won't compile (array length 2 to vec3_t)
        // vec3_t vec3 = make_from(vec_data);
    }

    // generic make_from_arr vec3_t
    {
        real_t vec_data[3] = {1.0f, 2.0f, 3.0f};
        vec3_t vec3 = vec::from_arr(vec_data);

        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // generic make_from_arr <char, 6>
    {
        char vec_data[6] = {11, 12, 13, 14, 15, 16};
        vec_t<char, 6> char_6 = vec::from_arr(vec_data);

        CHECK(char_6[0] == 11);
        CHECK(char_6[1] == 12);
        CHECK(char_6[2] == 13);
        CHECK(char_6[3] == 14);
        CHECK(char_6[4] == 15);
        CHECK(char_6[5] == 16);
    }

    // vec2::make_from_arr
    {
        real_t vec_data[2] = {2.0f, 4.0f};
        vec2_t vec2 = vec2::from_arr(vec_data);

        CHECK(vec2.x == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));
    }

    // vec3_make_from_arr
    {
        real_t vec_data[3] = {1.0f, 2.0f, 3.0f};
        vec3_t vec3 = vec3::from_arr(vec_data);

        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // vec4_make_from_arr
    {
        real_t vec_data[4] = {4.0f, 8.0f, 12.0f, 16.0f};
        vec4_t vec4 = vec4::from_arr(vec_data);

        CHECK(vec4.x == Approx(4.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(8.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(12.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(16.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("vec_make_from_ptr", "[as_vec]")
{
    // generic make_from_ptr vec2_t
    {
        std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(2);
        vec_data[0] = 2.0f;
        vec_data[1] = 4.0f;
        vec2_t vec2 = vec::from_ptr<real_t, 2>(vec_data.get());

        CHECK(vec2.x == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));
    }

    // generic make_from_ptr vec3_t
    {
        std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(3);
        vec_data[0] = 1.0f;
        vec_data[1] = 2.0f;
        vec_data[2] = 3.0f;
        vec3_t vec3 = vec::from_ptr<real_t, 3>(vec_data.get());

        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // generic make_from_ptr <char, 6>
    {
        std::unique_ptr<char[]> vec_data = std::make_unique<char[]>(6);
        vec_data[0] = 11;
        vec_data[1] = 12;
        vec_data[2] = 13;
        vec_data[3] = 14;
        vec_data[4] = 15;
        vec_data[5] = 16;
        vec_t<char, 6> char_6 = vec::from_ptr<char, 6>(vec_data.get());

        CHECK(char_6[0] == 11);
        CHECK(char_6[1] == 12);
        CHECK(char_6[2] == 13);
        CHECK(char_6[3] == 14);
        CHECK(char_6[4] == 15);
        CHECK(char_6[5] == 16);
    }

    // vec2::make_from_ptr
    {
        std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(2);
        vec_data[0] = 2.0f;
        vec_data[1] = 4.0f;
        vec2_t vec2 = vec2::from_ptr(vec_data.get());

        CHECK(vec2.x == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec2.y == Approx(4.0f).epsilon(g_epsilon));
    }

    // vec3_make_from_ptr
    {
        std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(3);
        vec_data[0] = 1.0f;
        vec_data[1] = 2.0f;
        vec_data[2] = 3.0f;
        vec3_t vec3 = vec3::from_ptr(vec_data.get());

        CHECK(vec3.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(vec3.y == Approx(2.0f).epsilon(g_epsilon));
        CHECK(vec3.z == Approx(3.0f).epsilon(g_epsilon));
    }

    // vec4_make_from_ptr
    {
        std::unique_ptr<real_t[]> vec_data = std::make_unique<real_t[]>(4);
        vec_data[0] = 4.0f;
        vec_data[1] = 8.0f;
        vec_data[2] = 12.0f;
        vec_data[3] = 16.0f;
        vec4_t vec4 = vec4::from_ptr(vec_data.get());

        CHECK(vec4.x == Approx(4.0f).epsilon(g_epsilon));
        CHECK(vec4.y == Approx(8.0f).epsilon(g_epsilon));
        CHECK(vec4.z == Approx(12.0f).epsilon(g_epsilon));
        CHECK(vec4.w == Approx(16.0f).epsilon(g_epsilon));
    }

    // generic type check
    {
        std::unique_ptr<double[]> vec_data = std::make_unique<double[]>(2);
        vec_data[0] = 2.0;
        vec_data[1] = 4.0;
        // does not compile - types do not match
        // vec_t<char, 2> char_2 = from_ptr<char, 2>(vec_data.get());
        // vec2_t vec2 = from_ptr<float, 2>(vec_data.get());
        vec_t<double, 2> vec2 = vec::from_ptr<double, 2>(vec_data.get());
        (void)vec2;
    }
}

TEST_CASE("addition", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '+'
    {
        vec5_t vec = vec5_t{10.0f, 20.0f, 30.0f, 40.0f, 50.0f} +
                     vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f};

        CHECK(vec::equal(vec, vec5_t(50.0f, 50.0f, 50.0f, 50.0f, 50.0f)));
    }

    // vec_t operator '+='
    {
        vec5_t vec1(10.0f, 20.0f, 30.0f, 40.0f, 50.0f);
        vec1 += vec5_t(25.0f, 15.0f, 5.0f, 10.0f, 1.0f);
        CHECK(vec::equal(vec1, vec5_t(35.0f, 35.0f, 35.0f, 50.0f, 51.0f)));
    }
}

TEST_CASE("addition_vec3", "[as_vec]")
{
    // vec3_t operator '+'
    {
        vec3_t vec = vec3_t{10.0f, 20.0f, 30.0f} + vec3_t{20.0f, 10.0f, 0.0f};
        CHECK(vec::equal(vec, vec3_t(30.0f, 30.0f, 30.0f)));
    }

    // vec3_t operator '+='
    {
        vec3_t vec(10.0f, 20.0f, 30.0f);
        vec += vec3_t(25.0f, 15.0f, 5.0f);
        CHECK(vec::equal(vec, vec3_t(35.0f, 35.0f, 35.0f)));
    }
}

TEST_CASE("substraction", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '-'
    {
        vec5_t vec = vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f} -
                     vec5_t{10.0f, 20.0f, 30.0f, 40.0f, 50.0f};

        CHECK(vec::equal(vec, vec5_t(30.0f, 10.0f, -10.0f, -30.0f, -50.0f)));
    }

    // vec_t operator '-='
    {
        vec5_t vec(10.0f, 20.0f, 30.0f, 40.0f, 50.0f);
        vec -= vec5_t(25.0f, 15.0f, 5.0f, 10.0f, 1.0f);
        CHECK(vec::equal(vec, vec5_t(-15.0f, 5.0f, 25.0f, 30.0f, 49.0f)));
    }
}

TEST_CASE("substraction_vec3", "[as_vec]")
{
    // vec3_t operator '-'
    {
        vec3_t vec = vec3_t{40.0f, 30.0f, 20.0f} - vec3_t{10.0f, 20.0f, 30.0f};
        CHECK(vec::equal(vec, vec3_t(30.0f, 10.0f, -10.0f)));
    }

    // vec3_t operator '-='
    {
        vec3_t vec(10.0f, 20.0f, 30.0f);
        vec -= vec3_t(25.0f, 15.0f, 5.0f);
        CHECK(vec::equal(vec, vec3_t(-15.0f, 5.0f, 25.0f)));
    }
}

TEST_CASE("negation", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    vec5_t vec = vec5_t{40.0f, 30.0f, 20.0f, 10.0f, 0.0f};
    vec5_t neg_vec = -vec;
    CHECK(vec::equal(neg_vec, vec5_t(-40.0f, -30.0f, -20.0f, -10.0f, -0.0f)));
}

TEST_CASE("negation_vec3", "[as_vec]")
{
    vec3_t vec = vec3_t{20.0f, 10.0f, 0.0f};
    vec3_t neg_vec = -vec;
    CHECK(vec::equal(neg_vec, vec3_t(-20.0f, -10.0f, -0.0f)));
}

TEST_CASE("multiplication_scalar", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '*'
    {
        vec5_t vec = real_t(5.0) * vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        CHECK(vec::equal(vec, vec5_t(250.0f, 200.0f, 125.0f, 100.0f, 50.0f)));
    }

    // vec_t operator '*='
    {
        vec5_t vec = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        vec *= real_t(5.0);
        CHECK(vec::equal(vec, vec5_t(250.0f, 200.0f, 125.0f, 100.0f, 50.0f)));
    }
}

TEST_CASE("multiplication_scalar_vec3", "[as_vec]")
{
    // vec3_t operator '*'
    {
        vec3_t vec = real_t(5.0) * vec3_t{50.0f, 40.0f, 25.0f};
        CHECK(vec::equal(vec, vec3_t(250.0f, 200.0f, 125.0)));
    }

    // vec3_t operator '*='
    {
        vec3_t vec = vec3_t{50.0f, 40.0f, 25.0f};
        vec *= real_t(5.0);
        CHECK(vec::equal(vec, vec3_t(250.0f, 200.0f, 125.0)));
    }
}

TEST_CASE("multiplication_vector", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '*'
    {
        vec5_t vec = vec5_t{2.0f, 3.0f, 4.0f, 5.0f, 0.5f} *
                     vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};

        CHECK(vec::equal(vec, vec5_t(100.0f, 120.0f, 100.0f, 100.0f, 5.0f)));
    }

    // vec_t operator '*='
    {
        vec5_t vec1 = vec5_t{2.0f, 3.0f, 4.0f, 5.0f, 0.5f};
        vec5_t vec2 = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        vec1 *= vec2;
        CHECK(vec::equal(vec1, vec5_t(100.0f, 120.0f, 100.0f, 100.0f, 5.0f)));
    }
}

TEST_CASE("multiplication_vector_vec3", "[as_vec]")
{
    // vec_t operator '*'
    {
        vec3_t vec = vec3_t{0.5f, 3.0f, 4.0f} * vec3_t{50.0f, 40.0f, 25.0f};
        CHECK(vec::equal(vec, vec3_t(25.0f, 120.0f, 100.0f)));
    }

    // vec_t operator '*='
    {
        vec3_t vec1 = vec3_t{0.5f, 3.0f, 4.0f};
        vec3_t vec2 = vec3_t{50.0f, 40.0f, 25.0f};
        vec1 *= vec2;
        CHECK(vec::equal(vec1, vec3_t(25.0f, 120.0f, 100.0f)));
    }
}

TEST_CASE("divide_scalar", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '/'
    {
        vec5_t vec = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f} / real_t(5.0);
        CHECK(vec::equal(vec, vec5_t(10.0f, 8.0f, 5.0f, 4.0f, 2.0f)));
    }

    // vec_t operator '/='
    {
        vec5_t vec = vec5_t{50.0f, 40.0f, 25.0f, 20.0f, 10.0f};
        vec /= real_t(5.0f);
        CHECK(vec::equal(vec, vec5_t(10.0f, 8.0f, 5.0f, 4.0f, 2.0f)));
    }
}

TEST_CASE("divide_scalar_vec3", "[as_vec]")
{
    // vec_t operator '/'
    {
        vec3_t vec = vec3_t{50.0f, 40.0f, 25.0f} / real_t(5.0);
        CHECK(vec::equal(vec, vec3_t(10.0f, 8.0f, 5.0f)));
    }

    // vec_t operator '/='
    {
        vec3_t vec = vec3_t{50.0f, 40.0f, 25.0f};
        vec /= real_t(5.0);
        CHECK(vec::equal(vec, vec3_t(10.0f, 8.0f, 5.0f)));
    }
}

TEST_CASE("divide_vector", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // vec_t operator '/'
    {
        vec5_t vec = vec5_t{33.0f, 48.0f, 10.0f, 120.0f, 2.0f} /
                     vec5_t{3.0f, 6.0f, 2.0f, 3.0f, 0.5f};

        CHECK(vec::equal(vec, vec5_t(11.0f, 8.0f, 5.0f, 40.0f, 4.0f)));
    }

    // vec_t operator '/='
    {
        vec5_t vec1 = vec5_t{33.0f, 48.0f, 10.0f, 120.0f, 2.0f};
        vec5_t vec2 = vec5_t{3.0f, 6.0f, 2.0f, 3.0f, 0.5f};
        vec1 /= vec2;
        CHECK(vec::equal(vec1, vec5_t(11.0f, 8.0f, 5.0f, 40.0f, 4.0f)));
    }
}

TEST_CASE("divide_vector_vec3", "[as_vec]")
{
    // vec_t operator '/'
    {
        vec3_t vec = vec3_t{33.0f, 48.0f, 10.0f} / vec3_t{3.0f, 6.0f, 2.0f};
        CHECK(vec::equal(vec, vec3_t(11.0f, 8.0f, 5.0f)));
    }

    // vec_t operator '/='
    {
        vec3_t vec1 = vec3_t{33.0f, 48.0f, 10.0f};
        vec3_t vec2 = vec3_t{3.0f, 6.0f, 2.0f};
        vec1 /= vec2;
        CHECK(vec::equal(vec1, vec3_t(11.0f, 8.0f, 5.0f)));
    }
}

TEST_CASE("dot", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    // note: comparison values calculated using - http://calculator.vhex.net
    {
        const vec5_t vec1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
        const vec5_t vec2(4.0f, 5.0f, 6.0f, 8.0f, 4.0f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(84.0f).epsilon(g_epsilon));
    }

    {
        const vec5_t vec1(-50.0f, 20.0f, 9.0f, 11.0f, 3.0f);
        const vec5_t vec2(-1.0f, -7.0f, 4.0f, 2.0f, 0.5f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(-30.5).epsilon(g_epsilon));
    }

    {
        const vec5_t vec1(-2.3f, 0.1f, 0.92f, 0.123f, 0.543f);
        const vec5_t vec2(-1.456f, -7.732f, 2.491f, -1.321f, -0.261f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(4.563114f).epsilon(g_epsilon));
    }
}

TEST_CASE("dot_vec3", "[as_vec]")
{
    // note: comparison values calculated using - http://calculator.vhex.net
    {
        const vec3_t vec1(1.0f, 2.0f, 3.0f);
        const vec3_t vec2(4.0f, 5.0f, 6.0f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(32.0f).epsilon(g_epsilon));
    }

    {
        const vec3_t vec1(-50.0f, 20.0f, 9.0f);
        const vec3_t vec2(-1.0f, -7.0f, 4.0f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(-54.0f).epsilon(g_epsilon));
    }

    {
        const vec3_t vec1(-2.3f, 0.1f, 0.92f);
        const vec3_t vec2(-1.456f, -7.732f, 2.491f);

        const real_t dot_result = vec::dot(vec1, vec2);
        CHECK(dot_result == Approx(4.86732f).epsilon(g_epsilon));
    }
}

TEST_CASE("axes_vec2", "[as_vec]")
{
    using gsl::make_span;

    constexpr real_t x_axis[] = {1.0f, 0.0f};
    CHECK_THAT(make_span(x_axis), make_elements_sub(vec2::axis_x(), 2));

    constexpr real_t y_axis[] = {0.0f, 1.0f};
    CHECK_THAT(make_span(y_axis), make_elements_sub(vec2::axis_y(), 2));

    constexpr real_t zero[] = {0.0f, 0.0f};
    CHECK_THAT(make_span(zero), make_elements_sub(vec2::zero(), 2));

    constexpr real_t one[] = {1.0f, 1.0f};
    CHECK_THAT(make_span(one), make_elements_sub(vec2::one(), 2));

    constexpr real_t max_val[] = {REAL_MAX, REAL_MAX};
    CHECK_THAT(make_span(max_val), make_elements_sub(vec2::max(), 2));

    constexpr real_t min_val[] = {REAL_MIN, REAL_MIN};
    CHECK_THAT(make_span(min_val), make_elements_sub(vec2::min(), 2));
}

TEST_CASE("axes_vec3", "[as_vec]")
{
    using gsl::make_span;

    constexpr real_t x_axis[] = {1.0f, 0.0f, 0.0f};
    CHECK_THAT(make_span(x_axis), make_elements_sub(vec3::axis_x(), 3));

    constexpr real_t y_axis[] = {0.0f, 1.0f, 0.0f};
    CHECK_THAT(make_span(y_axis), make_elements_sub(vec3::axis_y(), 3));

    constexpr real_t z_axis[] = {0.0f, 0.0f, 1.0f};
    CHECK_THAT(make_span(z_axis), make_elements_sub(vec3::axis_z(), 3));

    constexpr real_t zero[] = {0.0f, 0.0f, 0.0f};
    CHECK_THAT(make_span(zero), make_elements_sub(vec3::zero(), 3));

    constexpr real_t one[] = {1.0f, 1.0f, 1.0f};
    CHECK_THAT(make_span(one), make_elements_sub(vec3::one(), 3));

    constexpr real_t max_val[] = {REAL_MAX, REAL_MAX, REAL_MAX};
    CHECK_THAT(make_span(max_val), make_elements_sub(vec3::max(), 3));

    constexpr real_t min_val[] = {REAL_MIN, REAL_MIN, REAL_MIN};
    CHECK_THAT(make_span(min_val), make_elements_sub(vec3::min(), 3));
}

TEST_CASE("axes_vec4", "[as_vec]")
{
    using gsl::make_span;

    constexpr real_t x_axis[] = {1.0f, 0.0f, 0.0f, 0.0f};
    CHECK_THAT(make_span(x_axis), make_elements_sub(vec4::axis_x(), 4));

    constexpr real_t y_axis[] = {0.0f, 1.0f, 0.0f, 0.0f};
    CHECK_THAT(make_span(y_axis), make_elements_sub(vec4::axis_y(), 4));

    constexpr real_t z_axis[] = {0.0f, 0.0f, 1.0f, 0.0f};
    CHECK_THAT(make_span(z_axis), make_elements_sub(vec4::axis_z(), 4));

    constexpr real_t w_axis[] = {0.0f, 0.0f, 0.0f, 1.0f};
    CHECK_THAT(make_span(w_axis), make_elements_sub(vec4::axis_w(), 4));

    constexpr real_t zero[] = {0.0f, 0.0f, 0.0f, 0.0f};
    CHECK_THAT(make_span(zero), make_elements_sub(vec4::zero(), 4));

    constexpr real_t one[] = {1.0f, 1.0f, 1.0f, 1.0f};
    CHECK_THAT(make_span(one), make_elements_sub(vec4::one(), 4));

    constexpr real_t max_val[] = {REAL_MAX, REAL_MAX, REAL_MAX, REAL_MAX};
    CHECK_THAT(make_span(max_val), make_elements_sub(vec4::max(), 4));

    constexpr real_t min_val[] = {REAL_MIN, REAL_MIN, REAL_MIN, REAL_MIN};
    CHECK_THAT(make_span(min_val), make_elements_sub(vec4::min(), 4));
}

TEST_CASE("cross", "[as_vec]")
{
    // note: comparison values calculated using
    // https://www.symbolab.com/solver/vector-cross-product-calculator
    {
        vec3_t vec1(1.0f, 2.0f, 3.0f);
        vec3_t vec2(4.0f, 5.0f, 6.0f);

        vec3_t cross_result = vec3::cross(vec1, vec2);
        CHECK(cross_result.x == Approx(-3.0f).epsilon(g_epsilon));
        CHECK(cross_result.y == Approx(6.0f).epsilon(g_epsilon));
        CHECK(cross_result.z == Approx(-3.0f).epsilon(g_epsilon));
    }

    {
        vec3_t vec1(1.0f, 0.0f, 0.0f);
        vec3_t vec2(0.0f, 1.0f, 0.0f);

        vec3_t cross_result1 = vec3::cross(vec1, vec2);
        CHECK(cross_result1.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(cross_result1.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(cross_result1.z == Approx(1.0f).epsilon(g_epsilon));

        vec3_t cross_result2 = vec3::cross(vec2, vec1);
        CHECK(cross_result2.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(cross_result2.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(cross_result2.z == Approx(-1.0f).epsilon(g_epsilon));
    }

    {
        vec3_t vec1(0.0f, 5.0f, 0.0f);
        vec3_t vec2(0.0f, 0.0f, 12.0f);

        vec3_t cross_result = vec3::cross(vec1, vec2);
        CHECK(cross_result.x == Approx(60.0f).epsilon(g_epsilon));
        CHECK(cross_result.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(cross_result.z == Approx(0.0f).epsilon(g_epsilon));
    }

    {
        vec3_t x(1.0f, 0.0f, 0.0f);
        vec3_t y(0.0f, 1.0f, 0.0f);
        vec3_t z(0.0f, 0.0f, 1.0f);

        vec3_t cross_result1 = vec3::cross(x, y);
        CHECK(cross_result1.z == Approx(1.0f).epsilon(g_epsilon));

        vec3_t cross_result2 = vec3::cross(y, z);
        CHECK(cross_result2.x == Approx(1.0f).epsilon(g_epsilon));

        vec3_t cross_result3 = vec3::cross(z, x);
        CHECK(cross_result3.y == Approx(1.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("right_and_up", "[as_vec]")
{
    {
        vec3_t dir(0.0f, 0.0f, 1.0f);

        vec3_t across_lh;
        vec3_t up_lh;
        vec3::right_and_up_lh(dir, across_lh, up_lh);

        CHECK(across_lh.x == Approx(1.0f).epsilon(g_epsilon));
        CHECK(across_lh.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(across_lh.z == Approx(0.0f).epsilon(g_epsilon));

        CHECK(up_lh.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(up_lh.y == Approx(1.0f).epsilon(g_epsilon));
        CHECK(up_lh.z == Approx(0.0f).epsilon(g_epsilon));
    }

    {
        vec3_t dir(0.0f, 0.0f, 1.0f);

        vec3_t across_rh;
        vec3_t up_rh;
        vec3::right_and_up_rh(dir, across_rh, up_rh);

        CHECK(across_rh.x == Approx(-1.0f).epsilon(g_epsilon));
        CHECK(across_rh.y == Approx(0.0f).epsilon(g_epsilon));
        CHECK(across_rh.z == Approx(0.0f).epsilon(g_epsilon));

        CHECK(up_rh.x == Approx(0.0f).epsilon(g_epsilon));
        CHECK(up_rh.y == Approx(1.0f).epsilon(g_epsilon));
        CHECK(up_rh.z == Approx(0.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("equal", "[as_vec]")
{
    {
        vec3_t vec1(1.11f, 0.3f, 517.2f);
        vec3_t vec2(1.11f, 0.3f, 517.2f);

        CHECK(vec::equal(vec1, vec2));
    }

    {
        vec3_t vec1(1.11f, 0.3f, 514.2f);
        vec3_t vec2(1.114f, 0.3f, 517.2f);

        CHECK_FALSE(vec::equal(vec1, vec2));
    }

    {
        vec3_t vec1(1.11f, 0.3f, 514.2f);
        vec3_t vec2(1.11f, 0.311f, 514.2f);

        CHECK_FALSE(vec::equal(vec1, vec2));
    }
}

TEST_CASE("abs", "[as_vec]")
{
    {
        vec4_t vec(-1.0f, -2.0f, -100.0f, -7.0f);
        vec4_t result = vec::abs(vec);

        vec4_t vec_reference = {1.0f, 2.0f, 100.0f, 7.0f};

        CHECK(vec::equal(vec_reference, result));
    }

    {
        vec4_t vec{1.0f, 4.0f, 6.0f, 50.0f};
        vec4_t result = vec::abs(vec);

        vec4_t vec_reference = {1.0f, 4.0f, 6.0f, 50.0f};

        CHECK(vec::equal(vec_reference, result));
    }

    {
        using vec5_t = vec_t<real_t, 5>;

        vec5_t vec5{-1.0f, -2.0f, -100.0f, -7.0f, -4.0f};
        vec5_t result = vec::abs(vec5);

        vec5_t vec_reference = {1.0f, 2.0f, 100.0f, 7.0f, 4.0f};

        CHECK(vec::equal(vec_reference, result));
    }
}

TEST_CASE("min_vec", "[as_vec]")
{
    {
        vec4_t vec1(-1.0f, 2.0f, -100.0f, -7.0f);
        vec4_t vec2(-10.0f, 7.0f, -50.0f, -16.0f);

        vec4_t vec_reference(-10.0f, 2.0f, -100.0f, -16.0f);

        vec4_t result = vec::min(vec1, vec2);

        CHECK(vec::equal(vec_reference, result));
    }

    {
        vec4_t vec1(1.0f, 2.0f, 3.0f, 4.0f);
        vec4_t vec2(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t vec_reference(1.0f, 2.0f, 3.0f, 4.0f);

        vec4_t result = vec::min(vec1, vec2);

        CHECK(vec::equal(vec_reference, result));
    }
}

TEST_CASE("min_elem", "[as_vec]")
{
    {
        vec3_t vec{-1.0f, 2.0f, -100.0f};
        real_t result = vec::min_elem(vec);

        CHECK(result == Approx(-100.0f).epsilon(g_epsilon));
    }

    {
        vec3_t vec{1.0f, 2.0f, 3.0f};
        real_t result = vec::min_elem(vec);

        CHECK(result == Approx(1.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("max_vec", "[as_vec]")
{
    {
        vec4_t vec1(-1.0f, 2.0f, -100.0f, -7.0f);
        vec4_t vec2(-10.0f, 7.0f, -50.0f, -16.0f);

        vec4_t vec_reference(-1.0f, 7.0f, -50.0f, -7.0f);

        vec4_t result = vec::max(vec1, vec2);

        CHECK(vec::equal(vec_reference, result));
    }

    {
        vec4_t vec1(1.0f, 2.0f, 3.0f, 4.0f);
        vec4_t vec2(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t vec_reference(2.0f, 3.0f, 4.0f, 5.0f);

        vec4_t result = vec::max(vec1, vec2);

        CHECK(vec::equal(vec_reference, result));
    }
}

TEST_CASE("max_elem", "[as_vec]")
{
    {
        vec3_t vec{-1.0f, 2.0f, -100.0f};
        real_t result = vec::max_elem(vec);

        CHECK(result == Approx(2.0f).epsilon(g_epsilon));
    }

    {
        vec3_t vec{1.0f, 2.0f, 3.0f};
        real_t result = vec::max_elem(vec);

        CHECK(result == Approx(3.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("clamp", "[as_vec]")
{
    {
        vec3_t min_val(50.0f, 50.0f, 50.0f);
        vec3_t max_val(100.0f, 100.0f, 100.0f);

        vec3_t vec(20.0f, 20.0f, 20.0f);

        vec3_t result = vec::clamp(vec, min_val, max_val);

        CHECK(vec::equal(result, min_val));
    }

    {
        vec3_t min_val(50.0f, 50.0f, 50.0f);
        vec3_t max_val(100.0f, 100.0f, 100.0f);

        vec3_t vec(120.0f, 200.0f, 300.0f);

        vec3_t result = vec::clamp(vec, min_val, max_val);

        CHECK(vec::equal(result, max_val));
    }

    {
        vec3_t min_val(50.0f, 50.0f, 50.0f);
        vec3_t max_val(100.0f, 100.0f, 100.0f);

        vec3_t vec(20.0f, 120.0f, 20.0f);
        vec3_t vec_reference(50.0f, 100.0f, 50.0f);

        vec3_t result = vec::clamp(vec, min_val, max_val);

        CHECK(vec::equal(result, vec_reference));
    }

    {
        vec3_t min_val(50.0f, 50.0f, 50.0f);
        vec3_t max_val(100.0f, 100.0f, 100.0f);

        vec3_t vec(62.0f, 56.0f, 72.0f);

        vec3_t result = vec::clamp(vec, min_val, max_val);

        CHECK(vec::equal(result, vec));
    }
}

TEST_CASE("saturate", "[as_vec]")
{
    {
        vec3_t vec(-2.0f, 0.5f, 1.2f);
        vec3_t result = vec::saturate(vec);

        vec3_t vec_reference(0.0f, 0.5f, 1.0f);

        CHECK(vec::equal(result, vec_reference));
    }

    {
        vec3_t vec(3.0f, 0.1f, -1.2f);
        vec3_t result = vec::saturate(vec);

        vec3_t vec_reference(1.0f, 0.1f, 0.0f);

        CHECK(vec::equal(result, vec_reference));
    }
}

TEST_CASE("lerp", "[as_vec]")
{
    {
        using gsl::make_span;

        vec3_t start(0.0f, 10.0f, 20.0f);
        vec3_t end(10.0f, 40.0f, 100.0f);

        vec3_t result_begin = vec::lerp(real_t(0.0), start, end);
        vec3_t result_mid = vec::lerp(real_t(0.5), start, end);
        vec3_t result_end = vec::lerp(real_t(1.0), start, end);

        const real_t result_begin_arr[] = {0.0f, 10.0f, 20.0f};
        CHECK_THAT(
            make_span(result_begin_arr), make_elements_sub(result_begin, 3));

        const real_t result_mid_arr[] = {5.0f, 25.0f, 60.0f};
        CHECK_THAT(make_span(result_mid_arr), make_elements_sub(result_mid, 3));

        const real_t result_end_arr[] = {10.0f, 40.0f, 100.0f};
        CHECK_THAT(make_span(result_end_arr), make_elements_sub(result_end, 3));
    }
}

TEST_CASE("normalize_return_length", "[as_vec]")
{
    const vec3_t vec(3.0f, 4.0f, 0.0f);
    vec3_t vec_normalized;
    const real_t length = vec::normalize_return_length(vec, vec_normalized);

    CHECK(length == Approx(5.0f).epsilon(g_epsilon));
    CHECK(vec::length(vec_normalized) == Approx(1.0f).epsilon(g_epsilon));
}

TEST_CASE("length_squared_v3", "[as_vec]")
{
    const vec3_t vec(3.0f, 4.0f, 0.0f);
    const real_t length_sq = vec::length_sq(vec);

    CHECK(length_sq == Approx(25.0f).epsilon(g_epsilon));
}

TEST_CASE("length_squared_generic", "[as_vec]")
{
    using vec5_t = vec_t<real_t, 5>;

    const vec5_t vec(3.0f, 4.0f, 5.0f, 6.0f, 7.0f);
    const real_t length_sq = vec::length_sq(vec);

    CHECK(length_sq == Approx(135.0f).epsilon(g_epsilon));
}

TEST_CASE("select", "[as_vec]")
{
    using int3 = vec_t<int, 3>;

    int3 a(1, 2, 3);
    int3 b(5, 6, 7);

    using byte4 = vec_t<u8, 4>;

    byte4 c(u8(255), u8(255), u8(255), u8(255));
    byte4 d(u8(0), u8(0), u8(0), u8(0));

    int3 result = vec::select(a, b, true);
    byte4 result_byte = vec::select(c, d, false);

    CHECK(result[0] == 1);
    CHECK(result[1] == 2);
    CHECK(result[2] == 3);

    CHECK(result_byte[0] == 0);
    CHECK(result_byte[1] == 0);
    CHECK(result_byte[2] == 0);
    CHECK(result_byte[3] == 0);
}

TEST_CASE("wedge_vec2", "[as_vec]")
{
    {
        const vec2_t vec1(2.0f, 0.0f);
        const vec2_t vec2(0.0f, 2.0f);
        const real_t result = vec2::wedge(vec1, vec2);

        CHECK(result == Approx(4.0f).epsilon(g_epsilon));
    }

    {
        const vec2_t vec1(10.0f, 10.0f);
        const vec2_t vec2(20.0f, 5.0f);
        const real_t result = vec2::wedge(vec1, vec2);

        CHECK(result == Approx(-150.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("vec_to_arr", "[as_vec]")
{
    using gsl::make_span;

    vec_t<real_t, 5> vec5{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

    real_t vec5_arr[5];
    vec::to_arr(vec5, vec5_arr);

    CHECK_THAT(make_span(vec5_arr), make_elements_sub(vec5, 5));
}

} // namespace unit_test

// explicit instantiations (for coverage)

// types
template struct as::vec_t<as::real_t, 2>;
template struct as::vec_t<as::real_t, 3>;
template struct as::vec_t<as::real_t, 4>;
template struct as::vec_t<as::real_t, 5>;

#ifdef __GNUC__
// constructor
template as::vec_t<as::real_t, 5>::vec_t(
    as::real_t, as::real_t, as::real_t, as::real_t, as::real_t) noexcept;
#endif // __GNUC__

// operators
template const as::vec_t<as::real_t, 5> as::operator+(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator-(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator-(
    const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator*(
    const as::vec_t<as::real_t, 5>&, as::real_t);
template const as::vec_t<as::real_t, 5> as::operator*(
    as::real_t, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator*(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template const as::vec_t<as::real_t, 5> as::operator/(
    const as::vec_t<as::real_t, 5>&, as::real_t);
template const as::vec_t<as::real_t, 5> as::operator/(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);

// functions
template void as::vec::to_arr(
    const as::vec_t<as::real_t, 5>& vec, as::real_t (&data)[5]);
template as::index_t as::vec::size<as::real_t, 5>(
    const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec::dot(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec::normalize_return_length(
    const as::vec_t<as::real_t, 5>&, as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::min(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec::min_elem(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::max(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&);
template as::real_t as::vec::max_elem(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::abs(const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::clamp(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&,
    const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::saturate(
    const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::lerp(
    as::real_t t, const as::vec_t<as::real_t, 5>&,
    const as::vec_t<as::real_t, 5>&);
template as::vec_t<as::real_t, 5> as::vec::select(
    const as::vec_t<as::real_t, 5>&, const as::vec_t<as::real_t, 5>&, bool);
