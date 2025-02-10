#include <iostream>
#include <vector>
#include <conio.h>  
#include <windows.h> 
#include <cstdlib>   
#include <ctime>
#include <mmsystem.h>  // For sound

#pragma comment(lib, "winmm.lib")  // Link sound library

using namespace std;

class Snake {
private:
    vector<pair<int, int>> body;
    int dx, dy;

public:
    Snake(int startX, int startY) {
        body.push_back({startX, startY});
        dx = 1; dy = 0; // Start moving right
    }

    void setDirection(int newDx, int newDy) {
        if ((dx == 0 && newDx != 0) || (dy == 0 && newDy != 0)) { 
            if (!(dx == -newDx && dy == -newDy)) { 
                dx = newDx;
                dy = newDy;
            }
        }
    }

    void move() {
        pair<int, int> newHead = body.front();
        newHead.first += dx;
        newHead.second += dy;
        body.insert(body.begin(), newHead);
        body.pop_back();
    }

    void grow() { 
        body.push_back(body.back()); 
    }

    vector<pair<int, int>> getBody() { return body; }

    bool collidesWith(int x, int y) {
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i].first == x && body[i].second == y) return true;
        }
        return false;
    }

    pair<int, int> getHead() { return body.front(); }
};

class SnakeGame {
private:
    int width, height;
    int foodX, foodY;
    int score;
    bool gameOver;
    Snake snake;

public:
    SnakeGame(int w, int h) : width(w), height(h), snake(w / 2, h / 2) {
        gameOver = false;
        score = 0;
        srand(time(0));
        spawnFood();
    }

    void spawnFood() {
        do {
            foodX = rand() % (width - 2) + 1;
            foodY = rand() % (height - 2) + 1;
        } while (snake.collidesWith(foodX, foodY));
    }

   

    void playBGM() {
        PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP);
    }

    void playOver(){
        PlaySound(TEXT("over.wav"),NULL,SND_ASYNC| SND_LOOP);
    }

    int getScore() { return score; }

    void input() {
        if (_kbhit()) { 
            switch (_getch()) {
                case 'a': snake.setDirection(-1, 0); break;
                case 'd': snake.setDirection(1, 0); break;
                case 'w': snake.setDirection(0, -1); break;
                case 's': snake.setDirection(0, 1); break;
                case 'x': gameOver = true; break;
                default: break;
            }
        }
    }

    void update() {
        snake.move();
        auto head = snake.getHead();

        if (head.first <= 0 || head.first >= width - 1 || head.second <= 0 || head.second >= height - 1) {
            gameOver = true;
        }

        if (snake.collidesWith(head.first, head.second)) {
            gameOver = true;
        }

        if (head.first == foodX && head.second == foodY) {
            snake.grow();
            score += 1;
            spawnFood();
        }
    }

    void clearScreen() {
        system("cls");
    }

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void draw() {
        clearScreen();

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    setColor(5);
                    cout << "*";
                } else if (j == foodX && i == foodY) {
                    setColor(4);
                    cout << "&";
                } else {
                    bool printed = false;
                    for (auto segment : snake.getBody()) {
                        if (segment.first == j && segment.second == i) {
                            setColor(2);
                            cout << "O";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) cout << " ";
                }
            }
            cout << endl;
        }
        setColor(7);
        cout << "Score: " << score << "\n";
        cout << "Use WASD to move. Press X to exit.\n";
    }

    bool isGameOver() { 
        return gameOver; 
    }
};

int main() {
    int x;

    cout << "Choose difficulty:-" << endl 
         << "1. Easy" << endl 
         << "2. Medium" << endl 
         << "3. Hard" << endl;

    cin >> x;

    SnakeGame game(40, 20);

    cout << "Press any key to start the game..." << endl;
    _getch();

    game.playBGM(); // Start background music

    int speed = (x == 1) ? 100 : (x == 2) ? 50 : 20; // Adjust speed for difficulty

    while (!game.isGameOver()) {
        game.input();
        game.update();
        game.draw();
        Sleep(speed);
    }

    PlaySound(NULL, NULL, 0); // Stop BGM when game is over

    for(int i = 0;i<3;i++){
       
       game.playOver();


        system("cls");

        cout << "HAHA!";

        Sleep(500);

        system("cls");

        cout<< "YOU LOSE!"<<endl;

        Sleep(500);

        
 
    } 

    PlaySound(NULL,NULL,0);

    cout << "Game Over! Final Score: " << game.getScore() << "\n";

    return 0;
}
