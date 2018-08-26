<h1> Tic-Tac-Toe Game </h1>
<h2> Player vs. Computer </h2>

This program consists of a Game Class that takes care of all the game logic. All that we need to run the game is to create a Game object and call <strong>run()</strong> in the main program. The game will continue to run until either of the player wins or gets a tie. There are 4 states to this game as called by the <strong>checkBoardState()</strong> function: incomplete, a tie, "x" won, and "o" won. 

I used a 3x3 string matrix to represent the board for Tic-Tac-Toe. The position at each location can be accessed by the indices of the matrix or a number from 0 to 8 (variable named <strong>move</strong>). I've used both "row/column" and "move" indexing interchangebly through the entire program.
[include diagram here]

To check for a winner in the game, the sequence count should be either 3 in a row, in a column, or along a diagonal. The functions <strong>checkRow()</strong>, <strong>checkCol()</strong>, and <strong>checkDiag()</strong> returns 0 if there is no winner, 1 if "x" player won, and 2 if "o" player won. If one of the three conditions is satisfied, then we have a winner. The function <strong>checkWinner()</strong> takes care of this, and also returns the same thing.

When the state of the game is incomplete, this means that 1) the game is not yet completed (or in other words, the positions of the board have not been filled up) and 2) there is no winner at the current moment. For incomplete, I checked for <strong>checkWinner() == 0</strong> and <strong>isBoardFull() == 0</strong>. Similarly for a tie, there should be no winner for the game, but in contrast to being incomplete, the board should be filled, meaning that <strong>isBoardFull() == 1</strong>. 


