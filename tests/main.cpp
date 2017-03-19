#include "gtest/gtest.h"
#include "glm/glm.hpp"

#include "src/math/as-linear-transform.h"
#include "src/math/as-mat.h"
#include "src/math/as-mat3.h"
#include "src/math/as-mat4.h"
#include "src/math/as-math.h"
#include "src/math/as-quat.h"
#include "src/math/as-vec.h"

TEST(as_vec, initialisation) {
	as::v3 v = as::make_v3(0.0f, 0.0f, 0.0f);
	
	EXPECT_EQ(v.x, 0.0f) << "v.x is not equal to zero";
	EXPECT_EQ(v.y, 0.0f) << "v.y is not equal to zero";
	EXPECT_EQ(v.z, 0.0f) << "v.z is not equal to zero";

	EXPECT_TRUE(as::equal(0.0f, v.x)) << "v is not equal to v3_zero";
}

TEST(as_vec, cross) {
	glm::vec3 glm_a = glm::vec3( 1.0f, 2.0f, 3.0f );
	glm::vec3 glm_b = glm::vec3( 4.0f, 3.0f, 2.0f );

	glm::vec3 glm_ab_result = glm::cross( glm_a, glm_b );

	as::v3 as_a = as::make_v3( 1.0f, 2.0f, 3.0f );
	as::v3 as_b = as::make_v3( 4.0f, 3.0f, 2.0f );

	as::v3 as_ab_result = as::cross( as_a, as_b );

	EXPECT_TRUE( as::equal( as_ab_result.x, glm_ab_result.x ) );
	EXPECT_TRUE( as::equal( as_ab_result.y, glm_ab_result.y ) );
	EXPECT_TRUE( as::equal( as_ab_result.z, glm_ab_result.z ) );
}

TEST(as_mat4, inverse) {
	glm::mat4 glm_a = glm::mat4( 1.0f, 0.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f );

	as::m44 as_a = as::make_m44( 1.0f, 0.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f );

	glm::mat4 glm_a_inverse = glm::inverse( glm_a );
	as::m44 as_a_inverse = as::inverse( as_a );

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

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}