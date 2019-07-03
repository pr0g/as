namespace as
{

template <typename T, size_t lh_r, size_t lh_c, size_t rh_r, size_t rh_c>
const mat_t<T, lh_r, rh_c> operator*(const mat_t<T, lh_r, lh_c>& lhs, const mat_t<T, rh_r, rh_c>& rhs)
{
    mat_t<T, lh_r, rh_c> result;
#ifdef AS_COL_MAJOR
    size_t lhr = lh_r;
    size_t lhc = lh_c;
    size_t rhr = rh_r;
    size_t rhc = rh_c;
    for (size_t colIndex = 0; colIndex < rh_c; ++colIndex) {
        for (size_t rowIndex = 0; rowIndex < lh_r; ++rowIndex) {
            T value = 0;
            for (size_t step = 0; step < rh_r; ++step) {
                // size_t orhs = colIndex + rh_r * step;
                size_t orhs = colIndex * rh_r + step;
                // size_t orhs = colIndex * rh_c + step;
                // size_t olhs = rowIndex * lh_r + step;
                size_t olhs = rowIndex + lh_r * step;

                // works with square and mat31, mat13 * mat33
                real_t rr = rhs[orhs];
                real_t ll = lhs[olhs];
                value += ll * rr;
            }
            // size_t f = rowIndex * rh_c + colIndex;
            size_t f = colIndex * rh_c + rowIndex;
            result[f] = value;
        }
    }
#elif defined AS_ROW_MAJOR
    for (size_t rowIndex = 0; rowIndex < lh_r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < rh_c; ++colIndex) {
            T value = 0;
            for (size_t step = 0; step < lh_c; ++step) {
                value += lhs[rowIndex * lh_c + step] * rhs[colIndex + rh_c * step];
            }
            result[rowIndex * lh_r + colIndex] = value;
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
    mat_t<T, r, c> result { mat };
    result *= scalar;
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
