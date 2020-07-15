#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat3_t;
using as::mat4_t;
using as::point3_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace affine = as::affine;
namespace mat = as::mat;
namespace mat3 = as::mat3;
namespace mat4 = as::mat4;
namespace point = as::point;
namespace vec = as::vec;
namespace vec3 = as::vec3;

// use float epsilon for comparisons
const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("affine_constructor_position_rotation", "[as_affine]")
{
    affine_t affine;
    mat3_t rotation = mat3::rotation_x(deg_to_rad(90.0_r));
    point3_t position = point3_t{0.0_r, 2.0_r, 2.0_r};
    affine = affine_t(rotation, position);

    CHECK(as::point::equal(position, affine.position));
    CHECK(as::mat::equal(rotation, affine.rotation));
}

TEST_CASE("affine_constructor_position", "[as_affine]")
{
    affine_t affine;
    affine = affine_t(as::point3_t{1.0_r, 2.0_r, 3.0_r});

    CHECK_THAT(arr(1.0_r, 2.0_r, 3.0_r), make_elements_sub(affine.position, 3));
    CHECK(as::mat::equal(as::mat3_t::identity(), affine.rotation));
}

TEST_CASE("affine_transform_dir", "[as_affine]")
{
    const affine_t affine{
        mat3::rotation_y(deg_to_rad(90.0_r)), point3_t{5.0_r, 0.0_r, 0.0_r}};

    const vec3_t result =
        affine::transform_dir(affine, vec3_t{1.0_r, 0.0_r, 0.0_r});

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3_t::identity(), point3_t{5.0_r, 0.0_r, 0.0_r});

        const point3_t result =
            affine::inv_transform_pos(affine, point3_t{6.0_r, 0.0_r, 0.0_r});

        CHECK(result.as_vec3().x == Approx(1.0_r).margin(g_epsilon));
        CHECK(result.as_vec3().y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.as_vec3().z == Approx(0.0_r).margin(g_epsilon));
    }

    {
        const affine_t affine = affine_t(
            mat3::rotation_z(deg_to_rad(90.0_r)),
            point3_t{0.0_r, 10.0_r, 0.0_r});

        const point3_t result =
            affine::inv_transform_pos(affine, point3_t{5.0_r, 0.0_r, 0.0_r});

        CHECK(result.as_vec3().x == Approx(-10.0_r).margin(g_epsilon));
        CHECK(result.as_vec3().y == Approx(-5.0_r).margin(g_epsilon));
        CHECK(result.as_vec3().z == Approx(0.0_r).margin(g_epsilon));
    }
}

TEST_CASE("affine_transform_pos", "[as_affine]")
{
    const affine_t affine = affine_t(
        mat3::rotation_y(deg_to_rad(90.0_r)), point3_t{5.0_r, 0.0_r, 0.0_r});

    const point3_t result =
        affine::transform_pos(affine, point3_t{1.0_r, 0.0_r, 0.0_r});

    CHECK(result.as_vec3().x == Approx(5.0_r).margin(g_epsilon));
    CHECK(result.as_vec3().y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.as_vec3().z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3_t::identity(), point3_t{5.0_r, 0.0_r, 0.0_r});

        const vec3_t result =
            affine::inv_transform_dir(affine, vec3_t{6.0_r, 0.0_r, 0.0_r});

        CHECK(result.x == Approx(6.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
        const affine_t affine = affine_t(
            mat3::rotation_z(deg_to_rad(90.0_r)),
            point3_t{0.0_r, 10.0_r, 0.0_r});

        const vec3_t result =
            affine::inv_transform_dir(affine, vec3_t{5.0_r, 0.0_r, 0.0_r});

        const real_t local_epsilon = 1.0e-6_r;
        CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
        CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
    }
}

TEST_CASE("affine_to_arr", "[as_affine]")
{
    using gsl::make_span;

    affine_t affine{
        mat3_t{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r, 8.0_r, 9.0_r},
        point3_t{10.0f, 20.0f, 30.0f}};

    real_t expected_affine[12];
    affine::to_arr(affine, expected_affine);

    CHECK_THAT(
        make_span(expected_affine, 9), make_elements_sub(affine.rotation, 9));
    CHECK_THAT(
        make_span(&expected_affine[9], 3),
        make_elements_sub(affine.position.as_vec3(), 3));
}

TEST_CASE("affine_from_arr", "[as_affine]")
{
    using gsl::make_span;

    real_t affine_arr[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r,
                           7.0_r, 8.0_r, 9.0_r, 10.0f, 20.0f, 30.0f};

    affine_t affine;
    affine = affine::from_arr(affine_arr);

    CHECK_THAT(make_span(affine_arr, 9), make_elements_sub(affine.rotation, 9));
    CHECK_THAT(
        make_span(&affine_arr[9], 3),
        make_elements_sub(affine.position.as_vec3(), 3));
}

TEST_CASE("affine_from_mat3", "[as_affine]")
{
    using gsl::make_span;

    as::mat3_t mat3{10.0_r, 20.0_r, 30.0_r, 40.0_r, 50.0_r,
                    60.0_r, 70.0_r, 80.0_r, 90.0_r};

    affine_t affine;
    affine = affine::from_mat3(mat3);

    CHECK(mat::equal(mat3, affine.rotation));
    CHECK_THAT(arr(0.0_r, 0.0_r, 0.0_r), make_elements_sub(affine.position, 3));
}

TEST_CASE("affine_from_point3", "[as_affine]")
{
    using gsl::make_span;

    as::point3_t point3{5.0_r, 10.0_r, 15.0_r};

    affine_t affine;
    affine = affine::from_point3(point3);

    CHECK(mat::equal(mat3_t::identity(), affine.rotation));
    CHECK_THAT(
        arr(5.0_r, 10.0_r, 15.0_r), make_elements_sub(affine.position, 3));
}

TEST_CASE("affine_concatenation", "[as_affine]")
{
    using gsl::make_span;

    mat4_t mat_a = mat4::from_mat3_vec3(
        mat3::rotation_x(deg_to_rad(45.0_r)), vec3_t::axis_x(5.0_r));

    mat4_t mat_b = mat4::from_mat3_vec3(
        mat3::rotation_y(deg_to_rad(90.0_r)), vec3_t::axis_y(10.0_r));

    mat4_t mat_c = mat4::from_mat3_vec3(
        mat3::rotation_y(deg_to_rad(180.0_r)), vec3_t::axis_z(20.0_r));

    mat4_t mat_result;
    mat_result = mat::mul(mat::mul(mat_a, mat_b), mat_c);

    affine_t affine_a = affine::from_mat4(mat_a);
    affine_t affine_b = affine::from_mat4(mat_b);
    affine_t affine_c = affine::from_mat4(mat_c);

    affine_t affine_result;
    affine_result = affine::mul(affine::mul(affine_a, affine_b), affine_c);

    real_t expected_orientation[9];
    mat::to_arr(affine_result.rotation, expected_orientation);

    real_t expected_position[3];
    vec::to_arr(affine_result.position.as_vec3(), expected_position);

    CHECK_THAT(
        make_span(expected_orientation),
        make_elements_sub(mat3::from_mat4(mat_result), 9));

    CHECK_THAT(
        make_span(expected_position),
        make_elements_sub(vec3::from_vec4(mat4::translation(mat_result)), 3));
}

TEST_CASE("affine_inverse", "[as_affine]")
{
    using gsl::make_span;

    const affine_t affine{
        mat3::rotation_y(deg_to_rad(90.0_r)), point3_t{5.0_r, 10.0_r, 20.0_r}};

    const affine_t affine_expected_inverse{
        mat3::rotation_y(deg_to_rad(-90.0_r)),
        point3_t{20.0_r, -10.0_r, -5.0_r}};

    real_t expected_affine[12];
    affine::to_arr(affine_expected_inverse, expected_affine);

    affine_t result;
    result = as::affine::inverse(affine);

    CHECK_THAT(
        make_span(expected_affine, 9), make_elements_sub(result.rotation, 9));
    CHECK_THAT(
        make_span(&expected_affine[9], 3),
        make_elements_sub(result.position.as_vec3(), 3).margin(0.000001_r));
}

} // namespace unit_test
