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


public:
  AllPieces() = delete;
  AllPieces(const AllPieces &) = delete;
  AllPieces & operator = (const AllPieces &) = delete;

  static Piece next_piece(Board *);
};

#endif // ALLPIECES_H
