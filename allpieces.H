/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef ALLPIECES_H
# define ALLPIECES_H

# include <random>

# include <piece.H>

class AllPieces
{
  static QVector<QVector<QVector<Pos>>> all_rotations;
  static QVector<QVector<Pos>> cheat_piece;
  static QVector<QColor> colors;
  static QVector<Pos>::size_type gr_sz_piece;

public:
  AllPieces() = delete;
  AllPieces(const AllPieces &) = delete;
  AllPieces & operator = (const AllPieces &) = delete;

  static Piece next_piece(Board *, std::mt19937 &);

  static QVector<Pos>::size_type greater_piece_size();
};

#endif // ALLPIECES_H
