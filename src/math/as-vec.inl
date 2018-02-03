namespace as
{

constexpr v2 v2::from_ptr(const real* data)
{
    return vec::from_ptr<real, 2>(data);
}

constexpr v2 v2::from_arr(const real(&data)[2])
{
    return vec::from_arr(data);
}

constexpr v3 v3::from_ptr(const real* data)
{
    return vec::from_ptr<real, 3>(data);
}

constexpr v3 v3::from_arr(const real(&data)[3])
{
    return vec::from_arr(data);
}

constexpr v4 v4::from_ptr(const real* data)
{
    return vec::from_ptr<real, 4>(data);
}

constexpr v4 v4::from_arr(const real(&data)[4])
{
    return vec::from_arr(data);
}

namespace vec
{

template<typename T, size_t n>
size_t size(Vec<T, n>&)
{
    return n;
}

template<typename T, size_t n>
const T* const_data(const Vec<T, n>& vec)
{
    return vec.elem;
}

template<typename T, size_t n>
T* data(Vec<T, n>& vec)
{
    return vec.elem;
}

template<typename T, size_t n>
Vec<T, n> from_arr(const T(&data)[n])
{
    Vec<T, n> result;
    std::copy(std::begin(data), std::end(data), result.elem);
    return result;
}

template<typename T, size_t n>
Vec<T, n> from_ptr(const T* data)
{
    Vec<T, n> result;
    std::copy(data, data + n, result.elem);
    return result;
}

template<typename T, size_t n>
T dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += lhs[i] * rhs[i];
    }
    return result;
}

template<typename T, size_t n>
T length_squared(const Vec<T, n>& vec)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += vec[i] * vec[i];
    }
    return result;
}

template<typename T, size_t n>
T length(const Vec<T, n>& vec)
{
    return sqrt(length_squared(vec));
}

template<typename T, size_t n>
Vec<T, n> normalize(const Vec<T, n>& vec)
{
    return vec / length(vec);
}

template<typename T, size_t n>
T normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out)
{
    T len = length(vec);
    out = vec / len;
    return len;
}

template<typename T, size_t n>
Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
Vec<T, n> operator-(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = -vec[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> operator*(const Vec<T, n>& vec, T val)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> operator*(T val, const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
void operator*=(Vec<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i) {
        vec[i] *= val;
    }
}

template<typename T, size_t n>
Vec<T, n> operator/(const Vec<T, n>& vec, T val)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[i] = vec[i] / val;
    }
    return result;
}

template<typename T, size_t n>
void operator/=(Vec<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i) {
        vec[i] /= val;
    }
}

template<typename T, size_t n>
bool equal(const Vec<T, n>& lhs, const Vec<T, n>& rhs, real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    bool eq = true;
    for (size_t i = 0; i < n; ++i) {
        eq &= as::equal(lhs[i], rhs[i], epsilon, epsilon);
        if (!eq) { break; }
    }
    return eq;
}

template<typename T, size_t n>
Vec<T, n> min(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::min(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T min_elem(const Vec<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::min(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
Vec<T, n> max(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::max(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T max_elem(const Vec<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::max(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
Vec<T, n> abs(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = absr(vec[i]);
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> clamp(const Vec<T, n>& vec, const Vec<T, n>& min, const Vec<T, n>& max)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], min[ i ], max[ i ] );
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> saturate(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], 0.0f, 1.0f );
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> lerp(T t, const Vec<T, n>& v0, const Vec<T, n>& v1)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::lerp(t, v0[i], v1[i]);
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> select(const Vec<T, n>& v0, const Vec<T, n>& v1, bool select0)
{
    return select0 ? v0 : v1;
}

v3 cross(const v3& lhs, const v3& rhs)
{
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

// note: will not work if dir == +/-world_up
void right_and_up_lh(const v3& dir, v3& across, v3& up, const v3& world_up /*= v3_y*/)
{
    AS_ASSERT_DESC(!equal(dir, world_up), "dir and world_up are equal");

    across = cross(dir, world_up);
    up = normalize(cross(across, dir));
    across = normalize(cross(up, dir));
}

// note: will not work if dir == +/-world_up
void right_and_up_rh(const v3& dir, v3& across, v3& up, const v3& world_up /*= v3_y*/)
{
    AS_ASSERT_DESC(!equal(dir, world_up), "dir and world_up are equal");

    across = cross(dir, world_up);
    up = normalize(cross(across, dir));
    across = normalize(cross(dir, up));
}

} // namespace vec

} // namespace as