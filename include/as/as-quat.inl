namespace as
{

AS_API constexpr quat_t::quat_t(real_t w_, real_t x_, real_t y_, real_t z_)
    : w{w_}, x{x_}, y{y_}, z{z_}
{
}

AS_API constexpr quat_t::quat_t(real_t w_, const vec3_t& xyz_)
    : w{w_}, x{xyz_.x}, y{xyz_.y}, z{xyz_.z}
{
}

AS_API constexpr quat_t quat_t::identity()
{
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

AS_API constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs)
{
    return {
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x};
}

AS_API constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

AS_API inline const quat_t operator+(const quat_t& lhs, const quat_t& rhs)
{
    return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

AS_API inline const quat_t operator-(const quat_t& lhs, const quat_t& rhs)
{
    return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

AS_API inline const quat_t operator-(const quat_t& q)
{
    return {-q.w, -q.x, -q.y, -q.z};
}

AS_API inline const quat_t operator/(const quat_t& lhs, real_t rhs)
{
    return {lhs.w / rhs, lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

AS_API inline const quat_t operator*(const quat_t& lhs, real_t rhs)
{
    return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

} // namespace as
