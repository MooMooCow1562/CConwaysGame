#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <windows.h>

const int BOARD_SIZE = 33;

int check(int xLoc, int yLoc, int dGrid[][33]) {
	int neighbors = 0;
	for (int i = xLoc - 1; i < xLoc + 2; i++)
	{
		for (int j = yLoc - 1; j < yLoc + 2; j++) {
			
			int xPrime, yPrime;

			//adjust x coordinate for wraparound.
			if (i < 0) {
				xPrime = i + BOARD_SIZE;
			}
			else if (i >= BOARD_SIZE) {
				xPrime = i - BOARD_SIZE;
			}
			else {
				xPrime = i;
			}
			
			//adjust y coordinate for wraparound.
			if (j < 0) {
				yPrime = j + BOARD_SIZE;
			}else if(j>= BOARD_SIZE) {
				yPrime = j - BOARD_SIZE;
			}
			else {
				yPrime = j;
			}


			if (xPrime == xLoc && yPrime == yLoc) {
				//do nothing
			}
			else if (dGrid[xPrime][yPrime] == 1) {
				neighbors += 1; //found a cell.
			}
		}
	}
	//	printf(" Found %d neighbors.\n", neighbors);
	return neighbors;
}

int step(int dGrid[][33], int wGrid[][33]) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int neighbors = check(i, j, dGrid);
			if (dGrid[i][j] == 1) {
				if (neighbors < 2) {
					wGrid[i][j] = 0; //cell dies.
				}
				else if (neighbors > 3) {
					wGrid[i][j] = 0; //cell dies.
				}
				else {
					wGrid[i][j] = 1; //cell lives.
				}
			}
			else {
				if (neighbors == 3) {
					wGrid[i][j] = 1; //cell is born.
				}
				else {
					wGrid[i][j] = 0; //cell remains dead.
				}
			}
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			dGrid[i][j] = wGrid[i][j]; //copy the worker grid to the display grid.
		}
	}
	return 0;
}

int printGrid(int grid[][33]) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//print an empty cell
			if (grid[i][j] == 0) {
				printf("_|");
			}
			//print a filled cell
			else if (grid[i][j] == 1) {
				printf("#|");
			}
			//an incorrect cell
			else {
				printf("/|");
			}
		}
		printf("\n");
	}
	printf("Grid printed\n");
	return 0;
}

int randomize(int grid[][33]) {
	int randInt = rand() % 2;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			grid[i][j] = randInt;
			randInt = rand() % 2; //randomize the next cell.
		}
	}
	printf("Grid randomized.\n");
	return 0;
}

int loop(int dGrid[][33], int wGrid[][33]) {
	char c = 'n';
	while (c != 'q') {
		if (c != '\n' && c != '\r') {
			printf("Enter q to quit\nenter s to progress a state\nenter r to randomize the board\n");
		}

		c = getchar();

		if (c == '\n' || c == '\r') {
			c = getchar();//consume the newline character like the little dragon you are.
		}
		//q to quit
		if (c == 'q') {
			printf("Quitting...\n");
		}
		//s to step
		else if (c == 's') {
			step(dGrid, wGrid);
			printGrid(dGrid);
			Sleep(333);
		}
		//r to randomize
		else if (c == 'r') {
			randomize(dGrid);
			printGrid(dGrid);
		}
		//incorrect input message
		else {
			printf("Invalid input. Please try again.\n");
		}
	}
	return 0;
}

int main() {
	srand(BOARD_SIZE);
	
	//Can't use BOARD_SIZE here because the compiler can't be sure that BOARD_SIZE is a defined number.
	//wtf C why
	int displayGrid[33][33];
	int workerGrid[33][33];
	
	//fill the arrays with 0 to initialize them.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			displayGrid[i][j] = 0;
			workerGrid[i][j] = 0;
		}
	}
	//and start.
	return loop(displayGrid, workerGrid);
}