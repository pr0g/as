#include "gtest/gtest.h"

#include "src/math/as-linear-transform.h"
#include "src/math/as-mat.h"
#include "src/math/as-mat3.h"
#include "src/math/as-mat4.h"
#include "src/math/as-math.h"
#include "src/math/as-quat.h"
#include "src/math/as-vec.h"

TEST(as_vec_test, initialisation) {
	as::v3 v = as::make_v3(0.0f, 0.0f, 0.0f);
	EXPECT_EQ(v.x, 0.0f);
	EXPECT_EQ(v.y, 0.0f);
	EXPECT_EQ(v.z, 0.0f);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}