namespace as
{

template < typename T, size_t r, size_t c >
const mat_t<T, r, c> operator*(const mat_t<T, r, c>& lhs, const mat_t<T, r, c>& rhs)
{
    mat_t<T, r, c> result;
#ifdef AS_COL_MAJOR
    for (size_t colIndex = 0; colIndex < c; ++colIndex) {
        for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
            T value = 0;
            for (size_t step = 0; step < r; ++step) {
                value += lhs[rowIndex + c * step] * rhs[colIndex * r + step];
            }
            result[colIndex * c + rowIndex] = value;
        }
    }
    return result;
#elif defined AS_ROW_MAJOR
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            T value = 0;
            for (size_t step = 0; step < c; ++step) {
                value += lhs[rowIndex * r + step] * rhs[colIndex + c * step];
            }
            result[rowIndex * c + colIndex] = value;
        }
    }
    return result;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
}

template<typename T, size_t r, size_t c, size_t n>
#if defined AS_ROW_MAJOR
const vec_t<T, n> operator*(const vec_t<T, n>& v, const mat_t<T, r, c>& mat)
#elif defined AS_COL_MAJOR
const vec_t<T, n> operator*(const mat_t<T, r, c>& mat, const vec_t<T, n>& v)
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
{
#if defined AS_ROW_MAJOR
    static_assert(n == c, "Number of columns does not equal number of elements in vector");
#elif defined AS_COL_MAJOR
    static_assert(n == r, "Number of rows does not equal number of elements in vector");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    vec_t<T, n> result;
    for (size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
        T value = 0;
        for (size_t step = 0; step < n; ++step) {
            value += v[step] * mat[vertexIndex + step * c];
        }
        result[vertexIndex] = value;
    }
    return result;
}

template<typename T, size_t r, size_t c>
const mat_t<T, r, c> operator*(const mat_t<T, r, c>& mat, T scalar)
{
    mat_t<T, r, c> result;
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            result[rowIndex * c + colIndex] = mat[rowIndex * c + colIndex] * scalar;
        }
    }
    return result;
}

template<typename T, size_t r, size_t c>
mat_t<T, r, c>& operator*=(mat_t<T, r, c>& mat, T scalar)
{
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            mat[rowIndex * c + colIndex] *= scalar;
        }
    }
    return mat;
}

} // namespace as
