/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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

  QLabel * lbl_level;
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

  void slot_score(size_t, size_t);
};

#endif // TETRISCANVAS_H
