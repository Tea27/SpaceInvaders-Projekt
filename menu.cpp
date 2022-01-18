#include "menu.h"

using namespace std;

void Menu::color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Menu::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Menu::drawMenu() {
    gotoxy(10, 2); displayFile(LOGOTXT);
    gotoxy(25, 12); cout << " ±±±±±±±±±±±±±±±±±±±±±±±±±± ";
    gotoxy(25, 13); cout << " ±                        ± ";
    gotoxy(25, 14); cout << " ±      . . . . . .       ± ";
    gotoxy(25, 15); cout << " ±                        ± ";
    gotoxy(25, 16); cout << " ± "; color(Set[0]); cout << "  1. Start Game       ";color(INITIAL); cout << " ± ";
    gotoxy(25, 17); cout << " ± "; color(Set[1]); cout << "  2. Instructions     ";color(INITIAL); cout << " ± ";
    gotoxy(25, 18); cout << " ± "; color(Set[2]); cout << "  3. Score            ";color(INITIAL); cout << " ± ";
    gotoxy(25, 19); cout << " ± "; color(Set[3]); cout << "  4. Quit              ";color(INITIAL); cout << "± ";
    gotoxy(25, 20); cout << " ±                        ± ";
    gotoxy(25, 21); cout << " ±±±±±±±±±±±±±±±±±±±±±±±±±± ";
}

void Menu::drawInstructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Press spacebar to shoot";
    cout << "\n Press right key (>) to go right";
    cout << "\n Press left key (<) to go left";
    cout << "\n Press escape key (Esc) to end the game";
    cout << "\n Press backspace key (<- Backspace) to pause the game";
    cout << "\n\nPress any key to go back to menu";
    _getch();
    system("cls");
}

void Menu::displayFile(string fileName) {
    string line = " ";
    ifstream inFile;
    inFile.open(fileName);
    int x = 4;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            color(SELECTED);gotoxy(10, x);cout << line << endl;
            x++;
        }
    }
    else {
        cout << "File failed to display" << endl;
    }
    color(INITIAL);
    inFile.close();
}

void Menu::displayScore(string fileName) {
    system("cls");
    color(SELECTED);gotoxy(10, 2);cout << "Leading Board: " << endl;
    gotoxy(10, 3);cout << "---------" << endl;
    displayFile(SCORETXT);
    system("pause>nul");
}

void Menu::displayMenu() {
    Set[1] = SELECTED; 
    
    while (true){
        
        drawMenu();
        key = _getch();
        if (key == 72 && counter > 1){ //up
            counter--;
        }
        if (key == 80 && counter < 4){ //down
            counter++;
        }
        if (key == '\r') { //enter
            switch (counter) {
            case 1:
                system("cls");
                Set[0] = INITIAL;
                gamePlay();
                break;
            case 2:
                drawInstructions();
                break;
            case 3:
                displayScore(SCORETXT);
                system("cls");
                break;
            case 4:
                exit(0);
                break;
            }
        }

        Set[0] = Set[1] = Set[2] = Set[3] = INITIAL;

        switch (counter) {
        case 1:
            Set[0] = SELECTED;
            break;
        case 2:
            Set[1] = SELECTED;
            break;
        case 3:
            Set[2] = SELECTED;
            break;
        case 4:
            Set[3] = SELECTED;
            break;
        }
    }
    
}

void Menu::playerLost() {
    Sleep(200);
    system("cls");
    gotoxy(15, 15);cout << "YOU LOST";
    system("pause>nul");
    system("cls");
}

void Menu::playerWon() {
    Sleep(200);
    system("cls");
    gotoxy(15, 15); cout << "YOU WON";
    system("pause>nul");
    system("cls");
}

void Menu::gamePlay() {
    Board myBoard;
    Villain villain;
    Player player;
    player(myBoard);
    vector<Villain> arr;
    Bullet b;
    int move = 0;
    using clock = chrono::steady_clock;
    auto startTime = clock::now();
    auto roundTime = clock::now();
    auto seconds = 0;
    villain.updateVillains(arr);
    villain.setVillains(arr);
    
    while (player.checkLives() && (villain.checkArray(arr) <= 24)) {

        gotoxy(0, 0);

        player.displayLives(myBoard);
        player.displayScore(myBoard);
        
        auto currentTime = clock::now();
        int timepassed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
        seconds = chrono::duration_cast<chrono::seconds>(currentTime - roundTime).count();
     

        if (timepassed >= 14) {
            seconds += 1;
        }
        if (timepassed >= 30) {
            seconds += 2;
        }
        
        myBoard.display();
        villain.printVillains(arr, myBoard);

        if (player.checkShooting()) {
            player.updateShooting();
            player.bullet.eraseBullet(myBoard);
        }
        if (villain.checkShooting()) {
            villain.updateShooting();
            villain.bullet.eraseBullet(myBoard);
        }
        
        if (seconds == 2 || seconds == 4 || seconds == 6 ) {
            int random = rand() % arr.size();
            villain = arr[random];
            if (villain.vshoot(myBoard)) {
                player.setLives();
            }
            
        }
        
        if (GetAsyncKeyState(VK_SPACE)) {
            player.shoot(arr, myBoard);
            if (!arr.size()) {
                playerWon();
                checkScore(SCORETXT, player.getScore());
                displayMenu();
            }
        }
        if (!player.checkKeyStrokes(myBoard)) {
            system("cls");
            break;
        }

        if (seconds >= 6) {
            if (move > 2) move = 0;

            villain.updateVillains(arr);
            villain.setVillains(arr);
            myBoard.clearBoard();
            player(myBoard);

            switch (move) {
            case 0:
                villain.moveVillainsLeft(arr);
                break;
            case 1:
                villain.moveVillainsRight(arr);
                break;
            case 2:
                villain.moveVillainsRight(arr);
                break;
            }

            ++move;

            int random = rand() % arr.size();
            villain = arr[random];
            if (villain.vshoot(myBoard)) {
                player.setLives();
            }

            roundTime = clock::now();
        }

        Sleep(200);
    }
    if (!player.checkLives() || (villain.checkArray(arr) == 26)) {
        playerLost();
    }
    displayMenu();
}

void Menu::writeScoresToFile(string filename, vector<string> scores) {
    ofstream outfile;
    outfile.open(filename);
    if (!outfile.is_open()) {
        cout << "File failed to display";
    }
    else {
        for (auto el : scores) {
            outfile << el;
        }
    }
}
void Menu::writeNewScoreToVector(int playerScore, int& pos, int position, vector<string>& scores, bool& written) {
    string newScore = "    " + to_string(playerScore) + "\n";
    pos = position - 1;
    scores.insert(scores.begin() + (pos * 2), newScore);
    written = true;
}

void Menu::checkScore(string fileName, int playerScore) {
    color(SELECTED);
    string line, word;
    vector<string> scores;
    ifstream inFile;
    bool written = false;
    int count = 1, score = 0, position = 0, pos = 0;
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            scores.push_back(line);
            scores.push_back("\n");
            ++position;
            stringstream s(line);
            while (s >> word) {
                if (count % 2 == 0) {
                    score = stoi(word);
                    if (score < playerScore && !written) {
                        writeNewScoreToVector(playerScore, pos, position, scores, written);
                    }
                }
                count++;
            }
        }
        if (!written && position < 10) {
            writeNewScoreToVector(playerScore, pos, position, scores, written);
        }
    }
    else {
        cout << "File failed to display" << endl;
    }

    inFile.close();
    if (!written) {
        displayScore(fileName);
        gotoxy(22, 17);cout << "Your score: " << score << endl;
        system("pause>nul");
        system("cls");
        return;
    }
    string name = "";
    char ch;
    int i = 0;
    for (auto el : scores) {
        if (!pos && !i) {
            cout << "   " << el;
        }
        else if (i == pos * 2 - 1) {

            cout << el << "   ";
        }
        else {
            cout << el;
        }
        ++i;
    }

    cout << endl << "Please enter your name in Leading board..." << endl;
    int x = 0;
    gotoxy(0, pos);
    while (x < 3) {
        ch = _getch();
        name += ch;
        gotoxy(0, pos); cout << name;
        x++;
    }

    scores.insert(scores.begin() + (pos * 2), name);
    writeScoresToFile(fileName, scores);

    system("pause>nul");
    displayScore(fileName);
    system("pause>nul");
    system("cls");
    color(INITIAL);
}