namespace as
{

AS_API constexpr point2::point2(const real xy_) : v{xy_, xy_}
{
}

AS_API constexpr point2::point2(const vec2& xy_) : v{xy_}
{
}

AS_API constexpr point2::point2(const real x_, const real y_) : v{x_, y_}
{
}

AS_API inline real& point2::operator[](const index i) &
{
  return v[i];
}

AS_API inline const real& point2::operator[](const index i) const&
{
  return v[i];
}

AS_API inline real point2::operator[](const index i) &&
{
  return v[i];
}

AS_API constexpr index point2::size()
{
  return 2;
}

AS_API constexpr point2 point2::zero()
{
  return point2{vec2::zero()};
}

AS_API constexpr point2 point2::axis_x(const real x /* = 1.0_r */)
{
  return point2{vec2::axis_x(x)};
}

AS_API constexpr point2 point2::axis_y(const real y /* = 1.0_r */)
{
  return point2{vec2::axis_y(y)};
}

AS_API constexpr vec2 point2::as_vec() &&
{
  return v;
}

AS_API constexpr const vec2& point2::as_vec() const&
{
  return v;
}

AS_API constexpr const vec2 operator-(const point2& lhs, const point2& rhs)
{
  return lhs.v - rhs.v;
}

AS_API constexpr const point2 operator+(const point2& p, const vec2& v)
{
  return point2(p.v + v);
}

AS_API constexpr point2& operator+=(point2& p, const vec2& v)
{
  p.v += v;
  return p;
}

AS_API constexpr const point2 operator-(const point2& p, const vec2& v)
{
  return point2(p.v - v);
}

AS_API constexpr point2& operator-=(point2& p, const vec2& v)
{
  p.v -= v;
  return p;
}

AS_API inline const point2 operator-(const point2& p)
{
  return point2{-p.v};
}

AS_API constexpr point3::point3(const real xyz_) : v{xyz_, xyz_, xyz_}
{
}

AS_API constexpr point3::point3(const vec3& v_) : v{v_}
{
}

AS_API constexpr point3::point3(const real x_, const real y_, const real z_)
  : v{x_, y_, z_}
{
}

AS_API constexpr point3::point3(const vec2& xy_, const real z_)
  : v{xy_.x, xy_.y, z_}
{
}

AS_API inline real& point3::operator[](const index i) &
{
  return v[i];
}

AS_API inline const real& point3::operator[](const index i) const&
{
  return v[i];
}

AS_API inline real point3::operator[](const index i) &&
{
  return v[i];
}

AS_API constexpr index point3::size()
{
  return 3;
}

AS_API constexpr point3 point3::zero()
{
  return point3{vec3::zero()};
}

AS_API constexpr point3 point3::axis_x(const real x /* = 1.0_r */)
{
  return point3{vec3::axis_x(x)};
}

AS_API constexpr point3 point3::axis_y(const real y /* = 1.0_r */)
{
  return point3{vec3::axis_y(y)};
}

AS_API constexpr point3 point3::axis_z(const real z /* = 1.0_r */)
{
  return point3{vec3::axis_z(z)};
}

AS_API constexpr vec3 point3::as_vec() &&
{
  return v;
}

AS_API constexpr const vec3& point3::as_vec() const&
{
  return v;
}

AS_API constexpr const vec3 operator-(const point3& lhs, const point3& rhs)
{
  return lhs.v - rhs.v;
}

AS_API constexpr const point3 operator+(const point3& p, const vec3& v)
{
  return point3(p.v + v);
}

AS_API constexpr point3& operator+=(point3& p, const vec3& v)
{
  p.v += v;
  return p;
}

AS_API constexpr const point3 operator-(const point3& p, const vec3& v)
{
  return point3(p.v - v);
}

AS_API constexpr point3& operator-=(point3& p, const vec3& v)
{
  p.v -= v;
  return p;
}

AS_API constexpr const point3 operator-(const point3& p)
{
  return point3{-p.v};
}

} // namespace as
