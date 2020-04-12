#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::point2_t;
using as::point3_t;
using as::real_t;
using as::vec2_t;
using as::vec3_t;

// functions
using as::deg_to_rad;

// namespaces
namespace point = as::point;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("point2_initialization", "[as_point]")
{
    {
        point2_t point2;
        point2 = point2_t{2.0f, 4.0f};

        CHECK(point2[0] == Approx(2.0f).epsilon(g_epsilon));
        CHECK(point2[1] == Approx(4.0f).epsilon(g_epsilon));
    }

    {
        point2_t point2;
        point2 = point2_t{5.0f};

        CHECK(point2[0] == Approx(5.0f).epsilon(g_epsilon));
        CHECK(point2[1] == Approx(5.0f).epsilon(g_epsilon));
    }

    {
        vec2_t vec2 = vec2_t{10.0f, 20.0f};

        point2_t point2;
        point2 = point2_t{vec2};

        CHECK(point2[0] == Approx(10.0f).epsilon(g_epsilon));
        CHECK(point2[1] == Approx(20.0f).epsilon(g_epsilon));
    }

    {
        auto make_point = []() { return point2_t{1.0f, 2.0f}; };

        CHECK(make_point()[0] == Approx(1.0f).epsilon(g_epsilon));
        CHECK(make_point()[1] == Approx(2.0f).epsilon(g_epsilon));
    }

    {
        const point2_t point2 = point2_t{20.0f, 40.0f};

        const real_t& x = point2[0];
        const real_t& y = point2[1];

        CHECK(x == Approx(20.0f).epsilon(g_epsilon));
        CHECK(y == Approx(40.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("point3_initialization", "[as_point]")
{
    {
        point3_t point3;
        point3 = point3_t{2.0f, 4.0f, 6.0f};

        CHECK(point3[0] == Approx(2.0f).epsilon(g_epsilon));
        CHECK(point3[1] == Approx(4.0f).epsilon(g_epsilon));
        CHECK(point3[2] == Approx(6.0f).epsilon(g_epsilon));
    }

    {
        point3_t point3;
        point3 = point3_t{5.0f};

        CHECK(point3[0] == Approx(5.0f).epsilon(g_epsilon));
        CHECK(point3[1] == Approx(5.0f).epsilon(g_epsilon));
        CHECK(point3[2] == Approx(5.0f).epsilon(g_epsilon));
    }

    {
        vec3_t vec3 = vec3_t{10.0f, 20.0f, 30.0f};

        point3_t point3;
        point3 = point3_t{vec3};

        CHECK(point3[0] == Approx(10.0f).epsilon(g_epsilon));
        CHECK(point3[1] == Approx(20.0f).epsilon(g_epsilon));
        CHECK(point3[2] == Approx(30.0f).epsilon(g_epsilon));
    }

    {
        vec2_t vec2 = vec2_t{10.0f, 20.0f};
        real_t real = 30.0f;

        point3_t point3;
        point3 = point3_t{vec2, real};

        CHECK(point3[0] == Approx(10.0f).epsilon(g_epsilon));
        CHECK(point3[1] == Approx(20.0f).epsilon(g_epsilon));
        CHECK(point3[2] == Approx(30.0f).epsilon(g_epsilon));
    }

    {
        auto make_point = []() { return point3_t{1.0f, 2.0f, 3.0f}; };

        CHECK(make_point()[0] == Approx(1.0f).epsilon(g_epsilon));
        CHECK(make_point()[1] == Approx(2.0f).epsilon(g_epsilon));
        CHECK(make_point()[2] == Approx(3.0f).epsilon(g_epsilon));
    }

    {
        const point3_t point3 = point3_t{20.0f, 40.0f, 60.0f};

        const real_t& x = point3[0];
        const real_t& y = point3[1];
        const real_t& z = point3[2];

        CHECK(x == Approx(20.0f).epsilon(g_epsilon));
        CHECK(y == Approx(40.0f).epsilon(g_epsilon));
        CHECK(z == Approx(60.0f).epsilon(g_epsilon));
    }
}

TEST_CASE("point2_equals", "[as_point]")
{
    {
        const point2_t point2_a = point2_t{12.0f, 14.0f};
        const point2_t point2_b = point2_t{12.0f, 14.0f};

        CHECK(point::equal(point2_a, point2_b));
    }

    {
        const point2_t point2_a = point2_t{5.0f, 6.0f};
        const point2_t point2_b = point2_t{4.9f, 6.1f};

        CHECK(!point::equal(point2_a, point2_b));
    }
}

TEST_CASE("point3_equals", "[as_point]")
{
    {
        const point3_t point3_a = point3_t{20.0f, 40.0f, 60.0f};
        const point3_t point3_b = point3_t{20.0f, 40.0f, 60.0f};

        CHECK(point::equal(point3_a, point3_b));
    }

    {
        const point3_t point3_a = point3_t{20.0f, 40.0f, 60.0f};
        const point3_t point3_b = point3_t{19.0f, 40.0f, 60.0f};

        CHECK(!point::equal(point3_a, point3_b));
    }
}

TEST_CASE("point2_addition", "[as_point]")
{
    using gsl::make_span;

    const point2_t point2 = point2_t{18.0f, 22.0f};
    const vec2_t vec2 = vec2_t{32.0f, 28.0f};

    const point2_t result = point2 + vec2;

    const real_t result_ref_arr[] = {50.0f, 50.0f};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));

    point2_t result_mut = {};
    result_mut += vec2_t{1.0f, 2.0f};

    const real_t result_ref_arr_mut[] = {1.0f, 2.0f};
    CHECK_THAT(make_span(result_ref_arr_mut), make_elements_sub(result_mut, 2));
}

TEST_CASE("point3_addition", "[as_point]")
{
    using gsl::make_span;

    const point3_t point3 = point3_t{20.0f, 40.0f, 60.0f};
    const vec3_t vec3 = vec3_t{80.0f, 60.0f, 40.0f};

    const point3_t result = point3 + vec3;

    const real_t result_ref_arr[] = {100.0f, 100.0f, 100.0f};
    CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));

    point3_t result_mut = {};
    result_mut += vec3_t{1.0f, 2.0f, 3.0f};

    const real_t result_ref_arr_mut[] = {1.0f, 2.0f, 3.0f};
    CHECK_THAT(make_span(result_ref_arr_mut), make_elements_sub(result_mut, 3));
}

TEST_CASE("point2_substraction", "[as_point]")
{
    using gsl::make_span;

    {
        const point2_t point2_a = point2_t{18.0f, 22.0f};
        const point2_t point2_b = point2_t{32.0f, 28.0f};

        const vec2_t result = point2_b - point2_a;

        const real_t result_ref_arr[] = {14.0f, 6.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));
    }

    {
        const point2_t point2 = point2_t{18.0f, 22.0f};
        const vec2_t vec2 = vec2_t{32.0f, 28.0f};

        const point2_t result = point2 - vec2;

        const real_t result_ref_arr[] = {-14.0f, -6.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 2));
    }

    {
        const point2_t point2 = point2_t{18.0f, 22.0f};
        const vec2_t vec2 = vec2_t{32.0f, 28.0f};

        point2_t result_mut = point2;
        result_mut -= vec2;

        const real_t result_ref_arr[] = {-14.0f, -6.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result_mut, 2));
    }
}

TEST_CASE("point3_substraction", "[as_point]")
{
    using gsl::make_span;

    {
        const point3_t point3_a = point3_t{20.0f, 40.0f, 60.0f};
        const point3_t point3_b = point3_t{80.0f, 60.0f, 40.0f};

        const vec3_t result = point3_b - point3_a;

        const real_t result_ref_arr[] = {60.0f, 20.0f, -20.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));
    }

    {
        const point3_t point3 = point3_t{80.0f, 60.0f, 40.0f};
        const vec3_t vec3 = vec3_t{20.0f, 40.0f, 60.0f};

        const point3_t result = point3 - vec3;

        const real_t result_ref_arr[] = {60.0f, 20.0f, -20.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result, 3));
    }

    {
        const point3_t point3 = point3_t{80.0f, 60.0f, 40.0f};
        const vec3_t vec3 = vec3_t{20.0f, 40.0f, 60.0f};

        point3_t result_mut = point3;
        result_mut -= vec3;

        const real_t result_ref_arr[] = {60.0f, 20.0f, -20.0f};
        CHECK_THAT(make_span(result_ref_arr), make_elements_sub(result_mut, 3));
    }
}

} // namespace unit_test
