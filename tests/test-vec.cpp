// gtest
#include "gtest/gtest.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// as
#include "src/math/as-linear-transform.hpp"
#include "src/math/as-math.hpp"
#include "src/math/as-vec.hpp"

// as-test
#include "as-math-output.hpp"

TEST(as_vec, initialisation) {
	as::v3 v = as::v3(0.0f, 0.0f, 0.0f);
	
	EXPECT_EQ(v.x, 0.0f) << "v.x is not equal to zero";
	EXPECT_EQ(v.y, 0.0f) << "v.y is not equal to zero";
	EXPECT_EQ(v.z, 0.0f) << "v.z is not equal to zero";

	EXPECT_TRUE(as::equal(0.0f, v.x)) << "v is not equal to v3_zero";
}

TEST(as_vec, cross) {
	glm::vec3 glm_a = glm::vec3( 1.0f, 2.0f, 3.0f );
	glm::vec3 glm_b = glm::vec3( 4.0f, 3.0f, 2.0f );

	glm::vec3 glm_ab_result = glm::cross( glm_a, glm_b );

	as::v3 as_a = as::v3( 1.0f, 2.0f, 3.0f );
	as::v3 as_b = as::v3( 4.0f, 3.0f, 2.0f );

	as::v3 as_ab_result = as::cross( as_a, as_b );

	EXPECT_TRUE( as::equal( as_ab_result.x, glm_ab_result.x ) );
	EXPECT_TRUE( as::equal( as_ab_result.y, glm_ab_result.y ) );
	EXPECT_TRUE( as::equal( as_ab_result.z, glm_ab_result.z ) );
}

TEST(as_vec, right_and_up) {
	as::v3 dir(0.0f, 0.0f, -1.0f);
	
	printf( "dir - x: %f, y: %f, z: %f\n", dir.x, dir.y, dir.z);

	{
		as::v3 across_lh, up_lh;
		as::right_and_up_lh(dir, across_lh, up_lh);

		printf( "right lh - x: %f, y: %f, z: %f\n", across_lh.x, across_lh.y, across_lh.z);
		printf( "up lh - x: %f, y: %f, z: %f\n", up_lh.x, up_lh.y, up_lh.z);
	}

	{
		as::v3 across_rh, up_rh;
		as::right_and_up_rh(dir, across_rh, up_rh);

		printf( "right rh - x: %f, y: %f, z: %f\n", across_rh.x, across_rh.y, across_rh.z);
		printf( "up rh - x: %f, y: %f, z: %f\n", up_rh.x, up_rh.y, up_rh.z);
	}
}

TEST(as_vec, constants) {
	// todo
}

TEST(as_vec, equal) {
	as::v3 a(1.11f, 0.3f, 517.2f);
	as::v3 b(1.11f, 0.3f, 517.2f);

	EXPECT_TRUE(equal(a, b)) << "vector equality check for equal vectors failed";

	as::v3 c(1.11f, 0.3f, 514.2f);
	as::v3 d(1.114f, 0.3f, 517.2f);

	EXPECT_FALSE(equal(a, c)) << "vector equality check for different vectors failed";
	EXPECT_FALSE(equal(a, d)) << "vector equality check for different vectors failed";
	EXPECT_FALSE(equal(b, c)) << "vector equality check for different vectors failed";
}

TEST(as_vec, init_compat) {
	glm::vec3 glm_a(1.0f, 2.0f, 3.0f);

	real data[3] = { 1.0f, 2.0f, 3.0f };
	as::v3 as_a = as::make_from(data);
	as::v3 as_b = as::make_from<float, 3>(glm::value_ptr(glm_a));
	as::v3 as_c = as::v3(as::make_from<real, 3>(as::data(as_a)));
	as::v3 as_d = as::v3(as::make_v3_from(as::data(as_a)));

	real data_v4[4] = { 5.0f, 12.0f, 100.0f, 0.999f };
	as::v4 as_v4 = as::v4(as::make_v4_from(data_v4));

	as::v4 as_v4_2 = as::v4(as::make_v4_from(as::data(as_v4)));

	print_v3( as_a );
	print_v3( as_b );
	print_v3( as_c );
	print_v3( as_d );
	print_v4( as_v4 );
	print_v4( as_v4_2 );
}

TEST(as_vec, conversions) {
	as::v4 a_v4( 1.0f, 2.0f, 3.0f, 4.0f );
	as::v2 a_v2 = a_v4.xy;

	printf("%f %f\n", a_v2.x, a_v2.y);
}

TEST(as_vec, abs) {
	as::v4 v( -1.0f, 2.0f, -100.0f, -7.0f);
	as::v4 r = abs( v );

	bool is_abs = true;
	for( size_t i = 0; i < 4; ++i ) {
		is_abs &= r[i] >= 0.0f;
	}

	EXPECT_TRUE( is_abs ) << "as::vec abs failed";
}

TEST(as_vec, min) {
	as::v4 v1( -1.0f, 2.0f, -100.0f, -7.0f);
	as::v4 v2( -10.0f, 7.0f, -50.0f, -16.0f);

	as::v4 r = min( v1, v2 );

	EXPECT_TRUE( r.x == -10.0f && r.y == 2.0f && r.z == -100.0f && r.w == -16.0f ) << "as::vec min failed";
}

TEST(as_vec, min_elem) {
	as::v4 v( -1.0f, 2.0f, -100.0f, -7.0f);
	real min = min_elem(v);

	EXPECT_TRUE(min == -100.0f) << "as::vec min_elem failed";
}

TEST(as_vec, max) {
	as::v4 v1( -1.0f, 2.0f, -100.0f, -7.0f);
	as::v4 v2( -10.0f, 7.0f, -50.0f, -16.0f);

	as::v4 r = max( v1, v2 );

	EXPECT_TRUE( r.x == -1.0f && r.y == 7.0f && r.z == -50.0f && r.w == -7.0f ) << "as::vec max failed";
}

TEST(as_vec, max_elem) {
	as::v4 v( -1.0f, 2.0f, -100.0f, -7.0f);
	real max = max_elem(v);

	EXPECT_TRUE(max == 2.0f) << "as::vec max_elem failed";
}

TEST(as_vec, clamp) {
	as::v3 min(100.0f, 50.0f, -100.0f);
	as::v3 max(200.0f, 1000.0f, -50.0f);

	as::v3 v(50.0f, 1020.0f, -75.0f);

	as::v3 result = clamp(v, min, max);

	EXPECT_TRUE(result.x == 100.0f && result.y == 1000.0f && result.z == -75.0f) << "as::vec clamp failed";
}

TEST(as_vec, saturate) {
	as::v3 v(-2.0f, 0.5f, 1.2f);

	as::v3 result = saturate(v);

	EXPECT_TRUE(result.x == 0.0f && result.y == 0.5f && result.z == 1.0f) << "as::vec saturate failed";
}

TEST(as_vec, lerp) {
	as::v3 start(0.0f, 10.0f, 20.0f);
	as::v3 end(10.0f, 40.0f, 100.0f);

	as::v3 result_begin = lerp(0.0f, start, end);
	as::v3 result_mid = lerp(0.5f, start, end);
	as::v3 result_end = lerp(1.0f, start, end);

	EXPECT_TRUE(result_begin.x == 0.0f && result_begin.y == 10.0f && result_begin.z == 20.0f) << "as::vec lerp failed";
	EXPECT_TRUE(result_mid.x == 5.0f && result_mid.y == 25.0f && result_mid.z == 60.0f) << "as::vec lerp failed";
	EXPECT_TRUE(result_end.x == 10.0f && result_end.y == 40.0f && result_end.z == 100.0f) << "as::vec lerp failed";
}

TEST(as_vec, select) {
	using int3 = as::Vec<int, 3>;

	int3 a(1, 2, 3);
	int3 b(5, 6, 7);
	
	using byte4 = as::Vec<byte, 4>;

	byte4 c((byte)255, (byte)255, (byte)255, (byte)255);
	byte4 d((byte)0, (byte)0, (byte)0, (byte)0);

	using float3 = as::Vec<float, 3>;

	float3 x(1.0f, 2.0f, 3.0f);
	float3 y(4.0f, 5.0f, 6.0f);

	int3 result = select(a, b, true);
	byte4 result_byte = select(c, d, false);

	int3 e{8, 9, 10};
	int3 f({11, 12, 13});

	printf("v = x: %d, y: %d, z: %d\n", e[0], e[1], e[2]);
	printf("v = x: %d, y: %d, z: %d\n", f[0], f[1], f[2]);

	EXPECT_TRUE(result[0] == 1 && result[1] == 2 && result[2] == 3) << "as::vec select failed";
	EXPECT_TRUE(result_byte[0] == 0 && result_byte[1] == 0 && result_byte[2] == 0 && result_byte[3] == 0) << "as::vec select failed";
}