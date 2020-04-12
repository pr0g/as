namespace as
{

template<typename T>
constexpr index_t mat_t<T, 4>::dim()
{
    return 4;
}

template<typename T>
constexpr index_t mat_t<T, 4>::size()
{
    return 16;
}

// clang-format off
template<typename T>
constexpr mat_t<T, 4>::mat_t(
    T x0, T y0, T z0, T w0,
    T x1, T y1, T z1, T w1,
    T x2, T y2, T z2, T w2,
    T x3, T y3, T z3, T w3)
    : elem_rc{
        x0, y0, z0, w0,
        x1, y1, z1, w1,
        x2, y2, z2, w2,
        x3, y3, z3, w3}
{
}
// clang-format on

template<typename T>
#ifdef AS_ROW_MAJOR
constexpr mat_t<T, 4>::mat_t(
    const vec_t<T, 4>& row0, const vec_t<T, 4>& row1, const vec_t<T, 4>& row2,
    const vec_t<T, 4>& row3)
    : elem_rc{row0.x, row0.y, row0.z, row0.w, row1.x, row1.y, row1.z, row1.w,
              row2.x, row2.y, row2.z, row2.w, row3.x, row3.y, row3.z, row3.w}
{
}
#elif defined AS_COL_MAJOR
constexpr mat_t<T, 4>::mat_t(
    const vec_t<T, 4>& col0, const vec_t<T, 4>& col1, const vec_t<T, 4>& col2,
    const vec_t<T, 4>& col3)
    : elem_rc{col0.x, col0.y, col0.z, col0.w, col1.x, col1.y, col1.z, col1.w,
              col2.x, col2.y, col2.z, col2.w, col3.x, col3.y, col3.z, col3.w}
{
}
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T>
constexpr mat_t<T, 4>::mat_t(const mat_t<T, 3>& mat_, const vec_t<T, 3>& pos_)
    : elem_rc{mat_.elem_rc[0], mat_.elem_rc[1], mat_.elem_rc[2], 0.0f,
              mat_.elem_rc[3], mat_.elem_rc[4], mat_.elem_rc[5], 0.0f,
              mat_.elem_rc[6], mat_.elem_rc[7], mat_.elem_rc[8], 0.0f,
              pos_.x,          pos_.y,          pos_.z,          1.0f}
{
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::row0() const
{
    return row(0);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::row1() const
{
    return row(1);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::row2() const
{
    return row(2);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::row3() const
{
    return row(3);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::col0() const
{
    return col(0);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::col1() const
{
    return col(1);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::col2() const
{
    return col(2);
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::col3() const
{
    return col(3);
}

template<typename T>
void mat_t<T, 4>::row0(const vec_t<T, 4>& row_)
{
    row(0, row_);
}

template<typename T>
void mat_t<T, 4>::row1(const vec_t<T, 4>& row_)
{
    row(1, row_);
}

template<typename T>
void mat_t<T, 4>::row2(const vec_t<T, 4>& row_)
{
    row(2, row_);
}

template<typename T>
void mat_t<T, 4>::row3(const vec_t<T, 4>& row_)
{
    row(3, row_);
}

template<typename T>
void mat_t<T, 4>::col0(const vec_t<T, 4>& col_)
{
    col(0, col_);
}

template<typename T>
void mat_t<T, 4>::col1(const vec_t<T, 4>& col_)
{
    col(1, col_);
}

template<typename T>
void mat_t<T, 4>::col2(const vec_t<T, 4>& col_)
{
    col(2, col_);
}

template<typename T>
void mat_t<T, 4>::col3(const vec_t<T, 4>& col_)
{
    col(3, col_);
}

template<typename T>
void mat_t<T, 4>::row(index_t r, const vec_t<T, 4>& row)
{
    elem_rc[mat4::rc(r, 0)] = row.x;
    elem_rc[mat4::rc(r, 1)] = row.y;
    elem_rc[mat4::rc(r, 2)] = row.z;
    elem_rc[mat4::rc(r, 3)] = row.w;
}

template<typename T>
void mat_t<T, 4>::col(index_t c, const vec_t<T, 4>& col)
{
    elem_rc[mat4::rc(0, c)] = col.x;
    elem_rc[mat4::rc(1, c)] = col.y;
    elem_rc[mat4::rc(2, c)] = col.z;
    elem_rc[mat4::rc(3, c)] = col.w;
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::row(index_t r) const
{
    return vec_t<T, 4>{
        elem_rc[mat4::rc(r, 0)], elem_rc[mat4::rc(r, 1)],
        elem_rc[mat4::rc(r, 2)], elem_rc[mat4::rc(r, 3)]};
}

template<typename T>
const vec_t<T, 4> mat_t<T, 4>::col(index_t c) const
{
    return vec_t<T, 4>{
        elem_rc[mat4::rc(0, c)], elem_rc[mat4::rc(1, c)],
        elem_rc[mat4::rc(2, c)], elem_rc[mat4::rc(3, c)]};
}

template<typename T>
constexpr T& mat_t<T, 4>::operator[](index_t i) &
{
    return elem_rc[i];
}

template<typename T>
constexpr const T& mat_t<T, 4>::operator[](index_t i) const&
{
    return elem_rc[i];
}

template<typename T>
constexpr const T mat_t<T, 4>::operator[](index_t i) &&
{
    return elem_rc[i];
}

namespace mat4
{

inline index_t rc(const index_t r, const index_t c)
{
    return mat::rc(r, c, 4);
}

} // namespace mat4

} // namespace as
