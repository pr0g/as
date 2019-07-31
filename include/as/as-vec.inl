namespace as
{

template<typename T, size_t n>
const vec_t<T, n> operator+(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result { lhs };
    result += rhs;
    return result;
}

template<>
inline const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

template<typename T, size_t n>
vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<>
inline vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

template<typename T, size_t n>
const vec_t<T, n> operator-(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result { lhs };
    result -= rhs;
    return result;
}

template<>
inline const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

template<typename T, size_t n>
vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<>
inline vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

template<typename T, size_t n>
const vec_t<T, n> operator-(const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = -rhs[i];
    }
    return result;
}

template<>
inline const vec3_t operator-(const vec3_t& rhs)
{
    return { -rhs.x, -rhs.y, -rhs.z };
}

template<typename T, size_t n>
const vec_t<T, n> operator*(const vec_t<T, n>& lhs, T val)
{
    vec_t<T, n> result { lhs };
    result *= val;
    return result;
}

template<>
inline const vec3_t operator*(const vec3_t& lhs, real_t val)
{
    return { lhs.x * val, lhs.y * val, lhs.z * val };
}

template<typename T, size_t n>
const vec_t<T, n> operator*(T val, const vec_t<T, n>& rhs)
{
    return rhs * val;
}

template<>
inline const vec3_t operator*(real_t val, const vec3_t& rhs)
{
    return rhs * val;
}

template<typename T, size_t n>
vec_t<T, n>& operator*=(vec_t<T, n>& lhs, T val)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] *= val;
    }
    return lhs;
}

template<>
inline vec3_t& operator*=(vec3_t& lhs, real_t val)
{
    lhs.x *= val;
    lhs.y *= val;
    lhs.z *= val;
    return lhs;
}

template<typename T, size_t n>
const vec_t<T, n> operator*(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result { lhs };
    result *= rhs;
    return result;
}

template<>
inline const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs)
{
    return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
}

template<typename T, size_t n>
vec_t<T, n>& operator*=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] *= rhs[i];
    }
    return lhs;
}

template<>
inline vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    return lhs;
}

template<typename T, size_t n>
const vec_t<T, n> operator/(const vec_t<T, n>& lhs, T val)
{
    vec_t<T, n> result { lhs };
    result /= val;
    return result;
}

template<>
inline const vec3_t operator/(const vec3_t& lhs, real_t val)
{
    return { lhs.x / val, lhs.y / val, lhs.z / val };
}

template<typename T, size_t n>
vec_t<T, n>& operator/=(vec_t<T, n>& lhs, T val)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] /= val;
    }
    return lhs;
}

template<>
inline vec3_t& operator/=(vec3_t& lhs, real_t val)
{
    lhs.x /= val;
    lhs.y /= val;
    lhs.z /= val;
    return lhs;
}

template<typename T, size_t n>
const vec_t<T, n> operator/(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result { lhs };
    result /= rhs;
    return result;
}

template<>
inline const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs)
{
    return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
}

template<typename T, size_t n>
vec_t<T, n>& operator/=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

template<>
inline vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
    return lhs;
}

} // namespace as
