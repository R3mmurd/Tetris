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

# ifndef BOARD_H
# define BOARD_H

# include <QColor>
# include <QSound>

# include <piece.H>

class QPainter;

class Board
{
public:
  static constexpr size_t Scale = 20;

  struct Bucket
  {
    QColor color = Qt::transparent;
    bool busy = false;
  };

private:
  std::mt19937 rng;

  size_t num_rows;
  size_t num_cols;
  Bucket ** mat;
  size_t score = 0;
  size_t level = 0;
  bool game_over = false;
  bool _cheat = false;
  Piece current_block;

  void allocate();

  void destroy();

  void update_level();

  bool is_line(size_t i);

  void lines(size_t idx);

  QSound * one_line_sound;
  QSound * four_lines_sound;
  QSound * game_over_sound;
  QSound * block_bottom_sound;
  QSound * env_sound;

public:
  Board(size_t r, size_t c);

  ~Board();

  Board(const Board &) = delete;

  Board & operator = (const Board &) = delete;

  bool is_game_over() const;

  size_t rows() const;

  size_t cols() const;

  bool cheat() const;

  bool do_cheat();

  void uncheat();

  void reset();

  bool is_busy(size_t, size_t) const;

  void set(size_t, size_t, const QColor &);

  void draw(QPainter &, bool);

  void rotate_right();

  void rotate_left();

  void rotate_180();

  void move_right();

  void move_left();

  void move_down();

  void drop();

  void store_current();

  size_t get_score() const;

  size_t get_level() const;
};

# endif // BOARD_H
