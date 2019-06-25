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

    const real_t arr[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
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
