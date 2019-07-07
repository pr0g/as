namespace as
{

template <typename T, size_t d>
const mat_t<T, d> operator*(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs)
{
    mat_t<T, d> result;
#ifdef AS_COL_MAJOR
    for (size_t colIndex = 0; colIndex < d; ++colIndex) {
        for (size_t rowIndex = 0; rowIndex < d; ++rowIndex) {
            T value { 0 };
            for (size_t step = 0; step < d; ++step) {
                value += lhs[rowIndex + d * step] * rhs[colIndex * d + step];
             }
            result[colIndex * d + rowIndex] = value;
         }
     }
#elif defined AS_ROW_MAJOR
    for (size_t rowIndex = 0; rowIndex < d; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < d; ++colIndex) {
            T value { 0 };
            for (size_t step = 0; step < d; ++step) {
                value += lhs[rowIndex * d + step] * rhs[colIndex + d * step];
            }
            result[rowIndex * d + colIndex] = value;
        }
    }
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
    return result;
}

template<typename T, size_t d>
#if defined AS_ROW_MAJOR
const vec_t<T, d> operator*(const vec_t<T, d>& v, const mat_t<T, d>& mat)
#elif defined AS_COL_MAJOR
const vec_t<T, d> operator*(const mat_t<T, d>& mat, const vec_t<T, d>& v)
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
{
    vec_t<T, d> result;
    for (size_t vertexIndex = 0; vertexIndex < d; ++vertexIndex) {
        T value { 0 };
        for (size_t step = 0; step < d; ++step) {
            value += v[step] * mat[vertexIndex + step * d];
        }
        result[vertexIndex] = value;
    }
    return result;
}

template<typename T, size_t d>
const mat_t<T, d> operator*(const mat_t<T, d>& mat, T scalar)
{
    mat_t<T, d> result { mat };
    result *= scalar;
    return result;
}

template<typename T, size_t d>
mat_t<T, d>& operator*=(mat_t<T, d>& mat, T scalar)
{
    for (size_t rowIndex = 0; rowIndex < d; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < d; ++colIndex) {
            mat[rowIndex * d + colIndex] *= scalar;
        }
    }
    return mat;
}

} // namespace as
