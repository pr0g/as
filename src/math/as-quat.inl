namespace as
{

constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs)
{
    return {
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x
    };
}

constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

const quat_t operator+(const quat_t& lhs, const quat_t& rhs)
{
    return { lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

const quat_t operator-(const quat_t& lhs, const quat_t& rhs)
{
    return { lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

const quat_t operator-(const quat_t& q)
{
    return { -q.w, -q.x, -q.y, -q.z };
}

const quat_t operator/(const quat_t& lhs, real_t rhs)
{
    return { lhs.w / rhs, lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}

const quat_t operator*(const quat_t& lhs, real_t rhs)
{
    return { lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

} // namespace as
