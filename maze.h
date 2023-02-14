#include <vector>
#include <utility>
#include <string>

class Maze {
private:
	int rows;
	int cols;
	float seed;
	std::string filename;
	void GenArray();
	int BinToDec(int n);
	std::string DecToBin(int n);

public:
	Maze(int num_rows, int num_cols, float seed, std::string the_file);
	int GetRows();
	int GetCols();
	void Print();
	void MakeMaze();
	int **array;
};