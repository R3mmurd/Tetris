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

# include <allpieces.H>
# include <board.H>

std::mt19937 AllPieces::rng(time(nullptr));

QVector<QVector<QVector<Pos>>> AllPieces::all_rotations = {
  {{{0,0},{1,0},{0,1},{1,1}}}, // Square, sólo una rotación
  make_rotations({{0,0},{-1,0},{1,0},{0,-1}}), // T
  {{{0,0},{-1,0},{1,0},{2,0}},{{0,0},{0,-1},{0,1},{0,2}}}, // Long, sólo dos
  {{{0,0},{-2,0},{-1,0},{1,0},{2,0}},{{0,0},{0,-2},{0,-1},{0,1},{0,2}}}, //
  make_rotations({{0,0},{-1,0},{0,1}}), // short L
  make_rotations({{0,0},{1,0},{0,1},{1,1},{1,2}}),
  make_rotations({{0,0},{0,-1},{0,1},{1,1}}), // L
  make_rotations({{0,0},{0,-1},{0,1},{-1,1}}), // J
  make_rotations({{0,0},{-1,0},{0,-1},{1,-1}}), // S
  make_rotations({{0,0},{1,0},{0,-1},{-1,-1}}) // Z
};

QVector<QVector<Pos>> AllPieces::cheat_piece = {{{0,0}}};

QVector<QColor> AllPieces::colors = {
  QColor(255,0,0), QColor(255,128,0), QColor(255,255,0), QColor(128,255,0),
  QColor(0,255,0), QColor(0,255,128), QColor(0,255,255), QColor(0,128,255),
  QColor(0,0,255), QColor(127,0,255), QColor(255,0,255), QColor(255,0,127)
};

Piece AllPieces::next_piece(Board * b)
{
  std::uniform_int_distribution<size_t> dist_c(0, colors.size() - 1);

  if (b->cheat())
    {
      b->uncheat();
      return Piece(b, cheat_piece, colors[dist_c(rng)]);
    }

  std::uniform_int_distribution<size_t> dist_p(0, all_rotations.size() - 1);
  return Piece(b, all_rotations[dist_p(rng)], colors[dist_c(rng)]);
}

QVector<Pos>::size_type AllPieces::greater_piece_size()
{
  QVector<Pos>::size_type ret;

  for (const QVector<QVector<Pos>> & v : all_rotations)
    {
      auto sz = v.first().size();
      if (sz > ret)
        ret = sz;
    }
  return ret;
}
