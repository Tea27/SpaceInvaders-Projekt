#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include "Villain.h"
#include "Player.h"
#define INITIAL 7
#define SELECTED  2
#define SCORETXT "score.txt"
#define LOGOTXT "spaceInv.txt"

class Menu {
    int Set[4];
    int counter;
    char key;

public:
    Menu() {
       for(int i = 0; i < 4; i++){ //Default colors
           Set[i] = INITIAL;
       }
       counter = 2;
    }
    void drawMenu();
    void displayMenu();
    void gotoxy(int x, int y);
    void color(int color);
    void drawInstructions();
    void displayFile(std::string fileName);
    void displayScore(std::string fileName);
    void gamePlay();
    void playerLost();
    void playerWon();
    void writeScoresToFile(std::string filename, std::vector<std::string> scores);
    void writeNewScoreToVector(int playerScore, int& pos, int position, std::vector<std::string>& scores, bool& written);
    void checkScore(std::string fileName, int playerScore);
};