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
#include "as-math-output.h"

TEST(as_mat4, inverse) {
	// glm::mat4 glm_a = glm::mat4( 1.0f, 0.0f, 0.0f, 0.0f,
	// 							 0.0f, 1.0f, 0.0f, 0.0f,
	// 							 0.0f, 0.0f, 1.0f, 0.0f,
	// 							 0.0f, 0.0f, 0.0f, 1.0f );

	// as::m44 as_a = as::make_m44( 1.0f, 0.0f, 0.0f, 0.0f,
	// 							 0.0f, 1.0f, 0.0f, 0.0f,
	// 							 0.0f, 0.0f, 1.0f, 0.0f,
	// 							 0.0f, 0.0f, 0.0f, 1.0f );

	glm::mat4 glm_a = glm::rotate( glm::mat4(1.0f), glm::radians( 100.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
	as::m44 as_a = as::m44( as::make_rotation_x( as::degToRad( 100.0f ) ), as::v3_zero );

	glm::mat4 glm_a_inverse = glm::inverse( glm_a );
	as::m44 as_a_inverse = as::inverse( as_a );

	for ( size_t i = 0; i < 10000; ++i ) {
		glm_a_inverse = glm::inverse( glm_a_inverse );
		as_a_inverse = as::inverse( as_a_inverse );
	}

	EXPECT_TRUE( as::equal( glm_a_inverse[0].x, as_a_inverse[ 0 ] ) ) << "glm: " << glm_a_inverse[0].x << " as: " << as_a_inverse[ 0 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[0].y, as_a_inverse[ 1 ] ) ) << "glm: " << glm_a_inverse[0].y << " as: " << as_a_inverse[ 1 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[0].z, as_a_inverse[ 2 ] ) ) << "glm: " << glm_a_inverse[0].z << " as: " << as_a_inverse[ 2 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[0].w, as_a_inverse[ 3 ] ) ) << "glm: " << glm_a_inverse[0].w << " as: " << as_a_inverse[ 3 ];

	EXPECT_TRUE( as::equal( glm_a_inverse[1].x, as_a_inverse[ 4 ] ) ) << "glm: " << glm_a_inverse[1].x << " as: " << as_a_inverse[ 4 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[1].y, as_a_inverse[ 5 ] ) ) << "glm: " << glm_a_inverse[1].y << " as: " << as_a_inverse[ 5 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[1].z, as_a_inverse[ 6 ] ) ) << "glm: " << glm_a_inverse[1].z << " as: " << as_a_inverse[ 6 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[1].w, as_a_inverse[ 7 ] ) ) << "glm: " << glm_a_inverse[1].w << " as: " << as_a_inverse[ 7 ];

	EXPECT_TRUE( as::equal( glm_a_inverse[2].x, as_a_inverse[ 8 ] ) )  << "glm: " << glm_a_inverse[2].x << " as: " << as_a_inverse[ 8 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[2].y, as_a_inverse[ 9 ] ) )  << "glm: " << glm_a_inverse[2].y << " as: " << as_a_inverse[ 9 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[2].z, as_a_inverse[ 10 ] ) ) << "glm: " << glm_a_inverse[2].z << " as: " << as_a_inverse[ 10 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[2].w, as_a_inverse[ 11 ] ) ) << "glm: " << glm_a_inverse[2].w << " as: " << as_a_inverse[ 11 ];

	EXPECT_TRUE( as::equal( glm_a_inverse[3].x, as_a_inverse[ 12 ] ) ) << "glm: " << glm_a_inverse[3].x << " as: " << as_a_inverse[ 12 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[3].y, as_a_inverse[ 13 ] ) ) << "glm: " << glm_a_inverse[3].y << " as: " << as_a_inverse[ 13 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[3].z, as_a_inverse[ 14 ] ) ) << "glm: " << glm_a_inverse[3].z << " as: " << as_a_inverse[ 14 ];
	EXPECT_TRUE( as::equal( glm_a_inverse[3].w, as_a_inverse[ 15 ] ) ) << "glm: " << glm_a_inverse[3].w << " as: " << as_a_inverse[ 15 ];
}

TEST(as_mat, m33_init) {
	{
		real data[9];
		for ( size_t i = 0; i < 9; ++i ) {
			data[ i ] = (real)(i + 1);
		}

		as::m33 a(data);
		for ( size_t i = 0; i < 3; ++i ) {
			print_v3(a.v[i]);
		}
	}

	{
		real* data_p = new real[9];
		for ( size_t i = 0; i < 9; ++i ) {
			data_p[ i ] = (real)(i + 1);
		}

		as::m33 p_a(data_p);
		for ( size_t i = 0; i < 3; ++i ) {
			print_v3(p_a.v[i]);
		}
	}
}

TEST(as_mat, col_row) {
	as::Mat< int, 5, 5 > mat;

	for (size_t i = 0; i < 25; ++i) {
		mat[i] = i;
	}

	printf("%d ", mat.data_cr[0][0]);
	printf("%d ", mat.data_cr[0][1]);
	printf("%d ", mat.data_cr[0][2]);
	printf("%d ", mat.data_cr[0][3]);
	printf("%d ", mat.data_cr[0][4]);

	printf("\n");

	printf("%d ", mat.vec[0][0]);
	printf("%d ", mat.vec[0][1]);
	printf("%d ", mat.vec[0][2]);
	printf("%d ", mat.vec[0][3]);
	printf("%d ", mat.vec[0][4]);

	printf("\n");
}

TEST(as_mat, mat_mult) {
	// as::m44 a = as::identity<real, 4>();
	as::m44 mat = as::m44_id;
	as::v4 vec = as::v4_w;

	as::v4 result_col = mat * vec;
	/// as::v4 result_row = vec * mat;

	as::m33 mat_rot = as::make_rotation_x(as::degToRad(90.0f));
	as::m44 transform_rot = as::m44( mat_rot, as::v3_zero );

	as::v4 dir(0.0, 1.0f, 0.0f, 0.0f);
	as::v4 result_dir_col = transform_rot * dir;
	// as::v4 result_dir_row = dir * transform_rot;

	print_v4( result_dir_col );
	// print_v4( result_dir_row );

	print_v4( result_col );
	// print_v4( result_row );
}

TEST(as_mat, mat_proj) {
	as::m44 proj = as::make_perspective_gl_lh(as::degToRad(60.0f), 4.0f/3.0f, 0.1f, 100.0f);
	for (size_t i = 0; i < 16; ++i) {
		printf("proj[%zu]: %f, ", i, proj[i]);
	}

	glm::mat4 glm_proj = glm::perspective(as::degToRad(60.0f), 4.0f/3.0f, 0.1f, 100.0f);
	const float* glm_data = (const float*)glm::value_ptr(glm_proj);
	for (size_t i = 0; i < 16; ++i) {
		printf("glm proj[%zu]: %f, ", i, glm_data[i]);
	}
}

TEST(as_mat, mat_generic_init) {
	using int34 = as::Mat<int, 3, 4>;

	int34 int34_test(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);

	for (size_t i = 0; i < 12; ++i) {
		printf("%d, ", int34_test[i]);
	}
}