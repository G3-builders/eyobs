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
    

    public:
    SnakeGame() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                grid[i][j] = 0;
            }
        }
        snake[0] = make_pair(WIDTH / 2, HEIGHT / 2);
        snakeLength = 1; 
        dir = STOP;
        gameOver = false;
        score = 0;
        placeFood();
    }

    void placeFood() {
        while (true) {
            int x = rand() % WIDTH;
            int y = rand() % HEIGHT;
            if (grid[y][x] == 0) {
                food = make_pair(x, y);
                break;
            }
        }
    }
    
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

void display() {
    system("cls");
    
    for (int x = 0; x < WIDTH + 2; x++) {
        cout << '#';
    }
    cout << endl;

    for (int y = 0; y < HEIGHT; y++) {
        cout << '#';
        for (int x = 0; x < WIDTH; x++) {
            if (make_pair(x, y) == snake[0]) {
                cout << 'O';
            } else if (findSnake(make_pair(x, y))) {
                cout << 'X';
            } else if (make_pair(x, y) == food) {
                cout << '*';
            } else {
                cout << ' ';
            }
        }
        cout << '#' << endl;
    }

    for (int x = 0; x < WIDTH + 2; x++) {
        cout << '#';
    }
    cout << endl;

    cout << "Score: " << score << endl;
}
    
}