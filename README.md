# Tetris: A variation of the game. For beginner game developers.

This is an example of the classic game "Tetris" with some variants.
For example, in the classic game, all of the pieces are made of four squares.
In this version (designed for a homework in the course "Programming Languages"
by University of Washington) there are two five-squares pieces,
a three-square piece and a cheat piece (one square).

How to play? The game is designed for playing with the keyboard.

The control keys are:

- Left: move the current block a position to the left.
- Right: move the current block a position to the right.
- Up: rotates the current block counterclock wise.
- Down: rotates the current block clock wise.
- U: rotates the current block 180º.
- Space bar: drop the current block. It counts for your score.
- C: Try to make cheat. It means, if your score is greater than 100 points,
  then the next piece will be the cheat piece and you'll be penalized with 100
  points less in your score.
- P: pause or resume game.
- R: reinit the game when it has finished.

The game ends according the classic game rule for ending.

System requeriments:
- C++ v14
- Qt5

Enjoy it!
