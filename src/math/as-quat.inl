namespace as
{

constexpr inline real quat::dot(const quat& a, const quat& b)
{
    return a.r * b.r + a.i * b.i + a.j * b.j + a.k * b.k;
}

constexpr inline real quat::length_squared(const quat& a)
{
    return dot(a, a);
}

inline real quat::length(const quat& a)
{
    return std::sqrt(length_squared(a));
}

inline quat quat::normalize(const quat& a)
{
    return a / length(a);
}

constexpr inline quat quat::conjugate(const quat& a)
{
    return { a.r, -a.i, -a.j, -a.k };
}

inline quat quat::inverse(const quat& a)
{
    return conjugate(a) / length_squared(a);
}

inline v3 quat::rotate(const quat& q, const v3& v)
{
    const quat quat_result = q * quat{ 0.0f, v.x, v.y, v.z } * conjugate(q);
    return { quat_result.i, quat_result.j, quat_result.k };
}

inline quat quat::axis_angle(const v3& axis, real radians)
{
    return { cosr(0.5f * radians), axis * sinr(0.5f * radians) };
}

inline quat quat::rotation_zxy(real x, real y, real z)
{
    return quat{ cosr(0.5f * y), 0.0f, sinr(0.5f * y), 0.0f } *
        quat{ cosr(0.5f * x), sinr(0.5f * x), 0.0f, 0.0f } *
        quat{ cosr(0.5f * z), 0.0f, 0.0f, sinr(0.5f * z) };
}

inline quat quat::slerp(const quat& a, const quat& b, real u)
{
    const real theta = acosr(dot(a, b));
    return (a * sinr((1.0f - u) * theta) + b * sinr(u * theta)) / sinr(theta);
}

constexpr inline quat operator*(const quat& a, const quat& b)
{
    return {
        a.r * b.r - a.i * b.i - a.j * b.j - a.k * b.k,
        a.r * b.i + a.i * b.r + a.j * b.k - a.k * b.j,
        a.r * b.j + a.j * b.r + a.k * b.i - a.i * b.k,
        a.r * b.k + a.k * b.r + a.i * b.j - a.j * b.i
    };
}

constexpr inline void operator*=(quat& a, const quat& b)
{
    a = a * b;
}

inline quat operator+(const quat& a, const quat& b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

inline quat operator/(const quat& a, real b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] / b;
    }
    return result;
}

inline quat operator*(real a, const quat& b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a * b.data[i];
    }
    return result;
}

inline quat operator*(const quat& a, real b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] * b;
    }
    return result;
}

}