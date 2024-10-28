#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
const int MAX_SNAKE_LENGTH = 100;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    int grid[HEIGHT][WIDTH]; 
    pair<int, int> snake[MAX_SNAKE_LENGTH];
    pair<int, int> food; 
    Direction dir;
    bool gameOver;
    int score;
    int snakeLength;
    
    
    void moveSnake() {
    pair<int, int> head = snake[0];
    pair<int, int> newHead = head;

    switch (dir) {
        case LEFT: newHead.first--; break;
        case RIGHT: newHead.first++; break;
        case UP: newHead.second--; break;
        case DOWN: newHead.second++; break;
        default: break;
    }

    if (newHead.first < 0 || newHead.first >= WIDTH || 
        newHead.second < 0 || newHead.second >= HEIGHT ||
        findSnake(newHead)) {
        gameOver = true;
        return;
    }

    for (int i = snakeLength; i > 0; --i) {
        snake[i] = snake[i - 1];
    }
    snake[0] = newHead;

    if (newHead == food) {
        score++;
        snakeLength++;
        placeFood();
    }
}

bool findSnake(pair<int, int> position) {
    for (int i = 1; i < snakeLength; ++i) {
        if (snake[i] == position) {
            return true;
        }
    }
    return false;
}
    
}