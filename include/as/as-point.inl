namespace as
{

AS_API constexpr point2_t::point2_t(const real_t xy_) : v{xy_, xy_}
{
}

AS_API constexpr point2_t::point2_t(const vec2_t& v_) : v{v_}
{
}

AS_API constexpr point2_t::point2_t(const real_t x_, const real_t y_) : v{x_, y_}
{
}

AS_API inline real_t& point2_t::operator[](const index_t i) &
{
    return v[i];
}

AS_API inline const real_t& point2_t::operator[](const index_t i) const&
{
    return v[i];
}

AS_API inline real_t point2_t::operator[](const index_t i) &&
{
    return v[i];
}

AS_API constexpr point2_t point2_t::zero()
{
    return point2_t{vec2_t::zero()};
}

AS_API constexpr const vec2_t operator-(
    const point2_t& lhs, const point2_t& rhs)
{
    return lhs.v - rhs.v;
}

AS_API constexpr const point2_t operator+(
    const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v + vec);
}

AS_API constexpr point2_t& operator+=(point2_t& point, const vec2_t& vec)
{
    point.v += vec;
    return point;
}

AS_API constexpr const point2_t operator-(
    const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v - vec);
}

AS_API constexpr point2_t& operator-=(point2_t& point, const vec2_t& vec)
{
    point.v -= vec;
    return point;
}

AS_API constexpr point3_t::point3_t(const real_t xyz_) : v{xyz_, xyz_, xyz_}
{
}

AS_API constexpr point3_t::point3_t(const vec3_t& v_) : v{v_}
{
}

AS_API constexpr point3_t::point3_t(
    const real_t x_, const real_t y_, const real_t z_)
    : v{x_, y_, z_}
{
}

AS_API constexpr point3_t::point3_t(const vec2_t& xy_, const real_t z_)
    : v{xy_.x, xy_.y, z_}
{
}

AS_API inline real_t& point3_t::operator[](const index_t i) &
{
    return v[i];
}

AS_API inline const real_t& point3_t::operator[](const index_t i) const&
{
    return v[i];
}

AS_API inline real_t point3_t::operator[](const index_t i) &&
{
    return v[i];
}

AS_API constexpr point3_t point3_t::zero()
{
    return point3_t{vec3_t::zero()};
}

AS_API constexpr const vec3_t operator-(
    const point3_t& lhs, const point3_t& rhs)
{
    return lhs.v - rhs.v;
}

AS_API constexpr const point3_t operator+(
    const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v + vec);
}

AS_API constexpr point3_t& operator+=(point3_t& point, const vec3_t& vec)
{
    point.v += vec;
    return point;
}

AS_API constexpr const point3_t operator-(
    const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v - vec);
}

AS_API constexpr point3_t& operator-=(point3_t& point, const vec3_t& vec)
{
    point.v -= vec;
    return point;
}

} // namespace as
