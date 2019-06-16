#pragma once

#include <iostream>

#include "as/as-vec.hpp"

inline void print_vec2(const as::vec2_t& v) { printf("v = x: %f, y: %f\n", v.x, v.y); }
inline void print_vec3(const as::vec3_t& v) { printf("v = x: %f, y: %f, z: %f\n", v.x, v.y, v.z); }
inline void print_vec4(const as::vec4_t& v) { printf("v = x: %f, y: %f, z: %f, w: %f\n", v.x, v.y, v.z, v.w); }
