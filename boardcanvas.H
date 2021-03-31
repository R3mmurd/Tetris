/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef BOARDCANVAS_H
# define BOARDCANVAS_H

# include <QWidget>

# include <board.H>
# include <QTime>
# include <QTimer>

class BoardCanvas : public QWidget
{
  Q_OBJECT

  Board board;

  QTimer timer;
  QTime time;

  static constexpr size_t BASE_INTERVAL = 33;

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
