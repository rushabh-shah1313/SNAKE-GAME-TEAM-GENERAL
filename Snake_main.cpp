#include <iostream>
#include <vector>
#include <conio.h>  
#include <windows.h> 
#include <cstdlib>   
#include <ctime>
#include "game_mechanics.h"
#include <mmsystem.h>  // For sound
#pragma comment(lib, "winmm.lib")  // Link sound library
using namespace std;



int main() {
    int x;
    char c = 'A';
    int highscore = -4;
    do{
        
        cout << "Choose difficulty:-" << endl 
            << "1. Easy" << endl 
            << "2. Medium" << endl 
            << "3. Hard" << endl;

        cin >> x;
        
        SnakeGame game(40, 20);
        game.HighScore(highscore);

        cout << "Press any key to start the game..." << endl;
        _getch();

        game.playBGM(); // Start background music

        int speed = (x == 1) ? 100 : (x == 2) ? 20 : (x == 3) ? 10 : 0; // Adjust speed for difficulty
        
        system("cls");
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
        if(highscore<game.getScore()){
            highscore = game.getScore();
        }

        cout << "Game Over! Final Score: " << game.getScore() << "\n";
        cout << "Your Highest Score is : " << highscore << endl;
        cout << "Press x to restart :" << endl;
        cin >> c;
        
    }while(c == 'x');
    return 0;
}
