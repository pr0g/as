namespace as
{

template<typename T, index d>
AS_API mat<T, d> mat_identity()
{
  mat<T, d> identity{};
  for (index i = 0; i < mat<T, d>::size(); i += d + 1) {
    identity[i] = T(1.0);
  }

  return identity;
}

template<typename T, index d>
AS_API constexpr index mat<T, d>::dim()
{
  return d;
}

template<typename T, index d>
AS_API constexpr index mat<T, d>::size()
{
  return d * d;
}

template<typename T, index d>
AS_API constexpr index mat<T, d>::rows()
{
  return mat<T, d>::dim();
}

template<typename T, index d>
AS_API constexpr index mat<T, d>::cols()
{
  return mat<T, d>::dim();
}

template<typename T, index d>
AS_API mat<T, d> mat<T, d>::identity()
{
  return mat_identity<T, d>();
}

template<typename T, index d>
AS_API constexpr T& mat<T, d>::operator[](const index i) &
{
  return elem_rc[i];
}

template<typename T, index d>
AS_API constexpr const T& mat<T, d>::operator[](const index i) const&
{
  return elem_rc[i];
}

template<typename T, index d>
AS_API constexpr const T mat<T, d>::operator[](const index i) &&
{
  return elem_rc[i];
}

template<typename T, index d>
AS_API const mat<T, d> operator*(const mat<T, d>& lhs, const mat<T, d>& rhs)
{
  mat<T, d> result;
#ifdef AS_COL_MAJOR
  for (index col = 0; col < d; ++col) {
    for (index row = 0; row < d; ++row) {
      T value{0};
      for (index step = 0; step < d; ++step) {
        value += lhs[row + d * step] * rhs[col * d + step];
      }

      result[col * d + row] = value;
    }
  }
#elif defined AS_ROW_MAJOR
  for (index row = 0; row < d; ++row) {
    for (index col = 0; col < d; ++col) {
      T value{0};
      for (index step = 0; step < d; ++step) {
        value += lhs[row * d + step] * rhs[col + d * step];
      }

      result[row * d + col] = value;
    }
  }
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
  return result;
}

template<typename T, index d>
#ifdef AS_ROW_MAJOR
AS_API const vec<T, d> operator*(const vec<T, d>& v, const mat<T, d>& m)
#elif defined AS_COL_MAJOR
AS_API const vec<T, d> operator*(const mat<T, d>& m, const vec<T, d>& v)
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    T value{0};

    for (index step = 0; step < d; ++step) {
      value += v[step] * m[i + step * d];
    }

    result[i] = value;
  }

  return result;
}

template<typename T, index d>
AS_API constexpr const mat<T, d> operator*(const mat<T, d>& m, const T scalar)
{
  mat<T, d> result{m};
  result *= scalar;
  return result;
}

template<typename T, index d>
AS_API constexpr mat<T, d>& operator*=(mat<T, d>& m, const T scalar)
{
  for (index row = 0; row < d; ++row) {
    for (index col = 0; col < d; ++col) {
      m[row * d + col] *= scalar;
    }
  }

  return m;
}

template<typename T, index d>
AS_API constexpr bool operator==(const mat<T, d>& lhs, const mat<T, d>& rhs)
{
  return !(lhs != rhs);
}

template<typename T, index d>
AS_API constexpr bool operator!=(const mat<T, d>& lhs, const mat<T, d>& rhs)
{
  for (index row = 0; row < d; ++row) {
    for (index col = 0; col < d; ++col) {
      const index lookup = row * d + col;
      if (lhs[lookup] != rhs[lookup]) {
          return true;
      }
    }
  }

  return false;
}

template<typename T, index d>
AS_API constexpr subscript_iterator<mat<T, d>> begin(mat<T, d>& m)
{
  return subscript_iterator<mat<T, d>>(m, 0);
}

template<typename T, index d>
AS_API constexpr subscript_iterator<mat<T, d>> end(mat<T, d>& m)
{
  return subscript_iterator<mat<T, d>>(m, mat<T, d>::size());
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<mat<T, d>> begin(const mat<T, d>& m)
{
  return subscript_const_iterator<mat<T, d>>(m, 0);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<mat<T, d>> end(const mat<T, d>& m)
{
  return subscript_const_iterator<mat<T, d>>(m, mat<T, d>::size());
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<mat<T, d>> cbegin(const mat<T, d>& m)
{
  return begin(m);
}

template<typename T, index d>
AS_API constexpr subscript_const_iterator<mat<T, d>> cend(const mat<T, d>& m)
{
  return end(m);
}

} // namespace as
