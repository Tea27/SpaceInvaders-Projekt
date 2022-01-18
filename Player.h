#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Villain.h"
#include "Bullet.h"

class Player {
	std::string player;
	Position pos;
	int lives;
	int score;
	bool isShooting;

public:
	Bullet bullet;
	Player();
	int getScore() { return score; }
	void setLives() { lives--; }
	bool checkLives() { return(lives > 0); }
	bool checkShooting() { return isShooting; }
	void updateShooting() { isShooting = false; }
	void displayLives(Board& myBoard);
	void displayScore(Board& myBoard);
    Player operator()(Board& myBoard);
    void shoot(std::vector<Villain>& arr, Board& myBoard);
	bool checkKeyStrokes(Board& myBoard);
};