// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-mat.hpp"
#include "src/math/as-mat3.hpp"
#include "src/math/as-mat4.hpp"

// as-test
#include "as-math-output.hpp"

TEST(as_mat, constructor) {
    as::m33 m33_1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    for (size_t i = 0; i < m33_1.rows(); ++i)
    {
        printf("row: %f, %f, %f\n", m33_1.row(i).x, m33_1.row(i).y, m33_1.row(i).z);
    }
    for (size_t i = 0; i < m33_1.cols(); ++i)
    {
        printf("col: %f, %f, %f\n", m33_1.col(i).x, m33_1.col(i).y, m33_1.col(i).z);
    }

    as::m44 m44_1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    for (size_t i = 0; i < m44_1.rows(); ++i)
    {
        printf("row: %f, %f, %f, %f\n", m44_1.row(i).x, m44_1.row(i).y, m44_1.row(i).z, m44_1.row(i).w);
    }
    for (size_t i = 0; i < m44_1.cols(); ++i)
    {
        printf("col: %f, %f, %f, %f\n", m44_1.col(i).x, m44_1.col(i).y, m44_1.col(i).z, m44_1.col(i).w);
    }

    float data_33[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    as::m33 m33_data = as::make_m33_from(data_33);
    for (size_t i = 0; i < m33_data.rows(); ++i)
    {
        printf("row: %f, %f, %f\n", m33_data.row(i).x, m33_data.row(i).y, m33_data.row(i).z);
    }

    float data_44[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    as::m44 m44_data = as::make_m44_from(data_44);
    for (size_t i = 0; i < m44_data.rows(); ++i)
    {
        printf("row: %f, %f, %f, %f\n", m44_data.row(i).x, m44_data.row(i).y, m44_data.row(i).z, m44_data.row(i).w);
    }
}

TEST(as_mat, copy_constructor) {
    as::mat::Mat<double, 2, 4> a(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    as::mat::Mat<double, 2, 4> a_copy(a);

    EXPECT_EQ(a_copy[0], 1.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[1], 2.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[2], 3.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[3], 4.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[4], 5.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[5], 6.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[6], 7.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[7], 8.0f) << "mat copy constructor failed";

    as::m33 b(as::v3(1.0f, 5.0f, 10.0f), as::v3(2.0f, 6.0f, 11.0f), as::v3(3.0f, 7.0f, 12.0f));
    as::m33 b_copy(b);

    EXPECT_EQ(b_copy[0], 1.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[1], 5.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[2], 10.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[3], 2.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[4], 6.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[5], 11.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[6], 3.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[7], 7.0f) << "mat copy constructor failed";
    EXPECT_EQ(b_copy[8], 12.0f) << "mat copy constructor failed";
}

TEST(as_mat4, inverse) {
    // glm::mat4 glm_a = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
    // 							 0.0f, 1.0f, 0.0f, 0.0f,
    // 							 0.0f, 0.0f, 1.0f, 0.0f,
    // 							 0.0f, 0.0f, 0.0f, 1.0f);

    // as::m44 as_a = as::make_m44(1.0f, 0.0f, 0.0f, 0.0f,
    // 							 0.0f, 1.0f, 0.0f, 0.0f,
    // 							 0.0f, 0.0f, 1.0f, 0.0f,
    // 							 0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 glm_a = glm::rotate(glm::mat4(1.0f), glm::radians(100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    as::m44 as_a = as::m44(as::make_rotation_x(as::deg_to_rad(100.0f)), as::v3::zero());

    glm::mat4 glm_a_inverse = glm::inverse(glm_a);
    as::m44 as_a_inverse = as::mat::inverse(as_a);

    for (size_t i = 0; i < 10000; ++i) {
        glm_a_inverse = glm::inverse(glm_a_inverse);
        as_a_inverse = as::mat::inverse(as_a_inverse);
    }

    EXPECT_TRUE(as::equal(glm_a_inverse[0].x, as_a_inverse[0])) << "glm: " << glm_a_inverse[0].x << " as: " << as_a_inverse[0];
    EXPECT_TRUE(as::equal(glm_a_inverse[0].y, as_a_inverse[1])) << "glm: " << glm_a_inverse[0].y << " as: " << as_a_inverse[1];
    EXPECT_TRUE(as::equal(glm_a_inverse[0].z, as_a_inverse[2])) << "glm: " << glm_a_inverse[0].z << " as: " << as_a_inverse[2];
    EXPECT_TRUE(as::equal(glm_a_inverse[0].w, as_a_inverse[3])) << "glm: " << glm_a_inverse[0].w << " as: " << as_a_inverse[3];

    EXPECT_TRUE(as::equal(glm_a_inverse[1].x, as_a_inverse[4])) << "glm: " << glm_a_inverse[1].x << " as: " << as_a_inverse[4];
    EXPECT_TRUE(as::equal(glm_a_inverse[1].y, as_a_inverse[5])) << "glm: " << glm_a_inverse[1].y << " as: " << as_a_inverse[5];
    EXPECT_TRUE(as::equal(glm_a_inverse[1].z, as_a_inverse[6])) << "glm: " << glm_a_inverse[1].z << " as: " << as_a_inverse[6];
    EXPECT_TRUE(as::equal(glm_a_inverse[1].w, as_a_inverse[7])) << "glm: " << glm_a_inverse[1].w << " as: " << as_a_inverse[7];

    EXPECT_TRUE(as::equal(glm_a_inverse[2].x, as_a_inverse[8]))  << "glm: " << glm_a_inverse[2].x << " as: " << as_a_inverse[8];
    EXPECT_TRUE(as::equal(glm_a_inverse[2].y, as_a_inverse[9]))  << "glm: " << glm_a_inverse[2].y << " as: " << as_a_inverse[9];
    EXPECT_TRUE(as::equal(glm_a_inverse[2].z, as_a_inverse[10])) << "glm: " << glm_a_inverse[2].z << " as: " << as_a_inverse[10];
    EXPECT_TRUE(as::equal(glm_a_inverse[2].w, as_a_inverse[11])) << "glm: " << glm_a_inverse[2].w << " as: " << as_a_inverse[11];

    EXPECT_TRUE(as::equal(glm_a_inverse[3].x, as_a_inverse[12])) << "glm: " << glm_a_inverse[3].x << " as: " << as_a_inverse[12];
    EXPECT_TRUE(as::equal(glm_a_inverse[3].y, as_a_inverse[13])) << "glm: " << glm_a_inverse[3].y << " as: " << as_a_inverse[13];
    EXPECT_TRUE(as::equal(glm_a_inverse[3].z, as_a_inverse[14])) << "glm: " << glm_a_inverse[3].z << " as: " << as_a_inverse[14];
    EXPECT_TRUE(as::equal(glm_a_inverse[3].w, as_a_inverse[15])) << "glm: " << glm_a_inverse[3].w << " as: " << as_a_inverse[15];
}

TEST(as_mat, m33_init) {
    {
        as::real data[9];
        for (size_t i = 0; i < 9; ++i) {
            data[i] = (as::real)(i + 1);
        }

        as::m33 a = as::make_m33_from(data);
        for (size_t i = 0; i < 3; ++i) {
            print_v3(a.row(i));
        }
    }

    {
        as::real* data_p = new as::real[9];
        for (size_t i = 0; i < 9; ++i) {
            data_p[i] = (as::real)(i + 1);
        }

        as::m33 p_a = as::make_m33_from(data_p);
        for (size_t i = 0; i < 3; ++i) {
            print_v3(p_a.row(i));
        }
    }
}

TEST(as_mat, col_row) {
    as::mat::Mat< int, 5, 5 > mat;

    for (size_t i = 0; i < 25; ++i) {
        mat[i] = (int)i;
    }

    printf("%d ", mat.elem_rc[0][0]);
    printf("%d ", mat.elem_rc[0][1]);
    printf("%d ", mat.elem_rc[0][2]);
    printf("%d ", mat.elem_rc[0][3]);
    printf("%d ", mat.elem_rc[0][4]);

    printf("\n");

    printf("%d ", mat.vec[0][0]);
    printf("%d ", mat.vec[0][1]);
    printf("%d ", mat.vec[0][2]);
    printf("%d ", mat.vec[0][3]);
    printf("%d ", mat.vec[0][4]);

    printf("\n");
}

TEST(as_mat, mat_mult) {
    // as::m44 a = as::identity<as::real, 4>();
    as::m44 mat = as::m44_id;
    as::v4 vec = as::v4::axis_w();

#ifdef AS_COL_MAJOR
    as::v4 result_col = mat * vec;
#elif defined AS_ROW_MAJOR
    as::v4 result_row = vec * mat;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    as::m33 mat_rot = as::make_rotation_x(as::deg_to_rad(90.0f));
    as::m44 transform_rot = as::m44(mat_rot, as::v3::zero());

    as::v4 dir(0.0, 1.0f, 0.0f, 0.0f);
#ifdef AS_COL_MAJOR
    as::v4 result_dir_col = transform_rot * dir;
    print_v4(result_dir_col);
    print_v4(result_col);
#elif defined AS_ROW_MAJOR
    as::v4 result_dir_row = dir * transform_rot;
    print_v4(result_dir_row);
    print_v4(result_row);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST(as_mat, mat_proj) {
    as::m44 proj = as::make_perspective_gl_lh(as::deg_to_rad(60.0f), 4.0f/3.0f, 0.1f, 100.0f);
    for (size_t i = 0; i < 16; ++i) {
        printf("proj[%d]: %f, ", static_cast<int>(i), proj[i]);
    }

    glm::mat4 glm_proj = glm::perspective(as::deg_to_rad(60.0f), 4.0f/3.0f, 0.1f, 100.0f);
    const float* glm_data = (const float*)glm::value_ptr(glm_proj);
    for (size_t i = 0; i < 16; ++i) {
        printf("glm proj[%d]: %f, ", static_cast<int>(i), glm_data[i]);
    }
}

TEST(as_mat, mat_generic_init) {
    using int34 = as::mat::Mat<int, 3, 4>;

    int34 int34_test(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);

    for (size_t i = 0; i < 12; ++i) {
        printf("%d, ", int34_test[i]);
    }
}