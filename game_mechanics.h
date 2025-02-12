
#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")  // Link sound library

using namespace std;

class Snake {
private:
    vector<pair<int, int>> body;
    int dx, dy;

public:
    Snake(int startX, int startY);
    void reset(int startX, int startY);
    void setDirection(int newDx, int newDy);
    void move();
    void grow();
    void shrink();
    bool collidesWith(int x, int y);
    pair<int, int> getHead();
    vector<pair<int, int>> getBody();
};

// SnakeGame Class
class SnakeGame {
private:
    int width, height;
    int foodX, foodY;
    int poisonX, poisonY;
    int score;
    bool gameOver;
    Snake snake;

public:
    SnakeGame(int w, int h);
    
    void spawnFood();
    void spawnPoison();
    void playBGM();
    void playOver();
    void input();
    void update();
    void clearScreen();
    void setColor(int color);
    void draw();
    void restartGame();
    bool isGameOver();
    int getScore();
};


