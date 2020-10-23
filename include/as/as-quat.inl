namespace as
{

AS_API constexpr quat::quat(
  const real w_, const real x_, const real y_, const real z_)
  : w{w_}, x{x_}, y{y_}, z{z_}
{
}

AS_API constexpr quat::quat(const real w_, const vec3& xyz_)
  : w{w_}, x{xyz_.x}, y{xyz_.y}, z{xyz_.z}
{
}

AS_API constexpr quat quat::identity()
{
  return {1.0_r, 0.0_r, 0.0_r, 0.0_r};
}

AS_API constexpr const quat operator*(const quat& lhs, const quat& rhs)
{
  return {
    lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
    lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
    lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x};
}

AS_API constexpr quat& operator*=(quat& lhs, const quat& rhs)
{
  lhs = lhs * rhs;
  return lhs;
}

AS_API constexpr const quat operator+(const quat& lhs, const quat& rhs)
{
  return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

AS_API constexpr const quat operator-(const quat& lhs, const quat& rhs)
{
  return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

AS_API constexpr const quat operator-(const quat& q)
{
  return {-q.w, -q.x, -q.y, -q.z};
}

AS_API constexpr const quat operator/(const quat& lhs, const real rhs)
{
  const real rhs_recip = 1.0_r / rhs;
  return {
    lhs.w * rhs_recip, lhs.x * rhs_recip, lhs.y * rhs_recip, lhs.z * rhs_recip};
}

AS_API constexpr const quat operator*(const quat& lhs, const real rhs)
{
  return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

} // namespace as
