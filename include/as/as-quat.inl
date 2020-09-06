namespace as
{

AS_API constexpr quat_t::quat_t(
    const real_t w_, const real_t x_, const real_t y_, const real_t z_)
    : w{w_}, x{x_}, y{y_}, z{z_}
{
}

AS_API constexpr quat_t::quat_t(const real_t w_, const vec3_t& xyz_)
    : w{w_}, x{xyz_.x}, y{xyz_.y}, z{xyz_.z}
{
}

AS_API constexpr quat_t quat_t::identity()
{
    return {real_t(1.0), real_t(0.0), real_t(0.0), real_t(0.0)};
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

AS_API constexpr const quat_t operator+(const quat_t& lhs, const quat_t& rhs)
{
    return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

AS_API constexpr const quat_t operator-(const quat_t& lhs, const quat_t& rhs)
{
    return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

AS_API constexpr const quat_t operator-(const quat_t& quat)
{
    return {-quat.w, -quat.x, -quat.y, -quat.z};
}

AS_API constexpr const quat_t operator/(const quat_t& lhs, const real_t rhs)
{
    const real_t rhs_recip = 1.0_r / rhs;
    return {
        lhs.w * rhs_recip, lhs.x * rhs_recip, lhs.y * rhs_recip,
        lhs.z * rhs_recip};
}

AS_API constexpr const quat_t operator*(const quat_t& lhs, const real_t rhs)
{
    return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

} // namespace as
