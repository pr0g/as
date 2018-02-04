namespace as
{

constexpr inline quat operator*(const quat& lhs, const quat& rhs)
{
    return {
        lhs.r * rhs.r - lhs.i * rhs.i - lhs.j * rhs.j - lhs.k * rhs.k,
        lhs.r * rhs.i + lhs.i * rhs.r + lhs.j * rhs.k - lhs.k * rhs.j,
        lhs.r * rhs.j + lhs.j * rhs.r + lhs.k * rhs.i - lhs.i * rhs.k,
        lhs.r * rhs.k + lhs.k * rhs.r + lhs.i * rhs.j - lhs.j * rhs.i
    };
}

constexpr inline void operator*=(quat& lhs, const quat& rhs)
{
    lhs = lhs * rhs;
}

inline quat operator+(const quat& lhs, const quat& rhs)
{
    return { lhs.r + rhs.r, lhs.i + rhs.i, lhs.j + rhs.j, lhs.k + rhs.k };
}

inline quat operator/(const quat& lhs, real rhs)
{
    return { lhs.r / rhs, lhs.i / rhs, lhs.j / rhs, lhs.k / rhs };
}

inline quat operator*(const quat& lhs, real rhs)
{
    return { lhs.r * rhs, lhs.i * rhs, lhs.j * rhs, lhs.k * rhs };
}

}