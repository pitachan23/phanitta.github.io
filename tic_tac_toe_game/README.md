<!-- link to main stylesheet -->
<link rel="stylesheet" type="text/css" href="/style.css">

<h1> Tic-Tac-Toe Game </h1>
<h2> Player vs. Computer </h2>

This program consists of a Game Class that takes care of all the game logic. All that we need to run the game is to create a Game object and call <strong>run()</strong> in the main program. The game will continue to run until either of the player wins or gets a tie. There are 4 states to this game as called by the <strong>checkBoardState()</strong> function: incomplete, a tie, "x" won, and "o" won. 

I used a 3x3 string matrix to represent the board for Tic-Tac-Toe. The position at each location can be accessed by the indices of the matrix or a number from 0 to 8 (variable named <strong>move</strong>). I've used both "row/column" and "move" indexing interchangebly throughout the entire program. You may use <strong>getMove(int row, int col)</strong>, <strong>getRow(int move)</strong>, and <strong>getCol(int move)</strong> functions to convert between these two methods. 

<div class="center">
	<img src="/tic_tac_toe_game/images/tic-tac-toe-1.png" alt="" height="250"><br>
  <p class="caption">Row/Column and Move Indexing</p>
</div>

To check for a winner in the game, the sequence count should be either 3 in a row, in a column, or along a diagonal. The functions <strong>checkRow()</strong>, <strong>checkCol()</strong>, and <strong>checkDiag()</strong> returns 0 if there is no winner, 1 if "x" player won, and 2 if "o" player won. If one of the three conditions is satisfied, then we have a winner. The function <strong>checkWinner()</strong> takes care of this, and also returns the same thing.

<div class="row">
					<div class="column-three center">
						<img src="/tic_tac_toe_game/images/tic-tac-toe-3.png" alt="" height="250"><br>
						<p class="caption">Row</p>
				  </div>
				  <div class="column-three center">
				    		<img src="/tic_tac_toe_game/images/tic-tac-toe-4.png" alt="" height="250"><br>
						<p class="caption">Column</p>
				  </div>
				  <div class="column-three center">
				    		<img src="/tic_tac_toe_game/images/tic-tac-toe-2.png" alt="" height="250"><br>
						<p class="caption">Diagonal</p>
				  </div>
</div>

When the state of the game is incomplete, this means that 1) the game is not yet completed (or in other words, the positions of the board have not been filled up) and 2) there is no winner at the current moment. For incomplete, I checked for <strong>checkWinner() == 0</strong> and <strong>isBoardFull() == 0</strong>. Similarly for a tie, there should be no winner for the game, but in contrast to being incomplete, the board should be filled, meaning that <strong>isBoardFull() == 1</strong>. The <strong>checkBoardState()</strong> returns -1 if incomplete, 0 if tied, 1 if "x" player won, and 2 if "o" player won.

The <strong>run()</strong> will continue to loop while game is incomplete. Each time the game will check for nextPlayer, which is either "computer" or "player." The nextPlayer variable is first initialized when the Game constructor is called in the main program. The game randomly selects who goes first. The player has a choice whether he or she wants to play "x" or "o." The symbol selection will be stored in variables playerPick and compPick for the player and the computer respectively. When it's the computer's turn, it will try to get the next best move (getBestMove()) and make a move (makeMove(int row, int col, string symbol)) if the position is already not occupied. Similar things happen during the player's turn, but instead the player receives the input for the position (row/col) through the command line and make a move as long as the chosen position is empty. The function isEmpty(int row, int col) returns true if empty, otherwise returns false.

The mechanics of the game is very straightforward so far. The most complicated part of the game is writing the function getBestMove() for the AI player. Alternatively, if a player wants to plays in an easy mode, he or she may choose to replace getBestMove() with getRandMove(), which returns a random move. The best move include these considerations ranking in descending order:
1) The center position
2) A blocking move to prevent an opponent from winning, or a winning move that will make a sequence 3
3) When the above two conditions are not met, it's best to place the symbol along the same row/col/diag as the one that is already there to increase the chance of winning. 
4) If all of the above conditions are not satisfied, the computer finds a corner. If all corners are occupied, then it chooses an edge.

[include diagram]

