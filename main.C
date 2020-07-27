/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>
# include <tetriscanvas.H>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  TetrisCanvas tetris;
  tetris.show();
  return app.exec();
}

