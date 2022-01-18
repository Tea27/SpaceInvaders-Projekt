#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Board.h"
#include "Bullet.h"
class Villain {
	std::string villain;
	Position pos;
	bool isShooting;

public:
	Bullet bullet;
	Villain();
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	void setY(int y) { pos.y = y; }
	bool checkShooting() { return isShooting; }
	void updateShooting() { isShooting = false; }
	int checkArray(std::vector<Villain> arr);
	void moveVillainsLeft(std::vector<Villain>& arr);
	void moveVillainsRight(std::vector<Villain>& arr);
	void setVillains(std::vector<Villain>& arr);
	void updateVillains(std::vector<Villain>& arr);
	void deleteVillain(Board& myBoard);
	bool vshoot(Board& myBoard);
	void printVillains(std::vector<Villain>& arr, Board& myBoard);
};