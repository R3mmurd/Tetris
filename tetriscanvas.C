/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <tetriscanvas.H>

# include <QApplication>
# include <QDesktopWidget>

void TetrisCanvas::init_gui()
{
  main_layout = new QHBoxLayout(this);

  left_layout = new QVBoxLayout;
  left_layout->addWidget(board_canvas);
  main_layout->addLayout(left_layout);

  right_layout = new QVBoxLayout;

  QString stylesheet = "color: blue; font-size: 24pt; font: bold";

  lbl_level = new QLabel("Level: 0", this);
  lbl_level->setStyleSheet(stylesheet);
  right_layout->addWidget(lbl_level);

  lbl_score = new QLabel("Score: 0", this);
  lbl_score->setStyleSheet(stylesheet);
  right_layout->addWidget(lbl_score);

  lbl_status = new QLabel("Playing", this);
  lbl_status->setStyleSheet(stylesheet);
  right_layout->addWidget(lbl_status);

  lbl_cheat = new QLabel("Cheat: off", this);
  lbl_cheat->setStyleSheet(stylesheet);
  right_layout->addWidget(lbl_cheat);

  main_layout->addLayout(right_layout);

  setLayout(main_layout);

  setStyleSheet("background: lightBlue");
  setFixedSize(board_canvas->width() + 300, board_canvas->height() + 20);

  QRect rect = QApplication::desktop()->screenGeometry();
  move(rect.width() / 2 - width() / 2, rect.height() / 2 - height() / 2);

}

void TetrisCanvas::keyPressEvent(QKeyEvent * evt)
{
  board_canvas->handle_input(evt);
}

TetrisCanvas::TetrisCanvas(QWidget * parent)
  : QWidget(parent)
{
  board_canvas = new BoardCanvas(this);
  init_gui();
  connect(board_canvas, SIGNAL(signal_cheat(bool)),
          this, SLOT(slot_cheat(bool)));
  connect(board_canvas, SIGNAL(signal_score(size_t, size_t)),
          this, SLOT(slot_score(size_t, size_t)));
  connect(board_canvas, SIGNAL(signal_status(QString)),
          this, SLOT(slot_status(QString)));
}

void TetrisCanvas::slot_cheat(bool c)
{
  if (c)
    lbl_cheat->setText("Cheat: on");
  else
    lbl_cheat->setText("Cheat: off");
}

void TetrisCanvas::slot_status(QString txt)
{
  lbl_status->setText(txt);
}

void TetrisCanvas::slot_score(size_t score, size_t level)
{
  QString txt = "Score: ";
  txt.append(QString::number(score));
  lbl_score->setText(txt);
  txt = "Level: ";
  txt.append(QString::number(level));
  lbl_level->setText(txt);
}
