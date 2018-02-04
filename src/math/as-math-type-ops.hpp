#pragma once

#include "as-vec.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-point.hpp"
#include "as-quat.hpp"

namespace as
{

template<typename T, size_t n>
inline size_t v_size(Vec<T, n>& vec);

template<typename T, size_t n>
inline T* v_data(Vec<T, n>& vec);

template<typename T, size_t n>
inline const T* v_const_data(const Vec<T, n>& vec);

template<typename T, size_t n>
constexpr inline Vec<T, n> v_from_arr(const T(&data)[n]);

template<typename T, size_t n>
constexpr inline Vec<T, n> v_from_ptr(const T* data);

template<typename T, size_t n>
inline T v_dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline T v_length_squared(const Vec<T, n>& vec);

template<typename T, size_t n>
inline T v_length(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> v_normalize(const Vec<T, n>& vec);

template<typename T, size_t n>
inline T v_normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out);

template<typename T, size_t n>
inline bool v_equal(const Vec<T, n>& lhs, const Vec<T, n>& rhs, real epsilon = std::numeric_limits<real>::epsilon());

template<typename T, size_t n>
inline Vec<T, n> v_min(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline T v_min_elem(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> v_max(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline T v_max_elem(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> v_abs(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> v_clamp(const Vec<T, n>& vec, const Vec<T, n>& min, const Vec<T, n>& max);

template<typename T, size_t n>
inline Vec<T, n> v_saturate(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> v_lerp(T t, const Vec<T, n>& v0, const Vec<T, n>& v1);

template<typename T, size_t n>
inline Vec<T, n> v_select(const Vec<T, n>& v0, const Vec<T, n>& v1, bool select0);

constexpr inline v2 v2_axis_x() { return { 1.0f, 0.0f }; }
constexpr inline v2 v2_axis_y() { return { 0.0f, 1.0f }; }
constexpr inline v2 v2_zero() { return { 0.0f, 0.0f }; }
constexpr inline v2 v2_one() { return { 1.0f, 1.0f }; }
constexpr inline v2 v2_max() { return { REAL_MAX, REAL_MAX }; }
constexpr inline v2 v2_min() { return { REAL_MIN, REAL_MIN }; }
constexpr inline v2 v2_from_ptr(const real* data);
constexpr inline v2 v2_from_arr(const real(&data)[2]);

inline real v2_wedge(const v2& lhs, const v2& rhs);

constexpr inline v3 v3_axis_x() { return { 1.0f, 0.0f, 0.0f }; }
constexpr inline v3 v3_axis_y() { return { 0.0f, 1.0f, 0.0f }; }
constexpr inline v3 v3_axis_z() { return { 0.0f, 0.0f, 1.0f }; }
constexpr inline v3 v3_zero() { return { 0.0f, 0.0f, 0.0f }; }
constexpr inline v3 v3_one() { return { 1.0f, 1.0f, 1.0f }; }
constexpr inline v3 v3_max() { return { REAL_MAX, REAL_MAX, REAL_MAX }; }
constexpr inline v3 v3_min() { return { REAL_MIN, REAL_MIN, REAL_MIN }; }
constexpr inline v3 v3_from_ptr(const real* data);
constexpr inline v3 v3_from_arr(const real(&data)[3]);

inline v3 v3_cross(const v3& lhs, const v3& rhs);

// note: will not work if dir == +/-world_up
inline void v3_right_and_up_lh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_axis_y());

// note: will not work if dir == +/-world_up
inline void v3_right_and_up_rh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_axis_y());

constexpr inline v4 v4_axis_x() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
constexpr inline v4 v4_axis_y() { return { 0.0f, 1.0f, 0.0f, 0.0f }; }
constexpr inline v4 v4_axis_z() { return { 0.0f, 0.0f, 1.0f, 0.0f }; }
constexpr inline v4 v4_axis_w() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
constexpr inline v4 v4_zero() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
constexpr inline v4 v4_one() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
constexpr inline v4 v4_max() { return { REAL_MAX, REAL_MAX, REAL_MAX, REAL_MAX }; }
constexpr inline v4 v4_min() { return { REAL_MIN, REAL_MIN, REAL_MIN, REAL_MIN }; }
constexpr inline v4 v4_from_ptr(const real* data);
constexpr inline v4 v4_from_arr(const real(&data)[4]);

template<typename T, size_t r, size_t c>
inline T* m_data(const Mat<T, r, c>& mat);

template<typename T, size_t r, size_t c>
inline const T* m_const_data(const Mat<T, r, c>& mat);

template<typename T, size_t r, size_t c>
constexpr inline Mat<T, r, c> m_from_arr(const T(&data)[r * c]);

template<typename T, size_t r, size_t c>
constexpr inline Mat<T, r, c> m_from_ptr(const T* data);

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> m_transpose(const Mat<T, r, c>& mat);

template<typename T, size_t cr>
constexpr inline Mat<T, cr, cr> m_identity();

template<typename T, size_t cr>
inline T m_determinant(const Mat<T, cr, cr>& mat);

template<typename T, size_t cr>
inline Mat<T, cr, cr> m_inverse(const Mat<T, cr, cr>& mat);

template<typename T, size_t cr>
inline Mat<T, cr, cr> m_gj_inverse(const Mat<T, cr, cr>& mat);

constexpr inline size_t m33_rows() { return 3; }
constexpr inline size_t m33_cols() { return 3; }

constexpr inline m33 m33_identity() { return m_identity<real, 3>(); }

constexpr inline m33 m33_from_ptr(const real* data);
constexpr inline m33 m33_from_arr(const real(&data)[9]);
constexpr inline m33 m33_from_m44(const m44& transform);

constexpr inline m33 m33_axis_angle(const v3& axis, real radians);
constexpr inline m33 m33_rotation_xyz(real x, real y, real z);
constexpr inline m33 m33_rotation_zxy(real x, real y, real z);
constexpr inline m33 m33_rotation_x(real radians);
constexpr inline m33 m33_rotation_y(real radians);
constexpr inline m33 m33_rotation_z(real radians);

constexpr size_t m44_rows() { return 4; }
constexpr size_t m44_cols() { return 4; }

constexpr inline m44 m44_identity() { return m_identity<real, 4>(); }

constexpr inline m44 m44_from_ptr(const real* data);
constexpr inline m44 m44_from_arr(const real(&data)[16]);

constexpr inline m44 m44_from_v3(const v3& translation);
constexpr inline m44 m44_from_m33(const m33& rotation);
constexpr inline m44 m44_from_m33_v3(const m33& rotation, const v3& translation);

inline bool p_equal(const p2& lhs, const p2& rhs,
    real epsilon = std::numeric_limits<real>::epsilon());

inline bool p_equal(const p3& lhs, const p3& rhs,
    real epsilon = std::numeric_limits<real>::epsilon());

constexpr inline quat q_identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
constexpr inline real q_dot(const quat& a, const quat& b);
constexpr inline real q_length_squared(const quat& a);
constexpr inline quat q_conjugate(const quat& a);

inline quat q_axis_angle(const v3& axis, real radians);
inline quat q_rotation_zxy(real x, real y, real z);
inline real q_length(const quat& a);
inline quat q_normalize(const quat& a);
inline quat q_inverse(const quat& a);
inline v3 q_rotate(const quat& q, const v3& v);
inline quat q_slerp(const quat& a, const quat& b, real u);

} // namespace as

#include "as-math-type-ops.inl"