/*
  This file is part of Tetris game.
  Copyright (C) 2016 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
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
