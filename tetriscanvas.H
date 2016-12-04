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

# ifndef TETRISCANVAS_H
# define TETRISCANVAS_H

# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QLabel>

# include <boardcanvas.H>

class TetrisCanvas : public QWidget
{
  Q_OBJECT

  BoardCanvas * board_canvas;

  QHBoxLayout * main_layout;
  QVBoxLayout * left_layout;
  QVBoxLayout * right_layout;

  QLabel * lbl_score;
  QLabel * lbl_status;
  QLabel * lbl_cheat;

  void init_gui();

protected:
  void keyPressEvent(QKeyEvent *) override;

public:
  TetrisCanvas(QWidget * parent = 0);

public slots:
  void slot_cheat(bool);

  void slot_status(QString);

  void slot_score(size_t);
};

#endif // TETRISCANVAS_H
