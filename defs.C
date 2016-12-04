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

# include <defs.H>

QVector<QVector<Pos>> make_rotations(const QVector<Pos> & r)
{
  QVector<Pos> r1 = maps(r,[](const Pos & p){return Pos(p.second, -p.first);});
  QVector<Pos> r2 = maps(r,[](const Pos & p){return Pos(-p.first, -p.second);});
  QVector<Pos> r3 = maps(r,[](const Pos & p){return Pos(-p.second, p.first);});
  return { r, r1, r2, r3 };
}
