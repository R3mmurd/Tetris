/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef BOARD_H
# define BOARD_H

# include <random>

# include <QColor>
# include <QSound>

# include <piece.H>

class QPainter;

class Board
{
public:
  static const size_t SCALE;
  static const double INITIAL_MOVE_DOWN_DELAY;
  static const double MINIMUM_MOVE_DOWN_DELAY;

  struct Bucket
  {
    QColor color = Qt::transparent;
    bool busy = false;
  };

private:
  std::mt19937 rng;

  size_t num_rows;
  size_t num_cols;
  Bucket ** mat;
  size_t score = 0;
  size_t level = 0;
  bool game_over = false;
  bool _cheat = false;
  Piece current_block;

  double move_down_timer = 0.0;
  double move_down_delay = INITIAL_MOVE_DOWN_DELAY;

  void allocate();

  void destroy();

  void update_level();

  bool is_line(size_t i);

  void lines(size_t idx);

  QSound * one_line_sound;
  QSound * four_lines_sound;
  QSound * game_over_sound;
  QSound * block_bottom_sound;
  QSound * env_sound;

public:
  Board(size_t r, size_t c);

  ~Board();

  Board(const Board &) = delete;

  Board & operator = (const Board &) = delete;

  bool is_game_over() const;

  size_t rows() const;

  size_t cols() const;

  bool cheat() const;

  bool do_cheat();

  void uncheat();

  void reset();

  bool is_busy(size_t, size_t) const;

  void set(size_t, size_t, const QColor &);

  void draw(QPainter &, bool);

  void rotate_right();

  void rotate_left();

  void rotate_180();

  void move_right();

  void move_left();

  void move_down();

  void move_down(double dt);

  void drop();

  void store_current();

  size_t get_score() const;

  size_t get_level() const;
};

# endif // BOARD_H
