/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QPainter>

# include <piece.H>
# include <board.H>

Piece::Piece(Board * b, const QVector<QVector<Pos>> & r, const QColor & c)
  : board(b), rotations(r), color(c), current_rotation_index(0),
    base_pos(1, b->cols() / 2)
{
  // Empty
}

Piece::Piece(const Piece & p)
  : board(p.board), rotations(p.rotations), color(p.color),
    current_rotation_index(p.current_rotation_index), base_pos(p.base_pos)
{
  // Empty
}

Piece & Piece::operator =(const Piece & p)
{
  if (&p == this)
    return *this;

  board = p.board;
  rotations = p.rotations;
  color = p.color;
  current_rotation_index = p.current_rotation_index;
  base_pos = p.base_pos;

  return *this;
}

const QVector<Pos> & Piece::get_current_rotation() const
{
  return rotations[current_rotation_index];
}

const Pos & Piece::get_position() const
{
  return base_pos;
}

const QColor & Piece::get_color() const
{
  return color;
}

bool Piece::move(int di, int dj, int dr)
{
  if (di < 0) // You may not move to up
    return false;

  int rot_idx = current_rotation_index + dr;

  if (rot_idx < 0)
    rot_idx = (rotations.size() - abs(rot_idx)) % rotations.size();
  else
    rot_idx %= rotations.size();

  Pos new_pos = Pos(base_pos.first + di, base_pos.second + dj);

  bool invalid_move = exists(rotations[rot_idx],
                             [new_pos, this](const Pos & p) {
      int i = p.first + new_pos.first;
      int j = p.second + new_pos.second;
      if (i < 0 or j < 0 or i >= int(board->rows()) or j >= int(board->cols()))
        return true;
      return board->is_busy(i, j);
    });

  if (invalid_move)
    return false;

  current_rotation_index = rot_idx;
  base_pos = new_pos;

  return true;
}

void Piece::draw(QPainter & painter)
{
  painter.setBrush(color);
  for (const Pos & p : get_current_rotation())
    painter.drawRect((p.second + base_pos.second) * Board::SCALE,
                     (p.first + base_pos.first) * Board::SCALE,
                     Board::SCALE, Board::SCALE);
}
