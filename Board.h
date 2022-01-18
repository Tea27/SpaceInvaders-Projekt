#pragma once
#include <iostream>

class Position {
public:
	int x, y;
};

class Board {
	int rows, cols;
	bool gameruning = true;
	char** matrix;

public:
	Board();
	~Board();
	int getCols() { return cols; }
	int getRows() { return rows; };
	char** getMatrix() { return matrix; }
	void setMatrix(int x, int y, char ch) { matrix[x][y] = ch; };
	void display();
	void allocateMatrix(int row, int col);
	void clearBoard();
};

