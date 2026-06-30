#ifndef GAME_H
#define GAME_H
#include "globals.h"
#include "snake.h"
#include <string>
#include <cctype>
#include <vector>

class Game {
public:
    Game();
    ~Game();
    void chooseDiff();
    void run();
    char readInput();
    void checkCollision();
    void drawBoard();
    Position generateFood();
    void checkFood();
    void generateWalls();
    void showStartScreen();

private:
    Snake _snake;
    bool _isOver;
    int _score;
    Position _foodPos;
    std::string _difficulty;
    std::vector<Position> _walls;
    char _currentDirection;
};

#endif