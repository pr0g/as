namespace as
{

template<typename T>
AS_API constexpr quat_t<T>::quat_t(
  const T w_, const T x_, const T y_, const T z_)
  : w{w_}, x{x_}, y{y_}, z{z_}
{
}

template<typename T>
AS_API constexpr quat_t<T>::quat_t(const T w_, const vec3& xyz_)
  : w{w_}, x{xyz_.x}, y{xyz_.y}, z{xyz_.z}
{
}

template<typename T>
AS_API constexpr quat_t<T> quat_t<T>::identity()
{
  return {T(1.0), T(0.0), T(0.0), T(0.0)};
}

template<typename T>
AS_API constexpr index quat_t<T>::size()
{
  return 4;
}

template<typename T>
AS_API inline T& quat_t<T>::operator[](const index i) &
{
  return this->*elem[i];
}

template<typename T>
AS_API inline const T& quat_t<T>::operator[](const index i) const&
{
  return this->*elem[i];
}

template<typename T>
AS_API inline T quat_t<T>::operator[](const index i) &&
{
  return this->*elem[i];
}

template<typename T>
AS_API constexpr const quat_t<T> operator*(
  const quat_t<T>& lhs, const quat_t<T>& rhs)
{
  return {
    lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
    lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
    lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x};
}

template<typename T>
AS_API constexpr quat_t<T>& operator*=(quat_t<T>& lhs, const quat_t<T>& rhs)
{
  lhs = lhs * rhs;
  return lhs;
}

template<typename T>
AS_API constexpr const quat_t<T> operator+(
  const quat_t<T>& lhs, const quat_t<T>& rhs)
{
  return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template<typename T>
AS_API constexpr quat_t<T>& operator+=(quat_t<T>& lhs, const quat_t<T>& rhs)
{
  lhs.w += rhs.w;
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

template<typename T>
AS_API constexpr const quat_t<T> operator-(
  const quat_t<T>& lhs, const quat_t<T>& rhs)
{
  return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template<typename T>
AS_API constexpr quat_t<T>& operator-=(quat_t<T>& lhs, const quat_t<T>& rhs)
{
  lhs.w -= rhs.w;
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
  return lhs;
}

template<typename T>
AS_API constexpr const quat_t<T> operator-(const quat_t<T>& q)
{
  return {-q.w, -q.x, -q.y, -q.z};
}

template<typename T>
AS_API constexpr const quat_t<T> operator/(const quat_t<T>& lhs, const T rhs)
{
  const T rhs_recip = T(1.0) / rhs;
  return {
    lhs.w * rhs_recip, lhs.x * rhs_recip, lhs.y * rhs_recip, lhs.z * rhs_recip};
}

template<typename T>
AS_API constexpr const quat_t<T> operator*(const quat_t<T>& lhs, const T rhs)
{
  return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

template<typename T>
AS_API constexpr const quat_t<T> operator*(const T lhs, const quat_t<T>& rhs)
{
  return operator*(rhs, lhs);
}

template<typename T>
AS_API inline subscript_iterator<quat_t<T>> begin(quat_t<T>& q)
{
  return subscript_iterator<quat_t<T>>(q, 0);
}

template<typename T>
AS_API inline subscript_iterator<quat_t<T>> end(quat_t<T>& q)
{
  return subscript_iterator<quat_t<T>>(q, quat_t<T>::size());
}

template<typename T>
AS_API inline subscript_const_iterator<quat_t<T>> begin(const quat_t<T>& q)
{
  return subscript_const_iterator<quat_t<T>>(q, 0);
}

template<typename T>
AS_API inline subscript_const_iterator<quat_t<T>> end(const quat_t<T>& q)
{
  return subscript_const_iterator<quat_t<T>>(q, quat_t<T>::size());
}

template<typename T>
AS_API inline subscript_const_iterator<quat_t<T>> cbegin(const quat_t<T>& q)
{
  return begin(q);
}

template<typename T>
AS_API inline subscript_const_iterator<quat_t<T>> cend(const quat_t<T>& q)
{
  return end(q);
}

} // namespace as
