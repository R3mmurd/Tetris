/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef DEFS_H
# define DEFS_H

# include <QVector>
# include <QPair>

using Pos = QPair<int, int>;

template <typename T, typename R, class Op>
QVector<R> mapstr(const QVector<T> & src, const Op & op)
{
  QVector<R> tgt;

  for (const T & item : src)
    tgt.push_back(op(item));

  return tgt;
}

template <typename T, class Op>
QVector<T> maps(const QVector<T> & src, const Op & op)
{
  return mapstr<T, T, Op>(src, op);
}

template <typename T, class Op>
bool exists(const QVector<T> & v, const Op & op)
{
  for (const T & item : v)
    if (op(item))
      return true;

  return false;
}

template <typename T, class Op>
bool all(T * a, size_t sz, const Op & op)
{
  for (size_t i = 0; i < sz; ++i)
    if (not op(a[i]))
      return false;

  return true;
}

QVector<QVector<Pos>> make_rotations(const QVector<Pos> &);


# endif // DEFS_H
