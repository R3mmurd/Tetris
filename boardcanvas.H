/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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
