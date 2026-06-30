#include <iostream>
#include "snake.h"
#include "globals.h"
#include <stdexcept>
using namespace std;

Snake::Snake() {
    _segments.push_back({WIDTH / 2, HEIGHT / 2});
}

Snake::~Snake() {
}

void Snake::move(char direction) {
    Position newHead = _segments[0];
    if (direction == 'w') {
        newHead.y--;
    } else if (direction == 's') {
        newHead.y++;
    } else if (direction == 'a') {
        newHead.x--;
    } else if (direction == 'd') {
        newHead.x++;
    }
    //update all segment positions
    for (int i = _segments.size() - 1; i > 0; i--) {
        _segments[i] = _segments[i - 1];
    }
    _segments[0] = newHead;
}

void Snake::grow() {
    _segments.push_back(_segments.back());
}

int Snake::getLength() {
    return _segments.size();
}

Position Snake::headPosition() {
    return _segments[0];
}

Position Snake::segmentPosition(int index) {
    if (index < 0 || index >= _segments.size()) {
        throw std::out_of_range("Index out of range");
    }
    return _segments[index];
}