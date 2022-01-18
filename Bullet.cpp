#include "Bullet.h"

void Bullet::eraseBullet(Board& myBoard) {
	while (myBoard.getMatrix()[pos.x][pos.y] != '±') {
		if (myBoard.getMatrix()[pos.x][pos.y] == '|') {
			myBoard.setMatrix(pos.x, pos.y, ' ');
		}
		--pos.x;
	}
}