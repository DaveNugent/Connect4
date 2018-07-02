#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void printBoard(); // prints current board
void makeMove(int move, char player); //has player x or o place token in column move
int takeInput(); // takes first char as input
int checkForWinner(int row, int column, char player); //returns 1 if a player won, else returns 0
void twoPlayer(); // gameplay for two player
void onePlayer(); // gameplay for one player
void mainMenu (); // main menu

int BOARDSIZE = 7; //Length and width of board, top lables are hard coded in
char** gameBoard;
int gameOver = 0; // 0 until a player wins

int main(int argc, char const *argv[])
{
	// Setting up game board
	gameBoard = (char **)malloc( BOARDSIZE * sizeof(char *)); 
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		gameBoard[i] = (char *)malloc( BOARDSIZE * sizeof(char *));
	}
	// initializing all of board to ' '
	for (int i = 0; i < BOARDSIZE; ++i) 
	{
		for (int j = 0; j < BOARDSIZE; ++j)
		{
			gameBoard[i][j] = ' ';		
		}
	}

	mainMenu();
    free( gameBoard);
	return 0;
}

void printBoard(){
	printf("|1|2|3|4|5|6|7|\n"); // top lables of board
	for (int i =  0; i < BOARDSIZE; ++i) // for each column
	{
		for (int j = 0; j < BOARDSIZE; ++j) // print each row
		{
			printf("|%c", gameBoard[i][j]);
		}
	printf("|\n");
	}
	printf("|1|2|3|4|5|6|7|\n");
}

void makeMove (int column , char player){
	int row = BOARDSIZE - 1;
	// go up column until an open space is found
	while ( (gameBoard[row][column] != ' ') && (row > 0))
	{
		row--;
	}
	// when first open space is found
	if ( gameBoard[row][column] == ' ' )
	{
		// set choosen move to game board
		gameBoard[row][column] = player;
		gameOver = checkForWinner(row, column, player);
		printBoard();
	}
	else 
	{
		// ask for another option if no open spots are found
		printf("Column Full, Please choose another row\n");
		column = takeInput ();
		makeMove( column, player);
	}
}

int takeInput (){
	char move[256]; // buffer for move
	int column; //column choosen
	fgets (move, 256, stdin); //taking in move

	if( isdigit(move[0]) && move[1] == '\n' ) // making sure input is a 1 digit number
	{
		column = (int) move[0]; // setting row input
		column = column - '1'; // subtracting ascii value of 1 to get row starting at 0
		if (column >= 0 && column < BOARDSIZE) // making sure column is within range
		{
			return column;
		}
		else
		{
			printf("Move outside of bounds\n"); // if input is 1 digit number, but out of range
		}
	}
	else
	{
		printf("Unkown move, please try again\n"); // if input isn't a 1 digit number
	}
	return -1; // if takeInput fails, it returns -1
}

int checkForWinner( int row, int column, char player){
	int j;
		// check for 4 horizontal row of 4
		for (int i = -3; i < 4; i++)
		{
			j = i;
			if (((column - j) < BOARDSIZE) && (column - j > -1) && (gameBoard[row][column-j] == player))
			{
				j++;
				if (((column - j) < BOARDSIZE) && (column - j > -1) && (gameBoard[row][column-j] == player))
				{
					j++;
					if (((column - j) < BOARDSIZE) && (column - j > -1) && (gameBoard[row][column-j] == player))
					{
						j++;
						if (((column - j) < BOARDSIZE) && (column - j > -1) && (gameBoard[row][column-j] == player))
						{
						return 1;
						}
					}
				}
			}
		}
		// check for vertical row of 4
		for (int i = -3; i < 0; i++)
		{
			j = i;
			if ((((row - j) < BOARDSIZE) && (row - j) > -1) && (gameBoard[row - j][column] == player))
			{
				j++;
				if ((((row - j) < BOARDSIZE) && (row - j) > -1) && (gameBoard[row - j][column] == player))
				{
					j++;
					if ((((row - j) < BOARDSIZE) && (row - j) > -1) && (gameBoard[row - j][column] == player))					{
						j++;
						if ((((row - j) < BOARDSIZE) && (row - j) > -1) && (gameBoard[row - j][column] == player))
						{
						return 1;
						}
					}
				}
			}
		}
		// check for \ down right diagnal row of 4
		for (int i = -3; i < 0; i++)
		{
			j = i;
			if (row - j < BOARDSIZE && column - j < BOARDSIZE && row - j > -1 && column - j >-1 
				&& gameBoard[row - j][column - j] == player)
			{
				j++;
				if (row - j < BOARDSIZE && column - j < BOARDSIZE && row - j > -1 && column - j >-1 
					&& gameBoard[row - j][column - j] == player)
				{
					j++;
					if (row - j < BOARDSIZE && column - j < BOARDSIZE && row - j > -1 && column - j >-1 
						&& gameBoard[row - j][column - j] == player)
					{
						j++;
						if (row - j < BOARDSIZE && column - j < BOARDSIZE && row - j > -1 && column - j >-1 
							&& gameBoard[row - j][column - j] == player)
						{
						return 1;
						}
					}
				}
			}
		}
		// checking for / up right diagnal
		for (int i = -3; i < 0; i++)
		{
			j = i;
			if (row - j < BOARDSIZE && column + j < BOARDSIZE && row - j > -1 && column + j >-1 
				&& gameBoard[row - j][column + j] == player)
			{
				j++;
				if (row - j < BOARDSIZE && column + j < BOARDSIZE && row - j > -1 && column + j >-1 
					&& gameBoard[row - j][column + j] == player)
				{
					j++;
					if (row - j < BOARDSIZE && column + j < BOARDSIZE && row - j > -1 && column + j >-1 
						&& gameBoard[row - j][column + j] == player)
					{
						j++;
						if (row - j < BOARDSIZE && column + j < BOARDSIZE && row - j > -1 && column + j >-1 
							&& gameBoard[row - j][column + j] == player)
						{
							return 1;
						}
					}
				}
			}
		}
	return 0;
}
void mainMenu (){
	printf("Would you like to play with 1 player or 2?\n");
	char buffer [256];
	int numplayers;
	fgets (buffer, 256, stdin);
	numplayers = (int) buffer[0] - '0';
	if( (numplayers == 1) && buffer[1] == '\n' )
	{
		onePlayer();
	}
	else if ((numplayers == 2) && buffer[1] == '\n')
	{
		printBoard();
		twoPlayer();
	}
	else{
		printf("Please respond with 1 or 2 \n");
		mainMenu();
	}
}

// gameplay for two people
void twoPlayer (){
	int player = 0; // player switches between 0 and 1
	char turn; // o for player 0, x for player 1
	int column; // chosen column 

	while (!gameOver) //game play loop
	{
		column = takeInput(); //taking column input
		if (column != -1) // check for failed takeInput
		{
			if (player)
			{
				turn = 'o'; // player 1
			}
			else
			{
				turn = 'x'; // player 0
			}
			makeMove (column, turn);
			player = !player; // alternate between players
		}
	}
	printf("%c's won!\n", turn);
    for (int i = 0; i < BOARDSIZE; i++ )
    {
        free(gameBoard[i]);
    }
}

// Gameplay for one person and a random number opponent
void onePlayer (){
	srand(time(NULL));
	int randMove = -1; // random move for opponent 
	int player = 0; // player switches between 0 and 1
	char turn; // o for player 0, x for player 1
	int column; // chosen column 

	while (!gameOver) //game play loop
	{
		if (player) // when its real players turn
		{
			column = takeInput(); // take in column
				if (column != -1) // make sure takeInput succeded
				{
					turn = 'x';
					makeMove (column, turn);
					player = !player; // switch between players
				}
		}
		else
		{
			randMove = rand() % (BOARDSIZE - 1); //generate a random number between 0 - BOARDSIZE-1
			printf("Opponent chose column %i\n", randMove + 1); // prints out opponents choice
			while ( gameBoard[randMove][BOARDSIZE-1] != ' ') //making sure column isn't full
			{
				randMove = rand() % (BOARDSIZE - 1); // making new choice if first choice row full
			}
			turn = 'o';
			makeMove (randMove, turn);
			player = !player; // switch between players
		}
	}
	printf("%c's won!\n", turn); //print winner

    for (int i = 0; i < BOARDSIZE; i++ ) // freeing board
    {
        free(gameBoard[i]);
    }


}
