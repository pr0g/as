#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

using namespace as;

TEST_CASE("mat_row_col_access_mat3", "[as_mat]")
{
    using namespace gsl;

    mat3_t mat3 {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col0(), 3));
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col(0), 3));
    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col1(), 3));
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col(1), 3));
    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col2(), 3));
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col(2), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row0(), 3));
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row(0), 3));
    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row1(), 3));
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row(1), 3));
    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row2(), 3));
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row(2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row0(), 3));
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row(0), 3));
    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row1(), 3));
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row(1), 3));
    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row2(), 3));
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row(2), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col0(), 3));
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col(0), 3));
    const real_t col1[] = { 2.0f, 5.0f, 8.0f };
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col1(), 3));
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col(1), 3));
    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col2(), 3));
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col(2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

    CHECK_THAT(span(elems), ElementsAreSubscript(mat3, 9));

    mat3_t mat3_mult;
    mat3_mult = mat3_t(
        vec3_t(10.0f, 20.0f, 30.0f),  //
        vec3_t(40.0f, 50.0f, 60.0f),  //
        vec3_t(70.0f, 80.0f, 90.0f)); //

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f, //
        40.0f, 50.0f, 60.0f, //
        70.0f, 80.0f, 90.0f  //
    };

    CHECK_THAT(span(mult_elems), ElementsAreSubscript(mat3_mult, 9));
}

TEST_CASE("mat_row_col_mutate_mat3", "[as_mat]")
{
    using namespace gsl;

    mat3_t mat3;
    mat3 = mat3_t {
        0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f  //
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    const vec3_t c0 = vec3::from_arr(col0);
    mat3.col0(c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col0(), 3));
    mat3.col(0, c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col(0), 3));

    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    const vec3_t c1 = vec3::from_arr(col1);
    mat3.col1(c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col1(), 3));
    mat3.col(1, c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col(1), 3));

    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    const vec3_t c2 = vec3::from_arr(col2);
    mat3.col2(c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col2(), 3));
    mat3.col(2, c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col(2), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    const vec3_t r0 = vec3::from_arr(row0);
    mat3.row0(r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row0(), 3));
    mat3.row(0, r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row(0), 3));

    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    const vec3_t r1 = vec3::from_arr(row1);
    mat3.row1(r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row1(), 3));
    mat3.row(1, r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row(1), 3));

    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    const vec3_t r2 = vec3::from_arr(row2);
    mat3.row2(r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row2(), 3));
    mat3.row(2, r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row(2), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    const vec3_t r0 = vec3::from_arr(row0);
    mat3.row0(r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row0(), 3));
    mat3.row(0, r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat3.row(0), 3));

    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    const vec3_t r1 = vec3::from_arr(row1);
    mat3.row1(r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row1(), 3));
    mat3.row(1, r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat3.row(1), 3));

    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    const vec3_t r2 = vec3::from_arr(row2);
    mat3.row2(r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row2(), 3));
    mat3.row(2, r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat3.row(2), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    const vec3_t c0 = vec3::from_arr(col0);
    mat3.col0(c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col0(), 3));
    mat3.col(0, c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat3.col(0), 3));

    const real_t col1[] = { 2.0f, 5.0f, 9.0f };
    const vec3_t c1 = vec3::from_arr(col1);
    mat3.col1(c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col1(), 3));
    mat3.col(1, c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat3.col(1), 3));

    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    const vec3_t c2 = vec3::from_arr(col2);
    mat3.col2(c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col2(), 3));
    mat3.col(2, c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat3.col(2), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_row_col_access_mat4", "[as_mat]")
{
    using namespace gsl;

    mat4_t mat4 {
        1.0f, 2.0f, 3.0f, 4.0f,     //
        5.0f, 6.0f, 7.0f, 8.0f,     //
        9.0f, 10.0f, 11.0f, 12.0f,  //
        13.0f, 14.0f, 15.0f, 16.0f  //
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col0(), 4));
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col(0), 4));
    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col1(), 4));
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col(1), 4));
    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col2(), 4));
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col(2), 4));
    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col3(), 4));
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col(3), 4));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row0(), 4));
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row(0), 4));
    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row1(), 4));
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row(1), 4));
    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row2(), 4));
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row(2), 4));
    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row3(), 4));
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row(3), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row0(), 4));
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row(0), 4));
    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row1(), 4));
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row(1), 4));
    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row2(), 4));
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row(2), 4));
    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row3(), 4));
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row(3), 4));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col0(), 4));
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col(0), 4));
    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col1(), 4));
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col(1), 4));
    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col2(), 4));
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col(2), 4));
    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col3(), 4));
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col(3), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f, 4.0f,    //
        5.0f, 6.0f, 7.0f, 8.0f,    //
        9.0f, 10.0f, 11.0f, 12.0f, //
        13.0f, 14.0f, 15.0f, 16.0f //
    };

    CHECK_THAT(span(elems), ElementsAreSubscript(mat4, 16));

    mat4_t mat4_mult;
    mat4_mult = mat4_t(
        vec4_t(10.0f, 20.0f, 30.0f, 40.0f),    //
        vec4_t(50.0f, 60.0f, 70.0f, 80.0f),    //
        vec4_t(90.0f, 100.0f, 110.0f, 120.0f), //
        vec4_t(130.0f, 140.0f, 150.0f, 160.0f) //
    );

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f, 40.0f,    //
        50.0f, 60.0f, 70.0f, 80.0f,    //
        90.0f, 100.0f, 110.0f, 120.0f, //
        130.0f, 140.0f, 150.0f, 160.0f //
    };

    CHECK_THAT(span(mult_elems), ElementsAreSubscript(mat4_mult, 16));
}

TEST_CASE("mat_row_col_mutate_mat4", "[as_mat]")
{
    using namespace gsl;

    mat4_t mat4;
    mat4 = mat4_t {
        0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f  //
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const vec4_t c0 = vec4::from_arr(col0);
    mat4.col0(c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col0(), 4));
    mat4.col(0, c0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col(0), 4));

    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const vec4_t c1 = vec4::from_arr(col1);
    mat4.col1(c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col1(), 4));
    mat4.col(1, c1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col(1), 4));

    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const vec4_t c2 = vec4::from_arr(col2);
    mat4.col2(c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col2(), 4));
    mat4.col(2, c2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col(2), 4));

    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const vec4_t c3 = vec4::from_arr(col3);
    mat4.col3(c3);
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col3(), 4));
    mat4.col(3, c3);
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col(3), 4));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const vec4_t r0 = vec4::from_arr(row0);
    mat4.row0(r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row0(), 4));
    mat4.row(0, r0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row(0), 4));

    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const vec4_t r1 = vec4::from_arr(row1);
    mat4.row1(r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row1(), 4));
    mat4.row(1, r1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row(1), 4));

    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const vec4_t r2 = vec4::from_arr(row2);
    mat4.row2(r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row2(), 4));
    mat4.row(2, r2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row(2), 4));

    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const vec4_t r3 = vec4::from_arr(row3);
    mat4.row3(r3);
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row3(), 4));
    mat4.row(3, r3);
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row(3), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const vec4_t c0 = vec4::from_arr(row0);
    mat4.row0(c0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row0(), 4));
    mat4.row(0, c0);
    CHECK_THAT(span(row0), ElementsAreSubscript(mat4.row(0), 4));

    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const vec4_t c1 = vec4::from_arr(row1);
    mat4.row1(c1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row1(), 4));
    mat4.row(1, c1);
    CHECK_THAT(span(row1), ElementsAreSubscript(mat4.row(1), 4));

    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const vec4_t c2 = vec4::from_arr(row2);
    mat4.row2(c2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row2(), 4));
    mat4.row(2, c2);
    CHECK_THAT(span(row2), ElementsAreSubscript(mat4.row(2), 4));

    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const vec4_t c3 = vec4::from_arr(row3);
    mat4.row3(c3);
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row3(), 4));
    mat4.row(3, c3);
    CHECK_THAT(span(row3), ElementsAreSubscript(mat4.row(3), 4));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const vec4_t r0 = vec4::from_arr(col0);
    mat4.col0(r0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col0(), 4));
    mat4.col(0, r0);
    CHECK_THAT(span(col0), ElementsAreSubscript(mat4.col(0), 4));

    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const vec4_t r1 = vec4::from_arr(col1);
    mat4.col1(r1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col1(), 4));
    mat4.col(1, r1);
    CHECK_THAT(span(col1), ElementsAreSubscript(mat4.col(1), 4));

    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const vec4_t r2 = vec4::from_arr(col2);
    mat4.col2(r2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col2(), 4));
    mat4.col(2, r2);
    CHECK_THAT(span(col2), ElementsAreSubscript(mat4.col(2), 4));

    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const vec4_t r3 = vec4::from_arr(col3);
    mat4.col3(r3);
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col3(), 4));
    mat4.col(3, r3);
    CHECK_THAT(span(col3), ElementsAreSubscript(mat4.col(3), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_mat4_from_mat3_and_vec3", "[as_mat]")
{
    using namespace gsl;

    mat3_t mat3 {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

    vec3_t vec3 { 10.0f, 11.0f, 12.0f };

    mat4_t mat4;
    mat4 = mat4_t{ mat3, vec3 };

    const real_t mat3_and_vec3[] = {
        1.0f, 2.0f, 3.0f, 0.0f,   //
        4.0f, 5.0f, 6.0f, 0.0f,   //
        7.0f, 8.0f, 9.0f, 0.0f,   //
        10.0f, 11.0f, 12.0f, 1.0f //
    };

    CHECK_THAT(span(mat3_and_vec3), ElementsAreSubscript(mat4, 16));
}

TEST_CASE("const_elem_access_mat_const", "[as_mat]")
{
    using namespace gsl;

    const mat_t<real_t, 5> mat5(
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,       //
        6.0f, 7.0f, 8.0f, 9.0f, 10.0f,      //
        11.0f, 12.0f, 13.0f, 15.0f, 15.0f,  //
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f,  //
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f); //

    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],      //
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],      //
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14], //
        mat5[15], mat5[16], mat5[17], mat5[18], mat5[19], //
        mat5[20], mat5[21], mat5[22], mat5[23], mat5[24]  //
    };

    CHECK_THAT(span(mat_arr), ElementsAreSubscript(mat5, 25));
}

TEST_CASE("elem_access_mat", "[as_mat]")
{
    using namespace gsl;

    mat_t<real_t, 5> mat5(
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,      //
        6.0f, 7.0f, 8.0f, 9.0f, 10.0f,     //
        11.0f, 12.0f, 13.0f, 15.0f, 15.0f, //
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f, //
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f  //
    );

    mat5[15] = 100.0f;
    mat5[20] = 200.0f;

    const real_t mat_arr[] = {
        mat5[0], mat5[1], mat5[2], mat5[3], mat5[4],      //
        mat5[5], mat5[6], mat5[7], mat5[8], mat5[9],      //
        mat5[10], mat5[11], mat5[12], mat5[13], mat5[14], //
        100.0f, mat5[16], mat5[17], mat5[18], mat5[19],    //
        200.0f, mat5[21], mat5[22], mat5[23], mat5[24]     //
    };

    CHECK_THAT(span(mat_arr), ElementsAreSubscript(mat5, 25));
}

TEST_CASE("elem_access_mat4_const", "[as_mat]")
{
    using namespace gsl;

    const mat4_t mat4(
        1.0f, 2.0f, 3.0f, 4.0f,     //
        5.0f, 6.0f, 7.0f, 8.0f,     //
        9.0f, 10.0f, 11.0f, 12.0f,  //
        13.0f, 14.0f, 15.0f, 16.0f  //
    );

    const real_t mat_arr[] = {
        1.0f, 2.0f, 3.0f, 4.0f,     //
        5.0f, 6.0f, 7.0f, 8.0f,     //
        9.0f, 10.0f, 11.0f, 12.0f,  //
        13.0f, 14.0f, 15.0f, 16.0f, //
    };

    const real_t mat4_8 = mat4[8];
    CHECK(mat4_8 == mat_arr[8]);
    CHECK(mat4_8 == 9.0f);

    CHECK_THAT(span(mat_arr), ElementsAreSubscript(mat4, 16));
}

TEST_CASE("multiply_same_size", "[as_mat]")
{
    using namespace gsl;

    const mat3_t lhs {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

    const mat3_t rhs {
        9.0f, 8.0f, 7.0f, //
        6.0f, 5.0f, 4.0f, //
        3.0f, 2.0f, 1.0f  //
    };

    const real_t mat_arr[] = {
        30.0f, 24.0f, 18.0f,  //
        84.0f, 69.0f, 54.0f,  //
        138.0f, 114.0f, 90.0f //
    };

    mat3_t result;
#ifdef AS_ROW_MAJOR
    result = lhs * rhs;
#elif defined AS_COL_MAJOR
    result = rhs * lhs;
#endif

    CHECK_THAT(span(mat_arr), ElementsAreSubscript(result, 9));
}

TEST_CASE("multiply_vector", "[as_mat]")
{
    using namespace gsl;

    const mat3_t mat {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

    const vec3_t vec { 11.0f, 12.0f, 13.0f };

    vec3_t result;
#ifdef AS_ROW_MAJOR
    result = vec * mat;
#elif defined AS_COL_MAJOR
    result = mat * vec;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    const real_t vec_arr[] = { 150.0f, 186.0f, 222.0f };
    CHECK_THAT(span(vec_arr), ElementsAreSubscript(result, 3));
}

TEST_CASE("multiply_scalar", "[as_mat]")
{
    using namespace gsl;

    const mat3_t mat3 {
        1.0f, 2.0f, 3.0f, //
        4.0f, 5.0f, 6.0f, //
        7.0f, 8.0f, 9.0f  //
    };

    mat3_t result33 = mat3 * 2.0f;

    const real_t mat3_arr[] = {
        2.0f, 4.0f, 6.0f,   //
        8.0f, 10.0f, 12.0f, //
        14.0f, 16.0f, 18.0f //
    };

    CHECK_THAT(span(mat3_arr), ElementsAreSubscript(result33, 9));

    const mat4_t mat4 {
        2.0f, 4.0f, 6.0f, 8.0f,     //
        10.0f, 12.0f, 14.0f, 16.0f, //
        18.0f, 20.0f, 22.0f, 24.0f, //
        26.0f, 28.0f, 30.0f, 32.0f  //
    };

    const mat4_t result44 = mat4 * 2.0f;

    const real_t mat4_arr[] = {
        4.0f, 8.0f, 12.0f, 16.0f,   //
        20.0f, 24.0f, 28.0f, 32.0f, //
        36.0f, 40.0f, 44.0f, 48.0f, //
        52.0f, 56.0f, 60.0f, 64.0f  //
    };

    CHECK_THAT(span(mat4_arr), ElementsAreSubscript(result44, 16));
}

// explicit instantiations (for coverage)

// types
template struct as::mat_t<real_t, 2>;
template struct as::mat_t<real_t, 3>;
template struct as::mat_t<real_t, 4>;
template struct as::mat_t<real_t, 5>;

// constructor
template as::mat_t<real_t, 5>::mat_t(
    real_t, real_t, real_t, real_t, real_t,             //
    real_t, real_t, real_t, real_t, real_t,             //
    real_t, real_t, real_t, real_t, real_t,             //
    real_t, real_t, real_t, real_t, real_t,             //
    real_t, real_t, real_t, real_t, real_t) noexcept;   //

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
