#pragma once

#include <type_traits>

#include <ASframework/Types/AsTypes.h>

//#define AS_ROW_MAJOR
#define AS_COL_MAJOR

namespace as
{

template<typename T, size_t c, size_t r>
struct Mat
{
	T data[c * r];
	AS_INLINE T& operator[](size_t i) { return data[i]; }
	AS_INLINE const T& operator[](size_t i) const { return data[i]; }
};

typedef Mat<real, 2, 2> v22;

template < typename T, size_t c, size_t r >
AS_INLINE Mat<T, c, r> operator*(const Mat<T, c, r>& lhs, const Mat<T, c, r>& rhs)
{
#ifdef AS_COL_MAJOR
	Mat<T, c, r> result;
	for (size_t colIndex = 0; colIndex < c; ++colIndex) {
		for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
			real value = 0.0f;
			for (size_t step = 0; step < r; ++step) {
				value += lhs[rowIndex + (c * step)] * rhs[(colIndex * r) + step];
			}
			result[colIndex * c + rowIndex] = value;
		}
	}
	return result;
#elif defined AS_ROW_MAJOR
	Mat<T, c, r> result;
	for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
		for (size_t colIndex = 0; colIndex < c; ++colIndex) {
			real value = 0.0f;
			for (size_t step = 0; step < c; ++step) {
				value += lhs[(rowIndex * r) + step] * rhs[colIndex + (c * step)];
			}
			result[rowIndex * c + colIndex] = value;
		}
	}
	return result;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
}

template<typename T, size_t c, size_t r, size_t n>
AS_INLINE Vec<T, n> operator*(const Vec<T, n> vec, const Mat<T, c, r>& mat)
{
#ifdef AS_COL_MAJOR
	static_assert(n == r, "Number of rows does not equal number of elements in vector");
	Vec<T, n> result;
	for (size_t vertexIndex = 0; vertexIndex< n; ++vertexIndex) {
		real value = 0.0f;
		for (size_t step = 0; step < n; ++step) {
			value += vec[step] * mat[vertexIndex * c + step];
		}
		result[vertexIndex] = value;
	}
	return result;
#elif defined AS_ROW_MAJOR
	static_assert(n == c, "Number of columns does not equal number of elements in vector");
	Vec<T, n> result;
	for (size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
		real value = 0.0f;
		for (size_t step = 0; step < n; ++step) {
			value += vec[step] * mat[vertexIndex + step * c];
		}
		result[vertexIndex] = value;
	}
	return result;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
}

template<typename T, size_t c, size_t r, size_t n>
AS_INLINE Vec<T, n> operator*(const Mat<T, c, r>& mat, const Vec<T, n> vec)
{
#ifdef AS_COL_MAJOR
	static_assert(n == r, "Number of rows does not equal number of elements in vector");
	Vec<T, n> result;
	for (size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
		real value = 0.0f;
		for (size_t step = 0; step < n; ++step) {
			value += vec[step] * mat[vertexIndex + step * c];
		}
		result[vertexIndex] = value;
	}
	return result;
#elif defined AS_ROW_MAJOR
	static_assert(n == c, "Number of columns does not equal number of elements in vector");
	Vec<T, n> result;
	for (size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
		real v = 0.0f;
		for (size_t step = 0; step < n; ++step) {
			v += vec[step] * mat[vertexIndex * c + step];
		}
		result[vertexIndex] = v;
	}
	return result;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR
}

template<typename T, size_t c, size_t r>
AS_INLINE Mat<T, r, c> operator*(const Mat<T, c, r>& mat, T scalar)
{
	Mat<T, r, c> result;
	for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
		for (size_t colIndex = 0; colIndex < c; ++colIndex) {
			result[rowIndex * c + colIndex] = mat[rowIndex * c + colIndex] * scalar;
		}
	}
	return result;
}

template<typename T, size_t c, size_t r>
AS_INLINE void operator*=(Mat<T, c, r>& mat, T scalar)
{
	for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
		for (size_t colIndex = 0; colIndex < c; ++colIndex) {
			mat[rowIndex * c + colIndex] *= scalar;
		}
	}
}

template<typename T, size_t c, size_t r>
AS_INLINE Mat<T, r, c> transpose(const Mat<T, c, r>& mat)
{
	Mat<T, r, c> result;
	for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
		for (size_t colIndex = 0; colIndex < c; ++colIndex) {
			result[colIndex * r + rowIndex] = mat[rowIndex * c + colIndex];
		}
	}
	return result;
}

template<typename T, size_t cr>
AS_INLINE Mat<T, cr, cr> identity()
{
	Mat<T, cr, cr> identity;
	size_t size = cr * cr;
	memset(&identity.data[0], 0, size * sizeof(T));
	for (size_t i = 0; i < size; i += cr + 1) {
		identity.data[i] = 1.0f;
	}
	return identity;
}

template<typename T>
AS_INLINE T minor(const Mat<T, 2, 2>& mat)
{
	return mat[0] * mat[3] - mat[2] * mat[1];
}

template<typename T, int cr>
AS_INLINE Mat<T, cr - 1, cr - 1> sub_matrix(const Mat<T, cr, cr> mat, size_t col, size_t row)
{
	Mat<T, cr - 1, cr - 1> result = identity<T, cr - 1>();
	size_t i = 0;
	for (size_t r = 0; r < cr; ++r) {
		for (size_t c = 0; c < cr; ++c) {
			if (r == row || c == col)
				continue;
			result[i++] = mat[r * cr + c];
		}
	}
	return result;
}

template<typename T, int cr>
struct DeterminantHelper
{
	AS_INLINE static T calculate(const Mat<T, cr, cr>& mat) {
		T sign = (T)1;
		T result = 0;
		for (size_t i = 0; i < cr; ++i) {
			T minor = DeterminantHelper<T, cr - 1>::calculate(sub_matrix(mat, i, 0));
			result += (mat[i] * minor) * sign;
			sign *= (T)-1;
		}
		return result;
	}
};

template<typename T, int cr>
struct MinorHelper
{
	AS_INLINE static Mat<T, cr, cr> calculate(const Mat<T, cr, cr>& mat) {
		Mat<T, cr, cr> result;
		T outerSign = (T)1;
		for (size_t i = 0; i < cr; ++i) {
			T innerSign = outerSign;
			for (size_t j = 0; j < cr; ++j) {
				T minor = DeterminantHelper<T, cr - 1>::calculate(sub_matrix(mat, j, i));
				result[j + i * cr] = minor * innerSign;
				innerSign *= (T)-1;
			}
			outerSign *= (T)-1;
		}
		return result;
	}
};

template<typename T>
struct DeterminantHelper<T, 2>
{
	AS_INLINE static T calculate(const Mat<T, 2, 2>& mat) {
		return minor(mat);
	}
};

template<typename T, size_t cr>
AS_INLINE T determinant(const Mat<T, cr, cr>& mat)
{
	return DeterminantHelper<T, cr>::calculate(mat);
}

template<typename T, size_t cr>
AS_INLINE Mat<T, cr, cr> inverse(const Mat<T, cr, cr>& mat)
{
	Mat<T, cr, cr> result;

	T det = determinant(mat);

	result = MinorHelper<T, cr>::calculate(mat);
	result = transpose(result);
	result *= 1.0f / det;

	return result;
}

template<typename T, size_t cr>
AS_INLINE Mat<T, cr, cr> gj_inverse(const Mat<T, cr, cr>& mat)
{
	Mat<T, cr, cr> currentMat = mat;
	Mat<T, cr, cr> result = identity<T, cr>();

	size_t currentLine = 0;
	for (size_t i = 0; i < cr; ++i) {
		T diagonal = currentMat[(cr * i) + i];
		T diagonalRecip = (T)1 / diagonal;
		
		for (size_t j = cr * i; j < cr + (cr * i); ++j) {
			currentMat[j] *= diagonalRecip;
			result[j] *= diagonalRecip;
		}

		for (size_t row = 0; row < cr; ++row) {
			if (row == currentLine)
				continue;
			T next = currentMat[currentLine + row * cr];
			for (size_t col = 0; col < cr; ++col) {
				size_t index = cr * row + col;
				currentMat[index] -= (next * currentMat[cr * currentLine + col]);
				result[index] -= (next * result[cr * currentLine + col]);
			}
		}

		++currentLine;
	}

	return result;
}

}