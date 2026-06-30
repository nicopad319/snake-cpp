#ifndef SNAKE_H
#define SNAKE_H
#include "globals.h"
#include <vector>
class Snake {
public:
    Snake(); //constructor
    ~Snake(); //destructor
    void move(char direction);
    void grow();
    int getLength();
    Position headPosition();
    Position segmentPosition(int index);

private:
    std::vector<Position> _segments;
};



#endif