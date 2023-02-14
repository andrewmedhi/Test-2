#include "maze.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {

	float seed_arg = std::stoi(argv[1], nullptr);
	int row_arg = std::stoi(argv[2], nullptr);
	int col_arg = std::stoi(argv[3], nullptr);
	std::string filename = argv[4];

	Maze new_maze(row_arg, col_arg, seed_arg, filename);

	//new_maze.Print();

	new_maze.MakeMaze();

	new_maze.Print();




}
