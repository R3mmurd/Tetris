/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <defs.H>

QVector<QVector<Pos>> make_rotations(const QVector<Pos> & r)
{
  QVector<Pos> r1 = maps(r,[](const Pos & p){return Pos(p.second, -p.first);});
  QVector<Pos> r2 = maps(r,[](const Pos & p){return Pos(-p.first, -p.second);});
  QVector<Pos> r3 = maps(r,[](const Pos & p){return Pos(-p.second, p.first);});
  return { r, r1, r2, r3 };
}
