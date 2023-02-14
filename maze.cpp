#include "maze.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>

Maze::Maze(int num_rows, int num_cols, float the_seed, std::string the_file) {
	this->rows = num_rows;
	this->cols = num_cols;
	this->seed = the_seed;
	this->filename = the_file;
	std::srand(the_seed);
	this->GenArray();
}
int Maze::GetRows() {
	return this->rows;
}
int Maze::GetCols() {
	return this->cols;
}

void Maze::GenArray() {
	this->array = new int* [this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->array[i] = new int[this->cols];
	}

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			this->array[i][j] = 0;
		}
	}
}

int Maze::BinToDec(int n) {
	int num = n;
	int dec = 0;

	int base = 1;
	int temp = num;
	while (temp > 0) {
		int last = temp % 10;
		temp = temp / 10;
		dec += last * base;
		base *= 2;
	}
	return dec;
}

std::string	Maze::DecToBin(int n) {
	std::string r = "0000";
	for (int i = 3; i >= 0; i--) {
		int k = pow(2, i);
		if (n / k > 0) {
			r[3 - i] = '1';
			n = n % k;
		}
	}
	return r;
}



void Maze::MakeMaze() {
	std::vector<std::pair<int, int>> A;
	std::vector<std::pair<int, int>> visited;
	//forgot to add in visited


	std::vector<std::pair<int, int>> neighbors;
	//makes sure the top of the maze is open
	int decOfbin_c = 7;
	visited.push_back({ 0,0 });
	A.push_back({ 0,0 });
	this->array[0][0] = decOfbin_c;
	
	



	while (!A.empty()) {
		std::pair<int, int> current = A.back();
		A.pop_back();

		
		int first = current.first;
		int sec = current.second;
		std::pair<int, int> test;
		std::vector<char> dir;

		//first:y axis
		//sec:x axis

		//north
		test = { first - 1,sec };
		//std::cout << test.first << test.second << std::endl;
		if (test.first >= 0) {
			if (this->array[test.first][test.second] == 0) {
				neighbors.push_back(test);
				dir.push_back(0);
			}
		}
		//south
		test = { first + 1,sec };
		//std::cout << test.first << test.second << std::endl;
		if (test.first <= this->rows - 1) {
			if (this->array[test.first][test.second] == 0) {
				neighbors.push_back(test);
				dir.push_back(1);
			}
		}
		//east
		test = { first,sec + 1 };
		//std::cout << test.first << test.second << std::endl;
		if (test.second <= this->cols - 1) {
			if (this->array[test.first][test.second] == 0) {
				neighbors.push_back(test);
				dir.push_back(2);
			}
		}
		//west
		test = { first,sec - 1 };
		//std::cout << test.first << test.second << std::endl;
		if (test.second >= 0) {
			if (this->array[test.first][test.second] == 0) {
				neighbors.push_back(test);
				dir.push_back(3);
			}
			
		}
		//std::cout << "end of neighbors" << std::endl;

		if (!neighbors.empty()) {


			A.push_back(current);
			int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
			std::pair<int, int> neigh = neighbors[idx];

			int *place_c = &this->array[current.first][current.second];

			std::string binary_c = this->DecToBin(*place_c);
			std::string binary_n = "1111";

			//eliminate wall north of current
			if (dir[idx] == 0) {
				binary_c[0] = '0';
				binary_n[1] = '0';
			}
			//eliminate wall south of current
			else if (dir[idx] == 1) {
				binary_c[1] = '0';
				binary_n[0] = '0';
			}
			//eliminate wall east of current
			else if (dir[idx] == 2) {
				binary_c[2] = '0';
				binary_n[3] = '0';
			}
			//eliminate wall west of current
			else if (dir[idx] == 3) {
				binary_c[3] = '0';
				binary_n[2] = '0';
			}
			int str_c_temp = std::stoi(binary_c);
			int str_n_temp = std::stoi(binary_n);

			int binTodec_c = this->BinToDec(str_c_temp);
			int binTodec_n = this->BinToDec(str_n_temp);

			this->array[current.first][current.second] = binTodec_c;
			//std::cout << neigh.first << neigh.second << std::endl;
			this->array[neigh.first][neigh.second] = binTodec_n;
			visited.push_back(neigh);
			A.push_back(neigh);
			neighbors.clear();
		}
	}

	//make sure maze opens at the end
	int* last = &this->array[this->rows - 1][this->cols -1];
	std::string last_str = this->DecToBin(*last);
	last_str[1] = '0';
	*last = std::stoi(last_str);
	*last = this->BinToDec(*last);
	this->array[this->rows - 1][this->cols - 1] = *last;
}
 
void Maze::Print() {
	std::ofstream mazefile;
	mazefile.open(this->filename);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			mazefile << this->array[i][j] << ' ';
			std::cout << this->array[i][j] << ' ';
		}

			mazefile << std::endl;
			std::cout << std::endl;
		//delete[] this->array[i];
	}
	//delete this->array;
	mazefile.close();
}




