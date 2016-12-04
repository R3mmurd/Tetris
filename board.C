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

# include <stdexcept>

# include <QPainter>

# include <allpieces.H>
# include <board.H>

void Board::allocate()
{
  mat = new Bucket * [num_rows];

  for (size_t i = 0; i < num_rows; ++i)
    mat[i] = new Bucket[num_cols];
}

void Board::destroy()
{
  for (size_t i = 0; i < num_rows; ++i)
    delete [] mat[i];

  delete [] mat;
}

Board::Board(size_t r, size_t c)
  : num_rows(r), num_cols(c), mat(nullptr),
    current_block(AllPieces::next_piece(this))

{
  if (num_rows < 5 or num_cols < 5)
    throw std::domain_error("Size must be at least 5x5");

  allocate();
}

Board::~Board()
{
  destroy();
}

bool Board::is_game_over() const
{
  return game_over;
}

size_t Board::rows() const
{
  return num_rows;
}

size_t Board::cols() const
{
  return num_cols;
}

bool Board::cheat() const
{
  return _cheat;
}

bool Board::do_cheat()
{
  if (_cheat or score < 100)
    return false;

  score -= 100;
  _cheat = true;
  return true;
}

void Board::uncheat()
{
  _cheat = false;
}

void Board::reset()
{
  destroy();
  allocate();
}

bool Board::is_busy(size_t i, size_t j) const
{
  return mat[i][j].busy;
}

void Board::set(size_t i, size_t j, const QColor & c)
{
  mat[i][j] = { c, true };
}

void Board::draw(QPainter & painter)
{
  painter.fillRect(0, 0, num_cols * Scale, num_rows * Scale, Qt::darkGray);
  current_block.draw(painter);

  for (size_t y = 0; y < num_rows; ++y)
    for (size_t x = 0; x < num_cols; ++x)
      {
        if (not is_busy(y, x))
          continue;
        painter.setBrush(mat[y][x].color);
        painter.drawRect(x * Scale, y * Scale, Scale, Scale);
      }
}

void Board::rotate_right()
{
  current_block.move(0, 0, 1);
}

void Board::rotate_left()
{
  current_block.move(0, 0, -1);
}

void Board::rotate_180()
{
  current_block.move(0, 0, 2);
}

void Board::move_right()
{
  current_block.move(0, 1, 0);
}

void Board::move_left()
{
  current_block.move(0, -1, 0);
}

void Board::move_down()
{
  if (current_block.move(1, 0, 0))
    return;

  store_current();
}

void Board::drop()
{
  while(current_block.move(1, 0, 0))
    ++score;

  store_current();
}

void Board::store_current()
{
  const Pos & p = current_block.get_position();

  const QVector<Pos> & r = current_block.get_current_rotation();

  for (const Pos & pp : r)
    mat[p.first + pp.first][p.second + pp.second] =
    { current_block.get_color(), true };

  for (size_t i = 1; i < num_rows; ++i)
    {
      bool line = true;

      for (size_t j = 0; j < num_cols; ++j)
        line = line and mat[i][j].busy;

      if (not line)
        continue;

      score += 50;

      for (size_t ip = i; ip > 0; --ip)
        for (size_t j = 0; j < num_cols; ++j)
          mat[ip][j] = mat[ip - 1][j];
    }

  for (size_t j = 0; j < num_cols; ++j)
    game_over = game_over or mat[1][j].busy;

  if (not game_over)
    current_block = AllPieces::next_piece(this);
}

size_t Board::get_score() const
{
  return score;
}
