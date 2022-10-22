#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>

struct Point
{
    int y, x;
};

struct Snake
{
    Point m_head;
    std::vector<Point> m_body;
    char m_headChar;
    char m_bodyChar;

    Snake(){};
    Snake(int y, int x, char headChar, char bodyChar)
    {
        m_bodyChar = bodyChar;
        m_headChar = headChar;
        m_head = (Point){y, x};
        for (size_t i = 0; i < 5; i++)
        {
            m_body.push_back((Point){y, x+i});
        }
    };
};

class SnakeGame
{
private:
    int points, speed, maxwidth, maxheight;
    int game_max_x, game_max_y;

    char direction, foodChar;

    WINDOW *game;
    WINDOW *scoreboard;
    bool get;
    Snake m_snake;
    // snakebody food;
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