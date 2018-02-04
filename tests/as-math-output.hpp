#pragma once

#include <iostream>

#include "src/math/as-vec.hpp"

inline void print_v2(const as::v2& v) { printf("v = x: %f, y: %f\n", v.x, v.y); }
inline void print_v3(const as::v3& v) { printf("v = x: %f, y: %f, z: %f\n", v.x, v.y, v.z); }
inline void print_v4(const as::v4& v) { printf("v = x: %f, y: %f, z: %f, w: %f\n", v.x, v.y, v.z, v.w); }