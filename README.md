# SNAKE-GAME-TEAM-GENERAL


A simple console-based Snake game implemented in C++ using Windows API for graphics and sound. The game includes difficulty selection, background music, and a game-over sound effect.

## Features
- **Classic Snake Gameplay**: Move the snake to eat food and grow.
- **Difficulty Levels**: Choose between Easy, Medium, and Hard.
- **Sound Effects**: Background music and game-over sound.
- **Colorful Console Graphics**: Uses Windows API for colored output.

## Controls
- `W` - Move Up
- `A` - Move Left
- `S` - Move Down
- `D` - Move Right
- `X` - Exit the Game

## How to Run
1. **Compile the Code**
   ```sh
   g++ snake_game.cpp -o snake_game -lwinmm
   ```
   *(Ensure MinGW is installed if using Windows.)*

2. **Run the Executable**
   ```sh
   snake_game.exe
   ```

## Dependencies
- Windows OS (due to `windows.h` and `conio.h` usage)
- MinGW (for compiling with `g++`)
- `bgm.wav` and `over.wav` (place in the same directory as the executable)

## Future Improvements
- Smooth rendering without `system("cls")`
- Pause functionality
- Customizable controls
- High score tracking

## License
This project is open-source and free to use. Modify and improve as you like!

---

Enjoy the game! 🐍
