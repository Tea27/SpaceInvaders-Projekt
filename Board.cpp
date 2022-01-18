#include "Board.h"

using namespace std;

void Board::allocateMatrix(int rows, int cols) {
	matrix = new char* [rows];

	for (int i = 0; i < rows; i++)
		matrix[i] = new char[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0 || i == 3 || j == 0 || j == cols - 1 || i == rows - 1) {
				matrix[i][j] = '±';
			}
			else {
				matrix[i][j] = ' ';
			}	
		}
	}
}

Board::Board() {
	rows = 27;
	cols = 70;
	allocateMatrix(rows, cols);
}

Board::~Board() {
	rows = 0;
	cols = 0;

	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void Board::display()
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			cout << matrix[i][j];
		}
		cout << "\n";
	}
}

void Board::clearBoard() {
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (matrix[i][j] != '±') {
				matrix[i][j] = ' ';
			}
			
		}

	}
}