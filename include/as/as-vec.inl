namespace as
{

template<typename T, index_t d>
AS_API constexpr index_t vec_t<T, d>::size()
{
  return d;
}

template<typename T, index_t d>
AS_API constexpr T& vec_t<T, d>::operator[](const index_t i) &
{
  return elem[i];
}

template<typename T, index_t d>
AS_API constexpr const T& vec_t<T, d>::operator[](const index_t i) const&
{
  return elem[i];
}

template<typename T, index_t d>
AS_API constexpr const T vec_t<T, d>::operator[](const index_t i) &&
{
  return elem[i];
}

template<typename T>
AS_API constexpr index_t vec_t<T, 2>::size()
{
  return 2;
}

template<typename T>
AS_API T& vec_t<T, 2>::operator[](const index_t i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec_t<T, 2>::operator[](const index_t i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec_t<T, 2>::operator[](const index_t i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec_t<T, 2>::vec_t(const T xy_) : x(xy_), y(xy_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 2>::vec_t(const T x_, const T y_) : x(x_), y(y_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::axis_x(const T x)
{
  return {x, T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::axis_y(const T y)
{
  return {T(0), y};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::zero()
{
  return {T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::one()
{
  return {T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::max()
{
  return vec_t<T, 2>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::min()
{
  return vec_t<T, 2>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec_t<T, 2> vec_t<T, 2>::lowest()
{
  return vec_t<T, 2>{std::numeric_limits<T>::lowest()};
}

template<typename T>
AS_API constexpr index_t vec_t<T, 3>::size()
{
  return 3;
}

template<typename T>
AS_API T& vec_t<T, 3>::operator[](const index_t i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec_t<T, 3>::operator[](const index_t i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec_t<T, 3>::operator[](const index_t i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(const T xyz_) : x(xyz_), y(xyz_), z(xyz_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(const vec_t<T, 2>& xy_, const T z_)
  : x(xy_.x), y(xy_.y), z(z_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 3>::vec_t(const T x_, const T y_, const T z_)
  : x(x_), y(y_), z(z_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::axis_x(const T x)
{
  return {x, T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::axis_y(const T y)
{
  return {T(0), y, T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::axis_z(const T z)
{
  return {T(0), T(0), z};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::zero()
{
  return {T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::one()
{
  return {T(1.0), T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::max()
{
  return vec_t<T, 3>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::min()
{
  return vec_t<T, 3>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec_t<T, 3> vec_t<T, 3>::lowest()
{
  return vec_t<T, 3>{std::numeric_limits<T>::lowest()};
}

template<typename T>
AS_API constexpr index_t vec_t<T, 4>::size()
{
  return 4;
}

template<typename T>
AS_API T& vec_t<T, 4>::operator[](const index_t i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API const T& vec_t<T, 4>::operator[](const index_t i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API const T vec_t<T, 4>::operator[](const index_t i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(const T xyzw_)
  : x(xyzw_), y(xyzw_), z(xyzw_), w(xyzw_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(const vec_t<T, 3>& xyz_, const T w_)
  : x(xyz_.x), y(xyz_.y), z(xyz_.z), w(w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(
  const vec_t<T, 2>& xy_, const T z_, const T w_)
  : x(xy_.x), y(xy_.y), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(
  const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw_)
  : x(xy_.x), y(xy_.y), z(zw_.x), w(zw_.y)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4>::vec_t(
  const T x_, const T y_, const T z_, const T w_)
  : x(x_), y(y_), z(z_), w(w_)
{
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::axis_x(const T x)
{
  return {x, T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::axis_y(const T y)
{
  return {T(0), y, T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::axis_z(const T z)
{
  return {T(0), T(0), z, T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::axis_w(const T w)
{
  return {T(0), T(0), T(0), w};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::zero()
{
  return {T(0), T(0), T(0), T(0)};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::one()
{
  return {T(1.0), T(1.0), T(1.0), T(1.0)};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::max()
{
  return vec_t<T, 4>{std::numeric_limits<T>::max()};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::min()
{
  return vec_t<T, 4>{std::numeric_limits<T>::min()};
}

template<typename T>
AS_API constexpr vec_t<T, 4> vec_t<T, 4>::lowest()
{
  return vec_t<T, 4>{std::numeric_limits<T>::lowest()};
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator+(
  const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result{lhs};
  result += rhs;
  return result;
}

template<>
AS_API constexpr const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs)
{
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator+=(
  vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  for (index_t i = 0; i < d; ++i) {
    lhs[i] += rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator-(
  const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result{lhs};
  result -= rhs;
  return result;
}

template<>
AS_API constexpr const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs)
{
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator-=(
  vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  for (index_t i = 0; i < d; ++i) {
    lhs[i] -= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs)
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
  return lhs;
}

template<typename T, index_t d>
AS_API const vec_t<T, d> operator-(const vec_t<T, d>& rhs)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = -rhs[i];
  }

  return result;
}

template<>
AS_API constexpr const vec3_t operator-(const vec3_t& rhs)
{
  return {-rhs.x, -rhs.y, -rhs.z};
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator*(
  const vec_t<T, d>& lhs, const T val)
{
  vec_t<T, d> result{lhs};
  result *= val;
  return result;
}

template<>
AS_API constexpr const vec3_t operator*(const vec3_t& lhs, const real_t val)
{
  return {lhs.x * val, lhs.y * val, lhs.z * val};
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator*(T val, const vec_t<T, d>& rhs)
{
  return rhs * val;
}

template<>
AS_API constexpr const vec3_t operator*(const real_t val, const vec3_t& rhs)
{
  return rhs * val;
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator*=(vec_t<T, d>& lhs, const T val)
{
  for (index_t i = 0; i < d; ++i) {
    lhs[i] *= val;
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator*=(vec3_t& lhs, const real_t val)
{
  lhs.x *= val;
  lhs.y *= val;
  lhs.z *= val;
  return lhs;
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator*(
  const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result{lhs};
  result *= rhs;
  return result;
}

template<>
AS_API constexpr const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs)
{
  return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator*=(
  vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  for (index_t i = 0; i < d; ++i) {
    lhs[i] *= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs)
{
  lhs.x *= rhs.x;
  lhs.y *= rhs.y;
  lhs.z *= rhs.z;
  return lhs;
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator/(
  const vec_t<T, d>& lhs, const T val)
{
  vec_t<T, d> result{lhs};
  result /= val;
  return result;
}

template<>
AS_API constexpr const vec3_t operator/(const vec3_t& lhs, const real_t val)
{
  const real_t val_recip = 1.0_r / val;
  return {lhs.x * val_recip, lhs.y * val_recip, lhs.z * val_recip};
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator/=(vec_t<T, d>& lhs, const T val)
{
  const T val_recip = T(1.0) / val;
  for (index_t i = 0; i < d; ++i) {
    lhs[i] *= val_recip;
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator/=(vec3_t& lhs, const real_t val)
{
  const real_t val_recip = 1.0_r / val;
  lhs.x *= val_recip;
  lhs.y *= val_recip;
  lhs.z *= val_recip;
  return lhs;
}

template<typename T, index_t d>
AS_API constexpr const vec_t<T, d> operator/(
  const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result{lhs};
  result /= rhs;
  return result;
}

template<>
AS_API constexpr const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs)
{
  return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d>& operator/=(
  vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  for (index_t i = 0; i < d; ++i) {
    lhs[i] /= rhs[i];
  }

  return lhs;
}

template<>
AS_API constexpr vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs)
{
  lhs.x /= rhs.x;
  lhs.y /= rhs.y;
  lhs.z /= rhs.z;
  return lhs;
}

} // namespace as
