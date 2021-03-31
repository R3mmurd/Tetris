# Tetris

This is a remake of the classic game [Tetris](https://en.wikipedia.org/wiki/Tetris)
with some variants. In the classic game, all of the pieces are made of four squares.
In this version (designed for a homework in the course "Programming Languages"
by University of Washington) there are two five-squares pieces,
a three-square piece and a cheat piece (one square).

## How to play

The game is designed for playing with the keyboard. Control keys are:

- Left arrow: move the current block a position to the left.
- Right arrow: move the current block a position to the right.
- Up arrow: rotates the current block counterclockwise.
- Down arrow: move the current block down a position.
- U: rotates the current block 180º.
- Space bar: drop the current block. It counts for your score.
- C: Try to make cheat. It means if your score is greater than 100 points,
  then the next piece will be the cheat piece and you'll be penalized with 100
  points less in your score.
- P: pause or resume the game.
- R: restart the game when it has finished.

he game ends according to the classic game rule for ending.

## Requirements

- C++ v14 or higher
- Qt5
