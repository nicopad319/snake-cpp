#include <iostream>
#include "snake.h"
#include "globals.h"
#include "game.h"
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

Game::Game() {
    _isOver = false;
    _score = 0;
    _foodPos = generateFood();
    _currentDirection = 'd'; //initial direction is right
    showStartScreen();
    chooseDiff();
}

Game::~Game() {
    //no allocated memory to free
}

void Game::showStartScreen() {
    system("cls"); //clear screen
    cout << "Welcome to Snake Game!" << endl;
    cout << "Controls: W = Up, A = Left, S = Down, D = Right" << endl;
    cout << "Press any key to start..." << endl;
    _getch(); //wait for user input
}

void Game::chooseDiff() {
    std::cout << "Choose difficulty:" << std::endl;
    std::cout << "  easy   - walls only, no self collision" << std::endl;
    std::cout << "  normal - walls and self collision" << std::endl;
    std::cout << "  hard   - normal + barriers spawn on each fruit collected" << std::endl;
    std::cout << "\nEnter difficulty: ";
    std::cin >> _difficulty;
    for (char& c : _difficulty) c = tolower(c);

    while (_difficulty != "easy" && _difficulty != "normal" && _difficulty != "hard") {
        std::cout << "Invalid. Choose difficulty (easy, normal, hard): ";
        std::cin >> _difficulty;
        for (char& c : _difficulty) c = tolower(c);
    }
}

Position Game::generateFood() {
    Position foodPos;
    bool collision;
    do {
        collision = false;
        foodPos.x = rand() % WIDTH;
        foodPos.y = rand() % HEIGHT;
        for (int i = 0; i < _snake.getLength(); i++) {
            if (foodPos.x == _snake.segmentPosition(i).x &&
                foodPos.y == _snake.segmentPosition(i).y) {
                collision = true;
                break;
            }
        }
    } while (collision);
    return foodPos;
}

void Game::generateWalls() {
    Position wallPos;
    bool collision;
    do {
        collision = false;
        wallPos.x = rand() % WIDTH;
        wallPos.y = rand() % HEIGHT;
        // check snake segments
        for (int i = 0; i < _snake.getLength(); i++) {
            if (wallPos.x == _snake.segmentPosition(i).x &&
                wallPos.y == _snake.segmentPosition(i).y) {
                collision = true;
                break;
            }
        }
        // check food
        if (wallPos.x == _foodPos.x && wallPos.y == _foodPos.y) {
            collision = true;
        }
        // check existing walls
        for (int i = 0; i < _walls.size(); i++) {
            if (wallPos.x == _walls[i].x && wallPos.y == _walls[i].y) {
                collision = true;
                break;
            }
        }
    } while (collision);
    _walls.push_back(wallPos);
}

char Game::readInput() {
    char input;
    std::cin >> input;
    input = tolower(input);
    if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
        return input;
    }
    return ' '; //return space if invalid input
}

void Game::checkCollision() {
    Position headPos = _snake.headPosition();
    //wall collision (all diffs)
    if (headPos.x < 0 || headPos.x >= WIDTH || headPos.y < 0 || headPos.y >= HEIGHT) {
        _isOver = true;
    }
    //self collision (normal and hard)
    if (_difficulty == "normal" || _difficulty == "hard") {
        for (int i = 1; i < _snake.getLength(); i++) {
            if (headPos.x == _snake.segmentPosition(i).x && headPos.y == _snake.segmentPosition(i).y) {
                _isOver = true;
                break;
            }
        }
    }
    if (_difficulty == "hard") {
        //wall collision (hard)
        for (int i = 0; i < _walls.size(); i++) {
            if (headPos.x == _walls[i].x && headPos.y == _walls[i].y) {
                _isOver = true;
                break;
            }
        }
    }
}

void Game::checkFood() {
    Position headPos = _snake.headPosition();
    if (headPos.x == _foodPos.x && headPos.y == _foodPos.y) {
        _snake.grow();
        _score++;
        _foodPos = generateFood();
        if (_difficulty == "hard") {
            generateWalls();
        }
    }
}

void Game::drawBoard() {
    system("cls"); //clear screen
    cout << "Score: " << _score << "  Difficulty: " << _difficulty << endl;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == _foodPos.x && y == _foodPos.y) {
                cout << "*"; //draw food
            } 
            else {
                bool isWall = false;
                for (int i = 0; i < _walls.size(); i++) {
                    if (x == _walls[i].x && y == _walls[i].y) {
                        isWall = true;
                        break;
                    }
                }

                bool isSnakeSegment = false;
                for (int i = 1; i < _snake.getLength(); i++) {
                    if (x == _snake.segmentPosition(i).x && y == _snake.segmentPosition(i).y) {
                        isSnakeSegment = true;
                        break;
                    }
                }
                if (isWall) {
                    cout << "#"; //draw wall
                }
                else if (x == _snake.headPosition().x && y == _snake.headPosition().y) {
                    cout << "@"; //draw snake head
                }
                else if (isSnakeSegment) {
                    cout << "O"; //draw snake segment
                } else {
                    cout << "."; //draw empty space
                }
            }
        }
        cout << endl; // new row
    }
}

void Game::run() {
    while (!_isOver) {
        drawBoard();
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                _currentDirection = input;
                if (input == 'w' && _currentDirection != 's') _currentDirection = 'w';
                else if (input == 's' && _currentDirection != 'w') _currentDirection = 's';
                else if (input == 'a' && _currentDirection != 'd') _currentDirection = 'a';
                else if (input == 'd' && _currentDirection != 'a') _currentDirection = 'd';
            }
        }
        _snake.move(_currentDirection);
        checkCollision();
        checkFood();
        Sleep(max(50, 200 - (_score * 2))); //delay based on score, minimum 50ms
    }
    std::cout << "Game Over! Your score: " << _score << std::endl;
}