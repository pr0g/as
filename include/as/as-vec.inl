namespace as
{

template<typename T, index_t n>
AS_API constexpr index_t vec_t<T, n>::size()
{
    return n;
}

template<typename T, index_t n>
AS_API constexpr T& vec_t<T, n>::operator[](index_t i) &
{
    return elem[i];
}

template<typename T, index_t n>
AS_API constexpr const T& vec_t<T, n>::operator[](index_t i) const&
{
    return elem[i];
}

template<typename T, index_t n>
AS_API constexpr T vec_t<T, n>::operator[](index_t i) &&
{
    return elem[i];
}

namespace internal
{

template<typename T>
AS_API constexpr index_t vec2_base_t<T>::size()
{
    return 2;
}

template<typename T>
AS_API T& vec2_base_t<T>::operator[](index_t i) &
{
    return this->*elem[i];
}

template<typename T>
AS_API const T& vec2_base_t<T>::operator[](index_t i) const&
{
    return this->*elem[i];
}

template<typename T>
AS_API const T vec2_base_t<T>::operator[](index_t i) &&
{
    return this->*elem[i];
}

template<typename T>
AS_API constexpr vec2_base_t<T>::vec2_base_t(T xy_) : x(xy_), y(xy_)
{
}

template<typename T>
AS_API constexpr vec2_base_t<T>::vec2_base_t(T x_, T y_) : x(x_), y(y_)
{
}

} // namespace internal

template<typename T>
AS_API constexpr vec_t<T, 2>::vec_t(T xy_) : internal::vec2_base_t<T>(xy_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 2>::vec_t(T x_, T y_)
    : internal::vec2_base_t<T>(x_, y_)
{
}

namespace internal
{

template<typename T>
AS_API constexpr index_t vec3_base_t<T>::size()
{
    return 3;
}

template<typename T>
AS_API T& vec3_base_t<T>::operator[](index_t i) &
{
    return this->*elem[i];
}

template<typename T>
AS_API const T& vec3_base_t<T>::operator[](index_t i) const&
{
    return this->*elem[i];
}

template<typename T>
AS_API const T vec3_base_t<T>::operator[](index_t i) &&
{
    return this->*elem[i];
}

template<typename T>
AS_API constexpr vec3_base_t<T>::vec3_base_t(T xyz_) : x(xyz_), y(xyz_), z(xyz_)
{
}

template<typename T>
AS_API constexpr vec3_base_t<T>::vec3_base_t(const vec_t<T, 2>& xy_, T z_)
    : x(xy_.x), y(xy_.y), z(z_)
{
}

template<typename T>
AS_API constexpr vec3_base_t<T>::vec3_base_t(T x_, T y_, T z_) : x(x_), y(y_), z(z_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec3_base_t<T>::xy() const
{
    return {x, y};
}

} // namespace internal

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(T xyz_) : internal::vec3_base_t<T>(xyz_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(const vec_t<T, 2>& xy_, T z_)
    : internal::vec3_base_t<T>(xy_, z_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(T x_, T y_, T z_)
    : internal::vec3_base_t<T>(x_, y_, z_)
{
}

namespace internal
{

template<typename T>
AS_API constexpr index_t vec4_base_t<T>::size()
{
    return 4;
}

template<typename T>
AS_API T& vec4_base_t<T>::operator[](index_t i) &
{
    return this->*elem[i];
}

template<typename T>
AS_API const T& vec4_base_t<T>::operator[](index_t i) const&
{
    return this->*elem[i];
}

template<typename T>
AS_API const T vec4_base_t<T>::operator[](index_t i) &&
{
    return this->*elem[i];
}

template<typename T>
AS_API constexpr vec4_base_t<T>::vec4_base_t(T xyzw_)
    : x(xyzw_), y(xyzw_), z(xyzw_), w(xyzw_)
{
}

template<typename T>
AS_API constexpr vec4_base_t<T>::vec4_base_t(const vec_t<T, 3>& xyz_, T w_)
    : x(xyz_.x), y(xyz_.y), z(xyz_.z), w(w_)
{
}

template<typename T>
AS_API constexpr vec4_base_t<T>::vec4_base_t(const vec_t<T, 2>& xy_, T z_, T w_)
    : x(xy_.x), y(xy_.y), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec4_base_t<T>::vec4_base_t(
    const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw)
    : x(xy_.x), y(xy_.y), z(zw.x), w(zw.y)
{
}

template<typename T>
AS_API constexpr vec4_base_t<T>::vec4_base_t(T x_, T y_, T z_, T w_)
    : x(x_), y(y_), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec4_base_t<T>::xy() const
{
    return {x, y};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec4_base_t<T>::zw() const
{
    return {z, w};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec4_base_t<T>::xyz() const
{
    return {x, y, z};
}

} // namespace internal

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(T xyzw_) : internal::vec4_base_t<T>(xyzw_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(const vec_t<T, 3>& xyz_, T w_)
    : internal::vec4_base_t<T>(xyz_, w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(const vec_t<T, 2>& xy_, T z_, T w_)
    : internal::vec4_base_t<T>(xy_, z_, w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw)
    : internal::vec4_base_t<T>(xy_, zw)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(T x_, T y_, T z_, T w_)
    : internal::vec4_base_t<T>(x_, y_, z_, w_)
{
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator+(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result{lhs};
    result += rhs;
    return result;
}

template<>
AS_API inline const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator-(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result{lhs};
    result -= rhs;
    return result;
}

template<>
AS_API inline const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator-(const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = -rhs[i];
    }

    return result;
}

template<>
AS_API inline const vec3_t operator-(const vec3_t& rhs)
{
    return {-rhs.x, -rhs.y, -rhs.z};
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(const vec_t<T, n>& lhs, T val)
{
    vec_t<T, n> result{lhs};
    result *= val;
    return result;
}

template<>
AS_API inline const vec3_t operator*(const vec3_t& lhs, real_t val)
{
    return {lhs.x * val, lhs.y * val, lhs.z * val};
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(T val, const vec_t<T, n>& rhs)
{
    return rhs * val;
}

template<>
AS_API inline const vec3_t operator*(real_t val, const vec3_t& rhs)
{
    return rhs * val;
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator*=(vec_t<T, n>& lhs, T val)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] *= val;
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator*=(vec3_t& lhs, real_t val)
{
    lhs.x *= val;
    lhs.y *= val;
    lhs.z *= val;
    return lhs;
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result{lhs};
    result *= rhs;
    return result;
}

template<>
AS_API inline const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator*=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] *= rhs[i];
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    return lhs;
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator/(const vec_t<T, n>& lhs, T val)
{
    vec_t<T, n> result{lhs};
    result /= val;
    return result;
}

template<>
AS_API inline const vec3_t operator/(const vec3_t& lhs, real_t val)
{
    return {lhs.x / val, lhs.y / val, lhs.z / val};
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator/=(vec_t<T, n>& lhs, T val)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] /= val;
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator/=(vec3_t& lhs, real_t val)
{
    lhs.x /= val;
    lhs.y /= val;
    lhs.z /= val;
    return lhs;
}

template<typename T, index_t n>
AS_API const vec_t<T, n> operator/(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result{lhs};
    result /= rhs;
    return result;
}

template<>
AS_API inline const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs)
{
    return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template<typename T, index_t n>
AS_API vec_t<T, n>& operator/=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (index_t i = 0; i < n; ++i) {
        lhs[i] /= rhs[i];
    }

    return lhs;
}

template<>
AS_API inline vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
    return lhs;
}

} // namespace as
