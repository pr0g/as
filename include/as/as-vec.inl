namespace as
{

template<typename T, index d>
AS_API constexpr index vec<T, d>::size()
{
  return d;
}

template<typename T, index d>
AS_API constexpr T& vec<T, d>::operator[](const index i) &
{
  return elem[i];
}

template<typename T, index d>
AS_API constexpr const T& vec<T, d>::operator[](const index i) const&
{
  return elem[i];
}

template<typename T, index d>
AS_API constexpr const T vec<T, d>::operator[](const index i) &&
{
  return elem[i];
}

template<typename T>
AS_API constexpr index vec<T, 2>::size()
{
  return 2;
}

template<typename T>
AS_API T& vec<T, 2>::operator[](const index i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec<T, 2>::operator[](const index i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec<T, 2>::operator[](const index i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec<T, 2>::vec(const T xy_) : x(xy_), y(xy_)
{
}

template<typename T>
AS_API constexpr vec<T, 2>::vec(const T x_, const T y_) : x(x_), y(y_)
{
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::axis_x(const T x)
{
  return {x, T(0)};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::axis_y(const T y)
{
  return {T(0), y};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::zero()
{
  return {T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::one()
{
  return {T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::max()
{
  return vec<T, 2>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::min()
{
  return vec<T, 2>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec<T, 2> vec<T, 2>::lowest()
{
  return vec<T, 2>{std::numeric_limits<T>::lowest()};
}

template<typename T>
AS_API constexpr index vec<T, 3>::size()
{
  return 3;
}

template<typename T>
AS_API T& vec<T, 3>::operator[](const index i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec<T, 3>::operator[](const index i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec<T, 3>::operator[](const index i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec<T, 3>::vec(const T xyz_) : x(xyz_), y(xyz_), z(xyz_)
{
}

template<typename T>
AS_API constexpr vec<T, 3>::vec(const vec<T, 2>& xy_, const T z_)
  : x(xy_.x), y(xy_.y), z(z_)
{
}

template<typename T>
AS_API constexpr vec<T, 3>::vec(const T x_, const T y_, const T z_)
  : x(x_), y(y_), z(z_)
{
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::axis_x(const T x)
{
  return {x, T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::axis_y(const T y)
{
  return {T(0), y, T(0)};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::axis_z(const T z)
{
  return {T(0), T(0), z};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::zero()
{
  return {T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::one()
{
  return {T(1.0), T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::max()
{
  return vec<T, 3>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::min()
{
  return vec<T, 3>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec<T, 3> vec<T, 3>::lowest()
{
  return vec<T, 3>{std::numeric_limits<T>::lowest()};
}

template<typename T>
AS_API constexpr index vec<T, 4>::size()
{
  return 4;
}

template<typename T>
AS_API T& vec<T, 4>::operator[](const index i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec<T, 4>::operator[](const index i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec<T, 4>::operator[](const index i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec<T, 4>::vec(const T xyzw_)
  : x(xyzw_), y(xyzw_), z(xyzw_), w(xyzw_)
{
}

template<typename T>
AS_API constexpr vec<T, 4>::vec(const vec<T, 3>& xyz_, const T w_)
  : x(xyz_.x), y(xyz_.y), z(xyz_.z), w(w_)
{
}

template<typename T>
AS_API constexpr vec<T, 4>::vec(const vec<T, 2>& xy_, const T z_, const T w_)
  : x(xy_.x), y(xy_.y), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec<T, 4>::vec(const vec<T, 2>& xy_, const vec<T, 2>& zw_)
  : x(xy_.x), y(xy_.y), z(zw_.x), w(zw_.y)
{
}

template<typename T>
AS_API constexpr vec<T, 4>::vec(const T x_, const T y_, const T z_, const T w_)
  : x(x_), y(y_), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::axis_x(const T x)
{
  return {x, T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::axis_y(const T y)
{
  return {T(0), y, T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::axis_z(const T z)
{
  return {T(0), T(0), z, T(0)};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::axis_w(const T w)
{
  return {T(0), T(0), T(0), w};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::zero()
{
  return {T(0), T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::one()
{
  return {T(1.0), T(1.0), T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::max()
{
  return vec<T, 4>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::min()
{
  return vec<T, 4>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec<T, 4> vec<T, 4>::lowest()
{
  return vec<T, 4>{std::numeric_limits<T>::lowest()};
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator+(
  const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result{lhs};
  result += rhs;
  return result;
}

template<>
AS_API constexpr const vec2 operator+(const vec2& lhs, const vec2& rhs)
{
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template<>
AS_API constexpr const vec3 operator+(const vec3& lhs, const vec3& rhs)
{
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator+=(vec<T, d>& lhs, const vec<T, d>& rhs)
{
  for (index i = 0; i < d; ++i) {
    lhs[i] += rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator+=(vec3& lhs, const vec3& rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator-(
  const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result{lhs};
  result -= rhs;
  return result;
}

template<>
AS_API constexpr const vec2 operator-(const vec2& lhs, const vec2& rhs)
{
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template<>
AS_API constexpr const vec3 operator-(const vec3& lhs, const vec3& rhs)
{
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator-=(vec<T, d>& lhs, const vec<T, d>& rhs)
{
  for (index i = 0; i < d; ++i) {
    lhs[i] -= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator-=(vec3& lhs, const vec3& rhs)
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
  return lhs;
}

template<typename T, index d>
AS_API const vec<T, d> operator-(const vec<T, d>& rhs)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = -rhs[i];
  }

  return result;
}

template<>
AS_API constexpr const vec3 operator-(const vec3& rhs)
{
  return {-rhs.x, -rhs.y, -rhs.z};
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator*(const vec<T, d>& lhs, const T val)
{
  vec<T, d> result{lhs};
  result *= val;
  return result;
}

template<>
AS_API constexpr const vec3 operator*(const vec3& lhs, const real val)
{
  return {lhs.x * val, lhs.y * val, lhs.z * val};
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator*(T val, const vec<T, d>& rhs)
{
  return rhs * val;
}

template<>
AS_API constexpr const vec3 operator*(const real val, const vec3& rhs)
{
  return rhs * val;
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator*=(vec<T, d>& lhs, const T val)
{
  for (index i = 0; i < d; ++i) {
    lhs[i] *= val;
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator*=(vec3& lhs, const real val)
{
  lhs.x *= val;
  lhs.y *= val;
  lhs.z *= val;
  return lhs;
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator*(
  const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result{lhs};
  result *= rhs;
  return result;
}

template<>
AS_API constexpr const vec3 operator*(const vec3& lhs, const vec3& rhs)
{
  return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator*=(vec<T, d>& lhs, const vec<T, d>& rhs)
{
  for (index i = 0; i < d; ++i) {
    lhs[i] *= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator*=(vec3& lhs, const vec3& rhs)
{
  lhs.x *= rhs.x;
  lhs.y *= rhs.y;
  lhs.z *= rhs.z;
  return lhs;
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator/(const vec<T, d>& lhs, const T val)
{
  vec<T, d> result{lhs};
  result /= val;
  return result;
}

template<>
AS_API constexpr const vec3 operator/(const vec3& lhs, const real val)
{
  const real val_recip = 1.0_r / val;
  return {lhs.x * val_recip, lhs.y * val_recip, lhs.z * val_recip};
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator/=(vec<T, d>& lhs, const T val)
{
  const T val_recip = T(1.0) / val;
  for (index i = 0; i < d; ++i) {
    lhs[i] *= val_recip;
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator/=(vec3& lhs, const real val)
{
  const real val_recip = 1.0_r / val;
  lhs.x *= val_recip;
  lhs.y *= val_recip;
  lhs.z *= val_recip;
  return lhs;
}

template<typename T, index d>
AS_API constexpr const vec<T, d> operator/(
  const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result{lhs};
  result /= rhs;
  return result;
}

template<>
AS_API constexpr const vec3 operator/(const vec3& lhs, const vec3& rhs)
{
  return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template<typename T, index d>
AS_API constexpr vec<T, d>& operator/=(vec<T, d>& lhs, const vec<T, d>& rhs)
{
  for (index i = 0; i < d; ++i) {
    lhs[i] /= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3& operator/=(vec3& lhs, const vec3& rhs)
{
  lhs.x /= rhs.x;
  lhs.y /= rhs.y;
  lhs.z /= rhs.z;
  return lhs;
}

template<typename T, index d>
AS_API constexpr subscript_iterator<vec<T, d>> begin(vec<T, d>& v)
{
  return subscript_iterator<vec<T, d>>(v, 0);
}

template<typename T, index d>
AS_API constexpr subscript_iterator<vec<T, d>> end(vec<T, d>& v)
{
  return subscript_iterator<vec<T, d>>(v, d);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<vec<T, d>> begin(const vec<T, d>& v)
{
  return subscript_const_iterator<vec<T, d>>(v, 0);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<vec<T, d>> end(const vec<T, d>& v)
{
  return subscript_const_iterator<vec<T, d>>(v, d);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<vec<T, d>> cbegin(const vec<T, d>& v)
{
  return begin(v);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<vec<T, d>> cend(const vec<T, d>& v)
{
  return end(v);
}

} // namespace as
