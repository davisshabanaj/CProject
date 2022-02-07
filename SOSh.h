#ifndef SOSh_H
#define SOSh_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


/*
Used to activate the game. Inputs nothing and outsputs void
*/

void PlayGame();

/*c
Prints current state of the board
inputs an array for the board
outputs void
*/

void PrintBoard( char * board, int userScore1, int userScore2);

/*
Creates an empty board for the start of the game
inputs an array for the board
outputs void
*/

void InitializeGame( char * board );

void EmptyGame(char * board);

/*
Checks to make sure user entered space is empty
inputs user defined place. 
outsputs true (1) or false (0) for empty 
*/

int EmptySpace(int userSpot, char * board);

/*
Checks to make sure that the user entered value is a valid point on the array
Inputs: a user defined spot and the array,
Outputs: an int (1) = true or (0) = false if the userSpot is within a valid range within the grid
*/

int Valid(int userSpot);

/*
Gets the user Input given the correct user and a valid spot on the board that is also empty
outputs: 
*/

int userInput(int turn, char * board);

char GetUserInput(char*board, int user);

/*
Places the user Input on the array
inputs: The current player, the chosen spot, and where on the board
outputs: void
*/

void PlaceUserInput(int user, char * board, int userSpot,  char letter, char* l);

void SOS(int turn, char* board, int loc, char letter, int* userScore1, int* userScore2);

/*
Checks to see if there is a winner
*/

int Winner(int user, char * board, int loc, char letter, int userScore1, int userScore2);

void ArchiveGame( char * board );
void PrintBoardFile( FILE * fid, char * board );

void doMove(int turn, char * board);



#endif