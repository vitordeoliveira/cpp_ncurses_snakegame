#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>

struct Point
{
    int y, x;

    bool operator==(Point p)
    {
        return x == p.x && y == p.y;
    }

};

struct Snake
{
    Point m_head;
    Point m_tail;
    std::vector<Point> m_body;
    char m_headChar;
    char m_bodyChar;

    Snake();
    Snake(int y, int x, char headChar, char bodyChar);
};

class SnakeGame
{
private:
    int points, speed, maxwidth, maxheight;
    int game_max_x, game_max_y;
    int delay;

    char direction, foodChar;

    Point food;
    WINDOW *game;
    WINDOW *scoreboard;
    bool get, doubled;
    Snake m_snake;
    // std::vector<snakebody> snake;

    void createFood();
    bool collision();
    void moveSnake();
    void updateSnakePosition();

public:
    SnakeGame(/* args */);
    ~SnakeGame();
    void start();
};

// #ifdef SNAKE_HPP
// #define SNAKE_HPP
// #endif