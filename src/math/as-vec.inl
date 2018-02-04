namespace as
{

template<typename T, size_t n>
Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i)
    {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i)
    {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
Vec<T, n> operator-(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = -vec[i];
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> operator*(const Vec<T, n>& vec, T val)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> operator*(T val, const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
void operator*=(Vec<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i)
    {
        vec[i] *= val;
    }
}

template<typename T, size_t n>
Vec<T, n> operator/(const Vec<T, n>& vec, T val)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] / val;
    }
    return result;
}

template<typename T, size_t n>
void operator/=(Vec<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i)
    {
        vec[i] /= val;
    }
}

} // namespace as