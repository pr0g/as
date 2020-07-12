#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::index_t;
using as::mat3_t;
using as::mat4_t;
using as::mat_t;
using as::point3_t;
using as::quat_t;
using as::real_t;
using as::vec3_t;
using as::vec4_t;
using as::vec_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace affine = as::affine;
namespace mat = as::mat;
namespace mat3 = as::mat3;
namespace mat4 = as::mat4;
namespace quat = as::quat;
namespace vec2 = as::vec2;
namespace vec3 = as::vec3;
namespace vec4 = as::vec4;

const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("mat_row_col_access_mat3", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat3_t mat3 {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

#ifdef AS_COL_MAJOR
    const real_t col0[] = {1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(make_span(col0), make_elements_sub(mat3::col0(mat3), 3));
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat3, 0), 3));
    const real_t col1[] = {4.0_r, 5.0_r, 6.0_r};
    CHECK_THAT(make_span(col1), make_elements_sub(mat3::col1(mat3), 3));
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat3, 1), 3));
    const real_t col2[] = {7.0_r, 8.0_r, 9.0_r};
    CHECK_THAT(make_span(col2), make_elements_sub(mat3::col2(mat3), 3));
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat3, 2), 3));

    const real_t row0[] = {1.0_r, 4.0_r, 7.0_r};
    CHECK_THAT(make_span(row0), make_elements_sub(mat3::row0(mat3), 3));
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat3, 0), 3));
    const real_t row1[] = {2.0_r, 5.0_r, 8.0_r};
    CHECK_THAT(make_span(row1), make_elements_sub(mat3::row1(mat3), 3));
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat3, 1), 3));
    const real_t row2[] = {3.0_r, 6.0_r, 9.0_r};
    CHECK_THAT(make_span(row2), make_elements_sub(mat3::row2(mat3), 3));
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat3, 2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = {1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(make_span(row0), make_elements_sub(mat3::row0(mat3), 3));
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat3, 0), 3));
    const real_t row1[] = {4.0_r, 5.0_r, 6.0_r};
    CHECK_THAT(make_span(row1), make_elements_sub(mat3::row1(mat3), 3));
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat3, 1), 3));
    const real_t row2[] = {7.0_r, 8.0_r, 9.0_r};
    CHECK_THAT(make_span(row2), make_elements_sub(mat3::row2(mat3), 3));
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat3, 2), 3));

    const real_t col0[] = {1.0_r, 4.0_r, 7.0_r};
    CHECK_THAT(make_span(col0), make_elements_sub(mat3::col0(mat3), 3));
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat3, 0), 3));
    const real_t col1[] = {2.0_r, 5.0_r, 8.0_r};
    CHECK_THAT(make_span(col1), make_elements_sub(mat3::col1(mat3), 3));
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat3, 1), 3));
    const real_t col2[] = {3.0_r, 6.0_r, 9.0_r};
    CHECK_THAT(make_span(col2), make_elements_sub(mat3::col2(mat3), 3));
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat3, 2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    // clang-format off
    real_t elems[] = {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(elems), make_elements_sub(mat3, 9));

    // clang-format off
    mat3_t mat3_mult;
    mat3_mult = mat3_t(
        vec3_t(10.0_r, 20.0_r, 30.0_r),
        vec3_t(40.0_r, 50.0_r, 60.0_r),
        vec3_t(70.0_r, 80.0_r, 90.0_r));

    real_t mult_elems[] = {
        10.0_r, 20.0_r, 30.0_r,
        40.0_r, 50.0_r, 60.0_r,
        70.0_r, 80.0_r, 90.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mult_elems), make_elements_sub(mat3_mult, 9));
}

TEST_CASE("mat_row_col_mutate_mat3", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat3_t mat3;
    mat3 = mat3_t {
        0.0_r, 0.0_r, 0.0_r,
        0.0_r, 0.0_r, 0.0_r,
        0.0_r, 0.0_r, 0.0_r
    };
    // clang-format on

#ifdef AS_COL_MAJOR
    const real_t col0[] = {1.0_r, 2.0_r, 3.0_r};
    const vec3_t c0 = vec3::from_arr(col0);
    mat3::col0(mat3, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3::col0(mat3), 3));
    mat::col(mat3, 0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat3, 0), 3));

    const real_t col1[] = {4.0_r, 5.0_r, 6.0_r};
    const vec3_t c1 = vec3::from_arr(col1);
    mat3::col1(mat3, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3::col1(mat3), 3));
    mat::col(mat3, 1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat3, 1), 3));

    const real_t col2[] = {7.0_r, 8.0_r, 9.0_r};
    const vec3_t c2 = vec3::from_arr(col2);
    mat3::col2(mat3, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3::col2(mat3), 3));
    mat::col(mat3, 2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat3, 2), 3));

    const real_t row0[] = {1.0_r, 4.0_r, 7.0_r};
    const vec3_t r0 = vec3::from_arr(row0);
    mat3::row0(mat3, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3::row0(mat3), 3));
    mat::row(mat3, 0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat3, 0), 3));

    const real_t row1[] = {2.0_r, 5.0_r, 8.0_r};
    const vec3_t r1 = vec3::from_arr(row1);
    mat3::row1(mat3, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3::row1(mat3), 3));
    mat::row(mat3, 1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat3, 1), 3));

    const real_t row2[] = {3.0_r, 6.0_r, 9.0_r};
    const vec3_t r2 = vec3::from_arr(row2);
    mat3::row2(mat3, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3::row2(mat3), 3));
    mat::row(mat3, 2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat3, 2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = {1.0_r, 2.0_r, 3.0_r};
    const vec3_t r0 = vec3::from_arr(row0);
    mat3::row0(mat3, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3::row0(mat3), 3));
    mat::row(mat3, 0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat3, 0), 3));

    const real_t row1[] = {4.0_r, 5.0_r, 6.0_r};
    const vec3_t r1 = vec3::from_arr(row1);
    mat3::row1(mat3, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3::row1(mat3), 3));
    mat::row(mat3, 1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat3, 1), 3));

    const real_t row2[] = {7.0_r, 8.0_r, 9.0_r};
    const vec3_t r2 = vec3::from_arr(row2);
    mat3::row2(mat3, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3::row2(mat3), 3));
    mat::row(mat3, 2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat3, 2), 3));

    const real_t col0[] = {1.0_r, 4.0_r, 7.0_r};
    const vec3_t c0 = vec3::from_arr(col0);
    mat3::col0(mat3, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3::col0(mat3), 3));
    mat::col(mat3, 0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat3, 0), 3));

    const real_t col1[] = {2.0_r, 5.0_r, 9.0_r};
    const vec3_t c1 = vec3::from_arr(col1);
    mat3::col1(mat3, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3::col1(mat3), 3));
    mat::col(mat3, 1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat3, 1), 3));

    const real_t col2[] = {3.0_r, 6.0_r, 9.0_r};
    const vec3_t c2 = vec3::from_arr(col2);
    mat3::col2(mat3, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3::col2(mat3), 3));
    mat::col(mat3, 2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat3, 2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_row_col_access_mat4", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat4_t mat4 {
        1.0_r, 2.0_r, 3.0_r, 4.0_r,
        5.0_r, 6.0_r, 7.0_r, 8.0_r,
        9.0_r, 10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

#ifdef AS_COL_MAJOR
    const real_t col0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    CHECK_THAT(make_span(col0), make_elements_sub(mat4::col0(mat4), 4));
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat4, 0), 4));
    const real_t col1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
    CHECK_THAT(make_span(col1), make_elements_sub(mat4::col1(mat4), 4));
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat4, 1), 4));
    const real_t col2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
    CHECK_THAT(make_span(col2), make_elements_sub(mat4::col2(mat4), 4));
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat4, 2), 4));
    const real_t col3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
    CHECK_THAT(make_span(col3), make_elements_sub(mat4::col3(mat4), 4));
    CHECK_THAT(make_span(col3), make_elements_sub(mat::col(mat4, 3), 4));

    const real_t row0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
    CHECK_THAT(make_span(row0), make_elements_sub(mat4::row0(mat4), 4));
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat4, 0), 4));
    const real_t row1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
    CHECK_THAT(make_span(row1), make_elements_sub(mat4::row1(mat4), 4));
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat4, 1), 4));
    const real_t row2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
    CHECK_THAT(make_span(row2), make_elements_sub(mat4::row2(mat4), 4));
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat4, 2), 4));
    const real_t row3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    CHECK_THAT(make_span(row3), make_elements_sub(mat4::row3(mat4), 4));
    CHECK_THAT(make_span(row3), make_elements_sub(mat::row(mat4, 3), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    CHECK_THAT(make_span(row0), make_elements_sub(mat4::row0(mat4), 4));
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat4, 0), 4));
    const real_t row1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
    CHECK_THAT(make_span(row1), make_elements_sub(mat4::row1(mat4), 4));
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat4, 1), 4));
    const real_t row2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
    CHECK_THAT(make_span(row2), make_elements_sub(mat4::row2(mat4), 4));
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat4, 2), 4));
    const real_t row3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
    CHECK_THAT(make_span(row3), make_elements_sub(mat4::row3(mat4), 4));
    CHECK_THAT(make_span(row3), make_elements_sub(mat::row(mat4, 3), 4));

    const real_t col0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
    CHECK_THAT(make_span(col0), make_elements_sub(mat4::col0(mat4), 4));
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat4, 0), 4));
    const real_t col1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
    CHECK_THAT(make_span(col1), make_elements_sub(mat4::col1(mat4), 4));
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat4, 1), 4));
    const real_t col2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
    CHECK_THAT(make_span(col2), make_elements_sub(mat4::col2(mat4), 4));
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat4, 2), 4));
    const real_t col3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    CHECK_THAT(make_span(col3), make_elements_sub(mat4::col3(mat4), 4));
    CHECK_THAT(make_span(col3), make_elements_sub(mat::col(mat4, 3), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    // clang-format off
    real_t elems[] = {
        1.0_r, 2.0_r, 3.0_r, 4.0_r,
        5.0_r, 6.0_r, 7.0_r, 8.0_r,
        9.0_r, 10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(elems), make_elements_sub(mat4, 16));

    // clang-format off
    mat4_t mat4_mult;
    mat4_mult = mat4_t(
        vec4_t(10.0_r, 20.0_r, 30.0_r, 40.0_r),
        vec4_t(50.0_r, 60.0_r, 70.0_r, 80.0_r),
        vec4_t(90.0_r, 100.0_r, 110.0_r, 120.0_r),
        vec4_t(130.0_r, 140.0_r, 150.0_r, 160.0_r)
    );

    real_t mult_elems[] = {
        10.0_r, 20.0_r, 30.0_r, 40.0_r,
        50.0_r, 60.0_r, 70.0_r, 80.0_r,
        90.0_r, 100.0_r, 110.0_r, 120.0_r,
        130.0_r, 140.0_r, 150.0_r, 160.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mult_elems), make_elements_sub(mat4_mult, 16));
}

TEST_CASE("mat_row_col_mutate_mat4", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat4_t mat4;
    mat4 = mat4_t {
        0.0_r, 0.0_r, 0.0_r, 0.0_r,
        0.0_r, 0.0_r, 0.0_r, 0.0_r,
        0.0_r, 0.0_r, 0.0_r, 0.0_r,
        0.0_r, 0.0_r, 0.0_r, 0.0_r
    };
    // clang-format on

#ifdef AS_COL_MAJOR
    const real_t col0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    const vec4_t c0 = vec4::from_arr(col0);
    mat4::col0(mat4, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4::col0(mat4), 4));
    mat::col(mat4, 0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat4, 0), 4));
    CHECK(col0[0] == Approx(mat::col(mat4, 0)[0]).epsilon(g_epsilon));

    const real_t col1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
    const vec4_t c1 = vec4::from_arr(col1);
    mat4::col1(mat4, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4::col1(mat4), 4));
    mat::col(mat4, 1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat4, 1), 4));
    CHECK(col1[1] == Approx(mat::col(mat4, 1)[1]).epsilon(g_epsilon));

    const real_t col2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
    const vec4_t c2 = vec4::from_arr(col2);
    mat4::col2(mat4, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4::col2(mat4), 4));
    mat::col(mat4, 2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat4, 2), 4));
    CHECK(col2[2] == Approx(mat::col(mat4, 2)[2]).epsilon(g_epsilon));

    const real_t col3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
    const vec4_t c3 = vec4::from_arr(col3);
    mat4::col3(mat4, c3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4::col3(mat4), 4));
    mat::col(mat4, 3, c3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat::col(mat4, 3), 4));
    CHECK(col3[3] == Approx(mat::col(mat4, 3)[3]).epsilon(g_epsilon));

    const real_t row0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
    const vec4_t r0 = vec4::from_arr(row0);
    mat4::row0(mat4, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat4::row0(mat4), 4));
    mat::row(mat4, 0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat::row(mat4, 0), 4));
    CHECK(row0[0] == Approx(mat::row(mat4, 0)[0]).epsilon(g_epsilon));

    const real_t row1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
    const vec4_t r1 = vec4::from_arr(row1);
    mat4::row1(mat4, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4::row1(mat4), 4));
    mat::row(mat4, 1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat4, 1), 4));
    CHECK(row1[1] == Approx(mat::row(mat4, 1)[1]).epsilon(g_epsilon));

    const real_t row2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
    const vec4_t r2 = vec4::from_arr(row2);
    mat4::row2(mat4, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4::row2(mat4), 4));
    mat::row(mat4, 2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat4, 2), 4));
    CHECK(row2[2] == Approx(mat::row(mat4, 2)[2]).epsilon(g_epsilon));

    const real_t row3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    const vec4_t r3 = vec4::from_arr(row3);
    mat4::row3(mat4, r3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4::row3(mat4), 4));
    mat::row(mat4, 3, r3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat::row(mat4, 3), 4));
    CHECK(row3[3] == Approx(mat::row(mat4, 3)[3]).epsilon(g_epsilon));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    const vec4_t c0 = vec4::from_arr(row0);
    mat4::row0(mat4, c0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat4::row0(mat4), 4));
    mat::row(mat4, 0, c0);
    CHECK(row0[0] == Approx(mat::row(mat4, 0)[0]).epsilon(g_epsilon));

    const real_t row1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
    const vec4_t c1 = vec4::from_arr(row1);
    mat4::row1(mat4, c1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4::row1(mat4), 4));
    mat::row(mat4, 1, c1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat::row(mat4, 1), 4));
    CHECK(row1[1] == Approx(mat::row(mat4, 1)[1]).epsilon(g_epsilon));

    const real_t row2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
    const vec4_t c2 = vec4::from_arr(row2);
    mat4::row2(mat4, c2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4::row2(mat4), 4));
    mat::row(mat4, 2, c2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat::row(mat4, 2), 4));
    CHECK(row2[2] == Approx(mat::row(mat4, 2)[2]).epsilon(g_epsilon));

    const real_t row3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
    const vec4_t c3 = vec4::from_arr(row3);
    mat4::row3(mat4, c3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4::row3(mat4), 4));
    mat::row(mat4, 3, c3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat::row(mat4, 3), 4));
    CHECK(row3[3] == Approx(mat::row(mat4, 3)[3]).epsilon(g_epsilon));

    const real_t col0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
    const vec4_t r0 = vec4::from_arr(col0);
    mat4::col0(mat4, r0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4::col0(mat4), 4));
    mat::col(mat4, 0, r0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat::col(mat4, 0), 4));
    CHECK(col0[0] == Approx(mat::col(mat4, 0)[0]).epsilon(g_epsilon));

    const real_t col1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
    const vec4_t r1 = vec4::from_arr(col1);
    mat4::col1(mat4, r1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4::col1(mat4), 4));
    mat::col(mat4, 1, r1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat::col(mat4, 1), 4));
    CHECK(col1[1] == Approx(mat::col(mat4, 1)[1]).epsilon(g_epsilon));

    const real_t col2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
    const vec4_t r2 = vec4::from_arr(col2);
    mat4::col2(mat4, r2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4::col2(mat4), 4));
    mat::col(mat4, 2, r2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat::col(mat4, 2), 4));
    CHECK(col2[2] == Approx(mat::col(mat4, 2)[2]).epsilon(g_epsilon));

    const real_t col3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
    const vec4_t r3 = vec4::from_arr(col3);
    mat4::col3(mat4, r3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4::col3(mat4), 4));
    mat::col(mat4, 3, r3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat::col(mat4, 3), 4));
    CHECK(col3[3] == Approx(mat::col(mat4, 3)[3]).epsilon(g_epsilon));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_mat4_from_mat3_and_vec3", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat3_t mat3 {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    vec3_t vec3{10.0_r, 11.0_r, 12.0_r};

    // clang-format off
    const real_t mat3_and_vec3[] = {
        1.0_r, 2.0_r, 3.0_r, 0.0_r,
        4.0_r, 5.0_r, 6.0_r, 0.0_r,
        7.0_r, 8.0_r, 9.0_r, 0.0_r,
        10.0_r, 11.0_r, 12.0_r, 1.0_r
    };
    // clang-format on

    {
        mat4_t mat4;
        mat4 = mat4_t{mat3, vec3};

        CHECK_THAT(make_span(mat3_and_vec3), make_elements_sub(mat4, 16));
    }

    {
        mat4_t mat4;
        mat4 = mat4::from_mat3_vec3(mat3, vec3);

        CHECK_THAT(make_span(mat3_and_vec3), make_elements_sub(mat4, 16));
    }

    {
        mat4_t mat4;
        mat4 = mat4::from_mat3(mat3);

        // clang-format off
        const real_t mat3_and_zero[] = {
            1.0_r, 2.0_r, 3.0_r, 0.0_r,
            4.0_r, 5.0_r, 6.0_r, 0.0_r,
            7.0_r, 8.0_r, 9.0_r, 0.0_r,
            0.0_r, 0.0_r, 0.0_r, 1.0_r
        };
        // clang-format on

        CHECK_THAT(make_span(mat3_and_zero), make_elements_sub(mat4, 16));
    }

    {
        mat4_t mat4;
        mat4 = mat4::from_vec3(vec3_t{10.0_r, 20.0_r, 30.0_r});

        // clang-format off
        const real_t zero_and_vec3[] = {
            1.0_r, 0.0_r, 0.0_r, 0.0_r,
            0.0_r, 1.0_r, 0.0_r, 0.0_r,
            0.0_r, 0.0_r, 1.0_r, 0.0_r,
            10.0_r, 20.0_r, 30.0_r, 1.0_r
        };
        // clang-format on

        CHECK_THAT(make_span(zero_and_vec3), make_elements_sub(mat4, 16));
    }
}

TEST_CASE("const_elem_access_mat_const", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat_t<real_t, 5> mat5(
        1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r,
        6.0_r, 7.0_r, 8.0_r, 9.0_r, 10.0_r,
        11.0_r, 12.0_r, 13.0_r, 15.0_r, 15.0_r,
        16.0_r, 17.0_r, 18.0_r, 19.0_r, 20.0_r,
        21.0_r, 22.0_r, 23.0_r, 24.0_r, 25.0_r);

    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14],
        mat5[15], mat5[16], mat5[17], mat5[18], mat5[19],
        mat5[20], mat5[21], mat5[22], mat5[23], mat5[24]
    };
    // clang-format on

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat5, 25));
}

TEST_CASE("elem_access_mat", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    mat_t<real_t, 5> mat5(
        1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r,
        6.0_r, 7.0_r, 8.0_r, 9.0_r, 10.0_r,
        11.0_r, 12.0_r, 13.0_r, 15.0_r, 15.0_r,
        16.0_r, 17.0_r, 18.0_r, 19.0_r, 20.0_r,
        21.0_r, 22.0_r, 23.0_r, 24.0_r, 25.0_r
    );
    // clang-format on

    mat5[15] = 100.0_r;
    mat5[20] = 200.0_r;

    // clang-format off
    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14],
        100.0_r, mat5[16], mat5[17], mat5[18], mat5[19],
        200.0_r, mat5[21], mat5[22], mat5[23], mat5[24]
    };
    // clang-format on

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat5, 25));
}

TEST_CASE("elem_access_mat4_const", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat4_t mat4(
        1.0_r, 2.0_r, 3.0_r, 4.0_r,
        5.0_r, 6.0_r, 7.0_r, 8.0_r,
        9.0_r, 10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r
    );

    const real_t mat_arr[] = {
        1.0_r, 2.0_r, 3.0_r, 4.0_r,
        5.0_r, 6.0_r, 7.0_r, 8.0_r,
        9.0_r, 10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r,
    };
    // clang-format on

    const real_t mat4_8 = mat4[8];
    CHECK(mat4_8 == Approx(mat_arr[8]).epsilon(g_epsilon));
    CHECK(mat4_8 == Approx(9.0_r).epsilon(g_epsilon));

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat4, 16));
}

TEST_CASE("rvalue_elem_access_mat2_3_4", "[as_mat]")
{
    using gsl::make_span;

    auto make_mat2 = []() {
        return mat_t<real_t, 2>{5.0_r, 10.0_r, 15.0_r, 20.0_r};
    };
    CHECK(make_mat2()[0] == Approx(5.0_r).epsilon(g_epsilon));
    CHECK(make_mat2()[1] == Approx(10.0_r).epsilon(g_epsilon));
    CHECK(make_mat2()[2] == Approx(15.0_r).epsilon(g_epsilon));
    CHECK(make_mat2()[3] == Approx(20.0_r).epsilon(g_epsilon));

    // clang-format off
    auto make_mat3 = []() {
        return mat3_t{
            1.0_r, 2.0_r, 3.0_r,
            4.0_r, 5.0_r, 6.0_r,
            7.0_r, 8.0_r, 9.0_r
        };
    };
    // clang-format on

    CHECK(make_mat3()[4] == Approx(5.0_r).epsilon(g_epsilon));

    // clang-format off
    auto make_mat4 = [](){
        return mat4_t {
            1.0_r, 2.0_r, 3.0_r, 4.0_r,
            5.0_r, 6.0_r, 7.0_r, 8.0_r,
            9.0_r, 10.0_r, 11.0_r, 12.0_r,
            13.0_r, 14.0_r, 15.0_r, 16.0_r
        };
    };
    // clang-format on

    CHECK(make_mat4()[7] == Approx(8.0_r).epsilon(g_epsilon));
    CHECK(make_mat4()[15] == Approx(16.0_r).epsilon(g_epsilon));
}

TEST_CASE("mat_dimensions_are_valid", "[as_mat]")
{
    index_t mat3_rows;
    mat3_rows = mat3_t::rows();
    CHECK(mat3_rows == 3);

    index_t mat3_cols;
    mat3_cols = mat3_t::cols();
    CHECK(mat3_cols == 3);

    index_t mat3_dim;
    mat3_dim = mat3_t::dim();
    CHECK(mat3_dim == 3);

    index_t mat3_size;
    mat3_size = mat3_t::size();
    CHECK(mat3_size == 9);

    index_t mat4_rows;
    mat4_rows = mat4_t::rows();
    CHECK(mat4_rows == 4);

    index_t mat4_cols;
    mat4_cols = mat4_t::cols();
    CHECK(mat4_cols == 4);

    index_t mat4_dim;
    mat4_dim = mat4_t::dim();
    CHECK(mat4_dim == 4);

    index_t mat4_size;
    mat4_size = mat4_t::size();
    CHECK(mat4_size == 16);

    using mat5_t = mat_t<real_t, 5>;

    index_t mat5_rows;
    mat5_rows = mat5_t::rows();
    CHECK(mat5_rows == 5);

    index_t mat5_cols;
    mat5_cols = mat5_t::cols();
    CHECK(mat5_cols == 5);

    index_t mat5_dim;
    mat5_dim = mat5_t::dim();
    CHECK(mat5_dim == 5);

    index_t mat5_size;
    mat5_size = mat5_t::size();
    CHECK(mat5_size == 25);
}

TEST_CASE("multiply_same_size", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat3_t mat3_a {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };

    const mat3_t mat3_b {
        9.0_r, 8.0_r, 7.0_r,
        6.0_r, 5.0_r, 4.0_r,
        3.0_r, 2.0_r, 1.0_r
    };

    const real_t mat_arr[] = {
        30.0_r, 24.0_r, 18.0_r,
        84.0_r, 69.0_r, 54.0_r,
        138.0_r, 114.0_r, 90.0_r
    };
    // clang-format on

    mat3_t result;
#ifdef AS_ROW_MAJOR
    result = mat3_a * mat3_b;
#elif defined AS_COL_MAJOR
    result = mat3_b * mat3_a;
#endif

    CHECK_THAT(make_span(mat_arr), make_elements_sub(result, 9));
}

TEST_CASE("multiply_mul", "[as-mat]")
{
    using gsl::make_span;

    mat3_t rotate_x = mat3::rotation_x(deg_to_rad(30.0f));
    mat3_t rotate_y = mat3::rotation_y(deg_to_rad(30.0f));
    mat3_t rotate_z = mat3::rotation_z(deg_to_rad(30.0f));

    mat3_t result_mul;
    result_mul = as::mat::mul(as::mat::mul(rotate_x, rotate_y), rotate_z);

    mat3_t result;
#ifdef AS_ROW_MAJOR
    result = rotate_x * rotate_y * rotate_z;
#elif defined AS_COL_MAJOR
    result = rotate_z * rotate_y * rotate_x;
#endif

    real_t result_arr[9];
    as::mat::to_arr(result, result_arr);

    CHECK_THAT(make_span(result_arr), make_elements_sub(result_mul, 9));
    CHECK(as::mat::equal(result_mul, result));
}

TEST_CASE("equal_mat", "[as-mat]")
{
    // clang-format off
    const mat4_t mat_a = as::mat4_t{
        1.0_r,  2.0_r,  3.0_r,  4.0_r,
        5.0_r,  6.0_r,  7.0_r,  8.0_r,
        9.0_r,  10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

    const mat4_t mat_a_again = mat_a;

    CHECK(as::mat::equal(mat_a, mat_a_again));
}

TEST_CASE("not_equal_mat", "[as-mat]")
{
    // clang-format off
    const mat4_t mat_a = as::mat4_t{
        1.0_r,  2.0_r,  3.0_r,  4.0_r,
        5.0_r,  6.0_r,  7.0_r,  8.0_r,
        9.0_r,  10.0_r, 11.0_r, 12.0_r,
        13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

    // clang-format off
    const mat4_t mat_b = as::mat4_t{
        3.0_r,  3.0_r,  2.0_r,  1.0_r,
        8.0_r,  7.0_r,  6.0_r,  5.0_r,
        12.0_r, 11.0_r, 10.0_r, 9.0_r,
        16.0_r, 15.0_r, 14.0_r, 13.0_r
    };
    // clang-format on

    CHECK(!as::mat::equal(mat_a, mat_b));
}

TEST_CASE("multiply_vector", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat3_t mat {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    const vec3_t vec{11.0_r, 12.0_r, 13.0_r};

    vec3_t result;
#ifdef AS_ROW_MAJOR
    result = vec * mat;
#elif defined AS_COL_MAJOR
    result = mat * vec;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    const real_t vec_arr[] = {150.0_r, 186.0_r, 222.0_r};
    CHECK_THAT(make_span(vec_arr), make_elements_sub(result, 3));
}

TEST_CASE("multiply_scalar", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat3_t mat3 {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    mat3_t result33 = mat3 * real_t(2.0);

    // clang-format off
    const real_t mat3_arr[] = {
        2.0_r, 4.0_r, 6.0_r,
        8.0_r, 10.0_r, 12.0_r,
        14.0_r, 16.0_r, 18.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_arr), make_elements_sub(result33, 9));

    // clang-format off
    const mat4_t mat4 {
        2.0_r, 4.0_r, 6.0_r, 8.0_r,
        10.0_r, 12.0_r, 14.0_r, 16.0_r,
        18.0_r, 20.0_r, 22.0_r, 24.0_r,
        26.0_r, 28.0_r, 30.0_r, 32.0_r
    };

    const mat4_t result4 = mat4 * real_t(2.0);

    const real_t mat4_arr[] = {
        4.0_r, 8.0_r, 12.0_r, 16.0_r,
        20.0_r, 24.0_r, 28.0_r, 32.0_r,
        36.0_r, 40.0_r, 44.0_r, 48.0_r,
        52.0_r, 56.0_r, 60.0_r, 64.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat4_arr), make_elements_sub(result4, 16));
}

TEST_CASE("mat_from_arr", "[as_mat]")
{
    using gsl::make_span;

    {
        // clang-format off
        real_t elems[] = {
            1.0_r, 2.0_r, 3.0_r, 4.0_r,
            5.0_r, 6.0_r, 7.0_r, 8.0_r,
            9.0_r, 10.0_r, 11.0_r, 12.0_r,
            13.0_r, 14.0_r, 15.0_r, 16.0_r
        };
        // clang-format on

        const mat4_t mat4_a = mat::from_arr<real_t, 4>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_a, 16));

        const mat4_t mat4_b = mat4::from_arr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_b, 16));

        // clang-format off
        int64_t elems_long[] = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };
        // clang-format on

        const as::mat4l_t mat4_c = mat4::from_arr(elems_long);
        CHECK_THAT(make_span(elems_long), make_elements_sub(mat4_c, 16));
    }

    {
        // clang-format off
        real_t elems[] = {
            1.0_r, 2.0_r, 3.0_r,
            4.0_r, 5.0_r, 6.0_r,
            7.0_r, 8.0_r, 9.0_r
        };
        // clang-format on

        const mat3_t mat3_a = mat::from_arr<real_t, 3>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_a, 9));

        const mat3_t mat3_b = mat3::from_arr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_b, 9));
    }
}

TEST_CASE("mat_from_ptr", "[as_mat]")
{
    using gsl::make_span;

    {
        // clang-format off
        real_t elems[] = {
            1.0_r, 2.0_r, 3.0_r, 4.0_r,
            5.0_r, 6.0_r, 7.0_r, 8.0_r,
            9.0_r, 10.0_r, 11.0_r, 12.0_r,
            13.0_r, 14.0_r, 15.0_r, 16.0_r
        };
        // clang-format on

        const mat4_t mat4_a = mat::from_ptr<real_t, 4>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_a, 16));

        const mat4_t mat4_b = mat4::from_ptr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_b, 16));

        // clang-format off
        int64_t elems_long[] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        };
        // clang-format on

        const as::mat4l_t mat4_c = mat4::from_ptr(elems_long);
        CHECK_THAT(make_span(elems_long), make_elements_sub(mat4_c, 16));
    }

    {
        // clang-format off
        real_t elems[] = {
            1.0_r, 2.0_r, 3.0_r,
            4.0_r, 5.0_r, 6.0_r,
            7.0_r, 8.0_r, 9.0_r
        };
        // clang-format on

        const mat3_t mat3_a = mat::from_ptr<real_t, 3>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_a, 9));

        const mat3_t mat3_b = mat3::from_ptr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_b, 9));
    }
}

TEST_CASE("mat_to_arr", "[as_mat]")
{
    using gsl::make_span;

    // clang-format off
    const mat3_t mat3 {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    real_t mat3_arr[9];
    mat::to_arr(mat3, mat3_arr);

    CHECK_THAT(make_span(mat3_arr), make_elements_sub(mat3, 9));
}

TEST_CASE("mat_transpose", "[as_mat]")
{
    using gsl::make_span;

    {
        // clang-format off
        const mat3_t mat3 {
            1.0_r, 2.0_r, 3.0_r,
            4.0_r, 5.0_r, 6.0_r,
            7.0_r, 8.0_r, 9.0_r
        };

        const mat3_t mat3_transposed = mat::transpose(mat3);

        const real_t mat3_transposed_ref[] {
            1.0_r, 4.0_r, 7.0_r,
            2.0_r, 5.0_r, 8.0_r,
            3.0_r, 6.0_r, 9.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat3_transposed_ref),
            make_elements_sub(mat3_transposed, 9));
    }

    {
        // clang-format off
        const mat4_t mat4 = {
            1.0_r, 2.0_r, 3.0_r, 4.0_r,
            5.0_r, 6.0_r, 7.0_r, 8.0_r,
            9.0_r, 10.0_r, 11.0_r, 12.0_r,
            13.0_r, 14.0_r, 15.0_r, 16.0_r
        };

        const mat4_t mat4_transposed = mat::transpose(mat4);

        const real_t mat4_transposed_reference[] {
            1.0_r, 5.0_r, 9.0_r, 13.0_r,
            2.0_r, 6.0_r, 10.0_r, 14.0_r,
            3.0_r, 7.0_r, 11.0_r, 15.0_r,
            4.0_r, 8.0_r, 12.0_r, 16.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat4_transposed_reference),
            make_elements_sub(mat4_transposed, 16));
    }
}

TEST_CASE("mat_identity", "[as_mat]")
{
    using gsl::make_span;

    {
        mat3_t mat3_identity;
        mat3_identity = mat3_t::identity();

        // clang-format off
        const real_t mat3_identity_ref[] {
            1.0_r, 0.0_r, 0.0_r,
            0.0_r, 1.0_r, 0.0_r,
            0.0_r, 0.0_r, 1.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat3_identity_ref), make_elements_sub(mat3_identity, 9));
    }

    {
        mat4_t mat4_identity;
        mat4_identity = mat4_t::identity();

        // clang-format off
        const real_t mat4_identity_ref[] {
            1.0_r, 0.0_r, 0.0_r, 0.0_r,
            0.0_r, 1.0_r, 0.0_r, 0.0_r,
            0.0_r, 0.0_r, 1.0_r, 0.0_r,
            0.0_r, 0.0_r, 0.0_r, 1.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat4_identity_ref), make_elements_sub(mat4_identity, 16));
    }

    {
        using mat5_t = mat_t<real_t, 5>;

        mat5_t mat5_identity;
        mat5_identity = mat5_t::identity();

        // clang-format off
        const real_t mat5_identity_ref[] {
            1.0_r, 0.0_r, 0.0_r, 0.0_r, 0.0_r,
            0.0_r, 1.0_r, 0.0_r, 0.0_r, 0.0_r,
            0.0_r, 0.0_r, 1.0_r, 0.0_r, 0.0_r,
            0.0_r, 0.0_r, 0.0_r, 1.0_r, 0.0_r,
            0.0_r, 0.0_r, 0.0_r, 0.0_r, 1.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat5_identity_ref), make_elements_sub(mat5_identity, 25));
    }
}

TEST_CASE("mat_inverse", "[as_mat]")
{
    using gsl::make_span;

    {
        using mat2_t = mat_t<real_t, 2>;

        // clang-format off
        const mat2_t mat2 {
            1.0_r, 2.0_r,
            3.0_r, 4.0_r
        };
        // clang-format on

        const mat2_t mat2_inverse = mat::inverse(mat2);
        const real_t mat2_inverse_ref[]{
            -2.0_r, 1.0_r, 3.0_r / 2.0_r, -1.0_r / 2.0_r};

        CHECK_THAT(
            make_span(mat2_inverse_ref), make_elements_sub(mat2_inverse, 4));
    }

    {
        // clang-format off
        const mat3_t mat3 {
            1.0_r, 2.0_r, 3.0_r,
            4.0_r, 5.0_r, 6.0_r,
            7.0_r, 2.0_r, 9.0_r
        };
        // clang-format on

        const mat3_t mat3_inverse = mat::inverse(mat3);

        // clang-format off
        const real_t mat3_inverse_ref[] {
            -11.0_r/12.0_r, 1.0_r/3.0_r, 1.0_r/12.0_r,
            -1.0_r/6.0_r, 1.0_r/3.0_r, -1.0_r/6.0_r,
            3.0_r/4.0_r, -1.0_r/3.0_r, 1.0_r/12.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat3_inverse_ref), make_elements_sub(mat3_inverse, 9));
    }

    {
        // clang-format off
        const mat4_t mat4 = {
            1.0_r, 3.0_r, 5.0_r, 9.0_r,
            1.0_r, 3.0_r, 1.0_r, 7.0_r,
            4.0_r, 3.0_r, 9.0_r, 7.0_r,
            5.0_r, 2.0_r, 0.0_r, 9.0_r
        };
        // clang-format on

        const mat4_t mat4_inverse = mat::inverse(mat4);

        // clang-format off
        const real_t mat4_inverse_reference[] {
            -13.0_r/47.0_r, 2.0_r/47.0_r, 7.0_r/47.0_r, 6.0_r/47.0_r,
            -5.0_r/8.0_r, 7.0_r/8.0_r, 1.0_r/4.0_r, -1.0_r/4.0_r,
            39.0_r/376.0_r, -53.0_r/376.0_r, 13.0_r/188.0_r, -9.0_r/188.0_r,
            55.0_r/188.0_r, -41.0_r/188.0_r, -13.0_r/94.0_r, 9.0_r/94.0_r
        };
        // clang-format on

        CHECK_THAT(
            make_span(mat4_inverse_reference),
            make_elements_sub(mat4_inverse, 16));
    }
}

TEST_CASE("mat_scale", "[as_mat]")
{
    using gsl::make_span;

    mat3_t scale;
    scale = mat3::scale(vec3_t{1.0_r, 2.0_r, 3.0_r});

    // clang-format off
    const real_t mat3_scale_reference[] {
        1.0_r, 0.0_r, 0.0_r,
        0.0_r, 2.0_r, 0.0_r,
        0.0_r, 0.0_r, 3.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_scale_reference), make_elements_sub(scale, 9));

    mat3_t uniform_scale;
    uniform_scale = mat3::scale(5.0_r);

    // clang-format off
    const real_t mat3_uniform_scale_reference[] {
        5.0_r, 0.0_r, 0.0_r,
        0.0_r, 5.0_r, 0.0_r,
        0.0_r, 0.0_r, 5.0_r
    };
    // clang-format on

    CHECK_THAT(
        make_span(mat3_uniform_scale_reference),
        make_elements_sub(uniform_scale, 9));
}

TEST_CASE("mat3_from_mat4", "[as_mat]")
{
    using gsl::make_span;

    mat4_t mat4;
    mat4 = mat4_t::identity();

    mat3_t mat3;
    mat3 = mat3::from_mat4(mat4);

    // clang-format off
    const real_t mat3_identity_ref[] {
        1.0_r, 0.0_r, 0.0_r,
        0.0_r, 1.0_r, 0.0_r,
        0.0_r, 0.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_identity_ref), make_elements_sub(mat3, 9));
}

TEST_CASE("mat3_axis_angle", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle =
            mat3::axis_angle(vec3_t::axis_x(), deg_to_rad(90.0_r));
        real_t result_reference[] = {0.0_r, -1.0_r, 0.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3_t::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }

    {
        mat3_t axis_angle =
            mat3::axis_angle(vec3_t::axis_y(), deg_to_rad(90.0_r));
        real_t result_reference[] = {0.0_r, 0.0_r, -1.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_x() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3_t::axis_x();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }
}

TEST_CASE("mat3_rotate_xyz", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle = mat3::rotation_xyz(
            deg_to_rad(45.0_r), deg_to_rad(90.0_r), deg_to_rad(45.0_r));
        real_t result_reference[] = {0.0_r, 1.0_r, 0.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_y() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3_t::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }

    {
        mat3_t axis_angle = mat3::rotation_xyz(
            deg_to_rad(-180.0_r), deg_to_rad(90.0_r), deg_to_rad(-90.0_r));
        real_t result_reference[] = {0.0_r, 1.0_r, 0.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3_t::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }
}

TEST_CASE("mat3_rotate_zxy", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle = mat3::rotation_zxy(
            deg_to_rad(90.0_r), deg_to_rad(90.0_r), deg_to_rad(0.0_r));
        real_t result_reference_y[] = {1.0_r, 0.0_r, 0.0_r};
        real_t result_reference_z[] = {0.0_r, -1.0_r, 0.0_r};

        vec3_t result_y;
        vec3_t result_z;
#ifdef AS_ROW_MAJOR
        result_y = vec3_t::axis_y() * axis_angle;
        result_z = vec3_t::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result_y = axis_angle * vec3_t::axis_y();
        result_z = axis_angle * vec3_t::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference_y),
            make_elements_sub(result_y, 3).margin(g_epsilon));

        CHECK_THAT(
            make_span(result_reference_z),
            make_elements_sub(result_z, 3).margin(g_epsilon));
    }

    {
        mat3_t axis_angle = mat3::rotation_zxy(
            deg_to_rad(0.0_r), deg_to_rad(-90.0_r), deg_to_rad(-90.0_r));
        real_t result_reference_x[] = {0.0_r, -1.0_r, 0.0_r};
        real_t result_reference_y[] = {0.0_r, 0.0_r, 1.0_r};

        vec3_t result_x;
        vec3_t result_y;
#ifdef AS_ROW_MAJOR
        result_x = vec3_t::axis_x() * axis_angle;
        result_y = vec3_t::axis_y() * axis_angle;
#elif defined AS_COL_MAJOR
        result_x = axis_angle * vec3_t::axis_x();
        result_y = axis_angle * vec3_t::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference_x),
            make_elements_sub(result_x, 3).margin(g_epsilon));

        CHECK_THAT(
            make_span(result_reference_y),
            make_elements_sub(result_y, 3).margin(g_epsilon));
    }
}

TEST_CASE("mat3_from_quat", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle_mat = mat3::rotation_zxy(
            deg_to_rad(90.0_r), deg_to_rad(90.0_r), deg_to_rad(0.0_r));
        quat_t axis_angle_quat = quat::rotation_zxy(
            deg_to_rad(90.0_r), deg_to_rad(90.0_r), deg_to_rad(0.0_r));

        mat3_t axis_angle_mat_from_quat;
        axis_angle_mat_from_quat = mat3::from_quat(axis_angle_quat);

        real_t expected[9];
        mat::to_arr(axis_angle_mat_from_quat, expected);

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(expected, 9),
            make_elements_sub(axis_angle_mat, 9).margin(g_epsilon));
    }
}

TEST_CASE("mat3_rotate_x_y_z_separate", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_x = mat3::rotation_x(deg_to_rad(45.0_r));
        mat3_t axis_y = mat3::rotation_y(deg_to_rad(90.0_r));
        mat3_t axis_z = mat3::rotation_z(deg_to_rad(45.0_r));

        real_t result_reference[] = {0.0_r, 1.0_r, 0.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_y() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
        result = axis_z * axis_y * axis_x * vec3_t::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }

    {
        mat3_t axis_x = mat3::rotation_x(deg_to_rad(-180.0_r));
        mat3_t axis_y = mat3::rotation_y(deg_to_rad(90.0_r));
        mat3_t axis_z = mat3::rotation_z(deg_to_rad(-90.0_r));

        real_t result_reference[] = {0.0_r, 1.0_r, 0.0_r};

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3_t::axis_z() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
        result = axis_z * axis_y * axis_x * vec3_t::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0_r requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(g_epsilon));
    }
}

TEST_CASE("row_col_access", "[as-mat]")
{
    {
        index_t offset;
        offset = mat::rc(0, 0, 2);
        CHECK(offset == 0);
    }

    {
        index_t offset;
        offset = mat3::rc(1, 1);
        CHECK(offset == 4);
    }

    {
        index_t offset;
        offset = mat4::rc(2, 2);
        CHECK(offset == 10);
    }
}

TEST_CASE("mat4_shear", "[as-mat]")
{
    using gsl::make_span;

    {
        mat4_t shear_about_x;
        shear_about_x = as::mat4::shear_x(1.0_r, 0.0_r);

        const point3_t position{1.0_r, 0.0_r, 0.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_x), position);

        CHECK_THAT(arr(1.0_r, 1.0_r, 0.0_r), make_elements_sub(result, 3));
    }

    {
        mat4_t shear_about_x;
        shear_about_x = as::mat4::shear_x(0.0_r, 1.0_r);

        const point3_t position{1.0_r, 0.0_r, 0.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_x), position);

        CHECK_THAT(arr(1.0_r, 0.0_r, 1.0_r), make_elements_sub(result, 3));
    }

    {
        mat4_t shear_about_y;
        shear_about_y = as::mat4::shear_y(1.0_r, 0.0_r);

        const point3_t position{1.0_r, 1.0_r, 0.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_y), position);

        CHECK_THAT(arr(2.0_r, 1.0_r, 0.0_r), make_elements_sub(result, 3));
    }

    {
        mat4_t shear_about_y;
        shear_about_y = as::mat4::shear_y(0.0_r, 1.0_r);

        const point3_t position{1.0_r, 1.0_r, 0.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_y), position);

        CHECK_THAT(arr(1.0_r, 1.0_r, 1.0_r), make_elements_sub(result, 3));
    }

    {
        mat4_t shear_about_z;
        shear_about_z = as::mat4::shear_z(1.0_r, 0.0_r);

        const point3_t position{0.0_r, 0.0_r, 1.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_z), position);

        CHECK_THAT(arr(1.0_r, 0.0_r, 1.0_r), make_elements_sub(result, 3));
    }

    {
        mat4_t shear_about_z;
        shear_about_z = as::mat4::shear_z(0.0_r, 1.0_r);

        const point3_t position{1.0_r, 0.0_r, 1.0_r};

        point3_t result;
        result = as::affine::transform_pos(
            as::affine::from_mat4(shear_about_z), position);

        CHECK_THAT(arr(1.0_r, 1.0_r, 1.0_r), make_elements_sub(result, 3));
    }
}

TEST_CASE("mat_basis_access_mat3", "[as-mat]")
{
    using gsl::make_span;

    // clang-format off
    mat3_t mat3 {
        1.0_r, 2.0_r, 3.0_r,
        4.0_r, 5.0_r, 6.0_r,
        7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    const real_t basis_x[] = {1.0_r, 2.0_r, 3.0_r};
    CHECK_THAT(make_span(basis_x), make_elements_sub(mat3::basis_x(mat3), 3));
    const real_t basis_y[] = {4.0_r, 5.0_r, 6.0_r};
    CHECK_THAT(make_span(basis_y), make_elements_sub(mat3::basis_y(mat3), 3));
    const real_t basis_z[] = {7.0_r, 8.0_r, 9.0_r};
    CHECK_THAT(make_span(basis_z), make_elements_sub(mat3::basis_z(mat3), 3));
}

TEST_CASE("mat_basis_access_mat4", "[as-mat]")
{
    using gsl::make_span;

    // clang-format off
    mat4_t mat4 {
        1.0_r,  2.0_r,  3.0_r,  4.0_r,
        4.0_r,  5.0_r,  6.0_r,  7.0_r,
        7.0_r,  8.0_r,  9.0_r,  8.0_r,
        10.0_r, 11.0_r, 12.0_r, 9.0_r
    };
    // clang-format on

    const real_t basis_x[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    CHECK_THAT(make_span(basis_x), make_elements_sub(mat4::basis_x(mat4), 4));
    const real_t basis_y[] = {4.0_r, 5.0_r, 6.0_r, 7.0_r};
    CHECK_THAT(make_span(basis_y), make_elements_sub(mat4::basis_y(mat4), 4));
    const real_t basis_z[] = {7.0_r, 8.0_r, 9.0_r, 8.0_r};
    CHECK_THAT(make_span(basis_z), make_elements_sub(mat4::basis_z(mat4), 4));
    const real_t translation[] = {10.0_r, 11.0_r, 12.0_r, 9.0_r};
    CHECK_THAT(
        make_span(translation), make_elements_sub(mat4::translation(mat4), 4));
}

TEST_CASE("mat_basis_mutate_mat3", "[as-mat]")
{
    using gsl::make_span;

    mat3_t mat3{};

    const real_t basis_x[] = {1.0_r, 2.0_r, 3.0_r};
    const vec3_t x = vec3::from_arr(basis_x);
    mat3::basis_x(mat3, x);
    CHECK_THAT(make_span(basis_x), make_elements_sub(mat3::basis_x(mat3), 3));

    const real_t basis_y[] = {4.0_r, 5.0_r, 6.0_r};
    const vec3_t y = vec3::from_arr(basis_y);
    mat3::basis_y(mat3, y);
    CHECK_THAT(make_span(basis_y), make_elements_sub(mat3::basis_y(mat3), 3));

    const real_t basis_z[] = {7.0_r, 8.0_r, 9.0_r};
    const vec3_t z = vec3::from_arr(basis_z);
    mat3::basis_z(mat3, z);
    CHECK_THAT(make_span(basis_z), make_elements_sub(mat3::basis_z(mat3), 3));
}

TEST_CASE("mat_basis_mutate_mat4", "[as-mat]")
{
    using gsl::make_span;

    mat4_t mat4{};

    const real_t basis_x[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
    const vec4_t x = vec4::from_arr(basis_x);
    mat4::basis_x(mat4, x);
    CHECK_THAT(make_span(basis_x), make_elements_sub(mat4::basis_x(mat4), 4));

    const real_t basis_y[] = {4.0_r, 5.0_r, 6.0_r, 7.0_r};
    const vec4_t y = vec4::from_arr(basis_y);
    mat4::basis_y(mat4, y);
    CHECK_THAT(make_span(basis_y), make_elements_sub(mat4::basis_y(mat4), 4));

    const real_t basis_z[] = {7.0_r, 8.0_r, 9.0_r, 10.0_r};
    const vec4_t z = vec4::from_arr(basis_z);
    mat4::basis_z(mat4, z);
    CHECK_THAT(make_span(basis_z), make_elements_sub(mat4::basis_z(mat4), 4));

    const real_t translation[] = {10.0_r, 11.0_r, 12.0_r, 9.0_r};
    const vec4_t t = vec4::from_arr(translation);
    mat4::translation(mat4, t);
    CHECK_THAT(
        make_span(translation), make_elements_sub(mat4::translation(mat4), 4));
}

} // namespace unit_test

// explicit instantiations (for coverage)

// types
template struct as::mat_t<as::real_t, 2>;
template struct as::mat_t<as::real_t, 3>;
template struct as::mat_t<as::real_t, 4>;
template struct as::mat_t<as::real_t, 5>;

#ifdef __GNUC__
// constructor
template as::mat_t<as::real_t, 5>::mat_t(
    as::real_t, as::real_t, as::real_t, as::real_t, as::real_t, as::real_t,
    as::real_t, as::real_t, as::real_t, as::real_t, as::real_t, as::real_t,
    as::real_t, as::real_t, as::real_t, as::real_t, as::real_t, as::real_t,
    as::real_t, as::real_t, as::real_t, as::real_t, as::real_t, as::real_t,
    as::real_t) noexcept;
#endif // __GNUC__

// matrix multiply
template const as::mat_t<as::real_t, 3> as::operator*(
    const as::mat_t<as::real_t, 3>&, const as::mat_t<as::real_t, 3>&);
template const as::mat_t<as::real_t, 4> as::operator*(
    const as::mat_t<as::real_t, 4>&, const as::mat_t<as::real_t, 4>&);

// vector multiply
#if defined AS_ROW_MAJOR
template const as::vec_t<as::real_t, 3> as::operator*(
    const as::vec_t<as::real_t, 3>&, const as::mat_t<as::real_t, 3>&);
template const as::vec_t<as::real_t, 4> as::operator*(
    const as::vec_t<as::real_t, 4>&, const as::mat_t<as::real_t, 4>&);
#elif defined AS_COL_MAJOR
template const as::vec_t<as::real_t, 3> as::operator*(
    const as::mat_t<as::real_t, 3>&, const as::vec_t<as::real_t, 3>&);
template const as::vec_t<as::real_t, 4> as::operator*(
    const as::mat_t<as::real_t, 4>&, const as::vec_t<as::real_t, 4>&);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

// scalar multiply
template const as::mat_t<as::real_t, 3> as::operator*(
    const as::mat_t<as::real_t, 3>&, as::real_t scalar);
template const as::mat_t<as::real_t, 4> as::operator*(
    const as::mat_t<as::real_t, 4>&, as::real_t scalar);
template as::mat_t<as::real_t, 3>& as::operator*=(
    as::mat_t<as::real_t, 3>&, as::real_t scalar);
template as::mat_t<as::real_t, 4>& as::operator*=(
    as::mat_t<as::real_t, 4>&, as::real_t scalar);
