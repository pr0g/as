namespace as
{

template<typename T>
AS_API constexpr point<T, 2>::point(const T xy_) : v{xy_, xy_}
{
}

template<typename T>
AS_API constexpr point<T, 2>::point(const vec<T, 2>& xy_) : v{xy_}
{
}

template<typename T>
AS_API constexpr point<T, 2>::point(const T x_, const T y_) : v{x_, y_}
{
}

template<typename T>
AS_API inline T& point<T, 2>::operator[](const index i) &
{
  return v[i];
}

template<typename T>
AS_API inline const T& point<T, 2>::operator[](const index i) const&
{
  return v[i];
}

template<typename T>
AS_API inline T point<T, 2>::operator[](const index i) &&
{
  return v[i];
}

template<typename T>
AS_API constexpr index point<T, 2>::size()
{
  return 2;
}

template<typename T>
AS_API constexpr point<T, 2> point<T, 2>::zero()
{
  return point<T, 2>{vec<T, 2>::zero()};
}

template<typename T>
AS_API constexpr point<T, 2> point<T, 2>::axis_x(const T x /* = 1.0_r */)
{
  return point<T, 2>{vec<T, 2>::axis_x(x)};
}

template<typename T>
AS_API constexpr point<T, 2> point<T, 2>::axis_y(const T y /* = 1.0_r */)
{
  return point<T, 2>{vec<T, 2>::axis_y(y)};
}

template<typename T>
AS_API constexpr vec<T, 2> point<T, 2>::as_vec() &&
{
  return v;
}

template<typename T>
AS_API constexpr const vec<T, 2>& point<T, 2>::as_vec() const&
{
  return v;
}

template<typename T>
AS_API constexpr point<T, 3>::point(const T xyz_) : v{xyz_, xyz_, xyz_}
{
}

template<typename T>
AS_API constexpr point<T, 3>::point(const vec<T, 3>& v_) : v{v_}
{
}

template<typename T>
AS_API constexpr point<T, 3>::point(const T x_, const T y_, const T z_)
  : v{x_, y_, z_}
{
}

template<typename T>
AS_API constexpr point<T, 3>::point(const vec<T, 2>& xy_, const T z_)
  : v{xy_.x, xy_.y, z_}
{
}

template<typename T>
AS_API inline T& point<T, 3>::operator[](const index i) &
{
  return v[i];
}

template<typename T>
AS_API inline const T& point<T, 3>::operator[](const index i) const&
{
  return v[i];
}

template<typename T>
AS_API inline T point<T, 3>::operator[](const index i) &&
{
  return v[i];
}

template<typename T>
AS_API constexpr index point<T, 3>::size()
{
  return 3;
}

template<typename T>
AS_API constexpr point<T, 3> point<T, 3>::zero()
{
  return point<T, 3>{vec<T, 3>::zero()};
}

template<typename T>
AS_API constexpr point<T, 3> point<T, 3>::axis_x(const T x /* = 1.0_r */)
{
  return point<T, 3>{vec<T, 3>::axis_x(x)};
}

template<typename T>
AS_API constexpr point<T, 3> point<T, 3>::axis_y(const T y /* = 1.0_r */)
{
  return point<T, 3>{vec<T, 3>::axis_y(y)};
}

template<typename T>
AS_API constexpr point<T, 3> point<T, 3>::axis_z(const T z /* = 1.0_r */)
{
  return point<T, 3>{vec<T, 3>::axis_z(z)};
}

template<typename T>
AS_API constexpr vec<T, 3> point<T, 3>::as_vec() &&
{
  return v;
}

template<typename T>
AS_API constexpr const vec<T, 3>& point<T, 3>::as_vec() const&
{
  return v;
}

} // namespace as
