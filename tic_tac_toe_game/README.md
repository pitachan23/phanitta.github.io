<h1> Tic-Tac-Toe Game </h1>
<h2> Player vs. Computer </h2>

This program consists of a Game Class that takes care of all the game logic. All that we need to run the game is to create a Game object and call <strong>run()</strong> in the main program. The game will continue to run until either of the player wins or gets a tie. There are 4 states to this game as called by the <strong>checkBoardState()</strong> function: incomplete, a tie, "x" wins, and "o" wins. 

I used a 3x3 string matrix to represent the board for Tic-Tac-Toe. The position at each location can be accessed by the indices of the matrix or a number from 0 to 8 (variable called <strong>move</strong>). I've used both "row/column" and "move" indexing interchangebly through the entire program.
[include diagram here]

To check for a winner in the game, the sequence count should be 3 either in a row, in a column, or along a diagonal. If one of the three conditions is satisfied, then we have a winner. The functions <strong>checkRow()</strong>, <strong>checkCol()</strong>, and <strong>checkDiag()</strong> 

