namespace as
{

template <typename T, size_t lr, size_t lc, size_t rr, size_t rc>
#if defined AS_ROW_MAJOR
const mat_t<T, rc, rc>
#elif defined AS_COL_MAJOR
const mat_t<T, lc, lc>
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
operator*(const mat_t<T, lr, lc>& lhs, const mat_t<T, rr, rc>& rhs)
{
#if defined AS_ROW_MAJOR
    mat_t<T, rc, rc> result;
#elif defined AS_COL_MAJOR
    mat_t<T, lc, lc> result;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

#ifdef AS_COL_MAJOR
    for (size_t rowIndex = 0; rowIndex < rr; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < lc; ++colIndex) {
            T value = 0;
            for (size_t step = 0; step < lr; ++step) {
                const T left = lhs[colIndex + lc * step];
                const T right = rhs[rowIndex * rc + step];
                const T intermediate = left * right;
                value += intermediate;
            }
            result[rowIndex * lc + colIndex] = value;
        }
    }
#elif defined AS_ROW_MAJOR
    for (size_t rowIndex = 0; rowIndex < lr; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < rc; ++colIndex) {
            T value = 0;
            for (size_t step = 0; step < lc; ++step) {
                const T left = lhs[rowIndex * lc + step];
                const T right = rhs[colIndex + rc * step];
                const T intermediate = left * right;
                value += intermediate;
            }
            result[rowIndex * lr + colIndex] = value;
        }
    }
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
    return result;
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
