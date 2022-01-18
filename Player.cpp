#include <iostream>
#include <Windows.h>
#include "Player.h"
#include <time.h>
using namespace std;

Player::Player(){
        player = "=H=";
        lives = 3;
        score = 0;
        pos.x = 25;
        pos.y = 29;
        isShooting = false;
}

Player Player::operator()(Board& myBoard) {
	for (int i = 0; i < 3; i++) {
        myBoard.setMatrix(pos.x, pos.y, player[i]);
		pos.y++;
	}
    pos.y -= 2;
        
	return *this;
}

void Player::shoot(vector<Villain>& arr, Board& myBoard) {
    isShooting = true;
    bullet.setX(pos.x-1);
    bullet.setY(pos.y);
    int y = pos.y;
    int d = 0;
 
    for (int i = pos.x - 1; i > 0; i--) {
        if (myBoard.getMatrix()[i][y] != ' ') { 
            int k = 0;
            for (auto el : arr) {
                if ((el.getY() == y) || el.getY() + 1 == y || el.getY() + 2 == y || el.getY() - 1 == y || el.getY() - 2 == y) {
                    arr.erase(arr.begin() + k);
                    el.deleteVillain(myBoard);
                    isShooting = true;
                    this->score += 10;
                
                    break;
                }
                k++;
            }
            break;
        }
        else {
            myBoard.setMatrix(i, y, '|');  
        }
    }
}

bool Player::checkKeyStrokes(Board& myBoard) {
        
    if (GetAsyncKeyState(VK_RIGHT)) {
        for (int i = 0; i < 3; i++) {
            int y2 = pos.y + 2;
            if (myBoard.getMatrix()[pos.x][y2] == ' ' && myBoard.getMatrix()[pos.x][y2 + 1] != '±') {
                myBoard.setMatrix(pos.x, pos.y-1, ' ');
                ++pos.y;
                myBoard.setMatrix(pos.x, pos.y+1, player[i]);
            }
        }
    }  

    if (GetAsyncKeyState(VK_LEFT)) {
        for (int i = 0; i < 3; i++) {
            int y2 = pos.y - 2;
            if (myBoard.getMatrix()[pos.x][y2] == ' ' && myBoard.getMatrix()[pos.x][y2 - 1] != '±') {
                myBoard.setMatrix(pos.x, pos.y+1, ' ');
                --pos.y;
                myBoard.setMatrix(pos.x, pos.y - 1, player[i]);
            }
        }
    }
    if (GetAsyncKeyState(VK_BACK)) {
        cout << "game paused...";
        system("pause>nul");
        system("cls");
    }
    if(GetAsyncKeyState(VK_ESCAPE)) {
        return 0;
    }
    else {
        return 1;
    }
}
void Player::displayLives(Board& myBoard) {
    string livesLabel = "LIVES:";
    int col = 10;
    for (int i = 0; i < livesLabel.size(); col++, i++) {
        myBoard.setMatrix(1, col, livesLabel[i]);
    }
    col += 3;
    int lives = this->lives;
    
    while (lives > 0) {
        myBoard.setMatrix(1, col, 3);
        lives--;
        col+=2;
    }
    if (lives < 3) {
        myBoard.setMatrix(1, col, ' ');
    }
   
    
}
void Player::displayScore(Board& myBoard) {
    string scoreLabel = "SCORE:";
    int col = myBoard.getCols() - 20;
    for (int i = 0; i < scoreLabel.size(); ++col, i++) {
        myBoard.setMatrix(1, col, scoreLabel[i]);
    }
    col += 3;

    string score = to_string(this->score);

    for (int i = 0; i < score.size(); i++, col++) {
        myBoard.setMatrix(1, col, score[i]);
    }

    

}