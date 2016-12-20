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

# ifndef ALLPIECES_H
# define ALLPIECES_H

# include <random>

# include <piece.H>

class AllPieces
{
  static std::mt19937 rng;
  static QVector<QVector<QVector<Pos>>> all_rotations;
  static QVector<QVector<Pos>> cheat_piece;
  static QVector<QColor> colors;
  static QVector<Pos>::size_type gr_sz_piece;

public:
  AllPieces() = delete;
  AllPieces(const AllPieces &) = delete;
  AllPieces & operator = (const AllPieces &) = delete;

  static Piece next_piece(Board *);

  static QVector<Pos>::size_type greater_piece_size();
};

#endif // ALLPIECES_H
