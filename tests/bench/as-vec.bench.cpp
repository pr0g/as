#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

using namespace as;

TEST_CASE("as-vec-dot", "[as-vec]")
{
    BENCHMARK("as-vec")
    {
        return as::vec::dot(as::vec3_t{1.0f, 2.0f, 3.0f}, as::vec3_t{5.0f, 6.0f, 7.0f});
    };
}
