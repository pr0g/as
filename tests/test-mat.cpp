#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "as/as-math-ops.hpp"

using namespace as;

TEST(as_mat, mat_initialization)
{
    using ::testing::ElementsAreArray;

    mat_t<real_t, 2, 5> mat25 {
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f
    };

    const real_t arr[] = {
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f
    };

    EXPECT_THAT(arr, ElementsAreArray(mat25.elems(), 10));
}

TEST(as_mat, mat_row_col_access_mat33)
{
    using ::testing::ElementsAreArray;
    using ::testing::ElementsAre;

    mat33_t mat33 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    EXPECT_THAT(col0, ElementsAreArray(mat33.col0().elems(), 3));
    EXPECT_THAT(col0, ElementsAreArray(mat33.col(0).elems(), 3));
    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    EXPECT_THAT(col1, ElementsAreArray(mat33.col1().elems(), 3));
    EXPECT_THAT(col1, ElementsAreArray(mat33.col(1).elems(), 3));
    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    EXPECT_THAT(col2, ElementsAreArray(mat33.col2().elems(), 3));
    EXPECT_THAT(col2, ElementsAreArray(mat33.col(2).elems(), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    EXPECT_THAT(row0, ElementsAreArray(mat33.row0().elems(), 3));
    EXPECT_THAT(row0, ElementsAreArray(mat33.row(0).elems(), 3));
    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    EXPECT_THAT(row1, ElementsAreArray(mat33.row1().elems(), 3));
    EXPECT_THAT(row1, ElementsAreArray(mat33.row(1).elems(), 3));
    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    EXPECT_THAT(row2, ElementsAreArray(mat33.row2().elems(), 3));
    EXPECT_THAT(row2, ElementsAreArray(mat33.row(2).elems(), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    EXPECT_THAT(row0, ElementsAreArray(mat33.row0().elems(), 3));
    EXPECT_THAT(row0, ElementsAreArray(mat33.row(0).elems(), 3));
    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    EXPECT_THAT(row1, ElementsAreArray(mat33.row1().elems(), 3));
    EXPECT_THAT(row1, ElementsAreArray(mat33.row(1).elems(), 3));
    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    EXPECT_THAT(row2, ElementsAreArray(mat33.row2().elems(), 3));
    EXPECT_THAT(row2, ElementsAreArray(mat33.row(2).elems(), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    EXPECT_THAT(col0, ElementsAreArray(mat33.col0().elems(), 3));
    EXPECT_THAT(col0, ElementsAreArray(mat33.col(0).elems(), 3));
    const real_t col1[] = { 2.0f, 5.0f, 8.0f };
    EXPECT_THAT(col1, ElementsAreArray(mat33.col1().elems(), 3));
    EXPECT_THAT(col1, ElementsAreArray(mat33.col(1).elems(), 3));
    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    EXPECT_THAT(col2, ElementsAreArray(mat33.col2().elems(), 3));
    EXPECT_THAT(col2, ElementsAreArray(mat33.col(2).elems(), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    EXPECT_THAT(elems, ElementsAreArray(mat33.elems(), 9));

    mat33_t mat33_mult;
    mat33_mult = mat33_t(
        vec3_t(10.0f, 20.0f, 30.0f),
        vec3_t(40.0f, 50.0f, 60.0f),
        vec3_t(70.0f, 80.0f, 90.0f));

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f,
        40.0f, 50.0f, 60.0f,
        70.0f, 80.0f, 90.0f
    };

    EXPECT_THAT(mult_elems, ElementsAreArray(mat33_mult.elems(), 9));
}

TEST(as_mat, mat_row_col_mutate_mat33)
{
    using ::testing::ElementsAreArray;
    using ::testing::ElementsAre;

    mat33_t mat33;
    mat33 = mat33_t {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f };
    const as::vec3_t c0 = as::vec3::from_arr(col0);
    mat33.col0(c0);
    EXPECT_THAT(col0, ElementsAreArray(mat33.col0().elems(), 3));
    mat33.col(0, c0);
    EXPECT_THAT(col0, ElementsAreArray(mat33.col(0).elems(), 3));

    const real_t col1[] = { 4.0f, 5.0f, 6.0f };
    const as::vec3_t c1 = as::vec3::from_arr(col1);
    mat33.col1(c1);
    EXPECT_THAT(col1, ElementsAreArray(mat33.col1().elems(), 3));
    mat33.col(1, c1);
    EXPECT_THAT(col1, ElementsAreArray(mat33.col(1).elems(), 3));

    const real_t col2[] = { 7.0f, 8.0f, 9.0f };
    const as::vec3_t c2 = as::vec3::from_arr(col2);
    mat33.col2(c2);
    EXPECT_THAT(col2, ElementsAreArray(mat33.col2().elems(), 3));
    mat33.col(2, c2);
    EXPECT_THAT(col2, ElementsAreArray(mat33.col(2).elems(), 3));

    const real_t row0[] = { 1.0f, 4.0f, 7.0f };
    const as::vec3_t r0 = as::vec3::from_arr(row0);
    mat33.row0(r0);
    EXPECT_THAT(row0, ElementsAreArray(mat33.row0().elems(), 3));
    mat33.row(0, r0);
    EXPECT_THAT(row0, ElementsAreArray(mat33.row(0).elems(), 3));

    const real_t row1[] = { 2.0f, 5.0f, 8.0f };
    const as::vec3_t r1 = as::vec3::from_arr(row1);
    mat33.row1(r1);
    EXPECT_THAT(row1, ElementsAreArray(mat33.row1().elems(), 3));
    mat33.row(1, r1);
    EXPECT_THAT(row1, ElementsAreArray(mat33.row(1).elems(), 3));

    const real_t row2[] = { 3.0f, 6.0f, 9.0f };
    const as::vec3_t r2 = as::vec3::from_arr(row2);
    mat33.row2(r2);
    EXPECT_THAT(row2, ElementsAreArray(mat33.row2().elems(), 3));
    mat33.row(2, r2);
    EXPECT_THAT(row2, ElementsAreArray(mat33.row(2).elems(), 3));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f };
    const as::vec3_t r0 = as::vec3::from_arr(row0);
    mat33.row0(r0);
    EXPECT_THAT(row0, ElementsAreArray(mat33.row0().elems(), 3));
    mat33.row(0, r0);
    EXPECT_THAT(row0, ElementsAreArray(mat33.row(0).elems(), 3));

    const real_t row1[] = { 4.0f, 5.0f, 6.0f };
    const as::vec3_t r1 = as::vec3::from_arr(row1);
    mat33.row1(r1);
    EXPECT_THAT(row1, ElementsAreArray(mat33.row1().elems(), 3));
    mat33.row(1, r1);
    EXPECT_THAT(row1, ElementsAreArray(mat33.row(1).elems(), 3));

    const real_t row2[] = { 7.0f, 8.0f, 9.0f };
    const as::vec3_t r2 = as::vec3::from_arr(row2);
    mat33.row2(r2);
    EXPECT_THAT(row2, ElementsAreArray(mat33.row2().elems(), 3));
    mat33.row(2, r2);
    EXPECT_THAT(row2, ElementsAreArray(mat33.row(2).elems(), 3));

    const real_t col0[] = { 1.0f, 4.0f, 7.0f };
    const as::vec3_t c0 = as::vec3::from_arr(col0);
    mat33.col0(c0);
    EXPECT_THAT(col0, ElementsAreArray(mat33.col0().elems(), 3));
    mat33.col(0, c0);
    EXPECT_THAT(col0, ElementsAreArray(mat33.col(0).elems(), 3));

    const real_t col1[] = { 2.0f, 5.0f, 9.0f };
    const as::vec3_t c1 = as::vec3::from_arr(col1);
    mat33.col1(c1);
    EXPECT_THAT(col1, ElementsAreArray(mat33.col1().elems(), 3));
    mat33.col(1, c1);
    EXPECT_THAT(col1, ElementsAreArray(mat33.col(1).elems(), 3));

    const real_t col2[] = { 3.0f, 6.0f, 9.0f };
    const as::vec3_t c2 = as::vec3::from_arr(col2);
    mat33.col2(c2);
    EXPECT_THAT(col2, ElementsAreArray(mat33.col2().elems(), 3));
    mat33.col(2, c2);
    EXPECT_THAT(col2, ElementsAreArray(mat33.col(2).elems(), 3));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST(as_mat, mat_row_col_access_mat44)
{
    using ::testing::ElementsAreArray;
    using ::testing::ElementsAre;

    mat44_t mat44 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_THAT(col0, ElementsAreArray(mat44.col0().elems(), 4));
    EXPECT_THAT(col0, ElementsAreArray(mat44.col(0).elems(), 4));
    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    EXPECT_THAT(col1, ElementsAreArray(mat44.col1().elems(), 4));
    EXPECT_THAT(col1, ElementsAreArray(mat44.col(1).elems(), 4));
    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    EXPECT_THAT(col2, ElementsAreArray(mat44.col2().elems(), 4));
    EXPECT_THAT(col2, ElementsAreArray(mat44.col(2).elems(), 4));
    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    EXPECT_THAT(col3, ElementsAreArray(mat44.col3().elems(), 4));
    EXPECT_THAT(col3, ElementsAreArray(mat44.col(3).elems(), 4));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    EXPECT_THAT(row0, ElementsAreArray(mat44.row0().elems(), 4));
    EXPECT_THAT(row0, ElementsAreArray(mat44.row(0).elems(), 4));
    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    EXPECT_THAT(row1, ElementsAreArray(mat44.row1().elems(), 4));
    EXPECT_THAT(row1, ElementsAreArray(mat44.row(1).elems(), 4));
    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    EXPECT_THAT(row2, ElementsAreArray(mat44.row2().elems(), 4));
    EXPECT_THAT(row2, ElementsAreArray(mat44.row(2).elems(), 4));
    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    EXPECT_THAT(row3, ElementsAreArray(mat44.row3().elems(), 4));
    EXPECT_THAT(row3, ElementsAreArray(mat44.row(3).elems(), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_THAT(row0, ElementsAreArray(mat44.row0().elems(), 4));
    EXPECT_THAT(row0, ElementsAreArray(mat44.row(0).elems(), 4));
    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    EXPECT_THAT(row1, ElementsAreArray(mat44.row1().elems(), 4));
    EXPECT_THAT(row1, ElementsAreArray(mat44.row(1).elems(), 4));
    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    EXPECT_THAT(row2, ElementsAreArray(mat44.row2().elems(), 4));
    EXPECT_THAT(row2, ElementsAreArray(mat44.row(2).elems(), 4));
    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    EXPECT_THAT(row3, ElementsAreArray(mat44.row3().elems(), 4));
    EXPECT_THAT(row3, ElementsAreArray(mat44.row(3).elems(), 4));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    EXPECT_THAT(col0, ElementsAreArray(mat44.col0().elems(), 4));
    EXPECT_THAT(col0, ElementsAreArray(mat44.col(0).elems(), 4));
    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    EXPECT_THAT(col1, ElementsAreArray(mat44.col1().elems(), 4));
    EXPECT_THAT(col1, ElementsAreArray(mat44.col(1).elems(), 4));
    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    EXPECT_THAT(col2, ElementsAreArray(mat44.col2().elems(), 4));
    EXPECT_THAT(col2, ElementsAreArray(mat44.col(2).elems(), 4));
    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    EXPECT_THAT(col3, ElementsAreArray(mat44.col3().elems(), 4));
    EXPECT_THAT(col3, ElementsAreArray(mat44.col(3).elems(), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    real_t elems[] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    EXPECT_THAT(elems, ElementsAreArray(mat44.elems(), 16));

    mat44_t mat44_mult;
    mat44_mult = mat44_t(
        vec4_t(10.0f, 20.0f, 30.0f, 40.0f),
        vec4_t(50.0f, 60.0f, 70.0f, 80.0f),
        vec4_t(90.0f, 100.0f, 110.0f, 120.0f),
        vec4_t(130.0f, 140.0f, 150.0f, 160.0f));

    real_t mult_elems[] = {
        10.0f, 20.0f, 30.0f, 40.0f,
        50.0f, 60.0f, 70.0f, 80.0f,
        90.0f, 100.0f, 110.0f, 120.0f,
        130.0f, 140.0f, 150.0f, 160.0f
    };

    EXPECT_THAT(mult_elems, ElementsAreArray(mat44_mult.elems(), 16));
}

TEST(as_mat, mat_row_col_mutate_mat44)
{
    using ::testing::ElementsAreArray;
    using ::testing::ElementsAre;

    mat44_t mat44;
    mat44 = mat44_t {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

#ifdef AS_COL_MAJOR
    const real_t col0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const as::vec4_t c0 = as::vec4::from_arr(col0);
    mat44.col0(c0);
    EXPECT_THAT(col0, ElementsAreArray(mat44.col0().elems(), 4));
    mat44.col(0, c0);
    EXPECT_THAT(col0, ElementsAreArray(mat44.col(0).elems(), 4));

    const real_t col1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const as::vec4_t c1 = as::vec4::from_arr(col1);
    mat44.col1(c1);
    EXPECT_THAT(col1, ElementsAreArray(mat44.col1().elems(), 4));
    mat44.col(1, c1);
    EXPECT_THAT(col1, ElementsAreArray(mat44.col(1).elems(), 4));

    const real_t col2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const as::vec4_t c2 = as::vec4::from_arr(col2);
    mat44.col2(c2);
    EXPECT_THAT(col2, ElementsAreArray(mat44.col2().elems(), 4));
    mat44.col(2, c2);
    EXPECT_THAT(col2, ElementsAreArray(mat44.col(2).elems(), 4));

    const real_t col3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const as::vec4_t c3 = as::vec4::from_arr(col3);
    mat44.col3(c3);
    EXPECT_THAT(col3, ElementsAreArray(mat44.col3().elems(), 4));
    mat44.col(3, c3);
    EXPECT_THAT(col3, ElementsAreArray(mat44.col(3).elems(), 4));

    const real_t row0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const as::vec4_t r0 = as::vec4::from_arr(row0);
    mat44.row0(r0);
    EXPECT_THAT(row0, ElementsAreArray(mat44.row0().elems(), 4));
    mat44.row(0, r0);
    EXPECT_THAT(row0, ElementsAreArray(mat44.row(0).elems(), 4));

    const real_t row1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const as::vec4_t r1 = as::vec4::from_arr(row1);
    mat44.row1(r1);
    EXPECT_THAT(row1, ElementsAreArray(mat44.row1().elems(), 4));
    mat44.row(1, r1);
    EXPECT_THAT(row1, ElementsAreArray(mat44.row(1).elems(), 4));

    const real_t row2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const as::vec4_t r2 = as::vec4::from_arr(row2);
    mat44.row2(r2);
    EXPECT_THAT(row2, ElementsAreArray(mat44.row2().elems(), 4));
    mat44.row(2, r2);
    EXPECT_THAT(row2, ElementsAreArray(mat44.row(2).elems(), 4));

    const real_t row3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const as::vec4_t r3 = as::vec4::from_arr(row3);
    mat44.row3(r3);
    EXPECT_THAT(row3, ElementsAreArray(mat44.row3().elems(), 4));
    mat44.row(3, r3);
    EXPECT_THAT(row3, ElementsAreArray(mat44.row(3).elems(), 4));
#elif defined AS_ROW_MAJOR
    const real_t row0[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const as::vec4_t c0 = as::vec4::from_arr(row0);
    mat44.row0(c0);
    EXPECT_THAT(row0, ElementsAreArray(mat44.row0().elems(), 4));
    mat44.row(0, c0);
    EXPECT_THAT(row0, ElementsAreArray(mat44.row(0).elems(), 4));

    const real_t row1[] = { 5.0f, 6.0f, 7.0f, 8.0f };
    const as::vec4_t c1 = as::vec4::from_arr(row1);
    mat44.row1(c1);
    EXPECT_THAT(row1, ElementsAreArray(mat44.row1().elems(), 4));
    mat44.row(1, c1);
    EXPECT_THAT(row1, ElementsAreArray(mat44.row(1).elems(), 4));

    const real_t row2[] = { 9.0f, 10.0f, 11.0f, 12.0f };
    const as::vec4_t c2 = as::vec4::from_arr(row2);
    mat44.row2(c2);
    EXPECT_THAT(row2, ElementsAreArray(mat44.row2().elems(), 4));
    mat44.row(2, c2);
    EXPECT_THAT(row2, ElementsAreArray(mat44.row(2).elems(), 4));

    const real_t row3[] = { 13.0f, 14.0f, 15.0f, 16.0f };
    const as::vec4_t c3 = as::vec4::from_arr(row3);
    mat44.row3(c3);
    EXPECT_THAT(row3, ElementsAreArray(mat44.row3().elems(), 4));
    mat44.row(3, c3);
    EXPECT_THAT(row3, ElementsAreArray(mat44.row(3).elems(), 4));

    const real_t col0[] = { 1.0f, 5.0f, 9.0f, 13.0f };
    const as::vec4_t r0 = as::vec4::from_arr(col0);
    mat44.col0(r0);
    EXPECT_THAT(col0, ElementsAreArray(mat44.col0().elems(), 4));
    mat44.col(0, r0);
    EXPECT_THAT(col0, ElementsAreArray(mat44.col(0).elems(), 4));

    const real_t col1[] = { 2.0f, 6.0f, 10.0f, 14.0f };
    const as::vec4_t r1 = as::vec4::from_arr(col1);
    mat44.col1(r1);
    EXPECT_THAT(col1, ElementsAreArray(mat44.col1().elems(), 4));
    mat44.col(1, r1);
    EXPECT_THAT(col1, ElementsAreArray(mat44.col(1).elems(), 4));

    const real_t col2[] = { 3.0f, 7.0f, 11.0f, 15.0f };
    const as::vec4_t r2 = as::vec4::from_arr(col2);
    mat44.col2(r2);
    EXPECT_THAT(col2, ElementsAreArray(mat44.col2().elems(), 4));
    mat44.col(2, r2);
    EXPECT_THAT(col2, ElementsAreArray(mat44.col(2).elems(), 4));

    const real_t col3[] = { 4.0f, 8.0f, 12.0f, 16.0f };
    const as::vec4_t r3 = as::vec4::from_arr(col3);
    mat44.col3(r3);
    EXPECT_THAT(col3, ElementsAreArray(mat44.col3().elems(), 4));
    mat44.col(3, r3);
    EXPECT_THAT(col3, ElementsAreArray(mat44.col(3).elems(), 4));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST(as_mat, mat_mat44_from_mat33_and_vec3)
{
    using ::testing::ElementsAreArray;

    mat33_t mat33 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    vec3_t vec3 { 10.0f, 11.0f, 12.0f };

    mat44_t mat44;
    mat44 = mat44_t{ mat33, vec3 };

    const real_t mat33_and_vec3[] = {
        1.0f, 2.0f, 3.0f, 0.0f,
        4.0f, 5.0f, 6.0f, 0.0f,
        7.0f, 8.0f, 9.0f, 0.0f,
        10.0f, 11.0f, 12.0f, 1.0f
    };

    EXPECT_THAT(mat33_and_vec3, ElementsAreArray(mat44.elems(), 16));
}

template struct as::mat_t<real_t, 2, 2>;
template struct as::mat_t<real_t, 3, 3>;
template struct as::mat_t<real_t, 4, 4>;
template struct as::mat_t<real_t, 5, 5>;
