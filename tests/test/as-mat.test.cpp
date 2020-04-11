#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat_t;
using as::mat3_t;
using as::mat4_t;
using as::index_t;
using as::point3_t;
using as::real_t;
using as::vec_t;
using as::vec3_t;
using as::vec4_t;

// functions
using as::deg_to_rad;

// namespaces
namespace affine = as::affine;
namespace mat = as::mat;
namespace mat3 = as::mat3;
namespace mat4 = as::mat4;
namespace vec2 = as::vec2;
namespace vec3 = as::vec3;
namespace vec4 = as::vec4;

const real_t g_epsilon = std::numeric_limits<real_t>::epsilon();

TEST_CASE("mat_row_col_access_mat3", "[as_mat]")
{
    using gsl::make_span;

    mat3_t mat3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col0(), 3));
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col(0), 3));
    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col1(), 3));
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col(1), 3));
    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col2(), 3));
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col(2), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row0(), 3));
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row(0), 3));
    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row1(), 3));
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row(1), 3));
    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row2(), 3));
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row(2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row0(), 3));
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row(0), 3));
    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row1(), 3));
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row(1), 3));
    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row2(), 3));
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row(2), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col0(), 3));
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col(0), 3));
    const real_t col1[] = { 2.0f, 5.0f, 8.0f };
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col1(), 3));
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col(1), 3));
    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col2(), 3));
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col(2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    CHECK_THAT(make_span(elems), make_elements_sub(mat3, 9));

    mat3_t mat3_mult;
    mat3_mult = mat3_t(
        vec3_t(10.0f, 20.0f, 30.0f),
        vec3_t(40.0f, 50.0f, 60.0f),
        vec3_t(70.0f, 80.0f, 90.0f));

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f,
        40.0f, 50.0f, 60.0f,
        70.0f, 80.0f, 90.0f
    };

    CHECK_THAT(make_span(mult_elems), make_elements_sub(mat3_mult, 9));
}

TEST_CASE("mat_row_col_mutate_mat3", "[as_mat]")
{
    using gsl::make_span;

    mat3_t mat3;
    mat3 = mat3_t {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    const vec3_t c0 = vec3::from_arr(col0);
    mat3.col0(c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col0(), 3));
    mat3.col(0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col(0), 3));

    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    const vec3_t c1 = vec3::from_arr(col1);
    mat3.col1(c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col1(), 3));
    mat3.col(1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col(1), 3));

    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    const vec3_t c2 = vec3::from_arr(col2);
    mat3.col2(c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col2(), 3));
    mat3.col(2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col(2), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    const vec3_t r0 = vec3::from_arr(row0);
    mat3.row0(r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row0(), 3));
    mat3.row(0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row(0), 3));

    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    const vec3_t r1 = vec3::from_arr(row1);
    mat3.row1(r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row1(), 3));
    mat3.row(1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row(1), 3));

    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    const vec3_t r2 = vec3::from_arr(row2);
    mat3.row2(r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row2(), 3));
    mat3.row(2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row(2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    const vec3_t r0 = vec3::from_arr(row0);
    mat3.row0(r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row0(), 3));
    mat3.row(0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat3.row(0), 3));

    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    const vec3_t r1 = vec3::from_arr(row1);
    mat3.row1(r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row1(), 3));
    mat3.row(1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat3.row(1), 3));

    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    const vec3_t r2 = vec3::from_arr(row2);
    mat3.row2(r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row2(), 3));
    mat3.row(2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat3.row(2), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    const vec3_t c0 = vec3::from_arr(col0);
    mat3.col0(c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col0(), 3));
    mat3.col(0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat3.col(0), 3));

    const real_t col1[] = { 2.0f, 5.0f, 9.0f };
    const vec3_t c1 = vec3::from_arr(col1);
    mat3.col1(c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col1(), 3));
    mat3.col(1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat3.col(1), 3));

    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    const vec3_t c2 = vec3::from_arr(col2);
    mat3.col2(c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col2(), 3));
    mat3.col(2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat3.col(2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_row_col_access_mat4", "[as_mat]")
{
    using gsl::make_span;

    mat4_t mat4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col0(), 4));
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col(0), 4));
    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col1(), 4));
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col(1), 4));
    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col2(), 4));
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col(2), 4));
    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col3(), 4));
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col(3), 4));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row0(), 4));
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row(0), 4));
    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row1(), 4));
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row(1), 4));
    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row2(), 4));
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row(2), 4));
    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row3(), 4));
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row(3), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row0(), 4));
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row(0), 4));
    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row1(), 4));
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row(1), 4));
    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row2(), 4));
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row(2), 4));
    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row3(), 4));
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row(3), 4));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col0(), 4));
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col(0), 4));
    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col1(), 4));
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col(1), 4));
    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col2(), 4));
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col(2), 4));
    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col3(), 4));
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col(3), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    CHECK_THAT(make_span(elems), make_elements_sub(mat4, 16));

    mat4_t mat4_mult;
    mat4_mult = mat4_t(
        vec4_t(10.0f, 20.0f, 30.0f, 40.0f),
        vec4_t(50.0f, 60.0f, 70.0f, 80.0f),
        vec4_t(90.0f, 100.0f, 110.0f, 120.0f),
        vec4_t(130.0f, 140.0f, 150.0f, 160.0f)
    );

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f, 40.0f,
        50.0f, 60.0f, 70.0f, 80.0f,
        90.0f, 100.0f, 110.0f, 120.0f,
        130.0f, 140.0f, 150.0f, 160.0f
    };

    CHECK_THAT(make_span(mult_elems), make_elements_sub(mat4_mult, 16));
}

TEST_CASE("mat_row_col_mutate_mat4", "[as_mat]")
{
    using gsl::make_span;

    mat4_t mat4;
    mat4 = mat4_t {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const vec4_t c0 = vec4::from_arr(col0);
    mat4.col0(c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col0(), 4));
    mat4.col(0, c0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col(0), 4));
    CHECK(col0[0] == Approx(mat4.col(0)[0]).epsilon(g_epsilon));

    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const vec4_t c1 = vec4::from_arr(col1);
    mat4.col1(c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col1(), 4));
    mat4.col(1, c1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col(1), 4));
    CHECK(col1[1] == Approx(mat4.col(1)[1]).epsilon(g_epsilon));

    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const vec4_t c2 = vec4::from_arr(col2);
    mat4.col2(c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col2(), 4));
    mat4.col(2, c2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col(2), 4));
    CHECK(col2[2] == Approx(mat4.col(2)[2]).epsilon(g_epsilon));

    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const vec4_t c3 = vec4::from_arr(col3);
    mat4.col3(c3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col3(), 4));
    mat4.col(3, c3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col(3), 4));
    CHECK(col3[3] == Approx(mat4.col(3)[3]).epsilon(g_epsilon));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const vec4_t r0 = vec4::from_arr(row0);
    mat4.row0(r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row0(), 4));
    mat4.row(0, r0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row(0), 4));
    CHECK(row0[0] == Approx(mat4.row(0)[0]).epsilon(g_epsilon));

    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const vec4_t r1 = vec4::from_arr(row1);
    mat4.row1(r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row1(), 4));
    mat4.row(1, r1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row(1), 4));
    CHECK(row1[1] == Approx(mat4.row(1)[1]).epsilon(g_epsilon));

    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const vec4_t r2 = vec4::from_arr(row2);
    mat4.row2(r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row2(), 4));
    mat4.row(2, r2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row(2), 4));
    CHECK(row2[2] == Approx(mat4.row(2)[2]).epsilon(g_epsilon));

    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const vec4_t r3 = vec4::from_arr(row3);
    mat4.row3(r3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row3(), 4));
    mat4.row(3, r3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row(3), 4));
    CHECK(row3[3] == Approx(mat4.row(3)[3]).epsilon(g_epsilon));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const vec4_t c0 = vec4::from_arr(row0);
    mat4.row0(c0);
    CHECK_THAT(make_span(row0), make_elements_sub(mat4.row0(), 4));
    mat4.row(0, c0);
    CHECK(row0[0] == Approx(mat4.row(0)[0]).epsilon(g_epsilon));

    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const vec4_t c1 = vec4::from_arr(row1);
    mat4.row1(c1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row1(), 4));
    mat4.row(1, c1);
    CHECK_THAT(make_span(row1), make_elements_sub(mat4.row(1), 4));
    CHECK(row1[1] == Approx(mat4.row(1)[1]).epsilon(g_epsilon));

    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const vec4_t c2 = vec4::from_arr(row2);
    mat4.row2(c2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row2(), 4));
    mat4.row(2, c2);
    CHECK_THAT(make_span(row2), make_elements_sub(mat4.row(2), 4));
    CHECK(row2[2] == Approx(mat4.row(2)[2]).epsilon(g_epsilon));

    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const vec4_t c3 = vec4::from_arr(row3);
    mat4.row3(c3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row3(), 4));
    mat4.row(3, c3);
    CHECK_THAT(make_span(row3), make_elements_sub(mat4.row(3), 4));
    CHECK(row3[3] == Approx(mat4.row(3)[3]).epsilon(g_epsilon));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const vec4_t r0 = vec4::from_arr(col0);
    mat4.col0(r0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col0(), 4));
    mat4.col(0, r0);
    CHECK_THAT(make_span(col0), make_elements_sub(mat4.col(0), 4));
    CHECK(col0[0] == Approx(mat4.col(0)[0]).epsilon(g_epsilon));

    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const vec4_t r1 = vec4::from_arr(col1);
    mat4.col1(r1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col1(), 4));
    mat4.col(1, r1);
    CHECK_THAT(make_span(col1), make_elements_sub(mat4.col(1), 4));
    CHECK(col1[1] == Approx(mat4.col(1)[1]).epsilon(g_epsilon));

    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const vec4_t r2 = vec4::from_arr(col2);
    mat4.col2(r2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col2(), 4));
    mat4.col(2, r2);
    CHECK_THAT(make_span(col2), make_elements_sub(mat4.col(2), 4));
    CHECK(col2[2] == Approx(mat4.col(2)[2]).epsilon(g_epsilon));

    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const vec4_t r3 = vec4::from_arr(col3);
    mat4.col3(r3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col3(), 4));
    mat4.col(3, r3);
    CHECK_THAT(make_span(col3), make_elements_sub(mat4.col(3), 4));
    CHECK(col3[3] == Approx(mat4.col(3)[3]).epsilon(g_epsilon));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_mat4_from_mat3_and_vec3", "[as_mat]")
{
    using gsl::make_span;

    mat3_t mat3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    vec3_t vec3 { 10.0f, 11.0f, 12.0f };

    const real_t mat3_and_vec3[] = {
        1.0f, 2.0f, 3.0f, 0.0f,
        4.0f, 5.0f, 6.0f, 0.0f,
        7.0f, 8.0f, 9.0f, 0.0f,
        10.0f, 11.0f, 12.0f, 1.0f
    };

    {
        mat4_t mat4;
        mat4 = mat4_t{ mat3, vec3 };

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

        const real_t mat3_and_zero[] = {
            1.0f, 2.0f, 3.0f, 0.0f,
            4.0f, 5.0f, 6.0f, 0.0f,
            7.0f, 8.0f, 9.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        CHECK_THAT(make_span(mat3_and_zero), make_elements_sub(mat4, 16));
    }

    {
        mat4_t mat4;
        mat4 = mat4::from_vec3(vec3_t{ 10.f, 20.0f, 30.0f});

        const real_t zero_and_vec3[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            10.0f, 20.0f, 30.0f, 1.0f
        };

        CHECK_THAT(make_span(zero_and_vec3), make_elements_sub(mat4, 16));
    }
}

TEST_CASE("const_elem_access_mat_const", "[as_mat]")
{
    using gsl::make_span;

    const mat_t<real_t, 5> mat5(
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
        6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 15.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f);

    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14],
        mat5[15], mat5[16], mat5[17], mat5[18], mat5[19],
        mat5[20], mat5[21], mat5[22], mat5[23], mat5[24]
    };

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat5, 25));
}

TEST_CASE("elem_access_mat", "[as_mat]")
{
    using gsl::make_span;

    mat_t<real_t, 5> mat5(
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
        6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 15.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f
    );

    mat5[15] = 100.0f;
    mat5[20] = 200.0f;

    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14],
        100.0f, mat5[16], mat5[17], mat5[18], mat5[19],
        200.0f, mat5[21], mat5[22], mat5[23], mat5[24]
    };

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat5, 25));
}

TEST_CASE("elem_access_mat4_const", "[as_mat]")
{
    using gsl::make_span;

    const mat4_t mat4(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );

    const real_t mat_arr[] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f,
    };

    const real_t mat4_8 = mat4[8];
    CHECK(mat4_8 == Approx(mat_arr[8]).epsilon(g_epsilon));
    CHECK(mat4_8 == Approx(9.0f).epsilon(g_epsilon));

    CHECK_THAT(make_span(mat_arr), make_elements_sub(mat4, 16));
}

TEST_CASE("rvalue_elem_access_mat2_3_4", "[as_mat]")
{
    using gsl::make_span;

    auto make_mat2 = []() { return mat_t<real_t, 2>{ 5.0f, 10.0f, 15.0f, 20.0f }; };
    CHECK(make_mat2()[0] == Approx(5.0f).epsilon(g_epsilon));
    CHECK(make_mat2()[1] == Approx(10.0f).epsilon(g_epsilon));
    CHECK(make_mat2()[2] == Approx(15.0f).epsilon(g_epsilon));
    CHECK(make_mat2()[3] == Approx(20.0f).epsilon(g_epsilon));

    auto make_mat3 = []() {
        return mat3_t{
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        };
    };

    CHECK(make_mat3()[4] == Approx(5.0f).epsilon(g_epsilon));

    auto make_mat4 = [](){
        return mat4_t {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
    };

    CHECK(make_mat4()[7] == Approx(8.0f).epsilon(g_epsilon));
    CHECK(make_mat4()[15] == Approx(16.0f).epsilon(g_epsilon));
}

TEST_CASE("mat_dimensions_are_valid", "[as_mat]")
{
    CHECK(mat3::rows() == 3);
    CHECK(mat3::cols() == 3);
    CHECK(mat4::rows() == 4);
    CHECK(mat4::cols() == 4);

    CHECK(mat3_t::dim() == 3);
    CHECK(mat4_t::dim() == 4);
    CHECK(mat3_t::size() == 9);
    CHECK(mat4_t::size() == 16);

    mat_t<real_t, 5> mat5;
    CHECK(mat5.dim() == 5);
    CHECK(mat_t<real_t, 5>::dim() == index_t(5));
    CHECK(mat5.size() == 25);
}

TEST_CASE("multiply_same_size", "[as_mat]")
{
    using gsl::make_span;

    const mat3_t mat3_a {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    const mat3_t mat3_b {
        9.0f, 8.0f, 7.0f,
        6.0f, 5.0f, 4.0f,
        3.0f, 2.0f, 1.0f
    };

    const real_t mat_arr[] = {
        30.0f, 24.0f, 18.0f,
        84.0f, 69.0f, 54.0f,
        138.0f, 114.0f, 90.0f
    };

    mat3_t result;
#ifdef AS_ROW_MAJOR
    result = mat3_a * mat3_b;
#elif defined AS_COL_MAJOR
    result = mat3_b * mat3_a;
#endif

    CHECK_THAT(make_span(mat_arr), make_elements_sub(result, 9));
}

TEST_CASE("multiply_vector", "[as_mat]")
{
    using gsl::make_span;

    const mat3_t mat {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    const vec3_t vec { 11.0f, 12.0f, 13.0f };

    vec3_t result;
#ifdef AS_ROW_MAJOR
    result = vec * mat;
#elif defined AS_COL_MAJOR
    result = mat * vec;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    const real_t vec_arr[] = { 150.0f, 186.0f, 222.0f };
    CHECK_THAT(make_span(vec_arr), make_elements_sub(result, 3));
}

TEST_CASE("multiply_scalar", "[as_mat]")
{
    using gsl::make_span;

    const mat3_t mat3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    mat3_t result33 = mat3 * real_t(2.0);

    const real_t mat3_arr[] = {
        2.0f, 4.0f, 6.0f,
        8.0f, 10.0f, 12.0f,
        14.0f, 16.0f, 18.0f
    };

    CHECK_THAT(make_span(mat3_arr), make_elements_sub(result33, 9));

    const mat4_t mat4 {
        2.0f, 4.0f, 6.0f, 8.0f,
        10.0f, 12.0f, 14.0f, 16.0f,
        18.0f, 20.0f, 22.0f, 24.0f,
        26.0f, 28.0f, 30.0f, 32.0f
    };

    const mat4_t result4 = mat4 * real_t(2.0);

    const real_t mat4_arr[] = {
        4.0f, 8.0f, 12.0f, 16.0f,
        20.0f, 24.0f, 28.0f, 32.0f,
        36.0f, 40.0f, 44.0f, 48.0f,
        52.0f, 56.0f, 60.0f, 64.0f
    };

    CHECK_THAT(make_span(mat4_arr), make_elements_sub(result4, 16));
}

TEST_CASE("mat_from_arr", "[as_mat]")
{
    using gsl::make_span;

    {
        real_t elems[] = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };

        const mat4_t mat4_a = mat::from_arr<real_t, 4>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_a, 16));

        const mat4_t mat4_b = mat4::from_arr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_b, 16));
    }

    {
        real_t elems[] = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        };

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
        real_t elems[] = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };

        const mat4_t mat4_a = mat::from_ptr<real_t, 4>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_a, 16));

        const mat4_t mat4_b = mat4::from_ptr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat4_b, 16));
    }

    {
        real_t elems[] = {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        };

        const mat3_t mat3_a = mat::from_ptr<real_t, 3>(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_a, 9));

        const mat3_t mat3_b = mat3::from_ptr(elems);
        CHECK_THAT(make_span(elems), make_elements_sub(mat3_b, 9));
    }
}

TEST_CASE("mat_to_arr", "[as_mat]")
{
    using gsl::make_span;

    const mat3_t mat3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    real_t mat3_arr[9];
    mat::to_arr(mat3, mat3_arr);

    CHECK_THAT(make_span(mat3_arr), make_elements_sub(mat3, 9));
}

TEST_CASE("mat_transpose", "[as_mat]")
{
    using gsl::make_span;

    {
        const mat3_t mat3 {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f
        };

        const mat3_t mat3_transposed = mat::transpose(mat3);

        const real_t mat3_transposed_ref[] {
            1.0f, 4.0f, 7.0f,
            2.0f, 5.0f, 8.0f,
            3.0f, 6.0f, 9.0f
        };

        CHECK_THAT(make_span(mat3_transposed_ref), make_elements_sub(mat3_transposed, 9));
    }

    {
        const mat4_t mat4 = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };

        const mat4_t mat4_transposed = mat::transpose(mat4);

        const real_t mat4_transposed_reference[] {
            1.0f, 5.0f, 9.0f, 13.0f,
            2.0f, 6.0f, 10.0f, 14.0f,
            3.0f, 7.0f, 11.0f, 15.0f,
            4.0f, 8.0f, 12.0f, 16.0f
        };

        CHECK_THAT(make_span(mat4_transposed_reference), make_elements_sub(mat4_transposed, 16));
    }
}

TEST_CASE("mat_identity", "[as_mat]")
{
    using gsl::make_span;

    {
        mat3_t mat3_identity;
        mat3_identity = mat3::identity();

        const real_t mat3_identity_ref[] {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        CHECK_THAT(make_span(mat3_identity_ref), make_elements_sub(mat3_identity, 9));
    }

    {
        mat4_t mat4_identity;
        mat4_identity = mat4::identity();

        const real_t mat4_identity_ref[] {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        CHECK_THAT(make_span(mat4_identity_ref), make_elements_sub(mat4_identity, 16));
    }
}

TEST_CASE("mat_inverse", "[as_mat]")
{
    using gsl::make_span;

    {
        using mat2_t = mat_t<real_t, 2>;

        const mat2_t mat2 {
            1.0f, 2.0f,
            3.0f, 4.0f
        };

        const mat2_t mat2_inverse = mat::inverse(mat2);

        const real_t mat2_inverse_ref[] {
            -2.0f, 1.0f,
            3.0f/2.0f, -1.0f/2.0f
        };

        CHECK_THAT(make_span(mat2_inverse_ref), make_elements_sub(mat2_inverse, 4));
    }

    {
        const mat3_t mat3 {
            1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 2.0f, 9.0f
        };

        const mat3_t mat3_inverse = mat::inverse(mat3);

        const real_t mat3_inverse_ref[] {
            -11.0f/12.0f, 1.0f/3.0f, 1.0f/12.0f,
            -1.0f/6.0f, 1.0f/3.0f, -1.0f/6.0f,
            3.0f/4.0f, -1.0f/3.0f, 1.0f/12.0f
        };

        CHECK_THAT(make_span(mat3_inverse_ref), make_elements_sub(mat3_inverse, 9));
    }

    {
        const mat4_t mat4 = {
            1.0f, 3.0f, 5.0f, 9.0f,
            1.0f, 3.0f, 1.0f, 7.0f,
            4.0f, 3.0f, 9.0f, 7.0f,
            5.0f, 2.0f, 0.0f, 9.0f
        };

        const mat4_t mat4_inverse = mat::inverse(mat4);

        const real_t mat4_inverse_reference[] {
            -13.0f/47.0f, 2.0f/47.0f, 7.0f/47.0f, 6.0f/47.0f,
            -5.0f/8.0f, 7.0f/8.0f, 1.0f/4.0f, -1.0f/4.0f,
            39.0f/376.0f, -53.0f/376.0f, 13.0f/188.0f, -9.0f/188.0f,
            55.0f/188.0f, -41.0f/188.0f, -13.0f/94.0f, 9.0f/94.0f
        };

        CHECK_THAT(make_span(mat4_inverse_reference), make_elements_sub(mat4_inverse, 16));
    }
}

TEST_CASE("mat_scale", "[as_mat]")
{
    using gsl::make_span;

    mat3_t scale;
    scale = mat3::scale(vec3_t{ 1.0f, 2.0f, 3.0f});

    const real_t mat3_scale_reference[] {
        1.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 3.0f
    };

    CHECK_THAT(make_span(mat3_scale_reference), make_elements_sub(scale, 9));

    mat3_t uniform_scale;
    uniform_scale = mat3::scale(5.0f);

    const real_t mat3_uniform_scale_reference[] {
        5.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 5.0f
    };

    CHECK_THAT(make_span(mat3_uniform_scale_reference), make_elements_sub(uniform_scale, 9));
}

TEST_CASE("mat3_from_mat4", "[as_mat]")
{
    using gsl::make_span;

    mat4_t mat4;
    mat4 = mat4::identity();

    mat3_t mat3;
    mat3 = mat3::from_mat4(mat4);

    const real_t mat3_identity_ref[] {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    CHECK_THAT(make_span(mat3_identity_ref), make_elements_sub(mat3, 9));
}

TEST_CASE("mat3_axis_angle", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle =
            mat3::axis_angle(vec3::axis_x(), deg_to_rad(90.0f));
        real_t result_reference[] = { 0.0f, -1.0f, 0.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }

    {
        mat3_t axis_angle =
            mat3::axis_angle(vec3::axis_y(), deg_to_rad(90.0f));
        real_t result_reference[] = { 0.0f, 0.0f, -1.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_x() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3::axis_x();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }
}

TEST_CASE("mat3_rotate_xyz", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle =
            mat3::rotation_xyz(deg_to_rad(45.0f), deg_to_rad(90.0f), deg_to_rad(45.0f));
        real_t result_reference[] = { 0.0f, 1.0f, 0.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_y() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }

    {
        mat3_t axis_angle =
            mat3::rotation_xyz(deg_to_rad(-180.0f), deg_to_rad(90.0f), deg_to_rad(-90.0f));
        real_t result_reference[] = { 0.0f, 1.0f, 0.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result = axis_angle * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }
}

TEST_CASE("mat3_rotate_zxy", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_angle =
            mat3::rotation_zxy(deg_to_rad(90.0f), deg_to_rad(90.0f), deg_to_rad(0.0f));
        real_t result_reference_y[] = { 1.0f, 0.0f, 0.0f };
        real_t result_reference_z[] = { 0.0f, -1.0f, 0.0f };

        vec3_t result_y;
        vec3_t result_z;
#ifdef AS_ROW_MAJOR
        result_y = vec3::axis_y() * axis_angle;
        result_z = vec3::axis_z() * axis_angle;
#elif defined AS_COL_MAJOR
        result_y = axis_angle * vec3::axis_y();
        result_z = axis_angle * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference_y),
            make_elements_sub(result_y, 3).margin(std::numeric_limits<float>::epsilon())
        );

        CHECK_THAT(
            make_span(result_reference_z),
            make_elements_sub(result_z, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }

    {
        mat3_t axis_angle =
            mat3::rotation_zxy(deg_to_rad(0.0f), deg_to_rad(-90.0f), deg_to_rad(-90.0f));
        real_t result_reference_x[] = { 0.0f, -1.0f, 0.0f };
        real_t result_reference_y[] = { 0.0f, 0.0f, 1.0f };

        vec3_t result_x;
        vec3_t result_y;
#ifdef AS_ROW_MAJOR
        result_x = vec3::axis_x() * axis_angle;
        result_y = vec3::axis_y() * axis_angle;
#elif defined AS_COL_MAJOR
        result_x = axis_angle * vec3::axis_x();
        result_y = axis_angle * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference_x),
            make_elements_sub(result_x, 3).margin(std::numeric_limits<float>::epsilon())
        );

        CHECK_THAT(
            make_span(result_reference_y),
            make_elements_sub(result_y, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }
}

TEST_CASE("mat3_rotate_x_y_z_separate", "[as-mat]")
{
    using gsl::make_span;

    {
        mat3_t axis_x = mat3::rotation_x(deg_to_rad(45.0f));
        mat3_t axis_y = mat3::rotation_y(deg_to_rad(90.0f));
        mat3_t axis_z = mat3::rotation_z(deg_to_rad(45.0f));

        real_t result_reference[] = { 0.0f, 1.0f, 0.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_y() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
        result = axis_z * axis_y * axis_x * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }

    {
        mat3_t axis_x = mat3::rotation_x(deg_to_rad(-180.0f));
        mat3_t axis_y = mat3::rotation_y(deg_to_rad(90.0f));
        mat3_t axis_z = mat3::rotation_z(deg_to_rad(-90.0f));

        real_t result_reference[] = { 0.0f, 1.0f, 0.0f };

        vec3_t result;
#ifdef AS_ROW_MAJOR
        result = vec3::axis_z() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
        result = axis_z * axis_y * axis_x * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

        // note - checking against 0.0f requires margin
        CHECK_THAT(
            make_span(result_reference),
            make_elements_sub(result, 3).margin(std::numeric_limits<float>::epsilon())
        );
    }
}

// explicit instantiations (for coverage)

// types
template struct as::mat_t<real_t, 2>;
template struct as::mat_t<real_t, 3>;
template struct as::mat_t<real_t, 4>;
template struct as::mat_t<real_t, 5>;

#ifdef __GNUC__
// constructor
template as::mat_t<real_t, 5>::mat_t(
    real_t, real_t, real_t, real_t, real_t,
    real_t, real_t, real_t, real_t, real_t,
    real_t, real_t, real_t, real_t, real_t,
    real_t, real_t, real_t, real_t, real_t,
    real_t, real_t, real_t, real_t, real_t) noexcept;
#endif // __GNUC__

// matrix multiply
template const mat_t<real_t, 3> as::operator*(const mat_t<real_t, 3>&, const mat_t<real_t, 3>&);
template const mat_t<real_t, 4> as::operator*(const mat_t<real_t, 4>&, const mat_t<real_t, 4>&);

// vector multiply
#if defined AS_ROW_MAJOR
template const vec_t<real_t, 3> as::operator*(const vec_t<real_t, 3>&, const mat_t<real_t, 3>&);
template const vec_t<real_t, 4> as::operator*(const vec_t<real_t, 4>&, const mat_t<real_t, 4>&);
#elif defined AS_COL_MAJOR
template const vec_t<real_t, 3> as::operator*(const mat_t<real_t, 3>&, const vec_t<real_t, 3>&);
template const vec_t<real_t, 4> as::operator*(const mat_t<real_t, 4>&, const vec_t<real_t, 4>&);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

// scalar multiply
template const mat_t<real_t, 3> as::operator*(const mat_t<real_t, 3>&, real_t scalar);
template const mat_t<real_t, 4> as::operator*(const mat_t<real_t, 4>&, real_t scalar);
template mat_t<real_t, 3>& as::operator*=(mat_t<real_t, 3>&, real_t scalar);
template mat_t<real_t, 4>& as::operator*=(mat_t<real_t, 4>&, real_t scalar);

} // namespace unit_test
