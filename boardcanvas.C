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

# include <boardcanvas.H>
# include <QPainter>
# include <QKeyEvent>

BoardCanvas::BoardCanvas(QWidget * parent)
  : QWidget(parent), board(30, 15)
{
  setFixedSize(board.cols() * Board::Scale, board.rows() * Board::Scale);

  timer.setInterval(base_interval);
  connect(&timer, SIGNAL(timeout()), this, SLOT(slot_timer_timeout()));
  timer.start();
}

void BoardCanvas::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(Qt::black);
  board.draw(painter);
}

void BoardCanvas::handle_input(QKeyEvent * evt)
{
  if (board.is_game_over())
    {
      if (evt->key() == Qt::Key_R)
        {
          board.reset();
          timer.start();
          emit signal_score(0, 0);
          emit signal_cheat(false);
          emit signal_status("Playing");
          repaint();
        }
      return;
    }

  if (evt->key() == Qt::Key_P)
    {
      if (not pause)
        {
          timer.stop();
          pause = true;
          emit signal_status("Pause");
        }
      else
        {
          timer.start();
          pause = false;
          emit signal_status("Playing");
        }
      return;
    }

  if (pause)
    return;

  switch(evt->key())
    {
    case Qt::Key_Right: board.move_right(); break;
    case Qt::Key_Left: board.move_left(); break;
    case Qt::Key_Down: board.rotate_right(); break;
    case Qt::Key_Up: board.rotate_left(); break;
    case Qt::Key_Space:
      board.drop();
      emit signal_score(board.get_score(), board.get_level());
      break;
    case Qt::Key_U: board.rotate_180(); break;
    case Qt::Key_C:
      if (board.do_cheat())
        {
          emit signal_cheat(true);
          emit signal_score(board.get_score(), board.get_level());
        }
      break;
    }

  repaint();
}

void BoardCanvas::slot_timer_timeout()
{
  if (board.is_game_over())
    {
      timer.stop();
      emit signal_status("Game over!");
      return;
    }

  timer.setInterval(base_interval - board.get_level() * 30);

  board.move_down();
  emit signal_cheat(board.cheat());
  emit signal_score(board.get_score(), board.get_level());
  repaint();
}
