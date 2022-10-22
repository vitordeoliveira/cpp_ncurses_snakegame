#include "snake.hpp"




SnakeGame::SnakeGame()
{
    initscr();
    srand(time(NULL));
    getmaxyx(stdscr, maxheight, maxwidth);
    int borderGameY = maxheight - (maxheight * 0.1);
    int borderScoreY = maxheight * 0.11;

    game = newwin(borderGameY, maxwidth, 0, 0);
    scoreboard = newwin(borderScoreY, maxwidth, maxheight * 0.9, 0);

    getmaxyx(game, game_max_y, game_max_x);

    refresh();

    box(game, 0, 0);
    box(scoreboard, 0, 0);

    m_snake = Snake(game_max_y/2, game_max_x/2, '@', 'o');

    for (size_t i = 0; i < m_snake.m_body.size()+1; i++)
    {
        mvwaddch(game, m_snake.m_body[0].y, m_snake.m_body[0].x+i, m_snake.m_bodyChar);
    }
    

    for (size_t i = 0; i < 5; i++)
    {
        createFood();
    }

    mvwprintw(scoreboard, 5, 5, "Greeter");
    wrefresh(game);
    wrefresh(scoreboard);
    getch();
}

void SnakeGame::createFood()
{
    while (1)
    {
        int randX = rand() % game_max_x;
        int randY = rand() % game_max_y;

        mvwaddch(game, randY, randX, '@');

        //if is inside the snake continue;
        if (randX == 0 || randY == 0 || randX == game_max_x-1 || randY == game_max_y-1)
        {
            continue;
        }

        wrefresh(game);
        break;
    }
}

void SnakeGame::updateSnakePosition()
{

}

SnakeGame::~SnakeGame()
{
    endwin();
}