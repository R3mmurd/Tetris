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

# ifndef BOARDCANVAS_H
# define BOARDCANVAS_H

# include <QWidget>

# include <board.H>
# include <QTimer>

class BoardCanvas : public QWidget
{
  Q_OBJECT

  Board board;

  QTimer timer;

  static const size_t MIN_TIME_INTERVAL;
  static const size_t BASE_INTERVAL;

  bool pause = false;

public:
  BoardCanvas(QWidget * parent = 0);

  void handle_input(QKeyEvent *);

protected:
  void paintEvent(QPaintEvent *) override;

signals:
  void signal_score(size_t, size_t);

  void signal_cheat(bool);

  void signal_status(QString);

public slots:
  void slot_timer_timeout();
};

#endif // BOARDCANVAS_H
