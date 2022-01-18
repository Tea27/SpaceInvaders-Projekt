#pragma once
#include "Board.h"

class Bullet {
	Position pos;

public:
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	void setX(int x) { pos.x = x; }
	void setY(int y) { pos.y = y; }
	void eraseBullet(Board& myBoard);
};