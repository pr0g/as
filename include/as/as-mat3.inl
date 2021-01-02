namespace as
{

// clang-format off
template<typename T>
AS_API constexpr mat<T, 3>::mat(
  T x0, T y0, T z0,
  T x1, T y1, T z1,
  T x2, T y2, T z2)
  : elem_rc{
    x0, y0, z0,
    x1, y1, z1,
    x2, y2, z2}
{
}
// clang-format on

template<typename T>
#ifdef AS_ROW_MAJOR
AS_API constexpr mat<T, 3>::mat(
  const vec<T, 3>& row0, const vec<T, 3>& row1, const vec<T, 3>& row2)
  : elem_rc{row0.x, row0.y, row0.z, row1.x, row1.y,
            row1.z, row2.x, row2.y, row2.z}
{
}
#elif defined AS_COL_MAJOR
AS_API constexpr mat<T, 3>::mat(
  const vec<T, 3>& col0, const vec<T, 3>& col1, const vec<T, 3>& col2)
  : elem_rc{col0.x, col0.y, col0.z, col1.x, col1.y,
            col1.z, col2.x, col2.y, col2.z}
{
}
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T>
AS_API constexpr index mat<T, 3>::dim()
{
  return 3;
}

template<typename T>
AS_API constexpr index mat<T, 3>::size()
{
  return 9;
}

template<typename T>
AS_API constexpr index mat<T, 3>::rows()
{
  return mat<T, 3>::dim();
}

template<typename T>
AS_API constexpr index mat<T, 3>::cols()
{
  return mat<T, 3>::dim();
}

template<typename T>
AS_API constexpr mat<T, 3> mat<T, 3>::identity()
{
  return mat_identity<T, 3>();
}

template<typename T>
AS_API constexpr T& mat<T, 3>::operator[](index i) &
{
  return elem_rc[i];
}

template<typename T>
AS_API constexpr const T& mat<T, 3>::operator[](index i) const&
{
  return elem_rc[i];
}

template<typename T>
AS_API constexpr const T mat<T, 3>::operator[](index i) &&
{
  return elem_rc[i];
}

} // namespace as
