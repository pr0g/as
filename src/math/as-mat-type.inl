namespace as
{

template < typename T, size_t r, size_t c >
inline Mat<T, r, c> operator*(const Mat<T, r, c>& lhs, const Mat<T, r, c>& rhs)
{
#ifdef AS_COL_MAJOR
    Mat<T, r, c> result;
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
    Mat<T, r, c> result;
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
inline Vec<T, n> operator*(const Vec<T, n> v, const Mat<T, r, c>& mat)
#elif defined AS_COL_MAJOR
inline Vec<T, n> operator*(const Mat<T, r, c>& mat, const Vec<T, n> v)
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
{
#if defined AS_ROW_MAJOR
    static_assert(n == c, "Number of columns does not equal number of elements in vector");
#elif defined AS_COL_MAJOR
    static_assert(n == r, "Number of rows does not equal number of elements in vector");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    Vec<T, n> result;
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
inline Mat<T, r, c> operator*(const Mat<T, r, c>& mat, T scalar)
{
    Mat<T, r, c> result;
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            result[rowIndex * c + colIndex] = mat[rowIndex * c + colIndex] * scalar;
        }
    }
    return result;
}

template<typename T, size_t r, size_t c>
inline void operator*=(Mat<T, r, c>& mat, T scalar)
{
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            mat[rowIndex * c + colIndex] *= scalar;
        }
    }
}

namespace mat
{

template<typename T, size_t r, size_t c>
inline T* data(const Mat<T, r, c>& mat)
{
    return mat.elem;
}

template<typename T, size_t r, size_t c>
inline const T* const_data(const Mat<T, r, c>& mat)
{
    return mat.elem;
}

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> from_arr(const T(&data)[r * c])
{
    Mat<T, r, c> result;
    std::copy(std::begin(data), std::end(data), result.elem);
    return result;
}

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> from_ptr(const T* data)
{
    Mat<T, r, c> result;
    std::copy(data, data + r * c, result.elem);
    return result;
}

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> transpose(const Mat<T, r, c>& mat)
{
    Mat<T, r, c> result;
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            result[colIndex * r + rowIndex] = mat[rowIndex * c + colIndex];
        }
    }
    return result;
}

template<typename T, size_t rc>
inline Mat<T, rc, rc> identity()
{
    Mat<T, rc, rc> identity;
    size_t size = rc * rc;
    std::fill(std::begin(identity.elem), std::end(identity.elem), 0.0f);
    for (size_t i = 0; i < size; i += rc + 1) {
        identity.elem[i] = 1.0f;
    }
    return identity;
}

namespace internal
{

template<size_t> struct int2type {};

template<typename T>
inline T minor(const Mat<T, 2, 2>& mat)
{
    return mat[0] * mat[3] - mat[2] * mat[1];
}

// where col and row are the rows to ignore
template<typename T, size_t rc>
inline Mat<T, rc - 1, rc - 1> sub_matrix(const Mat<T, rc, rc>& mat, size_t col, size_t row)
{
    Mat<T, rc - 1, rc - 1> result = identity<T, rc - 1>();
    size_t i = 0;
    for (size_t r = 0; r < rc; ++r) {
        for (size_t c = 0; c < rc; ++c) {
            if (r == row || c == col)
                continue;
            result[i++] = mat[r * rc + c];
        }
    }
    return result;
}

template<typename T, size_t rc, size_t I>
T determinant_impl(const Mat<T, rc, rc>& mat, int2type<I>)
{
    T sign{ 1 };
    T result = 0;
    for (size_t i = 0; i < rc; ++i) {
        T minor = determinant_impl(sub_matrix(mat, i, 0), int2type<I - 1>{});
        result += (mat[i] * minor) * sign;
        sign *= T{ -1 };
    }
    return result;
}

template<typename T>
T determinant_impl(const Mat<T, 2, 2>& mat, int2type<2>)
{
    return minor(mat);
};

template<typename T, size_t rc, size_t I>
inline Mat<T, rc, rc> minor_impl(const Mat<T, rc, rc>& mat, int2type<I>)
{
    Mat<T, rc, rc> result;
    T outerSign = T{ 1 };
    for (size_t i = 0; i < rc; ++i) {
        T innerSign = outerSign;
        for (size_t j = 0; j < rc; ++j) {
            T minor = determinant_impl<T>(internal::sub_matrix(mat, j, i), int2type<rc - 1>{});
            result[j + i * rc] = minor * innerSign;
            innerSign *= T{ -1 };
        }
        outerSign *= T{ -1 };
    }
    return result;
}

} // namespace internal

template<typename T, size_t rc>
inline T determinant(const Mat<T, rc, rc>& mat)
{
    return internal::determinant_impl(mat, internal::int2type<rc>{});
}

template<typename T, size_t rc>
inline Mat<T, rc, rc> inverse(const Mat<T, rc, rc>& mat)
{
    Mat<T, rc, rc> result;

    result = internal::minor_impl(mat, internal::int2type<rc>{});
    result = transpose(result);
    result *= 1.0f / determinant(mat);

    return result;
}

template<typename T, size_t rc>
inline Mat<T, rc, rc> gj_inverse(const Mat<T, rc, rc>& mat)
{
    Mat<T, rc, rc> currentMat = mat;
    Mat<T, rc, rc> result = identity<T, rc>();

    size_t currentLine = 0;
    for (size_t i = 0; i < rc; ++i) {
        T diagonal = currentMat[(rc * i) + i];
        T diagonalRecip = T{ 1 } / diagonal;

        for (size_t j = rc * i; j < rc + (rc * i); ++j) {
            currentMat[j] *= diagonalRecip;
            result[j] *= diagonalRecip;
        }

        for (size_t row = 0; row < rc; ++row) {
            if (row == currentLine)
                continue;
            T next = currentMat[currentLine + row * rc];
            for (size_t col = 0; col < rc; ++col) {
                size_t index = rc * row + col;
                currentMat[index] -= (next * currentMat[rc * currentLine + col]);
                result[index] -= (next * result[rc * currentLine + col]);
            }
        }

        ++currentLine;
    }

    return result;
}

} // namespace mat

} // namespace as