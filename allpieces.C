/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <allpieces.H>
# include <board.H>

QVector<QVector<QVector<Pos>>> AllPieces::all_rotations = {
  {{{0,0},{1,0},{0,1},{1,1}}}, // Square, only a rotation
  make_rotations({{0,0},{-1,0},{1,0},{0,-1}}), // T
  {{{0,0},{-1,0},{1,0},{2,0}},{{0,0},{0,-1},{0,1},{0,2}}}, // Long, only two
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

QVector<Pos>::size_type AllPieces::gr_sz_piece = 0;

Piece AllPieces::next_piece(Board * b, std::mt19937 & rng)
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
  if (gr_sz_piece > 0)
    return gr_sz_piece;

  for (const QVector<QVector<Pos>> & v : all_rotations)
    {
      auto sz = v.first().size();
      if (sz > gr_sz_piece)
        gr_sz_piece = sz;
    }
  return gr_sz_piece;
}
