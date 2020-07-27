/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <boardcanvas.H>
# include <QPainter>
# include <QKeyEvent>

const size_t BoardCanvas::MIN_TIME_INTERVAL = 40;
const size_t BoardCanvas::BASE_INTERVAL = 1000;

BoardCanvas::BoardCanvas(QWidget * parent)
  : QWidget(parent), board(30, 15)
{
  setFixedSize(board.cols() * Board::Scale, board.rows() * Board::Scale);

  timer.setInterval(BASE_INTERVAL);
  connect(&timer, SIGNAL(timeout()), this, SLOT(slot_timer_timeout()));
  timer.start();
}

void BoardCanvas::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(Qt::black);
  board.draw(painter, pause);
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
      repaint();
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

  timer.setInterval(std::max(BASE_INTERVAL - board.get_level() * 80,
                             MIN_TIME_INTERVAL));

  board.move_down();
  emit signal_cheat(board.cheat());
  emit signal_score(board.get_score(), board.get_level());
  repaint();
}
