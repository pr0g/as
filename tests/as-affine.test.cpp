#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

using namespace as;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("affine_constructor", "[as_affine]")
{
    affine_t affine;
    mat3_t rotation = mat3::rotation_x(deg_to_rad(90.0f));
    vec3_t position = vec3_t{ 0.0f, 2.0f, 2.0f};
    affine = affine_t(rotation, position);

    CHECK(affine.position.x == Approx(position.x).margin(g_epsilon));
    CHECK(affine.position.y == Approx(position.y).margin(g_epsilon));
    CHECK(affine.position.z == Approx(position.z).margin(g_epsilon));
}

TEST_CASE("affine_multiply", "[as_affine]")
{

}

TEST_CASE("affine_transform_dir", "[as_affine]")
{

}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{

}

TEST_CASE("affine_transform_pos", "[as_affine]")
{

}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{

}
