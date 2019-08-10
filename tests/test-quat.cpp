#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

TEST_CASE("quat_identity", "[as_quat]")
{
    {
        as::quat_t q;
        q = as::quat::identity();
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }

    {
        as::quat_t q;
        q = as::quat_t(1.0f, as::vec3::zero());
        CHECK(q.x == 0.0f);
        CHECK(q.y == 0.0f);
        CHECK(q.z == 0.0f);
        CHECK(q.w == 1.0f);
    }
}
