/*
  Tetris remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <stdexcept>

# include <QPainter>

# include <allpieces.H>
# include <board.H>

const size_t Board::SCALE = 20;
const double Board::INITIAL_MOVE_DOWN_DELAY = 1.0;
const double Board::MINIMUM_MOVE_DOWN_DELAY = 0.04;

void Board::allocate()
{
  mat = new Bucket * [num_rows];

  for (size_t i = 0; i < num_rows; ++i)
    mat[i] = new Bucket[num_cols];
}

void Board::destroy()
{
  for (size_t i = 0; i < num_rows; ++i)
    delete [] mat[i];

  delete [] mat;
}

void Board::update_level()
{
  size_t new_level = score / 1000;
  level = std::max(level, new_level);
  move_down_delay = std::max(INITIAL_MOVE_DOWN_DELAY - level * 0.08,
                             MINIMUM_MOVE_DOWN_DELAY);
}

bool Board::is_line(size_t i)
{
  return all(mat[i], num_cols, [] (auto item) { return item.busy; });
}

void Board::lines(size_t idx)
{
  size_t max_lines = AllPieces::greater_piece_size();

  size_t lines_counter = 0;

  for (size_t i = 0; idx < num_rows and i < max_lines; ++i, ++idx)
    {
      if (not is_line(idx))
        continue;

      ++lines_counter;

      // Drop all pieces above
      for (size_t ip = idx; ip > 0; --ip)
        {
          bool all_over_empty = true;

          for (size_t j = 0; j < num_cols; ++j)
            {
              all_over_empty = all_over_empty and not mat[ip - 1][j].busy;
              mat[ip][j] = mat[ip-1][j];
            }

          if (all_over_empty)
            break;
        }
    }
  score += 20 * lines_counter * lines_counter;

  if (lines_counter >= 4)
    four_lines_sound->play();
  else if (lines_counter > 0)
    one_line_sound->play();
}

Board::Board(size_t r, size_t c)
  : rng(time(nullptr)), num_rows(r), num_cols(c), mat(nullptr),
    current_block(AllPieces::next_piece(this, rng))

{
  if (num_rows < 5 or num_cols < 5)
    throw std::domain_error("Size must be at least 5x5");

  one_line_sound = new QSound(":/audio/line");
  four_lines_sound = new QSound(":/audio/four_lines");
  game_over_sound = new QSound(":/audio/game_over");
  block_bottom_sound = new QSound(":/audio/hits_bottom");
  env_sound = new QSound(":/audio/music");
  env_sound->setLoops(QSound::Infinite);

  env_sound->play();

  allocate();
}

Board::~Board()
{
  destroy();
}

bool Board::is_game_over() const
{
  return game_over;
}

size_t Board::rows() const
{
  return num_rows;
}

size_t Board::cols() const
{
  return num_cols;
}

bool Board::cheat() const
{
  return _cheat;
}

bool Board::do_cheat()
{
  if (_cheat or score < 100)
    return false;

  score -= 100;
  _cheat = true;
  return true;
}

void Board::uncheat()
{
  _cheat = false;
}

void Board::reset()
{
  destroy();
  allocate();
  score = 0;
  game_over = false;
  _cheat = false;
  current_block = AllPieces::next_piece(this, rng);
  env_sound->play();
}

bool Board::is_busy(size_t i, size_t j) const
{
  return mat[i][j].busy;
}

void Board::set(size_t i, size_t j, const QColor & c)
{
  mat[i][j] = { c, true };
}

void Board::draw(QPainter & painter, bool is_paused)
{
  painter.fillRect(0, 0, num_cols * SCALE, num_rows * SCALE, Qt::darkGray);

  if (is_paused)
    return;

  current_block.draw(painter);

  for (size_t y = 0; y < num_rows; ++y)
    for (size_t x = 0; x < num_cols; ++x)
      {
        if (not is_busy(y, x))
          continue;
        painter.setBrush(mat[y][x].color);
        painter.drawRect(x * SCALE, y * SCALE, SCALE, SCALE);
      }
}

void Board::rotate_right()
{
  current_block.move(0, 0, 1);
}

void Board::rotate_left()
{
  current_block.move(0, 0, -1);
}

void Board::rotate_180()
{
  current_block.move(0, 0, 2);
}

void Board::move_right()
{
  current_block.move(0, 1, 0);
}

void Board::move_left()
{
  current_block.move(0, -1, 0);
}

void Board::move_down()
{
  if (current_block.move(1, 0, 0))
    return;

  store_current();
  block_bottom_sound->play();
}

void Board::move_down(double dt)
{
  move_down_timer += dt;
  if (move_down_timer < move_down_delay)
    return;

  move_down_timer = 0.0;

  move_down();
}

void Board::drop()
{
  while(current_block.move(1, 0, 0))
    ++score;
  store_current();
  block_bottom_sound->play();
}

void Board::store_current()
{
  const Pos & p = current_block.get_position();

  const QVector<Pos> & r = current_block.get_current_rotation();

  for (const Pos & pp : r)
    mat[p.first + pp.first][p.second + pp.second] =
    { current_block.get_color(), true };

  for (size_t i = 1; i < num_rows; ++i)
    {
      if (not is_line(i))
        continue;

      lines(i);
      break;
    }

  for (size_t j = 0; j < num_cols; ++j)
    game_over = game_over or mat[1][j].busy;

  if (game_over)
    {
      env_sound->stop();
      game_over_sound->play();
      return;
    }

  current_block = AllPieces::next_piece(this, rng);
  update_level();

}

size_t Board::get_score() const
{
  return score;
}

size_t Board::get_level() const
{
  return level;
}
