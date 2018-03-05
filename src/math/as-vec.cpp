#include "as-vec.hpp"

namespace as
{
    as::real_t as::vec2_t::*as::vec2_t::elem[2] = { &vec2_t::x, &vec2_t::y };
    as::real_t as::vec3_t::*as::vec3_t::elem[3] = { &vec3_t::x, &vec3_t::y, &vec3_t::z };
    as::real_t as::vec4_t::*as::vec4_t::elem[4] = { &vec4_t::x, &vec4_t::y, &vec4_t::z, &vec4_t::w };
}