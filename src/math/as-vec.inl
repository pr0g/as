namespace as
{

template<typename T, size_t n>
vec_t<T, n> operator+(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i)
    {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
vec_t<T, n> operator-(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    for (size_t i = 0; i < n; ++i)
    {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<typename T, size_t n>
vec_t<T, n> operator-(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = -vec[i];
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> operator*(const vec_t<T, n>& vec, T val)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> operator*(T val, const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] * val;
    }
    return result;
}

template<typename T, size_t n>
void operator*=(vec_t<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i)
    {
        vec[i] *= val;
    }
}

template<typename T, size_t n>
vec_t<T, n> operator/(const vec_t<T, n>& vec, T val)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = vec[i] / val;
    }
    return result;
}

template<typename T, size_t n>
void operator/=(vec_t<T, n>& vec, T val)
{
    for (size_t i = 0; i < n; ++i)
    {
        vec[i] /= val;
    }
}

} // namespace as