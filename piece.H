/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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
