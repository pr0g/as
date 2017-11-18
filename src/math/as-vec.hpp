#pragma once

#include <algorithm>
#include <type_traits>

#include "core/as-types.hpp"
#include "core/as-assert.hpp"

#include "as-math.hpp"

namespace as
{

template<typename T, size_t n>
struct Vec
{
    T elem[n];
    static const size_t size = n;

    constexpr T& operator[](size_t i) { return elem[i]; }
    constexpr const T& operator[](size_t i) const { return elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<Vec>, typelist<std::decay_t<Args>...>>::value>>
    Vec(Args... args) noexcept : elem{ std::forward<Args>(args)... } {}
};

template<>
struct Vec<real, 2>
{
    union
    {
        real elem[2];
        struct { real x; real y; };
    };

    static const size_t size = 2;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    explicit Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xy) : x(xy), y(xy) {}
    constexpr explicit Vec(real x, real y) : x(x), y(y) {}
};

using v2 = Vec<real, 2>;

template<>
struct Vec<real, 3>
{
    union
    {
        real elem[3];
        struct { real x; real y; real z; };
    };

    static const size_t size = 3;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    explicit Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr explicit Vec(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
    constexpr explicit Vec(real x, real y, real z) : x(x), y(y), z(z) {}

    v2 xy() const { return v2(x, y); }
};

using v3 = Vec<real, 3>;

template<>
struct Vec<real, 4>
{
    union
    {
        real elem[4];
        struct { real x; real y; real z; real w; };
    };

    static const size_t size = 4;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    explicit Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr explicit Vec(const v3& xyz, real w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr explicit Vec(const v2& xy, real z, real w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr explicit Vec(const v2& xy, const v2& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr explicit Vec(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}

    v2 xy() const { return v2(x, y); }
    v2 zw() const { return v2(z, w); }
    v3 xyz() const { return v3(x, y, z); }
};

using v4 = Vec<real, 4>;

template<typename T, size_t n>
AS_INLINE size_t size(Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE T* data(Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE const T* const_data(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> make_vec_from_arr(const T(&data)[n]);

template<typename T, size_t n>
AS_INLINE Vec<T, n> make_vec_from_ptr(const T* data);

AS_INLINE v2 make_v2_from_ptr(const real* data);
AS_INLINE v2 make_v2_from_arr(const real(&data)[2]);

AS_INLINE v3 make_v3_from_ptr(const real* data);
AS_INLINE v3 make_v3_from_arr(const real(&data)[3]);

AS_INLINE v4 make_v4_from_ptr(const real* data);
AS_INLINE v4 make_v4_from_arr(const real(&data)[4]);

template<typename T, size_t n>
AS_INLINE T dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE T length_squared(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE T length(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> normalize(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE T normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator-(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator*(const Vec<T, n>& vec, T val);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator*(T val, const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE void operator*=(Vec<T, n>& vec, T val);

template<typename T, size_t n>
AS_INLINE Vec<T, n> operator/(const Vec<T, n>& vec, T val);

template<typename T, size_t n>
AS_INLINE void operator/=(Vec<T, n>& vec, T val);

template<typename T, size_t n>
AS_INLINE bool equal(const Vec<T, n>& lhs, const Vec<T, n>& rhs, real epsilon = std::numeric_limits<real>::epsilon());

template<typename T, size_t n>
AS_INLINE Vec<T, n> min(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE T min_elem(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> max(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
AS_INLINE T max_elem(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> abs(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> clamp(const Vec<T, n>& vec, const Vec<T, n>& min, const Vec<T, n>& max);

template<typename T, size_t n>
AS_INLINE Vec<T, n> saturate(const Vec<T, n>& vec);

template<typename T, size_t n>
AS_INLINE Vec<T, n> lerp(T t, const Vec<T, n>& v0, const Vec<T, n>& v1);

template<typename T, size_t n>
AS_INLINE Vec<T, n> select(const Vec<T, n>& v0, const Vec<T, n>& v1, bool select0);

// constants

const v2 v2_x(1.0f, 0.0f);
const v2 v2_y(0.0f, 1.0f);
const v2 v2_zero(0.0f, 0.0f);
const v2 v2_one(1.0f, 1.0f);
const v2 v2_max(REAL_MAX, REAL_MAX);
const v2 v2_min(REAL_MIN, REAL_MIN);

const v3 v3_x(1.0f, 0.0f, 0.0f);
const v3 v3_y(0.0f, 1.0f, 0.0f);
const v3 v3_z(0.0f, 0.0f, 1.0f);
const v3 v3_zero(0.0f, 0.0f, 0.0f);
const v3 v3_one(1.0f, 1.0f, 1.0f);
const v3 v3_max(REAL_MAX, REAL_MAX, REAL_MAX);
const v3 v3_min(REAL_MIN, REAL_MIN, REAL_MIN);

const v4 v4_x(1.0f, 0.0f, 0.0f, 0.0f);
const v4 v4_y(0.0f, 1.0f, 0.0f, 0.0f);
const v4 v4_z(0.0f, 0.0f, 1.0f, 0.0f);
const v4 v4_w(0.0f, 0.0f, 0.0f, 1.0f);
const v4 v4_zero(0.0f, 0.0f, 0.0f, 0.0f);
const v4 v4_one(1.0f, 1.0f, 1.0f, 1.0f);
const v4 v4_max(REAL_MAX, REAL_MAX, REAL_MAX, REAL_MAX);
const v4 v4_min(REAL_MIN, REAL_MIN, REAL_MIN, REAL_MIN);

AS_INLINE v3 cross(const v3& lhs, const v3& rhs);

// note: will not work if dir == +/-world_up
AS_INLINE void right_and_up_lh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_y);

// note: will not work if dir == +/-world_up
AS_INLINE void right_and_up_rh(const v3& dir, v3& across, v3& up, const v3& world_up = v3_y);

}

#include "as-vec.inl"