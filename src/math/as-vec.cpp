#include "as-vec.hpp"

namespace as
{
    real_t vec2_t::*vec2_t::elem[2] = { &vec2_t::x, &vec2_t::y };
    real_t vec3_t::*vec3_t::elem[3] = { &vec3_t::x, &vec3_t::y, &vec3_t::z };
    real_t vec4_t::*vec4_t::elem[4] = { &vec4_t::x, &vec4_t::y, &vec4_t::z, &vec4_t::w };
}