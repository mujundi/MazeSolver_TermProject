#include <iostream>
#include <algorithm>
#include "DFSMaze.h"

/**
 * @brief creates a maze of specified dimensions generated by a
 * random depth-first search
 * @param width is the number of tiles per row
 * @param height is the number of rows
 */
DFSMaze::DFSMaze(int width, int length)
	: Maze(width, length)
{
	srand(time(NULL));

	// randomize maze generating parameters
	startingRow = rand() % width;
	startingCol = rand() % length;

	// generate maze starting at random cell
	generate_maze(startingRow, startingCol);
}

/**
 * @brief randomly selects the next cell to travel to
 * @param row is the row of the current cell
 * @param col is the column of the current cell
 * @return a char N, S, E, W depending on the chosen direction
 * or Q when there are no more tiles to visit
 */
char DFSMaze::find_available_neighbor(int row, int col)
{
	// array holds possible neighbors
	char tilesAround[4] = {'N', 'S', 'E', 'W'};
	// randomizes array
	random_shuffle(&tilesAround[0], &tilesAround[4]);

	// traverse randomized array to find next neighbor
	for(int i = 0; i < 4; ++i) {
		// if north neighbor was not passed and current row != 0
		if(row > 0 && tilesAround[i] == 'N' && !grid[row-1][col]->passed)
			return 'N';
		// if south neighbor was not passed and current row is not the last one
		else if(row+1 < height && tilesAround[i] == 'S' && !grid[row+1][col]->passed)
			return 'S';
		// if east neighbor was not passed and current column is not the last
		else if(col < width-1 && tilesAround[i] == 'E' && !grid[row][col+1]->passed)
			return 'E';
		// if west neighbor was not passed and current column != 0
		else if(col > 0 && tilesAround[i] == 'W' && !grid[row][col-1]->passed)
			return 'W';
	}
	// returns 'Q' when all cells in maze have been visited
	return 'Q';
}

/**
 * @brief recursively generates the maze at a given cell, deciding which cell to visit next
 * @param row is the row of the current cell
 * @param col is the column of the current cell
 * @return void
 */
void DFSMaze::generate_maze(int row, int col)
{
	grid[row][col]->passed = true;
	bool quit = false;

	while(!quit) {
		// determines which cell to travel to next
		char nextTile = find_available_neighbor(row, col);

		switch(nextTile) {
			// Removes wall between current cell and northern neighbor
		case 'N':
			grid[row][col]->north = false;
			grid[row-1][col]->south = false;
			generate_maze(row-1, col);
			break;
			// Removes wall between current cell and southern neighbor
		case 'S':
			grid[row][col]->south = false;
			grid[row+1][col]->north = false;
			generate_maze(row+1, col);
			break;
			// Removes wall between current cell and eastern neighbor
		case 'E':
			grid[row][col]->east = false;
			grid[row][col+1]->west = false;
			generate_maze(row, col+1);
			break;
			// Removes wall between current cell and western neighbor
		case 'W':
			grid[row][col]->west = false;
			grid[row][col-1]->east = false;
			generate_maze(row, col-1);
			break;
		default:
			quit = true;
			break;
		}
	}
}
