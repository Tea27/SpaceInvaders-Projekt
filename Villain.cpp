#include "Board.h"
#include "Villain.h"

using namespace std;

Villain::Villain() {
	villain = "~w~";
	isShooting = false;
}

void Villain::setVillains(vector<Villain>& arr) { 
	pos.y = 8;
	pos.x = 4;
	for (int i = 1; i < 5; i++) {
		arr.push_back(*this);
		pos.y += 16;
	}
	
}
void Villain::moveVillainsLeft(vector<Villain>& arr) {
	for (int i = 4; i < arr.size(); i++) {
		arr[i].pos.y -= 2;
	}
}
void Villain::moveVillainsRight(vector<Villain>& arr) {
	for (int i = 4; i < arr.size(); i++) {
		arr[i].pos.y += 2;
	}
}
void Villain::updateVillains(vector<Villain>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		arr[i].pos.x += 2;
	}
}
int Villain::checkArray(vector<Villain> arr) {
	
	return arr[0].getX();
	for (auto el : arr) {
		
		if (el.getX() == 24) return 0;
	}
	return 1;
}
void Villain::deleteVillain(Board& myBoard) {
	--pos.y;
	for (int i = 0; i < 5; i++) {
		myBoard.setMatrix(pos.x, pos.y++, ' '); 
	}
}
void Villain::printVillains(vector<Villain>& arr, Board& myBoard) {
	
	for (auto el : arr) {
		for (int i = 0; i < el.villain.size(); i++) {
			myBoard.setMatrix(el.pos.x, el.pos.y, el.villain[i]);
			el.pos.y++;
		}
	}
}
bool Villain::vshoot(Board& myBoard) {
	isShooting = true;
	bullet.setX(myBoard.getRows() - 2);
	bullet.setY(pos.y);
	int x = 0;
	for (x = pos.x; x < myBoard.getRows() - 2; x++) {
		if (myBoard.getMatrix()[x][pos.y] == ' ') {
			myBoard.setMatrix(x, pos.y, '|');
		}
	}
	return (myBoard.getMatrix()[x][pos.y] != ' ');
}