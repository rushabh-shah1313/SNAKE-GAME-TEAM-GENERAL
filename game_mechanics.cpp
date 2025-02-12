#include "game_mechanics.h"


Snake::Snake(int startX, int startY) {
    body.push_back({startX, startY});
    body.push_back({startX-1,startY});
    body.push_back({startX-2,startY});
    dx = 1;
    dy = 0;
}

void Snake::setDirection(int newDx, int newDy) {
    if ((dx == 0 && newDx != 0) || (dy == 0 && newDy != 0)) { 
        if (!(dx == -newDx && dy == -newDy)) { 
            dx = newDx;
            dy = newDy; 
        }
    }
}

void Snake::move() {
    pair<int, int> newHead = body.front();
    newHead.first += dx;
    newHead.second += dy;
    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::grow() { 
    body.push_back(body.back()); 
}

void Snake::shrink(){
    if(!body.empty()){
       body.pop_back();
    }
}

void Snake::reset(int startX, int startY) {
    body.clear();
    body.push_back({startX, startY});
    dx = 1;
    dy = 0;
}



vector<pair<int, int>> Snake::getBody() { return body; }

bool Snake::collidesWith(int x, int y) {
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i].first == x && body[i].second == y) return true;
    }
    return false;
}

pair<int, int> Snake::getHead() { return body.front(); }

SnakeGame::SnakeGame(int w, int h) : width(w), height(h), snake(w / 2, h / 2) {
    gameOver = false;
    score = 0;
    srand(time(0));
    spawnFood();
    spawnPoison();
}

void SnakeGame::spawnFood() {
    do {
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
    } while (snake.collidesWith(foodX, foodY));
}

void SnakeGame ::spawnPoison() {
     do{
         poisonX = rand() % (width - 2) + 1;
         poisonY = rand() % (height - 2) + 1;
     } while(snake.collidesWith(poisonX,poisonY));

}

void SnakeGame::playBGM() {
    PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void SnakeGame::playOver() {
    PlaySound(TEXT("over.wav"), NULL, SND_ASYNC | SND_LOOP);
}




int SnakeGame::getScore() { return score; }

void SnakeGame::input() {
    if (_kbhit()) { 
        switch (_getch()) {
            case 'a': snake.setDirection(-1, 0); break;
            case 'd': snake.setDirection(1, 0); break;
            case 'w': snake.setDirection(0, -1); break;
            case 's': snake.setDirection(0, 1); break;
            case 'x': restartGame(); break;
            default: break;
        }
    }
}

void SnakeGame::update() {
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

    if(head.first == poisonX && head.second == poisonY){
        snake.shrink();
          if (snake.getBody().empty()) {
        gameOver = true;
    }
        score -= 1;
        spawnPoison();
    }
}

void SnakeGame::clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);
}

void SnakeGame::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SnakeGame::draw() {
    clearScreen(); 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                setColor(5);
                cout << "*";
            } 
            else if (j == foodX && i == foodY) {
                setColor(4);
                cout << "&";
                
            } 
            else if(j== poisonX && i == poisonY){
                setColor(3);
                cout<<"#";
            }
            
            else {
                bool printed = false;
                for (auto segment : snake.getBody()) {
 
               if(segment.first == j && segment.second == i) {
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
    setColor(3);
    cout << "Score: " << score << "\n";
    cout << "Use WASD to Move. Press X to Restart.\n";
}

 void SnakeGame::restartGame() {
    snake.reset(width / 2, height / 2);  
    score = 0;  
    gameOver = false;  
    spawnFood();
    spawnPoison();
    system("cls");  
    draw();  
}


bool SnakeGame::isGameOver() { 
    return gameOver; 
}
