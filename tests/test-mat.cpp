// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-math-type-ops.hpp"
#include "src/math/as-view.hpp"

// as-test
#include "as-math-output.hpp"

TEST(as_mat, constructor) {
    as::mat33_t mat33_1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    for (size_t i = 0; i < as::mat33::rows(); ++i)
    {
        printf("row: %f, %f, %f\n", mat33_1.row(i).x, mat33_1.row(i).y, mat33_1.row(i).z);
    }
    for (size_t i = 0; i < as::mat33::cols(); ++i)
    {
        printf("col: %f, %f, %f\n", mat33_1.col(i).x, mat33_1.col(i).y, mat33_1.col(i).z);
    }

    as::mat44_t mat44_1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    for (size_t i = 0; i < as::mat44::rows(); ++i)
    {
        printf("row: %f, %f, %f, %f\n", mat44_1.row(i).x, mat44_1.row(i).y, mat44_1.row(i).z, mat44_1.row(i).w);
    }
    for (size_t i = 0; i < as::mat44::cols(); ++i)
    {
        printf("col: %f, %f, %f, %f\n", mat44_1.col(i).x, mat44_1.col(i).y, mat44_1.col(i).z, mat44_1.col(i).w);
    }

    float data_33[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    as::mat33_t mat33_data = as::mat33::from_ptr(data_33);
    for (size_t i = 0; i < as::mat33::rows(); ++i)
    {
        printf("row: %f, %f, %f\n", mat33_data.row(i).x, mat33_data.row(i).y, mat33_data.row(i).z);
    }

    float data_44[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    as::mat44_t mat44_data = as::mat44::from_ptr(data_44);
    for (size_t i = 0; i < as::mat44::rows(); ++i)
    {
        printf("row: %f, %f, %f, %f\n", mat44_data.row(i).x, mat44_data.row(i).y, mat44_data.row(i).z, mat44_data.row(i).w);
    }
}

TEST(as_mat, copy_constructor) {
    as::mat_t<double, 2, 4> a(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    as::mat_t<double, 2, 4> a_copy(a);

    EXPECT_EQ(a_copy[0], 1.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[1], 2.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[2], 3.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[3], 4.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[4], 5.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[5], 6.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[6], 7.0f) << "mat copy constructor failed";
    EXPECT_EQ(a_copy[7], 8.0f) << "mat copy constructor failed";

    as::mat33_t b(as::vec3_t(1.0f, 5.0f, 10.0f), as::vec3_t(2.0f, 6.0f, 11.0f), as::vec3_t(3.0f, 7.0f, 12.0f));
    as::mat33_t b_copy(b);

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
    glm::mat4 glm_a = glm::rotate(glm::mat4(1.0f), glm::radians(100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    as::mat44_t as_a = as::mat44_t(as::mat33::rotation_x(as::deg_to_rad(100.0f)), as::vec3::zero());

    glm::mat4 glm_a_inverse = glm::inverse(glm_a);
    as::mat44_t as_a_inverse = as::mat::inverse(as_a);

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

TEST(as_mat, mat33_init) {
    {
        as::real_t data[9];
        for (size_t i = 0; i < 9; ++i) {
            data[i] = (as::real_t)(i + 1);
        }

        as::mat33_t a = as::mat33::from_ptr(data);
        for (size_t i = 0; i < 3; ++i) {
            print_vec3(a.row(i));
        }
    }

    {
        as::real_t* data_p = new as::real_t[9];
        for (size_t i = 0; i < 9; ++i) {
            data_p[i] = (as::real_t)(i + 1);
        }

        as::mat33_t p_a = as::mat33::from_ptr(data_p);
        for (size_t i = 0; i < 3; ++i) {
            print_vec3(p_a.row(i));
        }
    }
}

TEST(as_mat, col_row) {
    as::mat_t< int, 5, 5 > mat;

    for (size_t i = 0; i < 25; ++i) {
        mat[i] = (int)i;
    }
}

TEST(as_mat, mat_mult) {
    // as::mat44_t a = as::identity<as::real_t, 4>();
    as::mat44_t mat = as::mat44::identity();
    as::vec4_t vec = as::vec4::axis_w();

#ifdef AS_COL_MAJOR
    as::vec4_t result_col = mat * vec;
#elif defined AS_ROW_MAJOR
    as::vec4_t result_row = vec * mat;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

    as::mat33_t mat_rot = as::mat33::rotation_x(as::deg_to_rad(90.0f));
    as::mat44_t transform_rot = as::mat44_t(mat_rot, as::vec3::zero());

    as::vec4_t dir(0.0, 1.0f, 0.0f, 0.0f);
#ifdef AS_COL_MAJOR
    as::vec4_t result_dir_col = transform_rot * dir;
    print_vec4(result_dir_col);
    print_vec4(result_col);
#elif defined AS_ROW_MAJOR
    as::vec4_t result_dir_row = dir * transform_rot;
    print_vec4(result_dir_row);
    print_vec4(result_row);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST(as_mat, mat_proj) {
    as::mat44_t proj = as::view::perspective_gl_lh(as::deg_to_rad(60.0f), 4.0f/3.0f, 0.1f, 100.0f);
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
    using int34 = as::mat_t<int, 3, 4>;

    int34 int34_test(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);

    for (size_t i = 0; i < 12; ++i) {
        printf("%d, ", int34_test[i]);
    }
}

TEST(as_mat, mat_transform_vec) {
    as::vec3_t a_vec3{ 1.0f, 2.0f, 3.0f };
    as::mat44_t a_mat44{ as::mat44::from_mat33(as::mat33::rotation_x(as::deg_to_rad(90.0f))) };

    //as::mat_t<as::real_t, 3, 4> my_mat34;

    //as::vec3_t result = my_mat34 * a_vec3;
    //as::vec4_t result2 = my_m34 * as::vec4_t{ 0.0f, 0.0f, 0.0f, 1.0f }; // fails to compile
}

TEST(as_mat, mat_generic_vs_33_44)
{
    as::mat_t<as::real_t, 5, 5> custom_m55(
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 
        11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f, 25.0f);
    as::mat44_t m44(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

    for (size_t i = 0; i < as::mat_t<as::real_t, 5, 5>::size; ++i)
    {
        as::real_t* number = custom_m55.elems() + i;
        printf("%f, ", *number);
        printf("%f, ", custom_m55[i]);
    }

    for (size_t i = 0; i < as::mat44_t::size; ++i)
    {
        as::real_t* number = m44.elems() + i;
        printf("%f, ", *number);
        printf("%f, ", m44[i]);
    }
}