namespace as
{

template<typename T>
AS_API constexpr index mat<T, 4>::dim()
{
  return 4;
}

template<typename T>
AS_API constexpr index mat<T, 4>::size()
{
  return 16;
}

template<typename T>
AS_API constexpr index mat<T, 4>::rows()
{
  return mat<T, 4>::dim();
}

template<typename T>
AS_API constexpr index mat<T, 4>::cols()
{
  return mat<T, 4>::dim();
}

template<typename T>
AS_API constexpr mat<T, 4> mat<T, 4>::identity()
{
  return mat_identity<T, 4>();
}

// clang-format off
template<typename T>
AS_API constexpr mat<T, 4>::mat(
  T x0, T y0, T z0, T w0,
  T x1, T y1, T z1, T w1,
  T x2, T y2, T z2, T w2,
  T x3, T y3, T z3, T w3)
  : elem_rc{
    x0, y0, z0, w0,
    x1, y1, z1, w1,
    x2, y2, z2, w2,
    x3, y3, z3, w3}
{
}
// clang-format on

template<typename T>
#ifdef AS_ROW_MAJOR
AS_API constexpr mat<T, 4>::mat(
  const vec<T, 4>& row0, const vec<T, 4>& row1, const vec<T, 4>& row2,
  const vec<T, 4>& row3)
  : elem_rc{row0.x, row0.y, row0.z, row0.w, row1.x, row1.y, row1.z, row1.w,
            row2.x, row2.y, row2.z, row2.w, row3.x, row3.y, row3.z, row3.w}
{
}
#elif defined AS_COL_MAJOR
AS_API constexpr mat<T, 4>::mat(
  const vec<T, 4>& col0, const vec<T, 4>& col1, const vec<T, 4>& col2,
  const vec<T, 4>& col3)
  : elem_rc{col0.x, col0.y, col0.z, col0.w, col1.x, col1.y, col1.z, col1.w,
            col2.x, col2.y, col2.z, col2.w, col3.x, col3.y, col3.z, col3.w}
{
}
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

// clang-format off
template<typename T>
AS_API constexpr mat<T, 4>::mat(
  const mat<T, 3>& m, const vec<T, 3>& pos)
  : elem_rc{m[0],  m[1],  m[2],  T(0.0),
            m[3],  m[4],  m[5],  T(0.0),
            m[6],  m[7],  m[8],  T(0.0),
            pos.x, pos.y, pos.z, T(1.0)}
{
}
// clang-format on

template<typename T>
AS_API constexpr T& mat<T, 4>::operator[](index i) &
{
  return elem_rc[i];
}

template<typename T>
AS_API constexpr const T& mat<T, 4>::operator[](index i) const&
{
  return elem_rc[i];
}

template<typename T>
AS_API constexpr const T mat<T, 4>::operator[](index i) &&
{
  return elem_rc[i];
}

AS_API constexpr index mat4_rc(const index r, const index c)
{
  return mat_rc(r, c, 4);
}

} // namespace as
