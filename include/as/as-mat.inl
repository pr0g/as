namespace as
{

namespace mat
{

template<typename T, index_t d>
AS_API mat_t<T, d> identity()
{
    mat_t<T, d> identity{};
    for (index_t i = 0; i < mat_t<T, d>::size(); i += d + 1) {
        identity[i] = T(1.0);
    }

    return identity;
}

} // namespace mat

template<typename T, index_t d>
AS_API constexpr index_t mat_t<T, d>::dim()
{
    return d;
}

template<typename T, index_t d>
AS_API constexpr index_t mat_t<T, d>::size()
{
    return d * d;
}

template<typename T, index_t d>
AS_API constexpr index_t mat_t<T, d>::rows()
{
    return mat_t<T, d>::dim();
}

template<typename T, index_t d>
AS_API constexpr index_t mat_t<T, d>::cols()
{
    return mat_t<T, d>::dim();
}

template<typename T, index_t d>
AS_API mat_t<T, d> mat_t<T, d>::identity()
{
    return mat::identity<T, d>();
}

template<typename T, index_t d>
AS_API constexpr T& mat_t<T, d>::operator[](const index_t i) &
{
    return elem_rc[i];
}

template<typename T, index_t d>
AS_API constexpr const T& mat_t<T, d>::operator[](const index_t i) const&
{
    return elem_rc[i];
}

template<typename T, index_t d>
AS_API constexpr const T mat_t<T, d>::operator[](const index_t i) &&
{
    return elem_rc[i];
}

template<typename T, index_t d>
AS_API const mat_t<T, d> operator*(
    const mat_t<T, d>& lhs, const mat_t<T, d>& rhs)
{
    mat_t<T, d> result;
#ifdef AS_COL_MAJOR
    for (index_t col = 0; col < d; ++col) {
        for (index_t row = 0; row < d; ++row) {
            T value{0};
            for (index_t step = 0; step < d; ++step) {
                value += lhs[row + d * step] * rhs[col * d + step];
            }

            result[col * d + row] = value;
        }
    }
#elif defined AS_ROW_MAJOR
    for (index_t row = 0; row < d; ++row) {
        for (index_t col = 0; col < d; ++col) {
            T value{0};
            for (index_t step = 0; step < d; ++step) {
                value += lhs[row * d + step] * rhs[col + d * step];
            }

            result[row * d + col] = value;
        }
    }
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
    return result;
}

template<typename T, index_t d>
#ifdef AS_ROW_MAJOR
AS_API const vec_t<T, d> operator*(
    const vec_t<T, d>& vec, const mat_t<T, d>& mat)
#elif defined AS_COL_MAJOR
AS_API const vec_t<T, d> operator*(
    const mat_t<T, d>& mat, const vec_t<T, d>& vec)
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
{
    vec_t<T, d> result;
    for (index_t i = 0; i < d; ++i) {
        T value{0};

        for (index_t step = 0; step < d; ++step) {
            value += vec[step] * mat[i + step * d];
        }

        result[i] = value;
    }

    return result;
}

template<typename T, index_t d>
AS_API constexpr const mat_t<T, d> operator*(
    const mat_t<T, d>& mat, const T scalar)
{
    mat_t<T, d> result{mat};
    result *= scalar;
    return result;
}

template<typename T, index_t d>
AS_API constexpr mat_t<T, d>& operator*=(mat_t<T, d>& mat, const T scalar)
{
    for (index_t row = 0; row < d; ++row) {
        for (index_t col = 0; col < d; ++col) {
            mat[row * d + col] *= scalar;
        }
    }

    return mat;
}

} // namespace as
