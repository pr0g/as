namespace as
{

// clang-format off
template<typename T>
constexpr mat_t<T, 3>::mat_t(
    T x0, T y0, T z0,
    T x1, T y1, T z1,
    T x2, T y2, T z2)
    : elem_rc{
        x0, y0, z0,
        x1, y1, z1,
        x2, y2, z2}
{
}
// clang-format on

template<typename T>
#ifdef AS_ROW_MAJOR
constexpr mat_t<T, 3>::mat_t(
    const vec_t<T, 3>& row0, const vec_t<T, 3>& row1, const vec_t<T, 3>& row2)
    : elem_rc{row0.x, row0.y, row0.z, row1.x, row1.y,
              row1.z, row2.x, row2.y, row2.z}
{
}
#elif defined AS_COL_MAJOR
constexpr mat_t<T, 3>::mat_t(
    const vec_t<T, 3>& col0, const vec_t<T, 3>& col1, const vec_t<T, 3>& col2)
    : elem_rc{col0.x, col0.y, col0.z, col1.x, col1.y,
              col1.z, col2.x, col2.y, col2.z}
{
}
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T>
constexpr index_t mat_t<T, 3>::dim()
{
    return 3;
}

template<typename T>
constexpr index_t mat_t<T, 3>::size()
{
    return 9;
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::row0() const
{
    return row(0);
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::row1() const
{
    return row(1);
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::row2() const
{
    return row(2);
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::col0() const
{
    return col(0);
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::col1() const
{
    return col(1);
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::col2() const
{
    return col(2);
}

template<typename T>
void mat_t<T, 3>::row0(const vec_t<T, 3>& row_)
{
    row(0, row_);
}

template<typename T>
void mat_t<T, 3>::row1(const vec_t<T, 3>& row_)
{
    row(1, row_);
}

template<typename T>
void mat_t<T, 3>::row2(const vec_t<T, 3>& row_)
{
    row(2, row_);
}

template<typename T>
void mat_t<T, 3>::col0(const vec_t<T, 3>& col_)
{
    col(0, col_);
}

template<typename T>
void mat_t<T, 3>::col1(const vec_t<T, 3>& col_)
{
    col(1, col_);
}

template<typename T>
void mat_t<T, 3>::col2(const vec_t<T, 3>& col_)
{
    col(2, col_);
}

template<typename T>
void mat_t<T, 3>::row(index_t r, const vec_t<T, 3>& row)
{
    elem_rc[mat3::rc(r, 0)] = row.x;
    elem_rc[mat3::rc(r, 1)] = row.y;
    elem_rc[mat3::rc(r, 2)] = row.z;
}

template<typename T>
void mat_t<T, 3>::col(index_t c, const vec_t<T, 3>& col)
{
    elem_rc[mat3::rc(0, c)] = col.x;
    elem_rc[mat3::rc(1, c)] = col.y;
    elem_rc[mat3::rc(2, c)] = col.z;
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::row(index_t r) const
{
    return vec_t<T, 3>{
        elem_rc[mat3::rc(r, 0)], elem_rc[mat3::rc(r, 1)],
        elem_rc[mat3::rc(r, 2)]};
}

template<typename T>
const vec_t<T, 3> mat_t<T, 3>::col(index_t c) const
{
    return vec_t<T, 3>{
        elem_rc[mat3::rc(0, c)], elem_rc[mat3::rc(1, c)],
        elem_rc[mat3::rc(2, c)]};
}

template<typename T>
constexpr T& mat_t<T, 3>::operator[](index_t i) &
{
    return elem_rc[i];
}

template<typename T>
constexpr const T& mat_t<T, 3>::operator[](index_t i) const&
{
    return elem_rc[i];
}

template<typename T>
constexpr const T mat_t<T, 3>::operator[](index_t i) &&
{
    return elem_rc[i];
}

namespace mat3
{

inline index_t rc(const index_t r, const index_t c)
{
    return mat::rc(r, c, 3);
}

} // namespace mat3

} // namespace as
