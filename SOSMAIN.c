#include "SOSh.h"

/*
playGame: Calls all the functions that were implemented in order to play Tic-Tac-Toe with two users
Inputs: None
Outputs: void
*/

void PlayGame(){
    //Initialization of all variables 
    int turn = 0;
    char board[36];
    char letter, l; 
    int loc;
    int userScore1 = 0;
    int userScore2 = 0;
    // prints out inital board with no input
    InitializeGame( board );
        // runs code while there is no winner, checks for winner each time
        while( !Winner(turn, board, loc, letter, userScore1, userScore2) ){
        // gets location in the array from userInput function
        loc = userInput(turn, board);
        // places the user provided letter in the user provided location
        PlaceUserInput(turn, board, loc, letter, &l);
        // tests to see if "SOS" was formed 
        SOS(turn, board, loc, l, &userScore1, &userScore2);
        // prints out the board after user gives location and letter
        PrintBoard( board, userScore1, userScore2 );
        // updates player
        turn++;
        }
        // makes a file of the game after a winner is found
        ArchiveGame( board );

    return;
}
/* 
Initalizes the game board to blank spaces and greets the players
Inputs: board
Outputs: void
*/

void InitializeGame( char *board ){
    int userScore1 = 0, userScore2 = 0;
    for(int i = 0; i < 36; i++){
        // places blank spots in all the board spots
        board[i] = ' ';
    }

    printf("Welcome to SOS!\n");
    printf("Each player will pick either S or O on their turn.\n");
    // prints out the blank board
    PrintBoard( board, userScore1, userScore2 );

    return;
}
/*
Prints out the board with any given state
Inputs: board and userScores
Outputs: void
*/
void PrintBoard( char * board, int userScore1, int userScore2){

    int i;
	int j = 0;
	for( i = 0; i < 36; i++ ){
		if( i % 6 == 0 ){
		// first row - print out location numbers
		printf(" %2d     |%2d     |%2d     |%2d     |%2d    |%2d     \n", i+1, i+2, i+3, i+4, i+5,i+6);
		}
		else if( i % 6 == 1 ){
			// middle row - print out the current user values stored on the board
			printf("   %c    |   %c   |   %c   |   %c   |   %c  |   %c   \n", board[j], board[j+1], board[j+2],board[j+3],board[j+4],board[j+5]);
			printf("        |       |       |       |      |    \n");
			printf("------------------------------------------------\n");
             j += 6;
		} 
    }
    // displays the userScores after each turn
    printf("Player 1 has %d points\nPlayer 2 has %d points\n", userScore1, userScore2);
	return;
}

/*
Checks to make sure that the user space is blank
Inputs: location and board
Outputs: if the location is empty
*/

int EmptySpace(int loc, char *board){
    return board[loc-1] == ' ';
}

/*
ValidLocation: checks if a location is valid
Inputs: an integer corresponding to a location on the board
Outputs: an integer 1 (true) or 0 (false) if the location is between 1 and 9 inclusive
*/
int Valid(int loc){
    if(loc >= 1 && loc <= 36);
    return 0;
}

/*
userInput: Prompts the appropriate user for a location to place S or O. User validation is
    performed to make sure the location is valid
Inputs: an integer corresponding to the turn order and a character array containing 36 locations
Outputs: an integer corresponding to their chosen turn
*/
int userInput( int turn, char * board){

    int loc;
    // even numbers = player 1, odd numbers = player 2
    // prompts user for a location
    printf("Player %d, please pick a location: ", (turn % 2) + 1);
    scanf("%d", &loc);
    // checks to see if the location is a valid move
    if( (!Valid( loc ) && !EmptySpace( loc, board))){
		printf("Sorry, Invalid Location, please reenter or try again\n");
		printf("Player %d, choose a location: \n", ((turn % 2) + 1));
		scanf(" %d", &loc);
    }

    return loc;
}

/*
PlaceUserInput: Places the user input onto the board, promtps user for a letter to place
Inputs: the userturn, board, location on the board, letter, and a pointer assigned to letter
Outputs: void
*/
void PlaceUserInput(int turn, char *board, int loc, char letter, char* l){
    printf("Please pick either S or O:\n");
    scanf(" %c", &letter);
    *l = letter;
// assings lower or uppercase 's' to uppercase S
if( *l == 'S' || *l == 's'){
    *l = 'S';
}
// assings lower or uppercase 'o' to uppercase O
if( *l == 'O' || *l == 'o'){
    *l = 'O';
}
// checks to see if the user letter is either S or O. Reprompts if it is not
if( *l != 'S' && *l != 'O'){
    printf("Incorrect letter chosen, please pick either S or O:\n");
    scanf(" %c", &letter);
    *l = letter;
}
// places user letter on the array
    board[loc - 1] = letter;
    // assigns the letter to point l to be used in other function
    //*l = letter;
    return;
}

/*
Checks to see if there is an "SOS" formed within the array
Inputs: User Turn, board, location, letter from previous function, userScores
Outputs: Void
*/
void SOS(int turn, char* board, int loc, char letter, int* userScore1, int* userScore2){
    // initializes sos to 0, sos will count how many sos were made during a turn
    int sos = 0;
    // checks all possible combos for SOS given that the user input was S
    if( letter == 'S'){

        // checks horizontal right
        // discludes side values
    if( loc != 1 && loc != 7 && loc != 13 && loc != 19 && loc != 25 && loc != 31 ){
        if( (board[loc - 3] == 'S') && board[loc - 2] == 'O'){
            printf("Player played %c at %d\n", letter, loc);
            sos++;
        }
    }

        // checks horizontal left
        // discludes side values 
    if( loc != 6 && loc != 12 && loc != 18 && loc != 24 && loc != 30 && loc != 36 ){
        if( (board[loc - 1] == 'S') && (board[loc] == 'O')){
            sos++;
        }
    }

        //checks up
        if( (board[loc - 7] == 'O') && (board[loc - 13] == 'S')){
            sos++;
        } 

        // checks down
        if( (board[loc + 5] == 'O') && (board[loc + 11] == 'S')){
            sos++;
        }

    if( loc != 1 && loc != 7 && loc != 13 && loc != 19 && loc != 25 && loc != 31 ){
        // checks on the negative diagonal, up
        if( (board[loc - 15] == 'S') && (board[loc - 8] == 'O') ){
            printf("Player played %c at %d\n", letter, loc);
            sos++;
        }
    }

    if( loc != 6 && loc != 12 && loc != 18 && loc != 24 && loc != 30 && loc != 36 ){
        // checks on the negative diagonal, down
        if( (board[loc + 13] == 'S') && (board[loc + 6] == 'O')){
            sos++;
        }
    }

    if( loc != 1 && loc != 7 && loc != 13 && loc != 19 && loc != 25 && loc != 31 ){
        // checks on the postive diagonal, down
        if(( board[loc + 4] == 'O') && (board[loc + 9] == 'S')){
            sos++;
        }
    }

    if( loc != 6 && loc != 12 && loc != 18 && loc != 24 && loc != 30 && loc != 36 ){
        // checks on the postive diagonal, up
        if( (board[loc - 6] == 'O') && (board[loc - 11] == 'S')){
            sos++;
        } 
    }
}
    // checks if an SOS was made given user input was O
    else if( letter == 'O'){

        // checks up and down from center O
        if( (board[ loc + 5] == 'S') && (board[loc - 7] == 'S')){
            sos++;
        }

    if( loc != 6 && loc != 12 && loc != 18 && loc != 24 && loc != 30 && loc != 36 ){
        // checks negative diagonal up and down from center O
        if( (board[ loc + 6] == 'S') && (board[loc - 8] == 'S')){
            sos++;
        }
    }

    if( loc != 1 && loc != 7 && loc != 13 && loc != 19 && loc != 25 && loc != 31 ){
        // checks postive diagonal up and down from center O
        if( (board[ loc + 4] == 'S') && (board[loc - 6] == 'S')){
            sos++;
        }
    }
    if(loc != 1 && loc != 7 && loc != 13 && loc != 19 && loc != 25 && loc != 31 && loc != 6 && loc != 12 && loc != 18 && loc != 24 && loc != 30 && loc != 36)
        // checks left and right from center O
        if( (board[ loc - 2] == 'S') && (board[loc] == 'S')){
            sos++;
        }
    }
    // updates userScore for player 1
    if((turn % 2) + 1 == 1){
    *userScore1 = *userScore1 + sos;
    }

    // updates userScore for player 2
    else{
    *userScore2 = *userScore2 + sos;
    }

    return;
}

/*
Checks to see if there is a winner, given that the maximum amount of terms were used
Inputs: User turn, board, location, letter, and the userScores
Outputs: 1 if there is a winner, 0 if there is no winner
*/
int Winner(int turn, char* board, int loc, char letter, int userScore1, int userScore2){
    // assigns the total amount of turns
    int TOTALTURNS = 36;
    // checks to see if the total amount of turns have been used
    if( turn == TOTALTURNS ){
        printf("Game is over. \n");
            //Assigns the winner after comparing scores of both users
            if(userScore1 > userScore2){
                printf("Player 1 wins with a score of %d\n", userScore1);
            }
            else if(userScore2 > userScore1){
                printf("Player 2 wins with a score of %d\n", userScore2);
            }
            else if(userScore1 == userScore2){
                printf("Game is a draw\n");
            }
            return 1;
    }
    // if no winner is found, game will continue
    else{
        return 0;
    }

}

/*
ArchiveGame: Archives the game to a file to keep track of each game
Inputs: a character array containing 36 locations (one location per square)
Outputs: void
*/
void ArchiveGame( char * board ){
	// open a file using append properties to keep archiving each game without erasing the previous one
	FILE * fid = fopen("SOS.txt", "a+");
	
	// print out some introduction information
	fprintf(fid, "SOS Game\n");
	
	// write the final state the board to the file
	PrintBoardFile( fid, board );
	fprintf(fid, "\n\n\n");
	
	// close the file
	fclose(fid);
	
	return;
}


/*
PrintBoardFile: Prints the current state of the board to a file
    Same as PrintBoard, but prints to a file, not the terminal
Inputs: a file pointer to the file, a character array containing 36 locations (one location per square)
Outputs: void
*/
void PrintBoardFile( FILE * fid, char * board ){
	
	int i;
	int j = 0;
	for( i = 0; i < 36; i++ ){
		if( i % 6 == 0 ){
		// first row - print out location numbers
		fprintf(fid, " %2d     |%2d     |%2d     |%2d     |%2d    |%2d     \n", i+1, i+2, i+3, i+4, i+5,i+6);
		}
		else if( i % 6 == 1 ){
			// middle row - print out the current user values stored on the board
			fprintf(fid, "   %c    |   %c   |   %c   |   %c   |   %c  |   %c   \n", board[j], board[j+1], board[j+2],board[j+3],board[j+4],board[j+5]);
			fprintf(fid, "        |       |       |       |      |    \n");
			fprintf(fid, "------------------------------------------------\n");
             j += 6;
		} 
	}
	return;
}