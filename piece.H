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

# ifndef PIECE_H
# define PIECE_H

# include <QColor>
# include <defs.H>

class Board;
class QPainter;

class Piece
{
  Board * board;

  QVector<QVector<Pos>> rotations;

  QColor color;

  QVector<Pos>::size_type current_rotation_index;

  Pos base_pos;

public:
  Piece(Board * b, const QVector<QVector<Pos>> & r, const QColor & c);

  Piece(const Piece &);

  Piece & operator = (const Piece &);

  const QVector<Pos> & get_current_rotation() const;

  const Pos & get_position() const;

  const QColor & get_color() const;

  bool move(int, int, int);

  void draw(QPainter &);
};

# endif // PIECE_H
