# Snake in C++

A terminal-based Snake game built in C++ with three difficulty modes. 
My first C++ project, built to learn the language and core game loop concepts.

## Difficulties
- **Easy** — wall collisions only, no self collision
- **Normal** — wall and self collision
- **Hard** — normal rules + barriers spawn each time you collect fruit

## Controls
- `W A S D` to move
- Snake moves automatically once the game starts

## How to Run
Windows only. Requires a C++ compiler (MinGW recommended).

Clone the repo, then in your terminal:
```
g++ main.cpp snake.cpp game.cpp -o snake
./snake
```

## Built With
- C++
- Windows API (`conio.h`, `windows.h`) for real-time input and timing

## Author
Nicolas Padilla — [github.com/nicopad319](https://github.com/nicopad319)